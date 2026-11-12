#!/bin/sh
# usage: tools/to_c.sh ROM_OFFSET...   (e.g. 10250 FF10)
# Switches the given splat segments from asm to c, re-extracts so splat writes
# src/<OFF>.c (INCLUDE_ASM stubs) + asm/nonmatchings/<OFF>/, and drops the stale asm/<OFF>.s.
set -e
cd "$(dirname "$0")/.."
for off in "$@"; do
  sed -i "s/      - \[0x$off, asm\]/      - [0x$off, c]/" ogrebattle64.yaml
  grep -q "\[0x$off, c\]" ogrebattle64.yaml || { echo "no asm segment 0x$off" >&2; exit 1; }
done
python3 -m splat split ogrebattle64.yaml > /dev/null
for off in "$@"; do rm -f asm/$off.s build/asm/$off.o; done
