"""Export ogredecomp matched C to an OB64-Decomp checkout as ordinary text-only targets.

Starts from the standalone translation units convert.py produced (and LordlyCaliber's
build verified), keeps only functions whose start and extent equal one OB64-Decomp
assembly owner, renames our symbols to OB64-Decomp names (owner symbols, existing
shared-registry names, or new D_<VRAM>/func_<ROM> registry entries), drops unused
declarations, recompiles with the pinned toolchain, links against the registry
addresses, and requires the owner's exact retail bytes. Writes src/, the target
records, relocation contracts and registry additions.

usage: LC_TOOLS=<toolchain dir> ob64.py LORDLYCALIBER/native OB64-DECOMP [--write]
"""
import glob, hashlib, json, os, re, shutil, struct, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elf32 import Elf

R = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))).replace(os.sep, '/') + '/'
TOOLS = os.environ['LC_TOOLS'].rstrip('/') + '/'
WORK = R + 'build/ob64work/'
LC, UP = sys.argv[1].rstrip('/') + '/', sys.argv[2].rstrip('/') + '/'
WRITE = '--write' in sys.argv
ROM = open(R + 'baserom/baserom.us.z64', 'rb').read()
RELTYPE = {2: 'R_MIPS_32', 4: 'R_MIPS_26', 5: 'R_MIPS_HI16', 6: 'R_MIPS_LO16'}

# ---- OB64-Decomp model --------------------------------------------------------
owners = {}  # rom start -> (symbol, end, vram, asm path)
for f in glob.glob(UP + 'asm/**/*.s', recursive=True):
    t = open(f, errors='ignore').read(6000)
    m = re.search(r'z64 range: 0x([0-9A-Fa-f]+)\.\.0x([0-9A-Fa-f]+)', t)
    w = re.search(r'/\* 0x([0-9A-F]{8}) 0x([0-9A-F]{8}) 0x[0-9A-F]{8} \*/', t)
    if not m or not w or int(w.group(1), 16) != int(m.group(1), 16):
        continue
    owners[int(m.group(1), 16)] = (os.path.basename(f)[:-2], int(m.group(2), 16), int(w.group(2), 16),
                                   os.path.relpath(f, UP).replace(os.sep, '/'))
targets_cfg = json.load(open(UP + 'config/matching-c-targets.json'))['targets']
taken = {t['symbol'].lower() for t in targets_cfg}
_here = os.path.dirname(os.path.abspath(__file__))
# Functions OB64-Decomp asked to keep in assembly (entry-label / fixed-symbol conflicts, tail-admit)
EXCLUDE = {l.split('#')[0].strip().lower() for l in open(os.path.join(_here, 'ob64_exclude.txt'))} - {''}
ONLY = None  # optional: restrict to OB64 symbols listed in $OB64_ONLY (one per line)
if os.environ.get('OB64_ONLY'):
    ONLY = {l.strip().lower() for l in open(os.environ['OB64_ONLY']) if l.strip()}
linkage = json.load(open(UP + 'config/matching-c-linkage.json'))
registry = {s['name']: int(s['address'], 16) for s in linkage['symbols']}
by_addr = {}
for n, a in registry.items():
    by_addr.setdefault(a, []).append(n)
descriptors = [(int(d['fields']['romStart'], 16), int(d['fields']['romEnd'], 16), d['id'])
               for d in json.load(open(UP + 'config/overlays/us_rev0.json'))['descriptors']]
LINKED = set()
for _c in json.load(open(UP + 'asm/original/rev0/manifest.json'))['chunks']:
    LINKED |= {_p['name'] for _p in _c['parts']}
LINKED |= {t['symbol'] for t in targets_cfg}
PLACEHOLDER = re.compile(r'^(func|D)_[0-9A-Fa-f]{8}$|_(start|end)$')  # also skip linker boundary markers

# ---- ogredecomp model ------------------------------------------------------------
our_func_rom = {}
for f in glob.glob(R + 'asm/nonmatchings/*/*.s'):
    t = open(f, errors='ignore').read()
    if 'glabel' not in t:
        continue
    m = re.search(r'/\* ([0-9A-F]+) [0-9A-F]{8} [0-9A-F]{8} \*/', t[t.index('glabel'):])
    if m:
        our_func_rom[os.path.basename(f)[:-2]] = int(m.group(1), 16)
