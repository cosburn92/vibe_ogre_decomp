"""Find pseudo-asm in C: operators used to reproduce the compiler's instructions in
place of what the code does. It matches, but it hides the behavior, and KMC GCC usually
produces the same instructions from the plain version:

  signed div fixup  `if (v < 0) v += 7; v >> 3`  ->  v / 8 (and v % 8 for the remainder)
  sign bit          `~f() >> 31`, `+ (x >> 31)`  ->  f() >= 0, x < 0
  cmp | cmp         `(a == 1) | (a == 2)`        ->  a == 1 || a == 2
  x ^ x             `h ^= h`                     ->  h = 0
  comma seq         `(a = f(), b = g(), a + b)`  ->  separate statements
  m2c names         temp_v0_7, var_a1_13         ->  names that say what the value is

Bit operations that are the code's actual job are not pseudo-asm and are not flagged:
flags and masks, packing fields, unsigned shifts, `(x >> 31) & 1` reading a top bit.
Keep those as bit operations, as the original programmer evidently wrote them.

usage: pseudoasm.py [--quiet] PATH ...   (.c files or directories)
Prints each hit as file:line function: kind: code. Exit status 1 if any.
Not always rewritable: OB64's func_00283E14 needs its explicit signed-quotient
correction, a plain `/` doesn't match there. Rewrite, rebuild, and keep the
spelled-out form (with a comment saying why) only when the plain one fails.
"""
import os
import re
import sys

SHIFT31 = r'>>\s*(?:31|0x1[fF])\b'
CMP = r'==|!=|<=|>=|(?<![<-])<(?![<=])|(?<![->])>(?![>=])'  # not <<, >>, ->
IDIOMS = [
    # a negative-value correction followed by a shift: the compiler's signed division
    ('signed div fixup', re.compile(
        r'if\s*\(\s*\w+\s*<\s*0\s*\)\s*\{?\s*\w+\s*=[^;{}]*;\s*\}?[^{}]{0,240}?>>\s*(?:\d|0x)', re.S)),
    # the sign bit used as a value: complemented, or added/multiplied into a result
    ('sign bit', re.compile(r'~[^;]*' + SHIFT31 + r'|[-+*]\s*\(+\s*(?:\(u32\)\s*)?[\w\[\]().>-]+\s*' + SHIFT31
                            + r'|' + SHIFT31 + r'\s*\)*\s*[-+*/]')),
    # comparisons combined with a bitwise | (a boolean || written the way it compiles)
    ('cmp | cmp', re.compile(r'(?:' + CMP + r')[^()|;]*\)\s*\|(?![|=])\s*\(+[^()|;]*?(?:' + CMP + r')')),
    ('x ^ x', re.compile(r'\b(\w+(?:->\w+|\.\w+)*)\s*\^=?\s*\1\b')),
    ('comma seq', re.compile(r'\(\s*\w+\s*=[^;()]*(?:\([^;()]*\)[^;()]*)*,\s*\w+\s*=[^;]*\)\s*[;:]')),
    ('m2c names', re.compile(r'\b(?:temp|var|phi)_(?:[atvs]\d|f\d+)\w*\b')),
]
FUNCTION = re.compile(r'^[A-Za-z_][^\n;()]*?\b(\w+)\s*\([^;{]*\)\s*\{', re.M)


def blank(match):
    """Replace a comment or parked block with as many newlines, keeping line numbers."""
    return '\n' * match.group(0).count('\n')


def matching_code(text):
    text = re.sub(r'/\*.*?\*/', blank, text, flags=re.S)
    text = re.sub(r'//[^\n]*', '', text)
    # parked rewrites are not the code that builds
    return re.sub(r'#ifdef NON_MATCHING.*?#else', blank, text, flags=re.S)


def scan(path):
    code = matching_code(open(path, encoding='utf-8', errors='replace').read())
    starts = [(m.start(), m.group(1)) for m in FUNCTION.finditer(code)]
    lines = code.split('\n')
    hits = set()
    for kind, pattern in IDIOMS:
        for m in pattern.finditer(code):
            owner = next((name for start, name in reversed(starts) if start <= m.start()), '-')
            lineno = code.count('\n', 0, m.start()) + 1
            hits.add((path, lineno, owner, kind, lines[lineno - 1].strip()))
    return sorted(hits)


def files(paths):
    for path in paths:
        if os.path.isdir(path):
            for folder, _, names in os.walk(path):
                yield from (os.path.join(folder, n) for n in sorted(names) if n.endswith('.c'))
        else:
            yield path


def main():
    args = sys.argv[1:]
    quiet = '--quiet' in args
    paths = [a for a in args if a != '--quiet']
    if not paths:
        sys.exit(__doc__)
    hits = [h for f in files(paths) for h in scan(f)]
    if not quiet:
        for path, line, owner, kind, code in hits:
            print('%s:%d %s: %s: %s' % (os.path.relpath(path), line, owner, kind, code[:100]))
    print('%d pseudo-asm hits in %d functions' % (len(hits), len({(h[0], h[2]) for h in hits})))
    sys.exit(1 if hits else 0)


if __name__ == '__main__':
    main()
