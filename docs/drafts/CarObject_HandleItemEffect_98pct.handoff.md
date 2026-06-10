# HANDOFF batch_promote_8004f858_handleitemfx

CarObject_HandleItemEffect 0x8004F858 (0x7B8, 494 instrs) taken from asm to **98.62% C**
(best build, attempt 6 of 9). Blocked on a dead-counter web that CW 1.3.2 deletes in every
probed source form, leaving the function 1 net instruction short of target (byte-identical
unreachable), plus a likely-cascading callee-saved permutation at 2 of 3 inline-expansion
sites. Worktree restored with git checkout; `ninja build/GNLJ82/ok` green at baseline.

```json
{
  "batch_id": "batch_promote_8004f858_handleitemfx",
  "sub_summary": "CarObject_HandleItemEffect promote: skipped at 98.62% - dead ctr-loop counter web (li r4,0 + addi r4,r4,1, no reads) in target's first table-scan loop is deleted by CW 1.3.2 under all 8 probed source forms incl. inline-asm addi with volatile_asm; remaining residue is that web (5 diff rows) + callee-saved permutations at lane-clear inline sites 2/3 (site 1 matched exactly)",
  "results": [
    {
      "addr": "0x8004F858",
      "name": "CarObject_HandleItemEffect",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 98.62% (494/494 aligned rows, 89 diff rows: 84 pure register renames at lane-clear inline sites 2/3, 5 the loop-1 dead counter web). All control flow, 20-body switch in memory order, 3x ApplyDriftBoost inline, 3x lane-clear inline content, lwzu scan loop, double-blt guard, u64 ClearMask, m/found2 short-circuit verified matching. Paste-ready C + required extern/struct edits in HANDOFF appendix."
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
      "path": "docs/notes/cw132-dead-counter-ctr-loop-hardblock.md",
      "content": "# CW 1.3.2 dead-counter-in-ctr-loop hard-block (2026-06-10, batch_promote_8004f858_handleitemfx)\n\nTarget idiom: ctr-converted scan loop that ALSO materializes a never-read up-counter (`li r4,0x0` init + `addi r4,r4,0x1` per iteration, no reads before the register is clobbered). Seen in CarObject_HandleItemEffect 0x8004F858 loop 1 (pair-table scan over lbl_802ED94C, 0x13 iterations, two compares per iteration via lwz/lwzu). Same family as the dead `i` counter in CarObject_MainUpdate's mtx loop (sec 14.2 flavor 5) and the const-prop-escaped `mr r6,r4` init in KartItem_GetMaxSpeedWithBonus.\n\nProbed source forms - ALL get the counter web deleted (or the loop fails to ctr-convert):\n1. do-while with `++i` + `while (i < 0x13)`: keeps i but NO ctr conversion (cmpwi/blt, init split addi r0+mr).\n2. `for (i = 0; i < 0x13; i++)` + manual `*p` / `*++p` / `++p` walk: ctr-converts, lwzu reproduced, counter eliminated with the loop control.\n3. separate body counter (`for (n...)` control + `++i` in body): ctr-converts, i web DCEd.\n4. shared u8 variable (loop-1 counter reused later as loop-2 found flag, hoping variable-granularity liveness): increments still DCEd.\n5. dead copy `n = i;` after the loop (single-pass-DCE test): both copy and web removed - CW DCE is iterative.\n6. `#pragma opt_dead_assignments off` around the fn: no effect (inert or not honored at -O4,p global optimizer).\n7. pointer-bound for (`p < base + 0x26`) with i++ header increment: does NOT ctr-convert (cmplw kept per iteration; CW does not derive trip count from pointer bounds here).\n8. inline `asm { addi i, i, 0x1 }` in the loop body (requires `register int i`, else \"not assigned to a register\" error): the asm statement itself is integrated into IR and DCEd; `#pragma volatile_asm on` does NOT protect it.\n\nConclusion: with -O4,p -inline auto, CW 1.3.2 always removes a never-read counter web in a ctr loop. No pure-C or pragma path found to retain it. Functions whose target carries this idiom cannot currently be promoted byte-identical.\n\nPrecan rule: in a ctr loop (`mtctr` + `bdnz`), an `addi rX,rX,1` whose register has no read before the next write to rX marks this class. Budget 0-2 probes, then park as asm_fn.\n\nSecondary observation from the same batch: the missing web also seems to perturb downstream callee-saved tie-breaks (lane-clear inline sites 2/3 land permuted registers while site 1 matches exactly with identical inlined source) - allocator history is global, so solving the counter may cascade-fix the site permutations.\n"
    }
  ],
  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },
  "blocked_reason": "Target's first scan loop carries a dead up-counter web (li r4,0 + addi r4,r4,1, never read) inside the ctr-converted loop; CW 1.3.2 (-O4,p) deletes that web in all 8 probed source forms (incl. inline-asm addi under volatile_asm), leaving the build 1 net instruction short (0x7B4 vs 0x7B8) - byte-identical structurally unreachable. Remaining 84 diff rows are callee-saved register renames at lane-clear inline-expansion sites 2/3 (site 1 matches exactly), suspected cascade from the missing web.",
  "user_attention": null
}
```

## Precan results (step 0)

- No `bl __unexpected` / FP prologue (not the EH-scaffolding class).
- No `subi rX,rY,0x217d` (no ScopedTimer).
- No class-1 invert sites: every `bne / li 1 / b` here is the natural break/early-exit form.
- No class-2 frsp interleave; no flavor-5 multi-web SR loop (the 2-lane clear loop is the
  already-matched KartItem_CancelActiveEffect body, cmplwi/blt form).
- One previously-uncatalogued precan signature WAS present and turned out to be the killer:
  ctr loop with materialized dead counter (docs note in the JSON). Add to the precan list.

## Decoded structure (verified at 98.62%)

`int CarObject_HandleItemEffect(ItemSecondaryLane *self, int itemId)` - self is the
secondary-lane view (owner 0x0 / itemId 0x8 / blend 0xc). Returns 0 (not in pair table /
default case), 1 (guard active / event filter / handler returned 0), 2 (committed).

1. Scan lbl_802ED94C = 19 pairs of int (0x98 bytes, ends exactly at lbl_802ED9E4) with
   `*p` / `*++p` / `++p` (the `*++p` spelling reproduces target lwzu). Not found -> 0.
2. ItemStateGuard_IsActive(self->owner->stateBlock->guard) == 1 -> return 1.
3. Scan lbl_803F75D0 = 13 s16 entries (lha) -> found2.
4. ev = self->owner->effectTable->run18; m = (ev==0x98 || ev==0x92) written as an
   if/else-if/else constant chain; if (m == 1 && found2 == 0) return 1;
5. handled = 1; then the double-blt guard: nested identical `if (self->itemId >= 0)`
   reproduces target cmpwi; blt; blt (dtor double-beq family). Inner body = the
   OnFallOffOrDeath sec-block (clear self lane).
6. self->blend = 0.0f; then a 20-body switch, source order = memory order:
   0x17 boost(5); {e,10,15,16,1e,1f,20,24,28} blend=26F8+cancel;
   {c,d,f,11,13,14,18,25,26,27,8b,91} blend=2700+cancel; 0x19 blend=2704 +
   movement->0x300=2708; 0x141 cancel+boost(6); 0x1b/0x1a/0x1c blend=2704; 0x142 boost(6);
   0x21/0x1d/0x23/0x8c blend=270C; 0x22 blend=2710; 0x52/0x99/0x9a/0x9d/0x9b blend=2714;
   default return 0. boost(N) = CarObject_ApplyDriftBoost(self->owner, lbl_806D26F0, N)
   (same-TU fn, auto-inlined); cancel = lane-clear helper (see below).
7. if (handled == 0) return 1; commit: itemId store + Compact/ThrowConfirm/Confirm calls
   (re-reading self->itemId per call) -> return 2.

## Win idioms verified this batch (do NOT rediscover)

1. Lane-clear inlining: `-inline auto` REFUSES loop-containing fns regardless of
   `#pragma inline_max_size(1024)` (before caller or callee). `-inline auto,deferred` as TU
   extra_cflags inlines nothing more and BREAKS the manual extab layout ([extab-0] dropped
   to 12.94%) - never use in extab_user TUs. Working mechanism: dedicated
   `static inline KartItem_CancelLanes_inl(ItemSecondaryLane *sec)` (explicit inline takes
   loops), with KartItem_CancelActiveEffect kept as its own untouched direct body (stays
   100%). A wrapper restructure (Cancel body moved to helper, Cancel = thin caller) flips
   Cancel's callee-saved assignment direction (drops to 97.35%) - avoid.