lc = json.load(open(LC + 'game/accepted/ogredecomp-owners.json'))['sources']


def sha(b):
    return hashlib.sha256(b).hexdigest().upper()


new_registry = {}


def their_name(name, addr):
    """OB64-Decomp spelling for one of our external symbols (None if unresolvable)."""
    overlay = '_ovl_' in name
    if name in our_func_rom:
        rom = our_func_rom[name]
        own = owners.get(rom)
        names = by_addr.get(addr, [])
        if not overlay:
            desc = [n for n in names if not PLACEHOLDER.match(n)]
            if desc: return sorted(desc)[0]
        exact = [n for n in names if n.lower() == ('func_%08x' % rom) or (own and n == own[0])]
        if exact: return exact[0]
        want = own[0] if own else 'func_%08X' % rom
    else:
        names = by_addr.get(addr, [])
        if not overlay:
            desc = [n for n in names if not PLACEHOLDER.match(n)]
            if desc: return sorted(desc)[0]
        want = 'D_%08X' % addr
        if want in names: return want
    have = registry.get(want, new_registry.get(want))
    if have is not None and have != addr:
        return None
    new_registry[want] = addr
    return want


def split_items(text):
    """Top-level items of a standalone TU (declarations / function definitions)."""
    items, i, n = [], 0, len(text)
    while i < n:
        while i < n and text[i] in ' \t\r\n': i += 1
        if i >= n: break
        start, depth, paren, body = i, 0, 0, False
        while i < n:
            c = text[i]
            if c in '"\'':
                q = c; i += 1
                while text[i] != q: i += 2 if text[i] == '\\' else 1
            elif c == '(': paren += 1
            elif c == ')': paren -= 1
            elif c == '{':
                if depth == 0 and paren == 0 and re.search(r'\)\s*$', text[start:i]): body = True
                depth += 1
            elif c == '}':
                depth -= 1
                if depth == 0 and body: i += 1; break
            elif c == ';' and depth == 0 and paren == 0: i += 1; break
            i += 1
        items.append((text[start:i], body))
    return items


def declared(item):
    t = item.strip()
    m = re.search(r'(\w+)\s*\((?:[^()]|\([^()]*\))*\)\s*(;|\{)', t)  # function
    if m and not t.startswith('typedef'): return m.group(1)
    m = re.search(r'(\w+)\s*(\[[^\]]*\]\s*)*;$', t)  # variable
    return m.group(1) if m else None


def item_names(text, body):
    """Identifiers an item defines (function, variable, typedef, tag, enum constants)."""
    t = text.strip()
    if body or not t.startswith(('typedef', 'struct', 'union', 'enum')):
        fp = re.match(r'(?:extern\s+)?[\w\s\*]*\(\s*\*\s*(\w+)', t)  # function-pointer objects
        if not body and fp:
            return {fp.group(1)}
        n = declared(t)
        return {n} if n else set()
    names = set(re.findall(r'\b(?:struct|union|enum)\s+(\w+)\s*\{', t))
    if t.startswith('typedef'):
        fp = re.search(r'\(\s*\*\s*(\w+)\s*\)\s*\(', t)
        if fp and '}' not in t:
            names.add(fp.group(1))
        else:
            tail = t[t.rindex('}') + 1:] if '}' in t else t[len('typedef'):]
            last = re.findall(r'(\w+)\s*(?:\[[^\]]*\]\s*)*(?=[,;])', tail)
            names |= set(last[-1:])
    for blk in re.findall(r'\benum\b[^{]*\{([^}]*)\}', t):
        names |= set(re.findall(r'(\w+)\s*(?:=[^,]*)?(?:,|$)', blk.strip()))
    return names


def reindent(text):
    out, depth = [], 0
    for line in text.split('\n'):
        s = line.strip()
        if not s:
            continue
        d = depth - (1 if s.startswith('}') else 0)
        out.append('    ' * max(d, 0) + s)
        depth += s.count('{') - s.count('}')
    return '\n'.join(out)


