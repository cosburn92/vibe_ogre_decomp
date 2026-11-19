"""Turn ogredecomp's matched C functions (absent from LordlyCaliber) into standalone
translation units in LordlyCaliber's accepted-source shape, compile each with
LordlyCaliber's pinned toolchain and flags, link at the original address, and keep
only those whose bytes equal the retail ROM. Writes sources + ogredecomp-owners.json.

usage: LC_TOOLS=<toolchain dir> convert.py LORDLYCALIBER/native [SEG ...]
(run after `make`; needs build/ogrebattle64.elf and build/src/*.i)
"""
import bisect, glob, hashlib, json, os, re, struct, subprocess, sys, shutil
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elf32 import Elf

R = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))).replace(os.sep, '/') + '/'
TOOLS = os.environ['LC_TOOLS'].rstrip('/') + '/'  # extracted native/rebuild/n64-toolchain-windows.zip
WORK = R + 'build/lcwork/'
S = WORK
OUT = sys.argv[1]
ONLY = set(sys.argv[2:])
ROM = open(R + 'baserom/baserom.us.z64', 'rb').read()


def sha(b):
    return hashlib.sha256(b).hexdigest().upper()


# ---- their accepted ranges -------------------------------------------------
ro = json.load(open(OUT + '/game/accepted/rom-owners.json'))
lc = sorted((p['start'], p['start'] + p['size']) for s in ro['sources'] for p in s['parts'] if p.get('code'))
lcs = [a for a, b in lc]


def in_lc(rom):
    i = bisect.bisect_right(lcs, rom) - 1
    return i >= 0 and lc[i][0] <= rom < lc[i][1]


# ---- our symbols -----------------------------------------------------------
ours = Elf(open(R + 'build/ogrebattle64.elf', 'rb').read())
symval = {}
for s in ours.symbols():
    if not s['name'] or s['shndx'] == 0:
        continue
    symval.setdefault(s['name'], set()).add(s['value'])
symval = {k: v.pop() for k, v in symval.items() if len(v) == 1}

# ---- targets: functions in matched C, not in LordlyCaliber -----------------
srcs = {os.path.basename(f)[:-2]: open(f, errors='ignore').read() for f in glob.glob(R + 'src/*.c')}
targets = {}  # seg -> [(name, rom, size)]
for f in glob.glob(R + 'asm/nonmatchings/*/*.s'):
    seg = os.path.basename(os.path.dirname(f)); n = os.path.basename(f)[:-2]
    if ONLY and seg not in ONLY:
        continue
    s = srcs.get(seg)
    if s is None or 'INCLUDE_ASM("asm/nonmatchings/%s", %s);' % (seg, n) in s:
        continue
    t = open(f, errors='ignore').read()
    if 'glabel' not in t:
        continue
    t = t[t.index('glabel'):]  # skip rodata (jump tables, literals) listed before the code
    m = re.search(r'/\* ([0-9A-F]+) [0-9A-F]{8} [0-9A-F]{8} \*/', t)
    if not m:
        continue
    rom = int(m.group(1), 16)
    if in_lc(rom):
        continue
    size = 4 * len(re.findall(r'/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/', t))
    targets.setdefault(seg, []).append((n, rom, size))


# ---- top-level splitter for preprocessed C ---------------------------------
def split_items(text):
    items, i, n = [], 0, len(text)
    while i < n:
        while i < n and text[i] in ' \t\r\n':
            i += 1
        if i >= n:
            break
        if text[i] == '#':  # line directives / pragmas
            j = text.find('\n', i); i = n if j < 0 else j + 1
            continue
        start, depth, paren, body = i, 0, 0, False
        while i < n:
            c = text[i]
            if c in '"\'':
                q = c; i += 1
                while text[i] != q:
                    i += 2 if text[i] == '\\' else 1
            elif c == '(':
                paren += 1
            elif c == ')':
                paren -= 1
            elif c == '{':
                if depth == 0 and paren == 0 and re.search(r'\)\s*$', text[start:i]):
                    body = True
                depth += 1
            elif c == '}':
                depth -= 1
                if depth == 0 and body:
                    i += 1; break
            elif c == ';' and depth == 0 and paren == 0:
                i += 1; break
            i += 1
        items.append((text[start:i], body))
    return items


