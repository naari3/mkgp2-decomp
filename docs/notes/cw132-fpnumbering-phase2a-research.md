# HANDOFF batch_research_fpnumbering_phase2a

fp-scratch register NUMBERING family final probe (approach-A roadmap Phase 2a).
Phase-0 methodology applied: minimal repro + automated direction classifier +
exhaustive compiler/pragma/-opt sweep. Harness + all result TSVs saved to
tools/compiler_probe/ (probe_fp.py, fpnum_*.c, run_fp_axis1-4.py,
results_fp_axis1-4.tsv).

## Verdict: PARTIAL-SOLVED (new source-form lever found; compiler/pragma/-opt axes all closed negative)

The family splits into TWO distinct mechanisms. One is now solved at the
minimal-repro level with a plain source-form recipe under the production flags;
the other is modeled but not yet fully controllable.

## Classifier

probe_fp.py: per fn, extract the longest run of consecutive `lfs fR, off(rX)`,
classify offset direction + register direction (a/d/m). TARGET signature for
asc-def forms = "ad" (offsets ascending, regs DESCENDING). Baseline CW 1.3.2
-O4,p (game_extab TU flags incl. -Cpp_exceptions on -use_lmw_stmw on):
c16_pipe (PerFrameStep 8-temp pipeline repro) = aa[0,1,2,3,4,5,6,7] -> family
reproduced in 30 lines.

## Probe matrix results (132 compile-probes total)

### Axis 1: compiler variants (29 probes, results_fp_axis1.tsv) - NEGATIVE
- GC 1.0 / 1.1 / 1.1p1 / 1.2.5 / 1.2.5n / 1.3 / 1.3.2 / 1.3.2r / 2.0 / 2.0p1 /
  2.5 / 2.6 / 2.7: byte-identical classification to baseline (ascending). No
  patch revision changes the GO-web numbering.
- GC 3.0a* / all Wii: c8_arr (array-element temps) flips to ad[7..0] = target
  direction, but c8_asc / c16_pipe stay ascending. Observation only (wrong
  compiler era for this game); shows the SROA-temp enumeration order was
  reversed post-2.7.

### Axis 2: pragma space (62 probes, results_fp_axis2.tsv) - NEGATIVE
All optimizer/codegen pragmas from help_132_all.txt: no change to numbering
direction at any usable opt level. Exceptions (not usable as recipes):
- `#pragma optimization_level 0`: DESCENDING f31,f30,... (callee-saved pool,
  no GO) - confirms the non-GO assigner allocates from the pool TOP downward.
- `#pragma global_optimizer off`: c8_arr only flips to ad[7..0] (scratch pool,
  descending); named-temp forms stay ascending. Whole-fn GO-off destroys
  CSE/scheduling everywhere else -> not viable for the 4 parked fns.

### Axis 3: -opt suboptions / -schedule (30 probes, results_fp_axis3.tsv) - NEGATIVE
nolifetimes / nocse / nodeadstore / nodeadcode / noprop / nostrength / noloop /
nopeephole / nospace / nospeed / -schedule on|off / explicit -opt spellings /
levels 1-4: GO-web coloring stays ASCENDING in every combination. Only
level=0 descends (same as pragma O0). Axis closed.

### Axis 4: source form (11 probes incl. manual asm inspection) - **HIT**

**`s8_member` (fpnum_struct.c): direct member-to-member copies with NO named
temps, into an escaping local struct, default flags, CW 1.3.2:**

```c
F16 x;                       /* escaping: sink(x.m) after */
x.m[0] = src->m[0];          /* NO intermediate named float */
...
x.m[7] = src->m[7];
```

emits **lfs f7,0x0(r3); lfs f6,0x4 ... lfs f0,0x1c; stfs f7..f0** - byte-for-
byte the target idiom of PerFrameStep rows 36-45 (ascending offsets,
DESCENDING regs, loads batched before stores). Survives read-back across a
call (s8_readback). GPR analog identical: i8_member emits lwz r10..r4,r0 /
stw r10..r4,r0 (descending), i3_member r5,r4,r0.

