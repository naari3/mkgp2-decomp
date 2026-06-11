# CW 1.3.2 register-allocator coloring-order model (Phase 2f, batch_research_allocator_phase2f, 2026-06-11)

Goal: build a predictive model for the order in which the CW 1.3.2 colorer assigns
physical registers to webs, to unlock the register-identity park family
(HandleItemEffect handled-r22, GetMaxSpeedWithBonus mv<->e, CarObject_Init ch/blk/sub/mgr,
OnKartHit GPR partition, fp callee-saved partition, ...). Verdict: **PARTIAL — a robust
GPR callee-saved coloring rule is established and is directly actionable; the binary
exposes a graph-coloring allocator and a (gated, not-yet-enabled) per-pass dump.**

Conventions: observations (compiled & disassembled facts) are under "OBSERVED";
inferences under "HYPOTHESIS". All probes use the production game_extab flag set
(`-O4,p -inline auto -Cpp_exceptions on -use_lmw_stmw on -fp hardware`, see alloc_run.py).

## B. mwcc binary static observation (OBSERVED facts)

Scanned tools `build/compilers/GC/1.3.2/mwcceppc.exe` (strings + targeted i386 disasm
with objdump). The backend is a **graph-coloring register allocator**, not first-fit:

- Source-file markers in the binary: `Coloring.c`, `InterferenceGraph.c`, `SpillCode.c`,
  `IroFlowgraph.c`, `IrOptimizer.c`, `FuncLevelAsmPPC.c`, `PCodeListing.c`.
- Per-web flags: `fSpilled`, `fCoalesced`, `fCoalescedInto` -> Chaitin/Briggs-style
  coalescing + spilling, with an explicit interference graph.
- Pass pipeline (dump banner strings, in order): `INITIAL CODE` -> ... ->
  `AFTER VALUE NUMBERING` -> `BEFORE SCHEDULING` -> `AFTER INSTRUCTION SCHEDULING` ->
  `AFTER PEEPHOLE FORWARD` -> **`AFTER REGISTER COLORING`** ->
  `AFTER VALUE NUMBERING (POST COLORING)` -> prologue/epilogue -> peephole -> final.
  So value-numbering (web formation) happens BEFORE coloring; coloring is a distinct pass.
- A per-pass IR dump exists: format strings `Dumping function %s after %s`,
  `Dumps for pass=%d`, `Flowgraph node %d First=%d, Last=%d`, plus
  `[FUNCTION-LEVEL ASM] AFTER REGISTER COLORING`. These are gated by a runtime flag at
  .bss global `0x5e90ec` (master "dump enabled" byte), copied from the options struct at
  code `0x4be0f3` (`mov dl,[eax+0x4]; mov [0x5e90ec],dl`).

### Dump-flag enable attempt (OBSERVED, NEGATIVE this batch)
- `#pragma dumpir on` is a recognised token (in the pragma table at 0x1a2bd0) but emits no
  output and `#pragma dumpir` (no arg) warns "illegal #pragma". `debug_listing on`,
  `experimental on`: silent, no output. No dump-enabling env var exists (only MWCIncludes).
- Binary-patched a private copy: forced `0x5e90ec` to 1 (patch `8a 50 04` -> `b2 01 90`
  at file-offset for VA 0x4be0f0). The patched compiler still produced a normal .o with
  **no dump output** on stdout/stderr. So `0x5e90ec` alone is not sufficient: there are
  additional gates (e.g. `0x5e91de` checked at 0x55b5b5 before the listing call 0x433310;
  the IrOptimizer pass-dump at 0x453820 has its own predicate) and/or the dump is routed to
  a file object, not the console. Fully enabling it is a multi-gate disasm task -> deferred
  (see "Next batch"). The private patched exe was deleted; the shipped compiler is untouched.

## A. Differential coloring experiments (OBSERVED)

