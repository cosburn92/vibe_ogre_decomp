"""Cross-file C interface check.

Every declaration of a function, and every call to it, should agree with the function's
C definition, even when they sit in different source files. Our compiler never sees two
files at once, so nothing else catches a prototype that drops an argument the code
passes straight through in a register, or declares s32 where the definition takes f32.
OB64-Decomp's verifier started checking this after our PR #3; this is the same check
done with libclang so we can run it on our own tree and on exported targets.

usage:
  ilint.py [options] PATH ...
    PATH          .c files, or directories searched for them
    -I DIR        include directory (repeatable)
    -D NAME[=V]   preprocessor define (repeatable)
    --json FILE   also write every finding as JSON
    --nodef       also print findings for functions that have no C definition yet

  ours:  ilint.py -I include -I src -D_LANGUAGE_C -D__GNUC__=2 src
  OB64:  ilint.py -I include src

needs: pip install libclang  (kept in build/ilint-venv)
Exit status is 1 when there is any error.

Rules (the same ones OB64's tools/lib/c_interfaces.js applies):
  * A declaration must have the definition's return type, parameter count and
    parameter types. Typedefs are expanded, so `u32` and `unsigned int` agree;
    signedness and `const` on a pointed-to type count, top-level `const` doesn't.
  * A call must pass as many arguments as the definition takes (at least as many,
    for a variadic one).
Findings come in three severities:
  error  disagrees with the C definition: OB64's verifier would reject it
  gap    can't be compared by OB64's rules: struct or function-pointer types, or a
         `f()` declaration with no prototype. Their maintainers review these by hand.
  nodef  the function is still assembly, and its declarations disagree with each
         other. Nothing upstream checks this yet; it becomes an error once someone
         writes the function in C.
Static functions and gnu89 `extern inline` definitions are skipped: neither is the
definition other files link against.
"""
import argparse
import json
import os
import sys
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor

import clang.cindex as ci

K = ci.CursorKind
T = ci.TypeKind

CLANG_ARGS = ['-target', 'mips-unknown-none', '-std=gnu89', '-fno-builtin',
              '-Wno-everything', '-ferror-limit=0']

SIGNED_INTS = {T.CHAR_S, T.SCHAR, T.SHORT, T.INT, T.LONG, T.LONGLONG, T.ENUM}
UNSIGNED_INTS = {T.BOOL, T.CHAR_U, T.UCHAR, T.USHORT, T.UINT, T.ULONG, T.ULONGLONG}
FLOATS = {T.FLOAT, T.DOUBLE, T.LONGDOUBLE}

# Difference classes that OB64's rules can't decide (see "gap" above).
GAP_CLASSES = {'struct', 'noproto'}


# ---- types ------------------------------------------------------------------------
# A type is reduced to a small tuple (kind, detail, const) so two files' spellings
# can be compared:
#   ('int', (size, signed), const)   ('float', size, const)   ('void', None, const)
#   ('ptr', pointee, const)          ('rec', 'struct Tag', const)
#   ('fn', None, const)              ('other', spelling, const)

def without_sugar(t):
    """Peel typedefs and `struct X` elaborations. Returns the bare type and the last
    typedef name passed, which names an otherwise anonymous struct."""
    typedef_name = None
    while True:
        if t.kind == T.TYPEDEF:
            typedef_name = t.get_declaration().spelling
            t = t.get_declaration().underlying_typedef_type
        elif t.kind == T.ELABORATED:
            t = t.get_named_type()
        else:
            return t, typedef_name


def record_name(canonical, typedef_name):
    """`struct Tag`; for an untagged struct, its typedef name, else its size. Two files'
    private copies of a struct with different names compare different, as they would
    for a compiler that saw both files together."""
    decl = canonical.get_declaration()
    tag = decl.spelling
    if not tag or '(unnamed' in tag or '(anonymous' in tag:
        tag = ('typedef ' + typedef_name) if typedef_name else 'anon%d' % canonical.get_size()
    keyword = 'union' if decl.kind == K.UNION_DECL else 'struct'
    return keyword + ' ' + tag


def reduce_type(t):
    t, typedef_name = without_sugar(t)
    const = t.is_const_qualified()
    canonical = t.get_canonical()
    kind = canonical.kind
    if kind == T.POINTER:
        pointee = t.get_pointee() if t.kind == T.POINTER else canonical.get_pointee()
        return ('ptr', reduce_type(pointee), const)
    if kind in (T.CONSTANTARRAY, T.INCOMPLETEARRAY, T.VARIABLEARRAY):
        return ('ptr', reduce_type(canonical.element_type), const)  # parameters decay
    if kind == T.RECORD:
        return ('rec', record_name(canonical, typedef_name), const)
    if kind in (T.FUNCTIONPROTO, T.FUNCTIONNOPROTO):
        return ('fn', None, const)
    if kind == T.VOID:
        return ('void', None, const)
    if kind in SIGNED_INTS or kind in UNSIGNED_INTS:
        return ('int', (canonical.get_size(), kind in SIGNED_INTS), const)
    if kind in FLOATS:
        return ('float', canonical.get_size(), const)
    return ('other', canonical.spelling, const)


