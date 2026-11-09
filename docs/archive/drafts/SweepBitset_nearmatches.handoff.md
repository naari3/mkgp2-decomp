# HANDOFF batch_promote_80051dec_sweepbitset

14 contiguous fns 0x80051DEC..0x80052508 in the auto_ONKARTHIT mega-bundle TU.
5 matched, 9 stay asm_fn (3 parked near-match + 6 adjustor thunks).

```json
{
  "batch_id": "batch_promote_80051dec_sweepbitset",
  "sub_summary": "5 matched (dtor_80052200, Bitset_TestBit/SetBit/MaxSize, dtor_800524CC); sweep parked 98.95% (callee-saved 6-web permutation), CarObjectManager_Dtor parked 99.76% (1 scratch-reg tie-break), Bitset_Init parked 81% (approach-B EH-pinned-web class); 6 adjustor thunks structurally unpromotable (no tail-call b from C)",
  "results": [
    {
      "addr": "0x80051DEC",
      "name": "CarObjectManager_RunKartKartCollisionSweep",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "parked at 98.95% after 5 probes; all 219 instrs content-identical, residue = 6-web callee-saved permutation (target bp2=r31 cfg=r30 na=r29 nb=r28 sent=r27 i=r26 vs CW cfg=r31 i=r30 bp2=r29 na=r28 nb=r27 sent=r26). cfg/i pinned across decl orders AND block scoping = allocator-internal intrinsic ranking (ProcessWarpAndDash family). Plus r12 vcall chain temp (CW picks r5) and one stw r4-vs-r23 copy pick. 98.95% C in appendix A; win idioms in docs_notes"
    },
    {
      "addr": "0x80052158",
      "name": "CarObjectManager_Dtor",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "parked at 99.76% after 4 probes; ONLY diff is end-value temp reg (target r7, CW r0, 2 instrs). Triple addic. guard chain REPRODUCED by nested static inline list-dtor helpers each re-guarding if(l) - new positive idiom vs WarpDashMgr_Cleanup dedup failure. 99.76% C in appendix B"
    },
    {
      "addr": "0x80052200",
      "name": "dtor_80052200",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "Bitset deleting dtor, first build; if (self) { if (self->data) free; if (flag > 0) free(self); } return self"
    },
    {
      "addr": "0x8005225C",
      "name": "Bitset_TestBit",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "first build; return ((1 << (idx & 0x1f)) & self->data[idx >> 5]) != 0; mask-first AND order, u8 return needs no clrlwi after the neg/or/srwi != materialization"
    },
    {
      "addr": "0x80052288",
      "name": "Bitset_SetBit",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "2 probes; w = idx >> 5 local must be declared BEFORE mask local so srwi lands between li r0,1 and slw (w->r6); decl order mask-first gives w=r0 + post-slw schedule"
    },
    {
      "addr": "0x800522D0",
      "name": "Bitset_Init",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "parked at 81% after 2 probes (both produced identical output): approach-B exceptions-off class. Structure fully decoded (throw length_error inline, 3 dead vtable stores DO survive plain C, cap math, CW auto-8x-unrolled word fill reproduced). Blockers: exception-object this/str webs (target r28/r27 + stmw r27) remat to sp-addi with exceptions off; param webs flip n=r31/pval=r30. 81% C in appendix C"
    },
    {
      "addr": "0x80052494",
      "name": "Bitset_MaxSize",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "return 0xFFFFFFFF; first build"
    },
    {
      "addr": "0x8005249C",
      "name": "fn_8005249C",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "adjustor thunk (subi r3,0xc; b KartItem_Dtor). 1 C probe confirms CW 1.3.2 emits bl + full prologue/epilogue (no sibling tail call) - structurally unpromotable from C; same verdict applies to the 5 sibling thunks below (identical 2-instr shape, not probed individually)"
    },
    {
      "addr": "0x800524A4",
      "name": "KartItem_TryDropCoinsAndPlaySE_AdjThunk",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "adjustor thunk class, see fn_8005249C"
    },
    {
      "addr": "0x800524AC",
      "name": "fn_800524AC",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "adjustor thunk class, see fn_8005249C"
    },
    {
      "addr": "0x800524B4",
      "name": "fn_800524B4",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "adjustor thunk class, see fn_8005249C"
    },
    {
      "addr": "0x800524BC",
      "name": "KartItem_PlayHitSE_DifferentVictim_AdjThunk",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "adjustor thunk class, see fn_8005249C"
    },
    {
      "addr": "0x800524C4",
      "name": "KartItem_ApplyEffectToVictim_AdjThunk",
      "status": "asm_fn",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "adjustor thunk class, see fn_8005249C"
    },
    {
      "addr": "0x800524CC",
      "name": "dtor_800524CC",
      "status": "matched",
      "src_path": "game/auto_ONKARTHIT_block.c",
      "objdiff_percent": 100.0,
      "notes": "first build; if (self) { if (flag > 0) free(self); } return self; (short flag, extsh.)"
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
    "rename": []
  },
  "docs_notes": [
    {
      "path": "docs/notes/cw132-sweepbitset-batch-idioms.md",
      "content": "# SweepBitset batch idioms (2026-06-10, batch_promote_80051dec_sweepbitset)\n\nMatched in src/game/auto_ONKARTHIT_block.c (commit d02557e): dtor_80052200, Bitset_TestBit, Bitset_SetBit, Bitset_MaxSize, dtor_800524CC.\n\nWin idioms:\n\n1. volatile-field proxy pair (NEW, answer to the inlined vector<bool>::reference dead ctor stores): typedef struct { Bitset * volatile b; volatile unsigned long i; } BitsetRef; + per-site ref.b = p; ref.i = idx; immediately before the direct Bitset_SetBit(p, idx, v) call reproduces the dead {ptr,idx} stack-pair stores the original C++ proxy ctor leaves behind. Plain struct stores (even read back through a static inline that forwards them into the call) are fully DSE'd. The volatile stores read the HOME register; one target site stores the latch-scheduled arg copy (stw r4) instead - 1-instr residue, no C lever found (a plain copy local gets copy-propagated).\n2. Triple addic. r0,rX,0x4; beq guard chain (CarObjectManager_Dtor) REPRODUCES from nested static inline list-dtor helpers each re-guarding if (l) on the member-pointer param: dtor->clear->erase 3 levels deep, inlined to 3 recomputed addic. tests. Contrast WarpDashMgr_Cleanup (sec 14.2) where literal same-variable if (x) if (x) was deduped - passing the address through an inline PARAMETER at each level defeats the dedup.\n3. Bitset_SetBit decl-order: the word-index local (w = idx >> 5) must be declared BEFORE the mask local; then srwi schedules between li r0,1 and slw while r0/r5 are busy -> w=r6 (target). mask-first decl gives w=r0 emitted after slw.\n4. fn_802D6618 scratch out-vec is float[4] not Vec3 (slot layout: 0x74/0x4c with 4-byte tails at 0x80/0x58 in the sweep frame).\n5. Vec3 fill statement order (extends effectsrun idiom 5): half = cfg->half; half.x/y/z = K*scr[i]; center = cfg->center; center.x/y/z = mt[12..14]; (copy then fill per vec) locks products to f3/f2/f0 with K=f4 and keeps the dead 12-byte blob copies in target store order. Interleaving the two copies first (copyA, copyB, fillA, fillB) shifts the whole fp pool (f5/f4) and store schedule.\n6. Adjustor thunks (subi r3; b target) are not expressible in C: CW 1.3.2 never emits sibling tail calls, probe gives stwu/mflr + bl + epilogue. Keep as asm_fn permanently.\n7. In-place asm signature retype scales further: Bitset_Init / KartItem_Dtor / StlList_EraseRange retyped so promoted C can call them, bodies untouched, all stay 100%.\n\nHard-block instances (existing families, new data points):\n- CarObjectManager_RunKartKartCollisionSweep 98.95%: 6-web callee-saved PERMUTATION with two webs (cfg = blob base ptr, i = outer counter) PINNED to r31/r30 across all decl orders and block scoping; remaining 4 webs follow decl order descending below them. Allocator intrinsic ranking not controllable from source (ProcessWarpAndDash family). Routing deep-site &bs refs through the cached ptr does NOT remat (CW keeps mr from the callee-saved) - made it worse (96%).\n- CarObjectManager_Dtor 99.76%: single scratch-web tie-break (end-iterator value target r7 vs CW r0). beg-first assignment order or comma-arg materialization churns the whole schedule (89%); end-first always picks r0.\n- Bitset_Init 81%: approach-B exceptions-off class (HandleObstacleHit family). The original -Cpp_exceptions on compile pins the exception object pointer webs (r28=&e, r27=&e.str, stmw r27); with #pragma exceptions off CW remats both to sp-relative addi and drops to stw r28-r31 saves. ep->vt vs e.vt spelling makes zero difference (identical output both probes). Unlockable only by TU-level approach-A switch (impossible here: manual-extab asm fns precede it in address order, sec 14.1 mix rule)."
    }
  ],
  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 5
  },
  "blocked_reason": null,
  "user_attention": null
}
```