2. Helper decl order for inline-site regs: (itemId, cursor, mediaReq, effectState, owner,
   i, tbl, obj, q) with `obj = sec->owner` inside the helper reproduced site 1 EXACTLY
   (id2=r22, cursor=r23, mb=r24, st=r25, owner=r26, i=r27, tbl=r28, obj=r29). Passing
   `self` (no argument temp) is what frees obj to land r29; an argument temp
   (`helper(self->owner)`) lands r22 and shifts every other web.
3. `*++p` forces lwzu (update-form load) for mid-iteration pointer bumps.
4. Double guard `if (x >= 0) if (x >= 0)` reproduces cmpwi + blt + blt (CSE keeps one
   compare, both branches survive).
5. The m flag must be the branchy if/else-if/else constant chain (li 1 / li 1 / li 0 into
   r0), then `if (m == 1 && found2 == 0)` short-circuit.
6. MWCC statement asm in C: operands naming locals require `register` qualifier
   ("i was not assigned to a register" otherwise); the asm node participates in global
   optimization and CAN be DCEd; volatile_asm does not protect it.

## Residue detail (for retry)

- Loop 1 dead counter: 5 diff rows (li r4,0 vs mr r4,r5 / addi r4,r4,1 missing / p walking
  r4 instead of r5). See docs note for the 8 failed probes.
