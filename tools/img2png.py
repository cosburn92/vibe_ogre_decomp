#!/usr/bin/env python3
"""Convert the game's "64" textures, "B5" tiled images and "HU" JPEG-style images to PNG
(from `make extract-assets`).

"64" format, big-endian:
  0x00  "64"
  0x02  u8  RDP image format: 0 = RGBA, 2 = CI (palette indices), 4 = I (intensity)
  0x03  u8  RDP pixel size:   0 = 4-bit, 1 = 8-bit, 2 = 16-bit, 3 = 32-bit
  0x04  u16 width, u16 height
  0x08  pixels, each row padded to 8 bytes (one TMEM line):
          4-bit rows roundup(w, 16) / 2 bytes, 8-bit roundup(w, 8), 16-bit roundup(w, 4) * 2,
          32-bit roundup(w, 2) * 4. 4-bit pixels are high nibble first.
  then, for CI: the palette, 16 (CI4) or 256 (CI8) RGBA5551 colours.
This fits 260 of the 263 "64" files exactly.

Some RGBA16 textures have the alpha bit clear everywhere and are presumably drawn opaque; --opaque
ignores alpha.

"B5" format (backgrounds: .bg2 files and .b5 chunks), big-endian:
  0x00  "B5"
  0x02  u8  pixel kind: 1 = RGBA16; 0 = RGBA16 then an 8-bit alpha plane; 3 = each tile is an "HU"
            image; 5 = unknown
  0x03  u8  tile count
  0x04  u16, u16 anchor
  0x08  tiles: {s16 x, s16 y, u16 w, u16 h, u32 size, u32 0} then size bytes. x, y are relative to
        the anchor. RGBA16 rows are roundup(w, 4) * 2 bytes, alpha rows roundup(w, 8).
All 571 tiles of kinds 0, 1, 3 and 5 have the predicted sizes and every file is consumed exactly.

"HU" format: a JPEG-style image decoded by the N64 SDK's JPEG microcode (M_NJPEGTASK, njpgdspMain):
  0x00  "HU", 0xFE, 0, u16 width, u16 height
  0x08  "HUFF", s16 macroblock count, then a bitstream (MSB first, no 0xFF byte stuffing) of 16x16
        macroblocks in raster order, each four 8x8 Y blocks (TL, TR, BL, BR) then Cb and Cr (4:2:0).
  Blocks are entropy-coded as in JPEG with the standard Annex K Huffman tables (in main's data at
  0x800AA0A0 / 0x800AA120 for luma DC / AC, 0x800AA0E0 / 0x800AA290 for chroma; decoded by
  func_8008B250 on the CPU). DC is differential per component with no reset (as in JPEG), and the
  coefficients are in zigzag order, but the zigzag walks the microcode's column-major (transposed)
  block layout rather than JPEG's row-major one. The microcode (data at 0x800AC050)
  dequantizes with the standard JPEG luminance table for all components, runs the IDCT (net scale
  1/4 against an orthonormal IDCT), and chroma is stored offset by +128.

usage: python3 tools/img2png.py [--opaque] <file> <out.png>
       python3 tools/img2png.py [--opaque] all <outdir>  # every "64"/"B5"/"HU" file in extracted/
The HU decoder reads its tables from baserom/baserom.us.z64.
"""
import math
import os
import struct
import sys
import zlib


def ru(x, m):
    return (x + m - 1) // m * m


STRIDE = {0: lambda w: ru(w, 16) // 2, 1: lambda w: ru(w, 8), 2: lambda w: ru(w, 4) * 2,
          3: lambda w: ru(w, 2) * 4}


def write_png_rgba(path, w, h, rgba):
    raw = b"".join(b"\0" + bytes(rgba[y * w * 4:(y + 1) * w * 4]) for y in range(h))

    def chunk(t, d):
        return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)

    with open(path, "wb") as f:
        f.write(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
                + chunk(b"IDAT", zlib.compress(raw)) + chunk(b"IEND", b""))


def rgba5551(c):
    return (((c >> 11) & 31) * 255 // 31, ((c >> 6) & 31) * 255 // 31, ((c >> 1) & 31) * 255 // 31,
            255 if c & 1 else 0)