## Appendix A: CarObjectManager_RunKartKartCollisionSweep 98.95% paste-ready C

Supporting decls already present in the TU (kept): Bitset, StlList, StlListNode body,
CarObjectManager, SweepCarObj/SweepCarObjVt, CollProbe, BitsetRef (volatile fields),
SweepCfgView; externs retyped: g_carObjectCount int, g_objCollChecker void*,
lbl_806D2704/2714/27AC/27B0 float, CollisionTest_CalcPenetration float-ret,
fn_802090F0 prototyped, Alloc(unsigned long) void*.

Residue: cfg->r31/i->r30 (want r30/r26), bp2 r29 (want r31), na/nb/sent off-by-one,
vcall vt temp r5 (want r12), site1 i-store reads r23 home (want the r4 latch copy).

```c
#pragma exceptions off
void CarObjectManager_RunKartKartCollisionSweep(CarObjectManager *self) { /* 0x80051DEC size:0x36C */
    CollProbe objA;                 /* 0x148 */
    CollProbe objB;                 /* 0xf0 */
    float mtxA[12];                 /* 0xc0 */
    float mtxB[12];                 /* 0x90 */
    Bitset bs;                      /* 0x84 */
    float scrA[4];                  /* 0x74: fn_802D6618 writes 4 floats */
    Vec3 halfA;                     /* 0x68 */
    Vec3 centerA;                   /* 0x5c */
    float scrB[4];                  /* 0x4c */
    Vec3 halfB;                     /* 0x40 */
    Vec3 centerB;                   /* 0x34 */
    BitsetRef ref1;                 /* 0x2c */
    BitsetRef ref2;                 /* 0x24 */
    BitsetRef ref3;                 /* 0x1c */
    BitsetRef ref4;                 /* 0x14 */
    BitsetRef ref5;                 /* 0xc */
    unsigned char flagFalse;        /* 0x8 */
    SweepCfgView *cfg = (SweepCfgView *)lbl_802EBA18;  /* r30 */
    int k;                          /* r23 first loop counter */
    Bitset *bp;                     /* r25, dies after first loop */
    unsigned long n;                /* count temp for Bitset_Init */

    self->frame = self->frame + 1;
    if (self->frame < g_carObjectCount) {
        return;
    }
    self->frame = 0;
    flagFalse = 0;
    n = self->list.count;
    bs.cap = 0;
    bs.size = 0;
    bs.data = 0;
    Bitset_Init(&bs, n, &flagFalse);
    bp = &bs;
    for (k = 0; k < self->list.count; k++) {
        ref1.b = bp;
        ref1.i = k;
        Bitset_SetBit(bp, k, 0);
    }
    {
    Bitset *bp2;                    /* r31 */
    StlListNode *na;                /* r29 */
    StlListNode *nb;                /* r28 */
    StlListNode *sent;              /* r27 */
    int i;                          /* r26 */
    int j;                          /* r25 second web */
    float *mt;                      /* r23 second web */
    na = self->list.tail;
    sent = (StlListNode *)&self->list.head;
    bp2 = &bs;
    i = 0;
    while (na != sent) {
        ref2.b = bp2;
        ref2.i = i;
        nb = self->list.tail;
        if (!Bitset_TestBit(bp2, i)) {
            j = 0;
            fn_802091BC(&objA, -1, 0);
            mt = (float *)((char *)na->obj->body28 + 0x58);
            Mtx4x4_TransposeTo4x3(mt, mtxA);
            fn_802D6618(mtxA, scrA);
            halfA = cfg->halfA;
            halfA.x = lbl_806D27AC * scrA[0];
            halfA.y = lbl_806D27AC * scrA[1];
            halfA.z = lbl_806D27AC * scrA[2];
            centerA = cfg->centerA;
            centerA.x = mt[12];
            centerA.y = mt[13];
            centerA.z = mt[14];
            fn_802090F0(&objA, &centerA, &halfA, lbl_806D2704, lbl_806D27B0, lbl_806D2714);
            while (nb != sent) {
                if (i != j) {
                    ref3.i = j;
                    ref3.b = &bs;
                    if (!Bitset_TestBit(&bs, j)) {
                        fn_802091BC(&objB, -1, 0);
                        mt = (float *)((char *)nb->obj->body28 + 0x58);
                        Mtx4x4_TransposeTo4x3(mt, mtxB);
                        fn_802D6618(mtxB, scrB);
                        halfB = cfg->halfB;
                        halfB.x = lbl_806D27AC * scrB[0];
                        halfB.y = lbl_806D27AC * scrB[1];
                        halfB.z = lbl_806D27AC * scrB[2];
                        centerB = cfg->centerB;
                        centerB.x = mt[12];
                        centerB.y = mt[13];
                        centerB.z = mt[14];
                        fn_802090F0(&objB, &centerB, &halfB, lbl_806D2704, lbl_806D27B0, lbl_806D2714);
                        if (g_objCollChecker) {
                            if (CollisionTest_CalcPenetration(g_objCollChecker, &objA, &objB) > lbl_806D26EC) {
                                na->obj->vt->onKartCollide(na->obj, nb->obj->coll2c);
                                nb->obj->vt->onKartCollide(nb->obj, na->obj->coll2c);
                                ref4.i = i;
                                ref4.b = &bs;
                                Bitset_SetBit(&bs, i, 1);
                                ref5.i = j;
                                ref5.b = &bs;
                                Bitset_SetBit(&bs, j, 1);
                                dtor_80209180(&objB, -1);
                                break;
                            }
                        }
                        dtor_80209180(&objB, -1);
                    }
                }
                nb = nb->next;
                j++;
            }
            dtor_80209180(&objA, -1);
        }
        na = na->next;
        i++;
    }
    }
    if (bs.data) {
        MemoryManager_TimedFree(bs.data);
    }
}
#pragma exceptions reset
```