- Sites 2 (FC44, case group 0xc..) and 3 (FD58, case 0x141): identical inlined content,
  registers permuted. Target site2: tbl=r27,cursor=r23,mb=r26,st=r25,owner=r24,i=r28,
  obj=r29; site3: i=r27,tbl=r28,mb=r26,st=r25,owner=r24,obj=r29. Mine (both sites):
  obj=r22,tbl=r23,i=r24,owner=r25,st=r26,mb=r27,cursor=r28,id2=r29. My site 1 matches
  target site 1 exactly with the same source -> divergence at 2/3 is allocator history;
  the only earlier difference left is the missing counter web. Hypothesis: solving the
  counter cascades sites 2/3 into place. Do not permute decls for sites 2/3 before the
  counter is solved.
- CarObject_Init 98.18% / ItemEffect_SelectAndDispatch 99.38% = known cosmetic artifacts.

## Required TU edits for the appendix C (reverted with the worktree, reapply on retry)

- extern retypes: lbl_806D26F8 / 2704 / 2708 / 270C / 2710 / 2714 -> `extern const float`
  (lbl_806D2700 is already const float).
- KartMovementSpeedView: append `char pad_0x2fc[0x4]; float field300; /* 0x300 */` after
  mueScale2f8 (additive, safe for existing users).
- forward decl: `asm void CarObject_HandleItemEffect(void);` ->
  `int CarObject_HandleItemEffect(ItemSecondaryLane *self, int itemId);`
- Tables typed via casts at use (shared open-array extern decls untouched):
  lbl_802ED94C = 19 int pairs, lbl_803F75D0 = 13 s16.
- No configure.py / splits.txt / symbols.txt changes (TU-internal promote; the
  `-use_lmw_stmw on` already on the Object line is sufficient).

## Appendix: best-attempt C (98.62%, paste-ready; replaces the asm body, helper goes right above the fn)

