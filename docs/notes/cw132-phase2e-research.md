# Phase 2e research: dead-counter SOLVED (invisible-use), per-site coloring levers, mtx-loop still open (2026-06-11, batch_research_phase2e)

## Headline results
1. SOLVED: the "dead-counter-in-ctr-loop" idiom (CarObject_HandleItemEffect 0x8004F858 loop 1).
   The counter is NOT dead in the original IR - it has an INVISIBLE USE: it is passed as an
   extra (ignored) argument to the post-loop call. `ItemStateGuard_IsActive(guard, i)` under a
   K&R empty-paren extern makes the web live; regalloc coalesces i straight into r4 (the arg
   slot, vacated because itemId moved to r31), so the use costs ZERO instructions and the loop
   region becomes byte-identical (li r4,0 / addi r4,r4,1 / bdnz, no read anywhere).
2. CarObject_HandleItemEffect taken 98.62% -> 99.93% (494 insns, 7 diff rows left, all one web:
   `handled` colored r29 vs target r22). Paste-ready patch: tools/compiler_probe/p2e_handleitemeffect_9993.patch.
3. REFUTED (correction to cw132-dead-counter-ctr-loop-hardblock.md): the class is NOT a hard
   block, and "solving the counter cascade-fixes the lane-clear site permutations" is false -
   the counter was fixed and the 84 permutation rows persisted until separately solved (below).
4. CORRECTION to cw132-mrsrinit-phase2c-research.md hypothesis: post-splice optimization DOES
   include iterative DCE (probes g1/g2: a dead counter added to the exact CalcMaxSpeed helper
   whose `mr` init survives is deleted, both dead-in-callee and live-in-callee/dead-at-site).
   Only copy/const FOLDING is FE-only. So no spliced web can survive by being dead; every
   surviving "dead-looking" web has a real use hidden by coalescing.

## Observations (facts)
- Binary-wide mining (p2e_mine_deadctr2.py): 76 ctr loops with an up-counter never read between
  its init and the next write. Inspected cases (fn_801DCCE4, ItemAliasTable_LookupSlotIndex,
  OSCreateHeap) are all live via RETURN-VALUE coalescing: the counter is the return value on the
  hit path, allocated to r3, so the "read" is the implicit blr - zero instructions. 46 of 76
  have `mr rX,rY` inits (the MainUpdate mtx-loop family, see below).
- h3 probe (p2e_deadctr4.c): counter as ignored 2nd call arg survives; in a minimal fn it costs
  one `mr r4,r5` because the itemId param occupies r4; in the real fn (itemId saved to r31) it
  coalesces to zero instructions. All 8 previous hardblock probes plus volatile / register
  volatile / exceptions-on / big-preopt-helper / non-leaf-helper / count-param variants stay
  negative (p2e_deadctr.c / p2e_deadctr2.c).
- ONE-HOME-PER-VARIABLE: CW 1.3.2 gives a named variable a single register home across all its
  disjoint live ranges. Verified: making the boost-site owner a fn-scope variable unified all
  three sites to one color. In the target, ALL FIVE owner/obj webs across the switch (3 lane-
  clear sites + boosts at 0x17/0x141/0x142) are r29 -> the original used one fn-scope obj.
  Its r29 home is forced by interference: inside each lane-clear block, 7 block-locals + obj
  fill the whole stmw pool r22-r29, leaving obj only r29.
- Per-site decl-order coloring: lane-clear written as per-case BLOCKS (not helpers) lets each
  site take its own decl order. Direction (first-declared -> lowest vs highest) OSCILLATES per
  configuration and per site; it is cheap to read off a build and re-tune (2 iterations here).
  Decl orders that match target (with fn-scope obj declared among fn locals, any position):
    site1 (case 0xe group):  tbl, i, owner, effectState, mediaReq, cursor, itemId
    site2 (case 0xc group):  itemId, cursor, owner, effectState, mediaReq, tbl, i
    site3 (case 0x141):      itemId, cursor, owner, effectState, mediaReq, i, tbl
  (block-local `ItemStateBlock *q` declared last in each; shadowing `int itemId` in-block is fine)
- Static-inline helper copies per site (KartItem_CancelLanes_inl/2/3 with per-copy decl order)
  also work for the lane-clear bodies (84 -> 14 diff rows) but cannot give the boost-site owner
  r29; the block + fn-scope-obj form supersedes them.
- Residual (source-closed this batch): `handled` (u8, fn-scope, written in every switch arm,
  read once after) colors r29, sharing with obj (they never interfere); target has r22. Inert:
  7 fn-scope decl permutations, register keyword on handled/obj, handled=1 statement motion
  (changes schedule = worse). 7 diff rows = li/mr/clrlwi of that single web.

