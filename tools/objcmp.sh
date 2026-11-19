#!/bin/sh
# usage: tools/objcmp.sh SEG FUNC ORIG_ROM ORIG_SIZE
# Side-by-side of FUNC as compiled in build/src/SEG.o against the baserom bytes at ORIG_ROM,
# so functions can be compared even when earlier code in the file shifted them.
# Lines differing beyond relocation fields are marked with '*'.
cd "$(dirname "$0")/.."
SEG=$1; FUNC=$2; ROM=$3; SIZE=$4
OFF=$(mips-linux-gnu-nm build/src/$SEG.o | awk -v f=$FUNC '$3==f{print $1}')
mips-linux-gnu-objcopy -O binary --only-section=.text build/src/$SEG.o build/objcmp.text
dis() { dd if=$1 bs=1 skip=$(($2)) count=$(($3)) 2>/dev/null > build/objcmp.bin
  mips-linux-gnu-objdump -D -EB -m mips:4300 -b binary build/objcmp.bin | tail -n +8 | cut -f1,3-; }
dis build/objcmp.text 0x$OFF $SIZE > build/romdiff.ours
dis baserom/baserom.us.z64 $ROM $SIZE > build/romdiff.theirs
paste -d'|' build/romdiff.ours build/romdiff.theirs | awk -F'|' '{a=$1; b=$2; sub(/^ *[0-9a-f]+:\t/,"",a); sub(/^ *[0-9a-f]+:\t/,"",b); gsub(/-?[0-9]+\(/,"(",a); gsub(/-?[0-9]+\(/,"(",b); gsub(/0x[0-9a-f]+$/,"",a); gsub(/0x[0-9a-f]+$/,"",b); if (a ~ /^(addiu|lui|j|jal)[ 	]/ && b ~ /^(addiu|lui|j|jal)[ 	]/) {sub(/,?-?[0-9a-fx]+$/,"",a); sub(/,?-?[0-9a-fx]+$/,"",b)} m=(a==b)?" ":"*"; print m $0}'
