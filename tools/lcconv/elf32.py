"""Minimal big-endian ELF32 reader: sections, symbols, REL relocations."""
import struct


class Elf:
    def __init__(self, data):
        self.data = bytearray(data)
        shoff, = struct.unpack_from('>I', data, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from('>HHH', data, 0x2E)
        self.sections = []
        for i in range(shnum):
            h = shoff + i * shentsize
            f = struct.unpack_from('>10I', data, h)
            self.sections.append(dict(header=h, name_off=f[0], type=f[1], flags=f[2], addr=f[3],
                                      offset=f[4], size=f[5], link=f[6], info=f[7], align=f[8], entsize=f[9]))
        strtab = self.sections[shstrndx]
        for s in self.sections:
            s['name'] = self._str(strtab, s['name_off'])
        self.by_name = {s['name']: (i, s) for i, s in enumerate(self.sections)}

    def _str(self, sec, off):
        b = self.data[sec['offset'] + off:]
        return bytes(b[:b.index(0)]).decode('latin1')

    def bytes_of(self, name):
        i, s = self.by_name[name]
        if s['type'] == 8:  # NOBITS
            return bytes(s['size'])
        return bytes(self.data[s['offset']:s['offset'] + s['size']])

    def symbols(self):
        if '.symtab' not in self.by_name:
            return []
        _, st = self.by_name['.symtab']
        strs = self.sections[st['link']]
        out = []
        for o in range(st['offset'], st['offset'] + st['size'], 16):
            name, value, size, info, other, shndx = struct.unpack_from('>IIIBBH', self.data, o)
            out.append(dict(name=self._str(strs, name), value=value, size=size,
                            bind=info >> 4, type=info & 15, shndx=shndx))
        return out

    def rels(self, name):
        if name not in self.by_name:
            return []
        _, s = self.by_name[name]
        out = []
        for o in range(s['offset'], s['offset'] + s['size'], 8):
            off, info = struct.unpack_from('>II', self.data, o)
            out.append((off, info >> 8, info & 255))
        return out
