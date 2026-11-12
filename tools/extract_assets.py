#!/usr/bin/env python3
"""Extract the assets stored in the ROM's asset region (0x2B8BA0 onward).

- 0x2B8BA0-0x594280: libmus sound data (two sample banks' .ptr/.wbk, a table, and songs), split
  into <outdir>/sound/ at the boundaries the sound overlay ovl_03F1B0 DMAs.
- 0x594280 to the version string "ORGE3_ROM_VER_...": the asset archive, [u32 chunk count][index of
  handles][chunk chain]. The game addresses chunks by handle (offset from 0x594280). Each chunk is
  [u32 BE size][payload] on a 2-byte boundary (size may be 0), and a payload is one of:
  - an LHA archive (level 1/2 headers, -lh5-/-lh0-; the game embeds a port of LHa for UNIX). Every
    member is decompressed, checked against its header's CRC-16, and written to
    <outdir>/lha/<original name>, with <outdir>/lha/manifest.tsv;
  - the game's "format 1" LZ (decoded by func_8007A110, run by the UnpackProc thread):
    [u32 BE unpacked size][stream];
  - stored data (images tagged HU/B5, tables, ...).
  LZ and stored chunks are written to <outdir>/chunks/<handle>.<type>, with
  <outdir>/chunks/manifest.tsv (handle, ROM offset, sizes, kind) and index.tsv.

This is for looking at the assets; the ROM build keeps using the original bytes.

usage: python3 tools/extract_assets.py [baserom] [outdir]
"""
import os
import re
import struct
import sys

ASSET_START = 0x2B8BA0
# The asset archive: [u32 chunk count][index of handles][chunk chain up to the ROM version string].
# The game addresses every chunk by its handle = offset from ARCHIVE_BASE (func_8009DD38 reads the
# chunk's u32 size at ARCHIVE_BASE + (handle & 0x0FFFFFFF)). Before it: libmus sound data.
ARCHIVE_BASE = 0x594280
VERSION_PREFIX = b"ORGE3_ROM_VER_"

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


# ---- the game's "format 1" LZ (func_8007A110) ----
def lz_decode(src, size):
    """Decode `size` bytes; returns (output, number of src bytes consumed)."""
    out = bytearray()
    i = 0
    while len(out) < size:
        b = src[i]
        i += 1
        if b & 0x80:  # 1LLLLDDD DDDDDDDD: copy L+3 from D+1 back
            n = ((b >> 3) & 0xF) + 3
            d = ((b & 7) << 8 | src[i]) + 1
            i += 1
        elif b & 0x40:  # 01NNNNNN: N+1 literals
            n = (b & 0x3F) + 1
            out += src[i:i + n]
            i += n
            continue
        elif b & 0x20:  # 001NNNNN: N+2 zeros
            out += bytes((b & 0x1F) + 2)
            continue
        elif b & 0x10:  # 0001LLLL HHDDDDDD DDDDDDDD: copy (L | HH<<4)+4 from D+1 back
            b1, b2 = src[i], src[i + 1]
            i += 2
            d = ((b1 & 0x3F) << 8 | b2) + 1
            n = ((b & 0xF) | ((b1 >> 2) & 0x30)) + 4
        elif b == 0:  # 00 LL DDDD: copy L+5 from D+1 back
            n = src[i] + 5
            d = (src[i + 1] << 8 | src[i + 2]) + 1
            i += 3
        elif b == 1:  # 01 LL: L+3 bytes of 0xFF
            out += b"\xff" * (src[i] + 3)
            i += 1
            continue
        elif b == 2:  # 02 LL: L+3 zeros
            out += bytes(src[i] + 3)
            i += 1
            continue
        else:  # 03-0F: no-op
            continue
        start = len(out) - d
        if start < 0:
            raise ValueError("copy before start of output")
        if d >= n:
            out += out[start:start + n]
        else:
            for k in range(n):
                out.append(out[start + k])
    return bytes(out[:size]), i


def _walk(rom, o, end, allow_empty=False):
    out = []
    while o + 8 <= end:
        if rom[o:o + len(VERSION_PREFIX)] == VERSION_PREFIX:
            break
        size = struct.unpack_from(">I", rom, o)[0]
        if (size == 0 and not allow_empty) or o + 4 + size > end:
            break
        out.append((o, size))
        o = (o + 4 + size + 1) & ~1
    return out


def unpack_chunk(rom, o, size):
    """(data, kind): kind is 'lz' if the payload decodes exactly as format 1, else 'raw'."""
    payload = rom[o + 4:o + 4 + size]
    usize = struct.unpack_from(">I", payload)[0] if size >= 8 else 0
    if 0 < usize <= 64 * size:
        try:
            out, used = lz_decode(payload[4:] + bytes(3), usize)
            if used == size - 4:
                return out, "lz"
        except (IndexError, ValueError):
            pass
    return payload, "raw"


def chunk_ext(data):
    m = re.match(rb"[A-Z][A-Z0-9]{1,3}", data[:4])
    return m.group(0).decode().lower() if m else "bin"


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


