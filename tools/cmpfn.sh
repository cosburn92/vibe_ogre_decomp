#!/bin/sh
# usage: tools/cmpfn.sh ROM SIZE  - side-by-side, marking lines that differ beyond relocation offsets
sh tools/romdiff.sh $1 $2 >/dev/null
paste -d'|' build/romdiff.ours build/romdiff.theirs | awk -F'|' '{a=$1; b=$2; sub(/^ *[0-9a-f]+:\t/,"",a); sub(/^ *[0-9a-f]+:\t/,"",b); gsub(/-?[0-9]+\(/,"(",a); gsub(/-?[0-9]+\(/,"(",b); if (a ~ /^(b|j)/) gsub(/0x[0-9a-f]+$/,"",a); if (b ~ /^(b|j)/) gsub(/0x[0-9a-f]+$/,"",b); if (a ~ /^addiu/ && b ~ /^addiu/) {sub(/,-?[0-9]+$/,"",a); sub(/,-?[0-9]+$/,"",b)} m=(a==b)?" ":"*"; print m $0}'
