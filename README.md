# Ogre Battle 64 decompilation

Work-in-progress decompilation of *Ogre Battle 64: Person of Lordly Caliber* (USA).

No game content is included in this repository. You must supply your own ROM.

| Version | File | SHA-1 |
|---|---|---|
| US | `baserom/baserom.us.z64` | `9cd0cfb50b883edb068e0c30d213193b9cf89895` |

## Setup (Windows + WSL Ubuntu, or Linux)

```sh
sudo apt install -y binutils-mips-linux-gnu make python3-pip qemu-user-static
pip install "splat64[mips]"
make toolchain # fetch KMC GCC 2.7.2 + KMC binutils 2.6 into tools/
make extract   # split the ROM into asm/ and assets/
make           # rebuild and verify the ROM matches
```

`qemu-user-static` is only needed on WSL1, which can't run the 32-bit `cc1`; the Makefile uses it
automatically when `cc1` won't run natively.

## Compiler

The game was built with **KMC GCC 2.7.2** (`-O2 -G0 -mips3 -mgp32 -mfp32`) and assembled with the
KMC-era GNU `as` 2.6. The old assembler matters: it inserts a `nop` between back-to-back FP multiplies
(the VR4300 "mulmul" errata fix), which modern binutils doesn't do. C files in `src/` are
preprocessed with the host `cpp` (KMC's `cpp` crashes under qemu, and preprocessing doesn't affect
codegen), compiled with `cc1`, and assembled with the KMC `as`.

To test a candidate C function against the ROM without touching the build:

```sh
tools/matchtest/check.sh candidate.c <rom_offset> <size>   # prints MATCH or an asm diff
```

Workflow for decompiling a file:

```sh
tools/to_c.sh FDC0              # asm segment -> src/FDC0.c of INCLUDE_ASM stubs (+ its rodata chunk)
make                            # still matches; now replace stubs with C one at a time
tools/romdiff.sh 0xFDC0 0x150   # disassembly diff of a ROM range when it doesn't
```

### Data, rodata and BSS

Each source file's `.data`, `.rodata` and `.bss` sit in one chunk per section, and the chunks appear
in the same order as the files' `.text`. `tools/section_chunks.py` assigns chunks to text files by which
file references their symbols and emits the yaml subsegments:

```sh
python3 tools/section_chunks.py data   2E570 3E100 --cut 38CF0
python3 tools/section_chunks.py rodata 3E100 3F1B0 --cut 3EE70
python3 tools/section_chunks.py bss 800AEDB0 800C47F0 --own 800B17A0=10190   # VRAM, no ROM
```

Rodata ownership is unambiguous. Data is noisier, because shared globals are referenced from many
files, so the script follows the longest run of owners that increases in ROM order. A wrong boundary
between two asm chunks doesn't matter, but **check a file's chunk by hand before converting it to C**
(`-v` lists every symbol with its referencing files), and use `--cut` where the chunk should end
earlier. Once a file is C, its chunks become `.data`/`.rodata` so they're linked from the C object;
for `INCLUDE_ASM` functions splat migrates the rodata into the function's `.s`.

Main's BSS is per-file `static` variables (`.lcomm`) from `0x800AEDB0`, then from `0x800C47F0` the
linker's COMMON area: uninitialized non-static globals, which GCC 2.7.2 emits as `.comm` and the
linker allocates in its own order. That area stays one asm chunk (`common`), and the linker script
has no `*(COMMON)` rule, so C files must declare those globals `extern` rather than define them.
Watch for one-past-the-end addresses: `main()` passes its thread stack top, which equals the next
file's first BSS symbol, so `reloc_addrs.txt` rewrites it as `gIdleThreadStack + 0x2000`.

Every input already carries its own padding, so the linker script uses `SUBALIGN(4)` and asm files are
assembled with `-no-pad-sections`. KMC GCC 2.7.2 puts explicitly zero-initialized globals
(`s32 x = 0;`) in `.data`, not `.bss`.

## Assets

The whole asset region is mapped, and `make extract-assets` (`tools/extract_assets.py`) unpacks it to
`extracted/` (gitignored, about 30 s). The build keeps the original bytes.

