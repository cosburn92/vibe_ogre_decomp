# usage: python3 tools/getfn.py SRC FUNC  - print FUNC's definition from SRC (for building tryrom variants)
import sys, re
s = open(sys.argv[1]).read()
m = re.search(r'^\w[^\n;]*\b%s\([^;]*?\{\n.*?^\}\n' % sys.argv[2], s, re.S | re.M)
sys.stdout.write(m.group(0))
