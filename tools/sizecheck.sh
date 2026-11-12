#!/bin/sh
# usage: tools/sizecheck.sh SEG   -- functions in src/SEG.c whose compiled size differs from the original
cd "$(dirname "$0")/.."
python3 tools/funcdiff.py src/$1.c | while read st n r rom s sz; do
  o=$(grep -m1 -o "nonmatching $n, 0x[0-9A-F]*" asm/nonmatchings/$1/$n.s 2>/dev/null | awk '{print $3}')
  [ -n "$o" ] && [ $((o)) -ne $((sz)) ] && echo "$n ours $sz orig $o"
done