| ROM range | Contents | Extracted to |
|---|---|---|
| `0x2B8BA0`–`0x594280` | libmus sound data: two sample banks (`.ptr` + `.wbk`), a table, songs | `sound/` |
| `0x594280`–`0x275DD0F` | the asset archive (below) | `lha/`, `chunks/` |
| `0x275DD0F` | version string `ORGE3_ROM_VER_99/05/30_22:47:42`, then `0xFF` padding | |

The sound overlay `ovl_03F1B0` DMAs the libmus pieces by literal start/end ROM addresses, which give
the boundaries.

The asset archive is `[u32 chunk count (25,794)][index: 79 handle slots][chain of 25,795 chunks]`.
The game addresses every chunk by its **handle**, its offset from `0x594280`. `LoadChunk(handle)`
reads the size at `0x594280 + (handle & 0x0FFFFFFF)`, DMAs the payload and LZ-decodes it, and
`LoadChunkRaw` skips the decoding. The top 4 bits of a handle are flags. Stored chunks that hold handle
lists tie assets together. Extracted chunks are named by handle.

Each chunk is `[u32 BE size][payload]` on a 2-byte boundary (size may be 0), and the payload is one of:
- **An LHA archive** (524): 828 members in all, mostly `-lh5-`, with their original filenames
  (`.bin` ×565, `.n64` ×119, `.bg2`, `.k64`, some Shift-JIS). Each is verified against its
  header's CRC-16. Many `.n64` files are 153,608 bytes: a 320×240 16-bit image plus an 8-byte header.
- **The game's own LZ, "format 1"** (24,582): `[u32 BE unpacked size][stream]`, decoded by
  `DecodeLZ` (`func_8007A110`) on the `UnpackProc` thread. Every one decodes to exactly its stated
  size. Control bytes:

  | byte | meaning |
  |---|---|
  | `1LLLLDDD` `DD` | copy `L+3` bytes from `D+1` back (11-bit distance) |
  | `01NNNNNN` | `N+1` literal bytes follow |
  | `001NNNNN` | `N+2` zero bytes |
  | `0001LLLL` `HHDDDDDD` `DD` | copy `(L \| HH<<4)+4` bytes from `D+1` back (14-bit distance) |
  | `00` `LL` `DDDD` | copy `L+5` bytes from `D+1` back (16-bit distance) |
  | `01` `LL` / `02` `LL` | `L+3` bytes of `0xFF` / zero |

  Two-thirds of them decompress to `UT` sprite graphics (16,957, below).
- **Stored data** (658): uncompressed images tagged `HU` (320×240, `HUFF`) or `B5`, offset tables,
  and similar.

### UT sprites

`UT` chunks hold unit sprite graphics: each part is a pose or body piece with one or more frames, as
CI8 colour indices plus a 4bpp alpha plane, coloured by a separate palette chunk of 256-colour
RGBA5551 palettes. A unit set is a stored table of handles, `[frames, animations, info, palettes, UT part, ...]`
(231 of them). `UnitSetLoad` in `ovl_1CE070` loads it, and `UnitSetLoadPart` converts part `i` to a
texture with `UtCreateTexture`, using palette `info[u32(info + 0x1C) + i]`. The info chunk starts with
the part count. In all 231 sets the indices are in range and use every palette. The byte layout is
in `tools/ut2png.py`, which renders sets with each part's own palette:

```sh
python3 tools/ut2png.py set 0x3BAC1C out.png      # every part of a unit set, in colour
python3 tools/ut2png.py frames 0xF72D3C out.png   # the set's composite frames
python3 tools/ut2png.py anims 0x3BAC1C            # disassemble the set's animations
python3 tools/ut2png.py all extracted/ut/         # all sets
```

- **Frames** (entry 0): composite sprite frames. Each is a list of pieces `{part, x, y, w, h,
  flags, scale x, scale y}`, with flags bit 0 = mirror horizontally and scale `0x400` = 1.0. All
  13,402 frames in the 231 sets reference valid parts, with the parts' own sizes.
