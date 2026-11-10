#!/bin/bash
# One struct_dedup batch, verified: baseline build -> apply -> build -> every
# object byte-identical (sources of changed objects are reverted and the
# build repeated).  Run from a clean tree on top of origin/main.
#   bash tools/helpers/struct_dedup_batch.sh [struct_dedup.py apply args...]
#   bash tools/helpers/struct_dedup_batch.sh unify|relayout [args...]
# Leaves the result uncommitted for review; see docs/notes/struct_dedup.md.
set -u
cd "$(git rev-parse --show-toplevel)" || exit 2
if [ -n "$(git status --porcelain --untracked-files=no)" ]; then
  echo "batch: tree not clean"; exit 2
fi
ninja > build/struct_dedup_base.log 2>&1 || { echo "batch: baseline build failed"; tail -5 build/struct_dedup_base.log; exit 1; }
python3 tools/struct_dedup.py hashes save || exit 1
case "${1:-}" in
  unify|relayout) python3 tools/struct_dedup.py "$@" | tail -6;;
  *) python3 tools/struct_dedup.py apply "$@" | tail -3;;
esac
for round in 1 2 3 4 5 6; do
  ninja -k 0 > build/struct_dedup.log 2>&1
  rc=$?
  if [ $rc -ne 0 ]; then
    # compile errors: revert the sources that failed
    failed=$(grep -oE '^FAILED: build/GNLJ82/src/[^ ]+\.o' build/struct_dedup.log | sed -E 's#^FAILED: build/GNLJ82/##; s#\.o$##' | sort -u)
    if [ -z "$failed" ]; then echo "batch: build failed, no object to blame"; tail -20 build/struct_dedup.log; exit 1; fi
    for f in $failed; do
      for ext in c cpp; do [ -f "$f.$ext" ] && git checkout -- "$f.$ext" && echo "batch: reverted $f.$ext (compile error)"; done
    done
    continue
  fi
  if python3 tools/struct_dedup.py hashes diff --revert > build/struct_dedup_diff.log; then
    grep -q "main.dol: OK" build/struct_dedup.log || ninja | grep -q "main.dol: OK" || { rm -f build/GNLJ82/main.dol; ninja | tail -1; }
    tail -1 build/struct_dedup_diff.log
    echo "batch: clean after round $round"
    # headers whose every copy was reverted
    for h in include/game/types/*.h; do
      n=$(basename "$h")
      if ! grep -rqF "game/types/$n" src include --include='*.c' --include='*.cpp' --include='*.h' --include='*.hpp' --include='*.inc'; then
        rm -f "$h"; echo "batch: removed unused $h"
      fi
    done
    python3 tools/struct_dedup.py scan > /dev/null
    exit 0
  fi
  grep -E '^(CHANGED|reverted)' build/struct_dedup_diff.log
done
echo "batch: did not converge"; exit 1
