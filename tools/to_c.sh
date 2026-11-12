#!/bin/sh
# usage: tools/to_c.sh ROM_OFFSET...   (e.g. 10250 FF10)
# Switches the given splat segments from asm to c (and their rodata chunks to .rodata), re-extracts so splat writes
# src/<OFF>.c (INCLUDE_ASM stubs) + asm/nonmatchings/<OFF>/, and drops the stale asm/<OFF>.s.
set -e
cd "$(dirname "$0")/.."
for off in "$@"; do
  sed -i "s/      - \[0x$off, asm\]/      - [0x$off, c]/" ogrebattle64.yaml
  grep -q "\[0x$off, c\]" ogrebattle64.yaml || { echo "no asm segment 0x$off" >&2; exit 1; }
  # its rodata chunk (if any) now comes from the C object
  sed -i "s/\(\[0x[0-9A-F]*, \)rodata, $off\]/\1.rodata, $off]/" ogrebattle64.yaml
done
python3 -m splat split ogrebattle64.yaml > /dev/null
for off in "$@"; do rm -f asm/$off.s build/asm/$off.o; done
