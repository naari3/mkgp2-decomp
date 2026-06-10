# HANDOFF batch_promote_80050410_dispatchpair

KartItem_TickActiveEffectsTwoLane 0x8005094C (0x3A4) promoted asm_fn -> matched C at
100.0%, SHA-1 OK. ItemEffect_Dispatch 0x80050410 (0x53C) attempted (best 86.34%) and
reverted to asm_fn: its kind14 branch carries the 16-float-copy frsp store-forward
interleave (sec 14.2 KartItem_OnKartHit family). 5 new source forms probed, none makes
CW 1.3.2 emit frsp on lfs-derived singles. Salvage C + probe ledger below.

```json
{
  "batch_id": "batch_promote_80050410_dispatchpair",
  "sub_summary": "TwoLane matched 100% (jumptable switch promote w/ .data split, comma-&& state fold, flat decl-order regalloc chase); Dispatch skipped at 86.34% on the frsp store-forward interleave hard-block (5 new negative probes, salvage C in appendix)",

  "results": [
    {
      "addr": "0x80050410",
      "name": "ItemEffect_Dispatch",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 86.34% over 6 builds. Everything matches except the kind14 fp block (5 frsp webs unreproducible; their absence drops f30/f31 saves and shifts the frame from 0xa0, cascading prologue/epilogue + fctiwz slot). Full 22-store volatile scratch block incl. the m2 store+reload reproduced at exact offsets; strPcb speed clamp (add+lfs 0x8 form), 9-case jumptable, speed/cam switches, indirect onApply call all matched. Probes: memberwise copy (copy-prop+DSE), struct block-assign (integer lwz/stw copy), volatile+assignment-expr value (raw, no frsp), (float)(double) cast (folded), static inline float params (bound raw), alias-pointer read-backs (fp pressure explosion). Same family as sec 14.2 OnKartHit frsp interleave; precan-skip until that class is solved. Paste-ready 86% C in appendix."
    },
    {
      "addr": "0x8005094C",
      "name": "KartItem_TickActiveEffectsTwoLane",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "TU-internal promote (approach B, manual extab kept). Needs the splits.txt .data line for the CW-emitted switch jumptable (see user_attention). 5 builds: structure in 1, state-machine fold + switch guard + sc20 local in 2, callee-saved chase in 3 (scope reversal -> flatten -> expiry reorder)."
    }
  ],

  "configure_py": {
    "add_objects": []
  },

  "splits_txt": {
    "add_entries": [
      {
        "path": "game/auto_ONKARTHIT_block.c",
        "sections": [
          {"section": ".data", "start": "0x803F7668", "end": "0x803F7690"}
        ]
      }
    ]
  },

  "symbols_txt": {
    "set_scope": [],
    "set_attr": [],
    "rename": []
  },

  "docs_notes": [
    {
      "path": "docs/notes/cw132-frsp-store-forward-negative-probes.md",
      "content": "# CW 1.3.2 frsp store-forward interleave: negative probe ledger (2026-06-10, batch_promote_80050410_dispatchpair)\n\nTarget idiom (ItemEffect_Dispatch 0x80050410 kind14 branch, same family as KartItem_OnKartHit sec 14.2 row '16-float copy block frsp store-forward interleave'): a 22-float stack scratch block { dir[3] @+0x8; d[3] @+0x14; mtx[16] @+0x20 } where all 16 matrix copies are stfs'd RAW, while the 5 values consumed by the dot product (m0, m1, m12, m13, m14) appear as SEPARATE frsp-copies of the load registers, plus exactly one real stack reload (m2, register evicted). CW-built code, so some source form produces it - but none found:\n\n1. memberwise float copies + read-backs: copy-prop rewrites reads to the original loads, then DSE deletes the whole block (frame shrinks 0xa0 -> 0x30).\n2. struct block-assignment (s.mtx = *(Mtx16S *)mov->transform): copy RETAINED but emitted as integer lwz/stw pairs, reads become stw+lfs same-slot pairs. Useful fact: block copies survive DCE.\n3. volatile struct + plain member stores (store order = source order) + assignment-expression values for the computed uses: all 22 stores reproduce at exact offsets INCLUDING the m2 store+reload, but the assignment-expression value is the RAW register - no frsp. Best result (86.3%).\n4. (float)(double)x on an lfs-derived single: folded to nothing (CW tracks f32-roundedness through cast chains).\n5. static inline helper with float params (hoping for param-copy rounding at the inline boundary): params bound to the raw values, no frsp.\n6. read-backs through a non-volatile alias pointer into the volatile object: no frsp, and fp pressure exploded (f26-f31 saves) - strictly worse.\n\nConclusion: CW 1.3.2 -O4,p provably tracks single-precision roundedness of lfs-derived values and elides frsp in every reachable C path probed (n=6 incl. the sec 14.2 untried 'assignment-expression copy' salvage, now falsified). The frsp copies in target likely come from a compiler state we cannot reach from plain C (possibly C++ reference/aliasing semantics in the original). Precan: a block of raw lfs+stfs matrix copies with interleaved frsp fN,fM where fM is itself an lfs result marks this class - park as asm_fn after the volatile-block form (probe 3) is verified, do not chase frsp.\n\nPositive salvage from the same batch: the volatile scratch struct + source-order member stores is a reliable way to materialize a fully dead spill block at exact offsets (extends strpcbrun idiom 3 from Vec3 to 22 floats), including a mid-block volatile read-back reload."
    },
    {
      "path": "docs/notes/cw132-twolane-batch-idioms.md",
      "content": "# TwoLane batch idioms (2026-06-10, batch_promote_80050410_dispatchpair)\n\nMatched: KartItem_TickActiveEffectsTwoLane 0x8005094C (100%, src/game/auto_ONKARTHIT_block.c).\n\n1. Jumptable switch in a promoted bundle TU: CW emits one .data jumptable per switch, in function order; the TU's splits.txt entry needs a matching `.data start: end:` range. Table is 0-anchored when min case is small (entry 0 = default), bounds check `cmplwi rX, maxcase; bgt`; case bodies emit in SOURCE order, so write cases 1..9 in target address order. dtk matches the anonymous local jumptable to `jumptable_8xxxxxxx` by layout ([.data-0] 100%).\n2. cmpwi-0-first 2-case switch shape (`cmpwi 0; beq end; cmpwi 2; beq; bge end; cmpwi 1; bge; b end`): write `if (v != 0) { switch (v) { case 1: ...; case 2: ...; } }` - the guard supplies the leading 0-test, the switch lowers to the binary tree.\n3. Single shared `li r0,1` state assignment with two branch entries (ble + bgt both landing on it): comma-&& fold `else if (t > 0 && (t = t - 1, t <= 0)) { state = 2; } else { state = 1; }`. Separate else branches emit two li blocks (+2 instrs).\n4. fp temp pair swap at a `fmuls f2, f1, f0` site (scale=f1, blend=f0): name the scale load as a local (`float sc20 = d->steerScale20;`) declared AFTER the blend local; also lets cases 6/8/9 (fctiwz / fmr) reuse the same CSE web via the named local.\n5. Callee-saved chase recipe that converged in 3 steps (stmw r23 fn, 12 webs): (a) get relative order right per scope - reversing a block-scope decl list inverts that group's relative order; (b) FLATTEN all callee-saved locals to one fn-top decl list - this changed the outer/inner register pool partition (scoped: outer webs grabbed r31..r29; flat: matched target's r27/r25/r24 outer + r26,r28-r31 inner); (c) groups sharing freed registers pick ascending-from-bottom in decl order for the earlier block, descending-from-top for the later block - reorder within the flat list accordingly. Final working order for this fn: own2, own, est2, est, mreq2, mreq, kc, cursor, id, other, expired, i.\n6. `int n = i - 1; if (n >= 0)` reproduces `subic. r0, rI, 1; blt` and keeps n in r0 for the following mulli.\n7. Re-test idiom: `if (other->timer >= 0 && other->itemId >= 0)` after an earlier `if (other->itemId < 0) continue`-shape guard keeps the second cmpwi on the CSE'd register (no reload, no branch fold).\n8. Calling a same-TU asm_fn from promoted C: change the asm body's signature in place (`asm void f(void)` -> `asm void f(ItemEffectTable *self)`), body untouched - precedent extended (KartItem_TickStatusEffectsByFlag)."
    }
  ],

  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },

  "blocked_reason": null,
  "user_attention": "splits.txt edit needed that apply_handoff.py will SKIP (path already present): the existing game/auto_ONKARTHIT_block.c block must gain one line `.data       start:0x803F7668 end:0x803F7690` (tab-indented, the promoted switch's jumptable). Without it the merged TU emits a .data section with no split range and the build fails. The worktree commit 401a482 contains the exact splits.txt diff; merge_promote's src patch alone is NOT sufficient."
}
```