## Appendix B: CarObjectManager_Dtor 99.76% paste-ready C

Residue: 2 instrs, end-value temp addi r7, r30, 0x8 / stw r7, 0x10(r1) - CW picks r0.
Decl order ret/beg/end gives the exact slot layout (first declared = lowest, inline-body locals).

```c
/* inlined std-list dtor chain: each inline level re-guards its `this` */
static inline void StlList_EraseAllInner(StlList *l) {
    if (l) {
        void *ret;            /* 0x8 */
        StlListNode *beg;     /* 0xc */
        StlListNode *end;     /* 0x10 */
        end = (StlListNode *)&l->head;
        beg = l->tail;
        StlList_EraseRange(&ret, l, &beg, &end);
    }
}

static inline void StlList_ClearInline(StlList *l) {
    if (l) { StlList_EraseAllInner(l); }
}

static inline void StlList_DtorInline(StlList *l) {
    if (l) { StlList_ClearInline(l); }
}

#pragma exceptions off
CarObjectManager *CarObjectManager_Dtor(CarObjectManager *self, short flag) { /* 0x80052158 */
    if (self) {
        self->vtable = lbl_803F76A8;
        StlList_DtorInline(&self->list);
        if (self) {
            self->vtable = lbl_803F7690;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
```

## Appendix C: Bitset_Init 81% paste-ready C

