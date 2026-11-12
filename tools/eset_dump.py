#!/usr/bin/env python3
"""Dump the per-stage enemy sets (extracted/lha/eset*.bin) with their squad templates (enemydat.bin).

Read by StageSetupUnits (ovl_195410). All big-endian.

eset file:
  0x00  s16 offsets to sections A, B, C, D (0 = absent)
  A     stage parameters, copied to globals: base level (D_801F1035), two more bytes (D_801F1036/37),
        a byte (D_80196A2C), a byte (D_80196A2E), then two bytes (D_801F0E0C/0D)
  B     u8 count, then 18-byte squad records:
          0     squad group (records with the same non-zero value share the first one's position)
          1     ? (not read by StageSetupUnits)
          2     unit slot (bit 7 is set by the game for a few special stage/template pairs)
          3-4   u16 enemy template, 1-based index into enemydat.bin
          5, 6  position: if byte 6 is 0, byte 5 is a 1-based spawn-point index; otherwise x, y in
                1/256ths of the map's extent
          7     sprite scale: v < 3 -> 0.75 + (v-1)/8, else (v-1)/8 - 0.25
          8, 9  stored in the unit at 0xBA / 0xBB (0xBA 4-19 indexes an 18-byte table at D_801F0EBF)
          10    per-unit byte (stored as v-1), 11 per-unit byte
          12    flag (sets bit 15 of D_8019367C[slot]), 13-14 u16 stored in D_8019367C[slot]
          15-17 passed to func_8021590C(slot, a, b, c) (builds a 20-byte list; each value 1-6)
  C, D  not decoded

enemydat.bin: 556 squad templates of 35 bytes (eset ids go up to 554):
  0x00  leader class, 0x01 leader level (signed, relative to the stage's base level),
  0x02-0x05 four values passed to func_80214F80 (probably equipment), 0x06 leader position (1-9 on
  the 3x3 formation grid)
  0x07  group A class (0 = none), 0x08 level, 0x09-0x0C four values, 0x0D-0x0F positions (0 = unused)
  0x10  group B class, 0x11 level, 0x12-0x15 four values, 0x16-0x18 positions
  0x19-0x22 always zero
Class ids index the class table (gClassTable, 165 records of 0x48 bytes at 0x80187C14 in ovl_040E80,
name pointer first; 0 = None). Item ids index the item table (gItemTable, 0x20-byte records at
0x8018C40C: name pointer, then a category byte; 0 = None). Names are read from the baserom.

usage: python3 tools/eset_dump.py [eset files...]   # default: all of them
"""
import glob
import os
import struct
import sys


OVL_040E80 = (0x40E80, 0x8016AF80, 0x80190F10)  # ROM start, VRAM start, VRAM end


def name_table(rom, vram, stride, count):
    """[name] for a table of records whose first word points at a NUL-terminated name."""
    rom_start, vram_start, vram_end = OVL_040E80
    out = []
    for i in range(count):
        ptr, = struct.unpack_from(">I", rom, rom_start + vram + i * stride - vram_start)
        if not vram_start <= ptr < vram_end:
            break
        o = rom_start + ptr - vram_start
        raw = rom[o:rom.index(b"\0", o)]
        # names may hold formatting bytes: 0x0E/0x0F wrap a two-line name, 0x10 is its line break
        out.append(raw.replace(b"\x0e", b"").replace(b"\x0f", b"").replace(b"\x10", b"/").decode("latin-1"))
    return out


def template(d, tid):
    t = d[(tid - 1) * 35:tid * 35]

    def group(c, lv, eq, pos):
        return {"class": t[c], "level": struct.unpack_from(">b", t, lv)[0],
                "items": list(t[eq:eq + 4]), "positions": [p for p in t[pos[0]:pos[1]] if p]}
    out = [group(0, 1, 2, (6, 7))]
    for c, lv, eq, pos in ((7, 8, 9, (0xD, 0x10)), (0x10, 0x11, 0x12, (0x16, 0x19))):
        if t[c]:
            out.append(group(c, lv, eq, pos))
    return out


def dump(path, enemydat, classes, items):
    d = open(path, "rb").read()
    offs = struct.unpack_from(">4h", d, 0)
    print(f"=== {os.path.basename(path)}  sections {['%#x' % o if o else '-' for o in offs]}")
    if offs[0]:
        a = d[offs[0]:offs[0] + 7]
        print(f"  stage: base level {a[0]}, params {list(a[1:])}")
    if not offs[1]:
        return
    count = d[offs[1]]
    for i in range(count):
        r = d[offs[1] + 1 + 18 * i:offs[1] + 19 + 18 * i]
        tid, = struct.unpack_from(">H", r, 3)
        pos = f"spawn point {r[5]}" if r[6] == 0 else f"x={r[5]}/256 y={r[6]}/256"
        print(f"  squad {r[0]:2} slot {r[2] & 0x7F:2} template {tid:3}  {pos:22} scale {r[7]}  "
              f"ai {r[8]},{r[9]}  misc {list(r[10:15])} {list(r[15:18])}")
        for g in template(enemydat, tid):
            lv = f"{g['level']:+d}"
            cls = classes[g["class"]] if g["class"] < len(classes) else f"#{g['class']}"
            its = [items[i] if i < len(items) else f"#{i}" for i in g["items"] if i]
            print(f"      {cls:18} level {lv:>3} at {g['positions']}" + (f"  items {its}" if its else ""))
    if offs[2] or offs[3]:
        print(f"  sections C/D: not decoded")


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    enemydat = open("extracted/lha/enemydat.bin", "rb").read()
    rom = open("baserom/baserom.us.z64", "rb").read()
    classes = name_table(rom, 0x80187C14, 0x48, 165)
    items = name_table(rom, 0x8018C40C, 0x20, 400)
    for path in sys.argv[1:] or sorted(glob.glob("extracted/lha/eset*.bin")):
        dump(path, enemydat, classes, items)
    return 0


if __name__ == "__main__":
    sys.exit(main())
