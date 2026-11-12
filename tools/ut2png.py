#!/usr/bin/env python3
"""Render UT sprite graphics from extracted/chunks/ (run `make extract-assets` first) to PNG.

UT format (decompressed chunk), all big-endian:
  0x00  "UT"
  0x02  u8  frame count
  0x03  u8  format: bit 0 = 4bpp alpha plane follows the 8bpp plane (05), else a second 8bpp
            plane (04)
  0x04  u16 width, u16 height
  then per frame: 8-byte header ("UT", u8 frame/source index, 0x03, 4 zero bytes) and the planes:
    plane 1: CI8 colour indices, rows of roundup(width, 8) bytes
    plane 2 (format 05): 4bpp alpha, rows of roundup(width, 16) / 2 bytes, high nibble first
  so size = 8 + frames * (8 + height * (roundup(w, 8) + roundup(w, 16) / 2)).

Colours come from a separate palette chunk: 256 RGBA5551 colours (0x200 bytes) per palette. A unit
set is a stored table of handles: [?, ?, ?, palette chunk, UT part, UT part, ...] (see the loader
in ovl_1CE070 around 0x801AD1C0).

usage: python3 tools/ut2png.py set <set table handle> out.png    # all parts of a set, in colour
       python3 tools/ut2png.py file <chunk.ut> out.png [palette]  # one UT file (grey if no palette)
       python3 tools/ut2png.py all <outdir>                       # every set table found
"""
import csv
import os
import struct
import sys
import zlib

CHUNKS = "extracted/chunks"


def ru(x, m):
    return (x + m - 1) // m * m


def write_png(path, w, h, rgb):
    raw = b"".join(b"\0" + bytes(rgb[y * w * 3:(y + 1) * w * 3]) for y in range(h))

    def chunk(t, d):
        return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)

    with open(path, "wb") as f:
        f.write(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0))
                + chunk(b"IDAT", zlib.compress(raw)) + chunk(b"IEND", b""))


def ut_frames(d):
    """Yield (width, height, ci8 rows, ci8 stride, alpha rows or None, alpha stride) per frame."""
    assert d[:2] == b"UT", "not a UT file"
    count, fmt, w, h = struct.unpack_from(">BBHH", d, 2)
    s8 = ru(w, 8)
    s2 = ru(w, 16) // 2 if fmt & 1 else s8
    plane = h * (s8 + s2)
    for i in range(count):
        o = 16 + i * (8 + plane)
        yield w, h, d[o:o + h * s8], s8, (d[o + h * s8:o + plane] if fmt & 1 else None), s2


def rgb_of(pal, i):
    if pal is None:
        return i, i, i
    c = pal[i]
    return ((c >> 11) & 31) * 255 // 31, ((c >> 6) & 31) * 255 // 31, ((c >> 1) & 31) * 255 // 31


def sheet(tiles, pal, path, scale=2, cols=8):
    cw = max(t[0] for t in tiles) * scale + 2
    chh = max(t[1] for t in tiles) * scale + 2
    W, H = cols * cw, ((len(tiles) + cols - 1) // cols) * chh
    img = bytearray(W * H * 3)
    for k, (w, h, A, s8, B, s2) in enumerate(tiles):
        ox, oy = (k % cols) * cw, (k // cols) * chh
        for py in range(h):
            for px in range(w):
                r, g, b = rgb_of(pal, A[py * s8 + px])
                if B is not None:
                    nib = B[py * s2 + px // 2]
                    al = (nib >> 4 if px % 2 == 0 else nib & 15) / 15
                else:
                    al = 1.0
                for dy in range(scale):
                    for dx in range(scale):
                        x, y = px * scale + dx, py * scale + dy
                        bg = 200 if ((x // 8 + y // 8) % 2) else 150
                        i = ((oy + y) * W + ox + x) * 3
                        img[i:i + 3] = bytes(int(c * al + bg * (1 - al)) for c in (r, g, b))
    write_png(path, W, H, img)


def manifest():
    with open(os.path.join(CHUNKS, "manifest.tsv"), encoding="utf-8") as f:
        return {int(r["handle"], 16): r for r in csv.DictReader(f, delimiter="\t")}


def load(rows, h):
    return open(os.path.join(CHUNKS, rows[h]["name"]), "rb").read()


def set_tables(rows):
    """Stored chunks that read as [h0, h1, h2, palette, UT parts...]."""
    for h, r in rows.items():
        if r["kind"] != "raw":
            continue
        d = load(rows, h)
        if len(d) < 20 or len(d) % 4:
            continue
        hs = struct.unpack(f">{len(d) // 4}I", d)
        if all(x in rows for x in hs[:5]) and rows[hs[3]]["kind"] == "lz" \
                and int(rows[hs[3]]["unpacked"]) % 0x200 == 0 \
                and all(rows.get(x, {}).get("name", "").endswith(".ut") for x in hs[4:] if x):
            yield h, hs


def render_set(rows, hs, path):
    pd = load(rows, hs[3])
    pal = struct.unpack(f">{len(pd) // 2}H", pd)
    tiles = [next(ut_frames(load(rows, x))) for x in hs[4:] if x]
    sheet(tiles, pal, path)
    return len(tiles)


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else ""
    if mode == "set":
        rows = manifest()
        d = load(rows, int(sys.argv[2], 16))
        hs = struct.unpack(f">{len(d) // 4}I", d)
        print(f"{render_set(rows, hs, sys.argv[3])} parts -> {sys.argv[3]}")
    elif mode == "file":
        d = open(sys.argv[2], "rb").read()
        pal = None
        if len(sys.argv) > 4:
            pd = open(sys.argv[4], "rb").read()
            pal = struct.unpack(f">{len(pd) // 2}H", pd)
        tiles = list(ut_frames(d))
        sheet(tiles, pal, sys.argv[3])
        print(f"{len(tiles)} frames -> {sys.argv[3]}")
    elif mode == "all":
        rows = manifest()
        os.makedirs(sys.argv[2], exist_ok=True)
        n = 0
        for h, hs in set_tables(rows):
            render_set(rows, hs, os.path.join(sys.argv[2], f"{h:07X}.png"))
            n += 1
        print(f"{n} sets -> {sys.argv[2]}")
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
