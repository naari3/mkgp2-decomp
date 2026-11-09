# tools/

Run everything from the repo root. Most matching tools need a finished build
(`ninja`, so `build/GNLJ82/asm` and `report.json` exist).

## Build (used by configure.py / ninja / CI; do not move)

`project.py`, `ninja_syntax.py`, `download_tool.py`, `decompctx.py`,
`transform_dep.py`, `changes_fmt.py`, `extab_slices.py`, `reorder_extab.py`,
`postprocess_*.py`, `extab_order.json`, `extab_user_renames.json`.
CI / progress page: `gen_progress_page.py`, `progress_history.py`,
`progress_metrics.py`, `verify_publication.py`, `test_operations.py`.

## Near-miss sweeps (register allocation / scheduling)

Rough order to try; each one writes nothing to the repo unless `--apply`.

| Tool | What it varies | Notes |
| --- | --- | --- |
| `pragmasweep.py` | compiler version x `opt_*` pragmas x decl order | start here (regalloc_patterns §1, §2, §6) |
| `stmtsweep.py` | order of independent statements | |
| `typesweep.py` | integer types of locals | §17 |
| `retname_sweep.py` | named return value inside inlines | §16 |
| `shapesweep.py` | source shape (inline wrappers, temporaries, hoists) | when the above are exhausted |
| `permuter/mkperm.py` | sets up upstream decomp-permuter (random AST mutations) for one fn | C and C++ free fns; see `permuter/README.md` |
| `autopipe.py` | runs pragmasweep -> decl order -> permuter unattended | uses `helpers/cperm.py` / `helpers/workqueue.py`; logs to `docs/sweeps/autopipe*/` |
| `regswap_classify.py` | nothing; groups near misses by diff shape | picks targets; output `docs/reports/regswap_census.md` |
| `regfix.py` | diagnoses register-only diffs by re-running MWCC's allocator offline on mwccdbg dumps; solves the local declaration order exactly (all orders simulated, no compile); `fix` = focused shapesweep moves + that solver | `diag UNIT FN [--start-tu F]`, `fix UNIT FN`; needs mwccdbg install; parallel via `unshare -n` (`netns_lo.py`) |
| `asmgrep.py` | nothing; finds matched functions whose target asm has a given shape and prints their source (`like`, `find`, `similar`, `idioms`) | docs/asm_to_source.md |
| `rewrite_rules.py` | nothing; matches `patterns/rules.jsonl` (target shape -> source rewrite) against near misses, logs rule hits, convergence report | docs/asm_to_source.md |
| `mwccdbg.py` | nothing; shows why a register went where it did | mwcc-debugger wrapper; `mwcc_dump.py` is the older private-mwcc variant |

## Data / TU boundaries

`tu_audit.py` (merge/split/own proposals -> `docs/reports/tu_boundary_audit.md`),
`pool_audit.py` (pooled-data ownership -> `docs/reports/pool_audit.md`),
`own_data.py` + `data2c.py` (give a data run to the TU that uses it),
`extab_renumber.py`, `scan_asm_fns.py`, `extract_fn_asm.py`.

## Other

- `grind_stop_hook.py`: opt-in Claude Code Stop hook (`.claude/settings.json`).
- `ghidra_symbol_dump.json`, `mkgp2_types.gdt`, `ghidra_export_gdt.java`:
  symbols and types for your own Ghidra project (see CONTRIBUTING.md).
- `oneshot/`: symbol seeding scripts used once in 2026-05..07.
- `compiler_probe/`: 2026-06 MWCC register-allocator research
  (`docs/notes/cw132-*-research.md`, used by `mwcc_dump.py`).

## helpers/

Scripts naari3's Claude threads use day to day (moved here from the project's
shared folder on 2026-11-09):

- `cperm.py`: text-level permuter for C/C++ TUs; `autosweep.py` / `cbatch.sh` run it in bulk.
- `workqueue.py`: the shared grind queue (`list/take/done/park/release/add/snapshot`).
  Its live state (append-only logs) stays in `$MKGP2_SHARE/setup/queue/` because
  threads in different containers append to it without committing;
  `workqueue.py snapshot` copies it to `docs/sweeps/queue/` for the repo.
- `land.sh`: verify (clean main.dol + no regressions), commit, rebase, push one match.
- `flipcheck.py`: TUs whose functions are all 100% but still marked NonMatching.
- `declsweep.py`, `psweep.py`, `probe.py`, `vt.py`, `try.py`, `cmp.py`, `mxident.py`, `lit.py`,
  `fd.py`, `doldiff.py`, `asmr.py`, `seqmap.py`, `mksplit.py`, `addtu.py`, `rep.py`, `runs.py`:
  small one-purpose probes from rounds 1-2, kept as they were (paths fixed to the repo).

Run python helpers with `python3 -I` (the old name `queue.py` shadowed stdlib `queue`).

## Where results go (all in the repo)

| What | Path |
| --- | --- |
| sweep logs (autopipe, autopipe99, shapesweep, regfix) + best near-miss sources | `docs/sweeps/` (README there) |
| rewrite-rule hits (`rewrite_rules.py`, `regfix.py`, `shapesweep.py`, `autopipe.py`) | `tools/patterns/hits.jsonl` |
| hand-work drafts and notes for near misses | `docs/wip/` |
| regenerated: `rewrite_rules.py backfill` | `build/patterns/hits_backfill.jsonl` |

Commit these with your landing or at the end of a run. The jsonl logs use git's
union merge driver (`.gitattributes`), so parallel appends rebase cleanly.

Outside the repo (`$MKGP2_SHARE`, default `/mnt/project-files`, the Claude project
folder) are only: the game ISO and the compiler zip that `tools/cloud_setup.sh`
needs, the live work-queue state and the `setup/GRIND_STOP` switch, and an optional
prebuilt `setup/mwccdbg/retrowin32` that `mwccdbg_install.py` would otherwise
build with cargo.