- **Animations** (entry 1): byte-code scripts, a command count then commands. The player is
  `UnitAnimStep` in `ovl_1CE070` (a copy, `UnitAnimStep2`, sits in the same overlay). Its command
  fetcher's opcode-length table matches the data for all 17 opcodes in use, and all 8,741 scripts
  parse exactly. The player keeps a position offset, a call stack, a loop stack, and 16 channels
  with per-step deltas. **Channel `k` is the opacity of piece `k` of the current frame**:
  `BattleDrawUnitSprite` skips a piece whose channel is 0 and otherwise sets its alpha to
  `unit alpha × channel / 255` via `SetPrimColor`. So `0D FF 00` then `10 FF 10` fades the whole
  sprite in, and `0D FF FF` then `10 FF F8` fades it out.

  | op | args | effect |
  |---|---|---|
  | `00` | | end: return from a call, else reset to the unit's default animation |
  | `01` | f t | show frame `f` for `t` ticks (`15 lo hi t`: 16-bit frame number) |
  | `02` / `0C` | a b / a b c | move: x −= a, y −= b / x −= a, y += b, z += c |
  | `03` | t | wait `t` ticks |
  | `04` / `05` | n | jump to command `n` / start animation `n` |
  | `0D` / `10` | ch v | set piece `ch`'s opacity / its per-step change (`ch` = `FF`: all 16) |
  | `0E` | n c | repeat from command `n`, `c` times |

  The battle interpreter `BattleAnimStep` (`ovl_1F0A30`, copied as `BattleAnimStep2` in
  `ovl_29A4C0`) adds:

  | op | args | effect |
  |---|---|---|
  | `0F` | a | call animation `a` (`00` returns) |
  | `11` / `13` | hi lo | play sound `table[hi << 8 \| lo]` on channel A / B (`SoundRequest`) |
  | `12` / `14` | hi lo | play a sound chosen by the unit's class and weapon, at its position, on channel A / B |
  | `0B` | | timing marker: `BattleAnimEventTimes` dry-runs an animation and returns when each `0B` is reached (e.g. to sync a hit) |

  `06` does nothing in any interpreter (it's used twice), and `07`–`0A` are never used. Animation
  numbers seem to come in banks of 50.

Not decoded yet: the sound ID tables, the second per-part byte array at
`info + 0x20`, the other piece flag bits (bit 2 may be additive blending, used by glow effects), and how frames map
to unit actions.

### Images

`tools/img2png.py` converts the game's image formats (477 files; the byte layouts are in its header
comment):

- **`"64"` textures** (`.n64` files and LZ chunks, 263 of them): the header holds the RDP image
  format (RGBA / CI / I) and pixel size (4/8/16/32-bit) in the N64's own encoding, then width and
  height, then the pixels with rows padded to 8 bytes, then any CI palette. 260 match the size
  formula exactly. Examples: full-screen backgrounds (`camp.n64`), title-screen text, menu labels.
- **`"B5"` tiled images** (`.bg2` backgrounds and `.b5` chunks): a tile count and anchor, then tiles
  with their own position and size. Kind 1 is RGBA16, and kind 0 is RGBA16 plus an 8-bit alpha
  plane. All 571 tiles have the predicted sizes. Backgrounds can be larger than the screen (e.g.
  440×330).

- **`"HU"` images** (34 chunks, plus B5 kind-3 tiles): JPEG-style, decoded in two halves. The CPU
  does the Huffman stage (`HuDecode` in main), and the N64 SDK's JPEG microcode (`M_NJPEGTASK`,
  submitted by `BgJpegTask`) does dequantization, the IDCT and YUV→RGB. It's baseline JPEG in all
  but the details: the standard Annex K Huffman tables and luminance quantization table, 16×16
  4:2:0 macroblocks, and differential DC, but with no `FF` byte stuffing, the zigzag walking a
  transposed (column-major) block, one quantization table for all components, and chroma stored
  with a +128 offset. Examples: battle-map ground, a castle throne hall.

```sh
python3 tools/img2png.py extracted/lha/camp.n64 camp.png
python3 tools/img2png.py all extracted/png/        # about 45 s
```

- **`"K"` textures** (60 UI icons and labels, e.g. "BATTLE STRATEGY"): `"64"` with a short palette.
  The header byte after `K` is the last palette index used, and only that many colours follow the
  pixels. All 60 fit exactly.
