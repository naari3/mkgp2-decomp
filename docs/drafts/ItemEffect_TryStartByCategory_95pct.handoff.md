# HANDOFF batch_promote_80051100_onapplyrun

4 of 5 fns promoted asm_fn -> matched C at 100.0%, SHA-1 OK (commit 640aa84).
ItemEffect_TryStartByCategory attempted (7 probes, best ~95%) and reverted to
asm_fn on a new addressing-reassociation hard-block; probe ledger + salvage C
below.

```json
{
  "batch_id": "batch_promote_80051100_onapplyrun",
  "sub_summary": "OnApply_BoostLandingSE / OnApply_FreezeKartOrSlowdown / OnApply_MushroomBoost / TryStartByCategory_Wrap matched 100% (4 fns, 1-2 builds each); TryStartByCategory skipped at ~95% on a new category-table addressing reassociation hard-block (7 negative probes, salvage C in appendix)",

  "results": [
    {
      "addr": "0x80051100",
      "name": "ItemEffectDesc_OnApply_BoostLandingSE",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "TU-internal promote (approach B, manual extab kept). 1 build. ItemEffectApplyFn impl: 7th param is unsigned char isPrimary ((u8)r9, cmplwi 1), returns int desc->itemId. Reuses strpcbrun condition-assign sda21 fold for lbl_806D10A0; body parallels matched KartItem_TryArmBoostOnLanding."
    },
    {
      "addr": "0x80051184",
      "name": "ItemEffectDesc_OnApply_FreezeKartOrSlowdown",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "2 builds (1st failed compile only: TornadoEffect_SetColorY must stay K&R-unprototyped because matched StopCarObjectSE calls it with 1 arg; the unprototyped 2-arg call with a float lvalue still emits plain lfs f1 - default promotion costs nothing for codegen). Early return desc->itemId duplicated per path matches the two epilogue loads."
    },
    {
      "addr": "0x8005125C",
      "name": "ItemEffectDesc_OnApply_MushroomBoost",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "1 build. Same body as the GenericHandler itemId==0x17 block. Target falls off without a return value on the isPrimary path (r3 garbage) - C body ends without return statement."
    },
    {
      "addr": "0x800512E4",
      "name": "ItemEffect_TryStartByCategory_Wrap",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "1 build, SelectAndDispatch_Wrap pattern (pass-through thunk, no prologue load hoist). Callee stays asm_fn with signature retyped in place (twolane idiom 8): asm int ItemEffect_TryStartByCategory(ItemStateBlock*, int, void*)."
    },
    {
      "addr": "0x80051304",
      "name": "ItemEffect_TryStartByCategory",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best ~95% over 7 builds (203/214 instruction regions; entire find-chain front half, all guards, Projectile/Trap/Explosion/TornadoLift/BossGrab calls, StrPcb gates, vel-zero blocks and both vec3 fills exact). Sole hard residue: category-table entry addressing. Target computes (r31+0x1f18/0x1f24) into a SCRATCH addi then adds the scaled index (lwz 0x4/0x8 displacements) and keeps only idx<<4 callee-saved (r29) across the BossGrab calls. CW 1.3.2 -lang=c reassociates every probed form (cast-index, byte-arith, fn-scope/block-scope named table ptrs, named off local, blob-struct member, static inline accessor) - the constant sinks into the displacement or joins the product, and the cross-call CSE saves the full pointer instead of the offset. Likely C++ accessor this-temp semantics in the original (same family as itemeffect idiom 3 table-base init split). Probe ledger comment above the asm body in the TU; paste-ready ~95% C in appendix. Reverted to asm_fn, signature retyped for the Wrap caller."
    }
  ],

  "configure_py": {
    "add_objects": []
  },

  "splits_txt": {
    "add_entries": []
  },

  "symbols_txt": {
    "set_scope": [],
    "set_attr": [],
    "rename": []
  },

  "docs_notes": [
    {
      "path": "docs/notes/cw132-onapplyrun-batch-idioms.md",
      "content": "# OnApply/TryStart batch idioms (2026-06-10, batch_promote_80051100_onapplyrun)\n\nMatched in src/game/auto_ONKARTHIT_block.c (commit 640aa84): ItemEffectDesc_OnApply_BoostLandingSE / _FreezeKartOrSlowdown / _MushroomBoost / ItemEffect_TryStartByCategory_Wrap.\n\nWin idioms:\n\n1. Vec3 out-param fill, SOLVED shape for the z,y,x load-order family (cf. strpcbrun idiom 8 hard-block KartItem_GetCarVelocityVec3): declare three float locals in x,y,z order (-> f0,f1,f2 by decl-order rule), ASSIGN them in z,y,x order, then store x,y,z into the struct. Reproduces target lfs f2(z); lfs f1(y); lfs f0(x); stfs f0; stfs f1; stfs f2 exactly (two sites in TryStartByCategory). A block-local pointer + direct member copies collapses to lfs/stfs pairs reusing f0 (wrong); the named-float split is load-bearing.\n2. K&R-unprototyped extern with a float argument: a matched fn may call the same symbol with a different arg count (TornadoEffect_SetColorY: 1 arg in KartItem_StopCarObjectSE, 2 args in OnApply_Freeze). Keep the extern unprototyped; passing a float LVALUE through default promotion still emits a single lfs f1 (no frsp, no double penalty), byte-identical to a prototyped call.\n3. ItemEffectApplyFn hook ABI as implemented (vs the call-site typedef): 7th param is unsigned char isPrimary (clrlwi r9,24), return type int = desc->itemId. BoostLandingSE tests isPrimary == 1 (cmplwi 1) with a single shared return load; Freeze/Mushroom test isPrimary == 0 with an early return (per-path return loads). MushroomBoost falls off the end without a return value on the isPrimary path (no lwz before epilogue) - write the C body with no final return statement.\n4. asm_fn in-place signature retype (twolane idiom 8) scales: 9 asm fns retyped this batch (5x ItemTable_FindEntryByIdStride*, ItemEffect_Projectile/Trap/Explosion, ItemEffect_TryStartByCategory) so promoted C can call them; bodies untouched, all stay 100%.\n5. ItemStateBlock pad fields named (owner 0x0 / curItemId 0x8) without disturbing existing users; driver field 0x1f8 accessed via a fresh DriverStateView cast instead of widening KartDriverBusView.\n\nHard-block (new instance class for sec 14.2): category-table entry addressing reassociation, ItemEffect_TryStartByCategory 0x80051304. Target: addi rScratch, rBase, K (K=0x1f18/0x1f24 inside lbl_802EBA18); add rE, rScratch, prod; lwz 0x4/0x8(rE); only idx<<4 kept callee-saved across calls (the table-base addi is rematerialized per use region). CW 1.3.2 -lang=c instead (a) sinks K+memberoff into the load displacement for ((T*)(base+K))[idx].f, (b) joins K with the product for (T*)(base+K+idx*S), (c) materializes a fn-scope named table ptr into a callee-saved (stmw set grows - disqualifying), (d) copy-propagates block-scope tb/e locals back to (a)/(b), (e) with named int off=idx<<4 folds K+4 into off (lwzx) or displacement, (f) lowers blob-struct member access ->t12[idx] same as (a), (g) inlines a static inline accessor At(tbl,idx) transparently to (a). 7 probes, no C form produced the grouped scratch-addi shape; the double-mention loaded-pointer precedent (mov->table[mov->tableIdx] add+lfs form) works only because its table base is an OPAQUE loaded value, not symbol+const. Precan rule: if target walks a const-offset table inside a larger blob via addi rScratch,rBase,K + add and the table base is symbol+const, expect this class; budget 2 probes (named-off + cast-index) then park."
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

## Precan results (step 0)

- No class 1 invert sites, no class 2 frsp interleave, no mtctr/bdnz, no
  `bl __unexpected`, no `subi rX,rY,0x217d` in any of the 5 fns.
- Wrap has no hoisted load above the LR-save (pure pass-through thunk) ->
  not the prologue-load-hoist class.
- TryStartByCategory carries two dtor-bearing stack objects in its manual
  extab (dtor_80036E40 at sp+0x14 / sp+0x8) = the two Vec3 locals; approach B
  keeps the manual emit so plain C Vec3 locals suffice (vt declared before vg
  lands them at 0x14 / 0x8 naturally).

## funcs_matched_delta note

0 by the PROGRESS counter: bundle-internal promotes replace byte-identical
asm_fn bodies, so dtk's matched-function count does not move (same as the
dispatchpair / twolane batches). decomp value: 4 fns now have real C.

## Appendix: ItemEffect_TryStartByCategory salvage C (~95%, paste-ready)

Replaces the asm body. TU edits it relies on are ALREADY COMMITTED (ItemStateBlock
owner/curItemId fields, DriverStateView, ItemCatEntry12/16 typedefs, typed asm
helper signatures, prototyped ShadowBillboard_/StrPcb_SetTimer3034_38/
ItemEffect_TornadoLift/ItemEffect_BossGrab externs). Known residue vs target:
(a) tornado/boss-grab entry addressing reassociation (the hard-block above);
(b) its cascades: bb2/off callee-saved swap (r27/r29), vel-zero volatile regs
(r4 vs r3/r6), li r3,0 placement, branch-target offsets.

```c
#pragma exceptions off
int ItemEffect_TryStartByCategory(ItemStateBlock *self, int itemId, void *arg) { /* 0x80051304 size:0x344 */
    unsigned char *base = (unsigned char *)lbl_802EBA18;
    int idx;
    Vec3 vt; /* sp+0x14, tornado branch */
    Vec3 vg; /* sp+0x8, boss-grab branch */

    idx = ItemTable_FindEntryByIdStride20(base + 0x1b9c, 0x1a, itemId);
    if (idx >= 0) {
        if (self->curItemId >= 0) {
            return 2;
        }
        if (itemId == 0x44 || itemId == 0x43) {
            int st = ((DriverStateView *)self->owner->ownerDriver)->state1f8;
            if (st == 0 || st == 1) {
                return 2;
            }
        }
        self->curItemId = itemId;
        ItemEffect_Projectile(self, idx, arg);
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride24(base + 0x1da4, 0xb, itemId);
    if (idx >= 0) {
        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        ItemEffect_Trap(self, idx, arg);
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride12_v2(base + 0x1eac, 0x9, itemId);
    if (idx >= 0) {
        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        ItemEffect_Explosion(self, idx, arg);
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride12_v1(base + 0x1f18, 0x1, itemId);
    if (idx >= 0) {
        void *bb;

        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        ItemEffect_TornadoLift(self->guard, self->owner->movement->transform);
        if (self->owner->strPcbGate20 != 0) {
            StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 0xc, 2, lbl_806D26E4);
        }
        {
            KartMovementSpeedView *m = self->owner->movement;
            m->velX = lbl_806D26EC;
            m->velY = lbl_806D26EC;
            m->velZ = lbl_806D26EC;
            m->impact194 = lbl_806D26EC;
            m->impact198 = lbl_806D26EC;
            m->impact19c = lbl_806D26EC;
            m->impact1ac = lbl_806D26EC;
            m->impact1b0 = lbl_806D26EC;
            m->impact1b4 = lbl_806D26EC;
        }
        bb = self->owner->billboard;
        ShadowBillboard_SetField0x6CAndComputeAxis(bb, 2);
        {
            KartMovementSpeedView *m2 = self->owner->movement;
            float fx, fy, fz;
            fz = m2->transform[14];
            fy = m2->transform[13];
            fx = m2->transform[12];
            vt.x = fx;
            vt.y = fy;
            vt.z = fz;
        }
        ShadowBillboard_SetVec3At0x70(bb, &vt);
        /* HARD-BLOCK: target = addi r0,r31,0x1f18; add r5,r0,(idx*0xc);
         * lwz 0x4/0x8(r5). No probed C form reproduces the grouping. */
        self->activeId = ((ItemCatEntry12 *)(base + 0x1f18))[idx].valA;
        self->activeFlag = ((ItemCatEntry12 *)(base + 0x1f18))[idx].valB;
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride16(base + 0x1f24, 0x1, itemId);
    if (idx >= 0) {
        void *bb2;

        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        /* HARD-BLOCK: target keeps idx<<4 in r29 and remats addi
         * r0,r31,0x1f24 per use; CW saves the full pointer instead. */
        ItemEffect_BossGrab(self->guard, self->owner->movement->transform, arg, ((ItemCatEntry16 *)(base + 0x1f24))[idx].valA);
        bb2 = self->owner->billboard;
        ShadowBillboard_SetField0x6CAndComputeAxis(bb2, 4);
        {
            KartMovementSpeedView *m3 = self->owner->movement;
            float gx, gy, gz;
            gz = m3->transform[14];
            gy = m3->transform[13];
            gx = m3->transform[12];
            vg.x = gx;
            vg.y = gy;
            vg.z = gz;
        }
        ShadowBillboard_SetVec3At0x70(bb2, &vg);
        if (self->owner->strPcbGate20 != 0) {
            StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 0xc, 2, lbl_806D26E4);
        }
        {
            KartMovementSpeedView *m4 = self->owner->movement;
            m4->velX = lbl_806D26EC;
            m4->velY = lbl_806D26EC;
            m4->velZ = lbl_806D26EC;
            m4->impact194 = lbl_806D26EC;
            m4->impact198 = lbl_806D26EC;
            m4->impact19c = lbl_806D26EC;
            m4->impact1ac = lbl_806D26EC;
            m4->impact1b0 = lbl_806D26EC;
            m4->impact1b4 = lbl_806D26EC;
        }
        self->activeId = ((ItemCatEntry16 *)(base + 0x1f24))[idx].valB;
        self->activeFlag = ((ItemCatEntry16 *)(base + 0x1f24))[idx].valC;
        return 0;
    }
    return 1;
}
#pragma exceptions reset
```