## mtx-multiply loop (CarObject_MainUpdate 0x8004DA44, flavor 5) - still open, mechanism narrowed
- Target loop traits: NO strength reduction on out (slwi rK,2 + stfsx for every store, out base
  r6 materialized once), k+=4 kept twice (unmerged), a-row elements CSEd into 4 regs per row
  (source row-locals), b loads folded to r1 const offsets, dead i web kept (init `mr r4,r5`).
- The same loop body appears in 14+ unmatched fns (Camera_RotateByYaw, KartMovement_RotateByYaw /
  _Init / _CollisionUpdate, TornadoEffect_ComposeRenderMatrix, ItemEffectSpin_TickWorker,
  ExplosionTumble_Update, TornadoLift_Update, ItemEffectImpact_Tick, fn_801DEF94 family x6,
  fn_8019A9BC, fn_8019C6B4, ...; see results_p2e_mine2.tsv `mr` rows) -> a shared (header-)inline
  MtxConcat-like helper; solving it unlocks all of them.
- Probe results (p2e_mtxmul*.c): every -O4/-O3 build SRs the first-row stores into a pointer IV,
  merges k+=4+4 into +8, and deletes i. -O2 produces the no-SR stfsx shape but no ctr loop.
  Helper vs standalone vs direct: same. `k = 0; for (i = k; ...)` opaque-init: no. volatile
  float *out: ignored (identical output). #pragma optimization_level 2 island: ignored by GC/1.3.2.
  Accumulator-chain spelling (f = a0*b[0]; f += a1*b[4]; ...) fixes the fmuls first-pair
  reassociation and the a-row local CSE - keep it for any retry.
- Reading (hypothesis): the target shape looks like O2-grade loop codegen finished by O4-grade
  late backend (ctr conversion, scheduling, regalloc). No source lever found under production
  flags. Untried axes for a next batch: two nested loops (4-row x 1 inside), `*(out + k)`
  per-store pointer arithmetic, unsigned/short k, and checking whether i has an invisible use of
  the h3 kind through a different call signature (r4 is occupied by &s.mA at the next call, so
  the plain extra-arg trick does not fit MainUpdate).

## Per-fn status
- CarObject_HandleItemEffect 0x8004F858: 99.93%, 7 rows (handled web color). Patch saved;
  promote NOT committed (TU must stay sha1-green). Next session: hunt the handled-r22 lever
  (scope of handled, boost-result spelling, switch-arm write forms).
- CarObject_MainUpdate 0x8004D404: parked, no in-TU attempt this batch (research only).
- KartItem_ApplyImpactReflectAndDampVelocity 0x8004B140 (priority 3) and
  CarObject_ProcessWarpAndDash 0x8004D1A8 (priority 4): NOT attempted - budget consumed by
  priorities 1-2. Note for priority 3: re-examine the chain li-0 with the invisible-use lens
  (is the 0 a variable with a hidden use - ignored call arg or return-coalesced web?) before
  any more spelling probes.

## Probe harness added (tools/compiler_probe/)
p2e_run.py (deadctr/mtx classifiers), p2e_deadctr{,2,3,4}.c, p2e_mtxmul{,2,3,4,5}.c,
p2e_mine_deadctr{,2}.py (binary-wide miners), results_p2e_*.tsv, target_mainupdate.txt,
p2e_handleitemeffect_9993.patch (apply onto src/game/auto_ONKARTHIT_block.c for retry).

## Part 2 (2026-06-11, batch_research_phase2e_b): handled-r22 lever hunt - NEGATIVE, new share-pick invariant found

### Headline
1. CarObject_HandleItemEffect 0x8004F858 stays parked at 99.93% (7 rows, handled web r29 vs
   target r22). ~28 additional probes, ALL negative for the flip; but the probe matrix
   isolates a NEW allocator invariant (below) and refutes the unification hypothesis.
2. NEW INVARIANT (observation, robust across 20+ configs): CW 1.3.2 always gives the
   low-priority fn-scope u8 flag the SAME register as a fn-scope POINTER sibling (obj/obj2),
   wherever that pair lands. H1 (helper form) moved the obj-pair web to r22 and handled
   FOLLOWED it to r22 (read-site row matched target for the first time); c9 (block-local obj
   in lane-clear arms) left handled glued to the remaining fn-scope obj2 at r29. The pairing
   itself never broke. Target needs handled (r22) DECOUPLED from obj (r29) -> the original
   source must break this pairing by a mechanism not found this session.
3. REFUTED: "handled unified with the lane-clear loop's block itemId temp" (one-variable
   theory). Probe P1: int handled doubling as loop temp -> handled grabs r29 FIRST (outranking
   obj, which gets pushed to r28) and the boost def emits `clrlwi r29,r0,24` instead of
   target `mr` (u8->int conversion artifact) => original handled was u8-typed at the boost
   def AND separate from the loop temp.

