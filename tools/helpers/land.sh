#!/bin/bash
# land.sh: the "landing" steps every thread repeats, in one command.
#
#   bash tools/helpers/land.sh [--queue ID] [--dry-run] [--clean]
#
# Run from the repo root with your change already COMMITTED on a local branch
# (or local main). It:
#   1. fetches origin/main and rebases onto it (stops on conflict);
#   2. builds (incremental when tools/extab_slices.py exists, i.e. ninja
#      tracks the extab jsons; otherwise or with --clean: rm -rf build/GNLJ82/src);
#   3. checks ninja's exit code AND "main.dol: OK";
#      on failure runs tools/extab_renumber.py on the changed TUs + doldiff;
#   4. prints matched-function / complete-unit totals and every changed TU's
#      functions with their %, ready to paste into the report;
#   5. pushes HEAD to origin main (retry 2/4/8/16 s; on a race it re-fetches,
#      rebases, rebuilds (incremental, only the DOL check) and tries again,
#      up to --tries rounds, default 10, with a short random pause);
#   6. with --queue ID: queue.py done ID --note <sha> (needs MKGP2_THREAD).
# Before building it runs `tools/rewrite_rules.py check --strict` (duplicate
# docs/regalloc_patterns.md section numbers stop the landing).
# --dry-run stops after step 4. Claims are NOT touched: close your
# [unit-claim] issue with the GitHub MCP tool yourself after it says LANDED.
set -u
QUEUE=""; DRY=0; CLEAN=0; TRIES=10
while [ $# -gt 0 ]; do
  case "$1" in
    --queue) QUEUE="$2"; shift 2;;
    --dry-run) DRY=1; shift;;
    --clean) CLEAN=1; shift;;
    --tries) TRIES="$2"; shift 2;;
    *) echo "unknown arg $1"; exit 2;;
  esac
done
ROOT=$(git rev-parse --show-toplevel) || exit 2
cd "$ROOT"
if [ -n "$(git status --porcelain --untracked-files=no)" ]; then
  echo "land: uncommitted changes to tracked files; commit or stash first"; git status --short --untracked-files=no; exit 2
fi

fetch() {
  for d in 0 2 4 8 16; do
    [ $d -gt 0 ] && sleep $d
    git fetch -q origin main && return 0
  done
  echo "land: git fetch failed"; return 1
}

build() {
  if [ $CLEAN = 1 ] || [ ! -f tools/extab_slices.py ]; then
    rm -rf build/GNLJ82/src
  fi
  rm -f build/GNLJ82/main.dol build/GNLJ82/ok
  if [ "${QUICK:-0}" = 1 ]; then
    ninja build/GNLJ82/ok > build/land.log 2>&1
  else
    ninja all_source progress build/GNLJ82/report.json build/GNLJ82/ok > build/land.log 2>&1
  fi
  local rc=$?
  if [ $rc -ne 0 ] || ! grep -q 'main.dol: OK' build/land.log; then
    echo "land: BUILD/SHA FAILED (ninja rc=$rc). Tail of build/land.log:"
    tail -15 build/land.log
    local changed
    changed=$(git diff --name-only origin/main -- src | grep -E '\.(c|cpp)$')
    if [ -n "$changed" ] && [ -f tools/extab_renumber.py ]; then
      echo "--- extab @N renames of changed TUs (fix: tools/extab_renumber.py <src> --write) ---"
      python3 tools/extab_renumber.py $changed
    fi
    if [ -f build/GNLJ82/main.dol ]; then
      echo "--- first differing DOL bytes (file off, vaddr, orig, built) ---"
      python3 - <<'PY'
import struct
a=open('orig/GNLJ82/sys/main.dol','rb').read();b=open('build/GNLJ82/main.dol','rb').read()
print('size', len(a), len(b))
h=a[:0x100];offs=struct.unpack('>18I',h[:72]);addrs=struct.unpack('>18I',h[72:144]);sz=struct.unpack('>18I',h[144:216])
n=0
for i in range(min(len(a),len(b))):
    if a[i]!=b[i]:
        va=next((ad+i-o for o,ad,s in zip(offs,addrs,sz) if o<=i<o+s),0)
        print(hex(i),hex(va),a[i],b[i]); n+=1
        if n>8: break
PY
      echo "(hint: DOL larger by a weak fn's size = unrenamed weak copy; off by 4/0x20 = DATA_ALIGN4_TUS; see TIPS.md)"
    fi
    return 1
  fi
  return 0
}

