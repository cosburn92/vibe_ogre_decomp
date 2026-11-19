#!/bin/sh
# usage: tools/scoreall.sh SEG LISTFILE  - objcmp diff-line counts for each "FUNC ROM SIZE" line in LISTFILE
cd "$(dirname "$0")/.."
while read f r z; do echo "$(sh tools/objcmp.sh $1 $f $r $z | grep -c '^\*') $f"; done < $2