def decode64(d, opaque=False):
    """(width, height, RGBA bytes) for a "64" texture."""
    if d[:2] != b"64":
        raise ValueError("not a \"64\" texture")
    fmt, siz, w, h = struct.unpack_from(">BBHH", d, 2)
    if siz not in STRIDE:
        raise ValueError(f"unsupported pixel size {siz}")
    stride = STRIDE[siz](w)
    px = d[8:8 + stride * h]
    pal = None
    if fmt == 2:
        n = 16 if siz == 0 else 256
        pd = d[8 + stride * h:8 + stride * h + 2 * n]
        pal = [rgba5551(c) for c in struct.unpack(f">{n}H", pd)]
    out = bytearray(w * h * 4)
    for y in range(h):
        row = px[y * stride:(y + 1) * stride]
        for x in range(w):
            if siz == 0:
                v = row[x // 2] >> 4 if x % 2 == 0 else row[x // 2] & 15
            elif siz == 1:
                v = row[x]
            elif siz == 2:
                v = struct.unpack_from(">H", row, 2 * x)[0]
            else:
                v = struct.unpack_from(">I", row, 4 * x)[0]
            if fmt == 2:
                p = pal[v]
            elif fmt == 4:
                i = v * 17 if siz == 0 else v
                p = (i, i, i, 255)
            elif siz == 2:
                p = rgba5551(v)
            elif siz == 3:
                p = (v >> 24, (v >> 16) & 255, (v >> 8) & 255, v & 255)
            else:
                raise ValueError(f"unsupported format {fmt}/{siz}")
            out[(y * w + x) * 4:(y * w + x) * 4 + 4] = bytes(p[:3]) + bytes((255 if opaque else p[3],))
    return w, h, out


# ---- HU (JPEG-style) ----
_HU = {}


def _hu_tables():
    if not _HU:
        rom = open("baserom/baserom.us.z64", "rb").read()

        def rom_off(vram):
            return vram - 0x80070C60 + 0x1060

        def huff(vram):
            o = rom_off(vram)
            bits = struct.unpack_from(">16H", rom, o)
            vals = struct.unpack_from(f">{sum(bits)}H", rom, o + 0x20)
            codes, code, k = {}, 0, 0
            for length in range(1, 17):
                for _ in range(bits[length - 1]):
                    codes[(length, code)] = vals[k]
                    k += 1
                    code += 1
                code <<= 1
            return codes

        _HU["dc"] = (huff(0x800AA0A0), huff(0x800AA0E0))
        _HU["ac"] = (huff(0x800AA120), huff(0x800AA290))
        _HU["q"] = struct.unpack_from(">64h", rom, rom_off(0x800AC050) + 0x20)
        c = [[(math.sqrt(0.5) if u == 0 else 1.0) * math.cos((2 * x + 1) * u * math.pi / 16) / 2
              for x in range(8)] for u in range(8)]
        _HU["c"] = c
    return _HU


class _Bits:
    def __init__(self, d, pos):
        self.d, self.p = d, pos * 8

    def bit(self):
        b = (self.d[self.p >> 3] >> (7 - (self.p & 7))) & 1
        self.p += 1
        return b

    def get(self, n):
        v = 0
        for _ in range(n):
            v = v << 1 | self.bit()
        return v

    def sym(self, codes):
        code = 0
        for length in range(1, 17):
            code = code << 1 | self.bit()
            if (length, code) in codes:
                return codes[(length, code)]
        raise ValueError("invalid Huffman code")


def _extend(v, n):
    return v - (1 << n) + 1 if n and not v >> (n - 1) else v


def _hu_block(br, dc, ac):
    out = [0] * 64
    n = br.sym(dc)
    out[0] = _extend(br.get(n), n)
    i = 1
    while i < 64:
        rs = br.sym(ac)
        if rs == 0:
            break
        i += rs >> 4
        if rs & 15:
            out[i] = _extend(br.get(rs & 15), rs & 15)
        i += 1
    return out


_ZIGZAG = [0, 1, 8, 16, 9, 2, 3, 10, 17, 24, 32, 25, 18, 11, 4, 5, 12, 19, 26, 33, 40, 48, 41, 34, 27,
           20, 13, 6, 7, 14, 21, 28, 35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51, 58,
           59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63]


def _idct(coef, q, c):
    """coef in column-major order -> 8x8 pixels (row-major), dequantized, scaled 1/4."""
    F = [[coef[u * 8 + v] * q[u * 8 + v] / 4 for u in range(8)] for v in range(8)]  # F[v][u]
    tmp = [[sum(c[u][x] * F[v][u] for u in range(8)) for x in range(8)] for v in range(8)]
    return [sum(c[v][y] * tmp[v][x] for v in range(8)) for y in range(8) for x in range(8)]


def decode_hu(d):
    """(width, height, RGBA bytes) for an "HU" image."""
    if d[:2] != b"HU" or d[8:12] != b"HUFF":
        raise ValueError("not an HU image")
    t = _hu_tables()
    w, h = struct.unpack_from(">HH", d, 4)
    count, = struct.unpack_from(">h", d, 12)
    br = _Bits(d, 14)
    out = bytearray(w * h * 4)
    pred = [0, 0, 0]
    mbw = (w + 15) // 16
    for mb in range(count):
        blocks = []
        for k in range(6):
            comp = 0 if k < 4 else k - 3
            zz = _hu_block(br, t["dc"][comp > 0], t["ac"][comp > 0])
            pred[comp] += zz[0]
            zz[0] = pred[comp]
            coef = [0] * 64
            for i, v in enumerate(zz):
                coef[_ZIGZAG[i]] = v  # zigzag position, in the column-major layout
            blocks.append(_idct(coef, t["q"], t["c"]))
        mx, my = (mb % mbw) * 16, (mb // mbw) * 16
        for y in range(16):
            for x in range(16):
                if mx + x >= w or my + y >= h:
                    continue
                Y = blocks[(y // 8) * 2 + x // 8][(y % 8) * 8 + x % 8]
                cb = blocks[4][(y // 2) * 8 + x // 2] - 128
                cr = blocks[5][(y // 2) * 8 + x // 2] - 128
                rgb = (Y + 1.402 * cr, Y - 0.344136 * cb - 0.714136 * cr, Y + 1.772 * cb)
                i = ((my + y) * w + mx + x) * 4
                out[i:i + 4] = bytes(max(0, min(255, int(round(v)))) for v in rgb) + b"\xff"
    return w, h, out


def decode_b5(d):
    """(width, height, RGBA bytes): the tiles composited on their bounding box."""
    if d[:2] != b"B5":
        raise ValueError("not a B5 image")
    kind, count = d[2], d[3]
    if kind not in (0, 1, 3):
        raise ValueError(f"unsupported B5 pixel kind {kind}")
    tiles, o = [], 8
    for _ in range(count):
        x, y, w, h, size, _z = struct.unpack_from(">hhHHII", d, o)
        tiles.append((x, y, w, h, d[o + 16:o + 16 + size]))
        o += 16 + size
    x0 = min(t[0] for t in tiles)
    y0 = min(t[1] for t in tiles)
    W = max(t[0] + t[2] for t in tiles) - x0
    H = max(t[1] + t[3] for t in tiles) - y0
    out = bytearray(W * H * 4)
    for x, y, w, h, px in tiles:
        if kind == 3:
            tw, th, rgba = decode_hu(px)
            for ty in range(min(h, th)):
                i = ((y - y0 + ty) * W + x - x0) * 4
                out[i:i + 4 * min(w, tw)] = rgba[ty * tw * 4:(ty * tw + min(w, tw)) * 4]
            continue
        s16, s8 = ru(w, 4) * 2, ru(w, 8)
        for ty in range(h):
            for tx in range(w):
                r, g, b, a = rgba5551(struct.unpack_from(">H", px, ty * s16 + tx * 2)[0])
                if kind == 0:
                    a = px[h * s16 + ty * s8 + tx]
                i = ((y - y0 + ty) * W + x - x0 + tx) * 4
                out[i:i + 4] = bytes((r, g, b, a))
    return W, H, out


def decode(d, opaque=False):
    if d[:2] == b"HU":
        return decode_hu(d)
    if d[:2] == b"B5":
        w, h, rgba = decode_b5(d)
        if opaque:
            rgba[3::4] = b"\xff" * (w * h)
        return w, h, rgba
    return decode64(d, opaque)


def main():
    opaque = "--opaque" in sys.argv
    if opaque:
        sys.argv.remove("--opaque")
    if len(sys.argv) != 3:
        print(__doc__)
        return 1
    if sys.argv[1] != "all":
        w, h, rgba = decode(open(sys.argv[1], "rb").read(), opaque)
        write_png_rgba(sys.argv[2], w, h, rgba)
        print(f"{w}x{h} -> {sys.argv[2]}")
        return 0
    os.makedirs(sys.argv[2], exist_ok=True)
    done = bad = 0
    for sub in ("extracted/lha", "extracted/chunks"):
        for name in sorted(os.listdir(sub)):
            path = os.path.join(sub, name)
            if name.endswith(".tsv") or os.path.isdir(path):
                continue
            with open(path, "rb") as f:
                if f.read(2) not in (b"64", b"B5", b"HU"):
                    continue
            try:
                w, h, rgba = decode(open(path, "rb").read(), opaque)
                write_png_rgba(os.path.join(sys.argv[2], name + ".png"), w, h, rgba)
                done += 1
            except (ValueError, struct.error, IndexError):
                bad += 1
    print(f"{done} images -> {sys.argv[2]} ({bad} skipped: unsupported kinds)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
