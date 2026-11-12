#!/bin/sh
# usage: tools/romdiff.sh ROM_OFFSET SIZE   — disassembly diff of built ROM vs baserom
cd "$(dirname "$0")/.."
dis() { dd if=$1 bs=1 skip=$(($2)) count=$(($3)) 2>/dev/null > build/romdiff.bin
  mips-linux-gnu-objdump -D -EB -m mips:4300 -b binary --adjust-vma=$(($2)) build/romdiff.bin | tail -n +8 | cut -f1,3-; }
dis build/ogrebattle64.us.z64 $1 $2 > build/romdiff.ours
dis baserom/baserom.us.z64 $1 $2 > build/romdiff.theirs
diff build/romdiff.ours build/romdiff.theirs && echo "range matches"
