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
