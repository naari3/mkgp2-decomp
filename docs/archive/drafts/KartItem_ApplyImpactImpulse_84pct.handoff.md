# HANDOFF batch_promote_phase1_class1batch2

Class-1 salvage batch #2 (2 mid-size fns in the ONKARTHIT mega-bundle TU).
1 matched (CarObject_OnItemHit 100%, SHA-1 OK), 1 parked at 83.66% best
(KartItem_ApplyImpactImpulseAndRumble; precan found class-2 frsp store-forward,
parked per the established rule; paste-ready C in appendix A).

## Class-1 recipe verification data (the batch's primary deliverable)

Both sites were precanned as the u64-flag-test family (NOT the int-equality-chain
variant) and the recipe `u8 b; if ((flags & MASK_ULL) == 0) { b = 0; } else { b = 1; }`
was applied:

- CarObject_OnItemHit site 0x8004AA14 (mask `0x40ULL`, hi half = 0, zero reg r4):
  byte-exact ON FIRST BUILD, register-for-register including the b/r4 coalesce and
  the bne/b/li r4,1/clrlwi/cmplwi-1 sequence. Third consecutive real-TU
  confirmation of the Phase-0 recipe (after UpdateCoinSpeedBonus / ShadowBB).
- KartItem_ApplyImpactImpulseAndRumble site 0x8004B7D4 (mask `0x0000000010000000ULL`,
  hi half = 0): NEW SUB-SHAPE - the same mask is tested TWICE in the fn
  (`if ((flags & M) == 0 || (u8)mode == 0) {...} else { <class-1 site> }`).
  CW CSEs the and-halves with the first test, so the recipe site emits only
  `xor; or.; bne L1; b L2; L1: li rZ,1; L2: clrlwi; cmplwi 1` reusing the earlier
  partials - the recipe TRANSFERS (shape + fold structure reproduced; verified in
  the 83.66% build). Residual at the site is one scratch-web naming swap
  (bus=r5/zero=r4 generated vs bus=r4/zero=r5 target; xor operand order follows),
  which is part of the fn's class-2 cascade, NOT a recipe failure. Probe: moving
  the `bus = ...->itemBus;` statement before/after the fdivs and moving the `b`
  decl did not flip the pair (2 probes negative).

Conclusion: recipe holds for u64-family sites including the CSE-reuse sub-shape.
Remaining class-1 fns (OnKartHit x7, KartItem_Tick, KartItem_PerFrameStep,
TickStatusEffectsByFlag x7) can proceed; precan each site for u64 vs chain as before.

## Per-fn results

### CarObject_OnItemHit 0x8004A918 (matched, 3 builds / 1 approach)

Promoted asm_fn -> C (approach B, manual 8-byte extab kept, `#pragma exceptions
off/reset`). Build 1 = 96.60%, build 3 = 100.0% / `build/GNLJ82/main.dol: OK`.

Fix ledger (all by source-order/decl-order levers, no hard blocks hit):

1. **GPR decl order = OnFallOffOrDeath pattern**: the lane-clear loop webs map
   descending from decl order. Final order: id(r31), bus(r30), i(r29), owner(r27),
   effectState(r26), mediaReq(r25), sec2(r25 case-1), tbl(r24), id2(r24 case-1),
   sec(r24 case-0), cursor(r23), stats(r23), itemId(r22), blocked(r22). The case-1
   webs needed FRESH names (sec2/id2) declared between mediaReq and tbl to land on
   r25/r24; reusing the case-0 `sec` variable put the case-1 web on r29.
2. **switch case order = memory order**: CW puts the first source case body at the
   compare-tree fallthrough. Target has `case 2: return 0` inline in the tree and
   `case 0` after, so source must list `case 2:` BEFORE `case 0:` in both switches
   (TryStartByCategory_Wrap and SelectAndDispatch_Wrap result switches, the
   binary-search tree on case set {0,2} pivots at the non-case value 1).