def func_name(header):
    # name of the function being declared/defined: identifier before the
    # parameter list's '(' at nesting level 0 (handles pointer returns)
    m = re.search(r'(\w+)\s*\((?:[^()]|\([^()]*\))*\)\s*$', header.strip().rstrip(';').rstrip('{').strip())
    return m.group(1) if m else None


def strip_static(t):
    return re.sub(r'^\s*static\s+', '', t)


def to_extern(item):
    """Variable definition -> extern declaration (no storage emitted)."""
    t = strip_static(item.strip().rstrip(';'))
    depth = paren = 0
    for k, c in enumerate(t):
        if c in '({[':
            depth += 1
        elif c in ')}]':
            depth -= 1
        elif c == '=' and depth == 0:
            t = t[:k].rstrip(); break
    if not t.startswith('extern'):
        t = 'extern ' + t
    return t + ';'


def fix_char(t):
    # ogredecomp builds with signed plain char; LordlyCaliber passes -funsigned-char
    t = re.sub(r'(?<!signed )(?<!unsigned )\bchar\b', 'signed char', t)
    # ogredecomp compiles fabs/fabsf as builtins; -fno-builtin keeps the explicit spelling
    return re.sub(r'(?<![\w.])(fabsf?)\s*\(', r'__builtin_\1(', re.sub(r'^(?:extern\s+)?(?:f32|f64|float|double)\s+fabsf?\s*\([^;{]*\)\s*;\s*$', '', t, flags=re.M))


def build_tu(items, target):
    out = []
    for text, body in items:
        st = text.lstrip()
        if st.startswith('__asm__') or st.startswith('asm'):
            continue
        if body:
            header = text[:text.index('{')]
            name = func_name(header)
            if name == target:
                out.append(strip_static(text))
            elif re.search(r'\binline\b', header):
                # inline-only: never emitted beside the target; calls that are not
                # inlined bind to the original function's address
                out.append('extern inline ' + re.sub(r'\b(static|inline|extern)\s+', '', text.lstrip(), count=2))
            else:
                out.append(strip_static(header.rstrip()) + ';')
            continue
        if st.startswith(('typedef', 'extern')) or re.match(r'(struct|union|enum)\s+\w*\s*\{[\s\S]*\}\s*;$', st) \
                or re.match(r'(struct|union|enum)\s+\w+\s*;$', st):
            out.append(text if not st.startswith('extern') else text)
            continue
        # prototype?  a top-level parameter list right before ';'
        if func_name(st) and not re.search(r'=', st.split('(')[0]):
            out.append(strip_static(text))
            continue
        out.append(to_extern(text))
    return fix_char('\n'.join(out) + '\n')


# ---- compile / link exactly like native/tools/build-accepted-rom.cjs -------
def run(cwd, tool, args):
    return subprocess.run([TOOLS + tool] + args, cwd=cwd, capture_output=True, timeout=60)


def patch_obj(path, sections):
    e = Elf(open(path, 'rb').read())
    for name in sections:
        _, s = e.by_name[name]
        struct.pack_into('>I', e.data, s['header'] + 32, 4)
        if name == '.rodata':
            struct.pack_into('>I', e.data, s['header'] + 8, 2)
    open(path, 'wb').write(e.data)


def sext16(x):
    return x - 0x10000 if x & 0x8000 else x


