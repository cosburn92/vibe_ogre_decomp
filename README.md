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
| `0x003F1B0`–`~0x02B0000` | **Unmapped.** Code-like data, likely many overlays at varying VRAM addresses |
| `~0x02C0000`–`~0x2750000` | High-entropy data: compressed or packed assets |
| `~0x2750000`–`0x2800000` | `0xFF` padding |

## Next steps

1. Find the overlay loader in `main` (DMA calls that use ROM addresses from a data table) and record each overlay's ROM and VRAM range as splat segments.
2. Identify libultra functions (osPiStartDma, osCreateThread, etc.) and name them in `symbol_addrs.txt`.
3. Choose a compiler. The game likely used KMC GCC 2.7.2, or IDO 5.3 if it doesn't, and should be confirmed by matching a small function. Then add C build rules and start converting `asm/` functions into `src/` C using `INCLUDE_ASM`.
4. Identify the asset compression format.
