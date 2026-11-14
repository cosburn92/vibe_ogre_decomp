# usage: python3 tools/try.py SEG FUNC variants.c   (variants separated by lines "//----"; keeps the closest)
import sys, subprocess, re
seg, func, vf = sys.argv[1:4]
src = 'src/%s.c' % seg
orig = open(src).read()
# locate function definition: line containing 'FUNC(' at col 0 that ends with '{', up to next '\n}\n'
m = re.search(r'^[^\n;]*\b%s\([^;]*?\{\n.*?^\}\n' % func, orig, re.S | re.M)
assert m, 'func not found'
vars_ = open(vf).read().split('//----\n')
S = 'tools/fdiff.sh'
best = None
for i, v in enumerate(vars_):
    new = orig[:m.start()] + v.strip('\n') + '\n' + orig[m.end():]
    open(src, 'w').write(new)
    subprocess.run('make build/ogrebattle64.us.z64 >/dev/null 2>&1', shell=True)
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