### Probe matrix (all on top of p2e_handleitemeffect_9993.patch, driver tools/compiler_probe/p2e_hie_check.py)
- P1 unify handled+loop-itemId as int: 98.22%, pool rotated, clrlwi artifact. NEGATIVE (2 new facts).
- P2 block-scope handled (switch+read wrapped in block): inert (same 7 rows).
- P3 extra named temp web (et = self->owner->effectTable): inert.
- renames x9 (h/ok/ret2/res/flag2/bHandled/x/zz/aa): ALL inert -> symbol-name/hash axis closed.
- q decl moved first in each lane-clear block: inert.
- handled fn-scope decl position x9 (all 10 slots now covered incl. previous batch): ALL inert
  -> fn-scope decl-order axis CLOSED exhaustively for this web.
- copy-coalescing web-ancestry probes: c1 (read via fn-scope h2=handled), c3 (arm def via
  block-local t), c4 (boost def via block-local t), c5 (all), c8 (obj split into obj/obj2 for
  boost arms - output identical, handled still r29): ALL inert.
- H1 helper form (3 static inline copies, obj passed as arg => arg-coalescing): 494/494 insns
  preserved, whole stmw pool ROTATED: obj+handled = r22 (read site matched!), site locals
  climbed r23..r28 with direction flips. 98.48%. Shows inline/block structure is the ONLY
  lever class that moves the pair - but it moves obj along with handled.
- c9 block-local obj in lane-clear arms + fn-scope obj2 at boosts: lane-clear pools rotated
  (block obj=r22), handled stayed r29 with obj2. 99.49%.
- c11/c12/c13 dead handled=1 writes (inside 0x141 block end / after block / in 0x142 arm)
  hoping interference is computed before DCE: ALL inert -> dead defs are eliminated BEFORE
  the interference graph is built (FE or early opt). Closes the dead-write-interference axis.

### Hypotheses for a future session (untested)
- The share-pick may be an affinity recorded between a u8 flag web and the pointer web used
  in its defining call's args (obj is an arg of the boost call defining handled at 3 sites;
  most-recently-dead web at every handled def is obj). If so the original would need handled's
  defs NOT adjacent to obj death - but li placement is fixed by the match, so this suggests
  the original differed in IR only (e.g., C++ front end artifact; TU is -lang=c).
- fp-numbering-family analog: residual is GPR register identity only; binary-level allocator
  research may be the only unlock. Park verdict: source-closed for now, same family treatment
  ("~99%+ with single-GPR-web residual -> park, no probe budget").

### Priority 2: KartItem_ApplyImpactReflectAndDampVelocity 0x8004B140 chain (95.19% park stands)
- Invisible-use lens applied to the chain's r6 web: r6 = VACATED 4th-arg register (outZ saved
  to r31 in prologue) - same vacancy pattern as the solved dead-counter (r4). But the web has
  a NORMAL visible read (`clrlwi. r0,r6,24`); there is NO hidden use; the residual is the arm
  li-0 deletion + init survival combination, not liveness.
- New probes (appendix-B C re-staged then reverted): F0 no-init else-if chain
  = identical to ledger probe 1 (arms keep 4x li r0,0). F1/F1b OR-compound class-1 canonical
  (then=0/else=1, with/without init): beq-fold collapses every link (no diamond survives;
  class-1 then=0 trick does NOT transfer to multi-link ||). F2 goto-out form: init li SURVIVES
  (li r5,0 - first form to keep it!) but links fold to beq.
- Synthesis: target shape needs BOTH (a) init survival = some match path must NOT redefine b
  (F2 proves the mechanism) AND (b) bne+b diamonds = arms non-empty at fold time with content
  deleted LATER (class-1 mechanism = coalesce with an independent live zero web). The chain
  has no independent zero web, and manufacturing one without instruction cost was not found
  (FE const-prop folds u8 zero copies; probe-3 ledger). No C handle in 4+4 probes total ->
  park confirmed; unlock likely binary-level or needs a zero-web donor discovered elsewhere.

### Priority 3: CarObject_ProcessWarpAndDash 0x8004D1A8 - not attempted (budget)
Transferable insight from Part 2 for the next retry: the self/mov r31<->r30 swap looks like the
same fn-scope pair tie-break family as handled/obj (symbol-level levers proven useless there;
prior ledger agrees). The ONLY lever class that flipped pair placement this session was
inline/block restructuring (H1/c9). Suggested 2-probe retry: (1) wrap the dash-apply block
(9-clear + GetParam + stores) in a static inline helper taking self (arg-coalescing keeps the
web count but changes allocation order); (2) split mov into per-region variables (warp-mov
block-local, dash uses existing m temps) to see if self can win r31.
