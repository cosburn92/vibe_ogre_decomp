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

### Rodata

Each source file's `.rodata` (strings, jump tables, float/double constants) sits in one chunk, and
the chunks appear in the same order as the files' `.text`. `tools/rodata_chunks.py 3E100 3F1B0`
assigns each chunk to the text file that references it and emits the yaml subsegments. Once a file is
C, its chunk becomes `.rodata` so it's linked from the C object; for `INCLUDE_ASM` functions splat
migrates the constants into the function's `.s`. The linker script uses `SUBALIGN(4)` because every
input already carries its own padding.

## ROM layout (as currently understood)

| ROM range | Contents |
|---|---|
| `0x0000000`–`0x0000040` | Header (`NOBE`, entry `0x80070C00`) |
| `0x0000040`–`0x0001000` | IPL3 boot code |
| `0x0001000`–`0x0001060` | Entrypoint (clears BSS, jumps to `main` @ `0x8007F880`) |
| `0x0001060`–`0x002E570` | `main` .text — split into ~228 files |
| `0x002E570`–`0x003F1B0` | `main` .data / .rodata (BSS `0x800AEDB0`, size `0x3AE70`) |
| `0x003F1B0`–`0x02B8BA0` | 46 code overlays (`ovl_<ROM>` segments), plus two data blobs at `0xDDF60` and `0x1C3300` |
| `0x02B8BA0`–`~0x2750000` | High-entropy data: compressed or packed assets |
| `~0x2750000`–`0x2800000` | `0xFF` padding |

### Overlays

The game loads overlays with `func_8009DA50(rom_start, vram, size)` (a DMA wrapper), along with
icache/dcache invalidation (`func_800900C0` / `func_80090010`) and a BSS clear (`func_80093380`).
19 overlays are described by a table in main's data at `0x800A83C0` (10 words each:
vram, ?, rom start/end, bss start/end, text start/end, data start/end). The rest are loaded with
literal arguments. `tools/find_overlays.py` recovers both and generates the splat segments:

```sh
python3 tools/find_overlays.py baserom/baserom.us.z64          # list loader call sites
python3 tools/find_overlays.py baserom/baserom.us.z64 --yaml   # emit splat segments
```

Many overlays share a VRAM address (twelve load at `0x80214F80`), so overlay symbols are named
`func_<VRAM>_ovl_<ROM>`.

## Next steps

1. Split main's `.data` per file the same way, and the overlays' data sections into data/rodata/BSS.
2. Identify libultra functions (osPiStartDma, osCreateThread, etc.) and name them in `symbol_addrs.txt`.
3. Keep converting `asm/` functions into `src/` C. Functions whose only diff is a prologue sunk
   toward a call (e.g. `func_8007FE70`) don't match with this cc1; leave them `NON_MATCHING`.
4. Identify the asset compression format.
