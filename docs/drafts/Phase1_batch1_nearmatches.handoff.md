# HANDOFF batch_promote_phase1_class1batch1

Class-1 salvage batch #1 (3 fns in the ONKARTHIT mega-bundle TU). 1 matched, 2 parked
high (97.95% / 95.19%, reverted to asm_fn, paste-ready C in appendices).

## CLASS-1 RECIPE: VERIFIED IN REAL TU (Phase 1 evidence)

The Phase-0 recipe (`u8 b; if ((flags & MASK_ULL) == 0) { b = 0; } else { b = 1; }`,
explicit ==0 + then=0/else=1 arm order) reproduced the branch-over-branch shape
**byte-identically at BOTH u64 flag-test sites attempted**, on the first build, with
zero site-specific tuning:

- CarObject_UpdateCoinSpeedBonus site 0x8004D110, mask `0x800000ULL` (hi word = 0):
  bool coalesced into r4 = the zero mask-half register, `bne/b/li r4,1/clrlwi/cmplwi 1`
  all byte-exact. Fn reached 100% (matched).
- KartItem_UpdateShadowBillboardAndViewport site 0x8004EF18, mask
  `0x0000200000000000ULL` (LO word = 0 this time, zero register still r4): site fully
  matched inside the 97.95% build. The coalesce precondition holds with either half
  being the zero.

Conclusion for the remaining 16 sites / 6 fns (OnKartHit x7, CarObject_OnItemHit,
ApplyImpactImpulse, KartItem_Tick, KartItem_PerFrameStep, TickStatusEffectsByFlag x7):
recipe is expected to apply directly wherever the site is the u64-flag-test family.

**Caveat discovered (new sub-class)**: KartItem_ApplyImpactReflectAndDampVelocity's
"class-1 site" is NOT the u64 family - it is an int-equality CHAIN
(`cmpw; bne L1; b LDONE; L1: ...` x4 against the 4-word table lbl_802ED9E4, with a
hoisted `li r6,0` and arm re-stores deleted late). The ULL recipe does not transfer;
see the probe ledger below. Check each remaining site's actual shape (u64 test vs
equality chain) during precan.

## Per-fn results

### CarObject_UpdateCoinSpeedBonus 0x8004CF64 (matched, 2 attempts)

Promoted to C (approach B, manual extab kept). Attempt 1 -> 99.53%; fixes:
`(int)g_gameMode == 2` for the signed cmpwi, and float out-locals decl order flip
(outA declared first lands at sp+0xc = r5 arg). Raw objdiff shows 99.97% because the
int->float cookie is the TU-local anonymous `@351` until `postprocess_sdata2` renames
it to lbl_806D2790 (same known cosmetic family as CarObject_Init 98.18% /
ItemEffect_SelectAndDispatch 99.38%); full `ninja build/GNLJ82/ok` SHA-1 = OK, so the
fn is byte-identical in the dol.

Idioms used (all pre-existing): StrPcb 4-call gate block, `bus` local +
ItemEffectBus_OrMask(bus, 0x80ULL) u64 args, store-then-reload smoothing
(`self->cc = cur - step; if (self->cc < bonus) ...`), nested same-operand compares
(`!=` outer + `<` inner CSE to one cmpw), typed asm prototype for the TU-internal
KartMovement_UpdateBoostVisualBlend call.

### KartItem_UpdateShadowBillboardAndViewport 0x8004EDD4 (parked 97.95%, asm_fn kept)

Class-1 site matched (see above). Residual = EXACTLY the known smallrun hard-block
(cw132-prologue-load-hoist-unreproduced.md item (b), KartItem_GetMaxSpeedWithBonus
94.35% family): the dual-induction search-loop SR init. Target has
`li r5,0 / mr r6,r5` (off = reg-copy of i that escaped const-prop); every C spelling
emits `li r6,0x0`. 2 diff lines total (the mr, plus the mv `lwz r3,0x28(r29)`
preheader slot that shifts with it).

Negative probes this batch (do not repeat):
- `int zero = 0; for (i = zero, off = zero; ...)` -> const-prop folds both copies to
  li, zero var DCE'd (hoped-for i==zero coalesce + mr for off did not materialize).
- `#pragma opt_propagation off` around the fn -> **bit-identical output to baseline**
  (does not even disable the copy/const folding here; clean no-op negative).
