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
| `0x0001060`–`0x002E570` | `main` .text — split into ~228 files |
| `0x002E570`–`0x003F1B0` | `main` .data / .rodata (BSS `0x800AEDB0`, size `0x3AE70`) |
| `0x003F1B0`–`0x02B8BA0` | 46 code overlays (`ovl_<ROM>` segments), plus two data blobs at `0xDDF60` and `0x1C3300` |
| `0x02B8BA0`–`~0x2750000` | Assets: LHA archive members (828 headers, mostly `-lh5-`, some stored `-lh0-`), with filenames |
| `~0x2750000`–`0x2800000` | `0xFF` padding |

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
3. Extract the assets: walk the LHA member headers in the asset region and unpack them by name.