3. **float clamp pair**: `spd = lbl_806D26EC * mv->speed; ref = ...refSpeed;
   if (spd > ref) spd = ref;` with decl order spd-then-ref -> f0/f1 (single named
   `spd` local got f1 instead).

Reused verified idioms: lane-clear loop + secondary-slot clear spelled exactly as
the matched KartItem_OnFallOffOrDeath; TitleStats getter
`if ((stats = lbl_806D10A0) == 0) { stats = 0; }`; u64 split-arg
`ItemEffectBus_ClearMask(bus, 0x6bULL)` (r5:r6); `(unsigned char)(x > 0) == 1`
for the neg/andc/srwi branchless bool and `(unsigned char)(x >= 0) == 1` for
srwi/xori (both compare-to-1 value-context forms worked first try);
coin decrement clamp `t = drv->coins2cc - 1; if (t < 0) t = 0;` (subic./bge/li).

### KartItem_ApplyImpactImpulseAndRumble 0x8004B49C (parked 83.66%, asm_fn restored)

**Precan verdict: class-2 frsp store-forward interleave** (the documented
park class, `docs/notes/cw132-frsp-store-forward-negative-probes.md`): the fn
opens with a 16-float transform copy (mv+0x58..0x94 -> sp+0x38..0x74) where the
3 translation elements feed `frsp fN, fM` copies of the lfs-loaded registers
(no stack reload) into the dx/dy/dz subtraction - frsp of lfs-derived singles,
proven unreachable from plain C (n=6 probe ledger). Parked after verifying the
volatile-block form per the rule; 3 attempts used on the reachable remainder.

Verified within the 83.66% build (keep for the future retry):

- volatile scratch struct `{sqB,sqA,sqD,tA[3],tB[3],d[3],m[16]}` at sp+0x8
  reproduces ALL 22+ stack slots at exact offsets, the store ORDER
  (m[4],m[5],m[6],m[0..3],m[7],m[8..15] then d[0..2]), the double tA overwrite
  block, and the three in-place sqrtf store/reload slots (0x10/0xc/0x8) -
  extends the Dispatch probe-3 result to a 3x-sqrt 31-slot frame.
- in-place MSL sqrtf with the volatile STRUCT MEMBER as y
  (`s.sqD = (float)(dist * guess); dist = s.sqD;`) lands the reload in the
  variable's own register (f31/f4/f4) - the batch-1 idiom works with a struct
  member, not just a block-local volatile.
- anti-fmadds for the dist^2 sum needs explicit product locals
  (`p0 = dx*dx; p1 = dy*dy; dist = p0 + p1; p2 = dz*dz; dist = p2 + dist;`);
  the parenthesized one-liner fuses to fmadds. Same for the block-E forward dot:
  in-place products (`v0 = c0 * v0;` etc.) reproduce the 3-fmuls/2-fadds shape.
- fp decl-order mapping held end-to-end for the big block-E web set:
  decl order ... impZ/k/aZ(f2), negInv/impY/c1/n0(f3), impX/magSq/c2/n2(f4),
  scale/c0/n1(f5), dx/aY(f6), aX(f7), rumZ(f8), w2(f9), rumY(f10), w1(f11),
  rumX(f12), w0(f13) -> ALL block C/E registers match target.
- volatile-cast const dedup `dist = *(volatile const float *)&lbl_806D26FC;`
  kills the CSE with the invD 1.0f load (plain spelling emitted `fmr f31, f3`).
- StrPcb sel pair: `if (dot > lbl_806D26EC) sel = lbl_806D2734; else sel = lbl_806D2738;`
  + f30 across StrPcb_GetInstance matches.