- **Headerless RGBA16** (they start with the transparent key colour `0x07C0`): location pictures
  `k001`–`k025.k64` (84×67), map markers `kmark*.k64` (20×20) and `kmarks*.k64` (20×13), and name
  plates `kname_*.bin` (24×33). Their sizes come from the image data, not a header (`--raw16 W` for
  others).

Not decoded yet: B5 kind 5 (2 files), one `"64"` file with pixel size 4, and the data formats
(`.bin` files, headerless chunks).

### Dialogue text

The 348 `serifu*` / `Serifu_*` files (9,138 messages) are dialogue: a table of u32 offsets, then
NUL-terminated strings. The text is ASCII with inline `@` control codes and `{T##}` glyphs, and some
untranslated Japanese is left in the US ROM in Shift-JIS. `tools/text_dump.py` dumps it all (every
message decodes); `--plain` renders newlines, page breaks and ellipses. The control-code meanings in
its header (`@n` newline, `@p` page, `@c` clear, `@k`/`@F###` speaker, `@l#` colour, `@%#` name
insertion, `@T###` pause, …) are inferred from context, not yet from the game's text engine.

```sh
python3 tools/text_dump.py --plain extracted/lha/serifu_00_0.bin
```

### Enemy sets (`eset*`)

The 63 `eset<chapter>_<map>[variant].bin` files (one LHA archive, handle `0x21B35BA`, reached through
the 4-byte indirection chunk `0x21B35B2`) are per-stage enemy setups. `ovl_0EBBB0` loads the stage's
member with `LoadAsset(0x21B35B2, 0, -4, D_8018F5A8[stage * 9])`, and `StageSetupUnits` in
`ovl_195410` reads it together with `enemydat.bin` (handle `0x21AE74C`). `tools/eset_dump.py`
prints them, with the byte layouts in its header:

- **eset file:** four section offsets; stage parameters including the base level; then 18-byte
  squad records giving the legion and its formation, unit slot, template id, position (a spawn point or x/y in
  1/256ths of the map), sprite scale, starting order, retreat setting and behaviour bytes. 891
  records in all.
- **Legions** (bytes 0 and 1): consecutive squads with the same non-zero byte 0 form a legion of up
  to five squads that marches together behind its first squad, the legion core. Byte 1 of the
  first record is the legion's formation: 1 Mobile Wall, 2 Right Ahead, 3 Left Ahead, 4 Grand
  Arrow, 5 Wedge Shift, 6 Dual Wedge, 7 Funnel Shift, 8 Wing Shift (`gFormationNames` in
  `ovl_14EBE0`). The in-game help says the formation decides which way a beaten enemy squad is
  pushed back. `StageSetupUnits` fills an 11-byte `gLegions` record per legion, with the formation
  at `+8`. Legions appear in 18 stage files, mostly in Funnel Shift (19) or Dual Wedge (11).
- **Retreat setting** (byte 9, unit `+0xBB`): an enemy squad leaves its order to rest once a member
  is below 75%, 50% or 25% HP (settings 1, 2, 3) or too fatigued. It stays until everyone is at
  full HP with no fatigue. Setting 4 never retreats; 2 (340 squads) and 4 (272) are the most
  common. Squads also use their Heal Leaves/Seeds/Packs below 25% HP and Power/Angel Fruit at
  fatigue 70 (`SquadUpkeep`, `UnitShouldRetreat`, `SquadUseHealItem`, `SquadUseFatigueItem` in
  `ovl_101CE0`).
- **The other squad bytes:** byte 10 is the battle strategy (Autonomous, Attack Strongest, Attack
  Leader, Attack Weakest; `gStrategyNames`) and byte 11 the squad's harmony (0–100; the Flag of
  Unity raises it). Bytes 12–14 are what the squad drops when beaten, with an 80% chance: an item
  if byte 12 is set, otherwise a consumable (`InventoryAdd`). Bytes 15–17 pick its starting heal
  items, Power/Angel Fruit and Revive Stones (`SquadSetupItems`); the mix is repeated to fill the
  squad's item slots.