def prune(tu, target):
    """Keep only the target and the declarations/types it reaches."""
    items = split_items(tu)
    owner = {}
    for i, (t, b) in enumerate(items):
        for n in item_names(t, b):
            owner.setdefault(n, []).append(i)
    start = [i for i, (t, b) in enumerate(items) if b and declared(t[:t.index('{')] + '{') == target]
    keep, todo = set(start), list(start)
    while todo:
        i = todo.pop()
        for tok in set(re.findall(r'\b[A-Za-z_]\w*\b', items[i][0])):
            for j in owner.get(tok, []):
                if j not in keep:
                    keep.add(j)
                    todo.append(j)
    return '\n'.join(items[i][0] if items[i][1] else reindent(items[i][0])
                     for i in range(len(items)) if i in keep) + '\n'


def run(cwd, tool, args):
    return subprocess.run([TOOLS + tool] + args, cwd=cwd, capture_output=True, timeout=60)


def attempt(e, own):
    sym, end, vram, asm = own
    rom = [p for p in e['parts'] if p['code']][0]['start']
    tu = open(LC + e['source'], encoding='utf-8').read()
    rename = {e['name']: sym}
    for helper in re.findall(r'^extern inline [^(;]*?\b(\w+)\s*\(', tu, re.M):
        if helper in our_func_rom:
            own2 = owners.get(our_func_rom[helper])
            rename[helper] = own2[0] if own2 else 'func_%08X' % our_func_rom[helper]
    for n, a in e['bindings'].items():
        t = their_name(n, a)
        if t is None: return 'name', n
        rename[n] = t
    if len(set(rename.values())) != len(rename):
        return 'name', 'two symbols share one OB64 name'
    pat = re.compile(r'\b(%s)\b' % '|'.join(map(re.escape, sorted(rename, key=len, reverse=True))))
    tu = pat.sub(lambda m: rename[m.group(1)], tu)  # one pass: no chained renames
    tu = prune(tu, sym)
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
    for s in ('.data', '.bss', '.rodata', '.rdata', '.lit4', '.lit8', '.sdata', '.sbss'):
        if s in o.by_name and o.by_name[s][1]['size']: return 'section', s
    syms = o.symbols()
    text_syms = [s for s in syms if s['name'] and s['shndx'] == o.by_name['.text'][0]]
    if [s['name'] for s in text_syms if s['bind'] == 1] != [sym] or any(s['value'] for s in text_syms):
        return 'census', [s['name'] for s in text_syms]
    binds = {}
    for s in syms:
        if s['shndx'] == 0 and s['name']:
            a = registry.get(s['name'], new_registry.get(s['name']))
            if a is None: return 'unbound', s['name']
            binds[s['name']] = a
    relocs = []
    for off, si, typ in o.rels('.rel.text'):
        s = syms[si]
        name = s['name'] if s['name'] else o.sections[s['shndx']]['name']
        relocs.append(dict(offset='0x%08X' % off, type=RELTYPE[typ], symbol=name, section='.rel.text'))
    relocs.sort(key=lambda r: int(r['offset'], 16))  # OB64 requires numeric offset order
    struct.pack_into('>I', o.data, o.by_name['.text'][1]['header'] + 32, 4)
    open(d + 'link.o', 'wb').write(o.data)
    open(d + 'source.ld', 'w', newline='\n').write(''.join('%s = 0x%x;\n' % kv for kv in binds.items()) +
                                                   'SECTIONS {\n.text 0x%x : { *(.text) }\n}\n' % vram)
    r = run(d, 'mips-kmc-elf-ld.exe', ['-EB', '-m', 'elf32bmip', '-T', 'source.ld', '-o', 'source.elf', 'link.o'])
    if r.returncode: return 'ld', r.stderr.decode(errors='replace')[-300:]
    lt = Elf(open(d + 'source.elf', 'rb').read()).bytes_of('.text')
    want = ROM[rom:end]
    if lt[:len(want)] != want or any(lt[len(want):]) or len(lt) - len(want) >= 16:
        return 'bytes', 'compiled %d bytes vs owner %d bytes' % (len(lt), len(want))
    area = next(('src/overlays/descriptor_%02d' % i for a, b, i in descriptors if a <= rom < b),
                'src/boot' if '/boot/' in asm else 'src/lib')
    return 'ok', dict(symbol=sym, source='%s/%s.c' % (area, sym), tu=tu, relocs=relocs, rom=rom)


