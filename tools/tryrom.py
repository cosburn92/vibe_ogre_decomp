# usage: python3 tools/tryrom.py SEG FUNC ROM SIZE variants.c  (variants split by "//----"; variant 0 = current code; keeps the best; scores with tools/cmpfn.sh so relocation shifts are ignored)
import sys, subprocess, re
seg, func, rom, size, vf = sys.argv[1:6]
src = 'src/%s.c' % seg
orig = open(src).read()
m = re.search(r'^[^\n;]*\b%s\([^;]*?\{\n.*?^\}\n' % func, orig, re.S | re.M)
best = None
for i, v in enumerate([orig[m.start():m.end()]] + open(vf).read().split('//----\n')):  # variant 0 = current
    new = orig[:m.start()] + v.strip('\n') + '\n' + orig[m.end():]
    open(src, 'w').write(new)
    r = subprocess.run('make build/ogrebattle64.us.z64', shell=True, capture_output=True, text=True)
    if r.returncode:
        print(i, 'BUILD FAIL'); continue
    out = subprocess.run('sh tools/cmpfn.sh %s %s' % (rom, size), shell=True, capture_output=True, text=True).stdout
    n = len([l for l in out.splitlines() if l.startswith('*')])
    print('variant', i, 'difflines', n)
    if best is None or n < best[0]: best = (n, i, new)
    if n == 0: break
open(src, 'w').write(best[2] if best else orig)
print('kept', best[1] if best else None)