- **Section C, orders:** 18-byte records, one per order id from 4 up. A squad's starting order is
  byte 8 of its record. An order is "hold", "move" (through up to three waypoints given as map
  coordinates or point indexes) or "reserve". A reserve squad is off the map, and not counted
  as an enemy squad, until its condition holds; the next order puts it on the map at its spawn
  point. An order also has a condition and the next order to switch to once the condition holds.
  The condition is up to four section D entries joined by AND/OR, or a two-way branch.
  `OrderCheckNext` in `ovl_101CE0` checks it every frame, `UnitStartOrder` starts the next order
  and `UnitStartScriptOrder` carries out a section C one. This is how patrols, ambushes and
  reinforcements are scripted.
- **Section D, conditions:** 10-byte records evaluated per unit by `func_801CED18`:
  - "the unit is inside this rectangle" or "another unit is";
  - "the squad is fully healed";
  - unit event flags;
  - otherwise a trigger bit in `gStageTriggers`. Each frame, `StageTriggerUpdate` checks three map
    units against every condition (`StageTriggerScanUnit`). After a full pass it latches the results:
    - a player unit in an area, at a town/stronghold, or near a map point;
    - no enemy left in an area;
    - a given squad in an area, or defeated;
    - at most N enemy squads left on the map;
    - a story flag, or the enemy holding a town/stronghold. Each location has flags in
      `gLocations` (0x24-byte records, flags at `+0x1C`): 0x2 liberated by the player, 0x4
      taken by the enemy. An enemy squad heading for a location captures it once it is in range
      with no player unit nearby (in `func_801C2B70`); the player liberating it swaps the bits
      back. `LocationSetLiberated`, `LocationSetCaptured` and `LocationClearOwner` set them
      directly.

    Most triggers stay set once fired; a few are re-evaluated every pass.
- **`enemydat.bin`:** 556 squad templates of 35 bytes, each a leader plus up to two member groups.
  Each has a class, a level relative to the stage's base level, four values that are probably
  equipment, and positions on the 3×3 formation grid. Every eset template id is in range, every
  position is 1–9, and a group's class is 0 exactly when it has no positions.

Class and item ids index tables in `ovl_040E80`'s data, which the dump uses for names.

### Class, item and attack tables

`tools/table_dump.py` prints the tables in `ovl_040E80`'s data, with the field layouts in its header.
The fields come from the getters in `ovl_040E80` (one function per field) and from `UnitSetupForLevel`,
which builds a unit of a given class and level:

