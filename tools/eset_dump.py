#!/usr/bin/env python3
"""Dump the per-stage enemy sets (extracted/lha/eset*.bin) with their squad templates (enemydat.bin).

Read by StageSetupUnits (ovl_195410). All big-endian.

eset file:
  0x00  s16 offsets to sections A, B, C, D (0 = absent)
  A     stage parameters, copied to globals:
          0     base level (gStageBaseLevel)
          1     D_801F1036 (always 1; use unknown)
          2     defeat checks (D_801F1037): 1 the stage is lost if the lord dies or the headquarters
                (location flag 0x10) falls; 2 the same plus a deadline (bytes 5-6)
          3-4   starting time of day, hour and minute (gClock: u16 hour at 0x80196A2C, then minute
                and second; hours 6-17 are day). 7:00 for most stages, 18:00 or 21:00 for night ones
          5-6   deadline hour and minute (D_801F0E0C/0D, 0xFF = none), shown on the HUD;
                19:00 in the six timed stages
  B     u8 count, then 18-byte squad records:
          0     legion (0 = none). Consecutive records with the same non-zero value form a legion
                of up to five squads; the first is the legion core, and the others share its
                position. StageSetupUnits builds one 11-byte gLegions record per legion:
                +0 number, +1 flags (0x01 in use, 0x80 enemy), +2-6 squad slots (0xFF = empty),
                +7 0, +8 formation
          1     legion formation, set on the first record of a legion: 1 Mobile Wall, 2 Right
                Ahead, 3 Left Ahead, 4 Grand Arrow, 5 Wedge Shift, 6 Dual Wedge, 7 Funnel Shift,
                8 Wing Shift (gFormationNames). The formation decides which way a beaten enemy
                squad is pushed back
          2     unit slot (bit 7 is set by the game for a few special stage/template pairs)
          3-4   u16 enemy template, 1-based index into enemydat.bin
          5, 6  position: if byte 6 is 0, byte 5 is a 1-based spawn-point index; otherwise x, y in
                1/256ths of the map's extent
          7     sprite scale: v < 3 -> 0.75 + (v-1)/8, else (v-1)/8 - 0.25
          8     starting order (unit +0xBA): 0-3 built in, 4-19 a section C order
          9     retreat setting (unit +0xBB). Enemy squads head for a safe spot and rest until every
                member is at full HP with no fatigue, once a member is below the threshold:
                1 HP < 75% or fatigue > 75, 2 HP < 50% or fatigue > 75, 3 HP < 25% or fatigue > 100,
                4 never, 0 fatigue > 100 only (UnitShouldRetreat). Every squad also uses its
                consumables (SquadUseHealItem / SquadUseFatigueItem): Heal Leaf/Seed/Pack when a
                member is under 25% HP (35% with setting 1), Power/Angel Fruit at fatigue >= 70
          10    battle strategy, stored as v-1 in the squad roster (D_801971F0[slot * 25] +0x17):
                1 Autonomous, 2 Attack Strongest, 3 Attack Leader, 4 Attack Weakest
                (StrategyGetName)
          11    harmony 0-100 (roster +0xC; the Flag of Unity raises it by 1-5, and a
                battle outcome in ovl_213B10 adds 5 for player squads)
          12-14 drop (D_8019367C[slot], enemy squads only): byte 12 set = an item (gItemTable id),
                clear = a consumable (gConsumableTable id); 13-14 u16 id, 0 = none. Dropped with
                an 80% chance when the squad is beaten (InventoryAdd)
          15-17 starting consumables (SquadSetupItems): 15 heals 1 Leaf, 2 Leaf x2,
                3 Leaf x2 + Seed, 4 Seed x2, 5 Seed x2 + Pack, 6 Pack x2; 16 fruit 1 Power x2,
                2 Power + Angel, 3 Angel x2; 17 Revive Stones x1 or x2. The mix repeats until the
                squad's item slots (roster +0xD, up to 10) are full
  C     orders (ovl_101CE0). u8 count, then 18-byte records copied to D_801F0EBE; order id = index + 4.
        func_801CD668 starts a unit's order, func_801CD7F8 carries out a section C one, and
        func_801CF0B0 checks each frame whether it is finished and returns the next order.
          0     id (index + 4)
          1     kind: 0 hold (bytes 2 and 3 go to unit +0x91 / +0x92), 1 move, 2 reserve: the squad
                is taken off the map (clears unit flag 0x1 and bit 0x4 of its roster byte
                D_801971F1[slot * 25]) until its condition holds; UnitStartOrder sets both again
                when the next order starts. Off-map squads are not counted in gEnemySquadsOnMap.
          2     move: route mode 0-2 (unit +0x91)
          3     unit +0x92; 2 = return to the waypoint stored in the unit (flag 0x800000)
          4-9   move: up to three waypoints (x, y) in 1/256ths of the map, or (point index, 0); the
                list ends at the first 0 x/index
          10-16 condition: c1, op1, c2, op2, c3, op3, c4. c = 1-based section D entry, op 0 end,
                2 AND, 3 OR (evaluated left to right); op1 = 1 is a branch: if c1 go to order
                byte 16, else if c2 go to byte 17
          17    next order once the condition holds (0 = none, 1-3 built in, 0xFF = ?)
  D     conditions. u8 count, then 10-byte records copied to D_801F0E19, evaluated per unit by
        func_801CED18:
          0     id (index + 1)
          1     type:
                0x10  the unit is inside the rectangle x0, y0, x1, y1 (bytes 2-5, 1/256ths of the
                      map); bytes 6-7 its centre
                0x17  unit slot byte 6 is inside the rectangle (bytes 8-9: its centre)
                0x15  the unit's flag bit 31 is set (cleared when read)
                0x16  the hour of the day (gClock) is byte 6 (fires once per unit)
                0x18  unit +0x20 equals unit +0x24
                0x19  every member of the squad is at full HP with no status
                0x1A  func_801DD2B0(unit) and the unit's flag 0x1000000 (cleared when read)
                0x1B  unit +0x74 equals byte 6 - 1
                0x14  on stage 0x36: story flags (FlagGet/FlagSet)
                other trigger bit (id - 1) of gStageTriggers (D_801F0EBA); type 9 clears it when read.
        Trigger types (StageTriggerScanUnit / StageTriggerUpdate in ovl_101CE0): every frame 3 map units
        are checked against each condition and matching ones set a pending bit; after a pass over all
        units the pending bits are latched into gStageTriggers. Most triggers stay set once fired;
        types 5, 9, 0xC and 0xE are re-evaluated every pass. "Player" = unit flag 0x8 set, "enemy" =
        clear; a "location" is a town/stronghold (unit +0x74 = location - 1):
                1     a player unit is in the rectangle x0, y0, x1, y1 (bytes 2-5)
                2     no enemy unit is in the rectangle
                3     no enemy unit is near map point byte 6
                4     a player unit is at location byte 6
                5     unit slot byte 6 is in the rectangle (bytes 8-9: a point near it)
                6     story flag: byte 6 (1, 6-0x12, 0x17) selects FlagGet(0-0xE)
                7     a player unit is near map point byte 6
                8     unit slot byte 6 is in the rectangle
                9     at most byte 6 enemy squads are left on the map (gEnemySquadsOnMap)
                0xA   the squad in slot byte 6 is gone (its flag 0x10 is clear)
                0xC   the enemy has taken location byte 6 (flag 0x4 of gLocations[n - 1] +0x1C; 0x24-byte
                      records). Flag 0x2 = liberated by the player. An enemy squad sent to a
                      location captures it once it is in range with no player unit nearby,
                      swapping 0x2 for 0x4; liberating it again swaps them back
                0xD   a player unit is at location byte 6 or byte 7
                0x13  the squad in slot byte 6 is gone or inactive (func_801D92D0)
                Unused by the eset files: 0xB, 0xE, 0xF (0xB and 0xF are scanned but never latched).
        Four files (eset4_08b, eset4_14_, eset5_02, eset5_04) have conditions but no section D.

enemydat.bin: 556 squad templates of 35 bytes (eset ids go up to 554):
  0x00  leader class, 0x01 leader level (signed, relative to the stage's base level),
  0x02-0x05 four item ids (gItemTable, 0 = none), each equipped by CharacterEquipItem in the slot
  whose class default item (class +0x2E-0x34) has the same category; 0x06 leader position (1-9 on
  the 3x3 formation grid)
  0x07  group A class (0 = none), 0x08 level, 0x09-0x0C four items, 0x0D-0x0F positions (0 = unused)
  0x10  group B class, 0x11 level, 0x12-0x15 four values, 0x16-0x18 positions
  0x19-0x22 always zero
Class ids index the class table (gClassTable, 165 records of 0x48 bytes at 0x80187C14 in ovl_040E80,
name pointer first; 0 = None). Item ids index the item table (gItemTable, 278 records of 0x20 bytes at
0x8018C40C; 0 = None). Names are read from the baserom; tools/table_dump.py dumps both tables.

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
        # names may hold formatting bytes: 0x0E/0x0F wrap a two-line name, 0x10 "c" is its line break
        raw = raw.replace(b"\x0e", b"").replace(b"\x0f", b"").replace(b"\x10c", b" ").replace(b"\x10", b" ")
        out.append(raw.decode("cp932", errors="replace"))
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


COND_TYPES = {0x10: "unit in area", 0x17: "slot in area", 0x15: "unit flag 31", 0x16: "hour is",
              0x18: "unit +0x20 == +0x24", 0x19: "squad healthy", 0x1A: "unit event",
              0x1B: "unit +0x74", 0x14: "story flags",
              0x01: "player unit in area", 0x02: "no enemy in area", 0x03: "no enemy near point",
              0x04: "player at location", 0x05: "slot in area (live)", 0x06: "story flag",
              0x07: "player near point", 0x08: "slot in area", 0x09: "enemy squads left <=",
              0x0A: "squad gone", 0x0C: "enemy holds location", 0x0D: "player at location",
              0x13: "squad gone or inactive"}


def point(x, y):
    return "-" if not x else f"point {x}" if not y else f"({x},{y})"


STRATEGY = {1: "autonomous", 2: "strongest", 3: "leader", 4: "weakest"}
CONSUMABLES = ["None", "Heal Leaf", "Heal Seed", "Heal Pack", "Power Fruit", "Angel Fruit",
               "Revive Stone", "Altar of Resurrection", "Quit Gate"]


def drop(r, items):
    v = r[13] << 8 | r[14]
    if not v:
        return ""
    if r[12]:
        return f"  drops {items[v] if v < len(items) else v}"
    return f"  drops consumable {CONSUMABLES[v] if v < len(CONSUMABLES) else v}"


FORMATIONS = ["", "Mobile Wall", "Right Ahead", "Left Ahead", "Grand Arrow", "Wedge Shift",
              "Dual Wedge", "Funnel Shift", "Wing Shift"]
RETREAT = {0: "fatigued", 1: "HP<75%", 2: "HP<50%", 3: "HP<25%", 4: "never"}


def dump_orders(d, off):
    kinds = {0: "hold", 1: "move", 2: "reserve"}
    for i in range(d[off]):
        r = d[off + 1 + 18 * i:off + 19 + 18 * i]
        desc = f"  order {r[0]:2}: {kinds.get(r[1], f'kind {r[1]}')} [{r[2]},{r[3]}]"
        if r[1] == 1:
            pts = []
            for k in (4, 6, 8):
                if not r[k]:
                    break
                pts.append(point(r[k], r[k + 1]))
            desc += " via " + " -> ".join(pts) if pts else ""
        c, ops = r[10:17:2], r[11:16:2]
        if r[11] == 1:
            cond = f"if D{c[0]} -> order {r[16]}, elif D{c[1]} -> order {r[17]}"
        elif c[0]:
            cond = f"D{c[0]}"
            for op, cc in zip(ops, c[1:]):
                if not op:
                    break
                cond += {2: " and ", 3: " or "}.get(op, f" op{op} ") + f"D{cc}"
            cond = f"when {cond} -> order {r[17]}"
        else:
            cond = f"-> order {r[17]}" if r[17] else "(no next order)"
        print(f"{desc}; {cond}")


def dump_conditions(d, off):
    for i in range(d[off]):
        r = d[off + 1 + 10 * i:off + 11 + 10 * i]
        name = COND_TYPES.get(r[1], "trigger")
        extra = ""
        rect = f"({r[2]},{r[3]})-({r[4]},{r[5]})"
        if r[1] in (0x10, 0x01, 0x02):
            extra = f" {rect}"
        elif r[1] in (0x17, 0x05, 0x08):
            extra = f" slot {r[6]} in {rect}"
        elif r[1] in (0x03, 0x07):
            extra = f" point {r[6]}"
        elif r[1] in (0x04, 0x0C):
            extra = f" {r[6]}"
        elif r[1] == 0x16:
            extra = f" {r[6]}:00"
        elif r[1] == 0x0D:
            extra = f" {r[6]} or {r[7]}"
        elif r[1] in (0x09, 0x06):
            extra = f" {r[6]}"
        elif r[1] in (0x0A, 0x13):
            extra = f" slot {r[6]}"
        print(f"  cond D{r[0]}: type {r[1]:#04x} {name}{extra}  [{r[2:].hex(' ')}]")


def dump(path, enemydat, classes, items):
    d = open(path, "rb").read()
    offs = struct.unpack_from(">4h", d, 0)
    print(f"=== {os.path.basename(path)}  sections {['%#x' % o if o else '-' for o in offs]}")
    if offs[0]:
        a = d[offs[0]:offs[0] + 7]
        deadline = f", deadline {a[5]}:{a[6]:02}" if a[2] == 2 else ""
        print(f"  stage: base level {a[0]}, starts {a[3]}:{a[4]:02}{deadline}  [1] {a[1]}")
    if not offs[1]:
        return
    count = d[offs[1]]
    for i in range(count):
        r = d[offs[1] + 1 + 18 * i:offs[1] + 19 + 18 * i]
        tid, = struct.unpack_from(">H", r, 3)
        pos = f"spawn point {r[5]}" if r[6] == 0 else f"x={r[5]}/256 y={r[6]}/256"
        legion = f"  legion {r[0]}" + (f" {FORMATIONS[r[1]]}" if r[1] < len(FORMATIONS) and r[1] else "") if r[0] else ""
        print(f"  squad    slot {r[2] & 0x7F:2} template {tid:3}  {pos:22} scale {r[7]}  "
              f"order {r[8]:2} retreat {RETREAT.get(r[9], r[9])}  {STRATEGY.get(r[10], r[10])}  harmony {r[11]}"
              f"  heal/fruit/revive {r[15]}/{r[16]}/{r[17]}{drop(r, items)}{legion}")
        for g in template(enemydat, tid):
            lv = f"{g['level']:+d}"
            cls = classes[g["class"]] if g["class"] < len(classes) else f"#{g['class']}"
            its = [items[i] if i < len(items) else f"#{i}" for i in g["items"] if i]
            print(f"      {cls:18} level {lv:>3} at {g['positions']}" + (f"  items {its}" if its else ""))
    if offs[2]:
        dump_orders(d, offs[2])
    if offs[3]:
        dump_conditions(d, offs[3])


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    enemydat = open("extracted/lha/enemydat.bin", "rb").read()
    rom = open("baserom/baserom.us.z64", "rb").read()
    classes = name_table(rom, 0x80187C14, 0x48, 165)
    items = name_table(rom, 0x8018C40C, 0x20, 278)
    for path in sys.argv[1:] or sorted(glob.glob("extracted/lha/eset*.bin")):
        dump(path, enemydat, classes, items)
    return 0


if __name__ == "__main__":
    sys.exit(main())
