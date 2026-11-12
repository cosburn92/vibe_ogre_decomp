#!/usr/bin/env python3
"""Recover overlay ROM/VRAM ranges from calls to the DMA loader.

Pattern used by the game (see main @ 0x80071F3C):
    osInvalICache(text_start, text_size)
    osInvalDCache(data_start, data_size)
    func_8009DA50(rom_start, vram, size)   ; DMA load
    bzero(bss_start, bss_size)
Constant args are recovered by simple linear propagation of lui/addiu/ori/addu/subu.
"""
import struct, sys

LOAD, ICACHE, DCACHE, BZERO = 0x8009DA50, 0x800900C0, 0x80090010, 0x80093380

def jal(t): return 0x0C000000 | ((t & 0x3FFFFFF) >> 2)

def s16(x): return (x ^ 0x8000) - 0x8000

def track(rom, start, end):
    """Execute [start, end) linearly, returning register constants (None = unknown)."""
    W = lambda o: struct.unpack('>I', rom[o:o+4])[0]
    r = {0: 0}
    for o in range(start, end, 4):
        x = W(o); op = x >> 26; rs = (x >> 21) & 31; rt = (x >> 16) & 31; rd = (x >> 11) & 15 | ((x >> 11) & 16)
        imm = x & 0xFFFF
        if op == 0xF: r[rt] = (imm << 16) & 0xFFFFFFFF
        elif op == 9: r[rt] = (r[rs] + s16(imm)) & 0xFFFFFFFF if r.get(rs) is not None else None
        elif op == 0xD: r[rt] = r[rs] | imm if r.get(rs) is not None else None
        elif op == 0 and (x & 0x3F) in (0x21, 0x23, 0x25):
            a, b = r.get(rs), r.get(rt); f = x & 0x3F
            rd = (x >> 11) & 31
            r[rd] = None if a is None or b is None else ((a + b) if f == 0x21 else (a - b) if f == 0x23 else (a | b)) & 0xFFFFFFFF
        elif op == 0 and (x & 0x3F) == 9: pass
        elif op in (0x20, 0x21, 0x23, 0x24, 0x25, 0x0F) or op == 0: 
            if op == 0: r[(x >> 11) & 31] = None
            else: r[rt] = None
        elif op in (8, 0xA, 0xB, 0xC, 0xE): r[rt] = None
        elif op == 3:  # jal clobbers temporaries/args except in delay slot (handled by caller)
            pass
        r[0] = 0
    return r

def args_at(rom, call, back=48):
    r = track(rom, max(call - back * 4, 0), call + 8)  # include delay slot
    return r.get(4), r.get(5), r.get(6)

def main():
    rom = open(sys.argv[1], 'rb').read()
    W = lambda o: struct.unpack('>I', rom[o:o+4])[0]
    J = {jal(t): n for t, n in ((LOAD, 'load'), (ICACHE, 'icache'), (DCACHE, 'dcache'), (BZERO, 'bzero'))}
    calls = [(o, J[W(o)]) for o in range(0x1000, 0x2C0000, 4) if W(o) in J]
    for o, kind in calls:
        a0, a1, a2 = args_at(rom, o)
        f = lambda v: f"{v:08X}" if v is not None else "????????"
        print(f"{o:06X} {kind:6s} a0={f(a0)} a1={f(a1)} a2={f(a2)}")

if __name__ == "__main__" and len(sys.argv) == 2:
    main()


def parse_table(rom, start=0x387C0):
    """Overlay descriptor table in main .data (0x800A83C0 in RAM).

    struct { u32 vram, unk_04, rom_start, rom_end, bss_start, bss_end,
                 text_start, text_end, data_start, data_end; }
    """
    W = lambda o: struct.unpack('>I', rom[o:o+4])[0]
    out = []
    o = start
    while True:
        e = [W(o + i * 4) for i in range(10)]
        vram, _, rs, re_, bs, be, ts, te, ds, de = e
        if not (vram >> 24 == 0x80 and rs < re_ < 0x2800000 and ts == vram and de - ts == re_ - rs):
            break
        out.append(dict(rom=rs, rom_end=re_, vram=vram, text_end=te, data_end=de, bss_end=be, entry=o))
        o += 0x28
    return out


def dma_overlays(rom):
    """Overlays loaded by literal-argument calls, sized via the adjacent icache call."""
    W = lambda o: struct.unpack('>I', rom[o:o+4])[0]
    J = {jal(t): n for t, n in ((LOAD, 'load'), (ICACHE, 'icache'))}
    calls = [(o, J[W(o)]) for o in range(0x1000, 0x2C0000, 4) if W(o) in J]
    out = {}
    for i, (o, kind) in enumerate(calls):
        if kind != 'load':
            continue
        a0, a1, a2 = args_at(rom, o)
        if None in (a0, a1, a2) or a2 < 0x100 or a1 >> 24 != 0x80:
            continue
        for p, k in calls[max(0, i - 4):i + 4]:
            if k == 'icache' and abs(p - o) < 0x80:
                t0, t1, _ = args_at(rom, p)
                if t0 == a1 and t1 is not None and t1 <= a2:
                    out[a0] = dict(rom=a0, rom_end=a0 + a2, vram=a1, text_end=a1 + t1, data_end=a1 + a2)
                    break
    return out


def all_overlays(rom):
    ovl = dma_overlays(rom)
    for e in parse_table(rom):
        ovl[e['rom']] = e
    for e in ovl.values():
        assert e['data_end'] - e['vram'] == e['rom_end'] - e['rom'], hex(e['rom'])
    return [ovl[k] for k in sorted(ovl)]


def yaml_segments(rom, start=0x3F1B0, assets_end=0x2800000):
    lines, pos = [], start
    def binseg(a):
        lines.extend([f"  - name: bin_{a:06X}", "    type: bin", f"    start: 0x{a:X}", ""])
    for e in all_overlays(rom):
        if e['rom'] > pos:
            binseg(pos)
        name = f"ovl_{e['rom']:06X}"
        text_rom = e['rom'] + (e['text_end'] - e['vram'])
        lines += [f"  - name: {name}", "    type: code", f"    start: 0x{e['rom']:X}",
                  f"    vram: 0x{e['vram']:08X}", "    exclusive_ram_id: overlay",
                  "    symbol_name_format: $VRAM_$SEG", "    symbol_name_format_no_rom: $VRAM_$SEG",
                  "    subsegments:", f"      - [0x{e['rom']:X}, asm]"]
        if text_rom < e['rom_end']:
            lines.append(f"      - [0x{text_rom:X}, data]")
        lines.append("")
        pos = e['rom_end']
    binseg(pos)
    lines.append(f"  - [0x{assets_end:X}]")
    return "\n".join(lines)


if __name__ == '__main__' and len(sys.argv) > 2 and sys.argv[2] == '--yaml':
    print(yaml_segments(open(sys.argv[1], 'rb').read()))