summary() {
  python3 - "$@" <<'PY'
import json, subprocess, sys
r = json.load(open('build/GNLJ82/report.json'))
m = r['measures']
print(f"totals: {m['matched_functions']}/{m['total_functions']} fns, "
      f"{m['complete_units']}/{m['total_units']} complete units, fuzzy {m['fuzzy_match_percent']:.3f}%")
changed = subprocess.run(['git', 'diff', '--name-only', 'origin/main', '--', 'src'],
                         capture_output=True, text=True).stdout.split()
by_src = {u['metadata'].get('source_path'): u for u in r['units'] if u.get('metadata')}
for src in changed:
    u = by_src.get(src)
    if not u:
        print(f"  {src}: (not in report)"); continue
    tag = 'Matching' if u['metadata'].get('complete') else 'NonMatching'
    fs = u.get('functions', [])
    done = sum(1 for f in fs if f.get('fuzzy_match_percent') == 100.0)
    print(f"  {src} [{tag}] {done}/{len(fs)} fns 100%")
    for f in fs:
        p = f.get('fuzzy_match_percent', 0.0)
        if p != 100.0:
            print(f"      {f['name']}: {p:.2f}%")
    if tag == 'NonMatching' and fs and done == len(fs):
        print("      -> every function is 100%: try flipping this TU to Matching")
PY
}

QUICK=0
for round in $(seq 1 "$TRIES"); do
  fetch || exit 1
  if ! git rebase -q origin/main; then
    echo "land: rebase conflict; resolve it (or git rebase --abort) and rerun"; exit 1
  fi
  if [ -z "$(git log --oneline origin/main..HEAD)" ]; then
    echo "land: nothing to push (HEAD is already in origin/main)"; exit 0
  fi
  # catalog consistency after the rebase: parallel threads must not take the
  # same docs/regalloc_patterns.md section number (fails); other findings warn
  if [ -f tools/rewrite_rules.py ]; then
    python3 -I tools/rewrite_rules.py check --strict || { echo "land: fix the section numbering above and rerun"; exit 1; }
  fi
  build || exit 1
  echo "land: main.dol OK on $(git rev-parse --short HEAD) (rebased on $(git rev-parse --short origin/main))"
  git log --oneline origin/main..HEAD
  [ $QUICK = 0 ] && summary
  [ $DRY = 1 ] && { echo "land: --dry-run, not pushing"; exit 0; }
  pushed=0
  for d in 0 2 4 8 16; do
    [ $d -gt 0 ] && sleep $d
    out=$(git push origin HEAD:main 2>&1) && { pushed=1; break; }
    echo "$out" | grep -q 'rejected\|non-fast-forward\|fetch first' && break
  done
  if [ $pushed = 1 ]; then
    SHA=$(git rev-parse --short HEAD)
    echo "LANDED $SHA: $(git log -1 --format=%s)"
    if [ -n "$QUEUE" ]; then
      python3 -I "$(dirname "$(readlink -f "$0")")/workqueue.py" done "$QUEUE" --note "$SHA"
    fi
    echo "reminder: close your [unit-claim] issue if you are leaving this TU"
    echo "reminder: log the rule NOW that the commit is on main (the id is resolved from main):"
    echo "  python3 -I tools/rewrite_rules.py record --fn FN --unit UNIT --rule RULE_ID --outcome landed --commit $SHA"
    echo "  (new rule? add it to tools/patterns/rules.jsonl first; then commit tools/patterns/ and land again)"
    exit 0
  fi
  echo "land: push rejected (main moved); rebasing again (round $round/$TRIES)"
  QUICK=1  # tools/extab_slices.py makes the post-rebase rebuild incremental
  sleep $((1 + RANDOM % 5))
done
echo "land: gave up after $TRIES rounds (main kept moving); rerun land.sh"; exit 1
