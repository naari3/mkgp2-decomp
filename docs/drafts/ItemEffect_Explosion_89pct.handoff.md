# HANDOFF batch_promote_80051648_effectsrun

6 of 9 fns promoted asm_fn -> matched C at 100.0%, SHA-1 OK (commit 50ec08e).
ItemEffect_Explosion attempted (11 probes, best 88.99%) and reverted to asm_fn
on an fp volatile-web tie-break swap; salvage C below. ItemEffect_Trap and
ItemEffect_Projectile precan-parked at 0 probes (class-2 frsp interleave +
cross-call reassociation, both documented classes).

```json
{
  "batch_id": "batch_promote_80051648_effectsrun",
  "sub_summary": "5x ItemTable_FindEntryByIdStride* + CarObject_GetField304Vec3 matched 100% (6 fns, 1 build for all); ItemEffect_Explosion skipped at 88.99% on an fp tie-break swap (11 probes, salvage C in appendix); ItemEffect_Trap / ItemEffect_Projectile precan-parked 0 probes (class-2 frsp interleave + cross-call product-only-callee-saved)",

  "results": [
    {
      "addr": "0x80051648",
      "name": "ItemEffect_Explosion",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 88.99% over 11 builds; every instruction byte-exact EXCEPT one fp volatile web tie-break: target vx=f3 / lbl_806D271C const=f4, CW 1.3.2 inverts to const=f3 / vx=f4 (cascade: d.x store cannot sink below the sqrtf fcmpo because vx=f4 must die before mag=f4 reuse). Same family as CarObject_ProcessWarpAndDash tie-break swap. exceptions on/off probe identical -> NOT approach-B class. 4 solved sub-shapes recorded in TU ledger + docs note (sqrtf inline byte-exact, d-fill-then-a-fill pool regime, anti-fmadds sum form, IdFlagPair 8-byte copy tail). Salvage C in appendix; probe ledger comment above the asm body."
    },
    {
      "addr": "0x80051834",
      "name": "ItemEffect_Trap",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "precan park, 0 probes. Two documented hard-block classes at once: (1) class-2 frsp store-forward interleave (16-float transform copy stores raw lfs values while the dot product consumes frsp-rounded copies of the same loads - cw132-frsp-store-forward-negative-probes ledger says unreachable from plain C); (2) cross-call product-only-callee-saved (mulli r30,idx,0x18 kept across ItemEffectDamp_TryArm, lbl_802ED7BC base rematerialized per region = TryStartByCategory addressing-reassociation family)."
    },
    {
      "addr": "0x80051A70",
      "name": "ItemEffect_Projectile",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "precan park, 0 probes. Same two classes as Trap: class-2 frsp interleave in the velocity-magnitude block (raw stfs of velX/Y/Z to two stack regions interleaved with frsp-rounded squares) + mulli r31,idx,0x14 kept callee-saved across ItemEffectImpact_TryArm with lbl_802ED5B4 base remat. First normalize block (from arg, no frsp) is solvable with the Explosion sqrtf recipe if the classes ever unlock."
    },
    {
      "addr": "0x80051CB8",
      "name": "ItemTable_FindEntryByIdStride16",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "TU-internal promote (approach B). 1 build. Plain for (i=0; i<count; i++) { if (tbl->id == itemId) return i; tbl++; } over typed ItemCatEntry16* converts to li r6,0 / mtctr / cmpwi-ble guard / lwz-cmpw-bne / mr r3,r6 early return / addi-addi-bdnz with the pointer walk reusing the r3 param web. No extab (leaf), no manual emit existed."
    },
    {
      "addr": "0x80051CF0",
      "name": "ItemTable_FindEntryByIdStride12_v1",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "sibling replication of Stride16 with ItemCatEntry12*. 1 build."
    },
    {
      "addr": "0x80051D28",
      "name": "ItemTable_FindEntryByIdStride12_v2",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "sibling replication. 1 build."
    },
    {
      "addr": "0x80051D60",
      "name": "ItemTable_FindEntryByIdStride24",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "sibling replication with new ItemCatEntry24 typedef (id + pad to 0x18). 1 build."
    },
    {
      "addr": "0x80051D98",
      "name": "ItemTable_FindEntryByIdStride20",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "sibling replication with new ItemCatEntry20 typedef (id + pad to 0x14). 1 build."
    },
    {
      "addr": "0x80051DD0",
      "name": "CarObject_GetField304Vec3",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "1 build. *out = car->vec304 (12-byte Vec3 struct assignment via new CarObjAux304View) reproduces the CW word-copy lwz r5/lwz r0/stw/stw/lwz r0/stw exactly. Signature retyped from asm void f(void) to void f(Vec3 *out, CarObjAux304View *car); only caller is an asm bl (no type pressure)."
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
      "path": "docs/notes/cw132-effectsrun-batch-idioms.md",
      "content": "# EffectsRun batch idioms (2026-06-10, batch_promote_80051648_effectsrun)\n\nMatched in src/game/auto_ONKARTHIT_block.c (commit 50ec08e): ItemTable_FindEntryByIdStride16/12_v1/12_v2/24/20 + CarObject_GetField304Vec3.\n\nWin idioms:\n\n1. ctr scan loop WITH live counter (extends itemeffect idiom 2): for (i = 0; i < count; i++) { if (tbl->id == itemId) return i; tbl++; } over a typed entry pointer param converts to li r6,0; mtctr r4; cmpwi r4,0; ble fail + lwz/cmpw/bne; mr r3,r6; blr + addi tbl; addi i; bdnz. The counter being READ on the success exit does not block ctr conversion (the dead-counter class only bites when the counter is never read); the tbl walk reuses the r3 param register when the param itself is mutated (tbl++), no fresh callee-saved. Matched 5 stride siblings (0x10/0xc/0xc/0x18/0x14) on the first build each.\n2. 12-byte Vec3 out-copy: *out = car->vec304; struct assignment emits the canonical CW word copy lwz r5,0x304(r4); lwz r0,0x308(r4); stw r5; stw r0; lwz r0,0x30c(r4); stw r0 - no lfs/stfs, no member-wise spelling needed.\n3. 8-byte pair tail copy (solved sub-shape inside the parked Explosion): *(IdFlagPair *)&self->activeId = *(const IdFlagPair *)&tbl[idx].valA; reproduces mulli; lis; addi rScratch,@l; add rD (coalesced with the mulli web); lwz r3,0x4; lwz r0,0x8; stw r3; stw r0. Named int pair locals ALWAYS canonicalize to reversed loads (second field first) regardless of decl/assign order - the struct copy is the only probed form that loads ascending and pairs r3/r0.\n4. MSL inline sqrtf recipe (MainUpdate handoff idiom 4) confirmed byte-exact in a second context: static inline with volatile float y, guard x > lbl_806D26EC, __frsqrte, 3 NR steps written lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess)), then y = (float)(x * guess); return y; - frsqrte block + sp+0x8 store/reload exact. Requires retyping the lbl externs to const double.\n5. fp pool regime depends on statement order around a Vec3 const fill: with the const fill FIRST, a single-use const load web stays scratch (f0) and the zero web takes the slot right after the first named local; moving the const fill AFTER the d-fill (d.x..d.z stores) promotes BOTH const webs into the pool in target-like positions (zero=f5, vy=f6, vz=f7, mag reusing f4). Statement order is a register-allocation lever even when emission order barely changes.\n6. anti-fmadds sum form: mag = sqrtf(d.z*d.z + (d.x*d.x + d.y*d.y)) reading the JUST-STORED struct members (CSE keeps the loaded registers) emits 3 fmuls + 2 fadds; the same sum written over the named float locals fuses into fmadds. Pair with onapplyrun idiom 1 (named trio assigned then stored).\n\nHard-block instance (existing family, new data point): ItemEffect_Explosion 0x80051648, fp volatile-web TIE-BREAK SWAP - target vx=f3 / lbl_806D271C-const=f4, CW emits const=f3 / vx=f4 with everything else byte-identical (88.99%; the diff is the 2-reg rename + the schedule cascade: the d.x store sinks below the sqrtf fcmpo only when vx is not mag's reuse register). Negative probes: vel assign order x,y,z vs y,x,z (canonicalized), a.y = mag = C fold and cv named local (both copy-propagated), pragma opt_propagation off (no effect), exceptions on/off (identical -> not approach-B class), decl-order permutations (pool position of the const web did not respond). Same family as CarObject_ProcessWarpAndDash callee-saved tie-break (allocator-internal ordering artifact). Precan note: a 2-register-swap residue at ~89-99% with zero instruction-content diff should be classified here after 2-3 decl/order probes, not chased to 11.\n\nPrecan parks (0 probes, both classes already documented): ItemEffect_Trap and ItemEffect_Projectile each combine class-2 frsp store-forward interleave with the cross-call product-only-callee-saved reassociation (mulli kept in a callee-saved across a TryArm call while the table base lis/addi is rematerialized per use region). Ledger comments above both asm bodies in the TU."
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

- No class 1 invert sites, no `bl __unexpected`, no ScopedTimer `subi rX,rY,0x217d`
  in any of the 9 fns.
- The 5 find-loop ctr loops are NOT the dead-counter class (counter r6 is read
  on the success exit) - promoted cleanly.
- Trap and Projectile: class-2 frsp interleave spotted in precan (raw stfs +
  frsp-rounded math on the same lfs values) -> 0-probe park per the batch
  precan rules; both ALSO carry the cross-call product-only-callee-saved shape.
- Explosion's table tail uses the direct symbol lbl_802ED8C4 (the sub-table has
  its own label), NOT the symbol+const addi form -> not the
  addressing-reassociation class; it indeed matched (IdFlagPair copy).
- All three effect fns have manual extab with dtor_80036E40 refs (approach B
  mandatory); the 6 promoted fns have no extabindex entries (leaf, no emit).

## funcs_matched_delta note

0 by the PROGRESS counter: bundle-internal promotes replace byte-identical
asm_fn bodies (same as dispatchpair / twolane / onapplyrun batches).
decomp value: 6 more fns now have real C.

## TU edits future batches can reuse (already committed)

- `extern const float lbl_806D271C;` / `extern const double lbl_806D2720;`
  `lbl_806D2728;` (retyped from unsigned int for fp use).
- typedefs: ItemCatEntry20, ItemCatEntry24, IdFlagPair, CarObjAux304View;
  ItemObjectPosView gained velX/velY/velZ at 0xb8..0xc0.
- `extern ItemCatEntry12 lbl_802ED8C4[];` (moved below the typedef; explosion
  table = lbl_802EBA18+0x1eac with its own label).
- Find-loop signatures retyped in the forward decls to typed entry pointers
  (callers are asm bl only).

## Appendix: ItemEffect_Explosion salvage C (88.99%, paste-ready)

Replaces the asm body; relies on the committed TU edits above. Known residue
vs target: the fp tie-break swap (vx <-> constC on f3/f4) and its schedule
cascade (prologue stw r30/r29 + mr r29 slots, d/a store placement vs fcmpo).
Everything else, including the call region, vel-zero block, Vec3 fills and
the table tail, is byte-exact.

```c
/* MSL-style inline sqrtf (frsqrte + 3 NR steps, volatile store-reload);
 * consts referenced via lbl externs so no local rodata is emitted. */