Negative source forms (same TU): named temps (asc/desc/revuse/register),
array temps t[8], struct assignment `x = *src` (lowers to GPR word copy, no
lfs; gprfloatcopy/block_assign pragmas do not change this).

## Model (observed rules, with reservations)

1. CW 1.3.2 has two value-numbering paths:
   - **User-named locals become global-optimizer webs**: colored ASCENDING in
     web-creation order. Direction is unconditional across all compilers
     1.0-2.7, all pragmas, all -opt suboptions (this is what every previous
     negative probe was hitting).
   - **Front-end expression temps** (memory-to-memory member/element copies
     that never touch a named local): allocated DESCENDING from the top of the
     currently-free scratch pool. This matches the target's
     "later-first-use -> lower reg" appearance exactly for copy regions: the
     descending pool-top allocation is the actual mechanism, not a
     live-range-based tie-break.
2. Batching width of FE-temp copies adapts to free-reg count at that point:
   16 free -> one 16-load batch (f30,f31,f13..f0); ~0 free -> serialized
   lfs f0/stfs f0 pairs (s16_pressure); the target's 8-deep alternation
   (load 8 / store+refill alternation / store 8) is the width-8 instance.
   The named-temp version pins width 8 by construction but numbers ascending;
   the direct-copy version numbers descending but lets the batch width float.
   In-fn register pressure decides whether direct copies reproduce the
   target's exact emission - must be validated per fn in the promote batch.
3. The GO-web sub-family (Explosion vx/const f3-f4 tie, PerFrameStep na/nb
   zero-vs-velX and cross-product clusters) is the OTHER mechanism: coloring
   order is context-dependent (in minimal repros it follows def order and
   def-order swaps DO move the assignment; the real fns reportedly resisted
   def reorder, so surrounding live webs shift the tie). Not closed.

## Recipe (for the promote batch to validate in-TU)

- 16-float copy region (PerFrameStep rows 36-59) and the GPR word-copy
  residues: replace named-temp pipelines with direct member-to-member copies
  (`x.m[i] = mv->mtx[i];`, ascending, no named float temps). Expect descending
  f-numbering for free; verify the batch width against target (if CW batches
  wider than 8, add register pressure or split flow to clamp it).
- na/nb + cross-product + Explosion tie-break: retry def-order permutation of
  the two tied webs WHILE keeping the member-to-member form for neighbors
  (mixed mechanism regions; my na_named minimal repro moved regs with def
  order, contradicting the in-fn negative - the earlier probes likely swapped
  decls, or the neighboring named webs absorbed the change).
- Do NOT burn probes on: compiler revisions, pragmas, -opt suboptions for this
  family - all closed negative here.

## Time / leftovers

~70 min. Not reached: (a) in-context validation against the real PerFrameStep
asm (promote-batch work by design); (b) Explosion-specific 2-web minimal repro
matching its exact surrounding pressure; (c) the 2 small scheduling artifacts
(prologue mr pair order, addi churn) - likely fall out of the same GO-web
ordering, untested.

```json
{
  "verdict": "partial",
  "recipe": "Direct member-to-member copies (no named locals) make CW 1.3.2 allocate FE expression temps DESCENDING from the scratch-pool top: s8_member emits lfs f7..f0 / stfs f7..f0 byte-exact target shape under production flags (GPR analog r10..r4,r0 identical). Replaces the named-temp pipeline in copy regions; batch width floats with free-reg count and needs per-fn validation. GO-web tie-breaks (Explosion vx/const, na/nb, cross product) remain context-dependent: def-order swap moves regs in minimal repros, retry in-fn.",
  "model": "Two mechanisms: (1) user-named locals -> global-optimizer webs, colored ASCENDING in creation order, invariant across GC 1.0-2.7 / all pragmas / all -opt suboptions (GC 3.0+/Wii reversed SROA-temp order only); (2) front-end memory-to-memory expression temps -> allocated DESCENDING from pool top, which is what the target's later-first-use->lower-reg appearance actually is in copy regions. Non-GO paths (level 0, global_optimizer off) also descend.",
  "probes": 132
}
```
