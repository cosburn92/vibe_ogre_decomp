#!/usr/bin/env python3
"""Dump the class, item, consumable and attack tables from ovl_040E80's data (read from the baserom).

All big-endian. Names that are marked "?" below come from the data only, not yet from code.

gClassTable (0x80187C14): 165 records of 0x48 bytes; id 0 = None. Most fields have a getter in
ovl_040E80 (func_8016D200..func_8016E084) of the form get(class, base): if class's +0x45 equals base,
read class's own record, else read record `base`.
  0x00  name pointer
  0x04  ? (0-2; 0 only for Soldier)
  0x05  gender: 0 male, 1 female, 3 none (stored as 0), 4 random (UnitSetupForLevel)
  0x06  ? (0 for starting classes, 1 for most promoted ones, 2 for a few special ones)
  0x08  7 stats x 4 bytes: u16 base value, u8 growth (1-7), u8 0, for HP, STR, VIT, INT, MEN, AGI,
        DEX. UnitSetupForLevel copies the bases to unit +0x16 (HP; also +0x18), +0x1C..+0x26.
  0x23  u8 copied to unit +0x28 (40-60) ?
  0x24  u8 alignment, copied to unit +0x1B (Cleric 65, Priest 78, Black Knight 30, Lich 15)
  0x25  7 resistances, u8 each, 50 = neutral: Physical, Wind, Flame, Earth, Water, Virtue, Bane
        (the order of the element-name pointer table at 0x80187BD4)
  0x2C  movement type ? (1 flyers, 2 most infantry, 3 Amazon/Archer/Ninja, 4 beast tamers,
        5 Valkyrie/Freya, 7 giants and non-combat classes)
  0x2E  4 u16 default equipment items: weapon, body, off-hand, head (0 = none)
  0x36  ? (0-15)
  0x37  3 rows x (u8 attack id, u8 attack count): front, middle, rear row. Attack ids index
        gAttackTable (1-based; func_8016E440)
  0x3D  4 u8 ?
  0x41  promotion path: u8 class, u8 level, u8 class, u8 level (0xFF = none). ClassAtLevel(class,
        base, level) returns the first class if level < first level, else the second if
        level < second level, else the class itself. UnitSetupForLevel starts a unit as its
        level-1 class and levels it up through this path.
  0x45  base class: for a named or special variant, the generic class it belongs to (0 = itself)
  0x46  unit element, copied to unit +0x1A; 0xFF = random 1-4 (Wind, Flame, Earth, Water)
  0x47  ? (1 for most spellcasters, 2 for most fighters)

gItemTable (0x8018C40C): 278 records of 0x20 bytes; id 0 = None.
  0x00  name pointer
  0x04  category (ItemGetCategory; 1-13 and 24 are weapons, func_8016F9F0). func_80214F80 checks it
        against the class's equipment slots.
  0x05  element (0 none, 1 Wind, 2 Flame, 3 Earth, 4 Water, 5 Virtue, 6 Bane, 7 ?; 0x10 = taken from
        a global, D_80193C12)
  0x06  ? (0-11, rises with the item's strength)
  0x08  u16 price
  0x0A  s8 STR, INT, AGI, DEX, VIT, MEN (getters in unit-stat order read 0x0A, 0x0E, 0x0B, 0x0F,
        0x0C, 0x0D); item 0x84 (Gallant Doll) computes its STR from D_80193C14 / 10
  0x10  s8 ?
  0x11  s8 x 7: Physical (armour value), Wind, Flame, Earth, Water, Virtue, Bane
  0x18  two bytes of four 2-bit fields each, read by the level-up code (func_8016EBA4)
  0x1A  bit 7: flag ? (set on a few unique items)
  0x1B  flags; bit 0 on dragon-slaying weapons, bit 4 on most Virtue weapons
  0x1C  ?

gConsumableTable (0x8018E6CC, right after the items): 12-byte records: name pointer, u8, u8,
  u16 price, u8, u8, 2 bytes 0 (healing items, stat-raising items, key items, ...).

gAttackTable (0x8018AA7C): 16-byte records, name pointer first; id 0 = none.

usage: python3 tools/table_dump.py [classes|items|consumables|attacks]...   # default: all
"""
import struct
import sys

OVL_040E80 = (0x40E80, 0x8016AF80, 0x80190F10)  # ROM start, VRAM start, VRAM end
CLASSES, ITEMS = 0x80187C14, 0x8018C40C
CONSUMABLES, ATTACKS = 0x8018E6CC, 0x8018AA7C
STATS = ["HP", "STR", "VIT", "INT", "MEN", "AGI", "DEX"]
RES = ["Phys", "Wind", "Flame", "Earth", "Water", "Virtue", "Bane"]


def rom_off(vram):
    rom_start, vram_start, _ = OVL_040E80
    return rom_start + vram - vram_start


