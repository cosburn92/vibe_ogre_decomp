#!/usr/bin/env python3
"""Dump the buried-treasure files (extracted/lha/maizo*.bin, 埋蔵 "buried treasure").

The 40 files are the members of one LHA archive (handle 0x21AFA08), the first entry of the 3-handle
indirection chunk 0x21AF9F8. StageSetupUnits (ovl_195410) loads the stage's member with
LoadAsset(0x21AF9F8, 0, -3, D_801E7E16[stage * 12]) (0-based member index, in archive order) and
unpacks it into ovl_101CE0's globals:

  u8 count (D_801F0FE2), then 6-byte records:
    0     treasure id, 1-230, global across maps (D_801F1024[i]); found treasures are bits in
          the saved bitfield D_80196A38 (bit id & 7 of byte id >> 3), so each can be found once
    1, 2  x, y in 1/256ths of the map (D_801F1004[i], D_801F1014[i])
    3     kind: 1 an item (gItemTable id), 2 a consumable (gConsumableTable id)
    4-5   u16 id. Stored as D_801F0FE4[i] = id | 0x8000 for items, the form InventoryAdd takes

A unit that reaches a treasure gets it through InventoryAdd (func_801B9674_ovl_101CE0).
TreasureDowse (func_8021B5E0_ovl_1A9290, called from the field item menu) picks an unfound treasure
on the map and marks it found: a random item one 76% of the time when any are left, otherwise the
first unfound one.

usage: python3 tools/maizo_dump.py [maizo files...]   # default: all, plus the stage -> file table
"""
import glob
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(__file__))
from eset_dump import name_table  # noqa: E402

STAGE_TABLE = 0x801E7E16 - 0x800AB8C0  # ROM offset of D_801E7E16 (ovl_101CE0 data), 12-byte stride


def members():
    """Member names in archive order (the index LoadAsset takes)."""
    rows = [l.split("\t") for l in open("extracted/lha/manifest.tsv", encoding="utf-8").read().splitlines()[1:]]
    return [r[6] for r in sorted(rows, key=lambda r: int(r[0], 16)) if r[6].startswith("maizo")]


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    rom = open("baserom/baserom.us.z64", "rb").read()
    items = name_table(rom, 0x8018C40C, 0x20, 278)
    cons = name_table(rom, 0x8018E6CC, 12, 45)
    paths = sys.argv[1:] or sorted(glob.glob("extracted/lha/maizo*.bin"))
    for p in paths:
        d = open(p, "rb").read()
        print(f"=== {os.path.basename(p)}  {d[0]} treasures")
        for i in range(d[0]):
            tid, x, y, kind, v = struct.unpack_from(">4BH", d, 1 + 6 * i)
            name = items[v] if kind == 1 else cons[v] if kind == 2 else f"kind {kind} #{v}"
            print(f"  #{tid:3} at ({x:3},{y:3})  {'item' if kind == 1 else 'consumable':10} {name}")
    if not sys.argv[1:]:
        names = members()
        print("=== stage -> member (D_801E7E16; values past the last member mean none)")
        for s in range(0x50):
            m = rom[STAGE_TABLE + 12 * s]
            print(f"  stage 0x{s:02X}: {m:3}  {names[m] if m < len(names) else '-'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
