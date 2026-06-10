# Phase-2a recipe in-TU validation (2026-06-11, batch_promote_phase2a_validation)

Target fns: KartItem_TickStatusEffectsByFlag 0x80050CF0 (fp residue 23 instrs) and
KartItem_PerFrameStep 0x8004C320 (91-row residue). NEITHER promoted. The phase-2a
recipe was validated in-TU and came back NEGATIVE for both residue classes, with
the mechanism boundary now precisely mapped. 10 in-TU build trials + 12 compile
probes (copyprobe shapes documented below).

## A. Direct member-to-member copy recipe: INAPPLICABLE to chased-src copy regions

Applying `mtxs.m[i] = mv->mtx[i];` (16x, no named temps) to the PerFrameStep
copy region SERIALIZES (lfs f0/stfs f0 pairs x16), not the width-8 batch.
Root cause found by bisect (9 minimal probes, same production flags):

| src pointer form | result |
|---|---|
| `const Mv *mv` function PARAM | batches 16-wide: lfs f30,f31,f13..f0 (research s8_member shape) |
| non-const param | serialized |
| `const Mv *mv = self->movement` (const LOCAL, chased) | serialized |
| `(const float *)` cast of chased ptr | serialized |
| `__restrict` on src and/or dst locals | ignored (serialized) |
| static inline helper w/ const param (16-wide or 8+8) | serialized - the CW inliner DROPS the param no-alias property |

=> CW 1.3.2 hoists pointer loads over stack stores ONLY for loads through a
const-qualified TOP-LEVEL pointer parameter. The s8_member repro worked because
its src was `const F8 *` param. Any fn whose copy source is loaded from a struct
member (PerFrameStep: mv = self->movement) can NEVER take the FE-batch path.
Recipe precondition to add to the ledger: "src is a const pointer param".
Also: even when it batches, width is 16 (f30/f31 spill into callee-saved),
not the target's 8-deep alternation - the alternation is the named-temp
pipeline shape, NOT an FE batch.

## B. NEW positive result: pipeline def order fixes the copy-region EMISSION

The 97.87% draft defined the temps t7=mtx[7] first .. t0=mtx[0] last, which
emits the 8 loads at DESCENDING offsets (0x74 first) - the target emits
ASCENDING (0x58 first). Rewriting the pipeline with ASCENDING defs
(t0=mtx[0] first, refills t0=mtx[8] first, stores m[0] first - block below)
makes the emission byte-exact vs target (load8 / store-refill alternation /
store8, all offsets in order). Residue left = a PURE 8-register mirror:
mine t0..t7 = f0..f7, target = f7..f0.

```c
float t0, t1, t2, t3, t4, t5, t6, t7;
mode = self->physModeD4;
t0 = mv->mtx[0];  t1 = mv->mtx[1];  t2 = mv->mtx[2];  t3 = mv->mtx[3];
t4 = mv->mtx[4];  t5 = mv->mtx[5];  t6 = mv->mtx[6];  t7 = mv->mtx[7];
mtxs.m[0] = t0;  t0 = mv->mtx[8];
mtxs.m[1] = t1;  t1 = mv->mtx[9];
mtxs.m[2] = t2;  t2 = mv->mtx[10];
mtxs.m[3] = t3;  t3 = mv->mtx[11];
mtxs.m[4] = t4;  t4 = mv->mtx[12];
mtxs.m[5] = t5;  t5 = mv->mtx[13];
mtxs.m[6] = t6;  t6 = mv->mtx[14];
mtxs.m[7] = t7;  t7 = mv->mtx[15];
mtxs.m[8] = t0;  mtxs.m[9] = t1;  mtxs.m[10] = t2;  mtxs.m[11] = t3;
mtxs.m[12] = t4;  mtxs.m[13] = t5;  mtxs.m[14] = t6;  mtxs.m[15] = t7;
```

## C. Named-web coloring invariant pinned down: ascending by FIRST-USE (store) order

Three in-TU permutation probes on the pipeline:
- decl-order flip (float t7,..,t0;) : no-op (re-confirms batch4 negative)
- variable NAME reversal (u7 holds mtx[0]) : no-op
- def-order reversal (the draft, t7 first): colors STILL follow store order
  (m[0]'s temp = f0 in every variant; draft got t4..t7=f8..f11 holes but
  t0..t3=f0..f3 unchanged)
=> creation order = order of first USE (the m[i]=ti stores), not decl/def/name.
Since the target store order (m[0] first) is fixed, the first-stored temp
always takes f0: the mirror is UNREACHABLE from source under GO. Direction
remains the closed-negative axis (132 probes phase 2a + 5 here).

## D. GO-web tie (na/nb zero-vs-velX): def-order swap is a no-op IN-FN

Recipe item 3 (def-order permutation, worked in na_named minimal repro)
applied to both na and nb blocks: zero moved after ax=velX. Built byte-identical
output - even the EMISSION order did not change (FE canonicalizes the
const load first). The minimal-repro lever does not transfer; the in-fn
negative from batch4 is environment-independent, not an artifact.

## E. TickStatusEffectsByFlag: CSE'd const webs are a separate, immune sub-family

4 trials, ALL FOUR produced byte-identical objects (the optimizer canonicalizes
every variant to the same IR - strongest invariance seen in this family):
1. colA/colB named locals removed (exprs inlined into call args) - no-op,
   copy-prop had already eliminated them
2. named `w = lbl_806D26FC` def-first for the wrap web - no-op (copy-prop)
3. wrap rewritten as single-statement ternary w/ self-assign else arm - no-op
   (lowers to the identical branch IR)
4. `inv =` fused into the ShadowBillboard call arg - no-op

Residue structure (23 instrs, 3 clusters): every SINGLE-USE temp batch already
numbers descending = target (e.g. the 27B8*reload cluster matches). Every web
with 2+ uses (the multi-block 26FC wrap web, 27BC used twice in one expr,
2768/26E8 CSE'd across two args) is colored OUTSIDE the descending batch and
mismatches. Boundary statement for the ledger: the phase-2a descending-FE
mechanism covers single-use expression temps only; CSE'd const webs are
GO-colored by an order no probed source form can influence.

## Park state

Both fns reverted to asm bodies; worktree at baseline, ninja build/GNLJ82/ok
green. Best-state percentages (strict label-normalized LCS over dtk disasm):
- PerFrameStep trial-3 state: 683/785 = 87.0% strict (objdiff-fuzzy class ~98%);
  two-sided residue rows: direct-copy 131 / draft 97 / trial-3 113 (113 counts
  the mirror as 2x16 rows where the draft's misordered loads aligned cheaper -
  trial-3 is structurally closer: ordering rows are gone, pure renames remain)
- TickStatusEffectsByFlag: 20 two-sided rows (23 instrs content-identical,
  fp renames only), unchanged from batch3

Unlock paths (for any future allocator-research batch): (a) find the GO
coloring-order lever for CSE'd const webs / store-order webs - all source-form
axes are now closed, so this likely needs a binary-level allocator study or
acceptance as unported; (b) both fns self-correct together if found - bundle
with ItemEffect_Explosion (88.99%) / KartMovement_UpdateBoostVisualBlend (98.88%).