Harness: `tools/compiler_probe/alloc_gpr.c`, `alloc_gpr2.c`, `alloc_gpr3.c`, driver
`alloc_run.py` (reads each fn's `mr rArg,rSrc` moves into the sink-call arg regs => each
web's physical home). Raw output saved to `results_alloc_gpr.txt`.

Each probe builds a clique of long-range int webs (each defined by a separate `src()` call,
all simultaneously live at one `sink()` call) so the interference graph is complete and every
web must get a distinct register. Then permute the source axes:

| probe | axis varied | result (home assignment) |
|---|---|---|
| p0_baseline | decl=def=arg order a..e | a=r31 b=r30 c=r29 d=r28 e=volatile(r0) |
| p1_argrev | sink ARG order reversed | IDENTICAL to p0 (a=r31..) -> arg/use order irrelevant |
| p2_defrev | decl=def order e..a | e=r31 d=r30 c=r29 b=r28 a=volatile -> first-decl=r31 |
| p3_usecount | +5 extra uses of c | c stays r29 -> use-count does NOT reorder homes |
| p3 (param q) | param vs locals | locals a..d = r31..r28, param q = r27 (lowest) |
| p4/p5_two | 2 webs, arg order | a(decl1)=r31, b=volatile; arg swap no-op |
| q0_decl_vs_def | decl a,b,c / def c,a,b | a=r31(decl1) c=r30(decl3) b=volatile -> **DECL order, not def order** |
| q2_chain | a dead before c def | c REUSES r31 -> real graph coloring, reg reuse across disjoint ranges |
| q3_param_priority | param p vs local x | x(local)=r31, p(param)=r30 -> locals outrank params |
| q4_six | 6 webs, 5 cross call | a..e=r31..r27 by decl order; 6th reuses a freed reg |
| r0_vol_clique | webs from exprs not calls | a..e=r31..r27 decl-order descending (live across sink => callee) |
| r1_declrev | decl=def d,c,b,a | d=r31(decl1) c=r30 b=r29 a=volatile -> decl-order descending |

## Model (callee-saved GPR locals) — established, with reservations

**RULE 1 (volatile vs callee split, OBSERVED):** a web is given a callee-saved register
iff its live range crosses at least one `bl`; otherwise it stays in the volatile pool
(r0 / r3..r12). This is a live-range property (the def point relative to calls), independent
of decl order. (q0: `b` is decl-2nd but defined last -> volatile; `c` decl-3rd defined first
-> callee.)

**RULE 2 (callee-saved ranking, OBSERVED, robust across 8 probes):** among the webs that
get callee-saved registers, the physical register is assigned **in source DECLARATION order**:
first-declared local -> r31, next -> r30, ... descending. This is NOT definition order
(q0 discriminates: decl-1st `a` wins r31 over def-1st `c`), NOT use/arg order (p1/p5 no-op),
NOT use-count (p3 no-op).

**RULE 3 (class priority, OBSERVED):** locals outrank parameters. A parameter web (an
incoming-arg copy) is colored AFTER all callee-saved locals, taking the next-lower register
(p3: q=r27 below a..d; q3: p=r30 below x=r31). Matches prior notes ("self saved to r29",
"param-merged web pins to r7").

**RULE 4 (reuse, OBSERVED):** registers are reused across disjoint live ranges (q2: c takes
r31 after a dies) — confirms a true interference-graph colorer and the existing
"one-home-per-VARIABLE only within that variable's live range" picture (#4): distinct
variables with non-overlapping ranges freely share a home.

### What this explains (invariant cross-check)
- #3 GPR block-local "declaration order": YES — RULE 2 is exactly this, sharpened to
  "declaration order, callee pool, r31-descending". The earlier "direction oscillates per
  configuration" is NOT reproduced here (8/8 probes are r31-descending); HYPOTHESIS: the
  oscillation came from confounds — mixed volatile/callee membership shifting which webs are
  in the callee set, and param-class webs interleaving — not a genuine direction flip.
- #4 one-home-per-variable / #5 share-pick: consistent with RULES 2+4 (a low-priority u8
  flag and a pointer that never interfere are colored into the same physical reg in
  declaration-rank order; "follows the pointer sibling" = both land adjacent in the decl-rank
  sweep and coalesce).
- #8 partition families (CarObject_Init ch/blk/sub/mgr, OnKartHit): predicted to be
  movable by reordering the DECLARATIONS of the four owner objects (RULE 2). This is the
  concrete actionable lever to retry.

### What it does NOT yet explain
- #1 fp named web "first-USE (store) ascending" and #2 "FE temp descending from pool top":
  these are SHORT-RANGE expression-temp webs in the FP pool, a DIFFERENT web class from the
  long-range callee-saved GPR locals probed here. HYPOTHESIS (two-tier model): the colorer
  ranks long-range/callee webs by declaration order (RULE 2), but short-range scratch temps
  by first-use order out of a separately-managed scratch pool (matches phase2a/2a-validation:
  for fp temps decl-order is a no-op and store-order wins). The two rules are not in conflict;
  they apply to different web classes. Unifying them precisely needs the GPR-scratch-pool
  direction (r0_vol_clique was forced callee-saved by the tail sum; a pure no-tail volatile
  clique probe is the missing data point).
- #6 fp callee-saved partition pairwise-swap and #7 inline-splice coloring: not re-probed.
  RULE 2 predicts the fp callee partition should also be decl-order rankable; the reported
  "pairwise swap invariant under source reorder" suggests the FP callee pool may rank by a
  different key (first-def?) — untested, flagged.

## Recipe / actionable lever for the park family

For a GPR register-identity residue where web X wants reg rN but lands on rM:
1. Confirm both webs cross a call (callee-saved) — if one is volatile, RULE 1 governs first.
2. Reorder the **source declarations** of the function-scope locals so the target's
   r31-owner is declared first, r30-owner second, etc. (RULE 2). Parameters always rank
   below locals (RULE 3) — if a param must own a high reg, that is unreachable by decl order
   and likely needs the value re-expressed as a local.
3. Use-count, statement/arg order, and the def order are levers ONLY through RULE 1
   (do they move a web across the volatile/callee boundary?) — they will NOT re-rank within
   the callee pool. Stop probing those axes for this family.

Caveat: HandleItemEffect handled-r22 specifically resisted decl-order permutation in phase2e
(all 10 fn-scope slots tried). Under RULE 2 that means `handled` and `obj` are not BOTH in
the plain callee-local decl sweep — `handled` is a u8 that share-picks with the pointer
(#5), so it inherits obj's rank rather than taking its own. The decl-order lever must move
`obj`'s rank (and detach handled), consistent with phase2e's conclusion that only
inline/block restructuring moved the pair. RULE 2 reframes that as: the pair shares one
decl-rank slot; to split them, break the share-pick (give handled an independent
call-crossing live range so it enters the sweep as its own web).

## Next batch recommendation

MODEL-REFINE + DUMP-ENABLE are both worth one more batch, in this order of payoff:
1. **Enable the per-pass dump (highest payoff if it lands).** The strings prove a
   `Dumping function %s after %s` / `AFTER REGISTER COLORING` dump exists. This batch found
   the master gate (0x5e90ec) but it is multi-gated. A focused disasm of 0x55b510 (per-fn
   compile driver), 0x433310 (listing emit), 0x453820 (IrOptimizer pass dump) and the
   options-struct layout (copied at 0x4be0d0; fields at struct offsets +0x4=dump,
   +0x2=?, +0x5f/0x60 = the two `0x5e91ca/cb` codegen flags) should reveal the full
   predicate and the output sink. If enabled, the colorer's web visit order becomes directly
   observable and the model is solved, not inferred.
2. **Close the two-tier model.** One probe set: pure volatile GPR clique (no tail use) to get
   the scratch-pool direction; an fp callee-saved clique to test whether FP callee ranks by
   decl order (RULE 2) or first-def (the #6 pairwise-swap hint).
3. **Validate RULE 2 in-TU** on CarObject_Init (ch/blk/sub/mgr) and OnKartHit GPR partition
   by permuting the owner-object declarations — these are the cleanest decl-order test cases
   in the park set. If they flip on cue, promote; if not, the share-pick (#5) is interleaving
   and the inline-restructure lever (phase2e H1/c9) is the fallback.

Do NOT re-burn budget on: compiler-revision sweeps, pragma space, -opt suboptions, symbol
renames, use-count/arg-order/statement-motion for GPR identity (all closed negative across
phase2a-2e and reconfirmed here).