- increment order in the for-step must be `off += 8, i++` (target increments off
  first).

NEW WIN IDIOM (volatile-cast load dedup): `sel = *(volatile const float *)&lbl_806D26EC;`
forces a SEPARATE `lfs f4, 26EC` for the sel init instead of CW CSE-ing it with the
later Saturate lo-arg load (plain `sel = lbl_806D26EC;` produced one shared load +
`fmr f5,f2` and cascaded the f2/f4 cookie registers). With the volatile read the whole
sel/conversion/Saturate block is byte-exact. Also: plain `if (b == 1) sel = lbl_806D2708;`
after the unconditional init reproduces target layout (if/else two-arm form does NOT -
it emits the literal then-first diamond).

Unlock chain: solving the `mr` SR-init unlocks this fn AND KartItem_GetMaxSpeedWithBonus
(94.35%) - identical loop, identical residual.

Paste-ready C: appendix A (drops in over the asm body; struct fields it needs are
already committed).

### KartItem_ApplyImpactReflectAndDampVelocity 0x8004B140 (parked 95.19%, asm_fn kept)

Everything matches EXCEPT the equality-chain bool block (~12 instr region). Solved
pieces (verified byte-exact, keep):
- in-place MSL sqrtf: `if (sq > lbl_806D26EC) { volatile float y; ... y = (float)(sq*guess); sq = y; }`
  - assigning the result BACK INTO sq makes the volatile reload land in f4 (= sq's
  register) and kills the else-path fmr that a helper-with-return produces.
- velocity scale block f1/f2 assignment: hoist ONLY the outer const into a local
  (`cB = lbl_806D2714;`) and leave the inner const literal
  (`*outX = cB * (lbl_806D2730 * mv->velX);`) -> inner CSE temp lands in f1, cB in f2,
  byte-exact. Both-as-locals or both-literal give a register swap or per-component
  reloads (4 permutations probed).
- else branch needs `mv = self->movement;` REASSIGNED inside the arm (one fresh lwz;
  repeating `self->movement->` reloads it per store due to float* alias conservatism).
- TitleStats getter idiom `if ((stats = lbl_806D10A0) == 0) { stats = 0; } if (stats)`
  matches at both sites; `fn_801B5B60(GetKartStartSlot(self->raceScore10));` tail.

Equality-chain hard residual - target shape per link `cmpw; bne Lnext; b LDONE` with a
single hoisted `li r6,0` and NO li in the arms. Probe ledger (4 forms, all negative):
1. arms `{ b = 0; }` + init `b = 0;` -> init dead-def-eliminated (all paths redefine),
   arms keep their own `li r0,0` x4. bne/b pairs PRESENT (closest shape, used in
   appendix B). ~95%.
2. arms empty `{}` + init -> init survives but branch folding collapses every pair to
   `beq LDONE` (confirms the class-1 fold mechanism applies to int compares too).
3. arms `b = zero;` copies of a `u8 zero = 0;` var -> const-prop folds the copies,
   zero DCE'd, identical to (1).
4. mixed (first arm empty, rest `b = 0;`) -> init li survives AND arms keep their li:
   disproves the "register already holds 0 -> redundant li deleted" cleanup hypothesis;
   the class-1 arm-li deletion evidently requires coalescing with a DIFFERENT live
   zero web (the u64 mask half), which this site does not have. New sub-class; no
   source-level handle found in 4 probes.

Also unreproduced (1 cosmetic): CW fuses `lis+addi+lwz` of the table base into
`lis+lwzu @l(r4)` (target keeps the addi + plain `lwz 0x0(r4)`), and b sits in r0/r5
instead of r6 pending the chain solution.

Paste-ready C: appendix B.

## Committed (orch/batch_promote_phase1_class1batch1, 17a79fd)

Single file `src/game/auto_ONKARTHIT_block.c`:
- CarObject_UpdateCoinSpeedBonus asm body -> C (approach B, manual extab kept).
- extern retypes: `int GetKartStartSlot();`, `int ItemSelect_StartRouletteSpin();`,
  `unsigned char KartEffectFadeTransit_IsActive();`, lbl_806D2708/2730/2784/2788 ->
  `const float` (all previously asm-only references).
