#!/bin/sh
# usage: check.sh file.c rom_offset size [extra cc1 flags...]
# Compiles file.c with KMC GCC 2.7.2 and compares .text to the baserom.
set -e
cd "$(dirname "$0")/../.."
src=$1; off=$2; size=$3; shift 3
KMC=${KMC:-tools/gcc-2.7.2}
# WSL1 can't exec 32-bit ELF; run through qemu if needed (-B avoids an mmap WSL1 lacks).
if [ -z "$RUN32" ] && ! $KMC/cc1 --version >/dev/null 2>&1; then RUN32="qemu-i386-static -B 0x100000000"; fi
CFLAGS=${*:-"-O2 -G0 -mips3 -mgp32 -mfp32"}
out=build/matchtest; mkdir -p $out
# KMC's own cpp aborts under qemu; preprocessing doesn't affect codegen, so use the host cpp.
cpp -P -undef -nostdinc -Iinclude -D_LANGUAGE_C -D__GNUC__=2 -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 "$src" > $out/test.i
rm -f $out/test.s $out/test.o
$RUN32 $KMC/cc1 -quiet $CFLAGS -o $out/test.s $out/test.i || { echo "COMPILE ERROR ($CFLAGS)"; exit 1; }
# KMC-era GNU as 2.6: inserts a nop between back-to-back FP multiplies (VR4300 mulmul errata).
tools/binutils-2.6/as -EB -mcpu=vr4300 -mips3 -G0 $ASFLAGS -o $out/test.o $out/test.s
mips-linux-gnu-objcopy -O binary -j .text $out/test.o $out/full.bin
# old as pads .text to alignment; compare only the function bytes
head -c $(($size)) $out/full.bin > $out/test.bin
dd if=baserom/baserom.us.z64 of=$out/target.bin bs=1 skip=$(($off)) count=$(($size)) 2>/dev/null
if [ "$(python3 tools/matchtest/maskj.py $out/test.bin)" = "$(python3 tools/matchtest/maskj.py $out/target.bin)" ]; then echo "MATCH ($CFLAGS)"; else
  echo "DIFF ($CFLAGS)"
  mips-linux-gnu-objdump -d -EB -m mips:4300 $out/test.o | tail -n +8 > $out/ours.s
  mips-linux-gnu-objdump -D -EB -m mips:4300 -b binary --adjust-vma=0 $out/target.bin | tail -n +8 > $out/theirs.s
  diff <(cut -f3- $out/ours.s) <(cut -f3- $out/theirs.s) | head -40 || true
fi