## Precan results (step 0)

- No mtctr/bdnz loops in either fn (only jumptable bctr + indirect bctrl) -> no
  dead-counter-ctr-loop class.
- No `bl __unexpected`, no `subi rX,rY,0x217d` (ScopedTimer), no class-1 invert sites
  (the li r0,0/1/2 chains are plain if/else state assignment).
- ItemEffect_Dispatch DOES carry the class-2 frsp interleave (16-float copy with
  frsp'd compute webs) - flagged at precan, budget-boxed, and it was indeed the killer.

## ItemEffect_Dispatch decoded structure (verified at 86.34%)

`void ItemEffect_Dispatch(ItemEffectLaneRun *lane /*r27*/, KartItemOpsView *owner /*r28*/,
unsigned char kind /*r29*/, void *effectState /*r30*/, void *mediaReq /*r31*/,
const ItemEffectDesc *desc, int itemId, void *itemObj, int arg4 /*stack 0xa8*/,
float intensity /*f1*/)` - no return value (r3 garbage at blr).

1. lane->itemId/itemObj/desc = params; lane->timer = arg4 < 0 ? lane->desc->duration10 : arg4.
2. if (desc->kind14 == 1): itemObj ? (approach-dot block -> blend = dot < 0 ? lbl_806D26E4
   : lbl_806D26FC) : (blend = intensity); mode = blend > 0 ? 1 : 2. else mode=0, blend=1.0f.
3. if (desc->strPcbKind8 == 1): optional StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 0xc, 2,
   lbl_806D26E4) behind owner->strPcbGate20; vel xyz *= lbl_806D2718; speed clamp
   `sp = lbl_806D2718 * mov->speed; if (sp > mov->table[mov->tableIdx].refSpeed) sp = ...;`
   (double-mention indexing reproduces the add+lfs-0x8 form; a named entry pointer folds to
   lfsx - wrong); aiTimerD0 <= 0 -> fn_8019A9BC(mov, 0,0,0) + aiTimerD0 = 0x2d. else just the
   aiTimerD0 reset.
