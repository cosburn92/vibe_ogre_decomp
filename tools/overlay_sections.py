"""Per-file .data/.rodata/.bss chunks for every overlay, from the splat yaml's overlay segments.

An overlay's data blob is all files' .data in text order, then all files' .rodata in text order, so
the owner sequence restarts at the .rodata start: pick the split that maximizes the two increasing
runs. With one owner there's no restart to find; fall back to the trailing run of rodata-looking
symbols (strings, jump tables, floats). BSS comes from the descriptor table or the bzero after the
overlay's DMA load, or else from the highest address the overlay's own code references.

usage: python3 tools/overlay_sections.py            # diagnostics per overlay
       python3 tools/overlay_sections.py --yaml     # rewrite ogrebattle64.yaml's overlay data/bss
"""
import bisect
import re
import struct
import sys

sys.path.insert(0, "tools")
import find_overlays as fo  # noqa: E402
import section_chunks as sc  # noqa: E402

ROM = open("baserom/baserom.us.z64", "rb").read()
RODATA_LIKE = {".asciz", ".float", ".double", "jtbl"}


def lis_len(seq):
    tails = []
    for o in seq:
        k = bisect.bisect_right(tails, o)
        tails[k:k + 1] = [o]
    return len(tails)


def overlays_from_yaml():
    """[(name, start, text files, data offset, end)] for every overlay code segment."""
    yaml = open("ogrebattle64.yaml").read()
    segs = re.findall(r"  - name: (ovl_[0-9A-F]+)\n    type: code\n    start: 0x([0-9A-F]+)\n(.*?)(?=\n  - )",
                      yaml, re.S)
    ends = {e["rom"]: e for e in fo.all_overlays(ROM)}
    out = []
    for name, start, body in segs:
        start = int(start, 16)
        texts = [int(x, 16) for x in re.findall(r"- \[0x([0-9A-F]+), \.?(?:asm|c)\]", body)]
        data = re.findall(r"- \[0x([0-9A-F]+), \.?(?:data|rodata)", body)
        e = ends[start]
        out.append(dict(name=name, start=start, texts=texts, data=int(data[0], 16) if data else None,
                        end=e["rom_end"], vram=e["vram"], data_end=e["data_end"]))
    return out


def directives(seg):
    """symbol -> first data directive (or 'jtbl') for an overlay's symbols."""
    out = {}
    for text in sc._data_files():
        for m in re.finditer(r"^dlabel ((?:D|jtbl)_[0-9A-F]{8}_" + seg + r")\n(?:.*\n)*?.*?\*/\s*(\.\w+)", text, re.M):
            out[m.group(1)] = "jtbl" if m.group(1).startswith("jtbl") else m.group(2)
    return out


def rodata_start(o):
    """(ROM offset where the overlay's .rodata starts, how it was decided)."""
    syms = sc.symbols("data", o["data"], o["end"], o["name"])
    refs = sc.refs_for((o["start"], o["data"]))
    kinds = directives(o["name"])
    # jump tables are always compiler-generated .rodata
    jt = min((a for a in syms if kinds.get(syms[a]) == "jtbl"), default=o["end"])
    cand = [(a, min(refs[syms[a]])) for a in sorted(syms) if refs.get(syms[a])]
    seq = [f for _, f in cand]
    if len(set(seq)) > 1 and lis_len(seq) < len(seq):
        best = max(range(1, len(cand)), key=lambda k: (lis_len(seq[:k]) + lis_len(seq[k:]), -k))
        # .rodata starts at the first symbol after the last .data owner candidate
        later = [a for a in sorted(syms) if cand[best - 1][0] < a <= cand[best][0]]
        r = later[0]
        return (r, "restart") if r <= jt else (jt, "restart>jtbl")
    r = o["end"]
    for a in sorted(syms, reverse=True):
        if kinds.get(syms[a]) in RODATA_LIKE:
            r = a
        else:
            break
    return min(r, jt), "types" if r <= jt else "jtbl"


