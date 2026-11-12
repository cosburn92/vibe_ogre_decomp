#!/usr/bin/env python3
"""Extract the LHA archive members stored in the ROM's asset region.

The game embeds a port of LHa for UNIX and keeps its assets as LHA members (level 1/2 headers,
methods -lh5- and -lh0-) packed back to back. This scans the asset region for member headers,
decompresses each member, checks it against the CRC-16 in its header, and writes it to
extracted/lha/<name> along with extracted/lha/manifest.tsv (ROM offset, sizes, method, CRC, name).

This is for looking at the assets; the ROM build keeps using the original compressed bytes.

usage: python3 tools/extract_assets.py [baserom] [outdir]
"""
import os
import re
import struct
import sys

ASSET_START = 0x2B8BA0

# ---- CRC-16 (LHA uses CRC-16/ARC: reflected poly 0xA001, init 0) ----
CRC_TABLE = []
for i in range(256):
    r = i
    for _ in range(8):
        r = (r >> 1) ^ 0xA001 if r & 1 else r >> 1
    CRC_TABLE.append(r)


def crc16(data):
    crc = 0
    for b in data:
        crc = (crc >> 8) ^ CRC_TABLE[(crc ^ b) & 0xFF]
    return crc


# ---- -lh5- decoder (static Huffman blocks over a 8 KB sliding window) ----
NC, NT, NP_LH5 = 510, 19, 14  # literal/length codes, pre-tree codes, position codes for -lh5-
CBIT, TBIT, PBIT = 9, 5, 4


class BitReader:
    def __init__(self, data):
        self.data, self.pos, self.buf, self.n = data, 0, 0, 0

    def peek(self, k):
        while self.n < k:
            b = self.data[self.pos] if self.pos < len(self.data) else 0
            self.pos += 1
            self.buf = (self.buf << 8) | b
            self.n += 8
        return (self.buf >> (self.n - k)) & ((1 << k) - 1)

    def skip(self, k):
        self.peek(k)
        self.n -= k
        self.buf &= (1 << self.n) - 1

    def get(self, k):
        v = self.peek(k)
        self.skip(k)
        return v


def make_table(lengths):
    """Canonical Huffman decode table: (code bit-length max, {code_prefix: (symbol, length)} via a flat
    table indexed by the next `maxlen` bits)."""
    maxlen = max(lengths)
    table = [None] * (1 << maxlen)
    code = 0
    for length in range(1, maxlen + 1):
        for sym, l in enumerate(lengths):
            if l == length:
                start = code << (maxlen - length)
                entry = (sym, length)
                for j in range(start, start + (1 << (maxlen - length))):
                    table[j] = entry
                code += 1
        code <<= 1
    return maxlen, table


def decode_sym(br, maxlen, table):
    sym, length = table[br.peek(maxlen)]
    br.skip(length)
    return sym


def read_pt_len(br, nn, nbit, special):
    n = br.get(nbit)
    if n == 0:
        c = br.get(nbit)
        return None, c  # single symbol
    lengths = [0] * nn
    i = 0
    while i < n:
        c = br.peek(3)
        if c == 7:  # unary extension: count 1-bits after the first three
            br.skip(3)
            while br.peek(1):
                br.skip(1)
                c += 1
            br.skip(1)
        else:
            br.skip(3)
        lengths[i] = c
        i += 1
        if i == special:
            z = br.get(2)
            for _ in range(z):
                lengths[i] = 0
                i += 1
    return lengths, None


def read_c_len(br, pt):
    n = br.get(CBIT)
    if n == 0:
        return None, br.get(CBIT)
    lengths = [0] * NC
    i = 0
    while i < n:
        c = pt_decode(br, pt)
        if c <= 2:
            run = 1 if c == 0 else br.get(4) + 3 if c == 1 else br.get(CBIT) + 20
            i += run  # zeros
        else:
            lengths[i] = c - 2
            i += 1
    return lengths, None


def pt_decode(br, pt):
    lengths, single, maxlen, table = pt
    if lengths is None:
        return single
    return decode_sym(br, maxlen, table)