```c
/* Shared lane-clear helper, same body as KartItem_CancelActiveEffect but
 * taking the secondary-lane view; inlined at three switch sites below.
 * Decl order tuned for the inline-site callee-saved assignment. */
#pragma inline_max_size(1024)
static inline int KartItem_CancelLanes_inl(ItemSecondaryLane *sec) {
    int itemId;
    ItemLaneCursor *cursor;
    void *mediaReq;
    void *effectState;
    KartItemOpsView *owner;
    unsigned int i;
    ItemEffectTable *tbl;
    KartItemOpsView *obj;
    ItemStateBlock *q;

    obj = sec->owner;
    q = obj->stateBlock;
    q->activeId = -1;
    q->activeFlag = i = 0;
    tbl = obj->effectTable;
    cursor = (ItemLaneCursor *)tbl;
    for (; i < 2; i++) {
        itemId = cursor->itemId;
        mediaReq = tbl->mediaReq;
        effectState = tbl->effectState;
        owner = tbl->owner;
        if (itemId >= 0) {
            TornadoEffect_ApplyItemVisual_Primary(owner->effectObj, itemId);
            KartItemAudio_StopSEByItemId(owner->soundCtrl, itemId);
            ItemEffectBus_ApplyItemEventClear(owner->ownerDriver->itemBus, itemId);
            EffectState_ReleaseAndClear(effectState);
            MediaBoard_SendAndCheck(mediaReq);
            ShadowBillboard_SetField0xA4(owner->billboard, lbl_806D26EC);
            cursor->itemId = -1;
            cursor->itemKind = -1;
            cursor->state8 = 0;
            cursor->stateC = 0;
            cursor->state10 = 0;
            cursor->blend = lbl_806D26FC;
        }
        cursor = (ItemLaneCursor *)((char *)cursor + 0x18);
    }
    tbl->run14 = 0;
    tbl->run1c = 0;
    tbl->runBlend20 = lbl_806D26EC;
    tbl->runBlend24 = lbl_806D26EC;
    ItemEffectBus_ClearMask(obj->ownerDriver->itemBus, 0xFFFFFFFFFFFFFFFFULL);
    SoundObj_PlaySE_Direct(obj->soundCtrl, 0x64);
    return 1;
}

#pragma exceptions off
int CarObject_HandleItemEffect(ItemSecondaryLane *self, int itemId) { /* 0x8004F858 size:0x7B8 */
    unsigned char found;
    int i;
    const int *p;
    unsigned char found2;
    const short *p2;
    int n;
    int ev;
    unsigned char m;
    unsigned char handled;

    found = 0;
    i = 0;
    p = (const int *)lbl_802ED94C;
    for (n = 0; n < 0x13; n++) {
        if (itemId == *p) {
            found = 1;
            break;
        }
        if (itemId == *++p) {
            found = 1;
            break;
        }
        ++p;
        ++i; /* dead counter: target keeps li r4,0 + addi r4,r4,1; CW DCEs this web in every probed form */
    }
    if (found == 0) {
        return 0;
    }
    if (ItemStateGuard_IsActive(self->owner->stateBlock->guard) == 1) {
        return 1;
    }
    p2 = (const short *)lbl_803F75D0;
    found2 = 0;
    for (n = 0; n < 0xd; n++) {
        if (itemId == *p2) {
            found2 = 1;
            break;
        }
        ++p2;
    }
    ev = self->owner->effectTable->run18;
    if (ev == 0x98) {
        m = 1;
    } else if (ev == 0x92) {
        m = 1;
    } else {
        m = 0;
    }
    if (m == 1 && found2 == 0) {
        return 1;
    }
    handled = 1;
    if (self->itemId >= 0) {
        if (self->itemId >= 0) {
            TornadoEffect_ApplyItemVisual_Primary(self->owner->effectObj, self->itemId);
            KartItemAudio_StopSEByItemId(self->owner->soundCtrl, self->itemId);
            ItemEffectBus_ApplyItemEventClear(self->owner->ownerDriver->itemBus, self->itemId);
            self->itemId = -1;
            self->blend = lbl_806D26EC;
        }
    }
    self->blend = lbl_806D26EC;
    switch (itemId) {
    case 0x17:
        handled = CarObject_ApplyDriftBoost(self->owner, lbl_806D26F0, 5);
        break;
    case 0xe:
    case 0x10:
    case 0x15:
    case 0x16:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x24:
    case 0x28:
        self->blend = lbl_806D26F8;
        handled = KartItem_CancelLanes_inl(self);
        break;
    case 0xc:
    case 0xd:
    case 0xf:
    case 0x11:
    case 0x13:
    case 0x14:
    case 0x18:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x8b:
    case 0x91:
        self->blend = lbl_806D2700;
        handled = KartItem_CancelLanes_inl(self);
        break;
    case 0x19:
        self->blend = lbl_806D2704;
        self->owner->movement->field300 = lbl_806D2708;
        break;
    case 0x141:
        KartItem_CancelLanes_inl(self);
        handled = CarObject_ApplyDriftBoost(self->owner, lbl_806D26F0, 6);
        break;
    case 0x1b:
        self->blend = lbl_806D2704;
        break;
    case 0x1a:
        self->blend = lbl_806D2704;
        break;
    case 0x142:
        handled = CarObject_ApplyDriftBoost(self->owner, lbl_806D26F0, 6);
        break;
    case 0x21:
        self->blend = lbl_806D270C;
        break;
    case 0x1c:
        self->blend = lbl_806D2704;
        break;
    case 0x1d:
        self->blend = lbl_806D270C;
        break;
    case 0x23:
        self->blend = lbl_806D270C;
        break;
    case 0x22:
        self->blend = lbl_806D2710;
        break;
    case 0x52:
        self->blend = lbl_806D2714;
        break;
    case 0x99:
        self->blend = lbl_806D2714;
        break;
    case 0x9a:
        self->blend = lbl_806D2714;
        break;
    case 0x8c:
        self->blend = lbl_806D270C;
        break;
    case 0x9d:
        self->blend = lbl_806D2714;
        break;
    case 0x9b:
        self->blend = lbl_806D2714;
        break;
    default:
        return 0;
    }
    if (handled == 0) {
        return 1;
    }
    self->itemId = itemId;
    TornadoEffect_ApplyItemVisual_Compact(self->owner->effectObj, self->itemId, 1);
    KartItemAudio_PlayThrowConfirmSE(self->owner->soundCtrl, self->itemId);
    ItemEffectBus_ApplyItemConfirm(self->owner->ownerDriver->itemBus, self->itemId);
    return 2;
}
#pragma exceptions reset
```