4. if (lane->timer >= 0 && lane->itemId >= 0): per-desc actions = steering jumptable
   (cases 1..9: Lock/Vibrate/Vibrate_Sub/Viscosity_Uniform/Viscosity/Split/Shake/Scale/Delay,
   f2 = sc20 * blend hoisted, Split/Delay pass (int)sc20 in r4 via fctiwz+stfd+lwz),
   speed switch {1: EffectSpeed_ApplySpeedScale, 2: InterpolationStep} on mediaReq,
   cam switch {3: TriggerSpinFlash+SetColorY(2700), 1/2: CameraEffect_Apply(cam, 1/3, f44)
   with the condition-assign sda21 fold on lbl_806D109C}, then indirect
   desc->onApply50(desc, owner, effectState, mediaReq, lane->itemObj, kind, 1).
5. Unconditional tail: if (desc->impactKind48 != 0 && lane->itemObj != 0) single-case
   switch (case 1): zero mov vel/impact194-19c/impact1ac-1b4 (9 stores, one 0.0f load),
   KartItem_ApplyImpactImpulseAndRumble(owner, 1, io->posX, io->posY, io->posZ).

All of 3-5 matched instruction-exact in the best build; residue is confined to the
kind14 fp block (no frsp -> no f30/f31 saves -> frame 0x80 vs 0xa0 -> prologue/epilogue
and fctiwz slot offsets) plus the small obj/mov scratch swap (r3/r4).

The TwoLane second-lane block replays the SAME desc-action body (separate jumptable
803F7668, isPrimary=0, fctiwz slot 0x8) - duplicated source, NOT a shared inline helper
(each fn reloads desc from its own lane view per section).

## Appendix: ItemEffect_Dispatch salvage C (86.34%, paste-ready)