static inline float ItemEffect_sqrtf(float x) {
    volatile float y;
    if (x > lbl_806D26EC) {
        double guess = __frsqrte(x);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

#pragma exceptions off
void ItemEffect_Explosion(ItemStateBlock *self, int idx, void *arg) { /* 0x80051648 size:0x1EC */
    ItemObjectPosView *obj = (ItemObjectPosView *)arg;
    Vec3 a; /* sp+0x24 */
    Vec3 d; /* sp+0x18 */
    Vec3 p; /* sp+0xc */
    void *bb;
    float vx, mag, vy, vz;

    vx = obj->velX;
    vy = obj->velY;
    vz = obj->velZ;
    d.x = vx;
    d.y = vy;
    d.z = vz;
    a.y = lbl_806D271C;
    a.x = lbl_806D26EC;
    a.z = lbl_806D26EC;
    mag = ItemEffect_sqrtf(d.z * d.z + (d.x * d.x + d.y * d.y));
    if (mag <= lbl_806D26EC) {
        d.x = d.y = d.z = lbl_806D26EC;
    } else {
        float inv = lbl_806D26FC / mag;
        d.x = d.x * inv;
        d.y = d.y * inv;
        d.z = d.z * inv;
    }
    ItemStateSlotC_TryArm(self->guard, &a, &d, self->owner->movement->transform);
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
    ShadowBillboard_SetField0x6CAndComputeAxis(bb, 3);
    {
        KartMovementSpeedView *m2 = self->owner->movement;
        float fx, fy, fz;
        fz = m2->transform[14];
        fy = m2->transform[13];
        fx = m2->transform[12];
        p.x = fx;
        p.y = fy;
        p.z = fz;
    }
    ShadowBillboard_SetVec3At0x70(bb, &p);
    *(IdFlagPair *)&self->activeId = *(const IdFlagPair *)&lbl_802ED8C4[idx].valA;
}
#pragma exceptions reset
```