def bss_range(o, table, post):
    t = table.get(o["start"])
    if t:
        return o["data_end"], t["bss_end"], "table"
    if o["start"] in post and post[o["start"]][0] == o["data_end"]:
        return o["data_end"], o["data_end"] + post[o["start"]][1], "bzero"
    addr_re = re.compile(r"%(?:hi|lo)\((?:D|jtbl)_([0-9A-F]{8})")
    top = o["data_end"]
    for off, src in sc._sources():
        if o["start"] <= off < o["data"]:
            for a in (int(x, 16) for x in addr_re.findall(src)):
                if o["data_end"] <= a < o["data_end"] + 0x1000:
                    top = max(top, a + 4)
    return o["data_end"], (top + 15) & ~15, "refs"


def post_load_bzero():
    W = lambda x: struct.unpack(">I", ROM[x:x + 4])[0]
    J = {fo.jal(t): n for t, n in ((fo.LOAD, "load"), (fo.BZERO, "bzero"))}
    calls = [(x, J[W(x)]) for x in range(0x1000, 0x2C0000, 4) if W(x) in J]
    post = {}
    for i, (x, k) in enumerate(calls):
        if k != "load":
            continue
        a0, a1, a2 = fo.args_at(ROM, x)
        if None in (a0, a1, a2):
            continue
        for p, k2 in calls[i + 1:i + 3]:
            if k2 == "bzero" and p - x < 0x40:
                b0, b1, _ = fo.args_at(ROM, p)
                if b0 == a1 + a2:
                    post.setdefault(a0, (b0, b1))
    return post


def subsegments(o, table, post):
    """yaml subsegment lines for an overlay's data, rodata and bss, plus its bss size."""
    text = (o["start"], o["data"])
    lines = []
    r, _ = rodata_start(o)
    if o["data"] < r:
        lines += sc.yaml_lines("data", sc.chunks("data", o["data"], r, text, o["name"]))
    if r < o["end"]:
        lines += sc.yaml_lines("rodata", sc.chunks("rodata", r, o["end"], text, o["name"]))
    b0, b1, _ = bss_range(o, table, post)
    if b1 > b0:
        lines += sc.yaml_lines("bss", sc.chunks("bss", b0, b1, text, o["name"]), o["name"])
    return lines, b1 - b0


def rewrite_yaml(table, post):
    """Replace each overlay's data/rodata/bss subsegments (and bss_size) in the yaml."""
    path = "ogrebattle64.yaml"
    yaml = open(path, newline="").read()
    for o in overlays_from_yaml():
        if o["data"] is None:
            continue
        lines, bss_size = subsegments(o, table, post)
        m = re.search(r"(  - name: " + o["name"] + r"\n)(.*?)(?=\n\n|\n  - name:|\Z)", yaml, re.S)
        body = re.sub(r"\n    bss_size: 0x[0-9A-F]+", "", m.group(2))
        if bss_size:
            body = re.sub(r"(    vram: 0x[0-9A-F]+)", lambda v: f"{v.group(1)}\n    bss_size: 0x{bss_size:X}", body, 1)
        keep = [l for l in body.split("\n")
                if not re.match(r"      - (\[0x[0-9A-F]+, \.?(data|rodata)|\{ type: \.?bss)", l)]
        yaml = yaml[:m.start(2)] + "\n".join(keep + lines) + yaml[m.end(2):]
    open(path, "w", newline="").write(yaml)


def main():
    table = {e["rom"]: e for e in fo.parse_table(ROM)}
    post = post_load_bzero()
    if "--yaml" in sys.argv:
        rewrite_yaml(table, post)
        return
    for o in overlays_from_yaml():
        if o["data"] is None:
            print(f"{o['name']}: no data")
            continue
        s, how = rodata_start(o)
        b0, b1, bhow = bss_range(o, table, post)
        print(f"{o['name']} files={len(o['texts']):2} data=0x{o['data']:X} rodata=0x{s:X} ({how}) "
              f"end=0x{o['end']:X} bss=0x{b0:X}-0x{b1:X} ({bhow})")


if __name__ == "__main__":
    main()
