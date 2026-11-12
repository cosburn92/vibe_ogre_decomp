"""Split main's .rodata into per-text-file chunks for the splat yaml.

Each rodata symbol is attributed to the main text file that references it. Symbols that nothing
references directly (e.g. strings reached through a pointer table) stay with the preceding chunk.
Symbols referenced only out of order (not by the file whose chunk they sit in) get their own
unnamed chunk. Prints yaml subsegment lines; C files (src/<name>.c) get `.rodata`.

usage: python3 tools/rodata_chunks.py RODATA_START RODATA_END
"""
import collections
import glob
import os
import re
import sys

start, end = (int(x, 16) for x in sys.argv[1:3])

# text file (ROM offset) -> referenced symbols
pat = re.compile(r"\b((?:D|jtbl)_[0-9A-F]{8})\b")
refs = collections.defaultdict(set)
for path in glob.glob("asm/*.s") + glob.glob("asm/nonmatchings/*/*.s") + glob.glob("src/*.c"):
    p = path.replace(os.sep, "/")
    m = re.match(r"(?:asm/nonmatchings/|asm/|src/)([0-9A-F]+)[./]", p)
    if m:
        for s in pat.findall(open(path).read()):
            refs[s].add(int(m.group(1), 16))

# rodata symbols in ROM order (from every *.rodata.s / nonmatching .s under asm/)
syms = {}
lab_re = re.compile(r"^dlabel ((?:D|jtbl)_[0-9A-F]{8})")
rom_re = re.compile(r"/\* ([0-9A-F]+) [0-9A-F]{8}")
for path in glob.glob("asm/data/*.s") + glob.glob("asm/nonmatchings/*/*.s"):
    pending = None
    for line in open(path):
        m = lab_re.match(line)
        if m:
            pending = m.group(1)
            continue
        if pending:
            r = rom_re.search(line)
            if r:
                rom = int(r.group(1), 16)
                if start <= rom < end:
                    syms[rom] = pending
                pending = None

chunks = []  # (rom, owner or None)
owner = None
for rom in sorted(syms):
    users = refs.get(syms[rom], set())
    if not users:
        continue  # stays with the current chunk
    if owner in users:
        continue
    new = min(users) if len(users) == 1 or (owner is None or min(users) > owner) else None
    if new is not None and owner is not None and new < owner:
        new = None  # out of order: shared/foreign symbol
    if new != owner or new is None:
        chunks.append((rom, new))
        owner = new

for rom, o in chunks:
    if o is None:
        print(f"      - [0x{rom:X}, rodata]")
    else:
        kind = ".rodata" if os.path.exists(f"src/{o:X}.c") else "rodata"
        print(f"      - [0x{rom:X}, {kind}, {o:X}]")
