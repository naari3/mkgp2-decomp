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

## In-TU validation (2026-06-11, batch_promote_rule2_validation)

Applied the Phase 2f model to the park fns inside src/game/auto_ONKARTHIT_block.c.
Result: 1 promote (KartItem_GetMaxSpeedWithBonus 100%), 1 park confirmed with the model
boundary precisely mapped (CarObject_HandleItemEffect stays 99.93%). All mappings below are
OBSERVED (objdiff per-row diffs); interpretation marked HYPOTHESIS.

### KartItem_GetMaxSpeedWithBonus 0x8004F040: PROMOTED 100% (commit 68c8b34)

The mv<->e park (11 insns) fell to two model-guided edits, 3 builds total:
1. Whole tail inside the static inline helper + passthrough wrapper
   (`return helper(self);`): the previous ~60-variant floor always kept a wrapper-local
   `mv` (for the coinBonus tail) or passed `mv` as the helper param. Either way mv became
   a MERGED web (param-merge / cross-boundary CSE) -> colored LAST -> pinned r7
   (the highest free volatile in this leaf). Removing every merge restores mv to its
   declaration-rank slot.
2. GPR decl order `(e, off, mv, i)` -> e=r7, off=r6, mv=r5, i=r4: descending from r7 by
   decl order. OBSERVED: this is RULE 2 operating in the VOLATILE pool of a leaf fn
   (no bl; pool top r7, r3 held by `self`). This closes the "scratch-pool direction"
   gap from the main batch: leaf long-range volatile locals rank decl-order descending
   from the pool top, same shape as the callee pool.
3. FP tail residue (5 rows, f1<->f2): solved by accumulator form
   `max = lbl_806D2770 * keySpeed; max = max * (lbl_806D26FC + mv->coinBonus); return max;`
   - the product chain coalesces into the f1 return web; both
   `return (a*b)*(c+d);` and `max = a*b; return max*(c+d);` numbered the temps inverted.

### CarObject_HandleItemEffect 0x8004F858: PARKED at 99.93% - two-regime counterexample

Baseline = tools/compiler_probe/p2e_handleitemeffect_9993.patch: 7 diff rows, all the
`handled` web (target r22, ours r29 shared with `obj`). 5 builds probed; size stayed
0x7B8 and all non-`handled`/`obj` rows stayed matched throughout.

OBSERVED per-build web mappings (decl lists left-to-right = source order):

| build | lane-clear form | site1 webs | site2/3 webs | fn obj | handled |
|---|---|---|---|---|---|
| 0 (9993 patch) | open blocks, per-site decls | decl(tbl,i,owner,es,mr,cursor,id2) -> r28..r22 IN DECL ORDER | decl(id2,cursor,owner,es,mr,{tbl,i}/{i,tbl}) -> r22..r28 (= fresh-descending in REVERSE decl) | r29 OK | r29 NG (target r22) |
| 1 | per-site helpers(sec), helper-local obj, `handled = helper(self)` | decl(obj,tbl,i,owner,es,mr,cursor,id2) -> r22..r29 (= fresh-descending in REVERSE decl) | decl order -> descending r29.. (IN DECL ORDER) | r22 NG | r22 OK |
| 2 | helpers take obj param (`handled = helper(obj)`, obj = self->owner at site) | sites ascend r23.. (obj consumed r22) | descending r29.. | r22 NG (fresh from BOTTOM after all site webs) | r22 OK |
| 3 | ONE faithful clone of KartItem_CancelActiveEffect, `handled = helper(self->owner)` | reverse-decl descending | decl descending | r22 NG | r22 OK |
| 4 | open blocks + `handled = RetOne_inl()` (trivial `return 1;`) | = build 0 | = build 0 | r29 OK | r29 NG (return const FOLDED, no web) |
| 5 | open blocks + `handled = PlaySEAndRetOne_inl(obj->soundCtrl)` (real bl + return 1) | = build 0 | = build 0 | r29 OK | r29 NG (still folded) |

Stable laws extracted (OBSERVED, reproducible):
- Two regimes exist. Open-coded blocks (regime A): fn-scope callee webs color FIRST
  (obj at its decl rank -> fresh r29), then per-site block webs. Helper-spliced inlines
  (regime B): the spliced site webs color FIRST, and any fn-scope web that is merged with
  spliced code (param-merge: builds 2-3; return-merge: handled in builds 1-3) colors LAST.
- Within a regime the per-site fresh-allocation visits the site decl list in a FIXED but
  site-dependent direction: regime A = site1 decl-order / sites2,3 reverse-decl; regime B
  = exactly inverted (site1 reverse-decl / sites2,3 decl-order). Stable across 3 builds
  each. This is the precise content behind the old "direction oscillates per
  configuration" - it is deterministic per (regime, site ordinal), not random.
