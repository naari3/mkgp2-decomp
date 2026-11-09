# HANDOFF batch_promote_phase1_class1batch4

KartItem_PerFrameStep 0x8004C320 (0xC44, TU max fn): **97.87% park** (805 instrs content-complete; residue = fp/GPR scratch register PERMUTATION only). Worktree restored to asm body, `ninja build/GNLJ82/ok` green (SHA-1 OK). Paste-ready 97.87% C in Appendix A.

## Class-1 recipe verification (REQUIRED REPORT)

Site 0x8004C8CC: u64 family, mask `0x10000000ULL`, hi half = 0 (bool coalesces into the `li r4,0` mask-hi register). Recipe (plain if/else form over direct `bus->flags`):

```c
unsigned char b;
if ((self->ownerDriver->itemBus->flags & 0x10000000ULL) == 0) { b = 0; } else { b = 1; }
if (b == 1) { SoundObj_PlaySE_Direct(self->soundCtrl, 0xc6); }
```

**byte-exact from build 1 and in every subsequent build** (and/and/xor/xor/or.; bne L1; b L2; L1: li r4,1; L2: clrlwi/cmplwi/bne - register-for-register incl. the r4 zero-web coalesce). No CSE complication (each flag test reloads the bus pointer; the adjacent direct test at 0x8004C5DC uses mask 0x30000000ULL on a separate load). **Recipe ledger now 14/14 u64-family sites across 4 batches.** Shape precan: NOT the int-equality-chain variant.

## Fresh precan (full fn, all classes)