- shared view structs extended INSIDE padding (no layout change): KartMovementSpeedView
  +accelFactor2c(0x2c)/restVelX..Z(0xb8..); KartDriverBusView +syncTarget23c(0x23c)/
  deathState2b8(0x2b8), itemBus typed as new ItemBusFlagsView* (u64 flags @0x10);
  KartItemOpsView +input30/coinCountC8/smoothBonusCC/boostBlendE0/prevSyncF0/
  coinBonusEnabledFE/itemSelect104.
- KartMovement_UpdateBoostVisualBlend asm fwd decl + definition given a typed
  signature (drv, mv, float* outA, float* outB, float* blend) for the C call site.

No configure.py / splits.txt / symbols.txt changes (TU already wired,
`extab_padding` + `-use_lmw_stmw on` Object line untouched).

`funcs_matched_delta` is 0 because the fn was already counted matched as a
byte-identical asm_fn body; PROGRESS stays 397/7614. The delta is C-coverage, not
match count.

```json
{
  "batch_id": "batch_promote_phase1_class1batch1",
  "sub_summary": "class-1 recipe VERIFIED in real TU (byte-exact at both u64 sites, both zero-half polarities): CarObject_UpdateCoinSpeedBonus matched 100%; ShadowBB parked 97.95% (sole residual = known mr-SR-init hard-block, shared with GetMaxSpeedWithBonus); ApplyImpactReflect parked 95.19% (site is an int-equality-chain class-1 VARIANT, ULL recipe does not transfer, 4-probe ledger in HANDOFF)",

  "results": [
    {
      "addr": "0x8004CF64",
      "name": "CarObject_UpdateCoinSpeedBonus",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "2 attempts. Class-1 recipe byte-exact at site 0x8004D110 (mask 0x800000ULL, bool coalesced into zero-mask-half r4). Raw objdiff reads 99.97% from the pre-postprocess @351 int->float cookie reloc (postprocess_sdata2 renames it; known cosmetic family); dol SHA-1 OK confirms byte-identity. Fix ledger: (int)g_gameMode for signed cmpwi; float out-locals decl order outA-then-outB -> sp+0xc/sp+0x8."
    },
    {
      "addr": "0x8004EDD4",
      "name": "KartItem_UpdateShadowBillboardAndViewport",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "Parked at 97.95% best (reverted to asm_fn, paste-ready C in HANDOFF appendix A). Class-1 site 0x8004EF18 MATCHED with the recipe (lo-word-zero polarity). Sole real residual: target 'mr r6,r5' dual-induction SR init vs emitted 'li r6,0' (1 instr + 1 schedule slot) = the exact KartItem_GetMaxSpeedWithBonus 94.35% hard-block; solving it unlocks both fns. Negative probes: zero-var copy init (const-prop folds), #pragma opt_propagation off (bit-identical no-op). New win idiom: volatile-cast sel init defeats the 26EC load CSE."
    },
    {
      "addr": "0x8004B140",
      "name": "KartItem_ApplyImpactReflectAndDampVelocity",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "Parked at 95.19% best (reverted to asm_fn, paste-ready C in HANDOFF appendix B). The 'class-1 site' here is an int-equality CHAIN variant (4 cmpw against lbl_802ED9E4 words, hoisted li r6,0, arm li-0s deleted late) - the ULL recipe does NOT apply; 4 chain probes negative (ledger in HANDOFF; probe 4 disproves the redundant-li cleanup hypothesis: deletion needs a coalescable independent zero web). Solved-byte-exact pieces worth keeping: in-place sqrtf (sq = y) f4 coalesce, cB-local + inner-literal const split for the f1/f2 scale block, mv reassign in the else arm."
    }
  ],

  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "set_attr": [], "rename": [] },

  "docs_notes": [
    {
      "path": "docs/notes/cw132-class1-batch1-verification.md",
      "content": "# Class-1 recipe: first real-TU verification (2026-06-11, batch_promote_phase1_class1batch1)\n\nRecipe `u8 b; if ((flags & MASK_ULL) == 0) { b = 0; } else { b = 1; }` verified byte-exact at 2 real sites in auto_ONKARTHIT_block.c, both zero-half polarities:\n\n- CarObject_UpdateCoinSpeedBonus 0x8004D110 (mask 0x800000ULL, hi half = 0): matched -> fn promoted to 100% / SHA OK.\n- KartItem_UpdateShadowBillboardAndViewport 0x8004EF18 (mask 0x0000200000000000ULL, LO half = 0): site matched inside a 97.95% build.\n\nCoalesce precondition holds with either u64 mask half being the zero register. No site-specific tuning was needed.\n\n## New sub-class: int-equality-chain bool (KartItem_ApplyImpactReflectAndDampVelocity 0x8004B1A8)\n\nTarget: `li r6,0` hoisted; per link `cmpw; bne Lnext; b LDONE`; only the final else materializes `li r6,1`. NOT the u64 family. 4 probes negative:\n1. arms `{b=0;}` + init -> init dead-def-eliminated, arms keep own li (bne/b shape OK, +4 li) = best fallback (95.19%).\n2. empty arms + init -> branch folding collapses to `beq LDONE` (fold applies to int compares too).\n3. arms `b = zero;` copies of u8 zero=0 -> const-prop folds, identical to 1.\n4. first-arm-empty mix -> init li SURVIVES and arm lis are STILL kept: the class-1 arm-li deletion is NOT a 'register already holds 0' cleanup; it requires coalescing with an independent live zero web (the u64 mask half). The chain has no such web -> no source handle found.\n\n## mr-SR-init negatives (ShadowBB = GetMaxSpeedWithBonus family)\n\n- `int zero = 0; i = zero; off = zero;` -> both copies const-folded, zero DCE'd.\n- `#pragma opt_propagation off` around the fn -> output bit-identical to baseline (does not disable the fold). Closes the pragma axis for this class.\n\n## New win idioms (verified byte-exact)\n\n- volatile-cast float const load dedup: `sel = *(volatile const float *)&lbl_806D26EC;` forces a second independent lfs when CW would otherwise CSE the const load with a later use and bridge with fmr (cascades cookie/register churn). Plain `if (b == 1) sel = lbl_806D2708;` after it reproduces the speculated-else layout; an if/else two-arm form does not.\n- in-place MSL sqrtf: assign the NR result back into the same variable (`y = (float)(sq*guess); sq = y;` inside the guard) -> volatile reload lands in the variable's own register (f4), no else-path fmr. Helper-with-return form leaves a separate result web.\n- 2-const scale block register split: hoist only the OUTER const into a local, keep the inner const literal (`cB = lbl_806D2714; *out = cB * (lbl_806D2730 * v);`) -> inner CSE temp = f1, local = f2. Both-local / both-literal permutations give a swap or per-component reloads.\n- alias-driven reload: repeated `self->movement->fieldX` across `*(float* out)` stores reloads the pointer per store; reassign `mv = self->movement;` inside the arm for a single lwz.\n- u64 split-arg ABI: `ItemEffectBus_OrMask(bus, 0x80ULL)` puts the mask in r5:r6 (r4 skipped) - prototype `(void *bus, unsigned long long mask)` is enough.\n"
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