def type_text(rt):
    """Readable spelling in the project's typedef style: s32, u8 *, struct Panel *."""
    kind, detail, const = rt
    qualifier = 'const ' if const else ''
    if kind == 'ptr':
        return type_text(detail) + ' *'
    if kind == 'int':
        size, signed = detail
        return qualifier + ('s' if signed else 'u') + str(size * 8)
    if kind == 'float':
        return qualifier + ('f32' if detail == 4 else 'f64')
    if kind == 'rec':
        return qualifier + detail
    return qualifier + (kind if detail is None else str(detail))


def comparable(rt):
    """OB64 only compares types spelled from builtin scalars and pointers to them."""
    kind, detail, _ = rt
    if kind == 'ptr':
        return comparable(detail)
    return kind in ('int', 'float', 'void')


def difference(a, b):
    """The class of difference between two reduced types, or None if they agree.
    Top-level const is ignored; const on a pointee counts."""
    a, b = a[:2], b[:2]
    if a == b:
        return None
    if not (comparable(a + (False,)) and comparable(b + (False,))):
        return 'struct'
    (kind_a, detail_a), (kind_b, detail_b) = a, b
    if kind_a != kind_b:
        kinds = {kind_a, kind_b}
        if 'ptr' in kinds and ('int' in kinds or 'void' in kinds):
            return 'ptr/int'
        if 'float' in kinds:
            return 'float/int'
        if 'void' in kinds:
            return 'void/value'
        return 'kind'
    if kind_a == 'ptr':
        if detail_a[:2] == detail_b[:2]:
            return 'const'
        return 'pointee'
    if kind_a == 'int':
        return 'width' if detail_a[0] != detail_b[0] else 'sign'
    return 'width'  # float vs double


# ---- signatures -------------------------------------------------------------------

class Signature:
    """One declaration or definition of a function, as written at one place."""

    def __init__(self, cursor, where, is_definition):
        ftype = cursor.type
        storage = cursor.storage_class
        self.where = where
        self.is_definition = is_definition
        # static functions, and gnu89 `extern inline` definitions, aren't what other
        # files link against
        self.is_local = storage == ci.StorageClass.STATIC or (
            is_definition and storage == ci.StorageClass.EXTERN)
        self.has_prototype = ftype.kind == T.FUNCTIONPROTO
        self.is_variadic = self.has_prototype and ftype.is_function_variadic()
        self.returns = reduce_type(cursor.result_type)
        self.params = [reduce_type(p) for p in ftype.argument_types()] if self.has_prototype else []

    def key(self):
        return (self.returns[:2], self.has_prototype, self.is_variadic,
                tuple(p[:2] for p in self.params))

    def text(self, name):
        if not self.has_prototype:
            params = ''
        else:
            params = ', '.join(type_text(p) for p in self.params) or 'void'
            if self.is_variadic:
                params += ', ...'
        return '%s %s(%s)' % (type_text(self.returns), name, params)


def compare(decl, ref):
    """The class of the most serious way `decl` disagrees with `ref`, or None."""
    returns = difference(decl.returns, ref.returns)
    if returns and returns not in GAP_CLASSES:
        return 'return ' + returns
    if decl.is_variadic != ref.is_variadic:
        return 'variadic'
    if len(decl.params) != len(ref.params):
        return 'param count'
    params = [difference(a, b) for a, b in zip(decl.params, ref.params)]
    params = [p for p in params if p]
    hard = [p for p in params if p not in GAP_CLASSES]
    if hard:
        return hard[0]
    if returns:
        return 'return ' + returns
    return params[0] if params else None


# ---- parsing ----------------------------------------------------------------------