- **`gClassTable`** (165 × 0x48 bytes, 0 = None) holds:
  - gender, unit size (small/large), and leadership (whether the class can lead a squad);
  - the seven stats as a u16 base plus a growth grade (HP, STR, VIT, INT, MEN, AGI, DEX);
  - alignment and luck;
  - seven resistances (Physical, Wind, Flame, Earth, Water, Virtue, Bane; 50 = neutral);
  - a movement type, which battle code uses to index a terrain-modifier table;
  - four default equipment items, and a mask of equipment slots the player can't change
    (the Soldier's spear and armour, the Princess's tiara);
  - the attack type and count for each row (front, middle, rear);
  - base physical attack, magic attack, physical defence and magic defence. The formation screen
    combines them with stats and equipment;
  - the unit's element (0xFF = random);
  - how many item slots the unit adds to its squad (the squad's total is capped at 10);
  - a base class, for named and special variants;
  - a promotion path: two (class, level) pairs. `ClassAtLevel` uses them so that a Paladin made at
    level 5 is a Fighter, and one made at level 14 is a Knight. `UnitSetupForLevel` levels a unit up
    through that path.
- **`gItemTable`** (278 × 0x20 bytes) holds:
  - category (1–13 and 24 are weapons);
  - element;
  - price;
  - signed modifiers for the stats, luck, and the seven resistances (Physical is the armour value);
  - level-up growth bonuses, 0–3 per stat (HP, STR, INT, AGI, DEX, VIT, MEN, luck). `UnitLevelUp`
    adds them for each equipped item, on top of the class's growth grade plus a 0–2 roll. The game
    reads the HP field for STR too, so the STR field (on the Ogre Blade, Heavy Axe and Ogre armour)
    never takes effect, and HP-growth items raise STR as well;
  - effects a weapon inflicts and effects armour blocks, using the same bits: dragons, Sleep,
    Paralyze, Petrify, Purify (most Virtue weapons) and Poison. Dragon-slaying weapons, or a
    Dragoon, get a bonus against dragons (`IsDragon`). Battle code drops the statuses the target's
    armour or class immunities block.
- **`gConsumableTable`** follows the items: 45 × 12 bytes for battle items, stat-raising items,
  map items and key items, with a kind byte and a price.
- **`gAttackTable`** has 159 × 16 bytes for attacks and spells. Class attack ids are 1-based into
  it; entry 0 is "－".
- **`gElementNames`** lists the element names.
- **Class status immunities** are a separate asset, chunk `0x3188AE`: one byte per class with Poison,
  Sleep, Paralyze and Petrify bits. Undead and golems ignore Poison, Sleep and Paralyze, Ghosts and
  Stone/Baldr Golems everything, Gorgons Poison, Cockatrices Petrify.

Still unknown:
- item byte `+0x06` (a 0–11 tier) and the `+0x1A` bit-7 flag (on a few unique items);
- consumable use bits `0x2` and `0x4` (`0x1` = usable from the Organize screen);
- whether a positive resistance modifier helps or hurts. An element's own items lower it and raise
  the opposite element's.

Every byte of the eset files is now accounted for.

Other named data, not decoded yet: `scincsv*` (59, binary `(index, value)` tables despite the name),
`maizo*` (40, 埋蔵 "buried treasure"), and about 7,000 headerless LZ chunks. Many assets are reached
the same way: overlays load handles with `lui`/`ori` immediates and call `LoadAsset`, sometimes
through a 4-byte chunk holding the real handle.

## Game code

Game names come first from the developers' own debug strings (`AddHeap()`, `HIsAllocatedPointer()`,
`UnpackProc`, `SetDeadEnd()`), which use CamelCase and an `H` prefix for the heap module. Names inferred
from behaviour follow the same style and are marked `inferred` in `symbol_addrs.txt`. Overlay
functions need a `rom:` attribute there, because overlay VRAM addresses collide.

Known so far:
- **Boot:** `main` → `IdleThreadEntry` (idle thread) → `MainThreadEntry` (main game thread).
- **Heap:** `HMalloc`/`HMallocBack`/`HFree` over `gHeaps` (blocks carry a 0x20-byte header), with
  `AddHeap` and `HIsAllocatedPointer`.
- **ROM access:** `RomRead(rom, dst, size)` on top of the PI DMA `PiDmaRead`.
- **Decompression:** an embedded port of LHa for UNIX (`UnpackProc`, `get_header`, `extract_one`, and
  its `lh0`–`lh5` and `lzs`/`lz4`/`lz5` decoders). Assets are LHA archives.

## Libraries

Main links libultra, both audio libraries (`libaudio` and `n_audio`) and a libc/printf (`_Printf`,
`_Litob`, `_Ldtob`). Their symbols in `symbol_addrs.txt` come from
[n64sym](https://github.com/shygoo/n64sym)'s built-in signatures (run on the ROM with `-s -f splat`),
minus its auto-generated local labels and hits outside main. Names that occur twice, because the same
static is in two objects (e.g. `_getRate`), get an address suffix. `osInvalICache` isn't in n64sym's
database for this SDK version; it was identified by hand.

n64sym masks relocations, so tiny or wrapper-shaped functions can match game code. Eight such hits were
dropped after checking them against the asm (`__udiv_w_sdiv`, `__dummy`, `myfree`,
`__osGetActiveQueue`, `n_alSynRemovePlayer`, `n_alSeqpDelete`, and `osViExtendVStart` with its
`__additional_scanline`, which is a libmus setter). Treat a short n64sym name that sits
among game functions with suspicion.

Main's library code is split into its original objects. splat's padding-based splits miss objects
whose size is a multiple of 16. n64sym's local labels (`<obj>_text_<off>`, mapped to an address)
give `object start = address - off`; the smallest offset is used, since this SDK's objects drift
slightly from n64sym's. The rest follow libultra/libaudio's file layout: functions that live in
separate source files there (e.g. `osSendMesg` / `osSetEventMesg`) start new files here. Every such
start is 16-aligned, which is independent confirmation. Game code is still only split at padding, so
some game "files" may hold several objects.

Statics and other functions n64sym can't see (e.g. `__osPackReadData`, `osContInit`, `__scMain`,
`osInitialize`, `_Putfld`) were named by hand from their source file's function order and call
structure. They're listed at the end of `symbol_addrs.txt`.

