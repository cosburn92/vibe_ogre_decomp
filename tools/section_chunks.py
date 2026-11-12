"""Split a section of main (.data or .rodata) into per-text-file chunks for the splat yaml.

Each symbol is attributed to the main text file that references it (overlay references are
ignored: overlays only import main's globals). Symbols nothing in main references by name stay
with the preceding chunk. Symbols only referenced out of order get their own unnamed chunk.
Prints yaml subsegment lines; files that are already C (src/<name>.c) get the dotted `.data` /
`.rodata` form so the chunk is linked from the C object.

Shared globals make .data references noisy, so owners are taken from the longest run of symbols whose
owners increase in ROM order; symbols off that run stay in the current chunk. A wrong boundary
between two asm chunks is harmless, but files converted to C need their chunk checked by hand;
--cut forces an unnamed chunk to start at the given offsets.

usage: python3 tools/section_chunks.py {data|rodata} START END [-v] [--cut ROM,ROM,...]
  -v  list every symbol with its referencing main files instead
"""
import bisect
import collections
import glob
import os
import re
import sys

MAIN_TEXT = (0x1060, 0x2E570)

kind = sys.argv[1]
start, end = (int(x, 16) for x in sys.argv[2:4])
verbose = "-v" in sys.argv
cuts = set()
if "--cut" in sys.argv:
    cuts = {int(x, 16) for x in sys.argv[sys.argv.index("--cut") + 1].split(",")}

# symbol -> main text files (ROM offsets) that reference it
pat = re.compile(r"\b((?:D|jtbl)_[0-9A-F]{8})\b")
refs = collections.defaultdict(set)
for path in glob.glob("asm/*.s") + glob.glob("asm/nonmatchings/*/*.s") + glob.glob("src/*.c"):
    p = path.replace(os.sep, "/")
    m = re.match(r"(?:asm/nonmatchings/|asm/|src/)([0-9A-F]+)[./]", p)
    if m and MAIN_TEXT[0] <= int(m.group(1), 16) < MAIN_TEXT[1]:
        for s in pat.findall(open(path).read()):
            refs[s].add(int(m.group(1), 16))

# symbols in ROM order, from the split data files and from migrated INCLUDE_ASM files
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

if verbose:
    for rom in sorted(syms):
        users = " ".join(f"{u:X}" for u in sorted(refs.get(syms[rom], ())))
        print(f"{rom:05X} {syms[rom]:16} {users}")
    sys.exit()

# owner candidates in ROM order, then the longest non-decreasing run of owners
cand = [(rom, min(refs[syms[rom]])) for rom in sorted(syms) if refs.get(syms[rom])]
tails, tail_idx, prev = [], [], [None] * len(cand)
for i, (_, o) in enumerate(cand):
    k = bisect.bisect_right(tails, o)
    if k == len(tails):
        tails.append(o)
        tail_idx.append(i)
    else:
        tails[k] = o
        tail_idx[k] = i
    prev[i] = tail_idx[k - 1] if k else None
backbone = {}
i = tail_idx[-1] if tail_idx else None
while i is not None:
    backbone[cand[i][0]] = cand[i][1]
    i = prev[i]

chunks = [(start, None)]  # (rom, owner or None)
for rom in sorted(set(backbone) | cuts):
    o = backbone.get(rom)
    if rom in cuts:
        o = None
    elif o == chunks[-1][1]:
        continue
    if chunks[-1][0] == rom:
        chunks.pop()
    chunks.append((rom, o))
for rom, o in chunks:
    if o is None:
        print(f"      - [0x{rom:X}, {kind}]")
    else:
        dot = "." if os.path.exists(f"src/{o:X}.c") else ""
        print(f"      - [0x{rom:X}, {dot}{kind}, {o:X}]")
