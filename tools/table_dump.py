#!/usr/bin/env python3
"""Dump the class, item, consumable and attack tables from ovl_040E80's data (read from the baserom).

All big-endian. Fields marked "?" are not understood yet.

gClassTable (0x80187C14): 165 records of 0x48 bytes; id 0 = None. Most fields have a getter in
ovl_040E80 (func_8016D200..func_8016E084) of the form get(class, base): if class's +0x45 equals base,
read class's own record, else read record `base`.
  0x00  name pointer
  0x04  unit size: 1 small, 2 large (dragons, beasts, golems, Ogre); 0 only for Soldier. The squad
        screens count units by it.
  0x05  gender: 0 male, 1 female, 3 none (stored as 0), 4 random (UnitSetupForLevel)
  0x06  leadership: 0 cannot lead a squad, 1 can, 2 special leaders (Princess, Centurion, Lord, ...;
        checked with == 2)
  0x08  7 stats x 4 bytes: u16 base value, u8 growth (1-7), u8 0, for HP, STR, VIT, INT, MEN, AGI,
        DEX. UnitSetupForLevel copies the bases to unit +0x16 (HP; also +0x18), +0x1C..+0x26.
  0x23  luck, copied to unit +0x28 and from there to battle unit +0x30. The battle hit/effect chance
        (func_801F32EC_ovl_22A280) uses attacker luck + equipment luck - target luck - equipment + 100.
  0x24  u8 alignment, copied to unit +0x1B (Cleric 65, Priest 78, Black Knight 30, Lich 15)
  0x25  7 resistances, u8 each, 50 = neutral: Physical, Wind, Flame, Earth, Water, Virtue, Bane
        (the order of the element-name pointer table at 0x80187BD4)
  0x2C  movement type 1-7 (1 flyers, 2 most infantry, 3 Amazon/Archer/Ninja, 4 beasts, 5 Valkyrie/
        Freya, 6 Zombies/Hydra/Blue Dragon, 7 giants and non-combat classes). Battle code indexes a
        signed modifier table by (type - 1) x 29 terrains + terrain (D_801F6910_ovl_22A280).
  0x2E  4 u16 default equipment items: weapon, body, off-hand, head (0 = none)
  0x36  locked equipment slots, one bit per slot (1 weapon, 2 body, 4 off-hand, 8 head): Soldier 3
        (Short Spear, Half Armor), Lycanthrope 15, Princess 8 (Dream Tiara), Lich 8, Vampire 10
  0x37  3 rows x (u8 attack id, u8 attack count): front, middle, rear row. Attack ids index
        gAttackTable (1-based; func_8016E440)
  0x3D  4 u8 bases for physical attack, magic attack, physical defence, magic defence. The
        formation screen (ovl_14EBE0, func_80201E4C..func_802017C0) computes e.g. magic attack as
        (base + equipment INT) / 20 * (INT + 50) / 50 * (MEN + equipment MEN + 100) / 100 * a row
        factor; the defences add the equipment resistances.
  0x41  promotion path: u8 class, u8 level, u8 class, u8 level (0xFF = none). ClassAtLevel(class,
        base, level) returns the first class if level < first level, else the second if
        level < second level, else the class itself. UnitSetupForLevel starts a unit as its
        level-1 class and levels it up through this path.
  0x45  base class: for a named or special variant, the generic class it belongs to (0 = itself)
  0x46  unit element, copied to unit +0x1A; 0xFF = random 1-4 (Wind, Flame, Earth, Water)
  0x47  squad item slots the unit brings: a squad can carry the sum over its 9 formation cells
        (empty cell = 1, at most 10); extra items go back to the army's stock (func_801D0484_ovl_087200)

gItemTable (0x8018C40C): 278 records of 0x20 bytes; id 0 = None.
  0x00  name pointer
  0x04  category (ItemGetCategory; 1-13 and 24 are weapons, func_8016F9F0). func_80214F80 checks it
        against the class's equipment slots.
  0x05  element (0 none, 1 Wind, 2 Flame, 3 Earth, 4 Water, 5 Virtue, 6 Bane, 7 ?; 0x10 = taken from
        a global, D_80193C12)
  0x06  ? (0-11, rises with the item's strength; 0 on a few special items, which the inventory code
        treats differently)
  0x08  u16 price
  0x0A  s8 STR, INT, AGI, DEX, VIT, MEN (getters in unit-stat order read 0x0A, 0x0E, 0x0B, 0x0F,
        0x0C, 0x0D); item 0x84 (Gallant Doll) computes its STR from D_80193C14 / 10
  0x10  s8 luck modifier (see class +0x23)
  0x11  s8 x 7: Physical (armour value), Wind, Flame, Earth, Water, Virtue, Bane
  0x18  two bytes of four 2-bit fields each: growth modifiers that UnitLevelUp reads from the
        equipped items (which field goes with which stat is not mapped yet)
  0x1A  bit 7: flag ? (set on a few unique items; an inventory screen marks them)
  0x1B  effects the weapon inflicts; 0x1C effects the armour protects against (same bits). Bit 0:
        dragons. Against a dragon (IsDragon: class 56-68 or 164), func_801F139C_ovl_22A280 returns 5
        if the unit is a Dragoon or wears an item with +0x1B bit 0; func_801F1444_ovl_22A280 is the
        same check with +0x1C bit 0 (Dragon armour). Bits 1, 2, 3 and 5 are status effects (func_801F45C0_ovl_22A280 masks the
        weapon's bits by the target's armour and class immunities). Bit 4 is on most Virtue weapons.

gConsumableTable (0x8018E6CC, right after the items): 45 records of 12 bytes:
  0x00  name pointer
  0x04  kind (by content): 0 battle items (Heal Leaf..Altar of Resurrection), 1 stat-raising items
        (Champion Statuette..Flag of Unity), 2 map items (Quit Gate, Silver Hourglass, Dowsing Rod,
        Love and Peace), 3 the eight items from Medal of Vigor to Charge Horn, 4 key items
  0x05  1 on map and key items ?
  0x06  u16 price
  0x08  target ? (1 one unit, 2 a squad, ...), 0x09 where usable ? (bit mask; 7 for battle items)

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
        print(f"      gender {d[5]}  size {d[4]}  leader {d[6]}  move {d[0x2C]}  alignment {d[0x24]}  "
              f"luck {d[0x23]}  element {elem}  locked slots {d[0x36]:#x}  item slots {d[0x47]}")
        print(f"      phys attack/magic attack/phys defence/magic defence bases {list(d[0x3D:0x41])}")
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
        stats = dict(zip(["STR", "INT", "AGI", "DEX", "VIT", "MEN", "LUK"], s[:7]))
        stats.update(zip(RES, s[7:]))
        mods = " ".join(f"{k} {v:+d}" for k, v in stats.items() if v)
        print(f"{iid:3} {name:24} cat {d[4]:2}  elem {d[5]}  [6] {d[6]:2}  price {price:5}  "
              f"{mods}  growth {d[0x18:0x1A].hex()}  flags {d[0x1A]:#x} inflict {d[0x1B]:#x} protect {d[0x1C]:#x}")


def dump_consumables(rom, names):
    print("=== consumables (gConsumableTable)")
    for i, (name, d) in enumerate(records(rom, CONSUMABLES, 12)):
        price, = struct.unpack_from(">H", d, 6)
        print(f"{i:3} {name:26} kind {d[4]:3} [5] {d[5]:3}  price {price:5}  [8] {d[8]} [9] {d[9]}")


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