def parse_file(path, clang_args):
    """All function declarations and resolved calls in one translation unit, located at
    the file and line where they're written (a header's line, for a header prototype)."""
    unit = ci.Index.create().parse(path, args=CLANG_ARGS + clang_args)
    signatures, calls = [], []
    seen = set()

    def location(cursor):
        loc = cursor.location
        return '%s:%d' % (os.path.relpath(loc.file.name if loc.file else path), loc.line)

    def visit(cursor):
        for child in cursor.get_children():
            if child.kind == K.FUNCTION_DECL:
                where = location(child)
                if (child.spelling, where) not in seen:  # each header line once per file
                    seen.add((child.spelling, where))
                    signatures.append((child.spelling, Signature(child, where, child.is_definition())))
            elif child.kind == K.CALL_EXPR:
                callee = child.referenced
                if callee is not None and callee.kind == K.FUNCTION_DECL:
                    calls.append((callee.spelling, len(list(child.get_arguments())), location(child)))
            visit(child)

    visit(unit.cursor)
    return signatures, calls


def source_files(paths):
    files = []
    for path in paths:
        if os.path.isdir(path):
            for folder, _, names in os.walk(path):
                files += [os.path.join(folder, n) for n in names if n.endswith('.c')]
        else:
            files.append(path)
    return sorted(files)


# ---- checking ---------------------------------------------------------------------

def check(files, clang_args):
    signatures = defaultdict(dict)  # name -> {where: Signature}; headers repeat across files
    calls = defaultdict(set)        # name -> {(arg count, where)}
    with ThreadPoolExecutor(8) as pool:
        for sigs, cs in pool.map(lambda f: parse_file(f, clang_args), files):
            for name, sig in sigs:
                signatures[name].setdefault(sig.where, sig)
            for name, count, where in cs:
                calls[name].add((count, where))

    findings = []

    def report(name, rule, cls, severity, where, got, want, ref_where):
        findings.append(dict(symbol=name, rule=rule, cls=cls, severity=severity,
                             at=where, got=got, want=want, ref=ref_where))

    for name in sorted(set(signatures) | set(calls)):
        sigs = [s for s in signatures[name].values() if not s.is_local]
        definitions = [s for s in sigs if s.is_definition]
        if definitions:
            ref = definitions[0]
            for other in definitions[1:]:
                if other.key() != ref.key():
                    report(name, 'decl', 'redefined', 'error', other.where,
                           other.text(name), ref.text(name), ref.where)
        else:
            # No C definition: compare against the most common prototype.
            prototypes = [s for s in sigs if s.has_prototype]
            if not prototypes:
                continue
            counts = Counter(s.key() for s in prototypes)
            ref = max(prototypes, key=lambda s: counts[s.key()])

        def severity(cls):
            if not definitions:
                return 'nodef'
            return 'gap' if cls.replace('return ', '') in GAP_CLASSES else 'error'

        for decl in sigs:
            if decl is ref or decl.is_definition:
                continue
            if not decl.has_prototype or not ref.has_prototype:
                if definitions:
                    report(name, 'decl', 'noproto', 'gap', decl.where,
                           decl.text(name), ref.text(name), ref.where)
                continue
            cls = compare(decl, ref)
            if cls:
                report(name, 'decl', cls, severity(cls), decl.where,
                       decl.text(name), ref.text(name), ref.where)

        if ref.has_prototype:
            wanted = len(ref.params)
            for count, where in sorted(calls[name]):
                wrong = count < wanted if ref.is_variadic else count != wanted
                if wrong:
                    report(name, 'call', 'arg count', severity('arg count'), where,
                           '%d args' % count, ref.text(name), ref.where)
    return findings


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    ap.add_argument('-I', action='append', default=[], dest='includes', metavar='DIR')
    ap.add_argument('-D', action='append', default=[], dest='defines', metavar='NAME[=V]')
    ap.add_argument('--json', metavar='FILE')
    ap.add_argument('--nodef', action='store_true',
                    help='also print findings for functions with no C definition')
    ap.add_argument('paths', nargs='+')
    args = ap.parse_args()

    clang_args = ['-I' + i for i in args.includes] + ['-D' + d for d in args.defines]
    files = source_files(args.paths)
    findings = check(files, clang_args)
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(findings, f, indent=1)

    printed = {'error', 'gap'} | ({'nodef'} if args.nodef else set())
    for f in findings:
        if f['severity'] in printed:
            print('%-5s %-12s %s  %s\n      has  %s\n      def  %s  (%s)' % (
                f['severity'], f['cls'], f['symbol'], f['at'], f['got'], f['want'], f['ref']))

    totals = Counter(f['severity'] for f in findings)
    print('\n%d files: %d errors, %d gaps, %d nodef' % (
        len(files), totals['error'], totals['gap'], totals['nodef']))
    for (severity, cls), n in sorted(Counter((f['severity'], f['cls']) for f in findings).items()):
        print('  %-5s %-17s %d' % (severity, cls, n))
    sys.exit(1 if totals['error'] else 0)


if __name__ == '__main__':
    main()