Identical output with e.vt or ep->vt spelling. Needs BitsetLengthErr {unsigned int *vt; char *str;}
(present in TU) + retyped strlen/FUN_8003b120/Alloc (present). Blockers in JSON notes.

```c
#pragma exceptions off
void Bitset_Init(Bitset *self, unsigned long n, const unsigned char *pval) { /* 0x800522D0 */
    if (n > Bitset_MaxSize()) {
        /* throw length_error(...) inline expansion */
        BitsetLengthErr e;
        BitsetLengthErr *ep = &e;
        char **sp = &ep->str;
        e.vt = lbl_803F5710;
        e.vt = lbl_803F5700;
        SharedPtr_Init(sp, FUN_8003b120(strlen((const char *)lbl_802EDA80) + 1));
        fn_802791BC(*sp, (const char *)lbl_802EDA80);
        e.vt = lbl_803F56F0;
        fn_80271EF4(lbl_802EDAA4, ep, ClStrPcb_Dtor);
    }
    if (n != 0) {
        unsigned long ones = 0xFFFFFFFF;
        unsigned long fill;
        unsigned long i;
        self->size = n;
        self->cap = (n + 0x20) - (((n - 1) & 0x1f) + 1);
        n = ((self->cap - 1) >> 5) + 1;
        self->data = (unsigned long *)Alloc(n << 2);
        fill = *pval ? ones : 0;
        for (i = 0; i < n; i++) {
            self->data[i] = fill;
        }
    }
}
#pragma exceptions reset
```
