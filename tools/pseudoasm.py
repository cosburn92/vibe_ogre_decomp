"""Find pseudo-asm in C: code that spells out what the compiler emits instead of what
the code means. It matches, but it is hard to read, and KMC GCC usually produces the
same instructions from the plain version:

  sign bit     `~x >> 31`, `(u32)x >> 31`      ->  x >= 0, x < 0
  shift div    `(v >> 2) * 4`, `+ 7` fixup     ->  v / 4, v % 8
  cmp | cmp    `(a == 1) | (a == 2)`           ->  a == 1 || a == 2
  x ^ x        `h ^= h`                        ->  h = 0
  comma seq    `(a = f(), b = g(), a + b)`     ->  separate statements
  m2c names    temp_v0_7, var_a1_13            ->  names that say what the value is

usage: pseudoasm.py [--quiet] PATH ...   (.c files or directories)
Prints each hit as file:line function: kind: code. Exit status 1 if any.
Some hits are real bit manipulation (packing fields, hashing); read before rewriting.
Not always rewritable: OB64's func_00283E14 needs its explicit signed-quotient
correction, a plain `/` doesn't match there. Rewrite, rebuild, and keep the
spelled-out form (with a comment saying why) only when the plain one fails.
"""
import os
import re
import sys

IDIOMS = [
    ('sign bit', re.compile(r'>>\s*(?:31|0x1[fF])\b')),
    ('shift div', re.compile(r'>>\s*\d+\s*\)\s*(?:\*|<<)\s*\d')),
    ('cmp | cmp', re.compile(r'\(\s*[^()|&]*?(?:==|!=)[^()|&]*\)\s*\|(?!\|)\s*\(\s*[^()|&]*?(?:==|!=)')),
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
    hits = []
    offset = 0  # of the current line, to find the function it is in
    for lineno, line in enumerate(code.split('\n'), 1):
        for kind, pattern in IDIOMS:
            if pattern.search(line):
                owner = next((name for start, name in reversed(starts) if start <= offset), '-')
                hits.append((path, lineno, owner, kind, line.strip()))
        offset += len(line) + 1
    return hits


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