Replaces the asm body; TU edits it relies on are ALREADY COMMITTED in this batch
(ItemEffectDesc full layout, ItemEffectApplyFn, ItemEffectLaneRun, ItemObjectPosView,
aiTimerD0, impact194.., const float lbl_806D2718, precise prototypes). Forward decl must
become `void ItemEffect_Dispatch(ItemEffectLaneRun *lane, KartItemOpsView *owner, unsigned
char kind, void *effectState, void *mediaReq, const ItemEffectDesc *desc, int itemId,
void *itemObj, int arg4, float intensity);`. Also re-widen the TU splits .data range to
start:0x803F7640 (Dispatch's own jumptable_803F7640 comes first).

```c
typedef struct DispatchDotScratch {
    float dir[3];
    float d[3];
    float mtx[16];
} DispatchDotScratch;

#pragma exceptions off
void ItemEffect_Dispatch(ItemEffectLaneRun *lane, KartItemOpsView *owner, unsigned char kind, void *effectState, void *mediaReq, const ItemEffectDesc *desc, int itemId, void *itemObj, int arg4, float intensity) { /* 0x80050410 size:0x53C */
    volatile DispatchDotScratch s;

    lane->itemId = itemId;
    lane->itemObj = itemObj;
    lane->desc = desc;
    if (arg4 < 0) {
        lane->timer = lane->desc->duration10;
    } else {
        lane->timer = arg4;
    }
    if (lane->desc->kind14 == 1) {
        if (lane->itemObj != 0) {
            KartMovementSpeedView *mov;
            ItemObjectPosView *obj;
            float dx, dy, dz, t0, t1, sum, t2, dot;
            float dir0v, dir1v, dir2v;

            obj = (ItemObjectPosView *)lane->itemObj;
            mov = owner->movement;
            s.mtx[4] = mov->transform[4];
            s.mtx[5] = mov->transform[5];
            s.mtx[6] = mov->transform[6];
            s.mtx[2] = mov->transform[2];
            dir2v = s.mtx[2];
            dir0v = (s.mtx[0] = mov->transform[0]);   /* TARGET WANTS frsp HERE - unsolved */
            dir1v = (s.mtx[1] = mov->transform[1]);
            s.mtx[3] = mov->transform[3];
            s.mtx[7] = mov->transform[7];
            s.mtx[8] = mov->transform[8];
            s.mtx[9] = mov->transform[9];
            s.mtx[10] = mov->transform[10];
            s.mtx[11] = mov->transform[11];
            dx = obj->posX - (s.mtx[12] = mov->transform[12]);  /* frsp wanted */
            dy = obj->posY - (s.mtx[13] = mov->transform[13]);  /* frsp wanted */
            dz = obj->posZ - (s.mtx[14] = mov->transform[14]);  /* frsp wanted */
            s.mtx[15] = mov->transform[15];
            s.d[0] = dx;
            s.d[1] = dy;
            s.d[2] = dz;
            s.dir[0] = dir0v;
            s.dir[1] = dir1v;
            s.dir[2] = dir2v;
            t0 = dx * dir0v;
            t1 = dy * dir1v;
            sum = t0 + t1;
            t2 = dz * dir2v;
            dot = t2 + sum;
            if (dot < lbl_806D26EC) {
                lane->blend = lbl_806D26E4;
            } else {
                lane->blend = lbl_806D26FC;
            }
        } else {
            lane->blend = intensity;
        }
        if (lane->blend > lbl_806D26EC) {
            lane->mode = 1;
        } else {
            lane->mode = 2;
        }
    } else {
        lane->mode = 0;
        lane->blend = lbl_806D26FC;
    }

    if (lane->desc->strPcbKind8 == 1) {
        KartMovementSpeedView *mov;
        float sp;

        if (owner->strPcbGate20 != 0) {
            StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 0xc, 2, lbl_806D26E4);
        }
        mov = owner->movement;
        mov->velX = mov->velX * lbl_806D2718;
        mov->velY = mov->velY * lbl_806D2718;
        mov->velZ = mov->velZ * lbl_806D2718;
        sp = lbl_806D2718 * mov->speed;
        if (sp > mov->table[mov->tableIdx].refSpeed) {
            sp = mov->table[mov->tableIdx].refSpeed;
        }
        mov->speed = sp;
        if (owner->aiTimerD0 <= 0) {
            fn_8019A9BC(owner->movement, lbl_806D26EC, lbl_806D26EC, lbl_806D26EC);
            owner->aiTimerD0 = 0x2d;
        }
    } else {
        if (owner->aiTimerD0 <= 0) {
            owner->aiTimerD0 = 0x2d;
        }
    }

    if (lane->timer >= 0 && lane->itemId >= 0) {
        const ItemEffectDesc *d2;
        float blendv;
        int steer;

        d2 = lane->desc;
        blendv = lane->blend;
        steer = d2->steerKind18;
        if (steer != 0 && kind != 0) {
            float sc20 = d2->steerScale20;
            float prod = sc20 * blendv;
            switch (steer) {
            case 1:
                EffectSteering_InitForLock(effectState, d2->steerParam1c, prod);
                break;
            case 2:
                EffectSteering_InitForVibrate(effectState, d2->steerParam1c, prod, d2->steerParam24);
                break;
            case 3:
                EffectSteering_InitForVibrate_Sub(effectState, d2->steerParam1c, prod);
                break;
            case 4:
                EffectSteering_InitForViscosity_Uniform(effectState, d2->steerParam1c, prod, d2->steerParam24);
                break;
            case 5:
                EffectSteering_InitForViscosity(effectState, d2->steerParam1c, prod, d2->steerParam24, d2->steerParam28, d2->steerParam2c, d2->steerParam30);
                break;
            case 6:
                EffectSteering_InitForSplit(effectState, (int)sc20, d2->steerParam1c);
                break;
            case 7:
                EffectSteering_InitForShake(effectState, d2->steerParam1c, prod, d2->steerParam24, d2->steerParam28);
                break;
            case 8:
                EffectSteering_InitForScale(effectState, d2->steerParam1c, sc20);
                break;
            case 9:
                EffectSteering_InitForDelay(effectState, (int)sc20, d2->steerParam1c);
                break;
            }
        }
        d2 = lane->desc;
        if (d2->speedKind34 != 0) {
            switch (d2->speedKind34) {
            case 1:
                EffectSpeed_ApplySpeedScale(mediaReq, d2->speedParam38, d2->speedParam3c);
                break;
            case 2:
                InterpolationStep(mediaReq, d2->speedParam38, d2->speedParam3c);
                break;
            }
        }
        {
            const ItemEffectDesc *d4 = lane->desc;
            int camk = d4->camKind40;
            if (camk != 0 && kind != 0) {
                float f44 = d4->camParam44;
                switch (camk) {
                case 3:
                    ShadowBillboard_TriggerSpinFlash(owner->billboard);
                    TornadoEffect_SetColorY(owner->effectObj, lbl_806D2700);
                    break;
                case 1: {
                    void *cam;
                    if ((cam = (void *)lbl_806D109C) == 0) {
                        cam = 0;
                    }
                    CameraEffect_Apply(cam, 1, f44);
                    break;
                }
                case 2: {
                    void *cam;
                    if ((cam = (void *)lbl_806D109C) == 0) {
                        cam = 0;
                    }
                    CameraEffect_Apply(cam, 3, f44);
                    break;
                }
                }
            }
        }
        {
            const ItemEffectDesc *d5 = lane->desc;
            void *io = lane->itemObj;
            ItemEffectApplyFn fnp = d5->onApply50;
            if (fnp != 0) {
                fnp(d5, owner, effectState, mediaReq, io, kind, 1);
            }
        }
    }
    {
        const ItemEffectDesc *d6 = lane->desc;
        void *io2 = lane->itemObj;
        if (d6->impactKind48 != 0 && io2 != 0) {
            switch (d6->impactKind48) {
            case 1: {
                KartMovementSpeedView *mv2 = owner->movement;
                mv2->velX = lbl_806D26EC;
                mv2->velY = lbl_806D26EC;
                mv2->velZ = lbl_806D26EC;
                mv2->impact194 = lbl_806D26EC;
                mv2->impact198 = lbl_806D26EC;
                mv2->impact19c = lbl_806D26EC;
                mv2->impact1ac = lbl_806D26EC;
                mv2->impact1b0 = lbl_806D26EC;
                mv2->impact1b4 = lbl_806D26EC;
                KartItem_ApplyImpactImpulseAndRumble(owner, 1, ((ItemObjectPosView *)io2)->posX, ((ItemObjectPosView *)io2)->posY, ((ItemObjectPosView *)io2)->posZ);
                break;
            }
            }
        }
    }
}
#pragma exceptions reset
```

Known residue of this form vs target: (a) no frsp f0/f2/f3/f4/f6 in the fp block (the
hard-block); (b) without those webs f30/f31 are not saved, frame is 0x80 not 0xa0, so
prologue/epilogue and the fctiwz spill slot (0x8 vs 0x60) differ; (c) obj/mov land r3/r4
swapped; (d) fp temp numbering inside the block cascades. Items b-d are expected to
self-correct if (a) is ever solved.
