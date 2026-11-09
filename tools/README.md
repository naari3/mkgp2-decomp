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
| `autopipe.py` | runs pragmasweep -> decl order -> permuter unattended | needs naari3's out-of-repo `cperm.py` / `queue.py` (see below) |
| `regswap_classify.py` | nothing; groups near misses by diff shape | picks targets; output `docs/reports/regswap_census.md` |
| `regfix.py` | diagnoses register-only diffs by re-running MWCC's allocator offline on mwccdbg dumps; solves the local declaration order exactly (all orders simulated, no compile); `fix` = focused shapesweep moves + that solver | `diag UNIT FN [--start-tu F]`, `fix UNIT FN`; needs mwccdbg install; parallel via `unshare -n` (`netns_lo.py`) |
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

## Out-of-repo helpers

naari3's Claude threads also use `cperm.py` (text permuter for C/C++),
`queue.py`, `land.sh`, `flipcheck.py` and `autosweep.py`, kept in the
project's shared folder, not here. `autopipe.py` and `shapesweep.py` default
to that location (`/mnt/project-files/setup`). Ask naari3 if you need them.