def extract_lha(rom, outdir, members):
    os.makedirs(outdir, exist_ok=True)
    seen, bad, rows = set(), [], []
    for h in members:
        raw = rom[h["data"]:h["data"] + h["packed"]]
        if h["method"] == "-lh0-":
            out = raw[:h["orig"]]
        elif h["method"] == "-lh5-":
            out = lh5_decode(raw, h["orig"])
        else:
            bad.append(f"0x{h['off']:07X} {h['name']}: unsupported method {h['method']}")
            continue
        ok = crc16(out) == h["crc"]
        if not ok:
            bad.append(f"0x{h['off']:07X} {h['name']}: CRC mismatch")
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
    print(f"LHA: {len(rows)} members -> {outdir}")
    return bad


def archive_index(rom):
    """(chunk count from the header, [handles in the index]). The index runs up to its first handle."""
    count, first = struct.unpack_from(">II", rom, ARCHIVE_BASE)
    n = (first - 4) // 4
    return count, list(struct.unpack_from(f">{n}I", rom, ARCHIVE_BASE + 4))


def extract_chunks(rom, outdir):
    """Walk the archive's chunk chain to the version string. LHA-archive chunks are left to
    extract_lha; the rest are written decoded (LZ) or as stored, named by handle."""
    os.makedirs(outdir, exist_ok=True)
    rows, kinds, bad = [], {"lz": 0, "raw": 0, "lha": 0, "empty": 0}, []
    count, index = archive_index(rom)
    found = _walk(rom, ARCHIVE_BASE + index[0], len(rom), allow_empty=True)
    end = found[-1][0] + 4 + found[-1][1]
    if not rom[end:end + 32].lstrip(b"\0").startswith(VERSION_PREFIX):
        bad.append(f"chunk chain ended at 0x{end:07X}, not at the version string")
    if len(found) != count + 1:
        bad.append(f"archive header says {count} chunks, walked {len(found)}")
    starts = {o for o, _ in found}
    bad += [f"index handle 0x{h:X} is not a chunk start" for h in index if h and ARCHIVE_BASE + h not in starts]
    for o, size in found:
        handle = o - ARCHIVE_BASE
        if size == 0:
            kinds["empty"] += 1
            rows.append(f"0x{handle:07X}\t0x{o:07X}\t0\t0\tempty\t")
            continue
        if re.match(rb"..-l[hz][0-9sd]-", rom[o + 4:o + 11], re.S):
            kinds["lha"] += 1
            rows.append(f"0x{handle:07X}\t0x{o:07X}\t{size}\t\tlha\t(see lha/manifest.tsv)")
            continue
        data, kind = unpack_chunk(rom, o, size)
        kinds[kind] += 1
        name = f"{handle:07X}.{chunk_ext(data)}"
        open(os.path.join(outdir, name), "wb").write(data)
        rows.append(f"0x{handle:07X}\t0x{o:07X}\t{size}\t{len(data)}\t{kind}\t{name}")
    with open(os.path.join(outdir, "manifest.tsv"), "w", encoding="utf-8", newline="\n") as f:
        f.write("handle\trom_offset\tsize\tunpacked\tkind\tname\n" + "\n".join(rows) + "\n")
    with open(os.path.join(outdir, "index.tsv"), "w", encoding="utf-8", newline="\n") as f:
        f.write("slot\thandle\n" + "".join(f"{i}\t0x{h:07X}\n" for i, h in enumerate(index)))
    print(f"chunks: {len(rows)} in the archive at 0x{ARCHIVE_BASE:X} (header: {count}; index: {len(index)} "
          f"handles), up to 0x{end:X}: {kinds['lz']} LZ, {kinds['raw']} stored, {kinds['lha']} LHA archives, "
          f"{kinds['empty']} empty -> {outdir}")
    return bad


# libmus sound data before the chunk chain; boundaries are the start/end pairs ovl_03F1B0 DMAs
SOUND_FILES = [
    (0x2B8BA0, 0x2BF250, "bank1.ptr"),   # "N64 PtrTablesV2" sample pointer table
    (0x2BF250, 0x423FF0, "bank1.wbk"),   # "N64 WaveTables" sample data
    (0x423FF0, 0x429CD0, "bank2.ptr"),
    (0x429CD0, 0x4E3140, "bank2.wbk"),
    (0x4E3140, 0x4F0FB0, "4E3140.bin"),  # loaded at boot by ovl_03F1B0 (effects?)
    (0x4F0FB0, ARCHIVE_BASE, "songs.bin"),  # starts with an offset table
]


def extract_sound(rom, outdir):
    os.makedirs(outdir, exist_ok=True)
    for start, end, name in SOUND_FILES:
        open(os.path.join(outdir, name), "wb").write(rom[start:end])
    print(f"sound: {len(SOUND_FILES)} libmus files -> {outdir}")
    return []


def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else "baserom/baserom.us.z64"
    outdir = sys.argv[2] if len(sys.argv) > 2 else "extracted"
    rom = open(rom_path, "rb").read()
    members = list(scan(rom))
    bad = extract_sound(rom, os.path.join(outdir, "sound"))
    bad += extract_lha(rom, os.path.join(outdir, "lha"), members)
    bad += extract_chunks(rom, os.path.join(outdir, "chunks"))
    print(f"{len(bad)} problems")
    for b in bad[:20]:
        print("  " + b)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
