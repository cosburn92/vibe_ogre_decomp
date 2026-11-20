"""Different-split exports for OB64-Decomp (companion to ob64.py).

* multi-owner: one ogredecomp function spans k>=2 contiguous OB64 owner rows
  -> config/matching-c-multi-owner.json + target + relocation contract.
* grouped:     one OB64 owner row holds k>=2 consecutive ogredecomp functions
  -> one translation unit (first function GLOBAL owner, the rest static) with a
     compilerTextFunctions contract.

Each candidate is compiled with the pinned toolchain, linked at its runtime address
against the shared registry, and must equal the retail bytes of the whole range.

usage: LC_TOOLS=<toolchain> ob64split.py LORDLYCALIBER/native OB64-DECOMP [--write]
"""
import bisect, glob, json, os, re, shutil, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ob64
from ob64 import Elf, ROM, R, UP, LC, WRITE, RELTYPE, run, prune, split_items, declared, their_name, our_func_rom, \
    registry, new_registry, descriptors, sha

WORK = R + 'build/ob64split/'
man = json.load(open(UP + 'asm/original/rev0/manifest.json'))
rows = sorted((int(p['romStart'], 16), int(p['romEndExclusive'], 16), p['name'], i + 1, p['file'])
              for i, p in enumerate(q for c in man['chunks'] for q in c['parts']))
row_starts = [r[0] for r in rows]
taken = {t['symbol'].lower() for t in json.load(open(UP + 'config/matching-c-targets.json'))['targets']}
lc = {[p for p in e['parts'] if p['code']][0]['start']: e for e in ob64.lc}
our_src = '\n'.join(open(f, errors='ignore').read() for f in glob.glob(R + 'src/*.c')) + \
    '\n'.join(open(f, errors='ignore').read() for f in glob.glob(R + 'asm/nonmatchings/*/*.s'))


def row_at(a):
    i = bisect.bisect_right(row_starts, a) - 1
    return rows[i] if i >= 0 and rows[i][0] <= a < rows[i][1] else None


def code(e):
    return [p for p in e['parts'] if p['code']][0]


def pad_ok(a, b):
    return 0 <= b - a < 16 and not any(ROM[a:b])


def area(rom, asm):
    return next(('src/overlays/descriptor_%02d' % i for a, b, i in descriptors if a <= rom < b),
                'src/boot' if '/boot/' in asm else 'src/lib')


def rename_tu(e, mapping):
    tu = open(LC + e['source'], encoding='utf-8').read()
    for helper in re.findall(r'^extern inline [^(;]*?\b(\w+)\s*\(', tu, re.M):
        if helper in our_func_rom and helper not in mapping:
            r = row_at(our_func_rom[helper])
            mapping[helper] = r[2] if r and r[0] == our_func_rom[helper] else 'func_%08X' % our_func_rom[helper]
    for n, a in e['bindings'].items():
        if n not in mapping:
            t = their_name(n, a)
            if t is None: return None
            mapping[n] = t
    pat = re.compile(r'\b(%s)\b' % '|'.join(map(re.escape, sorted(mapping, key=len, reverse=True))))
    return pat.sub(lambda m: mapping[m.group(1)], tu)


def merge(tus, names, statics):
    """One TU: union of declarations (first occurrence wins), then the bodies in order."""
    decls, seen, bodies = [], set(), []
    for tu, name in zip(tus, names):
        for text, body in split_items(prune(tu, name)):
            if body and declared(text[:text.index('{')] + '{') == name:
                bodies.append(('static ' if name in statics else '') + text.strip())
                continue
            key = re.sub(r'\s+', ' ', text.strip())
            dn = declared(text) if not text.lstrip().startswith(('typedef', 'struct', 'union', 'enum')) else None
            if key in seen or (dn in names): continue
            seen.add(key); decls.append(text.strip())
    protos = ['static ' + re.sub(r'\s*\{.*', '', b[len('static '):], flags=re.S).strip() + ';'
              for b in bodies if b.startswith('static ')]
    return '\n'.join(decls + protos + bodies) + '\n'


