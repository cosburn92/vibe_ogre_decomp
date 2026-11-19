#!/bin/sh
# usage: tools/objcmpall.sh SEG "FUNC ROM SIZE" ...   - count of differing lines per function (objcmp)
cd "$(dirname "$0")/.."
SEG=$1; shift
for f in "$@"; do set -- $f; echo "$(sh tools/objcmp.sh $SEG $1 $2 $3 | grep -c '^\*') $1"; done