## ROM layout (as currently understood)

| ROM range | Contents |
|---|---|
| `0x0000000`–`0x0000040` | Header (`NOBE`, entry `0x80070C00`) |
| `0x0000040`–`0x0001000` | IPL3 boot code |
| `0x0001000`–`0x0001060` | Entrypoint (clears BSS, jumps to `main` @ `0x8007F880`) |
| `0x0001060`–`0x002E570` | `main` .text, split into 265 files |
| `0x002E570`–`0x003E100` | `main` .data, per-file chunks |
| `0x003E100`–`0x003F1B0` | `main` .rodata, per-file chunks (BSS follows at `0x800AEDB0`, size `0x3AE70`) |
| `0x003F1B0`–`0x02B8BA0` | 46 code overlays (`ovl_<ROM>` segments), plus two data blobs at `0xDDF60` and `0x1C3300` |
| `0x02B8BA0`–`0x275DD0F` | Assets (see below) |
| `0x275DD0F`–`0x2800000` | ROM version string, then `0xFF` padding |

### Overlays

The game loads overlays with `func_8009DA50(rom_start, vram, size)` (a DMA wrapper), along with
`osInvalICache` / `osInvalDCache` and a `bzero` of the BSS.
19 overlays are described by a table in main's data at `0x800A83C0` (10 words each:
vram, ?, rom start/end, bss start/end, text start/end, data start/end). The rest are loaded with
literal arguments. `tools/find_overlays.py` recovers both and generates the splat segments:

```sh
python3 tools/find_overlays.py baserom/baserom.us.z64          # list loader call sites
python3 tools/find_overlays.py baserom/baserom.us.z64 --yaml   # emit splat segments
```

Many overlays share a VRAM address (twelve load at `0x80214F80`), so overlay symbols are named
`func_<VRAM>_ovl_<ROM>`.

Overlay text is split into files at the alignment padding that ends each source file (178 splits),
and each overlay's data, rodata and BSS are chunked per file like main's.
`tools/overlay_sections.py` does it for all overlays at once:

```sh
python3 tools/overlay_sections.py          # per overlay: rodata start, BSS range, and how each was found
python3 tools/overlay_sections.py --yaml   # rewrite the overlays' data/rodata/bss subsegments
```

- An overlay's data blob is every file's `.data`, then every file's `.rodata`, so the owner sequence
  restarts at the rodata start. With a single owner, it falls back to the trailing run of strings,
  jump tables and floats. Jump tables are always rodata, so rodata never starts after the first one.
- BSS ranges come from the descriptor table, else from the `bzero` right after the overlay's DMA load,
  else from the highest address the overlay's code references. BSS isn't in the ROM, so a wrong size
  can't break the match, only symbol layout.
- BSS chunking follows per-file statics until the owner first drops; from there on it's the
  linker's COMMON area (one `<ovl>_common` chunk, like main's `common`).
- Chunk boundaries must be 4-aligned, because of `SUBALIGN(4)`. `ld_align_section_vram_end: False`
  stops splat padding section ends to 16, since overlays' data/rodata boundaries often aren't.

## Next steps

1. Keep naming game functions, starting from the LHa port (match it against LHa for UNIX's source)
   and the callers of `HMalloc`/`RomRead`/`UnpackProc`.
2. Keep converting `asm/` functions into `src/` C. Functions whose only diff is a prologue sunk
   toward a call (e.g. `func_8007FE70`) don't match with this cc1; leave them `NON_MATCHING`.
   Before converting a file, check its data/rodata/BSS chunk boundaries by hand
   (`tools/section_chunks.py ... -v`); they're heuristic.
3. Decode the other data tables (`maizo`, `scincsv`, headerless chunks), and confirm the text
   control codes against the text engine. Callers of `LoadChunk` show what each handle is.
