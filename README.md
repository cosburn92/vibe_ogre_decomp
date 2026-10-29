# Ogre Battle 64 decompilation

Work-in-progress decompilation of *Ogre Battle 64: Person of Lordly Caliber* (USA).

No game content is included in this repository. You must supply your own ROM.

| Version | File | SHA-1 |
|---|---|---|
| US | `baserom/baserom.us.z64` | `9cd0cfb50b883edb068e0c30d213193b9cf89895` |

## Setup (Windows + WSL Ubuntu, or Linux)

```sh
sudo apt install -y binutils-mips-linux-gnu make python3-pip
pip install "splat64[mips]"
make extract   # split the ROM into asm/ and assets/
make           # rebuild and verify the ROM matches
```

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

1. Split the overlays' data sections into data and rodata, and add BSS segments.
2. Identify libultra functions (osPiStartDma, osCreateThread, etc.) and name them in `symbol_addrs.txt`.
3. Choose a compiler. The game likely used KMC GCC 2.7.2, or IDO 5.3 if it doesn't, and should be confirmed by matching a small function. Then add C build rules and start converting `asm/` functions into `src/` C using `INCLUDE_ASM`.
4. Identify the asset compression format.