Residual (all class-2 cascade or scratch-web tie-breaks, no content diffs):
(a) the 3 missing frsp + complete reschedule of the 50-insn copy block;
(b) block-A dot-accumulator register rotation (f3 vs f0/f1) downstream of (a);
(c) bus/zero r4-r5 swap (2 probes negative, see above);
(d) `rumble`/`dist` copy coalesce: target keeps `fsubs f1; fmr f31,f1; fcmpo f1`,
    CW coalesces to `fsubs f31; fcmpo f31` (x2 sites) - no source handle found
    in-budget for keeping the copy uncoalesced;
(e) minor scheduler slot swaps in block E.

## Committed (orch/batch_promote_phase1_class1batch2, 90436ad)

Single file `src/game/auto_ONKARTHIT_block.c`:
- CarObject_OnItemHit asm body -> C; forward decl typed.
- View struct fields added INSIDE padding (no layout change): KartItemOpsView
  +warpCtx54(0x54)/perfectGateB1(0xb1)/coinPenaltyFD(0xfd)/effectState44(0x44);
  KartDriverBusView +coins2cc(0x2cc); ItemObjectPosView +itemId8(0x8);
  KartMovementSpeedView +impactCap1b8(0x1b8)/rumbleX310/rumbleY314/rumbleZ318.
- Extern retypes (all previously asm-only refs): Field4NotMinusOne /
  ItemEffectBus_ArmTornadoAndQuery / EffectState_HasContent -> unsigned char
  return; ItemClass_GetFlagByte1(int) -> int; TitleStats_IncPerfectCount(void*,
  int, signed char); StrPcb_SetTimer3c40(void*, float, int);
  lbl_806D2734/273C/2740 -> const float.
- KartItem_ApplyImpactImpulseAndRumble asm body restored verbatim (manual extab
  + extabindex entries untouched throughout).

No configure.py / splits.txt / symbols.txt changes (TU already wired with
`extra_cflags=["-use_lmw_stmw on"]` + `extab_padding`).

`funcs_matched_delta` = 0: both fns were already counted matched as byte-identical
asm_fn bodies; the delta is C coverage (one 0x510 fn promoted).

