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