def main():
    jobs = []
    stat = {}
    for e in lc:
        if len(e['parts']) != 1:
            stat['has rodata'] = stat.get('has rodata', 0) + 1; continue
        p = e['parts'][0]
        own = owners.get(p['start'])
        if not own or own[0].lower() in taken or own[0].lower() in EXCLUDE or (ONLY is not None and own[0].lower() not in ONLY):
            stat['no owner / already upstream'] = stat.get('no owner / already upstream', 0) + 1; continue
        ours_end = p['start'] + p['size']
        if own[1] < ours_end:
            if any(ROM[own[1]:ours_end]):  # longer than the owner by real code
                stat['different extent'] = stat.get('different extent', 0) + 1; continue
        elif own[1] - ours_end not in range(0, 17) or any(ROM[ours_end:own[1]]):
            stat['different extent'] = stat.get('different extent', 0) + 1; continue
        # OB64-Decomp's reference-split comments use a naive overlay VRAM; place at the
        # runtime address our matching build links (its jal/HI16 words prove it)
        jobs.append((e, (own[0], own[1], p['address'], own[3])))
    # resolve names serially (registry additions must be deterministic), then compile in parallel
    res = []
    with ThreadPoolExecutor(8) as ex:
        res = list(ex.map(lambda j: attempt(*j), jobs))
    ok = [i for s, i in res if s == 'ok']
    fails = {}
    for (e, own), (s, i) in zip(jobs, res):
        if s != 'ok': fails.setdefault(s, []).append((e['name'], own[0], str(i)[:160]))
    json.dump(fails, open(WORK + 'fails.json', 'w'), indent=1)
    print('skipped', stat, '\ncandidates', len(jobs), 'ok', len(ok), {k: len(v) for k, v in fails.items()})
    # registry entries actually referenced by accepted objects
    used = {r['symbol'] for o in ok for r in o['relocs']}
    # names the linker already defines (assembly owners, targets) must not get absolute registry copies
    added = sorted((n, a) for n, a in new_registry.items() if n in used and n not in LINKED)
    print('new registry symbols', len(added))
    if not WRITE: return
    for o in sorted(ok, key=lambda o: o['rom']):
        p = UP + o['source']
        os.makedirs(os.path.dirname(p), exist_ok=True)
        open(p, 'w', newline='\n').write(o['tu'])
    # text insertion keeps the existing (mixed) line endings untouched
    p = UP + 'config/matching-c-targets.json'
    s = open(p, 'rb').read().decode('utf-8')
    k = s.rindex('}', 0, s.rindex(']'))
    add = ''.join(',\n    {\n      "symbol": "%s",\n      "source": "%s"\n    }' % (o['symbol'], o['source'])
                  for o in sorted(ok, key=lambda o: o['rom']))
    open(p, 'wb').write((s[:k + 1] + add + s[k + 1:]).encode('utf-8'))
    p = UP + 'config/matching-c-linkage.json'
    s = open(p, 'rb').read().decode('utf-8')
    ti = s.index('"targets": [')
    k = s.rindex('}', 0, s.rindex(']'))
    tadd = ''
    for o in sorted(ok, key=lambda o: o['rom']):
        rel = ',\n'.join('        {\n          "offset": "%(offset)s",\n          "type": "%(type)s",\n'
                         '          "symbol": "%(symbol)s",\n          "section": "%(section)s"\n        }' % r for r in o['relocs'])
        tadd += ',\n    {\n      "symbol": "%s",\n      "expectedRelocations": %s\n    }' % (
            o['symbol'], '[\n' + rel + '\n      ]' if rel else '[]')
    s = s[:k + 1] + tadd + s[k + 1:]
    k = s.rindex('}', 0, s.rindex(']', 0, ti))
    sadd = ''.join(',\n    {\n      "name": "%s",\n      "address": "0x%08X"\n    }' % na for na in added)
    s = s[:k + 1] + sadd + s[k + 1:]
    open(p, 'wb').write(s.encode('utf-8'))
    print('wrote', len(ok), 'targets')


if __name__ == '__main__':
    os.makedirs(WORK, exist_ok=True)
    main()