def check(sym, tu, rom, end, vram, local_names):
    d = WORK + sym + '/'
    shutil.rmtree(d, ignore_errors=True); os.makedirs(d)
    open(d + 'source.c', 'w', newline='\n').write(tu)
    for tool, args in [('cpp.exe', ['-P', '-undef', '-nostdinc', 'source.c', 'source.i']),
                       ('cc1.exe', ['-quiet', '-O2', '-meb', '-mips3', '-mgp32', '-mfp32', '-G', '0', '-fno-PIC',
                                    '-mno-abicalls', '-fno-builtin', '-funsigned-char', 'source.i', '-o', 'source.s']),
                       ('mips-kmc-elf-as.exe', ['-G', '0', '-mips3', '-mabi=32', '-force-n64align', '-EB', '-o', 'source.o', 'source.s'])]:
        r = run(d, tool, args)
        if r.returncode: return tool, r.stderr.decode(errors='replace')[-300:]
    o = Elf(open(d + 'source.o', 'rb').read())
    for s in ('.data', '.bss', '.rodata', '.rdata', '.lit4', '.lit8'):
        if s in o.by_name and o.by_name[s][1]['size']: return 'section', s
    syms = o.symbols()
    ti = o.by_name['.text'][0]
    fn = sorted((s['value'], s['name'], s['bind']) for s in syms if s['shndx'] == ti and s['name'] and s['type'] == 2)
    want = [(0, sym, 1)] + [(off, n, 0) for off, n in local_names]
    if fn != sorted(want): return 'census', fn
    binds = {}
    for s in syms:
        if s['shndx'] == 0 and s['name']:
            a = registry.get(s['name'], new_registry.get(s['name']))
            if a is None: return 'unbound', s['name']
            binds[s['name']] = a
    relocs = [dict(offset='0x%08X' % off, type=RELTYPE[t], symbol=syms[si]['name'] or o.sections[syms[si]['shndx']]['name'],
                   section='.rel.text') for off, si, t in o.rels('.rel.text')]
    relocs.sort(key=lambda r: int(r['offset'], 16))
    struct.pack_into('>I', o.data, o.by_name['.text'][1]['header'] + 32, 4)
    open(d + 'link.o', 'wb').write(o.data)
    open(d + 'source.ld', 'w', newline='\n').write(''.join('%s = 0x%x;\n' % kv for kv in binds.items()) +
                                                   'SECTIONS {\n.text 0x%x : { *(.text) }\n}\n' % vram)
    r = run(d, 'mips-kmc-elf-ld.exe', ['-EB', '-m', 'elf32bmip', '-T', 'source.ld', '-o', 'source.elf', 'link.o'])
    if r.returncode: return 'ld', r.stderr.decode(errors='replace')[-300:]
    lt = Elf(open(d + 'source.elf', 'rb').read()).bytes_of('.text')
    w = ROM[rom:end]
    if lt[:len(w)] != w or any(lt[len(w):]) or len(lt) - len(w) >= 16:
        return 'bytes', 'compiled %d vs %d' % (len(lt), len(w))
    return 'ok', relocs


def main():
    multi, groups, results = [], {}, []
    for a, e in sorted(lc.items()):
        if len(e['parts']) != 1: continue
        b = a + code(e)['size']
        r = row_at(a)
        if not r or r[2].lower() in taken: continue
        if r[0] == a and r[1] < b:
            k, end = [r], r[1]
            while end < b:
                n = row_at(end)
                if not n or n[0] != end: break
                k.append(n); end = n[1]
            if end >= b and pad_ok(b, end) and not any(x[2].lower() in taken for x in k)                     and not any(x[2].startswith('zero_fill_') for x in k)                     and not any(x[2].lower() in ob64.EXCLUDE for x in k)                     and (ob64.ONLY is None or k[0][2].lower() in ob64.ONLY):
                multi.append((e, k))
        elif r[0] != a or r[1] > b + 15:
            if r[2].lower() in ob64.EXCLUDE or (ob64.ONLY is not None and r[2].lower() not in ob64.ONLY):
                continue
            groups.setdefault(r, None)
    for r in list(groups):
        fns, x = [], r[0]
        while x < r[1] and x in lc and len(lc[x]['parts']) == 1:
            fns.append(lc[x]); x += code(lc[x])['size']
            while x < r[1] and x not in lc and ROM[x:x + 4] == b'\0\0\0\0': x += 4
        groups[r] = fns if x >= r[1] and len(fns) >= 2 else None
    groups = {r: f for r, f in groups.items() if f}
    print('multi-owner candidates', len(multi), 'grouped-owner candidates', len(groups))

    for e, k in multi:
        sym = k[0][2]
        tu = rename_tu(e, {e['name']: sym})
        if tu is None: results.append(('name', sym)); continue
        tu = prune(tu, sym)
        a = code(e)['start']; end = k[-1][1]
        st, info = check(sym, tu, a, end, code(e)['address'], [])
        results.append((st, sym))
        if st != 'ok': print('  multi', sym, st, str(info)[:120]); continue
        vram = code(e)['address']
        multi_rec = dict(symbol=sym, ownerRows=[x[3] for x in k], romStart='0x%08X' % a, romEndExclusive='0x%08X' % end,
                         vramStart='0x%08X' % vram, vramEndExclusive='0x%08X' % (vram + end - a),
                         expectedTextSha256=sha(ROM[a:end]))
        yield dict(kind='multi', symbol=sym, source='%s/%s.c' % (area(a, k[0][4]), sym), tu=tu, relocs=info, rom=a, multi=multi_rec)

    for r, fns in sorted(groups.items()):
        sym = r[2]
        locals_, mapping, tus, names = [], {}, [], []
        for i, f in enumerate(fns):
            off = code(f)['start'] - r[0]
            name = sym if i == 0 else 'func_%08X' % code(f)['start']
            mapping[f['name']] = name
            if i: locals_.append((off, name))
        ok = True
        for f in fns:
            tu = rename_tu(f, dict(mapping))
            if tu is None: ok = False; break
            tus.append(tu); names.append(mapping[f['name']])
        if not ok: results.append(('name', sym)); continue
        tu = merge(tus, names, set(n for _, n in locals_))
        st, info = check(sym, tu, r[0], r[1], code(fns[0])['address'], locals_)
        results.append((st, sym))
        if st != 'ok': print('  group', sym, st, str(info)[:160]); continue
        ctf, offs = [], [0] + [o for o, _ in locals_]
        for i, f in enumerate(fns):
            n = names[i]
            outside = len(re.findall(r'\b%s\b' % re.escape(f['name']), our_src)) > len(re.findall(r'\b%s\b' % re.escape(f['name']), ''.join(open(LC + g['source']).read() for g in fns)))
            nb = code(f)['size']
            if i == len(fns) - 1:  # the last function's size excludes trailing alignment zeros
                while nb > 4 and not any(ROM[code(f)['start'] + nb - 4:code(f)['start'] + nb]):
                    nb -= 4
            ctf.append(dict(symbol=n, offset='0x%08X' % offs[i], bytes=nb,
                            binding='GLOBAL' if i == 0 else 'LOCAL',
                            entryEvidence='owner' if i == 0 else ('fixed-address-call' if outside else 'internal-call-only')))
        yield dict(kind='group', symbol=sym, source='%s/%s.c' % (area(r[0], r[4]), sym), tu=tu, relocs=info, rom=r[0], ctf=ctf)