```json
{
  "batch_id": "batch_promote_phase1_class1batch2",
  "sub_summary": "CarObject_OnItemHit promoted to C, 100% / SHA OK - class-1 recipe byte-exact at the 0x40ULL site on first build (3rd real-TU confirmation); KartItem_ApplyImpactImpulseAndRumble parked 83.66% best - precan found class-2 frsp store-forward (16-float copy block), parked per rule; its class-1 site is a NEW CSE-reuse sub-shape (same mask tested twice) and the recipe still transfers",

  "results": [
    {
      "addr": "0x8004A918",
      "name": "CarObject_OnItemHit",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "1 approach / 3 builds. Class-1 site (mask 0x40ULL, hi-zero, b coalesced into r4) byte-exact on first build. Fix ledger: OnFallOffOrDeath-pattern GPR decl order incl. fresh sec2/id2 names for the case-1 webs (r25/r24); switch source case order 2-before-0 puts the return-0 body at the compare-tree fallthrough; spd/ref float pair decl order for f0/f1. No hard-block classes encountered (approach-B late-web pick did not bite: every late web reuses a just-died register)."
    },
    {
      "addr": "0x8004B49C",
      "name": "KartItem_ApplyImpactImpulseAndRumble",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "Parked at 83.66% best (asm_fn restored, paste-ready C in HANDOFF appendix A). Precan: class-2 frsp store-forward interleave (frsp of lfs-derived singles in the 16-float transform copy) - documented unreachable class, parked after volatile-block verification per rule. Class-1 site IS u64 family with a new CSE-reuse sub-shape (mask tested twice; recipe transfers, site emits xor/or./bne/b/li-1 reusing the first test's and-halves). Verified salvage: volatile scratch struct with 3 in-place sqrtf member slots, anti-fmadds product locals, full block-C/E fp decl-order mapping, volatile-cast 26FC dedup. Residual: frsp cascade, bus/zero r4-r5 scratch swap (2 probes), rumble/dist copy coalesce (fmr elided)."
    }
  ],

  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "set_attr": [], "rename": [] },

  "docs_notes": [
    {
      "path": "docs/notes/cw132-class1-batch2-verification.md",
      "content": "# Class-1 recipe: batch-2 verification (2026-06-11, batch_promote_phase1_class1batch2)\n\n- CarObject_OnItemHit 0x8004AA14 (mask 0x40ULL, hi=0): recipe byte-exact on first build; fn matched 100% / SHA OK. 3rd consecutive u64-family confirmation.\n- KartItem_ApplyImpactImpulseAndRumble 0x8004B7D4 (mask 0x10000000ULL, hi=0): NEW CSE-reuse sub-shape - the same mask is first consumed by a direct branch test (if ((f & M) == 0 || (u8)mode == 0)) and the class-1 site sits in the else arm re-testing the SAME mask. CW CSEs the and-halves; the recipe site emits only xor; or.; bne L1; b L2; L1: li rZ,1; L2: reusing the first test's partials. Recipe transfers (verified inside an 83.66% park; residual at the site is a bus/zero scratch-reg naming swap belonging to the fn's class-2 cascade).\n\n## OnItemHit win ledger (new, byte-exact)\n\n- switch-on-call-result {0,2,default} lowering: source case order must equal MEMORY order - case 2: return 0; listed BEFORE case 0: lands the return-0 body at the binary-search fallthrough (pivot cmpwi 1 / cmpwi 3 / cmpwi 0 tree).\n- case-disjoint webs want FRESH local names: the second switch arm's secondary/run18 webs only landed on target r25/r24 as new sec2/id2 locals declared between mediaReq and tbl; reusing the case-0 sec name pinned the web to r29.\n- (unsigned char)(x > 0) == 1 reproduces neg/andc/srwi+cmplwi and (unsigned char)(x >= 0) == 1 reproduces srwi/xori+cmplwi (value-context branchless bool then compare-to-1), both first try.\n\n## ApplyImpactImpulse salvage ledger (inside 83.66% park)\n\n- volatile scratch struct {sqB,sqA,sqD,tA[3],tB[3],d[3],m[16]} @ sp+0x8: all slots + store order + double-overwrite blocks + THREE in-place sqrtf slots reproduce; in-place sqrtf works with a volatile struct MEMBER as the y slot (s.sqD = (float)(x*guess); x = s.sqD;).\n- anti-fmadds applies to mag-squared sums over plain locals: explicit product temps (or in-place v0 = c0 * v0;) required; parenthesized sum fuses.\n- fp decl-order mapping scales to ~17 named floats (block C/E registers f2..f13 all matched via decl order).\n- NEW unresolved micro-classes: (1) bus/zero scratch pair swap (li r4,0 + bus=r5 vs target li r5,0 + bus=r4; stmt order + decl probes negative x2); (2) rumble/dist copy coalesce - target keeps fsubs f1; fmr f31,f1; fcmpo f1, CW coalesces into f31 (no handle found; 2 sites x 3 lines).\n"
    }
  ],

  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },

  "blocked_reason": null,
  "user_attention": null
}
```

## Appendix A: KartItem_ApplyImpactImpulseAndRumble paste-ready C (83.66%)

Drop-in over the asm body (struct fields and extern retypes are already
committed). Unlocks if the class-2 frsp store-forward class is ever solved;
all other blocks are register-exact (block C/E) or shape-exact.

