"""Split a .data/.rodata/.bss range into per-text-file chunks for the splat yaml.

Each symbol is attributed to the text file (of the same segment) that references it. Symbols nothing
references by name stay with the preceding chunk. References to .data are noisy because of shared
globals, so owners follow the longest run of symbols whose owners increase in address order; symbols
off that run stay in the current chunk. A wrong boundary between two asm chunks is harmless, but a
file's chunk must be checked by hand before converting that file to C (-v lists every symbol with
its referencing files).

--cut forces an unnamed chunk to start at the given addresses. --own pins a symbol's owner, e.g.
when a file only takes the address one past the end of its own array (a thread stack top), which
equals the next file's first symbol. Chunks already linked from C (dotted in the yaml) are kept.

usage: python3 tools/section_chunks.py {data|rodata|bss} START END [-v] [--cut A,...] [--own A=FILE,...]
       [--text LO,HI] [--seg ovl_XXXXXX]
  START/END are ROM offsets, or VRAM for bss. --text is the segment's text ROM range (default:
  main) and --seg selects an overlay's symbols (their names end in _<seg>).
"""
import bisect
import collections
import functools
import glob
import os
import re
import sys

MAIN_TEXT = (0x1060, 0x2E570)
# any data label: splat's D_/jtbl_ names and names from symbol_addrs.txt (e.g. libultra globals)
SYM = r"[A-Za-z_][A-Za-z0-9_]*"


@functools.lru_cache(None)
def _sources():
    """(text file ROM offset, file contents) for every asm/C text file."""
    out = []
    for path in glob.glob("asm/*.s") + glob.glob("asm/nonmatchings/*/*.s") + glob.glob("src/*.c"):
        p = path.replace(os.sep, "/")
        m = re.match(r"(?:asm/nonmatchings/|asm/|src/)([0-9A-F]+)[./]", p)
        if m:
            out.append((int(m.group(1), 16), open(path).read()))
    return out


@functools.lru_cache(None)
def _data_files():
    return [open(p).read() for p in glob.glob("asm/data/*.s") + glob.glob("asm/nonmatchings/*/*.s")]


def refs_for(text):
    pat = re.compile(r"\b(" + SYM + r")\b")
    refs = collections.defaultdict(set)
    for off, src in _sources():
        if text[0] <= off < text[1]:
            for s in pat.findall(src):
                refs[s].add(off)
    return refs


def symbols(kind, start, end, seg=None):
    """address -> symbol name, for symbols of this segment in [start, end)."""
    lab_re = re.compile(r"^dlabel (" + SYM + r")", re.M)
    # data/rodata lines carry "/* ROM VRAM ... */"; bss lines only "/* VRAM */"
    rom_re = re.compile(r"/\* ([0-9A-F]{8}) \*/" if kind == "bss" else r"/\* ([0-9A-F]+) [0-9A-F]{8}")
    syms = {}
    for text in _data_files():
        for m in lab_re.finditer(text):
            name = m.group(1)
            if (seg is None) == ("_ovl_" in name) or (seg and not name.endswith("_" + seg)):
                continue
            r = rom_re.search(text, m.end())
            if r:
                a = int(r.group(1), 16)
                if start <= a < end:
                    syms[a] = name
    return syms


def c_owned(kind):
    """Chunks already linked from C objects (dotted kinds in the yaml): address -> file."""
    yaml = open("ogrebattle64.yaml").read()
    owns = {}
    for a, f in re.findall(r"\[0x([0-9A-F]+), \." + kind + r", ([0-9A-F]+)\]", yaml):
        owns[int(a, 16)] = int(f, 16)
    for a, f in re.findall(r"type: \." + kind + r", vram: 0x([0-9A-F]+), name: ([0-9A-F]+)", yaml):
        owns[int(a, 16)] = int(f, 16)
    return owns


def chunks(kind, start, end, text=MAIN_TEXT, seg=None, cuts=(), owns=None, verbose=False):
    """[(address, owner file or None)] starting at `start`."""
    refs = refs_for(text)
    syms = symbols(kind, start, end, seg)
    owns = {**{a: f for a, f in c_owned(kind).items() if start <= a < end}, **(owns or {})}
    for a in owns:
        syms.setdefault(a, f"(C:{owns[a]:X})")

    if verbose:
        for a in sorted(syms):
            print(f"{a:05X} {syms[a]:28} " + " ".join(f"{u:X}" for u in sorted(refs.get(syms[a], ()))))
        return []

    # owner candidates in address order, then the longest non-decreasing run of owners
    cand = [(a, owns.get(a, min(refs.get(syms[a], [0])))) for a in sorted(syms) if a in owns or refs.get(syms[a])]
    common = None
    if kind == "bss":
        # .bss is per-file (in text order) up to where the owner first drops: from there on it's
        # the linker's COMMON area, allocated in the linker's own order. Keep that as one chunk.
        cur = None
        for i, (a, o) in enumerate(cand):
            if cur is not None and o < cur and a not in owns:
                common, cand = a, cand[:i]
                break
            cur = o
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

    out = [(start, None)]
    for a in sorted(set(backbone) | set(cuts)):
        if a % 4 and a not in cuts:
            continue  # objects' sections start 4-aligned (and the ld script uses SUBALIGN(4))
        o = None if a in cuts else backbone.get(a)
        if a not in cuts and o == out[-1][1]:
            continue
        if out[-1][0] == a:
            out.pop()
        out.append((a, o))
    if common is not None:
        # with SUBALIGN(4) a chunk must start 4-aligned: move up to the next aligned symbol
        common = min((a for a in syms if a >= common and a % 4 == 0), default=None)
    if common is not None:
        if out[-1][0] == common:
            out.pop()
        out.append((common, "common"))
    return out


def yaml_lines(kind, chunk_list, seg=None):
    lines = []
    for a, o in chunk_list:
        if o == "common":
            lines.append(f"      - {{ type: bss, vram: 0x{a:X}, name: {seg + '_' if seg else ''}common }}")
            continue
        dot = "." if o is not None and os.path.exists(f"src/{o:X}.c") else ""
        if kind == "bss":  # no ROM offset: splat's dict form, keyed by VRAM
            # unnamed: VRAM collides across overlays, so qualify it with the segment
            name = f", name: {o:X}" if o is not None else (f", name: {seg}_bss_{a:X}" if seg else "")
            lines.append(f"      - {{ type: {dot}bss, vram: 0x{a:X}{name} }}")
        elif o is None:
            lines.append(f"      - [0x{a:X}, {kind}]")
        else:
            lines.append(f"      - [0x{a:X}, {dot}{kind}, {o:X}]")
    return lines


def _arg(name, conv, default):
    return conv(sys.argv[sys.argv.index(name) + 1]) if name in sys.argv else default


if __name__ == "__main__":
    kind = sys.argv[1]
    start, end = (int(x, 16) for x in sys.argv[2:4])
    cuts = _arg("--cut", lambda s: {int(x, 16) for x in s.split(",")}, set())
    owns = _arg("--own", lambda s: {int(a, 16): int(f, 16) for a, f in (p.split("=") for p in s.split(","))}, {})
    text = _arg("--text", lambda s: tuple(int(x, 16) for x in s.split(",")), MAIN_TEXT)
    seg = _arg("--seg", str, None)
    res = chunks(kind, start, end, text, seg, cuts, owns, verbose="-v" in sys.argv)
    print("\n".join(yaml_lines(kind, res, seg)))
