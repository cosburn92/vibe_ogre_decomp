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

Colours come from a separate palette chunk: 256 RGBA5551 colours (0x200 bytes) per palette.

A unit set is a stored table of handles [frames, animations, info, palettes, UT part, ...], loaded by
UnitSetLoad in ovl_1CE070. Entries 0-2 are LZ chunks:

  info:       u32 part count N; N bytes at info + u32@0x1C are each part's palette index (part i is
              drawn with palette info[u32@0x1C + i]); N bytes at info + 0x20 are not yet known.
  frames:     u32 offsets to records (count = first offset / 4). A record is a composite sprite frame:
              u16 piece count, then 16-byte pieces
                {u16 part, s16 x, s16 y, u16 w, u16 h, u16 flags, u16 scale x, u16 scale y}
              (x, y relative to the unit's origin; w, h = the part's size; flags bit 0 = mirror
              horizontally; scale 0x400 = 1.0).
  animations: u32 offsets to scripts (count = first offset / 4). A script is a command count, then
              commands (opcode + fixed-size arguments; see ANIM_OPS). Signed arguments are bytes.

usage: python3 tools/ut2png.py set <set handle> out.png      # every part of a set, in colour
       python3 tools/ut2png.py frames <set handle> out.png   # the set's composite frames
       python3 tools/ut2png.py anims <set handle>            # disassemble the set's animations
       python3 tools/ut2png.py file <chunk.ut> out.png [palette]  # one UT file (grey if no palette)
       python3 tools/ut2png.py all <outdir>                  # every set's parts
"""
import csv
import os
import struct
import sys
import zlib

CHUNKS = "extracted/chunks"

# Animation opcodes: (argument bytes, meaning), from the players UnitAnimStep (ovl_1CE070) and
# BattleAnimStep (ovl_1F0A30, which adds sounds and calls), BattleAnimEventTimes, and the fetcher's
# length table D_801B8098 (which matches the data for every opcode in use). The player keeps
# a position offset (x, y, z), 16 channel values with per-step deltas (clamped 0-255, i.e. fades;
# channel k is the opacity of piece k of the current frame, 0 hides it: see BattleDrawUnitSprite),
# a call stack and a loop stack. Ticks: the counter drops by 2 per step.
ANIM_OPS = {
    0x00: (0, "end (return from a call, else reset to the default animation)"),
    0x01: (2, "frame f, ticks t"),
    0x02: (2, "move x -= a, y -= b"),
    0x03: (1, "wait t ticks"),
    0x04: (1, "jump to command n"),
    0x05: (1, "start animation a"),
    0x06: (0, "no-op (ignored by every interpreter; used twice)"),
    0x07: (0, "(ignored; unused)"),
    0x08: (0, "(ignored; unused)"),
    0x09: (0, "(ignored; unused)"),
    0x0A: (0, "(ignored; unused)"),
    0x0B: (0, "timing marker (BattleAnimEventTimes reports when it is reached)"),
    0x0C: (3, "move x -= a, y += b, z += c"),
    0x0D: (2, "opacity of piece ch = v (ch 0xFF: all 16)"),
    0x0E: (2, "repeat from command n, c times"),
    0x0F: (1, "call animation a (BattleAnimStep; 00 returns)"),
    0x10: (2, "opacity change of piece ch = d per step (ch 0xFF: all 16)"),
    0x11: (2, "play sound table[hi << 8 | lo] on channel A (BattleAnimStep)"),
    0x12: (2, "play weapon/class-dependent sound at the unit, channel A"),
    0x13: (2, "play sound table[hi << 8 | lo] on channel B"),
    0x14: (2, "play weapon/class-dependent sound at the unit, channel B"),
    0x15: (3, "frame lo | hi << 8, ticks t"),
}


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
    for k, t in enumerate(tiles):
        w, h, A, s8, B, s2 = t[:6]
        tpal = t[6] if len(t) > 6 else pal
        ox, oy = (k % cols) * cw, (k // cols) * chh
        for py in range(h):
            for px in range(w):
                r, g, b = rgb_of(tpal, A[py * s8 + px])
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


def part_palettes(rows, hs):
    """Per-part palette index from the set's info chunk (entry 2)."""
    info = load(rows, hs[2])
    n, = struct.unpack_from(">I", info, 0)
    off, = struct.unpack_from(">I", info, 0x1C)
    return list(info[off:off + n])


