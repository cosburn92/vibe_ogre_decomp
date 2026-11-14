#!/bin/sh
# usage: fdiff.sh SEG FUNC [N] -- diff our compiled FUNC (from build/src/SEG.o) against the original at its asm ROM offset
cd "$(dirname "$0")/.."
SEG=$1; F=$2
base=$((0x$SEG))
ours=$(mips-linux-gnu-nm -S build/src/$SEG.o | awk -v f=$F '$4==f{print $1" "$2}')
off=$((0x${ours% *})); size=$((0x${ours#* }))
orig=$(awk -v f="glabel $F" '$0==f{g=1;next} g && /\/\* [0-9A-F]+ 8/{print $2; exit}' asm/nonmatchings/$SEG/$F.s)
osize=$(grep -m1 "nonmatching $F," asm/nonmatchings/$SEG/$F.s | sed 's/.*, //')
dis() { dd if=$1 bs=1 skip=$(($2)) count=$(($3)) 2>/dev/null > /tmp/fd.bin
  mips-linux-gnu-objdump -D -EB -m mips:4300 -b binary /tmp/fd.bin | tail -n +8 | cut -f3- | sed 's/0x[0-9a-f]*$/ADDR/'; }
dis build/ogrebattle64.us.z64 $((base+off)) $size > /tmp/fd.ours
dis baserom/baserom.us.z64 $((0x$orig)) $((osize)) > /tmp/fd.theirs
diff /tmp/fd.ours /tmp/fd.theirs > /tmp/fd.diff && echo "$F MATCH" || { echo "$F ours $size orig $((osize))"; cat /tmp/fd.diff | head -${3:-40}; }