## Appendix A: KartItem_UpdateShadowBillboardAndViewport paste-ready C (97.95%)

Residual vs target: `li r6,0x0` instead of `mr r6,r5` at the loop SR init + the
adjacent `lwz r3,0x28(r29)` schedule slot. Drop-in over the asm body once the mr-init
class is solved (struct fields/extern retypes already committed).

```c
#pragma exceptions off
void KartItem_UpdateShadowBillboardAndViewport(KartItemOpsView *self, int arg2, int arg3) { /* 0x8004EDD4 size:0x204 */
    KartMovementSpeedView *mv;
    int i;
    int off;
    SpeedTableEntry *e;
    ItemBusFlagsView *bus;
    void *bb;
    float keySpeed;
    float ratio;
    float sel;
    unsigned char b;

    if (ItemStateGuard_IsActive(self->stateBlock->guard) == 1) {
        ShadowBillboard_StepSimple(self->billboard, arg2, arg3);
    } else {
        mv = self->movement;
        keySpeed = lbl_806D26EC;
        for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
            if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < lbl_806D26FC) {
                keySpeed = mv->table[mv->tableIdx].pairs[i].value;
                break;
            }
        }
        if (mv->capFlag == 1) {
            if (keySpeed >= lbl_806D276C) {
                keySpeed = lbl_806D276C;
            }
        }
        ratio = Saturate_Double(KartMovement_CalcSpeedWithCoinBonus(mv, 0) / (lbl_806D2770 * keySpeed), lbl_806D26EC, lbl_806D26FC);
        bus = self->ownerDriver->itemBus;
        sel = *(volatile const float *)&lbl_806D26EC; /* volatile cast defeats the 26EC load CSE */
        /* class-1 recipe: explicit ==0 compare, then=0 / else=1 arm order */
        if ((bus->flags & 0x0000200000000000ULL) == 0) {
            b = 0;
        } else {
            b = 1;
        }
        if (b == 1) {
            sel = lbl_806D2708;
        }
        bb = self->billboard;
        ShadowBillboard_SetTargetSaturation(bb, Saturate_Double(sel + (float)self->coinCountC8 / lbl_806D27B0, lbl_806D26EC, ratio + sel));
        ShadowBillboard_Tick(self->billboard, arg2, arg3);
        SceneRender_SetViewportRect(g_raceCamera,
            self->movement->transform[12], self->movement->transform[13], self->movement->transform[14],
            self->movement->transform[8], self->movement->transform[9], self->movement->transform[10]);
    }
}
#pragma exceptions reset
```

