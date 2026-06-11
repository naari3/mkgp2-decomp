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
