"""Print a MIPS binary as hex words with j/jal targets zeroed (they're relocations in test.o)."""
import sys

d = open(sys.argv[1], "rb").read()
for i in range(0, len(d) - 3, 4):
    w = int.from_bytes(d[i:i + 4], "big")
    if w >> 26 in (2, 3):
        w &= 0xFC000000
    print(f"{w:08X}")
