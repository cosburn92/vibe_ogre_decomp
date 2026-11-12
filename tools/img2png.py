#!/usr/bin/env python3
"""Convert the game's "64" textures and "B5" tiled images (extracted by `make extract-assets`) to PNG.

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
  0x02  u8  pixel kind: 1 = RGBA16; 0 = RGBA16 then an 8-bit alpha plane; 3 = "HU"-compressed tiles
            (not decoded here); 5 = unknown
  0x03  u8  tile count
  0x04  u16, u16 anchor
  0x08  tiles: {s16 x, s16 y, u16 w, u16 h, u32 size, u32 0} then size bytes. x, y are relative to
        the anchor. RGBA16 rows are roundup(w, 4) * 2 bytes, alpha rows roundup(w, 8).
All 571 tiles of kinds 0, 1, 3 and 5 have the predicted sizes and every file is consumed exactly.

usage: python3 tools/img2png.py [--opaque] <file> <out.png>
       python3 tools/img2png.py [--opaque] all <outdir>  # every "64"/"B5" file in extracted/lha, /chunks
"""
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


def decode_b5(d):
    """(width, height, RGBA bytes): the tiles composited on their bounding box."""
    if d[:2] != b"B5":
        raise ValueError("not a B5 image")
    kind, count = d[2], d[3]
    if kind not in (0, 1):
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
                if f.read(2) not in (b"64", b"B5"):
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
