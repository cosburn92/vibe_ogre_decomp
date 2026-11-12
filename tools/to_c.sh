#!/bin/sh
# usage: tools/to_c.sh ROM_OFFSET...   (e.g. 10250 FF10)
# Switches the given splat segments from asm to c (and their data/rodata/bss chunks to the dotted forms), re-extracts so splat writes
# src/<OFF>.c (INCLUDE_ASM stubs) + asm/nonmatchings/<OFF>/, and drops the stale asm/<OFF>.s.
set -e
cd "$(dirname "$0")/.."
for off in "$@"; do
  sed -i "s/      - \[0x$off, asm\]/      - [0x$off, c]/" ogrebattle64.yaml
  grep -q "\[0x$off, c\]" ogrebattle64.yaml || { echo "no asm segment 0x$off" >&2; exit 1; }
  # its .data/.rodata/.bss chunks (if any) now come from the C object
  sed -i "s/\(\[0x[0-9A-F]*, \)\(ro\)\{0,1\}data, $off\]/\1.\2data, $off]/" ogrebattle64.yaml
  sed -i "s/type: bss\(, vram: 0x[0-9A-F]*, name: $off \)/type: .bss\1/" ogrebattle64.yaml
done
python3 -m splat split ogrebattle64.yaml > /dev/null
for off in "$@"; do rm -f asm/$off.s build/asm/$off.o; done
