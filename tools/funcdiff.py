#!/usr/bin/env python3
"""After a `make`, report which functions of a source file match the baserom.

usage: python3 tools/funcdiff.py src/45CB0.c

Reads the function names defined in the file (C definitions and INCLUDE_ASM stubs), finds each one's
ROM range in build/ogrebattle64.map (the next symbol or section end bounds it), and compares those
bytes of build/ogrebattle64.us.z64 against baserom/baserom.us.z64. Functions after a size mismatch
shift, so fix the first failing one first.
"""
import re
import sys


def map_symbols():
    """[(vram, name)] for every symbol in .text sections, plus the ROM offset of each section."""
    syms, text = [], open("build/ogrebattle64.map").read().splitlines()
    sect = None
    for line in text:
        m = re.match(r"^ (\.text|\.data|\.rodata|\.bss)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)", line)
        if m:
            sect = (m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4))
            continue
        m = re.match(r"^\s+0x([0-9a-f]+)\s+([A-Za-z_][A-Za-z0-9_]*)$", line)
        if m and sect and sect[0] == ".text":
            syms.append((int(m.group(1), 16), m.group(2), sect))
    return syms


def load_addresses():
    """[(vram, rom)] of every segment, from the linker script's <seg>_ROM_START / <seg>_VRAM symbols."""
    m = open("build/ogrebattle64.map").read()
    rom = dict((n, int(v, 16)) for v, n in re.findall(r"\s+0x([0-9a-f]+)\s+(\w+)_ROM_START\b", m))
    vram = dict((n, int(v, 16)) for v, n in re.findall(r"\s+0x([0-9a-f]+)\s+(\w+)_VRAM\b", m))
    return [(vram[n], rom[n]) for n in rom if n in vram]


def main():
    src = sys.argv[1]
    text = open(src).read()
    names = re.findall(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", text)
    names += re.findall(r"^[A-Za-z_][\w \*]*?\b(\w+)\([^;{]*\)\s*\{", text, re.M)
    syms = sorted({(v, n) for v, n, _ in map_symbols()})
    addr = {n: v for v, n in syms}
    segs = sorted(load_addresses())
    built = open("build/ogrebattle64.us.z64", "rb").read()
    base = open("baserom/baserom.us.z64", "rb").read()
    for n in sorted(set(names), key=lambda n: addr.get(n, 0)):
        if n not in addr:
            print(f"  {n}: not in map")
            continue
        v = addr[n]
        nxt = min([w for w, _ in syms if w > v] or [v + 4])
        seg = max([s for s in segs if s[0] <= v], default=None)
        if not seg:
            print(f"  {n}: no segment")
            continue
        r0, r1 = seg[1] + v - seg[0], seg[1] + nxt - seg[0]
        ok = built[r0:r1] == base[r0:r1]
        print(f"  {'OK  ' if ok else 'DIFF'} {n}  rom 0x{r0:X} size 0x{r1 - r0:X}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