def attempt(seg, name, rom, size, tu):
    d = WORK + seg + '/' + name + '/'
    shutil.rmtree(d, ignore_errors=True); os.makedirs(d + 'inputs/src/' + seg)
    rel = 'src/%s/%s.c' % (seg, name)
    open(d + 'inputs/' + rel, 'w', newline='\n').write(tu)
    r = run(d, 'cpp.exe', ['-P', '-undef', '-nostdinc', '-D__mips=3', '-D__mips__', '-D_MIPSEB', '-D__MIPSEB__',
                           '-I', d + 'inputs/include', '-I', d + 'inputs', d + 'inputs/' + rel, 'source.i'])
    if r.returncode: return 'cpp', r.stderr.decode(errors='replace')[-300:]
    r = run(d, 'cc1.exe', ['-quiet', '-O2', '-meb', '-mips3', '-mgp32', '-mfp32', '-G', '0', '-fno-PIC',
                           '-mno-abicalls', '-fno-builtin', '-funsigned-char', 'source.i', '-o', 'source.s'])
    if r.returncode: return 'cc1', r.stderr.decode(errors='replace')[-300:]
    r = run(d, 'mips-kmc-elf-as.exe', ['-G', '0', '-mips3', '-mabi=32', '-force-n64align', '-EB', '-o', 'source.o', 'source.s'])
    if r.returncode: return 'as', r.stderr.decode(errors='replace')[-300:]
    o = Elf(open(d + 'source.o', 'rb').read())
    for bad in ('.data', '.bss', '.sdata', '.sbss', '.rdata', '.lit4', '.lit8'):
        if bad in o.by_name and o.by_name[bad][1]['size']:
            return 'section', bad
    vram = symval.get(name)
    if vram is None: return 'nosym', name
    delta = vram - rom
    syms = o.symbols()
    sections = {'.text': vram}
    rod_i = o.by_name.get('.rodata', (None, None))[0]
    rod_size = o.by_name['.rodata'][1]['size'] if rod_i is not None else 0
    text = o.bytes_of('.text')
    if rod_size:
        rels = o.rels('.rel.text'); base = None
        for k, (off, si, typ) in enumerate(rels):
            if typ != 5 or syms[si]['shndx'] != rod_i: continue
            for off2, si2, typ2 in rels[k + 1:]:
                if typ2 == 6 and si2 == si:
                    tu_t = syms[si]['value'] + ((struct.unpack_from('>I', text, off)[0] & 0xFFFF) << 16) \
                        + sext16(struct.unpack_from('>I', text, off2)[0] & 0xFFFF)
                    a = ((struct.unpack_from('>I', ROM, rom + off)[0] & 0xFFFF) << 16) \
                        + sext16(struct.unpack_from('>I', ROM, rom + off2)[0] & 0xFFFF)
                    base = (a - tu_t) & 0xFFFFFFFF
                    break
            if base is not None: break
        if base is None: return 'rodata', 'no text reference'
        sections['.rodata'] = base
    bindings = {}
    for s in syms:
        if s['shndx'] == 0 and s['name']:
            if s['name'] not in symval: return 'unbound', s['name']
            bindings[s['name']] = symval[s['name']]
    patch_obj(d + 'source.o', sections)
    os.replace(d + 'source.o', d + 'source-link.o')
    script = ''.join('%s = 0x%x;\n' % kv for kv in bindings.items()) + '\nSECTIONS {\n' + \
        ''.join('%s 0x%x : { *(%s) }\n' % (k, v, k) for k, v in sections.items()) + '}\n'
    open(d + 'source.ld', 'w', newline='\n').write(script)
    r = run(d, 'mips-kmc-elf-ld.exe', ['-EB', '-m', 'elf32bmip', '-T', 'source.ld', '-o', 'source.elf', 'source-link.o'])
    if r.returncode: return 'ld', r.stderr.decode(errors='replace')[-300:]
    L = Elf(open(d + 'source.elf', 'rb').read())
    lt = L.bytes_of('.text')
    if len(lt) < size and not any(ROM[rom + len(lt):rom + size]):
        size = len(lt)  # trailing alignment nops belong to no function
    tsym = [x for x in L.symbols() if x['name'] == name]
    if not tsym or tsym[0]['value'] != vram:
        return 'place', 'target not first in .text'
    if len(lt) < size or lt[:size] != ROM[rom:rom + size]:
        diff = sum(1 for k in range(0, min(size, len(lt)), 4) if lt[k:k + 4] != ROM[rom + k:rom + k + 4])
        return 'text', '%d words differ' % diff
    parts = [dict(section='.text', offset=0, start=rom, address=vram, size=size, sha256=sha(lt[:size]), code=1)]
    if rod_size:
        lr = L.bytes_of('.rodata'); rs = sections['.rodata'] - delta
        n = len(lr)
        while n > 0 and lr[:n] != ROM[rs:rs + n] and n > len(lr) - 16 and lr[n - 1] == 0:
            n -= 1
        if lr[:n] != ROM[rs:rs + n] or n == 0:
            return 'rodata', 'bytes differ'
        parts.append(dict(section='.rodata', offset=0, start=rs, address=sections['.rodata'], size=n, sha256=sha(lr[:n]), code=0))
    for name2 in ('.data', '.bss', '.rdata', '.lit4', '.lit8') + (() if rod_size else ('.rodata',)):
        if name2 in L.by_name and L.by_name[name2][1]['size']:
            return 'section', name2
    return 'ok', dict(name=name, rel=rel, tu=tu, vram=vram, bindings=bindings, sections=sections, parts=parts)


