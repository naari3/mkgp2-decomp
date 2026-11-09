# From target assembly to source: lookup tools and the rewrite-rule catalog

Two questions come up on every near miss: "how did we write this shape
elsewhere?" and "which source rewrite fixes this kind of diff?". This page
covers the tools that answer them from data instead of memory, and the
machine-readable catalog that the sweeps (regfix, shapesweep, autopipe) read
from and write back to.

## 1. "How was this asm written before?" (`tools/asmgrep.py`)

Every 100 % function's instructions ARE the target's, so its source is a
known-good way to produce them. `asmgrep.py` indexes the target assembly of
all matched functions (7391 on 2026-11-09, `build/GNLJ82/asm/*.s` filtered by
`report.json`, about 5 s) and finds functions that contain a given shape,
printing their source:

    # paste the target's window: registers become variables, offsets stay
    python3 tools/asmgrep.py like game/kartmove/carobject fn_8019EB9C --from 0x44 --to 0x70 --src
    # --loose: offsets/immediates match anything; --sub K: rank partial matches
    # hand-written pattern ($x = any register, consistently; * any operand; # any number; ...N gap)
    python3 tools/asmgrep.py find -e 'fmadds $a, *, *, $a' -e '...4' -e 'lfs $t, 0x30($m)' -e '...4' -e 'fadds $a, $t, $a' --src
    # nearest matched relatives by shared 5..3-instruction shapes (scheduling-tolerant)
    python3 tools/asmgrep.py similar game/kartmove/carobject fn_8019EB9C --src

`asmgrep.py idioms` runs the patterns in `tools/asm_idioms.json` (bool
compares, magic division, int/float conversion, rlwimi colours, fused
multiply-adds, virtual calls, ...) and writes
[reports/asm_idioms.md](reports/asm_idioms.md): count, the C/C++ form, and the
smallest matched example with its source.

Limit: the mapping is per function, not per source line. MWCC's DWARF line
table under `-O4` keeps only increasing line numbers (checked 11-09: the first
statement of a scheduled block simply has no entry), so it cannot attribute
instructions to statements. The PCode dumps of mwcc-debugger do carry a line
per instruction (tools/mwccdbg.py); asmgrep picks the smallest example so the
whole function stays readable.

## 2. The rewrite-rule catalog (`tools/patterns/`, `tools/rewrite_rules.py`)

- `tools/patterns/rules.jsonl`: one rule per line. `when` = triggers (register
  census signature from `tools/regswap_classify.py`, a regfix diagnosis, an
  asmgrep pattern found in the target, or a source regex), `rewrite` = kind +
  template, `tool` = the command that automates it, `evidence`, `refs`. The
  schema is in the docstring of `tools/rewrite_rules.py`. Rule kinds follow
  the regfix vocabulary (hoist_to_local, inline_wrap, unvar, split_init, ...)
  so regfix can turn its diagnoses into concrete rewrites.
- `tools/patterns/evidence.jsonl`: functions each rule fixed. Generated
  (`import-evidence`) from the rules plus the onmokoworks Codex table in
  [regalloc_patterns.md](regalloc_patterns.md); re-run when the table grows.
- `/mnt/project-files/setup/patterns/hits.jsonl` (shared, append-only): every
  application of a rule with outcome attempt / improved / match / landed.
  shapesweep's batch mode and autopipe append automatically, regfix appends
  its own, and anything else can call
  `python3 -I tools/rewrite_rules.py record --fn F --unit U --rule ID --tool T --before N --after M [--commit C]`.
  Recorded wins raise a rule's rank in `suggest`/`coverage`.

Commands:

    python3 -I tools/regswap_classify.py --min 90 --json build/regswap_census.json   # census first
    python3 -I tools/rewrite_rules.py suggest game/kartmove/carobject fn_8019EB9C    # ranked rules for one fn
    python3 -I tools/rewrite_rules.py coverage --md docs/reports/rewrite_coverage.md
    python3 -I tools/rewrite_rules.py report --md docs/reports/rewrite_convergence.md

## 3. Should this be rolled out, and does it converge? (assessment, 2026-11-09)

Numbers from [reports/rewrite_convergence.md](reports/rewrite_convergence.md)
and [reports/rewrite_coverage.md](reports/rewrite_coverage.md):

- 221 functions are left (7391/7612). Of the 209 at >= 90 %: 71 register-only,
  25 registers + order, 100 registers + other operands, 13 no register diff.
  Only the first two groups are what regfix and the source-shape rules can
  close; most of `reg+other` needs data ownership / TU merges or a different
  expression, which the catalog only points at.
- Past fixes reuse known levers: of the 193 dated fixes in the evidence
  (11-06..11-09), 153 fall under a rule family that had already fixed an
  earlier function, 23 were the first of a family, and 17 fit no rule
  (`unclassified`). So most fixes are repeats of a small set of levers, which
  is what makes a catalog worth having.
- But the families are broad. Every near miss gets at least one applicable
  rule from its census signature, while only 46/209 have a precise trigger
  (an asm shape, a regfix diagnosis or a source regex). The broad ones say
  "this lever has worked on this kind of diff", not "this will work".
- Pace is slowing (+353, +97, +25 matched functions on 11-07..11-09), as
  expected for a long tail.

Recommendation: keep the catalog as the shared vocabulary between regfix,
shapesweep and the onmokoworks workers (it is plain JSONL in the repo, so their
prompts can read it), and judge convergence from the hits log rather than from
the evidence, which was classified after the fact. The signal to watch in
`report`: wins per rule over the next days, and whether new 100 % landings
come from existing rules (converging) or keep needing `unclassified` ones (the
catalog is not the bottleneck). The most valuable next step is sharper
triggers: turn each regfix diagnosis kind into the rewrite that realises it
(most are "make this temp a named local"), and add asm-shape triggers as new
fixes land.