def lh5_decode(data, size, np_=NP_LH5):
    out = bytearray()
    br = BitReader(data)
    blocksize = 0
    while len(out) < size:
        if blocksize == 0:
            blocksize = br.get(16)
            l, s = read_pt_len(br, NT, TBIT, 3)
            pt = (l, s) + (make_table(l) if l else (0, None))
            l, s = read_c_len(br, pt)
            c_tab = (l, s) + (make_table(l) if l else (0, None))
            l, s = read_pt_len(br, np_, PBIT, -1)
            p_tab = (l, s) + (make_table(l) if l else (0, None))
        blocksize -= 1
        c = pt_decode(br, c_tab)
        if c < 256:
            out.append(c)
        else:
            length = c - 256 + 3
            p = pt_decode(br, p_tab)
            if p:
                p = (1 << (p - 1)) + br.get(p - 1)
            start = len(out) - p - 1
            if start + length <= len(out):
                out += out[start:start + length]
            else:  # overlapping copy
                for k in range(length):
                    out.append(out[start + k])
    return bytes(out[:size])


# ---- LHA headers ----
def parse_header(rom, o):
    method = rom[o + 2:o + 7]
    if not re.fullmatch(rb"-l[hz][0-9sd]-", method):
        return None
    level = rom[o + 20]
    packed, orig = struct.unpack_from("<II", rom, o + 7)
    if level == 2:
        hsize, = struct.unpack_from("<H", rom, o)
        crc, _osid, nxt = struct.unpack_from("<HBH", rom, o + 21)
        p, name, dirname = o + 26, b"", b""
        while nxt:
            ext = rom[p:p + nxt]
            if ext[0] == 1:
                name = ext[1:-2]
            elif ext[0] == 2:
                dirname = ext[1:-2].replace(b"\xff", b"/")
            nxt, = struct.unpack_from("<H", ext, len(ext) - 2)
            p += len(ext)
        data = o + hsize
    elif level == 1:
        hsize = rom[o] + 2
        nlen = rom[o + 21]
        name = rom[o + 22:o + 22 + nlen]
        crc, = struct.unpack_from("<H", rom, o + 22 + nlen)
        # level 1: extended headers follow the base header and count toward `packed`
        p, nxt, dirname = o + hsize, struct.unpack_from("<H", rom, o + hsize - 2)[0], b""
        while nxt:
            ext = rom[p:p + nxt]
            if ext[0] == 1:
                name = ext[1:-2]
            elif ext[0] == 2:
                dirname = ext[1:-2].replace(b"\xff", b"/")
            packed -= nxt
            nxt, = struct.unpack_from("<H", ext, len(ext) - 2)
            p += len(ext)
        data = p
    else:
        return None
    full = (dirname + name).decode("cp932", errors="replace")
    return dict(off=o, method=method.decode(), level=level, packed=packed, orig=orig, crc=crc,
                name=full, data=data)


def scan(rom):
    for m in re.finditer(rb"-l[hz][0-9sd]-", rom[ASSET_START:]):
        h = parse_header(rom, ASSET_START + m.start() - 2)
        if h and h["data"] + h["packed"] <= len(rom):
            yield h


def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else "baserom/baserom.us.z64"
    outdir = sys.argv[2] if len(sys.argv) > 2 else "extracted/lha"
    rom = open(rom_path, "rb").read()
    os.makedirs(outdir, exist_ok=True)
    seen, bad, rows = set(), [], []
    for h in scan(rom):
        raw = rom[h["data"]:h["data"] + h["packed"]]
        if h["method"] == "-lh0-":
            out = raw[:h["orig"]]
        elif h["method"] == "-lh5-":
            out = lh5_decode(raw, h["orig"])
        else:
            bad.append((h, "unsupported method"))
            continue
        ok = crc16(out) == h["crc"]
        if not ok:
            bad.append((h, "CRC mismatch"))
        # keep names unique and filesystem-safe; prefix duplicates with their ROM offset
        name = re.sub(r'[<>:"\\|?*\x00-\x1f]', "_", h["name"]).strip("/") or "unnamed"
        if name in seen:
            name = f"{h['off']:07X}_{name}"
        seen.add(name)
        path = os.path.join(outdir, name)
        os.makedirs(os.path.dirname(path) or outdir, exist_ok=True)
        open(path, "wb").write(out)
        rows.append(f"0x{h['off']:07X}\t{h['packed']}\t{h['orig']}\t{h['method']}\t0x{h['crc']:04X}\t"
                    f"{'ok' if ok else 'BAD'}\t{name}")
    with open(os.path.join(outdir, "manifest.tsv"), "w", encoding="utf-8", newline="\n") as f:
        f.write("rom_offset\tpacked\tsize\tmethod\tcrc16\tcheck\tname\n" + "\n".join(rows) + "\n")
    print(f"extracted {len(rows)} members to {outdir}; {len(bad)} problems")
    for h, why in bad[:20]:
        print(f"  0x{h['off']:07X} {h['method']} {h['name']}: {why}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