def main():
    jobs, cache, seen = [], {}, set()

    def items_of(seg):
        if seg not in cache:
            ipath = R + 'build/src/%s.i' % seg
            cache[seg] = split_items(open(ipath, errors='replace').read()) if os.path.exists(ipath) else []
        return cache[seg]

    def defines(seg, name):
        return any(b and func_name(t[:t.index('{')]) == name for t, b in items_of(seg))

    for seg, fs in sorted(targets.items()):
        for name, rom, size in fs:
            home = seg
            if not defines(seg, name):  # asm split into one segment, C written in another
                home = next((g for g in sorted(srcs) if re.search(r'^[^;\n]*\b%s\([^;]*\)\s*\{' % name, srcs[g], re.M)
                             and defines(g, name)), None)
                if home is None: continue
            if rom in seen: continue
            seen.add(rom)
            jobs.append((home, name, rom, size, build_tu(items_of(home), name)))
    print('candidates', len(jobs), flush=True)
    with ThreadPoolExecutor(8) as ex:
        res = list(ex.map(lambda j: (j, attempt(*j)), jobs))
    ok, fails = [], {}
    for (seg, name, rom, size, tu), (st, info) in res:
        if st == 'ok': ok.append(info)
        else: fails.setdefault(st, []).append((seg, name, str(info)[:200]))
    json.dump({k: v for k, v in fails.items()}, open(S + 'lcfails.json', 'w'), indent=1)
    print('ok', len(ok), {k: len(v) for k, v in fails.items()}, flush=True)
    # write sources and manifest
    root = OUT + '/game/accepted/ogredecomp/'
    entries = []
    for e in sorted(ok, key=lambda e: e['rel']):
        p = root + e['rel']
        os.makedirs(os.path.dirname(p), exist_ok=True)
        open(p, 'w', newline='\n').write(e['tu'])
        entries.append(dict(name=e['name'], source='game/accepted/ogredecomp/' + e['rel'], sourcePath=e['rel'],
                            sourceSha256=sha(e['tu'].encode()), headers=[], address=e['vram'],
                            bindings=e['bindings'], sections=e['sections'], projections=[], parts=e['parts'],
                            targets=[e['name']]))
    json.dump(dict(schemaVersion=1, generator='ogredecomp tools/lcconv/convert.py', upstream='https://github.com/cosburn92/vibe_ogre_decomp',
                   counts=dict(functions=len(entries), producerSources=len(entries)), sources=entries),
              open(OUT + '/game/accepted/ogredecomp-owners.json', 'w', newline='\n'), indent=2)


main()
