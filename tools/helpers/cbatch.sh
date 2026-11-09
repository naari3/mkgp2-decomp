#!/bin/bash
# cbatch.sh LIST MINUTES OUTDIR : run cperm.py on each "src obj fn" line
H=$(dirname $(readlink -f $0))
mkdir -p $3
while read src obj fn rest; do
  echo "=== $fn ($obj) $(date +%T)" >> $3/log.txt
  timeout $(awk "BEGIN{print int($2*60+90)}") python3 $H/cperm.py $src $obj $fn --minutes $2 --out $3/$fn >> $3/log.txt 2>&1
done < $1
echo ALLDONE >> $3/log.txt
