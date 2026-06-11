# CW1.3.2 class-2 / loop-copy recipe expansion (batch_promote_class2_expansion, 2026-06-10/11)

Batch: KartItem_OnKartHit 0x8004A238, KartItem_Tick 0x8004BAAC, ItemEffect_Trap 0x80051834,
ItemEffect_Projectile 0x80051A70 (TU src/game/auto_ONKARTHIT_block.c, -use_lmw_stmw on).
Result: 4/4 parked (96.38% / 98.83% / 85.34% / 88.40%), all residue register-identity or
instruction-selection-identity. Paste-ready bodies + reapply diff in the batch HANDOFF appendix
(docs/drafts/Class2_expansion_nearmatches.handoff.md; the Appendix-A TU header diff is
already merged to main).

## Observations (facts, reproduced in builds)

### Class-2 / struct copy mechanics
- ESCAPE-SERIALIZATION (Trap): if any member address of a struct escapes via call arg
  (s.vecA passed to ItemEffectDamp_TryArm), the backend serializes the same struct's
  16-float loop copy into single-register lfs/stfs pairs. Splitting the escaping vec into a
  separate struct object restores the parallel unrolled form.
- Escape also blocks FE store-forwarding: read-backs of escaped-struct slots survive to the
  late pass and become frsp; a fully non-escaped struct gets raw forwarding, and in one
  Projectile probe its stores were entirely DSE'd.
- `(float)(double)` cast forces frsp on a FORWARDED read-back, but is ELIDED on a direct
  field load (Projectile build 4). Lever only works on forwarded values.
- (Tick) A 16-float zero-fill loop + 4 diagonal const stores + 12 transpose stores all
  survive (no same-slot DSE) and interleave by scheduler; plain `for (i=0;i<16;i++) s.m[i]=lbl;`
  followed by straight-line overwrites reproduces the target store soup byte-pattern (only
  callee-saved reg names differed; see partition family below).
- 3-iteration loops FE-unroll with no class-2 disturbance; 16-iteration loops backend-unroll.

### Control flow / locals recipes (new, verified in Tick build steps)
- Join-variable coalescing: `spdJ = lbl; if (spd <= spdJ) { s.v[2]=spdJ; ... } else { spdJ = spd; ... }`
  coalesces the join home with the compare-constant register: then-arm emits NOTHING
  (stores reuse the const reg), else-arm emits exactly one `fmr`. Writing the const
  assignment inside the then-arm instead produces an extra fmr.
- Float call-result through a 4-way branch join: assign `vol = Saturate_Double(...)` in each
  arm and call `SoundCtrl_SetVolume(snd, vol)` once after the join; vol stays in f1, no fmr.
- Wrap-loop reload asymmetry: `while (x > 1.0f) x -= 1.0f;` target reloads the field in the
  body (needs `self->f = VF(self->f) - lbl;` volatile read), while `while (x < 0.0f) x = lbl + x;`
  target CSEs the check load into the body (plain spelling). Same field, opposite discipline.
- GPR scratch/callee assignment follows LOCAL DECLARATION ORDER: declaring `int i2; int off;
  KartMovementTickView *mv5;` then `SpeedTableEntry *e;` in an inner scope yielded the target
  r4/r5/r6/r7 assignment; with `e` declared before `mv5` the two swapped. Strong, cheap lever.
- Cap-up form `if (best >= K) { best = K; }` (then-assign, NO else) = fcmpo + cror ge + bne-skip
  + fmr. The empty-then/else-assign form inverts the branch (beq) and does not match.
- Named temp controls fmuls operand order: `float rr = a / b - c; f(rr * drift, ...)` puts rr
  first (target); inlining `(a / b - c) * drift` got commuted to drift-first.
- Hoisting `void *snd = self->soundCtrl;` before a call whose later arg contains another call
  forces snd into a callee-saved reg before the inner call (target r30 pattern); passing
  `self->soundCtrl` inline loads it AFTER the inner call (volatile reg) instead.
- Empty-paren extern decls promote float args to double (K&R); typed prototypes are required
  for any callee taking float in f1.. (e.g. KartAudioChannel_PlayColorMatchSE(void*,int,int,float)).
- class-1 u64-flag recipe `if ((flags & MASK) == 0) { b = 0; } else { b = 1; }` reproduces the
  bne/b/li-1 diamond with the li-0 arm coalescing into the mask-hi zero register, for bools that
  live in VOLATILE regs (Tick 0x30ULL site matched). For callee-saved bools (OnKartHit b27/b28)
  the coalescing FAILS: 4 extra li residue. Volatility of the bool is the precondition.
- Cross-call product-only-callee-saved (mulli idx*stride kept callee-saved, lis/addi table base
  rematerialized after the call) is what plain `tbl[idx].field` spelling produces NATURALLY.
  The earlier hard-block classification of this pattern was wrong.
- Volatile aux-pointer reload lever: `(*(View * volatile *)&drv->itemBus)->flags` forces the
  pointer reload without disturbing the u64 field access.

### fp callee-saved partition family (source-closed, new instance)
Tick entry has five long-range fp values: 0.0 const, velX, velY, velZ, 1.0 const.
Target: f31=0.0, f30=velX, f29=velY, f28=velZ, f13(volatile)=1.0 (= plain statement order).
Mine, across FOUR probe shapes (statement reorder; zero-loop before/after stores; named locals
k0/vx/vyv/vz/k1; named k0 only + compare via k0; reads+squares moved before/after transpose):
always a pairwise swap velY<->0.0 and velZ<->1.0 (f31=velY, f29=0.0, f28=1.0, f13=velZ),
with velX=f30 a fixed point. Source-closed like the StlList GPR partition family; ~32 rows
+ ~30 cascaded volatile-numbering rows. Cast-read values (ty/tx/tz read-back order) rank top
in my builds; constants rank top in target.

### Instruction-selection residue (source-closed in this batch)
- `mr r5, r4` for `off = i2` (i2 just set to 0): every spelling tried (`off = i2;`,
  `off = i2 = 0;`, `off = (unsigned int)i2;`) constant-propagates to `li r5, 0`. 1-row pair.

## Hypotheses (not established)
- fp callee-saved priority appears related to the order in which (float)(double) read-back
  rewrites touch values (first-read ranks f31), but no model tried predicted all four probe
  outcomes; possibly the target source produced frsp-on-register read-backs WITHOUT explicit
  casts (its priorities look like natural creation order), via a mechanism not yet identified.
- `one`(=1.0f) loop-invariant compare constant: removing the named local and comparing against
  the lbl directly changed nothing fundamental; its f0-vs-f2 placement is believed to be part
  of the same numbering cascade.

## Trial matrices
- KartItem_Tick (6 builds): 96.82 -> 98.31 (operand orders, snd hoist, VF wrap loops, cap form,
  decl order) -> 97.77 (named-locals probe, regression) -> 98.73 (revert + spdJ coalesce) ->
  98.79 (k0 probe, one removal) -> 98.83 (reads-early probe; alloc invariant). Park.
- KartItem_OnKartHit (8 builds): 77.90 -> 96.38. Parked on GPR partition + callee-saved bool li
  + vcall r6-vs-r12 x6 + f3/f5 swap.
- ItemEffect_Trap (12 builds): 44.94 -> 85.34. Escape-split solved block 1; region-2 eager
  per-component scheduling vs target batched 3-frsp+3-muls never matched across 5 shapes.
- ItemEffect_Projectile (6 builds): 85.42 -> 88.40. Remaining: &vecA addi hoist, eager
  scheduling, fp naming mirror.