def name_at(rom, ptr):
    _, vram_start, vram_end = OVL_040E80
    if not vram_start <= ptr < vram_end:
        return None
    o = rom_off(ptr)
    raw = rom[o:rom.index(b"\0", o)]
    # 0x0E/0x0F wrap a two-line name, 0x10 "c" is its line break; 0x81 0x7C is a Shift-JIS dash
    raw = raw.replace(b"\x0e", b"").replace(b"\x0f", b"").replace(b"\x10c", b" ").replace(b"\x10", b" ")
    return raw.decode("cp932", errors="replace")


def records(rom, vram, stride, count=None):
    """[(name, record bytes)] while the first word points at a name (or up to count records)."""
    out = []
    i = 0
    while count is None or i < count:
        o = rom_off(vram + i * stride)
        name = name_at(rom, struct.unpack_from(">I", rom, o)[0])
        if name is None:
            break
        out.append((name, rom[o:o + stride]))
        i += 1
    return out


def dump_classes(rom, names):
    cls, items, attacks = names["classes"], names["items"], names["attacks"]
    print("=== classes (gClassTable)")
    for cid, (name, d) in enumerate(records(rom, CLASSES, 0x48, 165)):
        if cid == 0:
            continue
        stats = " ".join(f"{s} {struct.unpack_from('>H', d, 8 + 4 * k)[0]}/{d[0xA + 4 * k]}"
                         for k, s in enumerate(STATS))
        res = " ".join(f"{r} {d[0x25 + k]}" for k, r in enumerate(RES))
        eq = [struct.unpack_from(">H", d, 0x2E + 2 * k)[0] for k in range(4)]
        eq = ", ".join(items[e] if e < len(items) else f"#{e}" for e in eq if e)
        rows = []
        for k in range(3):
            a, n = d[0x37 + 2 * k], d[0x38 + 2 * k]
            rows.append(f"{attacks[a] if a < len(attacks) else '#%d' % a} x{n}")
        path = [f"{cls[d[0x41 + 2 * k]]} below {d[0x42 + 2 * k]}"
                for k in range(2) if d[0x42 + 2 * k] not in (0, 0xFF) and d[0x41 + 2 * k] < len(cls)]
        base = f"  base class {cls[d[0x45]]}" if d[0x45] not in (0, cid, 0xFF) else ""
        elem = "random" if d[0x46] == 0xFF else d[0x46]
        print(f"{cid:3} {name}{base}")
        print(f"      gender {d[5]}  [4] {d[4]} [6] {d[6]}  move {d[0x2C]}  alignment {d[0x24]}  "
              f"[23] {d[0x23]}  element {elem}  [36] {d[0x36]}  [3D] {list(d[0x3D:0x41])}  [47] {d[0x47]}")
        print(f"      {stats}")
        print(f"      res {res}")
        print(f"      attacks front/middle/rear: {' | '.join(rows)}")
        if eq:
            print(f"      equipment: {eq}")
        if path:
            print(f"      as an enemy: {', '.join(path)}")


def dump_items(rom, names):
    print("=== items (gItemTable)")
    for iid, (name, d) in enumerate(records(rom, ITEMS, 0x20, 278)):
        if iid == 0:
            continue
        price, = struct.unpack_from(">H", d, 8)
        s = struct.unpack_from(">14b", d, 0xA)
        stats = dict(zip(["STR", "INT", "AGI", "DEX", "VIT", "MEN", "[10]"], s[:7]))
        stats.update(zip(RES, s[7:]))
        mods = " ".join(f"{k} {v:+d}" for k, v in stats.items() if v)
        print(f"{iid:3} {name:24} cat {d[4]:2}  elem {d[5]}  [6] {d[6]:2}  price {price:5}  "
              f"{mods}  [18] {d[0x18:0x1D].hex(' ')}")


def dump_consumables(rom, names):
    print("=== consumables (gConsumableTable)")
    for i, (name, d) in enumerate(records(rom, CONSUMABLES, 12)):
        price, = struct.unpack_from(">H", d, 6)
        print(f"{i:3} {name:26} [4] {d[4]:3} [5] {d[5]:3}  price {price:5}  [8] {d[8]} [9] {d[9]}")


def dump_attacks(rom, names):
    print("=== attacks (gAttackTable)")
    for i, (name, d) in enumerate(records(rom, ATTACKS, 0x10)):
        print(f"{i:3} {name:20} {d[4:].hex(' ')}")


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    rom = open("baserom/baserom.us.z64", "rb").read()
    names = {
        "classes": [n for n, _ in records(rom, CLASSES, 0x48, 165)],
        "items": [n for n, _ in records(rom, ITEMS, 0x20, 278)],
        "attacks": [n for n, _ in records(rom, ATTACKS, 0x10)],
    }
    which = sys.argv[1:] or ["classes", "items", "consumables", "attacks"]
    for w in which:
        {"classes": dump_classes, "items": dump_items, "consumables": dump_consumables,
         "attacks": dump_attacks}[w](rom, names)
    return 0


if __name__ == "__main__":
    sys.exit(main())
