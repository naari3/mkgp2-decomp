# docs/sweeps: automated sweep logs and best sources

Output of the unattended matching tools. Moved here on 2026-11-09 from the
Claude project's shared folder (`/mnt/project-files/setup/...`); the tools now
write here by default. Commit new results (they are the record of what was
already tried); the `*.jsonl` files use git's union merge (`.gitattributes`).

| Dir | Written by | Contents |
| --- | --- | --- |
| `autopipe/` | `tools/autopipe.py run` (default `AUTOPIPE_DIR`) | `results_<thread>.jsonl` one row per fn (stage scores, outcome), `best/`, `hits/`, `review/`, `landed_*.log` |
| `autopipe99/` | `AUTOPIPE_DIR=docs/sweeps/autopipe99 tools/autopipe.py run --min 99 ...` | same, for the >=99% sweep; `best/FN_PCT_GCcc.ext` = full TU with the best pragma/cc/decl/stmt setting (start point for shapesweep/regfix `--chain`/`--best-dir`) |
| `shapesweep/` | `tools/shapesweep.py batch` (`--out`) | `results_*.jsonl`, `hits/` (matched TU + fn list), best partial sources |
| `regfix/` | `tools/regfix.py batch` (`--out`, `--hits`) | `results.jsonl`, `hits/` |
| `autosweep/` | `tools/helpers/autosweep.py` (round 2) | candidate lists and `cc.json` (per-fn compiler probe) |
| `leversweep/` | `tools/leversweep.py batch` | diagnosis-triggered source levers (inline -> named locals + decl order, index for walk, restrict, arg-order prototype, try scope, non-const zero arm, dead def): `results.jsonl`, `summary.md` (per-lever fired/improved/matched and the levers that are not automated), `hits/` best TU text per improved fn. Rank by objdiff %, not by diff lines |
| `queue/` | `tools/helpers/workqueue.py snapshot` | copy of the live grind queue: `queue_snapshot.md` (every item with the notes of who tried what), `seed.txt`, `log/*.jsonl` |

`tools/rewrite_rules.py backfill` reads `autopipe*/`, `shapesweep/` and
`regfix/` from here and writes `build/patterns/hits_backfill.jsonl`.

Live state that is NOT here: claim lists (`claims.txt`, refresh them from the open
`unit-claim` issues), `STOP` files and `$MKGP2_SHARE/setup/GRIND_STOP`, and the
live queue logs (`$MKGP2_SHARE/setup/queue/`).