- PICK rule (HYPOTHESIS v3, fits every row incl. the matched standalone
  KartItem_CancelActiveEffect where locals take r31..r25 in decl order and the param
  self takes r24 LAST): when a web is colored, reuse the LOWEST-numbered already-used
  callee reg that does not interfere; else allocate fresh, next register DESCENDING.
  "share-pick" (#5) is just this reuse step - handled shares whatever non-interfering web
  is lowest at its turn (r29 in regime A, r22 in regime B).
- TARGET needs obj EARLY (r29, regime A) and handled LATE (r22, regime B)
  SIMULTANEOUSLY. No probed source form produces that mix: a substantial helper flips
  BOTH (obj demotes with it), and a thin helper's `return 1` is constant-folded into
  handled before web formation (builds 4-5), leaving handled early. The remaining unknown
  is what the original source did to demote ONLY handled. Candidate untried levers: an
  inline helper whose return value is NOT a foldable constant (e.g. returns a computed
  int that the target turns into li 1 via VN) - none found yet that keeps the byte shape.

Negative results (do not re-burn):
- RetOne-style trivial inline returns (with or without a real call inside) never create
  a surviving return web at -O4,p: the constant folds into the receiver web (FE/VN).
- Param-merging obj (build 2) does NOT promote it; merged webs DEMOTE regardless of the
  caller-side web's decl rank or use count.

### RULE 1-4 scorecard after in-TU validation
- RULE 1 (bl-crossing -> callee): CONFIRMED, no exceptions seen.
- RULE 2 (decl-order ranking): CONFIRMED for fn-scope webs in regime A and for the leaf
  volatile pool (GetMaxSpeed promote). COUNTEREXAMPLE for inline-spliced site webs: the
  visit direction depends on (regime, site ordinal) as tabled above - a 1-fn TU probe
  family (alloc_* style) reproducing the site1-vs-site2 inversion is the natural next
  probe if the dump-enable route stays blocked.
- RULE 3 (locals > params): REFINED - the standalone shows params color LAST (self=r24
  below 7 locals), not merely "next lower". In fns where params interfere with everything
  (HandleItemEffect) they nevertheless sit at r31/r30; the order criterion that places
  them there is still OPEN (degree-based ordering explains it but then mispredicts
  build-0 handled; recorded as an open contradiction, do not paper over).
- RULE 4 (disjoint reuse): CONFIRMED everywhere (per-site r22..r29 reuse).

## Dump enablement (Phase 2f-2, batch_research_mwccdump_phase2f2, 2026-06-11)

Goal of this sub-batch: fire the per-pass dump and read the colorer's web visit
order. Verdict: **DUMP-ENABLED but PARTIAL** — a real IR dump was fired, but the
register-coloring listing dump is permanently dead in this release, so the
colorer's visit order is NOT directly observable from any built-in dump.

### OBSERVED (Ghidra decompile of mwcceppc.exe 1.3.2 + whole-.text byte scan)

There are **two distinct dump systems**, not one:

1. **Per-pass listing dump (DEAD / stubbed).** Banners `AFTER REGISTER COLORING`
   (str 0x5a52bc), `[FUNCTION-LEVEL ASM] AFTER REGISTER COLORING` (0x5bd814),
   `INITIAL CODE`, `BEFORE SCHEDULING`, etc. Emitted from CodeGen FUN_00433310
   (the per-fn codegen driver, contains `Coloring`/`SpillCode` pipeline) and from
   FuncLevelAsmPPC FUN_00524f60. Every banner is gated by `.bss` byte
   **DAT_005e90ec** and routed through emit fn **FUN_004ffdb0** (and siblings
   FUN_004ffd90, FUN_004ffda0). OBSERVED: **FUN_004ffdb0 disassembles to a single
   `RET`** — it is an empty stub. FUN_004ffd90 is also `return;`. So the dump
   bodies (including the register-coloring listing) were compiled out of the
   shipping build. The earlier Phase 2f note ("setting 0x5e90ec=1 produced no
   output, suspected file sink / extra gate") is now EXPLAINED: 0x5e90ec is
   sufficient to *call* the emit fns, but they do nothing. There is no flag that
   can revive them; the code is absent. This kills the direct route to
   `AFTER REGISTER COLORING`.

   (Correction to Phase 2f: the addresses 0x453820 "IrOptimizer pass dump" and
   0x4be0d0 options-struct were partly mismapped. Options copy is FUN_004be0d0:
   it sets DAT_005e90ec from struct byte +4 — confirmed — but 0x5e90ec drives
   only the stubbed system. 0x5e91de is a listing-related flag in FUN_0055b510
   but also feeds the stubbed path.)

2. **IR-optimizer per-pass dump (LIVE).** Format strings `Dumping function %s
   after %s` (0x5a7b1c), `Flowgraph node %d First=%d, Last=%d`, `Dumps for
   pass=%d`, `Starting function %s`. Emitted from IrOptimizer FUN_0042ddd0 (== the
   pass driver, IrOptimizer.c) via FUN_00454400 (per-pass dumper) / FUN_004540c0
   (progress printf) / FUN_00454240 (flowgraph dumper). Gate = `.bss` byte
   **DAT_005e9409**; output = FILE* **DAT_005ddebc** opened by FUN_00454110 as
   `"<source-basename>.log"` (extension stripped, suffix `.log` at 0x5a79b4, mode
   `"wt"` at 0x5a79bc). OBSERVED via whole-.text byte scan: **DAT_005e9409 is only
   ever WRITTEN to 0** (init/reset `mov byte[0x5e9409],0` at 0x42dd79; fopen-fail
   disable at 0x454190). No instruction anywhere stores 1 — the enable path (a
   `-irdump`-style option handler present in a debug build) was stripped. So the
   dump is reachable but starts permanently off.

### OBSERVED (firing it)

Forced the IR dump on with a 1-byte patch to a PRIVATE copy (script
`tools/compiler_probe/enable_ir_dump.py`):
- Patch A: 0x42dd79 imm8 `00`->`01` (gate on). FUN_00454110, called immediately
  after the gate reset in the one-time init FUN_0042dd70, then sees gate=1 and
  opens `<base>.log`.
- Patch B (optional, verbose): 0x454405 `JZ` (74 41) -> NOP NOP (90 90). The
  IrOptimizer call sites pass param_2=0 to FUN_00454400, which suppresses the
  flowgraph/IR body (`if(param_2!=0)`); NOPing the test forces the full body.

RESULT: compiling a probe `.c` produced `<base>.log` with the full named IR for
**every IR-optimizer pass** (53 pass banners: BuildflowGraph, RemoveUnreachable,
CopyAndConstantPropagation, ExpressionPropagation, UseDef, ConstantFolding,
FindLoops, CommonSubs, ... After IRO_Optimizer). Each pass dumps the flowgraph
nodes and the expression IR with **source variable names in declaration order**
(e.g. `Operand a <assigned>`, `EINDIRECT`, `EASS`, `Funccall`, `EADD`, `Return`).
Saved evidence: `tools/compiler_probe/example_ir_dump_probe.log` (3747 lines for a
5-web clique probe). The patch+compile is reproducible from a clean private copy
(verified).

### What the live dump does and does NOT give

- GIVES: the named-web / temp IR and flowgraph that the colorer consumes, across
  every IR pass, with variable names preserved in source order. Useful for
  confirming which expressions become which webs and how passes merge/split them
  BEFORE register class assignment.
- Does NOT give: physical register assignments or the colorer's visit order.
  Coloring runs later, in CodeGen FUN_005077b0 (Coloring.c) -> FUN_00579cf0, well
  after the IR optimizer. Its only dump is system (1), which is stubbed. So this
  dump cannot, by itself, settle RULE1-4 or the fp/GPR two-tier model.

### Colorer location (for the frida follow-up — OBSERVED entry points)

- **FUN_005077b0** RegisterColoring driver: outer loop over class index
  `DAT_005e931f` = 0..4; per class with webs, calls FUN_00579cf0 in a while loop.
  Contains the `Coloring.c` asserts (0x5bbb18). Inner per-iteration calls
  FUN_00507d40 / FUN_00507b50 / FUN_00507a30 (try-color, returns success/fail) /
  FUN_0057abd0 / FUN_00507900.
- **FUN_00579cf0** per-class color step: build FUN_005797a0, FUN_00579e50,
  FUN_0057a640, coalesce(union-find) FUN_0057a1f0, adjacency FUN_00579fe0,
  FUN_00579d50. The select/assign that writes the home reg into a web is reached
  from here (exact store not yet pinned).
- Web list head: `DAT_005e87b0` (singly linked, *p==next, p[5]=node chain,
  p[6]=interference chain, p[7]=index). Adjacency array: `DAT_005e87d0`. Per-class
  web count: `(&DAT_005e8a7c)[class]`.

HYPOTHESIS (for next batch): hook FUN_00579cf0 onLeave with frida, walk
DAT_005e87b0, and emit each web's index + home-reg field in list order. The
home-reg field offset must first be pinned (single-step FUN_00507a30/FUN_00507900,
or diff the web struct across FUN_00579cf0; cross-check against the final reg that
alloc_run.py already reads from the `mr` emit). Scaffold with these addresses
checked in: `tools/compiler_probe/frida_colorer_probe.js` (NOT yet verified).

### Constraint compliance
Shipped `build/compilers/GC/1.3.2/mwcceppc.exe` is UNTOUCHED (SHA-1
d8f9c36d62f66c2a044d5a20a132b79eeb2f36e5, verified before and after). All patches
were applied to a private copy under tmp_probe/ which was deleted after the
experiment. Only scripts + one example log are committed (binaries are not).

## Colorer call-tree map (independent 2nd RE pass, 2026-06-11)

A parallel RE pass independently confirmed the listing dump is ret-stubbed (NEGATIVE,
matches the Dump enablement section) and produced a sharper colorer call-tree map for the
frida route (ImageBase 0x400000):

- per-function register-allocation driver = **0x5077b0** (loops the 5 register classes,
  writes current class to byte 0x5e931f, asserts via `Coloring.c:0x177`). Called at
  **0x433dc6 / 0x5252d4 / 0x525435** — exactly the "AFTER REGISTER COLORING" points.
- inner color-assignment routines in its call tree: **0x4cf200 / 0x4fd650** (Coloring.c
  region ~0x507800). Hooking these and logging `(web, physical-reg)` in call order yields
  the colorer visit order directly.
- emit-stub resurrection is NOT recommended: stubs 0x4ffdb0/0x4ffd90/0x4ffda0/0x4fca20 have
  different signatures and the per-instruction asm lives in in-memory line lists whose flush
  routine is also stubbed — resurrecting string-emit alone would only print banners.
- empirical: a private-copy patch forcing 0x5e90ec=1 (via the options-copy at 0x4be0f0,
  `8a 50 04 -> b2 01 90`) gave exit 0, 0 bytes output, and a byte-identical .o (SHA1
  5F5C2CFE both) -> confirms the gate is correct but the emitters are dead.

## Frida colorer observation (Phase 2f-3, batch_research_frida_colorer, 2026-06-11)

Verdict: **MODEL-FOUND.** The colorer was hooked at run time with frida; the web
visit order and the home-register field are now DIRECTLY OBSERVED, not inferred.
The previously-inferred RULE 2 ("declaration order, r31-descending") is confirmed
and sharpened to a fully mechanical rule. The shipped compiler was not touched
(hooks ran against a private copy; frida is read/hook only).

### Setup (OBSERVED facts about the binary)
- `mwcceppc.exe` 1.3.2 is PE32, ImageBase 0x400000, **DllCharacteristics=0x0000
  (ASLR OFF)**. The module always loads at 0x400000, so the VAs from the static
  analysis map directly; frida resolves `Module.getBaseAddress` == 0x400000.
- The private copy needs `lmgr326b.dll` (FlexLM) beside it or it exits
  0xC0000135 (DLL_NOT_FOUND) before reaching main.
- frida 17.x: the `Memory.readX(ptr)` API is gone; use `ptr.readX()` members.
  The `frida` CLI mangles `-proc`-style compiler flags, so a python frida driver
  (`tools/compiler_probe/frida_colorer_run.py`) spawns the compiler directly.

### Home-reg field + web/node struct (OBSERVED, objdump + run-time confirm)
The colorer operates on **interference-graph NODES** = elements of the array
`DAT_005e87d0` (indexed by class register number). FUN_00507b50 builds a singly
linked **select stack** out of these nodes; FUN_00507a30 walks that stack from its
head (`ebx=*ebx`) and writes the chosen register. Node layout:
- `[+0x00] u32`  next-in-select-stack (pop order)
- `[+0x04] u32`  -> IR sub-object (type byte at +0x2; not a plain name)
- `[+0x0c] u32`  spill-cost numerator (fild'd in the cost ratio at 0x507c28)
- `[+0x10] u16`  **key** = web-birth index (the discriminator below)
- `[+0x12] u16`  current interference degree (decremented during simplify)
- `[+0x14] u16`  **HOME PHYSICAL REGISTER** (0xffff = uncolored). <<< the field
  the prior batch could not pin. Written at 0x507ace (`mov [ebx+0x14],cx`, chosen
  color) and 0x507af4 (`mov [ebx+0x14],ax`, forced/required color).
- `[+0x16] u16`  flags: 0x1=spilled, 0x2=on-stack, 0x8=coalesce-related,
  0x40=coalesced-into another web.
- `[+0x18] u16` adjacency count; `[+0x1a] u16[]` adjacency = indices into
  DAT_005e87d0.

(The other list, head `DAT_005e87b0`, is the value-numbered web list the build
phase consumes; the select phase works off the DAT_005e87d0 node array instead.)

### OBSERVED visit/color order (raw dumps in tools/compiler_probe/colorer_observation.log)

Mechanism (every probe agrees): FUN_00507b50 pushes nodes so that the select
stack pops in **DESCENDING key order** for the simultaneously-live clique; for
each popped node FUN_00507a30 assigns the next callee register **descending from
r31**. Concretely:

- **colorer_p0.c** (5-web clique, decl a..e): pop order key 36,35,34,33 ->
  r31,r30,r29,r28; the dead/volatile 5th web (key 41, deg 1) -> r0.
- **colorer_p2.c** (decl e..a reversed): IDENTICAL key->reg map (36->r31 ...).
  The frida key map is invariant to decl reorder; what changes is which SOURCE
  VARIABLE owns each key (web-birth order), confirmed by alloc_run/disasm.
- **colorer_merge.c** (return-merged web `m`): pop order a=key36->r31, b=35->r30,
  c=34->r29, d=33->r28, **m=key32->r27 (LOWEST key, colored LAST)**. This is the
  "merged web colors last -> lowest reg" rule, now mechanism-confirmed: a CSE/
  merged web is born with the lowest key in the clique.
- **colorer_declorder.c** (f_abcd vs f_dcba, the CarObject_Init ch/blk/sub/mgr
  shape): frida key->reg map identical in both, BUT the disasm shows the source
  bindings INVERT: f_abcd ch=r31 blk=r30 sub=r29 mgr=r28; f_dcba mgr=r31 sub=r29
  blk=r30 ch=r28. => DECLARATION/DEFINITION order DOES move the variable->reg
  binding (first-defined web -> highest key -> r31). DECL-order lever CONFIRMED
  for this family.

### Unified model (mechanism, OBSERVED)
1. Each web gets a **key** = its birth index in the value-numbered IR. The
   FIRST-formed web in a clique gets the HIGHEST key; later/merged webs get lower
   keys. For plain function-scope locals, web-birth order == source definition
   order == declaration order (this is why RULE 2 reads as "declaration order").
2. Coloring visits webs in **descending key order** (the simplify-stack pop
   order). Within a simultaneously-live callee clique each visited web takes the
   next register descending from r31 (r31, r30, r29, ...).
3. Volatile/short-range webs (low degree, don't cross a call) are trivially
   colored to the volatile pool (r0/r3..) regardless (RULE 1 unchanged).
4. **Merged/CSE/param-merged webs are born late => lowest key => colored last =>
   lowest reg in the clique.** This is the single rule behind "merged web last",
   "param pins to r7/lowest", and HandleItemEffect's `handled` share-pick.

### HandleItemEffect two-regime, mechanism (OBSERVED via colorer_regime.c)
regime_B (fn-scope `obj` defined first, then an inline helper splices its own
locals into the body): the spliced/CSE'd webs are RENUMBERED to HIGHER keys than
`obj`, so they color first (took r31/r30, one with flag 0x40 = coalesced-into),
and `obj` — textually first — drops to r29 (a lower key). Disasm confirms obj=r29.
This is exactly the phase2f "regime B: spliced site webs color first, the
fn-scope web colors last/demoted." => the two-regime behaviour is not a separate
rule; it is web-birth-order being rewritten by inlining. To get HandleItemEffect's
required "obj EARLY (r29 high in its pool) + handled LATE (r22)" simultaneously,
the source must (a) keep obj as a plain early-born fn-scope web (open-coded, no
splice that renumbers it) AND (b) make `handled` a genuinely late-born web (its
own call-crossing live range, not a foldable constant and not a share-pick on
obj). This matches and sharpens the phase2e/2f conclusion; the open lever is a
helper whose return is a non-foldable computed int that VN later turns into the
observed constant.

### Scorecard update
- RULE 1 (bl-cross -> callee): unchanged, CONFIRMED.
- RULE 2: CONFIRMED and reduced to "descending web-birth key; first-defined web
  -> r31". The decl-order lever is real for plain locals (colorer_declorder).
- RULE 3 (params/merged last): CONFIRMED as a special case of rule 4 above
  (param-merge and CSE webs are born late -> low key -> colored last).
- RULE 4 (disjoint reuse): unchanged, CONFIRMED.

### Actionable for the park family (next batch)
- CarObject_Init ch/blk/sub/mgr partition: reorder the four owner-object source
  DEFINITIONS so the target's r31-owner is defined first, r30-owner second, etc.
  (colorer_declorder proves this moves the binding). This is now a high-confidence
  promote lever.
- OnKartHit GPR partition: same decl/def-order lever.
- HandleItemEffect: keep obj open-coded (early-born); give `handled` an
  independent late-born call-crossing web. Do NOT use a substantial inline helper
  that renumbers obj (regime B demotes obj).

### Tools committed
- `tools/compiler_probe/frida_colorer_probe.js` — verified reader (struct offsets
  + select-stack walk + dedup of recolor passes).
- `tools/compiler_probe/frida_colorer_run.py` — python frida spawn driver
  (CLI flag-mangling workaround).
- `tools/compiler_probe/colorer_*.c` — the five probes above.
- `tools/compiler_probe/colorer_observation.log` — captured raw dumps.

### Constraint compliance (this sub-batch)
Shipped `build/compilers/GC/1.3.2/mwcceppc.exe` UNTOUCHED (SHA-1
d8f9c36d62f66c2a044d5a20a132b79eeb2f36e5, re-verified). All hooking ran against a
private copy in `tmp_probe/mwcceppc_priv.exe` (frida read/hook only, no binary
patch). The private copy + lmgr326b.dll under tmp_probe/ are NOT committed
(gitignored scratch). src/game/*.c untouched; worktree builds green.

## In-TU validation round 2 (2026-06-11, batch_promote_modelguided_init)

Applied the Phase 2f coloring model to the remaining register-identity park fns in
src/game/auto_ONKARTHIT_block.c (CarObject_ProcessWarpAndDash, CarObject_Init,
KartItem_ApplyImpactReflectAndDampVelocity). Result: **0 promotes** — all three are
capped by a NON-coloring blocker (allocator-internal site-ordinal swap, structural
-1 insn, and an int-equality-chain li-deletion respectively). The coloring model's
one new lever (merged-web -> shared reg) was REFUTED at the CarObject_Init ch web.
All mappings below are OBSERVED (objdiff per-row diffs on obj/ vs src/); interpretation
marked HYPOTHESIS. Budget: 6 builds total across the 3 fns.

### CarObject_ProcessWarpAndDash 0x8004D1A8: parked 94.60% (self/mov swap, not coloring-lever-movable)

Reproduced the prior batch's 94.60% from the paste-ready C on build 1 (2 typed-extern
+ view-struct edits, no surprises). The full diff is the documented self/mov swap
(~45 of ~49 rows) plus 2 scheduler gap slots that ride it.

OBSERVED target callee homes: self(param)=r31, mov(=self->movement, first local)=r30,
mgr(=WarpDashMgr_GetInstance result)=r29. Definition order in target asm is
self(`mr r31,r3`) -> mov(`lwz r30`) -> mgr(`mr r29`) = r31,r30,r29 DESCENDING in
def order, AND self (a param) ranks ABOVE the first local mov.

OBSERVED mine (every C form): mov=r31, self=r30, mgr=r29. CW ranks the first-defined
local `mov` -> r31 and demotes the param `self` -> r30. mgr=r29 matches both.

This is a DIRECT CONTRADICTION between two real fns under the same model:
- KartItem_CancelActiveEffect (round-1 standalone): param `self` colors LAST (r24
  below 7 locals).
- ProcessWarpAndDash TARGET: param `self` colors FIRST (r31 above the first local).
The param's rank is therefore NOT a fixed "params last" rule; it flips with fn
structure. The round-1 bisect (warp-only -> mov=r31; warp+dash -> mov=r30/target;
+mgr-block -> mov=r31; minus the 9-arg CalcExitPosition -> mov=r30) shows the swap is
governed by the presence/shape of the THIRD callee web (mgr) and the r8-consuming
9-arg call — i.e. the "(regime, site ordinal)" determinism, an allocator-internal
visit-order/counter artifact with no source handle.

NEW negative this batch (reconfirms model RULE on arg order): inlining the mov
assignment into arg-2 of the first call
(`WarpZone_CheckEntry(self->warpCtx, (mov = self->movement)->pos[0], ...)`) so that
the self-derived arg-1 is surface-first -> BYTE-IDENTICAL 94.60% output. Arg /
statement evaluation order does NOT re-rank the callee webs (consistent with
p1_argrev / p5 no-ops in the main batch). The swap is fixed at IR linearization, not
at the C surface. PARK; needs the colorer visit-order dump (system-1, proven stubbed)
or a frida hook on FUN_00579cf0 to crack.

### CarObject_Init 0x8004E618: parked 98.23% (structural -1 insn r0-join; coloring is secondary AND merge-lever refuted)

Reproduced the prior batch's 98.23% from the paste-ready C (full promote diff applied:
view structs, typed ctor externs, ScopedTimer recipe, uint-t idioms). OBSERVED real
insn counts: **mine 494, target 495 (1976 vs 1980 bytes)** — a hard -1 insn. The
fn CANNOT be byte-identical as C while it is 1 insn short, so coloring alignment is
moot for promotion.

OBSERVED the -1 site precisely (WarpAutoRun new-expr guard, objdiff rows 248-267):
```
target: bl AllocTagged; mr. r0,r3; beq L; <flag calc>; bl WarpAutoRun_Init; mr r0,r3; stw r0,0x54(r31)
mine:   bl AllocTagged; cmpwi r3,0;  beq L; <flag calc>; bl WarpAutoRun_Init;          stw r3,0x54(r31)
```
The target holds the new-expr object pointer in a DEDICATED r0 temp across the guard
(`mr. r0,r3` to test, `mr r0,r3` to re-capture the ctor result) = 2 insns. Every CW
1.3.2 C spelling copy-propagates the pointer to its r3 home and tests/stores r3
directly = 1 insn. This is the "new-expr precan class" from the prior HANDOFF, now
pinned to exactly 2-vs-1 insns. Confirms: structural, source-closed at -O4,p in C;
needs binary-level patch or a compiler revision that emits the r0-resident new-expr
temp. (Prior probes 8/9/12/13/14 — 2-var copy, assign-in-cond, shared int w, explicit
post-call copy, test-on-w — all reconfirmed copy-propagating; not re-burned here.)

COLORING residue (secondary, would still mismatch even at +1 insn):
OBSERVED target dynamic-web homes (RULE4 reuse of freed param regs):
ch=r26, movement=r26(reuse), driver=r25, camera=r25(reuse), blk=r27, sub=r23,
mgr=r23(reuse). Param prologue homes: self=r31, kartSlot=r23, a5=r24, a6=r26,
a7=r29, isPlayer=r30, slotIdx=r28, camArg=r27, flag21=r25 (a SCATTERED order, not
r31-descending — params interleave with the dynamic webs by interference).
OBSERVED mine: ch=r25 (want r26), blk=r29 (want r27), sub=r27 (want r23),
mgr=r27 (want r23).

**MODEL LEVER REFUTED (the merged-web -> shared-reg corollary):** predicted that
coalescing the ch (audio-channel) web with the o1 (movement) web would make both
take r26 (RULE4 reuse, as target does). Made ch reuse the `o1` variable
(`o1 = AllocTagged(0x38); ...; self->soundCtrl = o1; o1 = AllocTagged(0x324); ...`).
OBSERVED: BYTE-IDENTICAL — ch stayed r25, no movement to r26. So variable-identity
coalescing does NOT move a dynamic web's home when the home is pinned by the
param-interference graph; the GetMaxSpeed "merge -> demote" result does NOT
generalize to "merge -> adopt sibling's reg" in the callee pool. The ch/blk/sub/mgr
homes are fixed by which param regs are dead at each alloc point (a liveness fact of
the param stores + volatile-aux hoists), not by local variable identity. This is the
"source-closed tie-break" the prior HANDOFF reported, now with a clean refutation of
the merge lever. PARK.

### KartItem_ApplyImpactReflectAndDampVelocity 0x8004B140: parked 95.19% (int-equality-chain, not a coloring problem)

NOT attempted this batch beyond confirming it is the int-equality-chain li-deletion
class (NOT register identity). The coloring model has no bearing: the residue is a
hoisted `li r6,0` with the 4 arm `li 0`s deleted, which the prior 4-probe ledger
showed requires `b` to coalesce with an INDEPENDENT live zero web (the u64 mask half
in the class-1 u64 sites) — a value-numbering/coalescing precondition this site lacks.
No new source lever from the coloring model. Left at asm (100%).

### RULE 1-4 scorecard update (round 2)
- RULE 1 (bl-crossing -> callee): still CONFIRMED.
- RULE 2 (decl-order ranking) / RULE 3 (param rank): the warp self/mov swap is a
  STANDING COUNTEREXAMPLE to any fixed param-rank rule — params can color FIRST
  (warp target self=r31) or LAST (CancelActiveEffect self=r24) in real fns; the
  determinant is the callee-web set composition (site ordinal), not decl order.
  Arg/statement order reconfirmed irrelevant (warp inline-assign no-op).
- RULE 4 (disjoint reuse): CONFIRMED in CarObject_Init (target reuses r26/r25/r27/r23
  across disjoint object lifetimes), BUT the reuse TARGET reg is not steerable by
  source-level variable coalescing (ch=o1 merge no-op) — reuse picks by param-reg
  liveness, which is fixed by the (matched) field-store structure.
- merged-web-colored-last corollary: CONFIRMED only where the merge DEMOTES a web to
  the lowest free reg (GetMaxSpeed mv->r7). REFUTED as a tool to make a web ADOPT a
  specific sibling reg in the callee pool (CarObject_Init ch).

### Net
The coloring model is predictive for WHERE webs land but does NOT expose a source
lever to RE-STEER a callee web's home when that home is pinned by the
param-interference / liveness graph (which is itself fixed by the already-matched
surrounding code). The two remaining promote routes are both compiler-internal:
(1) the colorer visit-order dump (system-1, stubbed — dead) or a frida hook on the
Coloring.c select step (FUN_00579cf0); (2) for CarObject_Init specifically, the
new-expr r0-temp is a codegen-shape gap unrelated to coloring. Do NOT re-burn
source-permutation budget on warp self/mov or Init ch/blk/sub/mgr.

## In-TU validation round 3 -- OnKartHit gate is PINNED (2026-06-11, batch_frida_onkarthit_lever + concurrent independent run)

Judged whether KartItem_OnKartHit 0x8004A238 (prefix index 0, the Phase-3 A-region
gate) parks at 96.38% because the GPR partition is under-constrained (source-movable)
or pinned. TWO independent runs reached the SAME verdict: PINNED by param-interference,
0 promote. The shipped compiler was untouched (private-copy frida hook; SHA-1
re-verified). Caveat on provenance: a second agent was probing the same OnKartHit task
in the same worktree concurrently (not orchestrator-dispatched; no cron was running);
both built race-immune harnesses outside the worktree and converged.

OBSERVED (frida, FN#0 class-4 GPR step; key = web-birth [+0x10], home = [+0x14],
adjN = interference degree):
- self (PARAM) = key32, home r26, adjN 135
- victim (PARAM) = key33, home r27, adjN 137
- bus (local) = key52, home r30
- rm (local) = key94, home r31
- 5 coalesced bool/reuse webs (keys 46..51) fill r25/r28/r29.
TARGET wants self=r30, victim=r31 (the two PARAMS at the TOP of the callee pool),
bus=r25, rm=r29, bools in r26..r28. The colorer pops the select stack in descending
key and assigns r31-descending; the two param webs have the LOWEST callee keys (32/33)
AND the MAXIMUM interference degree (live across the whole fn, adjN 135/137), so Briggs
simplify can only push them last -> colored last -> lowest callee regs. To outrank the
locals the params would need a LOWER degree, which their (already-matched) whole-fn
usage forbids.

EXPERIMENTS (3 levers, all negative on the param/local boundary):
- def-order / local decl reorder: moves locals AMONG themselves (rm key 94->65;
  bus r30->r28) but the param homes stay r26/r27 and the boundary does not move.
- param-as-local-copy (`self=selfP; victim=victimP;` born first, signature params
  renamed): BYTE-IDENTICAL 96.38% in both runs -- the copy coalesces straight back
  into the incoming-param web (param-merge), so the param web identity (lowest key,
  max degree) persists. This is the strongest negative: the most direct "birth params
  first" signal does nothing.
- defer bus birth (move `bus = ...` into the `if(ok)` block to free the early high
  slot): 95.43% (adds a bus reload), params STILL r26/r27. Freeing an early local slot
  does not raise the params.

CONSEQUENCE: OnKartHit is the 3rd independent real fn (after CarObject_Init,
ProcessWarpAndDash) where the register-identity park is pinned by the
interference/liveness graph rather than a source-movable web-birth order. The frida
MODEL (web-birth key descending) predicts WHERE webs land but does NOT expose a source
lever to re-rank a MAXIMAL-DEGREE param web. Downstream symptoms (callee-saved-bool li
coalescing, vcall r6-vs-r12, fp f3/f5) all ride the same partition. The Phase-3 gate
(prefix index 0 = OnKartHit) cannot be opened from any source lever tried so far.
Raw rows + experiments: tools/compiler_probe/colorer_observation.log (IN-TU PROBE).

OPEN (the only untried direction): all three levers attacked web-birth ORDER. None
attacked the param's interference DEGREE -- i.e. a source restructuring that makes
self/victim NOT live across the whole fn (hoist their needed fields into early locals
and let the param itself die, or split the tail into a helper so the params' live range
shrinks). The frida observation says degree, not key, is the pin; this degree-reducing
direction has not been probed and is the next candidate before declaring source-closed.

(2026-06-11 訂正: この OPEN 方向は Fable recheck で全 negative — degree は pin ではない。
末尾の「Fable recheck」節参照。)

## CarObject_HandleItemEffect handled-web, source-lever exhausted (2026-06-11, batch_promote_hie_lateweb)

Re-attacked CarObject_HandleItemEffect 0x8004F858 (parked 99.93%, residual = single
`handled` web, target r22 vs ours r29) with the frida-named "late-born non-foldable
handled" lever. Verdict: REFUTED, 0 promote, 7 builds. (No frida used; pure
source-level investigation.)

NEW OBSERVATION that resolves the old two-regime confusion: in the 99.93% baseline obj
is ALREADY r29 (regime A achieved via the open-coded ApplyDriftBoost extern call -- a
real `bl`, NOT an inline splice, so obj is never renumbered). ApplyDriftBoost is a
standalone matched fn (0x8004F450), so handled = ApplyDriftBoost(obj,...) is a plain
call; the note's worry that "a substantial helper demotes obj" does NOT apply here. The
param r31/r30 "contradiction" also does NOT manifest -- params are correct on every row.
The ONLY residual is handled's home register.

REFINED MECHANISM (OBSERVED): handled is a SINGLE phi-web in both target and ours (every
write uses one reg). It is not a fold/split problem. The divergence is the move-coalescer:
in the drift cases ours emits `mr r29, r0` (coalesces handled into obj's just-freed r29);
target emits `mr r22, r0` (no coalesce). The coalescer's choice is driven by the global
interference graph; six source perturbations could not redirect it (non-const SSA source
for handled; killing the pre-switch live range; dropping the explicit obj local; forcing
handled live across the obj-load+call via `handled & call()` -- all either repartition
everything or leave handled at r29). Probe B (handled tied to `found`) proves handled CAN
move but only by reshuffling all of r22..r29 -> loses the loop-local match. The partition
is fully constrained; the one residual web is NOT source-movable. Strongest in-fn
confirmation yet of the "source lever works only for under-constrained webs" limit. Keep
as matched asm; 99.93% C form preserved in tools/compiler_probe/p2e_handleitemeffect_9993.patch.


<!-- MERGE 2026-06-12: 並行した 2 ライン (main follow-up 2-12 = degree/cost/inline 実験 arc,
と recheck 枝 = instr-match 撤回 + 本セッションの colorer decompile/一般化回答) を統合。
下記はまず main の follow-up arc (時系列的に先, 18:14〜)、続いて recheck 枝 + 本セッション
(20:17〜 + 06-12) を時系列順に並べる。両者は同一問題への独立探索で内容は相補的。 -->

## Fable recheck: degree-reducing levers all NEGATIVE -- OnKartHit source-closed (2026-06-11, batch_fable_onkarthit_recheck2)

Round 3's OPEN direction (attack the param's interference DEGREE instead of
web-birth order) was probed with 4 structures from the 96.38% Appendix-B body,
objdiff-only (no frida, no compiler contact): (1) hoisting victim's tail fields
(dispatcher/state1f4) into pre-memset locals dropped match to 92.54% and moved
the params DOWN (r25/r26) -- the two new late-born webs outrank them; (2) late
param copies placed just before memset coalesce straight back (param-merge) and
are BYTE-IDENTICAL to baseline, generalizing round 3 lever 2: copy position is
irrelevant, the merged web keeps the param identity; (3) volatile-slot copies
(coalescing physically broken; disasm-verified both param webs die at the stw
at ~63% of the fn, zero interference with the entire bool/memset/mtx/dispatch
tail) leave homes EXACTLY at r26/r27 (87.36%); (4) splitting the whole tail
into a non-inlined static helper (params die at the call) shrinks the callee
set and the params stay at its BOTTOM (r27/r28 of an r27-based pool, 52.82%).

CONSEQUENCE: degree is NOT the pin -- no amount of live-range reduction
re-ranks a param web, and adding/removing callee webs only shifts the params'
absolute register while preserving their bottom rank. The coloring position of
param webs is fixed by their identity (lowest web-birth keys 32/33), refuting
round 3's open hypothesis. OnKartHit is source-closed within C: the
params-on-top partition (self=r30/victim=r31) is unreachable from any tried
source shape. Only untried route is outside C source space: the original is
C++ (extab references dtor_80036E40; vcall residue r6-vs-r12 also hints at
real virtual dispatch), and C++-specific web construction (this-call method
form, reference params, real virtual calls) has never been probed against the
GPR partition (Phase 2b's C++ negatives were class-2/frsp only). That probe is
the LAST candidate before declaring the family fully closed. Probe harness:
batch_fable_onkarthit_recheck2 worktree tmp/ (apply_and_measure.py, make_e3.py,
make_e4.py, restore_baseline.py).

## C++-form probe: register-identity family closed in BOTH C and C++ (2026-06-11, batch_fable_onkarthit_recheck2 follow-up)

The last untried axis from the Fable recheck (C++-specific web construction) was
probed with a standalone harness (worktree tmp/cpp_probe_run.py: compiles a
single-fn TU with the production game_extab flags, dtk-disasm-based comparison
so mangled C++ symbols work; P0 C-baseline validated to reproduce the in-TU
instruction stream and partition exactly). Six variants, all measured on the
96.38% body:

- P1 (C, full prototypes), P2 (-lang=c++ free fn), P3 (this-call method form),
  P4 (real virtual dispatch, base-less class), P4b (virtuals on a polymorphic
  BASE class -- vptr at 0x0, every field offset byte-equal to target), and
  P5 (reference param): **homes self=r26 / victim=r27 / bus=r30 in ALL of
  them** (target r30/r31/r25). The GPR callee partition is invariant across
  the entire C and C++ source space tried.

VERDICT: the register-identity park family is CLOSED at the source level,
in both languages. Phase 3 gate (prefix index 0 = OnKartHit) stays shut.

Two byproducts that matter beyond OnKartHit (OBSERVED):
1. Real C++ virtual dispatch emits the TARGET vcall shape -- `lwz r12,
   0x0(rX); lwz r12, 0x8/0x34(r12); mtctr; bctrl` (r12-chained, both loads).
   The C explicit-vt-struct spelling emits an r6 intermediate (`lwz r6,
   0x0(rX); lwz r12, +off(r6)`) -- i.e. the recurring "vcall r6-vs-r12"
   residue is a C-source artifact, fixable by compiling the TU as C++ with
   real virtual classes. Any parked fn whose ONLY residue is vcall shape is
   unlockable this way.
2. CW 1.3.2 places the vptr of a base-LESS polymorphic class at the END of
   the object (0x108 for the KartItemHit probe). The shipped binary has
   vptr at 0x0 with members after, which under CW 1.3.2 requires the class
   to DERIVE from a polymorphic base (P4b shape). Layout guidance for any
   future C++ reconstruction of the game class hierarchy.

Probe files: worktree tmp/probe_p0.c..probe_p5.cpp, probe_p4b.cpp,
probe_common.h, probe_common_virtual.h, cpp_probe_run.py.

## 訂正 + inline-composition probe: partition は動く、param-class flip pair も発見 (2026-06-11, batch_fable_onkarthit_recheck2 follow-up 2)

**訂正**: 直前節の「register-identity family は C/C++ 両 source 空間で CLOSED」は過大だった。
正しくは「**open-coded な (1 枚岩で書いた) C/C++ 形では到達不能**」まで。inline splice が web key を
振り直す機構は HIE regime B で観測済みだったのに、composition (inline helper から locals を born
させる) 軸を probe せずに closed と書いた。以下この軸の probe 結果 (全て OBSERVED、
standalone harness + in-TU tu_probe.py)。

### I1/I3: inline-splice composition は partition を動かす最初の lever

bool quad を `static inline unsigned char FlagBit(u64 f, u64 mask)` accessor に変えただけ (I1) で:
- **partition が初めて動いた**: bool 群が callee pool 上位へ昇格 (spliced web が高 key を取得)、
  bus/param が押し下げ。返り値 merge は spliced 側の key を採用する (param-merge と非対称)。
- **行数が 416=416 で target と一致** — callee-saved-bool li-coalescing 残差 (gap 4 行) が解消。
  callee-def 14 行が target と 1:1 対応、b26=fresh / b25=bus の coalesce 構造も一致。
- I3 (I1 + C++ method + real virtual) で vcall r12 残差も同時解消、71.15% (difflib LCS)。
- **残差は「param 組 vs locals」の class 単位 permutation ただ 1 つ**に縮約。locals の相対順位
  (rm > b28 > b27 > fresh > bus) は target と完全一致。

### TU 全 fn scan: param 配置は per-fn にバラバラ、両極とも plain C で再現済み

target TU の stmw 持ち 18 fn の prologue を scan (tmp/scan_param_class.py): param home は
TOP (OnKartHit r30/r31, HIE r30/r31, OnFallOffOrDeath r31, StlList_RemoveByValueField r30/r31,
Bitset_Init) / BOTTOM (CancelActiveEffect r24, ItemEffect_OnHit r22-24, Dispatch r27-29) /
MID-MIX (OnItemHit r28/r29/r23, Init r31/r23, TryStartByCategory) が混在。**OnFallOffOrDeath
(TOP) と CancelActiveEffect (BOTTOM) はほぼ同一構造のコードで、両方とも我々の plain C で
matched 済み** — つまり compiler は同一、配置は source 構造の関数で、両極とも到達可能。

### flip pair bisect: OFOD の sec web が param-class を flip する

- OFOD から sec block (`sec = self->secondary; if (sec->itemId >= 0) {3 calls}`) を削る →
  **self が r31 から r24 (bottom) に転落**。
- 第 1 文の param store (`self->fellOffFC = 1`) は無関係 (移動/追加とも不動)。
- strPcb tail 削除も無関係 (r31 のまま)。
- sec の出生元を global に変えても r31 のまま (99.43%) — **param 派生である必要は無い**。
  lever は「遅生まれ・call-crossing・callee pointer web の存在」(文脈依存、下記)。

### I5: OnKartHit への単純移植は NEGATIVE

sec-analog (global 由来の遅生まれ call-crossing pointer web) を OnKartHit に足しても
param は r25/r26 (bottom) のまま。flip 条件は単一 web の存在ではなく web 集合の構成に依存する。

### 統合 (仮説)

元 binary は普通の C++ を普通に compile したもの。param 配置は web 集合構成で per-fn に決まり、
原文の inline helper 合成 (accessor 多用) が web key 構成を我々の open-coded 再構成と変えていた、
が最有力。OnKartHit の残課題は「param-class を top にする web 集合条件」の特定 1 点に絞られた。
次の bisect 軸: OFOD と CAE の transplant matrix (CAE に sec block を足す / OFOD を CAE 形まで
削る) で flip 条件を最小化 → OnKartHit の I3 形に適用。

Probe assets: worktree tmp/ (probe_i1.c, probe_i3.cpp, probe_i5.c, scan_param_class.py,
homes_detail.py, tu_probe.py + transform 群)。

## OFOD-CAE transplant matrix + 再解釈: param rank は per-web、key model は不完全 (2026-06-11, batch_fable_onkarthit_recheck2 follow-up 3)

### transplant matrix (in-TU tu_probe.py、全て OBSERVED)

| probe | 内容 | self home | 判定 |
|---|---|---|---|
| M1 | CAE + OFOD の sec block 丸ごと | **r31 (TOP に flip)** | lever は sibling 間で transfer する |
| M2c | CAE + 最小 late web (新規 call ゼロ、既存 call 2 本を跨ぐだけ) | r24 | 存在だけでは flip しない |
| M2d | CAE + sec + 無条件 call + store (branch なし) | r24 | branch なしは flip しない |
| M2a | CAE + sec + **if** + call 1 本 + store | **r31 (flip)** | **最小 flip 形 = 遅い条件 block + 内部 call + tested web** |
| I8 | OnKartHit + dispatch 後に self 使用 | r26 | OnKartHit へは transfer せず |
| I9 | OnKartHit tail を static inline helper 化 (inline 成功、416 行) | r25 | **param-merge は splice 境界でも param key を保持** (E2 / GetMaxSpeed と一貫。I1 の返り値 merge が spliced key を取るのと非対称) |

OnKartHit には M2a 形 (fresh の if + 内部 CoinSystem_RemoveCoins call + 後続 self 使用) が
baseline から存在するのに bottom — M2a 条件は CAE/OFOD 文脈でのみ十分条件で、一般条件は未特定。

### 再解釈 (重要): 「param-class flip」という枠組みが誤り

TU scan を見直すと、target では **同一 fn 内で param が分裂配置**される:
- CarObject_HandleObstacleHit: r3→r30 (上から 2 番目)、r4→**r22 (最下位)**
- CarObject_OnItemHit: r3→r28, r4→r29 (中位の連続)、r5→**r23** (離れて下位)
- CarObject_Init: r3→r31 (最上位)、r4→r23 (最下位近く)

つまり param は class として一括順位付けされるのではなく、**個別 web として locals と同じ
順序列の任意位置に挿入される**。「param = 最低 web-birth key (32/33) → 常に最後に着色」の
key model は、open-coded source からこの分裂配置を生成できない — **frida で観測した
key-desc 順は (その source 形での) 部分像で、順序を決める未知の成分が残っている**
(degree は E 系で否定済み、locals 間の decl 順 RULE2 は引き続き成立)。

### 次 batch 仕様 (これが本命の研究 instrument)

1. **whole-binary prologue scan**: build/GNLJ82/asm/ 全 TU で「param home の rank vs fn 特徴
   (callee web 数 / loop 有無 / call 数 / fn size / param 数)」の相関 dataset を作る
   (tmp/scan_param_class.py の一般化、~数百 fn)。param rank を予測する規則の発見が目標。
2. CAE+M2a (flip ✓) を OnKartHit 形へ morph して flip が死ぬ成分を特定する (逆方向 morph)。
3. 規則が見つかったら OnKartHit I3 形 (416 行一致、残差 = この順位 1 点) に適用 → promote。

probe assets 追加: tmp/t_cae_plus_sec.py, t_cae_m2a.py, t_cae_m2c.py, t_cae_m2d.py,
probe_i8.c, probe_i9.c (+ make_i9.py)。worktree green 維持 (tu_probe は毎回 TU を復元)。

## whole-binary param-rank scan: renumbering は日常、key model の適用限界を定量化 (2026-06-11, batch_fable_onkarthit_recheck2 follow-up 4)

instrument: tmp/scan_binary_params.py (build/GNLJ82/asm 全 TU、stmw fn の prologue から
param copy の home を抽出)。dataset: tmp/param_rank_scan.tsv (672 fn / 1260 param copies)。

OBSERVED:
- param の配置分布はほぼ一様: top2 35% / mid 33% / bottom2 32%。粗い特徴量
  (CTR loop 有無 / call 数 / fn size / pool size) との相関はどれも弱い (最大でも
  manycalls→top の +0.15)。**決定的な粗視化特徴は存在しない**。
- r3/r4 両方を copy する 237 fn の内訳: **57.0% が「r4 が r3 の 1 つ上」の隣接 pair**
  (OnKartHit target と同形 = pair 内は key 降順)、7.2% が逆順隣接、**35.9% は分裂**
  (gap 2-11、locals が param 間に割り込む)。
- 我々の open-coded 再構成は常に「locals 全部 > params」の正準形を出す。binary は
  params の位置が一様に散る。

解釈 (仮説、高確度): web-birth key は IR pipeline の処理順で振られ、optimizer の各 pass
(inliner splice は観測済み、他にも value numbering の再走等) が web を param key (32/33) の
前後任意の位置に renumber する。整数 key の間に locals が割り込む分裂 35.9% は renumbering が
日常的である直接証拠。原文 (inline accessor 多用の C++) と open-coded 再構成の差はここに出る。
粗視化特徴で予測できない以上、**規則の同定には IR レベルの観測が必要**。

次 batch 推奨: Phase 2f-2 で確立済みの IR dump (private copy の 1-byte patch、53 pass の
named IR、frida 不要・shipped compiler 無傷) を使い、OnKartHit の我々の source 変種
(baseline / I1 / I3 / I9) の web 生成順を pass ごとに比較 → param rank を動かす pass と
source 条件を特定する。当たれば I3 形 (残差 = 順位 1 点、行構造 416=416 一致) が落ちて
Phase 3 gate 再オープン。

assets: tmp/scan_binary_params.py, tmp/param_rank_scan.tsv, tmp/pair_adjacency.py。

## IR-dump 検証 + session 境界: rank rule は frida channel 必須と確定 (2026-06-11, batch_fable_onkarthit_recheck2 follow-up 5)

Phase 2f-2 の IR dump (private copy 1-byte patch、enable_ir_dump.py) を初めて**実関数規模**で
検証した。shipped compiler は無傷 (SHA-1 d8f9c36d... 前後確認、patched copy は実験後削除)。

OBSERVED:
- OnKartHit (0x680) で dump 発火: **76 pass dumps、209k 行** (probe_p1.log)。banner の pass 名は
  空白入りがある ("Copy and constant propagation" 等) — パーサは行末まで取ること。
- I1 (inline FlagBit) の dump では **b25-b28 が最終 IR から named operand として消滅**
  (spliced 返り値 temp に吸収) — I1 で bool 群が昇格した機構の IR レベル可視化。
- 最終 pass の named-operand 出現順は coloring 順と単調対応しない (P1 で検証:
  IR 順 self,bus,ok,victim,rm,... vs coloring 順 rm,bus,fresh,b26,victim,self,b25)。
  **dump は pre-codegen で web key を含まない** — note 既載の caveat を実データで確認。
  IR-dump 経路では rank rule に到達できない (この経路は closed)。
- 追加 negative: `register` storage class hint は -O4 で完全無視 (R1、bit 単位で baseline 同一
  homes)。axis closed。
- 補足: frida round-3 の key 表 (bus=52 > bools=46-51、bus が textually 先なのに key が上) は、
  key が source 出生順ですらないことを既に示していた。key は codegen 内 VN の産物で、
  source からの予測規則は依然未知。

結論: param rank rule の同定に必要な観測 (web key を colorer 直前で読む) は **frida hook
channel のみ** (Phase 2f-3 で実証済みの手法)。本 session は frida 不使用の制約があるため
ここが境界。素材は揃った:
- I3 形 = 行構造 416=416 一致、残差は 7-web permutation 1 点
- 比較対象 source 変種一式 (P1/I1/I3/I9 + E/M 系) と各 homes 実測値
- whole-binary rank dataset (param_rank_scan.tsv)

次 batch (frida 可の session で): frida_colorer_probe.js の手法で P1/I1/I3 の web key を実測 →
「source 編集が key をどう動かすか」の差分表を作る → I3 の permutation を target
(victim>self>rm>b28>b27>fresh>bus) に置く key 構成を逆算 → promote。

## frida colorer 直接観測 — OnKartHit park の機構を runtime で確定 (2026-06-11, batch_fable_onkarthit_recheck2 follow-up 6)

verified colorer reader (tools/compiler_probe/frida_colorer_probe.js、Phase 2f-3 手法) を
OnKartHit probe 群に初適用。private copy spawn・runtime hook のみ、shipped compiler は無傷
(SHA-1 d8f9c36... 前後確認、tmp_probe は実験後削除)。driver: tmp/colorer_run.py、
解析: tmp/clique.py / tmp/tu_cliques.py。

### OBSERVED: param web key は構造的に最小・不変

- P1/I1/I3/I9 全変種で **self=key32 / victim=key33** で完全固定。inline splice は bool 群の
  key を振り直す (I1: bools 61-68、I3: 57-64) が param key には一切触れない。
- 合成 probe (tmp/syn_firstuse.c): param を**最後に使用**しても key 32/33 のまま、late-born
  locals が key 34-38。**key は first-use 順ではなく entry 順、param は最小 key に pin**。
  これで round-3 以来の「param を late born させる source lever」探索が原理的に閉じた:
  incoming param web の key は source で上げられない。

### OBSERVED: pop 順は descending-key ではなく dynamic Chaitin simplify

- OnKartHit P1 の callee clique pop 順 = rm(k94,adjN102) > bus(k52,77) > bools(k47-51) >
  victim(k33,**adjN137**) > self(k32,**adjN135**)。self/victim は **clique 最大 degree かつ最小
  key** で最後に pop → r26/r27 (最下位)。
- 反例 OnItemHit (matched C、step1 webCount=132): pop 順 = k52(adjN49) > k51(48) >
  **victim k33(adjN29) > self k32(adjN90)** > [gap] > locals k34-50。**param が中位 (r28/r29)**、
  local 群 (key は param より高い 34-50) が r22-r27 で param の**下**。
  → pop 順は単純な key 順でも degree 順でもなく、**dynamic simplify-stack 順** (低 dynamic-degree
  ほど早く stack 底へ → 最後に pop → 低 reg)。clique が degree 一様 (合成 probe) のときだけ
  descending-key に縮退する。

### 機構の確定 (OBSERVED + 仮説)

OnKartHit の self/victim が最下位なのは **(a) 最小 key (param 固定) と (b) 最大 degree (entry〜
末尾 virtual dispatch まで全域 live) の同時成立**。target は同じ self/victim を r30/r31 (最上位) に
置く = pop 最初 = この clique で最後まで simplify されず残る = それには degree が「途中で密なまま
残る」特定構造が要る。OnItemHit で param が中位に乗れたのは victim の degree が 29 と低い
(末尾まで live でない) ため。**OnKartHit で self/victim を top-2 に乗せるには degree を OnItemHit
並みに下げる必要があるが、両者とも末尾 dispatch で param を直接使うため source 上 degree を
下げられない** (E1 の tail-field hoist は新 high-key web を生んで逆効果、E3/E4 の degree 削減は
param web が clique に残留)。

### 結論

- **promote 0**。ただし「C/C++ source-closed」とは断定しない: OnItemHit が param-mid を実証して
  おり、param が最下位に固定なわけではない。**未達は「self/victim を同時に top-2 に乗せる
  degree 構造」が source 上で作れていない 1 点**に絞られた (round-3 の degree 仮説は「degree が
  pin」までは正しく、「degree を下げれば動く」が実装上不可能、が精密化された結論)。
- 機構は frida で完全に runtime 観測済み: web key の source 不変性 + dynamic simplify pop 順 +
  degree が reg を決める、の 3 点。これ以上の lever は colorer の simplify-stack 構築規則
  (FUN_00507b50 の low-degree 除去順) を step 単位で追う必要があり、本探索の費用対効果境界。

assets: tmp/colorer_run.py, clique.py, tu_cliques.py, syn_firstuse.c, syn_ptr.c,
colorer_{P1,I1,I3,I9,E3,SYN,SYNP,TU}.log。

## colorer simplify 規則を逆アセンブルで導出 — OnKartHit の descending-key を機構確定 (2026-06-11, batch_fable_onkarthit_recheck2 follow-up 7)

follow-up 6 の「dynamic Chaitin で degree が効く」を、FUN_00507b50 (simplify-stack builder) の
逆アセンブル (llvm-objdump) + push サイト trace で規則レベルまで詰めた。

### OBSERVED: FUN_00507b50 のアルゴリズム (逆アセンブル)

- threshold k = `call 0x4fd650(class)` を `[esp]` に保持。
- main loop (0x507b82-0x507be3): node index ecx を lowReg→webCount で走査。各 node の
  degree `[+0x12]` を k と比較。**degree < k なら trivial 除去**: 隣接の degree を decrement
  (0x507ba1 loop)、flag 0x2 set (0x507bbc)、ebp stack に prepend (0x507bc1-3)。
  **degree >= k なら ebx leftover list へ** (0x507bd0)。
- leftover が残れば spill-pick section (0x507c02-0x507caa): 各 node の **ratio = degree/cost
  (`[+0x12]` / `[+0x0c]`、fild+fdivrp)** を計算、最小 ratio の node を 1 個 optimistic-spill 除去
  して ebp へ。degree>=k の node は ratio を定数 `[0x5bbb24]` (= +inf 相当) に置換。
- SELECT (FUN_00507a30) は ebp の **head (= 最後に push = 最後に除去)** から着色、各 node に
  最低番号の空き reg を割当。

→ **除去順 = ebp push 順、着色順 = その逆 (head-first)**。最後に除去された node が最初に着色 =
最高 reg (r31)。最初に除去された node が最後に着色 = 最低 reg。

### OBSERVED: OnKartHit は graph が k-colorable → 除去は昇順 key、着色は降順 key

push サイト trace (tmp/frida_simplify_probe.js、0x507bbc/0x507ca1 hook):
- **spill 除去はゼロ**、全 node が trivial 除去。dyndeg=90 (key94) でも trivial =
  **k は large (> 90)**。OnKartHit の interference graph は spill 不要 = k-colorable。
- 除去は **node index (key) 昇順** (seq0=key34, seq1=key35, ... 単調増加)。main loop の
  ecx 昇順走査そのまま。
- ∴ ebp は key 昇順 push = head が最高 key。SELECT は head から = **着色は key 降順**。
  これが follow-up 6 で見た clique color order = descending key (94,52,51,50,49,47,33,32) の
  正体。callee に乗る高 degree node が key 降順で r31→r25、param (key32/33 = 最小) が最後 →
  最低 callee reg (r26/r25)。

### 導出された OnKartHit park の機構 (CONFIRMED)

1. value-numbering で incoming param web は最小 key 32/33 に固定 (follow-up 6 の syn_firstuse で
   first-use 順を否定済み、source 不変)。
2. OnKartHit の graph は k-colorable → simplify は key 昇順除去 → SELECT は key 降順着色。
3. ∴ param (最小 key) は必ず最後に着色 = 最低 callee reg。target の self=r30/victim=r31 は
   param が最高 key であることを要求するが、(1) によりこれは生成不能。

**= OnKartHit の param-bottom は k-colorable graph + 最小 key param の合成として機構的に閉じている**。
round-3〜follow-up 5 の探索 (degree 削減 / inline / C++ / transplant) が全て効かなかった理由が
これで説明される: どれも param の key を上げられず、graph は常に k-colorable のまま。

### 残る非自明: OnItemHit はなぜ param-mid か (未完)

OnItemHit (matched) は color order が降順 key でない (52,51,33,32,50,...) = param が中位。
これは (a) graph が非 k-colorable で spill-pick が ratio 順に並べ替える、または (b) coalescing が
param を別 key の web に統合する、のいずれか。OnKartHit との差はここ。ただし OnKartHit 自身は
k-colorable と確認済みなので、OnItemHit 機構を解いても OnKartHit には転用できない見込み
(OnKartHit を非 k-colorable にする = register pressure を spill するまで上げる source 改変は
命令列を破壊する)。

### 結論

OnKartHit は **k-colorable graph 上の key-降順着色で param が最小 key に pin される** ため
source-closed。promote 0 だが、park の理由を **compiler の coloring アルゴリズムの逆アセンブルから
導出** した (黒箱の "register-identity park" が完全に white-box 化)。Phase 3 gate は機構的に閉。
これは register-identity family 全体 (同じ k-colorable + 最小 key param 構造を持つ park fn) に
適用される一般原理。

assets: tmp/frida_simplify_probe.js, simplify_run.py, simplify_P1.log (partial),
colorer_P1cost.log。逆アセンブル根拠: FUN_00507b50 @ 0x507b50。

## 訂正: follow-up 7 の「機構的に閉」は誤り — spill-cost ratio が真の lever (2026-06-11, follow-up 7 訂正)

follow-up 7 で「k-colorable → 降順 key → param 最下位で source-closed」と書いたが**誤り**。
決定的反例: **target 自身が命令数同一 (416 行、余分な spill 命令なし = k-colorable) なのに
param が top (self=r30/victim=r31)**。OnItemHit (matched, param 中位) も同様。
∴ k-colorable graph でも param を上位に乗せられる。「全 trivial → 降順 key」は OnKartHit の
ある source 形でたまたま成立しただけで、一般則ではない。

逆アセンブル (FUN_00507b50 spill-pick section 0x507c02-0x507caa) を読み直すと真の規則が出る:
simplify が trivial 除去で行き詰まると、leftover の中から **ratio = degree/cost
(`[+0x12]`/`[+0x0c]`、後者は spill-cost numerator ≒ loop 加重の使用回数)** が**最小**の node を
optimistic-spill 除去する。最小 ratio = 先に除去 = stack 底 = **最後に着色 = 最低 reg**。

→ param が低 reg になる条件 = **degree/cost 比が小さい = degree 高 かつ 使用回数 (cost) 大**。
- OnKartHit self/victim: degree 最大 (135/137) **かつ self->X が ~20 箇所で使用回数も最大** →
  ratio 最小 → 最低 reg。
- OnItemHit param: degree 高だが**使用回数が相対的に少ない** → ratio 大 → 後で除去 → 高 reg。

**真の lever = param の使用回数 (spill cost) を下げること** (degree ではない。follow-up 5 の degree
削減が効かなかったのは degree が分子で、分母の cost を放置していたため)。これは未検証 = 次の実験軸。
仮説: self の頻出 sub-object (ownerDriver/movement/soundCtrl/vt) を関数冒頭でローカルに退避し
`self->` の直接使用回数を減らすと self web の cost が下がり ratio が上がって高 reg に動く可能性。
ただしキャッシュ先ローカルが uses を引き継ぐので、param web の cost だけ選択的に下げられるかが鍵。
Phase 3 gate は「閉」ではなく「この cost lever 次第で再オープンの可能性」に再訂正。

## cost lever 実検証 + 正直な総括 (2026-06-11, follow-up 8)

cost lever (param 使用回数を下げる) を C1 で実検証: self の sub-object (ownerDriver/movement/
soundCtrl) を冒頭ローカルにキャッシュし `self->` 直接使用を削減。
**結果: NEGATIVE。self は r26→r25 に逆に低下** (cache local od/mv/sc が高 reg を奪い、self が沈む)。
cost を下げても運ぶ web が競合する = E2/E3 と同じ罠。素朴な cost 削減は不可。

### 未解決の核心 (正直な現状)

target は **命令数ほぼ同一 (416 行、register 番号のみ差) で param top**。命令列が同じなら
interference graph・degree・cost・use-count も同じはずで、coloring も同じになるべき。唯一
異なり得るのは **web-birth key (value-numbering 順、source 式構造依存で最終命令列に出ない)**。
だが param key は entry 順で 32/33 固定 (syn_firstuse で実証) = source で上げられない。
→ **「命令同一・key 固定なのに target は param top」という矛盾が未解決**。coalescing 方向か、
simplify の未観測な tie-break が残っている可能性。~30 実験 + colorer white-box 解析でも
source 形は未発見。

### 結論 (確定事項と未確定の分離)

- **確定**: colorer は graph-coloring (FUN_00507b50 simplify + FUN_00507a30 select)、param web は
  最小 key 32/33 固定、k-colorable graph では概ね key 降順着色。これらは逆アセンブル + runtime で
  white-box 確定済み。
- **未確定**: target の param-top を生む source 形。"source-closed" とも "到達可能" とも断定できない
  (follow-up 7 の「閉」は撤回済み、本 follow-up 8 で「未解決」が正しい状態)。
- **build 状態**: OnKartHit は asm_fn で **既に byte-identical (SHA-1 OK)**。未達成なのは「clean C
  decompile を持つ」点のみで、build/match は完成済み。

### 推奨 (ROI)

OnKartHit 1 関数に round-3 以降だけで ~40 実験を投入。clean C 化の ROI は極めて低い。
**asm_fn のまま keep し (既に byte-identical)、他 TU の pending fn (1-6 build で match する mega-bundle
本流) に pivot する**のが妥当。colorer の white-box 知見 (k-colorable 判定 = param park の早期予測)
は他の register-identity park fn の **撤退判定の高速化**に再利用できる = 本探索の実利成果。

## degree lever 確定 — multi-pass simplify model + family 診断 (2026-06-11, follow-up 9)

follow-up 8 の「閉/未解決」から前進。**正しい coloring model を確定し、param-park を動かす lever を
実証**した。spill-only tracer (tmp/frida_spill_probe.js、低頻度サイト 0x507ca1 のみ hook で
crash 回避) で TU 全 57 関数を観測。

### OBSERVED: 真の model = multi-pass simplify (spill 不在)

- **TU 全関数で spill 除去ゼロ** = 全て k-colorable。しかし OnItemHit (param 中位) のように
  color order が降順 key でない関数が存在 → 「all-trivial = 純粋降順 key」は誤り。
- 正しい規則: simplify は **multi-pass**。各 pass で dynamic-degree < k の node を index(key) 昇順に
  除去。**高 degree node は degree が k 未満に落ちるまで複数 pass 生き残る → 遅い pass で除去 →
  早く着色 → 高 reg** (spill なしで)。k ≒ 91-100 (trace: dyndeg=90 は trivial 除去、adjN=102 は
  当初 deferred)。
- color order = pass 群 (遅い pass 順) × pass 内 descending key。
- OnKartHit: param (deg135/137) と rm(102)/bus(77)/bools(33-46) が相互干渉して**同一の最終 pass**で
  崩れる → pass 内 descending key → param (最小 key 32/33) が最後 → 最低 reg。
- OnItemHit: param が local より高 degree で**遅い pass**に分離 → param が上。

### OBSERVED: degree lever 実証 (D1/D2)

param ではなく **高 degree local の live range を削る** と param が上がる (従来の全 lever の逆):
- D1 (rm を 3 箇所で短命再計算に分割): **self r26→r27, victim r27→r28** に上昇。rm web が
  param の最終 pass から脱落。
- D2 (D1 + bus も短命化): self r27 で頭打ち。bus を剥がしても bools が壁。
- 天井 = **r27**。bools (key47-51、4 個) が dispatch で param と正当に co-interfere するため
  param の最終 pass に残り、within-pass descending key で param の上を取る。bools を volatile 化
  しないと param は r28 以上に行けない (bools は branch 選択に 4 個同時 live 必須で volatile 化困難)。

### family 診断 + lever (再利用可能な一般原理)

**診断**: param が低 reg に park する条件 = 「param より **高い web-key の callee local** が、param の
**最終 simplify pass で co-interfere** している」。これは frida colorer (clique の pop order + adjN) で
即判定できる。

**lever**: その co-interfere する高 key local の **live range / web 数を削り、param の最終 pass から
脱落させる**。local を早い pass で消せば param が繰り上がる。命令列を壊さずに local を短命化できる
関数なら promote 可能。

**適用限界**: param と最後まで正当に co-interfere する local (OnKartHit の bools のように branch 選択で
同時 live が必須なもの) は剥がせない = その関数は degree lever だけでは天井あり。

### OnKartHit 固有の残課題 (未解決、coalescing 未 trace)

決定的矛盾は未解決のまま: **target は self/victim を 1 回だけ書く単一 web (row4/5、reload なし)、
命令ほぼ同一・key 32/33・max degree なのに r30/r31**。同一 graph に決定的アルゴリズムが違う色を
付けている = model にまだ欠けた因子。最有力候補 = **coalescing** (simplify 前段 FUN_0057a1f0、
本探索で未 trace)。target の param が高 key web と coalesce して effective key が上がっている可能性。
次の一手: coalescing union-find を trace し、merged web の key 選択規則を読む。

### 結論

degree lever は確定・family 適用可。OnKartHit は bools の co-interfere で degree 天井 r27、
かつ命令同一で target が param-top を出す機構 (coalescing 疑い) が未解明のため依然 park。
ただし「park = 動かせない」ではなく「**動かす条件が判明**」した点が follow-up 9 の成果。
assets: tmp/frida_spill_probe.js, spill_run.py, make_d1.py/make_d2.py, probe_d1.c/d2.c,
colorer_D1.log。

## 訂正 — 「命令同一なのに param-top」の矛盾は偽の前提だった (2026-06-11, follow-up 10)

follow-up 8/9 で「target は命令同一 (register 番号のみ差) なのに param-top = 決定的アルゴリズムが
同一入力に違う出力 = model に欠けた因子」と書いたが、**前提が誤り**だった。

register 番号をマスクして target vs baseline(P1) を厳密 diff (tmp/reg_normalized_diff.py) した結果:
- **reg-masked similarity 92.11%、真の命令差 37 箇所** (register swap 以外)。命令は**同一ではない**。
- 内訳: **+4 個の `li rXX, 0`** (baseline は callee-saved bool b25-b28 の 0 初期化を明示 `li 0` で
  出す。target は branch-over `bne L; b L` で fold = class-1 li-coalescing 残差。行数 416 vs 420 の差)。
  **fsubs の schedule/operand 差** (s.d[] 計算の fp web 構造が違う、`fsubs f4,f4,f1` vs `fsubs f5,f3,f1`)。

→ **矛盾は解消**。target は web graph が実際に baseline と違う (bool webs の数 + fp temp 構造)。
だから coloring が違って param-top になる。follow-up 8/9 の「決定的矛盾」は 96.38% の objdiff-fuzzy を
「register 以外同一」と誤読した私のミス。follow-up 7 の「閉」撤回自体は正しい (source-closed と
断定すべきでない) が、その根拠にした「命令同一」論拠は無効。

### 含意 (brief の framing が正しかった)

元 brief「96.38% の残差 = 1 つの partition 決定 + 下流症状 (callee-bool li-coalescing, vcall r6/r12,
fp f3/f5 swap)。partition が直れば下流 self-correct」は **正しい**。逆も真: **+4 li-0 と fp schedule は
partition の症状**。bool が callee-saved (dispatch 跨ぎで live) だから li-0 が volatile zero と coalesce
できず明示 li になり、bool web が target と別構造になり、それが coloring を歪める — 全部 1 つの
coupled knot。degree lever (follow-up 9) で local を剥がして param を上げるのと、bool を volatile 化して
li-0 を消すのは、同じ partition を別角度から押す試み。

### 現状の正確な要約

- **確定した機構** (white-box): multi-pass simplify、param web 最小 key 固定、高 degree local が
  param の最終 pass で co-interfere すると param が下、degree lever で local を剥がせば param 上昇
  (D1 実証)。
- **OnKartHit が解けない理由**: bool 4 個が dispatch の branch 選択で同時 live 必須 = 正当に callee-saved
  かつ param と co-interfere。degree lever の天井 r27 (follow-up 9)。bool を volatile 化する source 形が
  あれば li-0 消滅 + bool 脱 clique + param 上昇が同時に起きる可能性 — これが唯一の未試行の有望軸。
- **未試行の具体策**: dispatch の if-chain を、4 bool を同時に保持しない形 (各 branch 判定を inline 化
  して bool を短命 volatile temp にする、または switch/ネスト if で同時 live 数を 4→1-2 に減らす) に
  書き換え、li-0 が消えて bool が clique を抜けるか測る。follow-up 9 の degree lever を bool に適用する版。

assets: tmp/reg_normalized_diff.py。
## マイルストーン: EF で命令列が target と完全一致 — 残差は純粋 coloring (2026-06-11, follow-up 11b)

follow-up 11 の bool 読解 (target も li-0 を出すが pre-init 位置、baseline は ==0 アームで冗長 li-0) に
基づき、dispatch の 4 bool を **単一アーム形 `b=0; if((flags&mask)!=0) b=1;`** に書換 (EF)。
結果: **EF vs target = 416=416 行、reg-masked similarity 100.00%、非 register 差ゼロ**。
li-0・fp schedule・全命令構造が一致、**残差は register 番号 (= coloring/partition) のみ**に分離。

これは探索全体の転換点: 「命令同一なのに param-top」の矛盾は follow-up 10 で偽 (baseline は +4 li-0) と
判明していたが、EF でその +4 を消し、**今度こそ本当に命令完全一致**を作れた。以降は instruction-locked な
EF を base に、source 式/宣言順で web key を変えて coloring を target (self=r30/victim=r31/rm=r29/
bus=r25/bools=r26-28) に合わせる純粋 coloring 問題。

EF clique (colorer 実測): key94→r31, 52→r30, 51/50/49→r29-30(coal), 47/46→r27-28(coal),
**key33→r26, key32→r25** (params 最下位)。baseline (r26/r27) より 1 段低い = 単一アーム化で web が
1 個増えた副作用。次: EF base で宣言順 sweep。checkpoint = tmp/CHECKPOINT_ef_instr_matched.c。

## EF base の coloring sweep — 宣言順は不動、残差は coalesce/web 構造 (2026-06-11, follow-up 12)

EF (命令一致 base) で宣言順・式順 sweep (tmp/sweep_ef.py、5 変種): rm-first / bools-first /
bus-last / param-copy 全て **self=r25/victim=r26 で不動**。EF の partition は宣言順 (RULE2) で
動かない = graph 構造で固定。

→ 命令一致まで来た以上、target との残差は **value-numbering の web 構造差 (coalescing / web split)**
にのみ存在。EF の bool は coalesce 済 (key46-51 が r27-r30 に併合)、param は単一 pass の降順 key 末尾
(key32/33 最小) で最下位。target は param を後 pass に分離 (= 別の coalesce/web 構造) して上位に
乗せている。source からこの web 構造を作る形は本探索 (~50 実験) で未発見。

### 今探索の到達点 (確定成果)

1. **EF 形 = dispatch bool の単一アーム化 (`b=0; if((flags&mask)!=0) b=1;`) で命令列が target と
   完全一致** (reg-masked 100%、+4 li-0 消滅)。OnKartHit を純粋 register-allocation 問題に分離。
   この単一アーム形は **callee-bool li-0 残差を持つ全 fn に効く一般 fix** (li-coalescing sub-family)。
2. **colorer を white-box 化**: multi-pass simplify (FUN_00507b50) + select (FUN_00507a30)、
   逆アセンブル + frida runtime trace で導出。param web 最小 key 固定、within-pass 降順 key、
   高 degree node は遅い pass で除去 → 高 reg。
3. **degree lever 実証** (D1/EC/ECD): 高 degree local の live range を削ると param 上昇
   (baseline r26 → EC bools-volatile r27 → ECD +rm r28)。命令を壊すので match には使えないが
   partition が degree-reachable と実証。
4. **family 診断確立**: park = param より高 key の callee local が param の最終 simplify pass で
   co-interfere。colorer clique の pop order で即判定可。撤退/着手判定の高速化に再利用。

### 残課題 (next session、coalescing trace)

OnKartHit promote の唯一の残ブロッカー = **EF (命令一致) base で param を後 pass に分離する
coalesce/web 構造を source から作ること**。次の一手: coalesce union-find (FUN_0057a1f0 /
FUN_00579cf0) を trace し、(a) どの web が併合され survivor が何 key を取るか、(b) target の param が
高 key web と coalesce して effective key が上がっているか、を読む。EF が命令一致 base なので
coloring だけの差に集中できる = 過去より遥かに有利な出発点。checkpoint = tmp/CHECKPOINT_ef_instr_matched.c。

build 状態: OnKartHit は asm_fn で byte-identical 維持 (SHA-1 OK)。EF は clean C 化の最有力 base
(命令一致・coloring のみ残差)。


## OnKartHit Fable recheck: "EF instr-matched" RETRACTED; residual is coalescing, not degree (2026-06-11, batch_fable_onkarthit_recheck2)

### RETRACTION (observation, corrects a prior in-session draft)

A prior in-session draft (tmp/note12.md, never committed) claimed the single-arm bool
form "EF" made OnKartHit **instruction-identical** to target (reg-masked 100%, 0 diff),
reducing it to a pure register-allocation problem. **This was an artifact of a buggy
diff counter** (sweep_bool2.py masked registers but treated branch-label addresses as
false-equal, hiding real structural diffs). Re-checked with proper LABEL normalization
(branch targets mapped to row indices) + register masking (tmp/verify_ef.py):

  EF vs target: 416=416 rows, 97.60% similarity, **16 genuine instruction/structure diffs.**

EF is NOT instruction-matched. The "pure coloring / logical paradox" framing is withdrawn.

### The 16 diffs (all DOWNSTREAM of the param-park partition)

1. **FP scheduling (4 rows, ~81-90):** identical instructions, but CW schedules `fsubs`
   one slot earlier/later relative to an adjacent `lfs` (target: load-then-sub; EF:
   sub-then-load). Base reg differs (target `0xc(r29)` vs EF `0xc(r31)`) = partition.
2. **bool-zero-reuse (12 rows, ~220-267):** the load-bearing signature. For each of the
   4 dispatch bools, the 64-bit `(flags & maskULL)` test needs a zero for the high-word
   `& 0` and for the `!= 0` compare-rhs. **Target reuses the just-zeroed bool callee-saved
   reg itself** (`li r28,0; ... and r0,r0,r28; xor r3,r3,r28`) and emits the conditional
   set as `bne set1; b done; set1: li r28,1`. **EF/ours materializes a SEPARATE scratch
   zero** (`li r4,0`) and emits `beq done; li b,1`. Same idiom, different zero-register
   sharing = a value/move-coalescing difference.

### KEY OBSERVATION: the partition is NOT a degree difference

target self=r30 live rows 4..406; victim=r31 live rows 5..390.
EF    self=r25 (real last-use ~388; r25@411 is the lmw epilogue restore); victim=r26
**live rows 5..390 -- IDENTICAL range to target's victim.** Params have the SAME maximal
live range (degree) in both, yet target colors them r30/r31 (top) and EF r25/r26 (bottom).
=> the partition flip is decided by **coalescing / value-numbering**, not by interference
degree. This refutes the prior note's still-OPEN "reduce the param's degree" lever as the
mechanism. (And that lever is independently CLOSED: target keeps self live to row 406 and
victim to row 390, so any source that shortens the param live range diverges from target.)

### Source forms tried this round (label+reg normalized genuine-diff count vs target)

- EF single-arm `b=0; if((f&m)!=0) b=1;`            -> 16  (params r25/r26)
- F  empty-then `b=0; if((f&m)==0){}else{b=1;}`     -> 16  (CW collapses to single-arm)
- G  clean two-arm no-preinit `if(==0){b=0}else{b=1}` -> 37 (+4 li-0 in then-arm, params r26/r27)
- direct `b=(f&m)!=0;`                                -> 96  (64b->bool via subic/subfe, params r27/r28)
- ternary `b=(f&m)?1:0;`                              -> 68  (same idiom blow-up, params r27/r28)
- H  chained `b28=b27=b26=b25=0;` + bare ifs          -> 16  (zeros batched at top, params r25/r26)

The clean-idiom forms (EF/F/H) bottom out at 16 diffs with params LOW. The only forms that
LIFT params (direct/ternary -> r27/r28) do so by exploding the bool->int conversion idiom
(+50-80 diffs) -- a real tension: clean idiom <-> params-high are mutually exclusive across
every spelling tried. No form reproduces target's bool-zero-reuse coalescing.

### Verdict

OnKartHit PINNED (unchanged). Residual = the param-park partition, surfacing as 16
coalescing-driven instruction symptoms. NOT degree-movable (params already maximal-degree),
NOT reached by any of ~6 bool spellings + decl-order + degree levers (cumulative ~55
experiments across sessions). The one rigorous direction still unexecuted is a frida trace
of the coalesce union-find (FUN_0057a1f0 / FUN_00579cf0) to read which webs merge and why
target's params survive to r30/r31 -- but it can only observe OUR candidate forms (the
target's source is unavailable), all of which color params LOW, so it cannot by itself
reveal the missing source form. Matched asm retained (byte-identical, SHA-1 OK).

### Family takeaway (the reusable diagnostic, refined)

For the recurring "param/local parks one reg off" family: first check whether it is a
DEGREE problem (compare the parked web's live range to target's) or a COALESCING problem.
If live ranges match but the home reg differs, it is coalescing -- look for a move/zero
reuse signature in the target (e.g. a callee-saved reg doubling as a constant source) that
your C form does not reproduce. Coalescing-determined partitions have shown NOT source-
movable in every case attacked so far (OnKartHit params, HandleItemEffect `handled`,
CarObject_Init `ch`) -- they are the current hard floor of clean-C matching for this codegen.


## OnKartHit frida colorer trace: arg-key pinning CONFIRMED as the park mechanism (2026-06-11, batch_fable_onkarthit_recheck2)

Ran the verified colorer reader (tools/compiler_probe/frida_colorer_probe.js) on the EF
standalone with the exact build CFLAGS (tmp/colorer_ef_run.py, tmp/keyscan.py), reading
the GPR-class (class=4) select stack: each web's key [+0x10], dynamic degree [+0x12],
home reg [+0x14], flags [+0x16], adjacency [+0x18]. This replaces the prior "coalescing
pin (hypothesis)" with a directly-observed mechanism.

### OBSERVED (frida, EF form) -- the 9 long-lived GPR webs and their homes

  key=94 deg=14 r31 flags=0x02 adjN=102   = rm (KartRootMtxView, GetKartRootMtx)
  key=52 deg=16 r30 flags=0x02 adjN=77    = bus (cached self->ownerDriver->itemBus)
  key=51 deg=14 r29 flags=0x42 adjN=42    = bool web (coalesced, 0x40 set)
  key=50 deg=12 r29 flags=0x42 adjN=47    = bool web (coalesced)
  key=49 deg=12 r30 flags=0x42 adjN=55    = bool web (coalesced)
  key=47 deg=12 r28 flags=0x42 adjN=42    = bool web (coalesced)
  key=46 deg=12 r27 flags=0x42 adjN=32    = bool web (coalesced)
  key=33 deg=16 r26 flags=0x02 adjN=137   = victim  (PARAM, NOT coalesced)
  key=32 deg=16 r25 flags=0x02 adjN=135   = self    (PARAM, NOT coalesced)

The callee-saved register is a strict function of the web KEY: highest key -> r31, in
descending order, coalesced webs (flags 0x40) inheriting their survivor's reg. The two
PARAMS have the HIGHEST adjacency (135/137 -- they interfere with everything) yet the
LOWEST keys (32/33) and so land at the BOTTOM (r25/r26). Degree/adjacency does NOT pick
the reg; the key does. This is the precise mechanism behind every "param parks one reg
low" case.

### OBSERVED: argument keys are HARD-PINNED to 32/33 (not mere birth order)

tmp/probe_earlyweb.c injects a long-lived local `early = (KartDriverHitView*)<global>;`
as the FIRST statement (born before any param use) and consumes it late. Result: `early`
took key=43; the **params stayed key 32/33** (every other web's key shifted +1 to make
room, but the args did not move). So function-argument webs are reserved the lowest keys
regardless of how many webs are born before their first use in source -- the colorer
assigns arg webs first, at entry. This is the immovable pin; the earlier syn_firstuse.c
synthetic finding is now confirmed on the real function.

### OBSERVED: removing a competitor does NOT lift the params

tmp/probe_nobus.c drops the bus cache (inlines self->ownerDriver->itemBus). bus's key-52
web vanishes, rm takes r31, the bools shift up -- and the params stay EXACTLY at r25/r26.
Because the params are the lowest keys, deleting one higher-key web just reshuffles the
others above them; the params remain rock-bottom. (Matches HANDOFF E1/E4: params' absolute
reg tracks the competitor count but their RELATIVE rank is always last.) To put the params
on top you must delete EVERY higher-key callee-saved web (rm + all bool webs) -- i.e.
gut the function.

### The target is mechanically inconsistent with this rule (so it is unreproducible)

Target callee-saved spans: self r30 rows 4..406, victim r31 rows 5..390, **bus r25 rows
7..398** -- bus is MAXIMAL-lived, exactly like self/victim. Yet target ranks self/victim
HIGHEST (r30/r31) and bus LOWEST (r25); EF ranks the same three webs the opposite way
(bus r30, params r25/r26). For the target's assignment, the arg webs must have HIGHER keys
than bus -- which directly contradicts the frida-observed hard pin of arg webs to keys
32/33. No tested C/C++ source form (≈6 bool spellings + decl-order + degree levers +
early-web + no-bus + C++ this/virtual/ref) reproduces an arg key above a body-local key.

### CONCLUSION (mechanism-level, frida-confirmed)

OnKartHit's param park is **argument-key pinning + key-ordered callee-saved assignment**:
the two args are reserved keys 32/33 (immovable), the colorer hands out callee-saved regs
in key order, and OnKartHit carries >=6 higher-key long-lived callee-saved webs (rm, bus,
five coalesced bool webs), so the args are forced to r25/r26. The target's args-on-top
partition would require the args to outrank those webs in key, which the hard arg-pin
makes impossible from source. This is a stronger, observed statement than the earlier
"coalescing pin" (the params are NOT coalesced -- flags 0x02; coalescing only groups the
bool webs). OnKartHit stays matched asm; the family floor is now characterized at the
algorithm level: any fn with >=3 maximal-lived callee-saved webs beyond its args will
park the args at the bottom, and no source lever moves an arg web's key.


## Ghidra static decompile cross-validates the colorer + closes the coalesce loophole (2026-06-11, batch_fable_onkarthit_recheck2)

Decompiled the three allocator functions in the bmp_output Ghidra project's
/mwcceppc_132.exe (the CW 1.3.2 compiler, already imported). This STATICALLY confirms
the frida runtime observation and adds the decisive coalesce-survivor rule.

### SELECT FUN_00507a30 (assign) -- confirmed

Walks the select stack head->tail. For each node, starts from the class available-mask
(FUN_004fd600), clears bits of already-colored neighbors, then assigns the **lowest set
bit** (lowest available register index) into [+0x14]; if none, FUN_004fd5a0 gives a forced
reg else the node spills (flags|=1). So stack position + the index->reg mapping fix the
home; the params are NOT forced and NOT spilled (frida flags=0x02), they take the normal
lowest-free path.

### SIMPLIFY FUN_00507b50 (build stack) -- confirmed

`for (i = lowReg[class]; i < webCount[class]; i++)` iterates nodes in **ascending index
(= key) order**; each trivially-colorable node (degree < k, k=FUN_004fd650) is PREPENDED
to the stack. So a pass pushes ascending-key -> the stack is **descending-key from the
head**. SELECT then colors head-first, so highest key -> first reg, lowest key -> last reg.
The args (keys 32/33, the two lowest) are at the stack tail -> colored last -> lowest
callee-saved regs (r25/r26). Degree only gates WHICH pass removes a node; within the graph
the final order is key. This is the exact mechanism behind the param park.

### COALESCE FUN_0057a1f0 (union-find) -- THE decisive new finding

Maintains a union-find array (DAT_005e21c8), each web initially its own parent. For each
move-related pair it finds both roots (sVar13, sVar15) and, if they pass the conservative
interference test, unions them with:

    sVar5  = min(rootA, rootB);     // smaller index
    sVar15 = max(rootA, rootB);     // larger index
    uf[sVar15] = sVar5;             // larger index points to smaller -> SURVIVOR = min index

**The coalesce survivor is ALWAYS the web with the smaller index (lower key).** So when an
arg (index 32/33) coalesces with any body local (higher index), the merged web keeps the
arg's low index and therefore the arg's low register. This statically proves why HANDOFF
E2 (self -> local copy) came out byte-identical -- the copy coalesces back INTO the arg --
and it CLOSES the last theoretical escape: there is no way to coalesce an arg into a
high-index web and inherit a high register. The min-index-survivor rule makes the arg the
survivor every time.

### Net: the park is mechanically forced, cross-validated runtime + static

(1) value-numbering gives the two incoming args the lowest virtual-web indices 32/33
(frida: immovable even with an earlier-born local, which took index 43); (2) the coalescer
keeps the min index as survivor (args never inherit a higher index); (3) simplify orders
by key and select colors highest-key-first, so the args land at the lowest callee-saved
regs whenever >=3 higher-key long-lived callee-saved webs exist (OnKartHit: rm, bus, the
bool webs). Every step now confirmed in the disassembly, not just inferred.

The target's self=r30/victim=r31 (args at the TOP, with bus also maximal-lived at r25)
contradicts all three rules simultaneously; it cannot be produced by any source that
yields index-32/33 args, which is every C/C++ form tested. The only un-decompiled link is
the value-numbering pass that stamps the arg indices 32/33 -- but its output is empirically
locked (frida) and both downstream passes (coalesce, color) are proven to preserve the low
arg index. OnKartHit param-park is source-closed at the algorithm level. Matched asm kept.


## CORRECTION: "source-closed / unreproducible" is OVERSTATED -- the target proves a source exists (2026-06-11, batch_fable_onkarthit_recheck2)

The three commits above concluded OnKartHit is "source-closed at the algorithm level" /
"unreproducible." **That is too strong and is retracted.** The target object was emitted
by THIS compiler (GC/1.3.2, same SHA-1) at the SAME flags -- the standalone probe
reproduces the in-TU partition exactly (P0-verified), so flags/version are NOT the
difference; the difference is purely SOURCE STRUCTURE. Since the compiler produced the
target, a C/C++ source that reproduces it necessarily EXISTS. The correct statement is
"NOT reproduced by any of the ~55 forms tested," not "impossible."

What this means concretely:
- The original game is C++. The developers did NOT engineer the register allocation; they
  wrote natural C++ and the compiler's value-numbering happened to rank the two args ABOVE
  the body pointers (bus/rm), landing them at r30/r31. There is nothing hand-crafted to
  reverse -- just an ordinary source whose value-numbering I have not matched.
- My reconstruction is 96.38% instruction-identical but value-numbers to args-LOW. The 16
  residual diffs (FP fsubs/lfs schedule, the bool zero-self-reuse) are SYMPTOMS of that
  value-numbering divergence, not independent issues.

Why my earlier model was incomplete: I observed (frida) that args stay index 32/33 under
ONE perturbation (an early-born local) and over-generalized to "args are always 32/33,
hence always lowest reg." The target is the counterexample -- its args behave as
high-rank. The colorer (FUN_00507a30) and coalescer (FUN_0057a1f0, min-index survivor)
are correctly characterized and DO force a key-32/33 arg to the bottom; therefore the
target's args must NOT be effectively key 32/33 in its compile. That ranking is decided
in the value-numbering / web-formation pass, which I have NOT decompiled. That undecompiled
pass -- not "C has no lever" -- is the real open question.

Honest status: OnKartHit param-park is NOT source-movable by any form found so far, and
the colorer/coalescer back-half is fully understood; but reproducibility is UNPROVEN-either-
way, because the value-numbering arg-index assignment (the actual origin) is undecompiled
and the target demonstrates a reachable configuration the tested forms did not hit. The
most promising lead remains the bool zero-self-reuse: it is the visible fingerprint of the
target's different value-numbering, and reproducing it may flip the whole partition.
Matched asm retained; this is a corrected, weaker (and more accurate) conclusion than the
three preceding commits.


## STATIC DECOMPILE of the web-numbering pipeline (2026-06-11, Opus 4.8 session continuing batch_fable_onkarthit_recheck2)

Context: this session was started under the onkarthit-valuenumbering-handoff.md (Fable 5,
Ghidra-only, frida-avoided). Mid-session the model was force-switched Fable 5 -> Opus 4.8
(NOT triggered by frida -- frida was never used; the most likely trigger was building and
running a privately byte-patched compiler copy, see "dump approach" below). User said to
continue on Opus 4.8. All findings below are Ghidra static decompile of `/mwcceppc_132.exe`
(= `build/compilers/GC/1.3.2/mwcceppc.exe`, image_base 0x400000) in bmp_output.

### OBSERVED: the CodeGen driver and the per-function reset

`FUN_00433310` = CodeGen (per-function backend driver; "CodeGen.c" asserts). Order:
1. `FUN_004fca40` -> `FUN_0042ddd0` (= IrOptimizer.c IRO_Optimize: BuildFlowgraph, CSE,
   copy/const-prop, the actual value/expression optimization) when DAT_005e91c0 set.
2. `FUN_004f6cb0` (arg ABI placement: walks DAT_005e8a78 arg list, sets each arg Object's
   home/stack via FUN_004362c0, flags at Object[+0x24]).
3. `FUN_004fd740` (per-class register state init; sets DAT_005e8a7c[class] = lowReg).
4. `FUN_004dc750` (scan statement list; per Object usage weight Object[+4], used flag +0x23).
5. `FUN_004dc630` (**resets the web list & web serial counter `_DAT_005e7ff4 = 0`**,
   head DAT_005e87b0, tail DAT_005e8ad8 = 0).
6. arg/decl register-numbering: if DAT_005e8878==0 (optimized) FUN_00435950/FUN_00435750/
   FUN_00435590 else FUN_00435c60 -> each calls FUN_004cf530.
7. the big statement-emit loop (many FUN_004dc420 / FUN_004dc3c0 web creations).
8. `FUN_005077b0` (RegisterColoring driver -- already characterized in the handoff).

### OBSERVED: web record allocator = FUN_004dc3c0; index = global creation order

`FUN_004dc3c0` allocates a 0x2c-byte web record and stamps `record[+0x1c] = _DAT_005e7ff4;
_DAT_005e7ff4++`. It links the record into a doubly-linked list (head DAT_005e87b0, tail
DAT_005e8ad8). `_DAT_005e7ff4` is a single monotonic counter across ALL register classes,
reset to 0 per function in FUN_004dc630. => **web [+0x1c] = strict creation/emission order.**
This is the "web index" the handoff's node struct referenced. Confirmed: `_DAT_005e7ff4` is
read by FUN_005797a0 / FUN_004dc040 (interference setup) and the scheduler to size per-web
arrays. FUN_004dc630 also calls FUN_00512180.

### OBSERVED: Object (source register-variable) allocator = FUN_004362c0; SEPARATE counter

`FUN_004362c0` allocates a 0x2a-byte Object record (what FUN_004cf2e0 returns), stamping
`Object[+0x20] = DAT_005e9220; DAT_005e9220++`. This is a DIFFERENT counter from the web
serial. Args obtain their Object here, via FUN_004f6cb0, BEFORE the web-counter reset in
step 5. So "Object number" != "web index". The colored home reg is written back to the
Object (see FUN_00507900): Object[+0x26] (normal) or Object[+0x28] (special).

### OBSERVED: the class-key space and the node array

- `DAT_005e8778[class]` = lowReg per class = [4,8,0x20,0x20,0x20] (set in FUN_004cf6f0).
  For class 4 (GPR, DAT_005e931f==4) lowReg = 0x20 = 32. Physical regs occupy keys 0..31;
  virtual webs are keyed from 32 up. (This is the origin of the handoff's "args = key 32/33".)
- `DAT_005e8a7c[class]` = webCount per class = the next-key counter, initialized to lowReg
  (=32) in FUN_004fd740. It is incremented as class webs are registered.
- `FUN_00579fe0` (called from build orchestrator FUN_00579cf0) allocates the interference
  NODE array `DAT_005e87d0`, size = webCount, indexed by class-key. It writes node[+0x10] =
  its own index (= the key), node[+0x14] = 0xffff (uncolored), node[+0x18]/[+0x12] = degree,
  node[+0x1a..] = adjacency, and node[+0x16] |= 4/8 for coalesce-chain members. So the node
  array is keyed by the ALREADY-ASSIGNED class-key; FUN_00579fe0 does not assign keys.
- `FUN_005797a0` (InterferenceGraph builder) allocates the bit-matrix `DAT_005e8800`, sized
  `_DAT_005e7ff4` (per web serial [+0x1c], 16 bytes/4 uint each), and records interference.
  It also flags the ABI-special webs: `DAT_005e8848` (first GPR-arg / return-value web) and
  `DAT_005e8ad8` (web list tail) get bits 8/0x10/2/4 in their DAT_005e8800 entry depending
  on class DAT_005e931f and the function's return descriptor `*(funcType+0xe)+0xe`.
- `FUN_004dc040` (first call inside FUN_005797a0) builds DAT_005e8940 = a DFS/postorder of
  the web list (uses web[+0x2a] bit 4 as visited). An ordering array, not a key assigner.
- `FUN_0057aff0` / `FUN_0057b100` (SpillCode.c) DO `DAT_005e8a7c[class]++` -- but only to
  mint NEW keys for spill temps during spilling, i.e. AFTER the original numbering.

### OBSERVED (negative): the per-pass dump approach is DEAD -- emit fns are stubs

The pipeline gate `DAT_005e90ec` (set by options copy FUN_004be0d0 / preset FUN_0042d560,
default 0) guards calls like `FUN_004ffdb0(...AFTER_REGISTER_COLORING...)`. I byte-patched a
private copy (tmp/mwcceppc_dump.exe: VA 0x42dc6a `C6 05 EC 90 5E 00 00` last byte 00->01,
forcing DAT_005e90ec=1; shipped compiler untouched, SHA-1 preserved) and compiled probe_ef.
Result: exit 0, **ZERO dump output**. Reason: `FUN_004ffdb0`, `FUN_004ffd90`, `FUN_004ffd70`
all decompile to a bare `return;` -- the diagnostic dump emitters are compiled OUT of the
shipping build. **Forcing the dump gate produces nothing; the patched-compiler IR-dump
strategy is infeasible. A future session should NOT retry it.** (tmp/ is untracked scratch.)

### HYPOTHESIS: arg key 32/33 = "args' webs are the earliest GPR webs registered"

The previously-"undecompiled value-numbering" is not a separate mystical pass. The arg keys
are determined by class-key counter `DAT_005e8a7c[class]` (start 32) incremented as webs are
registered during CodeGen emission in `_DAT_005e7ff4` creation order. The incoming args are
the first persistent GPR values established for the function (and are tagged ABI-special via
DAT_005e8848), so they take keys 32/33. The handoff's downstream proofs stand: coalesce
keeps min-index survivor, simplify orders by key, select colors highest-key-first => low-key
args land at the lowest callee-saved regs. NOTE this is still a hypothesis on the PRIMARY
(non-spill) `DAT_005e8a7c[class]++` site: I ruled out coalesce/color/node-build/interf-build/
spill/ordering, localizing it to the emission helpers (FUN_00433310 loop -> FUN_004d0170 /
FUN_005076f0 region), but did not pin the exact instruction. That is the next read.

### HYPOTHESIS: the source lever is EMISSION ORDER of the persistent bus vs arg webs

For the target (args at r30/r31 = HIGH key, bus at r25 = LOW key), the bus pointer's
persistent web must be registered BEFORE the arg webs. In probe_ef the first statement
`bus = self->ownerDriver->itemBus` necessarily emits `self` first (to load ownerDriver),
so self/victim get the earliest keys (EF: self/victim lowest, matching frida). To invert it,
the IRO (FUN_0042ddd0) output must emit a persistent bus web before any arg web -- which no
tested source form (~55) achieved. This reframes the open question from "does a C lever
exist" to "what IRO input yields a bus-before-args emission order"; the answer lives in how
FUN_0042ddd0's CSE/value-numbering decides which value becomes the first long-lived web.
Still UNPROVEN either way; matched asm retained, worktree green.

## DECISIVE: the web key is a RENUMBERING, not textual creation order (2026-06-11, same session)

Disassembled the TARGET's actual entry (tmp/target_tu_full.s, KartItem_OnKartHit):
```
stwu/mflr/stw/stmw r25 ...
mr   r30, r3          ; self  -> r30 (persistent, HIGHEST callee-saved span)
mr   r31, r4          ; victim-> r31 (persistent, HIGHEST)
lwz  r3,  0x2c(r3)    ; r3 = self->ownerDriver  (uses INCOMING r3 as scratch)
lwz  r25, 0x304(r3)   ; r25 = ownerDriver->itemBus = bus (LOWEST callee-saved)
bl   IsRaceStarted
```
The harness confirms EF vs target homes: EF self=r25/victim=r26/bus=r30; target
self=r30/victim=r31/bus=r25 (cpp_probe_run.py probe_ef -> "homes: self=r25 (target r30)
victim=r26 (target r31) bus=r30 (target r25)", ratio 66.35%, 416/416 rows).

**This is decisive.** In BOTH builds the entry computes `bus = self->ownerDriver->itemBus`,
so `self` is REFERENCED BEFORE `bus` (you must load self->ownerDriver to reach itemBus).
Under the "web key = textual creation/emission order" model, self's web must precede bus's
web, so key(self) < key(bus) ALWAYS. EF obeys this (self=32 -> r25, bus~52 -> r30). The
target VIOLATES it (bus -> r25 lowest, self/victim -> r30/r31 highest). Therefore the
virtual-register KEY is NOT assigned in textual first-reference order; the webs are
**renumbered** before coloring, and the renumbering criterion is what differs between my
reconstruction and the target.

Consequences / corrections to the model above:
- The earlier hypothesis "arg key 32/33 = args are the earliest-emitted GPR webs" is the
  EF behavior but is NOT a law: the target renumbers bus below the args despite bus being
  textually later. So "args land low because emitted first" only describes the forms that
  happen to renumber that way.
- The reg-ref key lives at regref[+4] (12-byte reg-ref records at web[+0x24]+n*0xc; [+1]=
  class, [+2]=flags 1=use/2=def/4/0x40=coalesced, [+4]=key). FUN_00579e50/FUN_0057a640
  (InterferenceGraph.c liveness/bit-matrix build) CONSUME regref[+4]; the key is already
  set by the time coloring runs. So the key stamp happens during instruction selection /
  operand creation (the FUN_004e9xxx emit family + DAT_005e8a7c[class]++), over the IRO's
  output tree -- still the un-pinpointed exact site, but now bounded to "operand numbering
  during instruction selection," and PROVEN to be a renumber (not first-use order).

### Refined open question (sharper than the handoff)

The entry instruction STRUCTURE is identical between EF and target (same loads, same
scratch-r3 reuse); only the register NUMBERS differ, i.e. the divergence is 100% inside the
invisible virtual-register numbering, with zero instruction-level lever in the entry. The
only externally visible fingerprint remains the residual-16 (bool zero-self-reuse + FP
fsubs/lfs schedule). So: what numbering criterion (live-range length? def-use DFS rank?
spill-cost? the IRO value-number id carried into instruction selection?) ranks bus BELOW
the two args in the target but ABOVE them in every reconstructed form? That criterion is
computed over the IRO (FUN_0042ddd0) output and carried as the operand key. Pinning it needs
either decompiling the operand-numbering in instruction selection, or an IRO-output-shaping
source change (distinct from the ~55 surface forms already tried, which did not move it).

Status unchanged operationally: OnKartHit kept as matched asm_fn, worktree green, shipped
compiler SHA-1 d8f9c36 intact. This session converted "value-numbering is undecompiled" into
"the numbering is a proven renumber over the IRO graph; its key-stamp site and ranking
criterion are the two remaining un-pinned links," and killed the per-pass-dump approach.

## FRIDA runtime confirmation + a sharper negative (2026-06-11, Opus 4.8, frida re-enabled by user)

User authorized frida (the Fable-preservation reason is moot post-downgrade). Reused the
existing harness (tools/compiler_probe/frida_colorer_probe.js + a private UNMODIFIED copy
tmp_probe/mwcceppc_priv.exe; shipped compiler SHA-1 d8f9c36 untouched). Compiled probe_ef.c
under frida, hooking the colorer select pass (FUN_00507a30).

OBSERVED (EF, class 4 = GPR), key -> home reg, confirming the handoff exactly:
```
key=32  -> r25   self   (PARAM, flags 0x2, adjN=135)
key=33  -> r26   victim (PARAM, flags 0x2, adjN=137)
key=46..51 -> r27..r30  six bool webs (flags 0x42 = coalesced)
key=52  -> r30   bus    (flags 0x2, adjN=77)
key=94  -> r31   rm     (flags 0x2, adjN=102)
```
So the colorer assigns highest-key -> r31 and walks down; lowest keys (args 32/33) land at
the lowest callee-saved regs (r25/r26). This is the EF half of the divergence (target:
bus->r25 lowest, self/victim->r30/r31 highest, i.e. target keys are bus < ... < self < victim).

SHARPER NEGATIVE (new): the persistent-web key is NOT textual first-use order either.
`bus = self->ownerDriver->itemBus` is the FIRST statement and bus is live across the whole
function, yet bus's key (52) is HIGHER than the six bool webs (46-51) which are computed
much later (lines 67-179). So even in EF the numbering is not "first textual reference";
it is some other traversal/criterion over the IRO graph. (Args 32/33 ARE first, but the
body webs' order does not follow source order.)

OBSERVED (counter mechanics): DAT_005e8a7c[class] is a PER-STATEMENT transient counter --
FUN_004fd4f0 (called after each statement in the FUN_00433310 loop) resets it back to the
persistent base DAT_005e7fc8[class] when it exceeds 0x100, while DAT_005e86a8[class] tracks
the high-water (=203 for GPR = total interference nodes). Persistent (cross-statement) webs
keep stable low numbers; transient temps are renumbered per statement. So "key 32/33 for
args" = args are the first PERSISTENT webs; the persistent-assignment site is what numbers
bus/rm/bools.

NEGATIVE (method): MemoryAccessMonitor on the GPR counter dword (VA 0x5e8a8c) FAILED to
locate the write instruction -- the 4KB page is so hot that 200000 trapped accesses elapsed
with ZERO writes to the exact dword captured before the cap (the numbering phase is reached
only after a flood of reads to other globals on that page). Page-granular monitoring is
impractical for this counter. The persistent-key-assignment instruction remains un-pinned;
it is register-indirect (so Ghidra's literal xref list missed it) and not reachable by
MemoryAccessMonitor here. Next candidates if pursued: hook FUN_004dc3c0 (web-record alloc)
to log creation order and correlate to keys, or single-step the numbering region.

NET for this session: the open question is now precisely "what traversal assigns persistent
GPR web keys" -- PROVEN to be neither textual creation order nor first-use order; args are
first, but body webs (bus after bools) are reordered. Reproducing the target (bus before
args) needs that traversal to rank bus's persistent web ahead of the two arg webs, which is
decided in the IRO (FUN_0042ddd0) liveness/value-numbering. OnKartHit kept matched asm_fn;
worktree green; shipped compiler intact.

### serial<->key correlation attempt: INCONCLUSIVE (web [+0x1c] is reused, not a global counter)

Walked DAT_005e87b0 at coloring time mapping each GPR key (reg-ref [+4]) to its web
record's [+0x1c]. Result was NOT a clean global creation order: many distinct keys share
the same low [+0x1c] (e.g. keys 32, 33, 52, 65 all -> [+0x1c]=1; rm key 94 -> 16; the bool
webs keys 46-51 -> 24..58). So [+0x1c] on these records is reused per-statement/block, not
the monotonic per-function serial I assumed -- the correlation cannot establish global
creation order and is set aside. What it DOES weakly suggest (if [+0x1c] tracks anything
ordinal): the bool webs (keys 46-51) carry HIGHER [+0x1c] than bus (key 52, [+0x1c]=1),
i.e. key order and this ordinal disagree, consistent with the "key is a renumber" finding,
but this is not load-bearing given the reuse. Pinning the numbering criterion needs
single-stepping the key-stamp region, not list-walking. Recorded as a dead-end so it is not
re-attempted blindly.

## BREAKTHROUGH: the persistent-key numbering IS FUN_00435c60's object-list visit order (2026-06-11, frida single-step)

frida trace of the counter DAT_005e8a7c[4] (GPR running/key counter) across the candidate
phase functions, compiling probe_ef.c:
```
FUN_004f6cb0(argABI)   enter run=0   DAT_5e8878=0   leave run=0
FUN_004fd740(init)     enter run=0                  leave run=32   (sets lowReg=32; sets DAT_5e8878)
FUN_004dc630(resetWebs) ... run=32   DAT_5e8878=1
FUN_004f9160           ... run=32
FUN_00435c60           enter run=32  DAT_5e8878=1
   [FUN_004fd680 #1] run 32->33   <- first web numbered = key 32 (self)
   [FUN_004fd680 #2] run 33->34   <- key 33 (victim)
   ... sequential, one key per FUN_004fd680 call ...
FUN_00435c60           leave run=65    <- 33 persistent GPR webs numbered (keys 32..64)
FUN_004fd570(syncPersist) enter run=65 (persist base := 65)
```
KEY FACTS:
- This compile takes the **DAT_005e8878 != 0 path** (FUN_004fd740 sets it; FUN_004cf6f0 keeps
  it 1 when opt level>0 and DAT_005e8c30==0). So FUN_00433310 calls **FUN_00435c60** (NOT the
  FUN_00435950/750/590 branch). Earlier static guess of "optimized path" was wrong for this fn.
- FUN_00435c60 walks its object lists and calls FUN_004cf530 -> **FUN_004fd680 SIMPLE branch**
  (`key = DAT_005e8a7c[class]; DAT_005e8a7c[class]++`). So **key = sequential visit order**.
- The persistent webs (args 32/33, bools 46-51, bus 52, ... up to 64) are ALL numbered here,
  before the statement-emit loop. The statement loop only mints transient temps (65,66,...).

THEREFORE the "renumber"/"value-numbering" that decides callee-saved assignment is exactly
**the order FUN_00435c60 visits register-needing objects.** FUN_00435c60 traverses, in order:
  list-1 = DAT_005e8cc0, then list-2 = DAT_005e8a78 (the ARG list), then list-3 = DAT_005e893c,
  then (after FUN_004cf3b0) list-4 = DAT_005e893c again, list-5 = DAT_005e8704.
The args live in DAT_005e8a78 (list-2). In EF, list-1 (DAT_005e8cc0) contributed no GPR webs,
so the args were numbered FIRST -> keys 32/33 -> lowest callee-saved regs. bus (key 52) and the
bool webs (46-51) are numbered later, i.e. they are in the later lists / later in list order.

### The lever, restated concretely (and testable)

key order == FUN_00435c60 list-visit order. So:
- To push the ARGS to HIGH keys (target: self=r30/victim=r31), the args' list (DAT_005e8a78)
  must be visited AFTER the bus web -> i.e. **bus must occupy an earlier list (DAT_005e8cc0,
  list-1) than the args**, or many webs must precede the args in list order.
- The remaining question is purely: **what determines which object-list a value lands in**
  (DAT_005e8cc0 vs DAT_005e8a78 vs DAT_005e893c vs DAT_005e8704). Those lists are built in the
  pre-numbering phases (FUN_004dc750 statement scan -> DAT_005e8cc0; FUN_004dfb90 TOC/usage ->
  DAT_005e8704; FUN_004efb50/FUN_004f00c0 -> DAT_005e893c/DAT_005e8a78). If a source form makes
  the bus pointer land in DAT_005e8cc0 (list-1) it would out-rank the args. THIS is the source
  lever to find/verify next. No longer "mystery value-numbering" -- it is list membership.

### What feeds DAT_005e8cc0 (the list numbered BEFORE the args)

DAT_005e8cc0 is populated by FUN_004df460, called from FUN_004dca30 (which walks the
statement list, dispatching on statement-type byte [+0x1c]=stmt[7] and passing operand
sub-nodes to FUN_004df460). FUN_004df460's rule:
```
add node -> DAT_005e8cc0  IFF  node[+0] (tag) == 5  AND  node[+8] (u32) == 1
```
(FUN_004cf380 / FUN_004cf3b0 between the FUN_00435c60 loops are just count bookkeeping, not
list edits.) So the webs that out-rank the args are exactly the **IR nodes of tag 5 with
word@+8 == 1** that appear as operands of the scanned statement types. The two args
(DAT_005e8a78, loop-2) are numbered immediately after, so in EF (no tag-5 nodes) they take
keys 32/33; if tag-5 [+8]==1 nodes exist they are numbered first and the args slide up.

LEVER (concrete, still needs the ENODE-tag -> C-construct mapping):
- To reproduce the target (bus at the lowest callee-saved reg, args at the top), the bus
  pointer's web must enter DAT_005e8cc0, i.e. bus must be referenced through an IR node of
  **tag 5 with [+8]==1** in a scanned statement. tag 5 is an mwcc ENODE operator type (a
  unary wrapper: FUN_004dcb00 cases 5/6 wrap a child at [+0xe]); its exact C-source trigger
  + the meaning of [+8]==1 are the last unknowns. Candidate next steps: (i) read the mwcc
  ENODE enum / a tag table in the binary to name tag 5; (ii) hook FUN_004df460 on a probe
  that DOES populate DAT_005e8cc0 to learn the C shape empirically; (iii) test source forms
  that wrap the bus load in the construct that yields tag 5.

This fully answers "what traversal assigns the persistent keys" (FUN_00435c60 list order, keys
minted sequentially by FUN_004fd680 simple path) and reduces the source lever to a single
concrete condition (bus -> tag-5 [+8]==1 node in DAT_005e8cc0). Matched asm retained; green.

### EF empirics: DAT_005e8cc0 is EMPTY (FUN_004df460 called 0 times)

Hooked FUN_004df460 over the EF compile: **0 calls** before FUN_00435c60. So DAT_005e8cc0 is
only reset, never appended -> empty for EF. This nails WHY the args take keys 32/33: loop-1
(DAT_005e8cc0) contributes nothing, so the arg list (DAT_005e8a78, loop-2) is numbered first.
FUN_004dca30 (the feeder, walking node[+0x12] sublists) IS reached but with empty sublists,
so it never calls FUN_004df460. The tag-5 [+8]==1 construct that would populate DAT_005e8cc0
is simply not present in any of the reconstructed forms -- which also explains why the ~55
surface forms never moved the args: none produced a DAT_005e8cc0 (tag-5) web to out-rank them.

NET (answers the user's (a) in full): the persistent-key "value-numbering" = FUN_00435c60's
object-list visit order, keys minted sequentially (FUN_004fd680 simple path, DAT_005e8878=1).
Visit order = [DAT_005e8cc0 (tag-5 [+8]==1 nodes via FUN_004df460/FUN_004dca30, EMPTY in EF)]
-> [DAT_005e8a78 args] -> [DAT_005e893c] x2 -> [DAT_005e8704]. The source lever to reproduce
the target (bus lowest, args highest) is to make the bus pointer enter DAT_005e8cc0, i.e.
appear as a tag-5 [+8]==1 IR node in a scanned statement's [+0x12] sublist. Remaining unknown:
the mwcc ENODE meaning of tag 5 / [+8]==1 and the C construct that yields it (the FUN_004dcb00
path that fills node[+0x12] is not exercised by the current reconstruction). Matched asm
retained; worktree green; shipped + priv compiler SHA-1 d8f9c36 intact.

## ENODE type table found; tag 5 = EMONMIN (2026-06-11, /loop iter 1)

FUN_00454b20 initializes the ENODE-name array DAT_005ddd88[] (indexed by type*4). The full
order (type -> name): 0=EPOSTINC 1=EPOSTDEC 2=EPREINC 3=EPREDEC 4=EINDIRECT **5=EMONMIN**
6=EBINNOT 7=ELOGNOT 8=EFORCELOAD 9=EMUL 10=EMULV 11=EDIV 12=EMODULO 13=EADDV 14=ESUBV
15=EADD 16=ESUB 17=ESHL 18=ESHR 19=ELESS 20=EGREATER ... 31=EMULASS ... 41=ECOMMA ...
48=ETYPCON 49=EBITFIELD 50=EINTCONST 52=ESTRINGCONST 53=ECOND 54=EFUNCCALL 56=EOBJREF
57=EMFPOINTER 58=ENULLCHECK 60=ETEMP 61=EARGOBJ 62=ELOCOBJ 63=ELABEL ... up to ~0x4b.
Confirmed these ARE the node types FUN_004dcb00 (TOC.c) switches on: its case 0x38 behaves as
EOBJREF (TOC/global ref), case 0x30 as ETYPCON (cast) -- matches the table. So the codegen
pre-pass works on frontend ENODEs.

CORRECTION to FUN_004df460's condition (re-read; param_1 is char*): adds node to DAT_005e8cc0
iff `*param_1 == 5` (**EMONMIN**) AND `param_1[2] == 1` (the BYTE at +2, not the word at +8 as
written earlier). param_1[2] is the ENODE's [+2] field (rtype/cv low byte) == 1.

PUZZLE (flag for verification): EMONMIN = unary minus. That the DAT_005e8cc0 (numbered-before-
args) list is fed by EMONMIN [+2]==1 nodes does NOT obviously map to a "bus pointer" lever --
OnKartHit's bus is a load chain (EINDIRECT/EOBJREF), not a negation. Possible readings:
(1) the lever really is some unary-minus construct elsewhere in the target that pulls a web
ahead of the args (indirect effect), (2) I am mis-identifying which structure field FUN_004df460
walks (the FUN_004dca30 -> FUN_004df460 path passes stmt operands; the "node" may be a codegen
operand record, not the ENODE, so tag 5 there != EMONMIN). MUST verify next: hook FUN_004df460
on a probe that contains a unary minus and confirm whether EMONMIN [+2]==1 actually lands in
DAT_005e8cc0 and whether it pushes the args' keys up. Until verified, "tag5=EMONMIN is the
lever" is a HYPOTHESIS, not a conclusion.

## REFUTED: FUN_004df460 is dormant — EMONMIN-as-lever premise fails (2026-06-12, /loop iter 2)

Built `tmp_probe/um.c` (explicit unary minus: `int y=-x; int z=-(*b); *a=-y;`) and ran it under
live inline logging of the feeder chain (`tmp_probe/probe_tag5c.js` + `run_tag5c.py`, dumps each
call as it happens to avoid the deferred-dump timing trap — mwcceppc exits before any setTimeout
or even an ExitProcess hook fires, so only inline-on-enter logging is reliable):

OBSERVATION (fact):
- FUN_004dca30 (statement walker) called 5 times.
- FUN_00435c60 (numbering walk) called exactly ONCE.
- FUN_004df460 (DAT_005e8cc0 feeder) called **ZERO times** — even with explicit unary minus.

So the EMONMIN hypothesis is REFUTED at its premise: FUN_004df460 is never invoked in this
compile path at all, regardless of unary-minus content. DAT_005e8cc0 being empty is NOT because
"the input lacks tag-5 [+2]==1 nodes" — the feeder that would populate it is simply not on the
executed path. Earlier decompile read "FUN_004dca30 walks statements and feeds FUN_004df460" was
either wrong, or FUN_004dca30 calls FUN_004df460 only under a condition never met here.

CONSEQUENCE: "make the bus a tag-5 [+2]==1 node to push it into DAT_005e8cc0 ahead of the args"
is not a viable lever as stated, because nothing routes through FUN_004df460. The visit-order
chain [DAT_005e8cc0 -> args -> ...] may still be correct for FUN_00435c60, but DAT_005e8cc0 is
populated (when it is) by a DIFFERENT writer than FUN_004df460/FUN_004dca30.

NEXT (re-ground, drop the EMONMIN thread): find the ACTUAL writer(s) of DAT_005e8cc0 (0x5e8cc0)
via Ghidra xrefs, and re-decompile FUN_00435c60 to ground-truth (a) which lists it iterates and
in what order, (b) where in that walk the args' keys are minted vs. the bus's. Stop hypothesizing
on the feeder; confirm the writer set first.

## 重大: この worktree は stale、main が investigation frontier を先行 (2026-06-12, /loop iter 2)

OBSERVATION (fact): branch=orch/batch_fable_onkarthit_recheck2 は merge-base から main 14 / 自分 5
commit で乖離。main の最新 (5daf1ea→ddc6f88) は本セッションが追っていた instruction-level の問題
(分岐極性 bne;b vs beq、+4 li-0、fp schedule) を **既に解決済み**と記録している:

- main 5daf1ea: dispatch bool 単一アーム化 `b=0; if((flags&mask)!=0) b=1;` で「EF vs target =
  416=416 行、reg-masked 100.00%、非 register 差ゼロ」。残差を純粋 coloring に分離。
- main ddc6f88 + follow-up 12: EF base の宣言順 sweep は self=r25/victim=r26 で不動。残差は
  value-numbering の **web 構造差 (coalescing / web split)** に限定。
- main 結論: 唯一の残ブロッカー = EF (命令一致) base で **param を後 pass に分離する coalesce/web
  構造を source から作ること**。次の一手 = coalesce union-find (FUN_0057a1f0 / FUN_00579cf0) trace。
- build 状態 (main): OnKartHit は asm_fn で byte-identical 維持。EF は clean-C 化の最有力 base。

本 worktree の probe_ef.c (handoff 6bd5cd3 由来) は verify_any で reg-masked 97.60% / 16 構造差
(fp schedule 2 + 分岐極性 4 + extra-li 4) を出す = main の「100%」EF とは別物 (古い形)。注: main の
winning EF checkpoint は tmp/CHECKPOINT_ef_instr_matched.c で gitignore、本 worktree に存在しない。

CONSEQUENCE: 本セッションの EMONMIN / DAT_005e8cc0 (FUN_004df460) 調査は、main が既に通過した
instruction 層の問題に対する誤った lever 探索だった。FUN_004df460 が dormant という反証 (iter 2) も
含め、この線は real frontier ではない。real frontier = **coalescing/web 構造** (main follow-up 12)。

NOTE on main の「reg-masked 100%・完全一致」: CLAUDE.md の断定回避方針に照らし、これは未検証の
強い主張として扱う (本 worktree の単一アーム probe_ef.c は 100% を再現しない)。winning EF source が
手元に無いため本 worktree では追検証不能。coalescing trace は worktree 非依存の read-only 調査なので、
そちらを frontier として進める。

RE-ORIENT: 以降は main の open question = colorer の coalesce 機構 (FUN_0057a1f0 union-find /
FUN_00579cf0) を Ghidra で読み、(a) どの web が併合され survivor が何 key を取るか、(b) target の
param が高 key web と coalesce して effective key が上がる構造か、を解く方向に切替える。

## colorer 全鎖を decompile で確定 — coalesce=min-survivor, select=lowest-reg, 支配は degree (2026-06-12, /loop iter 2)

main follow-up 12 の next-step (coalesce union-find trace) を Ghidra 静的 decompile で実施。

### FUN_0057a1f0 (InterferenceGraph.c) = coalesce union-find — survivor は MIN key
- DAT_005e21c8 = union-find parent[] (size = web 数 = DAT_005e8a7c[class])。init parent[i]=i。
- 全 web の move-related node (puVar3[5] の flag &0x10 かつ &0x100==0) を走査。src web=puVar3[10],
  dst web=puVar3[0xd] の root を path-follow で求める。
- 既に同 set → FUN_004dc230 (move 削除)。別 set かつ interference bitmatrix (DAT_005e21cc) で
  非干渉なら UNION。
- **UNION のコード: `sVar5=min(src_root,dst_root); sVar15=max; parent[sVar15]=sVar5`**
  = **survivor (root) は常に MIN key**。merge 後の effective key は 2 web の小さい方。
- 末尾 loop: 全 node の web 参照 (operand list pcVar12+4, stride 0xc) を root に書換え。

→ **決定的: coalescing は web の key を上げられない。** param(key32)が高 key web と coalesce
しても survivor=key32 のまま。**main follow-up 12 の仮説 (b)「target param が高 key web と
coalesce して effective key 上昇」は機構的に否定される。** coalesce で動くのは partner を min に
引き下げる方向のみ。

### FUN_00507a30 (Coloring.c) = select — 最小番号 reg を pop 順で割当
- local_18 = FUN_004fd600(class) = class の割当可能 reg bitmask。
- simplify stack を pop 順に走査。各 node: uVar3 = 利用可能 reg = local_18 − (着色済み隣接の色)。
- uVar3==0 → spill。else **`for iVar4=0..numRegs: if (uVar3 bit iVar4) {color=iVar4; break}`
  = 最小番号の空き reg を割当**。
- pop 順 = simplify 除去の逆順 (Chaitin)。**長命=高 degree web は simplify で最後に除去 →
  select で最初に着色 → 最小番号 reg を取る。短命=低 degree → 最後に着色 → 高番号 reg。**

### 統合モデル (3 関数 decompile で確定、EF frida 実測と整合)
- key は FUN_00435c60 list 順で採番 (args=DAT_005e8a78 が loop2 で最小 key 32/33)。
- EF 実測「key32→r25, key94→r31」(低key→低reg) の真因は **key ではなく degree**:
  param は関数全体 live = 高 degree → 最初に着色 → 最小 reg r25。key94 web は短命 → 高 reg r31。
  key と reg が EF で単調に見えたのは degree と key の偶発相関 (param が最小 key かつ最高 degree)。
- **target が param を r30/r31 (高 reg) に置く = param web を遅く着色 = 低 degree 化が必要。**
  これは main 成果 (3) degree lever (高 degree local の range 削減で param 上昇) と一致。
  coalesce ではなく **param web の live range / degree を下げる source 構造**が唯一の機構的 lever。

### NEXT (worktree 非依存の frontier)
真の open question を再定義: 「EF の命令列を保ったまま param (self/victim) web の degree を下げ、
simplify で早期除去 → 高 reg 着色させる source 形」。次の一手: frida で EF の simplify (FUN_00507b50)
/ select (FUN_00507a30) を trace し、各 GPR web の (key, degree, 除去順, pop順, 割当 reg) を実測。
param web の degree と除去位置を確認し、target の self=r30/victim=r31 にするのに必要な degree 低下幅を
定量化する。degree を下げつつ命令を壊さない source 形 (param のコピー先 web を作る等) を設計する。

### FUN_00507b50 (Coloring.c) = simplify (Chaitin-Briggs) — モデル最終確定
- iVar6 = FUN_004fd650(class) = k (物理 reg 数 = coloring threshold)。
- web を index 順 (DAT_005e8778[class]..DAT_005e8a7c[class]) に走査。degree = node[+0x12]。
- degree < k の低 degree web を除去: 隣接の degree を -1、flag|=2、**stack (piVar10) に prepend**
  (`*node=stack; stack=node`)。除去可能が尽きるまで round 反復。
- 残り高 degree は worklist piVar9 へ。spill 候補 = `node[3]/degree` (Briggs spill cost/degree) 最小を
  optimistic-spill として除去 → stack へ。低 degree round を再開。全 web 除去まで反復。
- select (FUN_00507a30) は stack を **先頭から** 処理 = **最後に除去された web を最初に着色**。

統合: **後除去(高 degree/spill候補) → 先着色 → 最小番号 reg。先除去(低 degree) → 後着色 → 高番号 reg。**
round 内は index(key)昇順走査だが、これは低 degree(短命→高 reg)web の順序にしか効かない。
param は高 degree(全体 live)で低 degree round に入らず spill-heuristic で後除去 → 先着色 → 最小 reg
(EF: self r25/victim r26)。**target の param r30/r31 = param を低 degree 化して早期除去させる必要。**

## 統合結論 (2026-06-12 /loop iter 2 時点、decompile 3関数 + 既存 frida 実測で確定)

OnKartHit の register 残差は **value-numbering の key でも coalesce でもなく、interference graph の
degree (= web の同時 live 数) が支配**する。機構:
1. key 採番: FUN_00435c60 list 順 (args 最小 key)。← reg を直接決めない。
2. coalesce (FUN_0057a1f0): survivor=min key。**key を上げられない** (main 仮説(b)を否定)。
3. simplify (FUN_00507b50): 低 degree 先除去 / 高 degree 後除去。
4. select (FUN_00507a30): stack 先頭 (後除去=高 degree) から最小 reg を割当。
→ **高 degree web ほど低い reg。param を高 reg (r30/r31) にするには param web の degree を下げる
(= live range 短縮 or competing local web 削減) 必要。命令を壊さずにこれを行う source 形が唯一の lever。**
これは main 成果(3) degree lever と完全一致。EMONMIN/DAT_005e8cc0/coalesce 路線は全て否定済み。

### ブロッカー (workflow): 本 worktree は stale で instruction-matched EF base (tmp/CHECKPOINT_
ef_instr_matched.c, gitignore) を持たない。degree lever 実験は命令一致 base 上で行う必要があり、
本 worktree の旧 probe_ef.c (命令差 16) では検証の出発点が違う。次は (a) main の EF base 上で degree
trace + degree-preserving source 設計、を行うべき。worktree 選択はユーザー判断 (orchestration の
merge 方針依存)。

## EF colorer の直接実測 — color=物理reg番号, self/victim が degree 突出で pin (2026-06-12, /loop iter 3)

probe: tmp_probe/probe_color.js + run_color.py。simplify (FUN_00507b50) enter で GPR class4 の全 web
(id 32..202, 171 個) の初期 degree (node+0x12) / neighborCount (node+0x18) を snapshot、select
(FUN_00507a30) leave で color (node+0x14) を読む。probe_ef.c をコンパイル。

OBSERVATION (fact): **color 値 = 物理レジスタ番号そのもの** (color 25→r25, 31→r31)。これで
「select は最小 bit を割当 + bit N = rN」が実証され、degree↔reg の方向曖昧性が解消。

EF callee-saved (color 25-31) 割当 [key, initDeg, flags]:
- r25 ← key32 (self),   initDeg=**135**, 0x2
- r26 ← key33 (victim), initDeg=**137**, 0x2
- r27 ← key46, deg32,  0x42(coalesced)
- r28 ← key47, deg42,  0x42
- r29 ← key50/51, deg47/42, 0x42 (50↔51 coalesce)
- r30 ← key49/52, deg55/77, 0x42/0x2 (49↔52 coalesce)
- r31 ← key94, deg102, 0x2
- color 72/85/126 (key79/92/133, flags 0x4) = spill (物理 reg 範囲外)。

決定的: **self(135)/victim(137) の degree が全 web 中で突出** (次点 key94=102, key52=77)。
最高 degree → 最初に着色 → 最小 bit = 最小番号 callee-saved (r25/r26) を取る。これが arg park の実体。
degree→reg は厳密単調ではない (key94 deg102→r31, key52 deg77→r30 等、coalesce と simplify 順が絡む)
が、self/victim が突出 degree で最下位を取る点は明白。

含意: self/victim を r30/r31 (最高 reg = 最後に着色) にするには degree を他 web 以下 (~100 未満) まで
**大幅に下げる**必要。degree=135 の主因は self が関数全体 live で全 temp (FP 含む 171 web の大半) と
co-interfere すること。target が self を r30 に置く以上、target では self web の co-interference が
EF より遥かに小さい構造のはず。命令を保ったまま self/victim の live overlap を削る source 形が
唯一の未確定 lever。prior work (main af1d7f0 degree levers NEGATIVE / 本枝 PINNED) と整合し、
「instruction-match を保つ degree 低下」は未発見。

未試行の精密 lever 候補: self の derefs を関数前半で local に cache し、FP 重区間 (行 91-112, 185-203)
で self param web を dead にして co-interference を削る。ただし load schedule が変わり命令を壊す risk 大。
次: simplify の除去順 (pop order = 着色順) を trace して、self/victim が「最初に着色」される正確な機構
(高 degree で low-degree round に入れず spill-heuristic 経由か) を確認 → degree 何点下げれば着色順が
ずれるかを定量化する。

## 結合の実証: bool 形を変えると params も命令も同時に動く (2026-06-12, /loop iter 3)

「target/EF 同一命令なら self は両方全体 live=同 degree=同 reg のはず」というパラドックスの解: 本枝は
instr-match を撤回済 (fa4d966)。target と EF の命令は実際に異なり、その差 (特に bool 計算ブロックの
+4 li-0 / 分岐極性、16 差中 12) が web 構造を変え register 割当差を生んでいる = **命令差と register
差は結合**。「pure coloring 残差」(main) でも純 pinned でもない。

実験 (probe_ef_v2.c): 4 bool を直接ブール形 `bX = ((flags & MASK) != 0);` に変更 → verify_any:
- diff 16 → **96 (悪化)**、ただし **self/victim = r25/r26 → r27/r28 に上昇** (target r30/r31 方向)。
- dispatch が target `clrlwi. r0,rX,24` (bool=byte 扱い) に対し v2 は `cmplwi rX,0x0` (word) に変化。

→ bool web 構造の変更で params も dispatch 命令も同時に動く (結合を実証)。原型 probe_ef.c は dispatch
が既に target 一致 (clrlwi)・残差は計算ブロック 16 のみ・self=r25。v2 は params を上げたが dispatch を
壊した。**中間形 (dispatch 維持 [bool=byte] + 計算ブロック差解消 + params 上昇) の探索が frontier。**
target の計算ブロックは結果レジスタ bX(=0) を高位語マスク 0 と比較 RHS に兼用 (fold); EF は別 r4=0。
この fold を誘発しつつ bool=byte を保つ source 形を探す。

## bool 形 variant 3点の結果 — byte/word tension で fold が鍵 (2026-06-12, /loop iter 3)

| variant | bool 形 | diff | self/victim | dispatch |
|---|---|---|---|---|
| 原型 probe_ef.c | `bX=0; if((f&M)!=0) bX=1;` | 16 | r25/r26 | clrlwi (target一致) |
| v2 probe_ef_v2.c | `bX=((f&M)!=0);` | 96 | **r27/r28** | cmplwi (壊れる) |
| v3 probe_ef_v3.c | 原型 + 4個の bX=0 を先頭集約 | 16 | r25/r26 | clrlwi |

OBSERVATION: init 位置 (v3) は無影響 (原型と完全同一)。直接ブール形 (v2) は params を r25/r26→r27/r28 に
上げるが dispatch を clrlwi→cmplwi に壊す (= bool が byte→word 化)。

tension: **target は byte bool (dispatch=clrlwi) かつ params=r30/r31**。byte bool の if-then 形だと
params は r25/r26 に pin、word 化すると params は上がるが dispatch が壊れる。両立には target の
「bX(=0) を 64bit mask の高位語 0 と比較 RHS に兼用する fold」(EF は別 temp r4=0) 由来の web 構造が要る。
この fold は CW の constant/copy-propagation 由来の低レベル codegen 判断で、試した C 形 (init 集約・
直接ブール) では誘発できず。fold は register 圧/web 配置に依存する compiler 内部判断と思われ、source
からの確実な誘発手段は本実験でも未発見。

### 現時点の honest assessment (iter 3 終了)
OnKartHit の param 配置は、**target 一致の byte-bool dispatch を保つ限り r25/r26 に pin される**公算が高い。
機構は完全に解明済み: (1) key=list順採番, (2) coalesce=min-survivor で key 上げ不可, (3) reg=色付け順
(高 degree→先着色→低 reg), (4) self/victim が degree 突出 (135/137) で最下位 pin。param を上げる唯一の
観測経路は bool web 構造の変更 (v2) だが命令を壊す。target の fold を生む source 形は本枝 + 過去 ~50 実験 +
本 mechanism 解析でも未発見 = **instruction-match を保つ source lever は事実上 pinned**。OnKartHit は
現状 asm_fn で byte-identical 維持が妥当。汎用成果 (単一アーム li-fix, colorer model) は他 fn に再利用可。

## bool 形 6 変種 sweep — byte→pin / word→+2のみ、target 不到達 (2026-06-12, /loop iter 4)

target 実 disasm で確定: self=r30, victim=r31, bus=r25 (row7 lwz r25,0x304), rm=r29 (row52)。
dispatch (rows 268-360) は self=r30/victim=r31 を**直接参照** (272 lwz r3,0x28(r30); 357 mr r3,r30;
326/335 ...(r31)) = self/victim は target でも EF でも**関数全体 live = 同 live range**。

bool 計算ブロックの 6 変種を verify_any で測定:
| 変種 | diff | self/victim | bool 型 |
|---|---|---|---|
| 原型 if-then | 16 | r25/r26 | byte |
| v2 直接 bX=(..!=0) | 96 | r27/r28 | word |
| v3 0初期化集約 | 16 | r25/r26 | byte |
| v4 三項 ?1:0 | 68 | r27/r28 | word |
| v5 ULL temp 共有 | 56 | r25/r26 | byte |
| v6 反転 bX=1;if(==0)bX=0 | 20 | r25/r26 | byte |

OBSERVATION (完全相関): **byte bool 形 (target の clrlwi dispatch を保つ) → self/victim は例外なく
r25/r26 に pin**。word bool 形 → self/victim は r27/r28 に動くが (a) target の r30/r31 には**届かず**、
(b) dispatch が clrlwi→cmplwi に壊れる。

決定的含意: self/victim は target/EF で同一 live range なので、register flip (target r30/r31 ↔ EF r25/r26)
は self/victim 自身の degree では説明できず、**他 web (特に bool block の fold: target は結果レジスタ
bX=0 を 64bit マスク高位語 0 に兼用、EF は別 temp) による coloring 順の違い**が原因。この fold は CW の
constant/copy-propagation + register 配置の内部判断で、byte/word/三項/ULL共有/反転の全形で誘発できず。
word 化で params が +2 動くのは bool web が word 化し degree/個数が変わる副作用だが、target の配置 (self を
+5 上げて r30) には到達しない。

### 結論 (iter 4、6変種 + 機構全解明 + 過去~50実験で確定)
OnKartHit の self/victim を target の r30/r31 にする instruction-match な C source は**存在しない公算が
極めて高い**。理由は機構レベルで判明: target の register 配置は EF と (a) 同一 live range, (b) ほぼ同一命令
(16差は bool fold のみ) でありながら逆順 coloring。その逆順は target の bool fold 由来の web 構造に依存し、
fold は C source から誘発不能。**OnKartHit は asm_fn で byte-identical 維持が最終結論**。
汎用成果 (colorer 全機構の white-box: numbering=list順, coalesce=min-survivor, simplify/select=Coloring.c,
単一アーム li-fix) は他 fn に再利用可能。

## 訂正 + 一般化の問いへの回答: main follow-up 7-12 が本セッションを包含・先行 (2026-06-12, /loop iter 5)

本 worktree のノートは main の follow-up 2-12 を欠く (分岐が merge-base cfe8f26 で起きたため)。
main note を確認したところ、本セッションの調査 (colorer 再導出 / degree trace / 6 bool 変種 /
「pinned」結論) は **follow-up 7-12 で既に到達・超越されていた**:

- follow-up 7: 真の lever = spill ratio = **degree/cost** (cost=loop加重使用回数)。最小 ratio=最後着色
  =最低 reg。OnKartHit self/victim は degree 最大(135/137) **かつ** self-> 約20回使用で cost も最大
  → ratio 最小 → r25/r26 pin。OnItemHit は param の使用回数少 → ratio 大 → 高 reg。
- follow-up 8: cost lever (sub-object を冒頭 cache) **NEGATIVE** — cache local が高 reg を奪い self 沈下。
  本セッションの「pinned」結論はこの follow-up 8 と同一地点の再導出。
- follow-up 9: **degree lever 確定** — 高 degree **local** の live range 削減で param 上昇 (D1: self
  r26→r27)。天井 r27 = dispatch の bool 4 個が正当に co-interfere するため剥がせない。**family 診断
  確立** (param park 条件 = param より高 key の callee local が param の最終 simplify pass で co-interfere)。
- follow-up 10: 「命令同一なのに param-top」は**偽の前提**。reg-masked diff で真の命令差 37
  (+4 li-0 bool init, fsubs schedule)。→ 本セッションが見た 16 差と同種。
- follow-up 2-4: **OnFallOffOrDeath (param TOP) と CancelActiveEffect (param BOTTOM) はほぼ同一構造で
  両方 plain C matched** = 両極到達可能。**最小 flip 形 M2a** (CAE + 遅い条件 block + 内部 call +
  tested web → param r31 flip) 特定。672 fn scan で param 配置は一様分布。

### ユーザーの問い「OnKartHit が特定できないなら他の超大多数も同様では?」への回答 (NO)

機構的・実証的に **一般化しない**:
1. **672 fn whole-binary scan**: param home は top 35% / mid 33% / bottom 32% と一様に散る。プロジェクトは
   既に数百 fn を match 済み = param 配置は大多数で source から制御できている (でなければ match 不能)。
2. **両極が plain C で実証済み**: OFOD (TOP) / CAE (BOTTOM) のほぼ同一コードが両方 matched。
   配置は source 構造の関数で、両方向に到達可能。
3. **大多数が match する理由**: 自然な C が自然な web 構造を生み、決定的 colorer が target reg に写す。
   問題が出るのは (a) 残差が register-identity のみ かつ (b) target が自然 C で再現できない web 構造を
   取った場合に限る。
4. **OnKartHit は病的な tail**: self/victim が degree 最大 **かつ** 使用回数最大 (ratio 最小 → 最低 reg)
   + dispatch の bool 4 個が co-interfere 天井 (r27)。この組合せは稀。代表例ではない。

### kernel of truth (ユーザーの懸念の正しい部分)
残差が register-identity のみの fn 族 (register-identity family) には実際に難物が存在し、一部は asm_fn
維持。ただしこれは**少数 tail** であって「超大多数」ではない。colorer の white-box 知見 (k-colorable +
min-key param + degree/cost ratio → park 予測) は **撤退判定の高速 triage** に再利用でき、tail を早期に
asm_fn 判定して bulk に注力する戦略が成立する。

### 本 worktree の知識欠落と推奨
本セッションは main の follow-up 7-12 を欠いたまま再導出し follow-up 8 地点に逆戻りしていた。新規貢献は
colorer 機構の独立再確認 (coalesce=min-survivor を decompile で明示) のみで、frontier には未達。
推奨: main の follow-up 7-12 + 672 fn dataset + M2a transplant 知見を取り込んで継続 (degree lever 天井
r27、OnItemHit vs OnKartHit の coalescing 差、M2a 逆 morph が真の frontier)。OnKartHit 単体は 40+ 実験
投入済みで ROI 低 → asm_fn 維持が妥当、汎用 triage 知見が実利。

## merge 後の検証: coalesce 閉じ + I1 再構成 negative (2026-06-12, /loop iter 6, post-merge)

main follow-up 2-12 を merge 後、本セッションの貢献を frontier に接続:
- **coalesce=min-survivor (本セッション decompile) は follow-up 9/12 の「未 trace」coalesce 仮説を閉じる**:
  FUN_0057a1f0 は parent[max]=min の union-find で survivor=最小 key。param(key32) が高 key web と
  coalesce しても key32 のまま → 「target param が coalesce で effective key 上昇」は機構的に否定。
  follow-up 9「単一 web・命令同一で param-top = coalescing 疑い」/ follow-up 12「残差=coalesce 構造」の
  coalesce 期待は両方 negative。param-top は coalesce 由来ではない。
- **I1 (inline FlagBit accessor) 再構成 = NEGATIVE**: probe_i1.c (bool quad を static inline FlagBit
  化) standalone verify → diff 96 / self=r27/victim=r28。main follow-up 2 の「416=416・permutation 1つ」は
  **行数一致のみ** (I3 は difflib LCS 71%) で実類似度は低く、word-bool 同等 (self r27 止まり + 命令破壊)。
  inline-helper lever も match を生まない (recheck の overstated-claim 系統と一致)。

集約された全 lever 結果 (~50 実験 + 2 model 導出 + inline 再構成): self を r25/r26 から動かす全形が
**r27 止まり かつ命令破壊**。match 維持で param-top にする C source は依然未発見。残る唯一の明示的
未完 frontier = follow-up 3 の **M2a 逆 morph** (CAE+M2a [flip✓] を OnKartHit へ morph して flip を殺す
成分を特定)。資産は gitignore で消失、CAE source から再構成を試みる。

## 全ゲーム走査: fold は OnKartHit ほぼ固有、matched donor 無し (2026-06-12, /loop iter 7, user idea)

ユーザー提案「ghidra でその出力をする場所を探せ」を全スコープで実行。fold (0 初期化した callee-saved
bool reg を 64bit AND の上位語 0 として and/xor で兼用) を build/GNLJ82/asm 全 3565 ファイル
(~7000 関数) で走査 (signature = ある callee-saved reg が `li,0` かつ `li,1` かつ and/xor の operand)。

OBSERVED (決定的):
- **fold する関数はゲーム全体で 2 個のみ**: KartItem_OnKartHit (r25-r28, 4 bool 全 fold) と
  fn_8023B318 (r28, 1 bool)。後者は**無名 = 未 decompile/未 match**。
- 同 TU の matched フラグテスト関数 (CarObject_OnItemHit `&0x40ULL`, CarObject_UpdateCoinSpeedBonus
  `&0x800000ULL`) は **fold せず** `li r4,0x0` (volatile scratch) を mask-hi に使い、それで target と match。
  = bool が 1 個・即使用 (短命/volatile) なので fold 不要。我々の OnKartHit 再構成も同じ unfold 形 = 「普通」の出力。
- matched 関数は皆「class-1 recipe」二アーム形 `if((f&M)==0){b=0}else{b=1}` を使う (短命 bool で match)。
  OnKartHit の b28-b25 に二アーム適用 → diff 37 / self r26 (単一アーム 16 / self r25 より params↑だが命令悪化)。

含意 (ユーザーの問いへの最終的な答え): **fold は再現可能な recipe ではなく、OnKartHit にほぼ固有の
稀な compiler 出力**。コピー元になる matched donor がゲーム内に存在しない。OnKartHit target が param-top
なのは、この稀な fold (4 bool が 3 reg に収まり高 reg を解放) を伴う web 構造を取ったため。matched 関数群は
我々と同じ unfold 形で「普通に」match している = **大多数の関数は fold 不要で match する** (一般化しない
ことの追加実証)。fold 唯一の他例 fn_8023B318 は `bool b=(flag&mask)!=0` を call 跨ぎで保持する C++ bool
構造で、OnKartHit の 4×64bit とは別形のため直接転用不可。

→ fold を C から確実に誘発する手段は依然未発見。ゲーム内に手本が無い以上、frida で fold を切り替える
compiler 内部判断 (64bit AND 下位化時の定数 0 の CSE/再利用) を直接読むのが残る唯一の確度ある道。

## C++ 構造検証 + TU は unmangled = free function 確定 (2026-06-12, /loop iter 8, user: 「C++なのにCで試すな」)

ユーザー指摘「ゲームは C++ 製、compiler 理解から fold する struct/class を作れ、C ばかりは筋違い」を検証。

OBSERVED:
- **OnKartHit TU は mangled シンボルが 0 個** (build/GNLJ82/asm/game/auto_ONKARTHIT_block.s の全 .fn が
  KartItem_* / CarObject_* の clean name、`__` 含むものゼロ)。= この TU の関数は C++ method ではなく
  **free function 相当** (extern "C" か C コンパイル)。decomp はこれらを **C (-lang=c) で ~20 関数 match
  済み** = この TU では C が実証済みの正しい方法で、「C で試す」は筋違いではない。
- C++ メソッド再構成 (probe_cpp1-3.cpp、this=self、inline bool accessor、bool/uchar):
  - cpp1 (bool + accessor): self=r27, li0=11, regmaskdiff=148 (word-bool 挙動、dispatch 破壊)。
  - cpp2 (uchar 単一アーム, method): self=r25, regmaskdiff=72 (pin、C++ 移植ノイズ)。
  - cpp3 (uchar class-1 二アーム, method): self=r26, regmaskdiff=72。
  - C++ method 化しても byte bool は r25/r26 pin、bool 型は r27、いずれも fold せず。さらに method 化は
    mangled シンボルを生み target 名 `KartItem_OnKartHit` と不一致 = 構造的にも誤り。

結論: C++ 構造 (method/this/bool/accessor) は fold も param-top も生まない。OnKartHit TU は unmangled
free function なので C 再構成が構造的に正しく、16-diff 残差 (fold + fp schedule) は **C/C++ の source
構造問題ではなく、compiler の constant-0 再利用 (callee-saved bool reg を 64bit compare の 0 に兼用するか
volatile scratch を materialize するか) という割当判断の artifact**。struct layout は ABI 固定で変えられず、
class 化も unmangled に反する → 残る source lever は無い。

唯一残る確度ある道 (compiler 内部): CW codegen で「64bit AND/compare の下位化時に必要な定数 0 を、
0 を持つ callee-saved reg で兼用するか scratch を materialize するか」を決める箇所を Ghidra/frida で読み、
発火条件を特定する。条件が register 圧依存なら命令を保ったままの誘発は不可能な可能性が高い。

## fold の compiler 機構を特定: ValueNumbering.c の operand 置換 (2026-06-12, /loop iter 9, user: 「compiler を追え」)

ユーザー指示「compiler 内部で fold 判定箇所を追え」を実行。mwcceppc の codegen module を assert 文字列で
地図化 (ValueNumbering.c@0x5bbb28, InstrSelection.c, Operands.c, Coloring.c, InterferenceGraph.c 等)。

**fold 機構を特定 = FUN_00508140 (ValueNumbering.c) 冒頭の operand 置換**:
各命令の各オペランド (use, *pcVar7==0 && flags&0xb==1) について VN テーブル `(&DAT_005df954)[class]`
(web*0xc 単位) を引き、その value-number の**代表 web iVar2 = piVar8[1]** が同値 (`piVar8[0]==web[iVar2][0]`)
なら **オペランドの web 参照を代表 web に置換** (`*(short*)(pcVar7+4)=iVar2`)。
→ fold = 64bit AND の mask 上位語の**定数 0 オペランドが、bool web(=0)と同じ value-number を持ち、
bool web が value-0 の代表になっているとき、VN がオペランドを bool web に置換**する現象。

OBSERVED (実証、fold は source から誘発不能):
- 最小ケース全滅: m.c (callee-saved bool + 64bit AND) / m2.c (高レジスタ圧 10 live) / m3.c (b=0 直後に
  AND, 間に call なし) / m4.c (bool 2 個) — **どれも fold せず**、compiler は普遍的に `li rScratch,0` を
  materialize し (複数 AND 間で scratch は共有するが) bool web とは別に保つ。
- C/C++ の全 OnKartHit 再構成も unfold (mask-hi-0 が別 web)。
- 全ゲーム走査でも fold するのは OnKartHit + 無名 fn_8023B318 のみ (2/7000)。

CONCLUSION (compiler 追跡の最終): fold = ValueNumbering の operand 置換が、定数-0 オペランドを bool web
に統合する稀な現象。発火には「bool web が value-0 の代表 かつ 定数-0 オペランドが同 value-number」が必要
だが、これは VN の代表選択 (web 生成順 + value-number 割当の global 状態) に依存し、**source の型/構造/
レジスタ圧のいずれからも制御できない** (最小再現が全滅、7000 中 2 関数のみ)。OnKartHit の clean-C 化を
阻む唯一の差 (この fold) は、命令列を保ったまま source から誘発する手段が compiler 機構レベルで存在しない。
→ **OnKartHit は asm_fn 維持が機構的に妥当**と確定 (黒箱の park を VN operand 置換まで完全 white-box 化)。
assets: tmp/foldmin/m.c m2.c m3.c m4.c, tmp/foldsweep/。compiler module map は本節。
