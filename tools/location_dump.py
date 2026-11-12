#!/usr/bin/env python3
"""Dump the towns and strongholds: ktenmain.bin (拠点 "stronghold") and the per-map scincsv*.bin lists.

Both are members of the LHA archive at handle 0x21B0F2A, the third entry of the indirection chunk
0x21AF9F8. When a map starts, MapSetupLocations (func_801D30F0_ovl_101CE0) loads member 0 (ktenmain)
and the map's scincsv member (D_801E7E15[stage * 12], 0-based in archive order), and fills one
0x24-byte gLocations record per scincsv entry.

ktenmain.bin: 316 records of 28 bytes, one per location in the game (1-based ids):
  0x00  u8 ? (0 for most; 1-12 on twelve locations)
  0x01  name, 21 bytes NUL-padded           -> gLocations +0x00
  0x16  u16 size (65-704) -> gLocations +0x20. LocationsLiberatedSize sums it over liberated
        locations for the stage-clear money
  0x18  u8 the alignment the town favours, 0-100 (0xFF on 48 = none; bit 7 adds 40 to the
        mismatch) -> gLocations +0x1E. ChaosFrameOnLiberate compares it with the liberating
        squad's alignment: a close match raises gChaosFrame by up to 2, a mismatch lowers it by up
        to 5; an enemy capture costs 2. func_801D3510 also weights the size by it (0xFF = 50)
  0x19  u16 base flags (0x01 and 0x08 always; 0x20-0x800 vary with the kind of place, e.g. 0x200
        on churches and temples)            -> gLocations +0x1C, plus the scincsv value
  0x1B  u8 ?

scincsv*.bin: u8 count, then (u16 ktenmain id, u16 flags to add) pairs, in the map's location order
(gLocations index = location - 1). The added flags set the starting state: 0x04 held by the enemy,
0x02 liberated, 0x10 the player's headquarters (0x2012 on the starting base). After story flag 0x11
every location is set to liberated. The positions come from the map, not from these files.

usage: python3 tools/location_dump.py [scincsv files...]   # default: ktenmain and every scincsv
"""
import glob
import os
import struct
import sys

STAGE_TABLE = 0x801E7E15 - 0x800AB8C0  # ROM offset of D_801E7E15 (ovl_101CE0 data), 12-byte stride
FLAGS = {0x10: "HQ", 0x04: "enemy", 0x02: "liberated"}


def kten():
    d = open("extracted/lha/ktenmain.bin", "rb").read()
    return [d[i:i + 28] for i in range(0, len(d), 28)]


def name(r):
    return r[1:0x16].split(b"\0")[0].decode("latin-1")


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    recs = kten()
    if not sys.argv[1:]:
        print(f"=== ktenmain.bin  {len(recs)} locations")
        for i, r in enumerate(recs, 1):
            u16, b18, flags = struct.unpack_from(">H", r, 0x16)[0], r[0x18], struct.unpack_from(">H", r, 0x19)[0]
            print(f"  {i:3} {name(r):22} [0] {r[0]:2}  [16] {u16:4}  [18] {b18:3}  flags 0x{flags:03X}  [1B] {r[0x1B]}")
    for p in sys.argv[1:] or sorted(glob.glob("extracted/lha/scincsv*.bin")):
        d = open(p, "rb").read()
        print(f"=== {os.path.basename(p)}  {d[0]} locations")
        for i in range(d[0]):
            kid, add = struct.unpack_from(">HH", d, 1 + 4 * i)
            state = " ".join(v for k, v in FLAGS.items() if add & k)
            print(f"  location {i + 1:2}: {name(recs[kid - 1]):22} +0x{add:04X} {state}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