def insert_array_tail(s, array_key, text):
    i = s.index('"%s": [' % array_key)
    depth, j = 0, s.index('[', i)
    for k in range(j, len(s)):
        if s[k] == '[': depth += 1
        elif s[k] == ']':
            depth -= 1
            if depth == 0: break
    last = s.rindex('}', j, k)
    return s[:last + 1] + text + s[last + 1:]


if __name__ == '__main__':
    os.makedirs(WORK, exist_ok=True)
    out = list(main())
    print('accepted', len(out), {k: sum(1 for o in out if o['kind'] == k) for k in ('multi', 'group')})
    if WRITE and out:
        for o in out:
            p = UP + o['source']; os.makedirs(os.path.dirname(p), exist_ok=True)
            open(p, 'w', newline='\n').write(o['tu'])
        p = UP + 'config/matching-c-targets.json'
        s = open(p, 'rb').read().decode()
        s = insert_array_tail(s, 'targets', ''.join(',\n    {\n      "symbol": "%s",\n      "source": "%s"\n    }' % (o['symbol'], o['source']) for o in out))
        open(p, 'wb').write(s.encode())
        p = UP + 'config/matching-c-linkage.json'
        s = open(p, 'rb').read().decode()
        used = {r['symbol'] for o in out for r in o['relocs']}
        cur = {x['name'] for x in json.loads(s)['symbols']}
        add = sorted((n, a) for n, a in new_registry.items() if n in used and n not in cur and n not in ob64.LINKED)
        s = insert_array_tail(s, 'symbols', ''.join(',\n    {\n      "name": "%s",\n      "address": "0x%08X"\n    }' % na for na in add))
        def rel(o):
            return ',\n'.join('        {\n          "offset": "%(offset)s",\n          "type": "%(type)s",\n          "symbol": "%(symbol)s",\n          "section": "%(section)s"\n        }' % r for r in o['relocs'])
        def ent(o):
            t = '    {\n      "symbol": "%s",\n      "expectedRelocations": %s' % (o['symbol'], '[\n' + rel(o) + '\n      ]' if o['relocs'] else '[]')
            if o['kind'] == 'group':
                t += ',\n      "compilerTextFunctions": [\n' + ',\n'.join(
                    '        {\n          "symbol": "%(symbol)s",\n          "offset": "%(offset)s",\n          "bytes": %(bytes)d,\n          "binding": "%(binding)s",\n          "entryEvidence": "%(entryEvidence)s"\n        }' % c for c in o['ctf']) + '\n      ]'
            return t + '\n    }'
        s = insert_array_tail(s, 'targets', ''.join(',\n' + ent(o) for o in out))
        open(p, 'wb').write(s.encode())
        mo = [o for o in out if o['kind'] == 'multi']
        if mo:
            p = UP + 'config/matching-c-multi-owner.json'
            s = open(p, 'rb').read().decode()
            s = insert_array_tail(s, 'targets', ''.join(
                ',\n    {\n      "symbol": "%(symbol)s",\n      "ownerRows": [\n        %(rows)s\n      ],\n      "romStart": "%(romStart)s",\n      "romEndExclusive": "%(romEndExclusive)s",\n      "vramStart": "%(vramStart)s",\n      "vramEndExclusive": "%(vramEndExclusive)s",\n      "expectedTextSha256": "%(expectedTextSha256)s"\n    }'
                % dict(o['multi'], rows=',\n        '.join(map(str, o['multi']['ownerRows']))) for o in mo))
            open(p, 'wb').write(s.encode())
        print('wrote', len(out))
