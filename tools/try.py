# usage: python3 tools/try.py SEG FUNC variants.c   (variants separated by lines "//----"; keeps the closest)
import sys, subprocess, re
seg, func, vf = sys.argv[1:4]
src = 'src/%s.c' % seg
orig = open(src).read()
# locate function definition: line containing 'FUNC(' at col 0 that ends with '{', up to next '\n}\n'
m = re.search(r'^[^\n;]*\b%s\([^;]*?\{\n.*?^\}\n' % func, orig, re.S | re.M)
assert m, 'func not found'
_before = orig[:m.start()]
_k = _before.rfind('#ifdef NON_MATCHING')
if _k >= 0 and '#endif' not in _before[_k:]:
    sys.exit('%s is inside #ifdef NON_MATCHING: the build uses the asm, so every variant would "match". Remove the guard first.' % func)
vars_ = open(vf).read().split('//----\n')
S = 'tools/fdiff.sh'
best = None
for i, v in enumerate(vars_):
    new = orig[:m.start()] + v.strip('\n') + '\n' + orig[m.end():]
    open(src, 'w').write(new)
    r = subprocess.run('make build/ogrebattle64.us.z64', shell=True, capture_output=True, text=True)
    if r.returncode != 0:
        err = [l for l in (r.stdout + r.stderr).splitlines() if 'rror' in l or '.i:' in l]
        print('variant', i, 'BUILD FAILED:', ' | '.join(err[:3]))
        continue
    out = subprocess.run('sh %s %s %s 400' % (S, seg, func), shell=True, capture_output=True, text=True).stdout
    # count diff lines ignoring relocation-only differences
    n = len([l for l in out.splitlines() if l.startswith('<')])
    print('variant', i, out.splitlines()[0] if out else '?', 'difflines', n)
    if best is None or n < best[0]:
        best = (n, i, new)
    if 'MATCH' in out.splitlines()[0]:
        break
open(src, 'w').write(best[2])
subprocess.run('make build/ogrebattle64.us.z64 >/dev/null 2>&1', shell=True)
print('kept variant', best[1])
