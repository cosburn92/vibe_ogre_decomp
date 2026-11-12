#!/usr/bin/env python3
"""Dump the stage table gStageTable (0x801E7E10 in ovl_101CE0's data): 0x43 records of 12 bytes,
indexed by the stage id (D_8018F481). Ids 0x0A, 0x16, 0x23 and 0x3E are empty separators between
chapters; the data after 0x42 belongs to something else.

  0x00  chapter, 0x01 map, 0x02 variant (0 none, 1-4 = a-d). These match the eset file names for most
        stages; the eset itself is chosen through a separate table (D_8018F5A8[stage * 9])
  0x03  ? (4 in the first maps, 1 later, 0 in chapter 9; read with story flag 0x11)
  0x04  ? (2, 3, 5, 6 or 7)
  0x05  scincsv member (0-based in archive 0x21B0F2A, so 1 = scincsv1a): the map's locations
  0x06  maizo member (0-based in archive 0x21AFA08): the map's buried treasure
  0x07  ? (0x11-0x19; compared with a value + 1 when the map starts)
  0x08  ? (3-0x30, rising through the game; 0 on a few stages; values below 3 skip something)
  0x0A  u16 base money for clearing the stage. The stage-clear code adds a share of the liberated
        locations' ktenmain +0x16 values, scaled by how far gChaosFrame (reputation) is from 50, and adds
        the total to gGoth (capped at 9,999,999)

usage: python3 tools/stage_dump.py
"""
import struct
import sys

TABLE = 0x801E7E10 - 0x800AB8C0  # ROM offset (ovl_101CE0: ROM = VRAM - 0x800AB8C0)
COUNT = 0x43


def archive_members(first):
    rows = [l.split("\t") for l in open("extracted/lha/manifest.tsv", encoding="utf-8").read().splitlines()[1:]]
    names = [r[6] for r in sorted(rows, key=lambda r: int(r[0], 16))]
    return names[names.index(first):]


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    rom = open("baserom/baserom.us.z64", "rb").read()
    locs = archive_members("ktenmain.bin")
    treasure = [n for n in archive_members("maizo01.bin") if n.startswith("maizo")]
    for s in range(COUNT):
        r = rom[TABLE + 12 * s:TABLE + 12 * s + 12]
        if not any(r):
            print(f"0x{s:02X}  -")
            continue
        money, = struct.unpack_from(">H", r, 0xA)
        eset = f"eset{r[0]}_{r[1]:02}{' abcd'[r[2]].strip()}"
        sc = locs[r[5]] if r[5] < len(locs) else r[5]
        mz = treasure[r[6]] if r[6] < len(treasure) else r[6]
        print(f"0x{s:02X}  {eset:11} {sc:15} {mz:12} [3] {r[3]} [4] {r[4]} [7] 0x{r[7]:02X} [8] {r[8]:2}"
              f"  money {money}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
