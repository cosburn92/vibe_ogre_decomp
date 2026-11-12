#!/usr/bin/env python3
"""After a `make`, report which functions of a source file match the baserom.

usage: python3 tools/funcdiff.py src/45CB0.c

Reads the function names defined in the file (C definitions and INCLUDE_ASM stubs), finds each one
in build/ogrebattle64.map under this file's object (build/src/<OFF>.o; overlays share VRAM, so only
that object's symbols count), bounds it by the next function symbol of the same object, and compares
those bytes of build/ogrebattle64.us.z64 against baserom/baserom.us.z64. The ROM address comes from
the file name, which is the segment's ROM offset. Functions after a size mismatch shift, so fix the
first failing one first.
"""
import os
import re
import sys

SECTION = re.compile(r"^ (\.text|\.data|\.rodata|\.bss)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)")
SYMBOL = re.compile(r"^\s+0x([0-9a-f]+)\s+([A-Za-z_][A-Za-z0-9_]*)$")
NOT_FUNC = re.compile(r"(L[0-9A-F]{8}|jtbl_|D_)")


def object_text(obj):
    """(VRAM start, size, [(vram, name)]) of obj's .text, from the link map."""
    start = size = None
    syms = []
    current = None
    for line in open("build/ogrebattle64.map"):
        m = SECTION.match(line)
        if m:
            current = (m.group(1), m.group(4))
            if current == (".text", obj):
                start, size = int(m.group(2), 16), int(m.group(3), 16)
            continue
        m = SYMBOL.match(line)
        if m and current == (".text", obj) and not NOT_FUNC.match(m.group(2)):
            syms.append((int(m.group(1), 16), m.group(2)))
    return start, size, sorted(set(syms))


def main():
    src = sys.argv[1]
    text = open(src).read()
    names = re.findall(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", text)
    names += re.findall(r"^[A-Za-z_][\w \*]*?\b(\w+)\([^;{]*\)\s*\{", text, re.M)
    seg = os.path.splitext(os.path.basename(src))[0]
    start, size, syms = object_text(f"build/src/{seg}.o")
    if start is None:
        print(f"build/src/{seg}.o: no .text in the map")
        return 1
    rom_start = int(seg, 16)
    addr = {n: v for v, n in syms}
    built = open("build/ogrebattle64.us.z64", "rb").read()
    base = open("baserom/baserom.us.z64", "rb").read()
    for n in sorted(set(names), key=lambda n: addr.get(n, 0)):
        if n not in addr:
            print(f"  {n}: not in map")
            continue
        v = addr[n]
        nxt = min([w for w, _ in syms if w > v] or [start + size])
        r0, r1 = rom_start + v - start, rom_start + nxt - start
        ok = built[r0:r1] == base[r0:r1]
        print(f"  {'OK  ' if ok else 'DIFF'} {n}  rom 0x{r0:X} size 0x{r1 - r0:X}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