```c
#pragma exceptions off
void KartItem_ApplyImpactImpulseAndRumble(KartItemOpsView *self, int mode, float x, float y, float z) { /* 0x8004B49C size:0x520 */
    volatile struct {
        float sqB;     /* sp+0x08: 3rd in-place sqrtf slot */
        float sqA;     /* sp+0x0c: 2nd in-place sqrtf slot */
        float sqD;     /* sp+0x10: 1st in-place sqrtf slot */
        float tA[3];   /* sp+0x14 */
        float tB[3];   /* sp+0x20 */
        float d[3];    /* sp+0x2c */
        float m[16];   /* sp+0x38 */
    } s;
    KartMovementSpeedView *mv;
    unsigned char b;
    ItemBusFlagsView *bus;
    float sel;      /* f30 */
    float dist;     /* f31 */
    double guess;
    float invD;
    float dot;
    float v1;
    float v0;
    float ratio;
    float rumble;
    float fwdDot;
    float impZ;     /* f2 */
    float k;        /* f2 */
    float aZ;       /* f2 */
    float v2;
    float negInv;   /* f3 */
    float impY;     /* f3 */
    float c1;       /* f3 */
    float n0;       /* f3 */
    float impX;     /* f4 */
    float magSq;    /* f4 */
    float c2;       /* f4 */
    float n2;       /* f4 */
    float scale;    /* f5 */
    float c0;       /* f5 */
    float n1;       /* f5 */
    float dx;       /* f6 */
    float aY;       /* f6 */
    float aX;       /* f7 */
    float rumZ;     /* f8 */
    float w2;       /* f9 */
    float dy;
    float rumY;     /* f10 */
    float w1;       /* f11 */
    float rumX;     /* f12 */
    float w0;       /* f13 */
    float dz;
    float p0;
    float p1;
    float p2;

    mv = self->movement;
    s.m[4] = mv->transform[4];
    s.m[5] = mv->transform[5];
    s.m[6] = mv->transform[6];
    s.m[0] = mv->transform[0];
    s.m[1] = mv->transform[1];
    s.m[2] = mv->transform[2];
    s.m[3] = mv->transform[3];
    s.m[7] = mv->transform[7];
    s.m[8] = mv->transform[8];
    s.m[9] = mv->transform[9];
    s.m[10] = mv->transform[10];
    s.m[11] = mv->transform[11];
    dx = x - (s.m[12] = mv->transform[12]);
    dy = y - (s.m[13] = mv->transform[13]);
    dz = z - (s.m[14] = mv->transform[14]);
    s.m[15] = mv->transform[15];
    s.d[0] = dx;
    s.d[1] = dy;
    s.d[2] = dz;
    p0 = dx * dx;
    p1 = dy * dy;
    dist = p0 + p1;
    p2 = dz * dz;
    dist = p2 + dist;
    if (dist > lbl_806D26EC) {
        guess = __frsqrte(dist);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - dist * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - dist * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - dist * (guess * guess));
        s.sqD = (float)(dist * guess);
        dist = s.sqD;
    }
    if (EffectState_HasContent(self->effectState44) == 0) {
        dot = s.d[1] * s.m[1];
        dot = s.d[0] * s.m[0] + dot;
        dot = s.d[2] * s.m[2] + dot;
        if (self->strPcbGate20 == 1) {
            if (dot > lbl_806D26EC) {
                sel = lbl_806D2734;
            } else {
                sel = lbl_806D2738;
            }
            StrPcb_SetTimer3c40(StrPcb_GetInstance(), sel, 12);
        }
    }
    bus = self->ownerDriver->itemBus;
    invD = lbl_806D26FC / dist;
    negInv = -invD;
    dx = s.d[0] * negInv;
    dy = s.d[1] * negInv;
    dz = s.d[2] * negInv;
    s.d[0] = dx;
    s.d[1] = dy;
    s.d[2] = dz;
    if ((bus->flags & 0x10000000ULL) == 0 || (unsigned char)mode == 0) {
        scale = lbl_806D273C * dist;
        mv = self->movement;
        impX = s.d[0] * scale;
        impY = s.d[1] * scale;
        impZ = s.d[2] * scale;
        s.d[0] = impX;
        mv->impact1ac = mv->impact1ac + impX;
        s.d[1] = impY;
        mv->impact1b0 = mv->impact1b0 + impY;
        s.d[2] = impZ;
        mv->impact1b4 = mv->impact1b4 + impZ;
        magSq = mv->impact1b4 * mv->impact1b4 + (mv->impact1ac * mv->impact1ac + mv->impact1b0 * mv->impact1b0);
        if (magSq > lbl_806D26EC) {
            guess = __frsqrte(magSq);
            guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
            s.sqA = (float)(magSq * guess);
            magSq = s.sqA;
        }
        if (magSq > mv->impactCap1b8) {
            ratio = mv->impactCap1b8 / magSq;
            mv->impact1ac = mv->impact1ac * ratio;
            mv->impact1b0 = mv->impact1b0 * ratio;
            mv->impact1b4 = mv->impact1b4 * ratio;
        }
        rumble = lbl_806D2740 - dist;
        dist = rumble;
        if (rumble < lbl_806D26EC) {
            dist = *(volatile const float *)&lbl_806D26FC; /* defeat CSE with the invD 1.0f load */
        }
        dist = dist * lbl_806D273C;
    } else {
        /* class-1 recipe: explicit ==0 compare, then=0 / else=1 arm order */
        if ((bus->flags & 0x10000000ULL) == 0) {
            b = 0;
        } else {
            b = 1;
        }
        if (b == 1) {
            rumble = lbl_806D2740 - dist;
            dist = rumble;
            if (rumble < lbl_806D26EC) {
                dist = *(volatile const float *)&lbl_806D26FC;
            }
            dist = dist * lbl_806D273C;
        }
    }
    c0 = s.m[8];
    c1 = s.m[9];
    v0 = s.d[0];
    v1 = s.d[1];
    c2 = s.m[10];
    v2 = s.d[2];
    v0 = c0 * v0;
    v1 = c1 * v1;
    v2 = c2 * v2;
    fwdDot = v0 + v1;
    fwdDot = v2 + fwdDot;
    w0 = s.d[0];
    w1 = s.d[1];
    mv = self->movement;
    w2 = s.d[2];
    rumX = w0 * dist;
    rumY = w1 * dist;
    rumZ = w2 * dist;
    mv->rumbleX310 = rumX;
    mv->rumbleY314 = rumY;
    mv->rumbleZ318 = rumZ;
    k = lbl_806D2744 * -fwdDot;
    mv = self->movement;
    s.tA[0] = c0;
    s.tA[1] = c1;
    s.tA[2] = c2;
    aX = c0 * k;
    aY = c1 * k;
    aZ = c2 * k;
    s.tB[0] = rumX;
    s.tB[1] = rumY;
    s.tB[2] = rumZ;
    n0 = w0 + aX;
    n1 = w1 + aY;
    n2 = w2 + aZ;
    mv->impact1ac = mv->impact1ac + n0;
    mv->impact1b0 = mv->impact1b0 + n1;
    mv->impact1b4 = mv->impact1b4 + n2;
    s.tA[0] = aX;
    s.tA[1] = aY;
    s.tA[2] = aZ;
    s.d[0] = n0;
    s.d[1] = n1;
    s.d[2] = n2;
    magSq = mv->impact1b4 * mv->impact1b4 + (mv->impact1ac * mv->impact1ac + mv->impact1b0 * mv->impact1b0);
    if (magSq > lbl_806D26EC) {
        guess = __frsqrte(magSq);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - magSq * (guess * guess));
        s.sqB = (float)(magSq * guess);
        magSq = s.sqB;
    }
    if (magSq > mv->impactCap1b8) {
        ratio = mv->impactCap1b8 / magSq;
        mv->impact1ac = mv->impact1ac * ratio;
        mv->impact1b0 = mv->impact1b0 * ratio;
        mv->impact1b4 = mv->impact1b4 * ratio;
    }
}
#pragma exceptions reset
```