def offset_table(d):
    """Records of an offset-table chunk (frames, animations): [(start, end)]."""
    n = struct.unpack_from(">I", d, 0)[0] // 4
    offs = list(struct.unpack_from(f">{n}I", d, 0)) + [len(d)]
    return [(offs[i], offs[i + 1]) for i in range(n)]


def frame_pieces(d, start):
    count, = struct.unpack_from(">H", d, start)
    return [struct.unpack_from(">HhhHHHHH", d, start + 2 + 16 * k) for k in range(count)]


def disassemble(d, start):
    """Commands of one animation script: [(opcode, args)]."""
    out, p = [], start + 1
    for _ in range(d[start]):
        op = d[p]
        n = ANIM_OPS[op][0]
        out.append((op, list(d[p + 1:p + 1 + n])))
        p += 1 + n
    return out


def render_frames(rows, hs, path, scale=2, cell=112, cols=6):
    """Compose each frame of the set from its parts and draw them on a grid."""
    pd = load(rows, hs[3])
    pals = struct.unpack(f">{len(pd) // 2}H", pd)
    parts = [next(ut_frames(load(rows, x))) for x in hs[4:] if x]
    pidx = part_palettes(rows, hs)
    fr = load(rows, hs[0])
    recs = offset_table(fr)
    W, H = cols * cell, ((len(recs) + cols - 1) // cols) * cell
    canvas = bytearray(b"\x60" * (W * H * 3))
    for fi, (a, _) in enumerate(recs):
        ox, oy = (fi % cols) * cell + cell // 2, (fi // cols) * cell + cell * 3 // 4
        for pi, x, y, _w, _h, flags, _sx, _sy in frame_pieces(fr, a):
            pw, ph, A, s8, B, s2 = parts[pi]
            pal = pals[256 * pidx[pi]:256 * pidx[pi] + 256]
            for py in range(ph):
                for px in range(pw):
                    al = 1.0
                    if B is not None:
                        nib = B[py * s2 + px // 2]
                        al = (nib >> 4 if px % 2 == 0 else nib & 15) / 15
                    X = ox + x + ((pw - 1 - px) if flags & 1 else px)
                    Y = oy + y + py
                    if al and 0 <= X < W and 0 <= Y < H:
                        i = (Y * W + X) * 3
                        r, g, b = rgb_of(pal, A[py * s8 + px])
                        canvas[i:i + 3] = bytes(int(c * al + canvas[i + j] * (1 - al))
                                                for j, c in enumerate((r, g, b)))
    big = bytearray(W * scale * H * scale * 3)
    for y in range(H * scale):
        for x in range(W * scale):
            i = ((y // scale) * W + x // scale) * 3
            big[(y * W * scale + x) * 3:(y * W * scale + x) * 3 + 3] = canvas[i:i + 3]
    write_png(path, W * scale, H * scale, big)
    return len(recs)


def render_set(rows, hs, path):
    pd = load(rows, hs[3])
    pals = struct.unpack(f">{len(pd) // 2}H", pd)
    parts = [x for x in hs[4:] if x]
    idx = part_palettes(rows, hs)
    tiles = [next(ut_frames(load(rows, x))) + (pals[256 * idx[i]:256 * idx[i] + 256],)
             for i, x in enumerate(parts)]
    sheet(tiles, None, path)
    return len(tiles)


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else ""
    if mode == "set":
        rows = manifest()
        d = load(rows, int(sys.argv[2], 16))
        hs = struct.unpack(f">{len(d) // 4}I", d)
        print(f"{render_set(rows, hs, sys.argv[3])} parts -> {sys.argv[3]}")
    elif mode in ("frames", "anims"):
        rows = manifest()
        d = load(rows, int(sys.argv[2], 16))
        hs = struct.unpack(f">{len(d) // 4}I", d)
        if mode == "frames":
            print(f"{render_frames(rows, hs, sys.argv[3])} frames -> {sys.argv[3]}")
        else:
            an = load(rows, hs[1])
            for i, (a, _) in enumerate(offset_table(an)):
                cmds = disassemble(an, a)
                print(f"anim {i}: " + "; ".join(
                    f"{op:02X}" + ("(" + ",".join(str(v) for v in args) + ")" if args else "")
                    for op, args in cmds))
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