- class-1: 1 site (above), u64 family. SOLVED in-fn.
- class 2 frsp store-forward: **absent**. All 3 frsp are reachable idioms: 2x in-place sqrtf store-reload (sp+0xc / sp+0x8) + 1x `(float)__fabs`.
- dead-counter ctr loop / flavor-5 multi-induction SR loop: none (no mtctr/bdnz at all).
- ScopedTimer subi 0x217d: none. EH FP-prologue / `bl __unexpected`: none. symbol+const table-walk reassociation: none.
- extab: real extab with `&dtor_80036E40` refs -> approach B mandatory (#pragma exceptions off + keep manual emit). Used; no extab issues in any build.
- Features that all MATCHED: duplicated 30-label binary-search switch x2 (case 0x22 body first, then the 29-label group body; guard `if (sl->itemId >= 0)` supplies the leading blt), GetInstance condition-assign folds x3, zero-blocks x2, coin clamp (`n = c - 1; if (n < 0) n = 0;`), fwdSpeed dot in f31 via fmadds fuse-first-addend, fctiwz conversion temp at sp+0xe0, the entire tail (ComposeRenderMatrix/Transpose + 4 joint calls + 2 TickAction calls + arg eval-order via `drv = self->ownerDriver;` reassignments), prologue/epilogue & frame 0x110, in-place sqrtf x2, cross product + (float)__fabs.

## Park reason (hard-block family)

Residue = **fp scratch web NUMBERING permutation** (ItemEffect_Explosion / UpdateBoostVisualBlend family, sec 14.2 "later-first-use -> lower reg"): target numbers simultaneously-live scratch webs DESCENDING from the top of the free pool (16-float copy t0=f7..t7=f0; na-block velX=f4/zero=f3 with zero defined later; cross-product cluster), while CW 1.3.2 assigns ASCENDING by def order in every probed source form. Probes (all negative on the direction): decl-order flip x2 (block / fn scope), def-order (assignment) reorder (changes emission order, NOT numbering), all-volatile-free restructure (escaping low-scratch struct; numbering unchanged -> volatile presence is NOT the lever), struct-wrap of the copy array (registerized f29-f31). Knock-on: ~50 of the 91 residue rows are pure register renames in 3 fp regions + 2 small scheduling artifacts (prologue mr r31/r30 pair order + addi r4 churn; pos word-copy r3/r5 pair + arg-load interleave).

## New verified idioms (propagated via docs_notes)

1. **CW 1.3.2 stack layout rule**: locals sorted by SIZE DESCENDING, allocated top-down; ties by decl order (first declared = higher address). To put small scalars at the frame bottom, SPLIT aggregates so sizes ascend toward sp (a single 0x58 scratch struct can never sit below 0x40 arrays).
2. **CW 1.3.2 does NOT hoist pointer loads above stack stores** (may-alias, flow-insensitive): target patterns that look scheduler-pipelined must be written in SOURCE order. Reproduced 3x: 16-float copy 8-deep pipeline via 8 named temps (load t0..t7, then alternate m[i]=ti / ti=mtx[8+i], then 8 stores); mode lbz into a temp before the copy stores; vb/na/nb load-temps before member stores.
3. **Array registerization matrix**: plain local array with 3/16 elements read across a call -> copy deleted, values kept in f29-f31; struct-wrap WITHOUT address-take does NOT stop it (SROA of array members); volatile array -> memory but strictly serialized lfs/stfs pairs; ESCAPING-struct member array -> pinned + source-pipelinable.
4. **volatile uint pair for cross-call int snapshots** reproduces target lwz r5/lwz r0 + stw 0x14/stw 0x10 exactly (non-volatile struct members serialize through r0; plain locals take r29).
5. **volatile Vec3 + cast-stripped struct copy** (`G.pos = *(Vec3 *)&v304;`) blocks whole-object copy-propagation while keeping the canonical 3-word lwz/stw copy.
6. **Escaping Vec3-group struct umbrella**: &G.scaled passed once pins all 5 Vec3 members - dead y-overwrite stores survive, vb not propagated, register forwarding intact (the `G.na.y*G.na.y` term reads the 0.0 const register -> separate fmuls, no fmadds).
7. **30-label binary-search switch** fully deterministic from the case set; source case-body order = memory order (0x22 first). Duplicated switch = duplicated source.

## Files in worktree tmp/ (not committed)

- tmp/pfs_appendix.c - paste-ready 97.87% C (types + fn)
- tmp/pfs_97pct.diff - full TU diff of the 97.87% state (incl. extern retypes)
- tmp/sxs_97pct_final.txt / tmp/residue_97pct.txt - side-by-side + 91 residue rows
- tmp/pfs_asm.txt - target asm extraction

## Required TU-side edits for retry (beyond the appendix types/fn)

- decl: `asm void KartItem_PerFrameStep(void);` -> `void KartItem_PerFrameStep(PfsKartView *self, void *arg);`
- extern retypes: IsRaceStarted / KartItem_Stub_Returns0 -> unsigned char; TornadoEffect_GetField114 / fn_8019A850 -> float; lbl_806D270C/2710/2748/2774/277C/2780 -> extern const float (all 6 currently unsigned int, referenced only from asm bodies -> safe).
- StrPcb_SetTimer3034_38 existing prototype `(void*, int, int, float)` works for both call shapes.

```json
{
  "batch_id": "batch_promote_phase1_class1batch4",
  "sub_summary": "KartItem_PerFrameStep (0xC44, TU max): 97.87% park. Class-1 site 0x8004C8CC (mask 0x10000000ULL) byte-exact via the ==0 arm-order recipe from build 1 - ledger 14/14. Fresh precan: NO class-2 / ctr / flavor-5 / ScopedTimer / EH blocks; all 3 frsp are known idioms; both 30-label switches, folds, zero blocks, tail all matched. Residue is the fp-scratch later-first-use->lower-reg numbering family (ItemEffect_Explosion class) in 3 fp regions + 2 tiny scheduling artifacts; 6 probe axes negative. New idioms: CW stack layout = size-desc top-down (tie: first-decl higher); CW never hoists loads over stack stores (target pipelined patterns are SOURCE patterns: 8-temp software-pipelined 16-float copy); array registerization/volatile/escape matrix.",
  "results": [
    {
      "addr": "0x8004C320",
      "name": "KartItem_PerFrameStep",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 97.87% (805 instrs, 91 residue rows, content-identical outside register permutation). 8 approach-level attempts. Hard-block: fp scratch web numbering (later-first-use->lower-reg, sec 14.2 ItemEffect_Explosion family) at the 16-float copy / na-nb normalize / cross-product regions + prologue param-mr pair order + pos word-copy reg pair. Class-1 recipe verified byte-exact at 0x8004C8CC. Paste-ready C + full TU diff + residue listing in HANDOFF appendix and worktree tmp/. Solving the numbering family self-corrects this fn (likely to ~100%) - bundle with ItemEffect_Explosion (88.99%) / KartMovement_UpdateBoostVisualBlend (98.88%) in any allocator-research batch."
    }
  ],
  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "set_attr": [], "rename": [] },
  "docs_notes": [
    {
      "path": "docs/notes/cw132-class1-batch4-verification.md",
      "content": "# Class-1 recipe: batch-4 verification (2026-06-11, batch_promote_phase1_class1batch4)\n\nKartItem_PerFrameStep 0x8004C320 site 0x8004C8CC: u64 family (mask 0x10000000ULL, hi=0), plain if/else recipe over direct bus->flags byte-exact from first build (register-for-register incl. r4 zero-web coalesce). Ledger: 14/14 u64-family sites across 4 batches. Fn itself parked at 97.87% on the fp-scratch later-first-use->lower-reg numbering family (NOT class-1; paste-ready C in HANDOFF batch_promote_phase1_class1batch4 appendix).\n\nNew verified idioms (full detail in the HANDOFF):\n1. CW132 stack layout rule: locals sorted size-DESCENDING allocated top-down, ties by decl order (first = higher). Split aggregates to put small scalars at the frame bottom.\n2. CW132 never hoists pointer loads above stack stores: target scheduler-looking patterns are SOURCE patterns. 16-float copy 8-deep pipeline reproduced with 8 named temps (t0..t7 load block, then m[i]=ti; ti=mtx[8+i] alternation, then 8 stores). Byte-exact except web numbering.\n3. Registerization matrix: plain local array w/ 3 of 16 elements read across a call -> copy deleted, f29-f31 keep values; struct-wrap without address-take does NOT stop SROA of array members; volatile array -> serialized lfs/stfs pairs; escaping-struct member array -> pinned + source-pipelinable.\n4. volatile unsigned int scalar pair = target cross-call int snapshot codegen (lwz r5/r0 batch + stw pair); non-volatile struct members serialize, plain locals take callee-saved.\n5. volatile Vec3 + cast-stripped struct copy (G.pos = *(Vec3*)&v) blocks whole-object copy-propagation while keeping the canonical word-copy.\n6. Escaping Vec3-group struct keeps dead y-overwrite stores AND register forwarding (separate fmuls for the zeroed-member square, no fmadds).\n7. 30-label binary-search switch deterministic; source case-body order = memory order.\n"
    }
  ],
  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },
  "blocked_reason": "fp scratch register NUMBERING permutation (later-first-use->lower-reg allocator family, docs sec 14.2 ItemEffect_Explosion): target numbers simultaneously-live scratch webs descending, CW 1.3.2 ascending-by-def-order in all probed forms (decl-order x2, def-reorder, volatile-free restructure, struct-wrap). 97.87%, everything else reproduces incl. the class-1 site.",
  "user_attention": null
}
```

## Appendix A: paste-ready 97.87% C (types + function)

Replace the asm body at the KartItem_PerFrameStep slot in src/game/auto_ONKARTHIT_block.c, insert the types before the forward-decls section, and apply the decl/retype edits listed above (or apply tmp/pfs_97pct.diff wholesale).

```c
/* --- views for KartItem_PerFrameStep (0x8004C320) --- */
typedef struct PfsMovementView {
    char pad_0x0[0x58];
    float mtx[16];              /* 0x58: transform matrix */
    float mtx98[16];            /* 0x98: render-source matrix */
    char pad_0xd8[0xa4];
    float velX;                 /* 0x17c */
    float velY;                 /* 0x180 */
    float velZ;                 /* 0x184 */
    char pad_0x188[0x50];
    float spin1d8;              /* 0x1d8 */
    char pad_0x1dc[0xc];
    float field1e8;             /* 0x1e8 */
    char pad_0x1ec[0x58];
    unsigned char gate244;      /* 0x244 */
    char pad_0x245[0x79];
    unsigned char gate2be;      /* 0x2be */
    char pad_0x2bf[0x5];
    unsigned int mode2c4;       /* 0x2c4 */
    unsigned int mode2c8;       /* 0x2c8 */
    char pad_0x2cc[0x4];
    unsigned char flag2d0;      /* 0x2d0 */
    char pad_0x2d1[0x2b];
    unsigned char flag2fc;      /* 0x2fc */
} PfsMovementView;

typedef struct PfsKartView {
    char pad_0x0[0x10];
    int raceScore10;            /* 0x10 */
    char pad_0x14[0xc];
    unsigned char strPcbGate20; /* 0x20 */
    char pad_0x21[0x3];
    void *soundCtrl;            /* 0x24 */
    PfsMovementView *movement;  /* 0x28 */
    KartDriverBusView *ownerDriver; /* 0x2c */
    char pad_0x30[0x4];
    void *effectObj;            /* 0x34 */
    char pad_0x38[0x4];
    void *boostObj;             /* 0x3c */
    char pad_0x40[0x10];
    ItemSecondaryLane *secondary; /* 0x50 */
    char pad_0x54[0xc];
    float xfrm60[12];           /* 0x60: transposed 4x3 out */
    float velSnapX;             /* 0x90 */
    float velSnapY;             /* 0x94 */
    float velSnapZ;             /* 0x98 */
    float spd0;                 /* 0x9c */
    float spd1;                 /* 0xa0 */
    float spd2;                 /* 0xa4 */
    unsigned char gateA8;       /* 0xa8 */
    char pad_0xa9[0x7];
    unsigned char boostArmedB0; /* 0xb0 */
    unsigned char perfectGateB1;/* 0xb1 */
    char pad_0xb2[0x2];
    float timerB4;              /* 0xb4 */
    char pad_0xb8[0x8];
    int timerC0;                /* 0xc0 */
    char pad_0xc4[0x4];
    int coinCountC8;            /* 0xc8 */
    char pad_0xcc[0x8];
    unsigned char physModeD4;   /* 0xd4 */
    char pad_0xd5[0xf];
    float decayE4;              /* 0xe4 */
    float depthE8;              /* 0xe8 */
    char pad_0xec[0xc];
    int slowTimerF8;            /* 0xf8 */
    char pad_0xfc[0x1];
    unsigned char coinPenaltyFD;/* 0xfd */
} PfsKartView;

/* Vec3 working group: one escaping struct (address escapes via &G.scaled
 * passed to KartItem_SetVec3At338) pins every member in memory - keeps the
 * dead y-overwrite stores in na/nb, keeps vb from being copy-propagated,
 * and keeps register forwarding of just-stored values (non-volatile). */
typedef struct PfsVecGroup {
    Vec3 nb;                    /* sp+0x24 */
    Vec3 na;                    /* sp+0x30 */
    Vec3 vb;                    /* sp+0x3c */
    Vec3 pos;                   /* sp+0x48 */
    Vec3 scaled;                /* sp+0x54 */
} PfsVecGroup;

/* combined matrix scratch: c (compose/transpose buffer) escapes via the
 * ComposeRenderMatrix call, which pins the whole struct in memory so the
 * 13 unread m[] copy slots survive (no registerization, no volatile
 * serialization of the 16-float copy schedule). Largest local -> top of
 * the frame (CW 1.3.2 sorts locals by size descending, fills top-down). */
typedef struct PfsMtxPair {
    float c[16];                /* sp+0x60 */
    float m[16];                /* sp+0xa0 */
} PfsMtxPair;

#pragma exceptions off
void KartItem_PerFrameStep(PfsKartView *self, void *arg) { /* 0x8004C320 size:0xC44 */
    PfsMtxPair mtxs;            /* sp+0x60..0xe0 */
    PfsVecGroup G;              /* sp+0x24..0x60 */
    volatile Vec3 v304;         /* sp+0x18: volatile blocks pos=v304 copy-propagation */
    volatile unsigned int modeA;/* sp+0x14: mov->mode2c4 snapshot */
    volatile unsigned int modeB;/* sp+0x10: mov->mode2c8 snapshot */
    volatile float sqA;         /* sp+0x0c: 1st in-place sqrtf slot */
    volatile float sqB;         /* sp+0x08: 2nd in-place sqrtf slot */
    KartDriverBusView *drv;
    ItemSecondaryLane *sl;
    void *t;
    float fwdSpeed;
    float t0, t1, t2, t3, t4, t5, t6, t7;

    G.scaled = *(Vec3 *)lbl_802ED9F4;
    G.scaled.x = lbl_806D2730 * self->movement->velX;
    G.scaled.y = lbl_806D2730 * self->movement->velY;
    G.scaled.z = lbl_806D2730 * self->movement->velZ;
    KartItem_SetVec3At338(self->ownerDriver, &G.scaled);

    {
        PfsMovementView *mv = self->movement;
        unsigned char mode;
        mode = self->physModeD4;
        t7 = mv->mtx[7];
        t6 = mv->mtx[6];
        t5 = mv->mtx[5];
        t4 = mv->mtx[4];
        t3 = mv->mtx[3];
        t2 = mv->mtx[2];
        t1 = mv->mtx[1];
        t0 = mv->mtx[0];
        mtxs.m[0] = t0;
        t0 = mv->mtx[8];
        mtxs.m[1] = t1;
        t1 = mv->mtx[9];
        mtxs.m[2] = t2;
        t2 = mv->mtx[10];
        mtxs.m[3] = t3;
        t3 = mv->mtx[11];
        mtxs.m[4] = t4;
        t4 = mv->mtx[12];
        mtxs.m[5] = t5;
        t5 = mv->mtx[13];
        mtxs.m[6] = t6;
        t6 = mv->mtx[14];
        mtxs.m[7] = t7;
        t7 = mv->mtx[15];
        mtxs.m[8] = t0;
        mtxs.m[9] = t1;
        mtxs.m[10] = t2;
        mtxs.m[11] = t3;
        mtxs.m[12] = t4;
        mtxs.m[13] = t5;
        mtxs.m[14] = t6;
        mtxs.m[15] = t7;
        if (mode == 1) {
            KartMovement_PhysicsStep(mv, self->spd0, self->spd1, self->spd2, self->gateA8);
        } else {
            fn_8019CC2C(mv);
        }
    }
    fwdSpeed = mtxs.m[4] * self->movement->mtx[4] + mtxs.m[5] * self->movement->mtx[5] + mtxs.m[6] * self->movement->mtx[6];
    if (self->slowTimerF8 > 0) {
        self->slowTimerF8--;
    }
    modeA = self->movement->mode2c4;
    modeB = self->movement->mode2c8;
    if (KartMovement_CalcSpeedWithCoinBonus(self->movement, 0) > lbl_806D26EC) {
        if (fwdSpeed < lbl_806D2774 || modeA == 4 || modeB == 4) {
            if (self->slowTimerF8 <= 0) {
                self->decayE4 = self->decayE4 * lbl_806D26E4;
                fwdSpeed = lbl_806D2778 * self->decayE4;
                if (self->strPcbGate20 != 0) {
                    StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 3, 3, fwdSpeed);
                }
                self->slowTimerF8 = 3;
            }
        }
    }
    if (self->movement->gate2be == 1) {
        if (self->boostArmedB0 == 1) {
            SoundObj_PlaySE_Direct(self->soundCtrl, 0x57);
            self->perfectGateB1 = 1;
            self->timerB4 = lbl_806D26EC;
            self->movement->flag2fc = 1;
            KartAudioChannel_Set24WithSeStop(self->soundCtrl, 1);
            TornadoEffect_SetFlagB4(self->effectObj, 1);
            TornadoEffect_SetField11c(self->effectObj, (self->spd0 < lbl_806D26EC) ? lbl_806D2710 : lbl_806D2748);
        } else if (IsRaceStarted() == 1) {
            SoundObj_PlaySE_Direct(self->soundCtrl, 0x57);
        }
        self->boostArmedB0 = 0;
    }
    if (self->movement->gate244 == 1) {
        if (self->timerC0 <= 0) {
            if ((self->ownerDriver->itemBus->flags & 0x30000000ULL) == 0) {
                CarObject_GetField304Vec3((Vec3 *)&v304, (CarObjAux304View *)self->movement);
                G.pos = *(Vec3 *)&v304;
                SoundObj_PlaySE(self->soundCtrl, 0x11);
                SoundObj_PlaySE_Direct(self->soundCtrl, 0x59);
                if (self->perfectGateB1 != 0) {
                    if (self->timerB4 >= lbl_806D270C) {
                        if ((t = lbl_806D10A0) == 0) {
                            t = 0;
                        }
                        if (t != 0) {
                            TitleStats_MarkAllCoursesClearedIfDistance(t, self->raceScore10);
                        }
                    }
                }
                self->perfectGateB1 = 0;
                self->timerB4 = lbl_806D26EC;
                self->movement->flag2d0 = 0;
                self->movement->flag2fc = 0;
                TornadoEffect_SetFlagB4(self->effectObj, 0);
                TornadoEffect_SetField11c(self->effectObj, lbl_806D26EC);
                ItemEffectBus_ClearMask(self->ownerDriver->itemBus, 0x40ULL);
                KartAudioChannel_Set24WithSeStop(self->soundCtrl, 0);
                sl = self->secondary;
                if (sl->itemId >= 0) {
                    switch (sl->itemId) {
                    case 0x22:
                        TornadoEffect_ApplyItemVisual_Compact(sl->owner->effectObj, sl->itemId, 1);
                        KartItemAudio_PlayThrowConfirmSE(sl->owner->soundCtrl, sl->itemId);
                        ItemEffectBus_ApplyItemConfirm(sl->owner->ownerDriver->itemBus, sl->itemId);
                        break;
                    case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11:
                    case 0x13: case 0x14: case 0x15: case 0x16:
                    case 0x18:
                    case 0x1e: case 0x1f: case 0x20:
                    case 0x24: case 0x25: case 0x26: case 0x27: case 0x28:
                    case 0xd5: case 0xd6:
                    case 0xdc:
                    case 0xe2:
                    case 0xe8:
                    case 0xee:
                    case 0xf4:
                    case 0xfa:
                    case 0x101:
                    case 0x107:
                        TornadoEffect_ApplyItemVisual_Compact(sl->owner->effectObj, sl->itemId, 1);
                        KartItemAudio_PlayThrowConfirmSE(sl->owner->soundCtrl, sl->itemId);
                        ItemEffectBus_ApplyItemConfirm(sl->owner->ownerDriver->itemBus, sl->itemId);
                        ItemEffectBus_SnapshotAndClearSpawnFlags(sl->owner->ownerDriver->itemBus);
                        break;
                    }
                }
                if (self->coinPenaltyFD != 0) {
                    if (self->raceScore10 != 4) {
                        CoinSystem_RemoveCoins(self->ownerDriver, 1);
                    } else {
                        int n = self->ownerDriver->coins2cc - 1;
                        if (n < 0) {
                            n = 0;
                        }
                        self->ownerDriver->coins2cc = n;
                    }
                    self->coinCountC8 = self->ownerDriver->coins2cc;
                }
                fn_801B1410(self->ownerDriver);
                if ((t = lbl_806D10A0) == 0) {
                    t = 0;
                }
                if (t != 0) {
                    RankLog_OnPlayerDefeated(t, self->raceScore10);
                }
                ItemEffectBus_RegisterBonkPosition(self->ownerDriver->itemBus, G.pos.x, G.pos.y, G.pos.z);
            }
            {
                unsigned char b;
                if ((self->ownerDriver->itemBus->flags & 0x10000000ULL) == 0) {
                    b = 0;
                } else {
                    b = 1;
                }
                if (b == 1) {
                    SoundObj_PlaySE_Direct(self->soundCtrl, 0xc6);
                }
            }
        }
        self->timerC0 = 0x1e;
    }
    if (self->perfectGateB1 == 1) {
        unsigned char flag;
        flag = 0;
        self->timerB4 = self->timerB4 + lbl_806D2730;
        {
            PfsMovementView *mv2 = self->movement;
            float vx, spin, vy, vz;
            spin = mv2->spin1d8;
            vz = mv2->mtx[10];
            vy = mv2->mtx[9];
            vx = mv2->mtx[8];
            G.vb.y = vy;
            G.vb.x = vx;
            G.vb.z = vz;
        if (spin >= lbl_806D273C) {
            flag = 1;
        } else {
            float zero, ax, ay, az, sq, inv;
            zero = lbl_806D26EC;
            ax = mv2->velX;
            ay = mv2->velY;
            az = mv2->velZ;
            G.na.x = ax;
            G.na.y = ay;
            G.na.z = az;
            G.na.y = zero;
            sq = G.na.z * G.na.z + (G.na.x * G.na.x + G.na.y * G.na.y);
            if (sq > zero) {
                double guess = __frsqrte(sq);
                guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
                guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
                guess = lbl_806D2720 * guess * (lbl_806D2728 - sq * (guess * guess));
                sqA = (float)(sq * guess);
                sq = sqA;
            }
            if (sq <= lbl_806D26EC) {
                G.na.x = G.na.y = G.na.z = lbl_806D26EC;
            } else {
                inv = lbl_806D26FC / sq;
                G.na.x = G.na.x * inv;
                G.na.y = G.na.y * inv;
                G.na.z = G.na.z * inv;
            }
            zero = lbl_806D26EC;
            ax = G.vb.x;
            ay = G.vb.y;
            az = G.vb.z;
            G.nb.x = ax;
            G.nb.y = ay;
            G.nb.z = az;
            G.nb.y = zero;
            sq = G.nb.z * G.nb.z + (G.nb.x * G.nb.x + G.nb.y * G.nb.y);
            if (sq > zero) {
                double guess2 = __frsqrte(sq);
                guess2 = lbl_806D2720 * guess2 * (lbl_806D2728 - sq * (guess2 * guess2));
                guess2 = lbl_806D2720 * guess2 * (lbl_806D2728 - sq * (guess2 * guess2));
                guess2 = lbl_806D2720 * guess2 * (lbl_806D2728 - sq * (guess2 * guess2));
                sqB = (float)(sq * guess2);
                sq = sqB;
            }
            if (sq <= lbl_806D26EC) {
                G.nb.x = G.nb.y = G.nb.z = lbl_806D26EC;
            } else {
                inv = lbl_806D26FC / sq;
                G.nb.x = G.nb.x * inv;
                G.nb.y = G.nb.y * inv;
                G.nb.z = G.nb.z * inv;
            }
            {
                float crX;
                float crY;
                float crZ;
                crX = G.nb.y * G.na.z - G.nb.z * G.na.y;
                crY = G.nb.z * G.na.x - G.nb.x * G.na.z;
                crZ = G.nb.x * G.na.y - G.nb.y * G.na.x;
                G.na.y = crY;
                G.na.x = crX;
                G.na.z = crZ;
                if ((float)__fabs(crZ + (crX + crY)) < lbl_806D277C) {
                    flag = 1;
                }
            }
        }
        }
        if (flag == 1) {
            if (KartItem_Stub_Returns0(self->boostObj, self->timerB4) == 1) {
                int t2 = (int)(lbl_806D2780 * self->timerB4 + lbl_806D2704);
                if (self->strPcbGate20 != 0) {
                    StrPcb_SetTimer3034_38(StrPcb_GetInstance(), t2, 3, lbl_806D26E4);
                }
            }
            if (self->perfectGateB1 != 0) {
                if (self->timerB4 >= lbl_806D270C) {
                    if ((t = lbl_806D10A0) == 0) {
                        t = 0;
                    }
                    if (t != 0) {
                        TitleStats_MarkAllCoursesClearedIfDistance(t, self->raceScore10);
                    }
                }
            }
            self->perfectGateB1 = 0;
            self->timerB4 = lbl_806D26EC;
            self->movement->flag2d0 = 0;
            self->movement->flag2fc = 0;
            TornadoEffect_SetFlagB4(self->effectObj, 0);
            TornadoEffect_SetField11c(self->effectObj, lbl_806D26EC);
            ItemEffectBus_ClearMask(self->ownerDriver->itemBus, 0x40ULL);
            KartAudioChannel_Set24WithSeStop(self->soundCtrl, 0);
            sl = self->secondary;
            if (sl->itemId >= 0) {
                switch (sl->itemId) {
                case 0x22:
                    TornadoEffect_ApplyItemVisual_Compact(sl->owner->effectObj, sl->itemId, 1);
                    KartItemAudio_PlayThrowConfirmSE(sl->owner->soundCtrl, sl->itemId);
                    ItemEffectBus_ApplyItemConfirm(sl->owner->ownerDriver->itemBus, sl->itemId);
                    break;
                case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11:
                case 0x13: case 0x14: case 0x15: case 0x16:
                case 0x18:
                case 0x1e: case 0x1f: case 0x20:
                case 0x24: case 0x25: case 0x26: case 0x27: case 0x28:
                case 0xd5: case 0xd6:
                case 0xdc:
                case 0xe2:
                case 0xe8:
                case 0xee:
                case 0xf4:
                case 0xfa:
                case 0x101:
                case 0x107:
                    TornadoEffect_ApplyItemVisual_Compact(sl->owner->effectObj, sl->itemId, 1);
                    KartItemAudio_PlayThrowConfirmSE(sl->owner->soundCtrl, sl->itemId);
                    ItemEffectBus_ApplyItemConfirm(sl->owner->ownerDriver->itemBus, sl->itemId);
                    ItemEffectBus_SnapshotAndClearSpawnFlags(sl->owner->ownerDriver->itemBus);
                    break;
                }
            }
        } else {
            if ((self->ownerDriver->itemBus->flags & 0x40ULL) == 0) {
                ItemEffectBus_OrMask(self->ownerDriver->itemBus, 0x40ULL);
                SoundObj_PlaySE(self->soundCtrl, 2);
            }
        }
    }
    {
        float px;
        float py;
        float pz;
        pz = self->movement->mtx[14];
        py = self->movement->mtx[13];
        px = self->movement->mtx[12];
        self->velSnapX = px;
        self->velSnapY = py;
        self->velSnapZ = pz;
    }
    TornadoEffect_SetField114(self->effectObj, self->movement->field1e8);
    TornadoEffect_ComposeRenderMatrix(self->effectObj, self->movement->mtx98, mtxs.c);
    Mtx4x4_TransposeTo4x3(mtxs.c, self->xfrm60);
    drv = self->ownerDriver;
    KartDriver_SetJointPosY_Slot3a(drv, -fn_8019A850(self->movement, 0));
    drv = self->ownerDriver;
    KartDriver_SetJointPosY_Slot3b(drv, -fn_8019A850(self->movement, 1));
    drv = self->ownerDriver;
    KartDriver_SetJointPosY_Slot3c(drv, -fn_8019A850(self->movement, 2));
    drv = self->ownerDriver;
    KartDriver_SetJointPosY_Slot3d(drv, -fn_8019A850(self->movement, 3));
    drv = self->ownerDriver;
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ(drv, TornadoEffect_GetField114(self->effectObj));
    drv = self->ownerDriver;
    KartDriver_TickAction_79260(drv, TornadoEffect_GetField114(self->effectObj));
    if (self->strPcbGate20 == 1) {
        fn_802C8B48(0);
    }
    RenderObj_ItemStateMachine_Timed(self->ownerDriver, arg, -self->depthE8, lbl_806D26EC);
    fn_802C8B48(1);
    KartEffectFadeTransit_Tick(self->boostObj);
}
#pragma exceptions reset
```

## Appendix B: 91-row residue (target | mine), 97.87% build

```
   9 | mr r31, r4                                   mr r30, r3
  11 | mr r30, r3                                   lfs f1, lbl_806D2730@sda21
  13 | addi r4, r1, 0x54                            addi r7, r1, 0x54
  15 | ---                                          mr r31, r4
  17 | ---                                          mr r4, r7
  19 | lfs f1, lbl_806D2730@sda21                   ---
  36 | lfs f7, 0x58(r3)                             lfs f11, 0x74(r3)
  37 | lfs f6, 0x5c(r3)                             lfs f10, 0x70(r3)
  39 | lfs f5, 0x60(r3)                             lfs f9, 0x6c(r3)
  40 | lfs f4, 0x64(r3)                             lfs f8, 0x68(r3)
  41 | lfs f3, 0x68(r3)                             lfs f3, 0x64(r3)
  42 | lfs f2, 0x6c(r3)                             lfs f2, 0x60(r3)
  43 | lfs f1, 0x70(r3)                             lfs f1, 0x5c(r3)
  44 | lfs f0, 0x74(r3)                             lfs f0, 0x58(r3)
  45 | stfs f7, 0xa0(r1)                            stfs f0, 0xa0(r1)
  47 | stfs f6, 0xa4(r1)                            stfs f1, 0xa4(r1)
  49 | stfs f5, 0xa8(r1)                            stfs f2, 0xa8(r1)
  51 | stfs f4, 0xac(r1)                            stfs f3, 0xac(r1)
  53 | stfs f3, 0xb0(r1)                            stfs f8, 0xb0(r1)
  55 | stfs f2, 0xb4(r1)                            stfs f9, 0xb4(r1)
  57 | stfs f1, 0xb8(r1)                            stfs f10, 0xb8(r1)
  59 | stfs f0, 0xbc(r1)                            stfs f11, 0xbc(r1)
 193 | lwz r3, 0x18(r1)                             lwz r5, 0x18(r1)
 195 | lwz r5, 0x1c(r1)                             lwz r3, 0x1c(r1)
 197 | stw r3, 0x48(r1)                             stw r5, 0x48(r1)
 198 | lwz r3, 0x24(r30)                            ---
 199 | stw r5, 0x4c(r1)                             stw r3, 0x4c(r1)
 201 | ---                                          lwz r3, 0x24(r30)
 399 | lfs f3, 0x80(r3)                             lfs f2, 0x80(r3)
 400 | ---                                          fcmpo cr0, f1, f0
 401 | lfs f2, 0x7c(r3)                             lfs f1, 0x78(r3)
 402 | fcmpo cr0, f1, f0                            ---
 403 | lfs f0, 0x78(r3)                             lfs f0, 0x7c(r3)
 404 | stfs f2, 0x40(r1)                            stfs f0, 0x40(r1)
 405 | stfs f0, 0x3c(r1)                            stfs f1, 0x3c(r1)
 406 | stfs f3, 0x44(r1)                            stfs f2, 0x44(r1)
 411 | lfs f4, 0x17c(r3)                            lfs f4, lbl_806D26EC@sda21
 412 | lfs f3, lbl_806D26EC@sda21                   lfs f3, 0x17c(r3)
 413 | fmuls f1, f4, f4                             fmuls f0, f4, f4
 415 | fmuls f0, f3, f3                             fmuls f1, f3, f3
 418 | stfs f4, 0x30(r1)                            stfs f5, 0x34(r1)
 420 | stfs f5, 0x34(r1)                            ---
 421 | stfs f6, 0x38(r1)                            stfs f3, 0x30(r1)
 422 | fadds f4, f2, f0                             fadds f5, f2, f0
 423 | stfs f3, 0x34(r1)                            stfs f6, 0x38(r1)
 424 | ---                                          stfs f4, 0x34(r1)
 425 | fcmpo cr0, f4, f3                            fcmpo cr0, f5, f4
 427 | frsqrte f1, f4                               frsqrte f1, f5
 432 | fnmsub f0, f4, f0, f2                        fnmsub f0, f5, f0, f2
 436 | fnmsub f0, f4, f0, f2                        fnmsub f0, f5, f0, f2
 440 | fnmsub f0, f4, f0, f2                        fnmsub f0, f5, f0, f2
 442 | fmul f0, f4, f0                              fmul f0, f5, f0
 445 | lfs f4, 0xc(r1)                              lfs f5, 0xc(r1)
 446 | lfs f0, lbl_806D26EC@sda21                   lfs f4, lbl_806D26EC@sda21
 447 | fcmpo cr0, f4, f0                            fcmpo cr0, f5, f4
 450 | stfs f0, 0x38(r1)                            stfs f4, 0x38(r1)
 451 | stfs f0, 0x34(r1)                            stfs f4, 0x34(r1)
 452 | stfs f0, 0x30(r1)                            stfs f4, 0x30(r1)
 456 | fdivs f3, f0, f4                             fdivs f3, f0, f5
 465 | lfs f4, 0x3c(r1)                             ---
 466 | lfs f3, lbl_806D26EC@sda21                   lfs f3, 0x3c(r1)
 467 | fmuls f1, f4, f4                             fmuls f0, f4, f4
 469 | fmuls f0, f3, f3                             fmuls f1, f3, f3
 472 | stfs f4, 0x24(r1)                            stfs f3, 0x24(r1)
 476 | fadds f4, f2, f0                             fadds f5, f2, f0
 477 | stfs f3, 0x28(r1)                            stfs f4, 0x28(r1)
 478 | fcmpo cr0, f4, f3                            fcmpo cr0, f5, f4
 480 | frsqrte f1, f4                               frsqrte f1, f5
 485 | fnmsub f0, f4, f0, f2                        fnmsub f0, f5, f0, f2
 489 | fnmsub f0, f4, f0, f2                        fnmsub f0, f5, f0, f2
 493 | fnmsub f0, f4, f0, f2                        fnmsub f0, f5, f0, f2
 495 | fmul f0, f4, f0                              fmul f0, f5, f0
 498 | lfs f4, 0x8(r1)                              lfs f5, 0x8(r1)
 500 | fcmpo cr0, f4, f0                            fcmpo cr0, f5, f0
 509 | fdivs f3, f0, f4                             fdivs f3, f0, f5
 518 | lfs f4, 0x38(r1)                             lfs f3, 0x38(r1)
 519 | lfs f8, 0x24(r1)                             lfs f7, 0x24(r1)
 521 | lfs f7, 0x34(r1)                             lfs f6, 0x34(r1)
 522 | fmuls f0, f8, f4                             fmuls f0, f7, f3
 523 | lfs f5, 0x30(r1)                             lfs f4, 0x30(r1)
 524 | lfs f6, 0x28(r1)                             lfs f5, 0x28(r1)
 525 | fmuls f2, f1, f7                             fmuls f2, f1, f6
 526 | fmsubs f3, f1, f5, f0                        fmsubs f8, f1, f4, f0
 528 | fmuls f1, f6, f5                             fmuls f1, f5, f4
 529 | fmsubs f4, f6, f4, f2                        fmsubs f2, f5, f3, f2
 530 | stfs f3, 0x34(r1)                            stfs f8, 0x34(r1)
 531 | fmsubs f2, f8, f7, f1                        fmsubs f3, f7, f6, f1
 532 | fadds f1, f4, f3                             fadds f1, f2, f8
 533 | stfs f4, 0x30(r1)                            stfs f2, 0x30(r1)
 534 | stfs f2, 0x38(r1)                            stfs f3, 0x38(r1)
 535 | fadds f1, f2, f1                             fadds f1, f3, f1
```