## Appendix B: KartItem_ApplyImpactReflectAndDampVelocity paste-ready C (95.19%, chain form 1)

Residual vs target: the equality chain (arms emit their own `li 0` x4, top `li r6,0`
missing because the init is dead-def-eliminated; b lands in r0; first table deref
fused to `lwzu @l(r4)`). Everything outside the chain block is byte-exact.

```c
#pragma exceptions off
int KartItem_ApplyImpactReflectAndDampVelocity(KartItemOpsView *self, float *outX, float *outY, float *outZ) { /* 0x8004B140 size:0x254 */
    int id;
    const int *p;
    unsigned char b;
    KartMovementSpeedView *mv;
    float sq;
    float cB;
    void *stats;

    if (self->ownerDriver->deathState2b8 == 1) {
        return 0;
    }
    p = (const int *)lbl_802ED9E4;
    id = self->secondary->itemId;
    b = 0; /* dead-def-eliminated; kept for semantics */
    if (id == *p) {
        b = 0;
    } else if (id == *++p) {
        b = 0;
    } else if (id == *++p) {
        b = 0;
    } else if (id == *++p) {
        b = 0;
    } else {
        b = 1;
    }
    if (b == 0) {
        return 0;
    }
    if (self->strPcbGate20) {
        SoundObj_PlaySE_Direct(self->soundCtrl, 0x4c);
    }
    mv = self->movement;
    sq = mv->velZ * mv->velZ + (mv->velX * mv->velX + mv->velY * mv->velY);
    /* MSL sqrtf inlined in place; assigning back into sq coalesces the volatile
     * reload into f4 (no else-path fmr) */
    if (sq > lbl_806D26EC) {
        volatile float y;
        double guess = __frsqrte(sq);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
        y = (float)(sq * guess);
        sq = y;
    }
    if (sq > lbl_806D26EC) {
        cB = lbl_806D2714; /* outer const as local -> f2; inner literal -> f1 */
        *outX = cB * (lbl_806D2730 * mv->velX);
        *outY = cB * (lbl_806D2730 * mv->velY);
        *outZ = cB * (lbl_806D2730 * mv->velZ);
    } else {
        mv = self->movement;
        *outX = mv->restVelX;
        *outY = mv->restVelY;
        *outZ = mv->restVelZ;
    }
    if ((stats = lbl_806D10A0) == 0) {
        stats = 0;
    }
    if (stats) {
        TitleStats_SetEventFlag_806d1420(stats, self->raceScore10);
    }
    if (KartMovement_GetCurrentItemId(self->ownerDriver) >= 0) {
        return 1;
    }
    if (self->itemSelect104) {
        if (ItemSelect_StartRouletteSpin(self->itemSelect104, self->ownerDriver, 1, 0) >= 0) {
            if ((stats = lbl_806D10A0) == 0) {
                stats = 0;
            }
            if (stats) {
                TitleStats_IncCurrentRaceScore(stats, self->raceScore10, 0);
            }
        }
    }
    fn_801B5B60(GetKartStartSlot(self->raceScore10));
    return 1;
}
#pragma exceptions reset
```
