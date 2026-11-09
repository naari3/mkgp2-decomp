# HANDOFF batch_promote_8004d404_mainupdate

## Result: skipped (82.05% reached; blocked on a NEW hard-block flavor: CW1.3.2 loop strength-reduction coalescing)

CarObject_MainUpdate (0x8004D404, 0xAC8, real extab w/ dtor refs -> approach B mandatory)
was taken from asm to 82.05% / 690-instr C. Control flow, calls, u64 flag tests, switch
dispatches, the 16-float copies, sqrtf inline, cross product (incl. the frsp re-round webs),
and the quat->matrix algebra all reproduce. The residual is dominated by ONE loop.

### Hard-block: 4x4 matrix-multiply loop SR coalescing (0x8004DA44..0x8004DC58, ~150 instrs)

Target loop keeps THREE separate induction webs per iteration:
- r26 = row pointer into s.mA (const offsets 0x0..0x1c, advanced 0x20/iter)
- r5  = out index k, kept as INTEGER, stores via `slwi r0,k,2` + `stfsx f8,r6,r0`
  (r6 = &s.mOut materialized once in preheader), k+1..k+3 as addi temps in r3
- r4  = dead loop counter i (`mr r4,r5` init + `addi r4,r4,1`), CTR does termination

CW 1.3.2 instead COALESCES every source form I tried into a single SR pointer based at
&s (or two pointers r3/r4 = s + k*4), emitting `stfs f0,0x34(r3)` / `lfs f1,0xb8(r4)`
shapes and reassociating the first fmuls operand pair. Forms tried (all 5 identical result):
1. `float *pa = s.mA;` + `s.mOut[k]` member stores + `for (i=0;i<2;i++)` + `pa += 8`
2. same + `pa = s.mA;` reset before the final call
3. `s.mA[k+m]` / `s.mA[j+m]` fully-indexed (separate j/k indices)
4. per-iteration `float *row = &s.mA[j];`
5. `do {...} while (i < 2);` with manual i/k/pa updates, and additionally `float *out = s.mOut;`

The coalescing also poisons downstream register allocation (ev/slot2 land r26 vs target r27,
expired lands r7 vs r6, u64 zero-web not CSE'd with expired, copy-back batches 16-wide with
f30/f31 vs target 8+8 with f0-f7), so most of the remaining 18% is knock-on from this loop.

Hypotheses NOT yet tried: compiler patch revision; writing the loop body as an inline
function taking (float *out, const float *a, const float *b, int k); two explicit loop
nests; #pragma opt_* toggles around the loop.

### Secondary unresolved (small, mostly blocked behind the loop cascade)

- &s.mA CSE shared web: `pa` init + final `fn_8019A6A4(self->movement, s.mA)` both fold to
  r1+0xc0 -> CW makes a shared callee-saved web (addi r30 + mr r26 + mr r4,r30); target
  rematerializes (addi r26 early + addi r4 at call). WarpAndDash interior-member class;
  mA cannot move to struct offset 0 (stack layout fixed: mA must sit at sp+0xc0 = s+0xb4).
  Value-based CSE confirmed: `&s.mB[16]` spelling did NOT defeat it.
- Wrap-result dispatch: target `cmpwi r3,0; beq A; blt END; b END`. Single-case switch gives
  beq/b (no blt); adding `case -1: break;` gives beq/bge/b (wrong polarity); `case 1: break;`
  gives a 6-instr binary search; if/else + break/break forms get folded to bne. blt polarity unsolved.
- case-1 zero web f0 vs f1 (4 instrs).
- u64 bool diamond at 0x8004DCAC: target `bne L1; mr r0,r6; b L2; L1: li r0,1` - the
  `hit = expired` false-arm gets const-propagated (expired provably 0) and coalesced into the
  mask-zero web in my builds; expected to re-align if expired lands r6 (cascade from loop regs).

### Verified idioms discovered this batch (do NOT rediscover)

1. asm precan: NO class-1 (the 0x8004DCAC bool diamond has `mr r0,r6` real code on
   fall-through), NO class-2 (copies have no frsp interleave). approach-B regalloc class did
   not manifest in the matched regions.
2. `extra_cflags=["-use_lmw_stmw on"]` on the Object line is REQUIRED for `stmw r26` and is
   harmless to the 5 already-promoted C fns (all have 0x10 frames, no multi-GPR saves) -
   verified via full-TU objdiff: only CarObject_MainUpdate differs.
3. Helper fns must be `static inline` (plain `static` gets emitted: +0x70 .text AND a stray
   auto extab/extabindex pair @12/@13 that shifts the whole extab section by 4 -> global dol
   +4 relocation cascade starting at file offset 0x12F).
4. MSL sqrtf inline (volatile float y; __frsqrte + 3 NR steps; consts via
   `extern const double lbl_806D2720 (0.5) / lbl_806D2728 (3.0)`) reproduces the target
   frsqrte block + store/reload at sp+0x8 byte-exact.
5. frsp re-round (store-forward family): plain `(float)expr` casts on known-single values are
   ELIDED by CW; `(float)(double)expr` FORCES the frsp. This reproduced target's double-frsp
   webs: `frsp f29,f1` (store web) + `frsp f27,f29` (arith web) for q.w, and the
   `frsp f3,f7 / frsp f11,f6` webs for the up-vector operands of the cross product.
6. quat->mtx block: MUST use explicit product locals (xx,yy,zz,xy,wz,xz,wy,yz,wx) so
   -fp_contract cannot fuse the products into fmadds; with locals CW emits the target
   fmuls + fadds/fsubs + `1-2*(...)` fnmsubs contraction shape (instruction content matched,
   register permutation remains pending the loop cascade).
7. GPR decl-order swap: declaring `obj` BEFORE `id` in the guard block flipped id->r26 /
   obj->r27 to match target (note: empirically FIRST-declared got the HIGHER number here).
8. fp callee-saved order: declare + assign az,ay,ax (z first) -> f29,f30,f31 matching target.
9. switch lowering shapes confirmed: 3-case switch in source order {1,2,0}+default reproduces
   the binary dispatch exactly; single-case switch = beq/b pair (matches the itemId 0x9b site).
10. Single escaping scratch struct (escape via s.mA passed to fn_8019A6A4) preserves ALL dead
   stores: axis (0,1,0) init, up vector, mB 16-zero + 4-diag-one double-stores. Layout that
   lands members at target addresses (s @ sp+0xc): qx,qy,qz,qw; axis[3]; colY[3]; up[3];
   mOut[16]; mB[16]; mA[16]. Declare s FIRST among locals.
11. Saturate_Double has float (not double) ABI here: `extern float Saturate_Double(float,float,float)`
   (bl then direct stfs f1, no frsp). ItemEffectBus_Or/ClearMask take a u64 mask in r5:r6
   (`(void *bus, unsigned long long mask)`); masks are 0x0080... / 0x0040... ULL (<<48).
12. u64 flag test codegen is mechanical: `(bus->flags & C) == 0` emits and/and/xor/xor/or.
   even with zero halves (no folding) - write the masks as ULL constants.

The full 82% C (view structs + fn body, paste-ready) is in the appendix below. Worktree was
restored with git checkout (TU + configure.py) and full `ninja build/GNLJ82/ok` is green.

```json
{
  "batch_id": "batch_promote_8004d404_mainupdate",
  "sub_summary": "CarObject_MainUpdate promote: skipped at 82.05% - new hard-block flavor: CW1.3.2 strength-reduction COALESCES the 4x4 matrix-multiply loop inductions into a single &s-base pointer for every source form tried (5 forms), while target keeps separate k-index (slwi/stfsx) + row-pointer (r26) + dead i counter webs; ~150-instr loop accounts for the bulk of the residual plus register-allocation knock-on",

  "results": [
    {
      "addr": "0x8004D404",
      "name": "CarObject_MainUpdate",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 82.05% (690 instrs). Hard-block: loop SR coalescing at 0x8004DA44..0x8004DC58 (mtx multiply); 5 source forms tried (for+pa, pa reset, fully-indexed k/j, per-iter row ptr, do-while manual counters + out ptr) all collapse to s-base pointer addressing. Secondary: &s.mA interior-member CSE web (WarpAndDash class, offset-0 placement impossible since mA is fixed at s+0xb4), Wrap-dispatch blt polarity, register cascades. Everything else verified matching: prologue/frame 0x170 w/ f27-f31 + stmw r26 (needs -use_lmw_stmw on), u64 flag tests, switch dispatches, 16-float copies, sqrtf inline, cross product frsp webs via (float)(double), quat->mtx product-locals form. Paste-ready 82% C + 12 verified idioms in HANDOFF body. No class-1/class-2 precan blocks present."
    }
  ],

  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "set_attr": [], "rename": [] },

  "docs_notes": [],

  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },

  "blocked_reason": "CW 1.3.2 loop strength-reduction coalescing: target 4x4 mtx-multiply loop keeps 3 separate induction webs (integer k via slwi+stfsx, mA row pointer r26 with const offsets, dead i counter); CW collapses all tried source forms into a single &s-base SR pointer addressing, ~150 instr divergence + downstream regalloc cascade. 82.05%, all other regions reproduce.",
  "user_attention": null
}
```

## Appendix: best-attempt C (82.05%) - paste-ready for retry

Also required (already verified):
- configure.py: Object(Matching, "game/auto_ONKARTHIT_block.c", extab_padding=..., extra_cflags=["-use_lmw_stmw on"])
- extern retypes (in-TU): EffectSpeed_TickAndGet -> float(void*); Saturate_Double -> float(float,float,float);
  ItemStateGuard_IsActive / ItemStateGuard_PruneIfDeadAndReport / InputCmd_GetDetectedFlag / fn_8019A8A4 -> unsigned char returns;
  ItemEffectBus_OrMask/ClearMask -> (void*, unsigned long long); KartAudioChannel_PlayColorMatchSE -> (void*,int,float,int);
  TireEffect_ResetSpin -> (void*,float,float); InputCmd_PushSample -> (void*,int,float,float,float);
  fn_8027E480 / fn_8027E9E8 -> double(double); GetInputManager -> void*(void); DebugPrintf -> (const char*,...);
  SoundObj_PlaySE -> (void*,int)
- const retypes: lbl_806D26E4/26EC/26FC/2730/2744/27A8 -> extern const float; lbl_806D2720/2728/27A0 -> extern const double
- same-TU asm fn signature changes (decl + def headers): CarObject_ProcessWarpAndDash(void*),
  ItemEffect_SelectAndDispatch_Wrap -> asm int (void*,int,int,void*), KartItem_TickActiveEffectsTwoLane(void*),
  CarObject_UpdateCoinSpeedBonus(void*), KartItem_PerFrameStep(void*,void*), KartItem_Tick(void*),
  CarObjectManager_RunKartKartCollisionSweep(unsigned int)
- forward decl: void CarObject_MainUpdate(CarObjMainView *self, void *arg);

```c
/* --- struct views for CarObject_MainUpdate --- */
typedef struct ItemEffectBusView {
    char pad_0x0[0x10];
    unsigned long long flags;        /* 0x10 (u64) */
} ItemEffectBusView;

typedef struct KartDriverAuxView {
    char pad_0x0[0x2cc];
    int coinCount;                   /* 0x2cc */
    char pad_0x2d0[0x34];
    ItemEffectBusView *bus;          /* 0x304 */
} KartDriverAuxView;

typedef struct KartItemObjView {
    char pad_0x0[0x24];
    void *soundCtrl;                 /* 0x24 */
    char pad_0x28[0x4];
    KartDriverAuxView *driver;       /* 0x2c */
    char pad_0x30[0x4];
    void *kartBody;                  /* 0x34 */
    void *billboard;                 /* 0x38 */
} KartItemObjView;

typedef struct CarObjGuardView {
    KartItemObjView *obj;            /* 0x0 */
    void *composite;                 /* 0x4 */
    int itemId;                      /* 0x8 */
    int param0c;                     /* 0xc */
    void *param10;                   /* 0x10 */
} CarObjGuardView;

typedef struct CarObjSlotView {
    KartItemObjView *obj;            /* 0x0 */
    char pad_0x4[0x4];
    int itemId;                      /* 0x8 */
    float timer;                     /* 0xc */
} CarObjSlotView;

typedef struct KartItemEventView {
    char pad_0x0[0x18];
    int eventId;                     /* 0x18 */
    char pad_0x1c[0xc];
    int hasObjField;                 /* 0x28 */
    char pad_0x2c[0xc];
    void *eventObj;                  /* 0x38 */
} KartItemEventView;

typedef struct KartMovementMtxView {
    char pad_0x0[0x98];
    float mtx[16];                   /* 0x98 */
} KartMovementMtxView;

typedef struct CarObjMainView {
    char pad_0x0[0x10];
    int kartSlot;                    /* 0x10 */
    char pad_0x14[0xc];
    unsigned char isPlayer;          /* 0x20 */
    char pad_0x21[0x3];
    void *soundCtrl;                 /* 0x24 */
    KartMovementMtxView *movement;   /* 0x28 */
    KartDriverAuxView *renderObj;    /* 0x2c */
    void *inputCmd;                  /* 0x30 */
    void *kartBody;                  /* 0x34 */
    char pad_0x38[0x8];
    CarObjGuardView *guard;          /* 0x40 */
    void *effSpeedA;                 /* 0x44 */
    void *effSpeedB;                 /* 0x48 */
    KartItemEventView *kartItem;     /* 0x4c */
    CarObjSlotView *slot;            /* 0x50 */
    char pad_0x54[0x48];
    float spd0;                      /* 0x9c */
    float spd1;                      /* 0xa0 */
    float spd2;                      /* 0xa4 */
    unsigned char gateA8;            /* 0xa8 */
    char pad_0xa9[0x7];
    unsigned char flagB0;            /* 0xb0 */
    char pad_0xb1[0xf];
    int timerC0;                     /* 0xc0 */
    int timerC4;                     /* 0xc4 */
    int coinCount;                   /* 0xc8 */
    char pad_0xcc[0x4];
    int timerD0;                     /* 0xd0 */
} CarObjMainView;

/* single escaping scratch struct: all float locals of CarObject_MainUpdate
 * live here so dead stores survive DSE (s.mA escapes via fn_8019A6A4). */
typedef struct MainUpdateScratch {
    float qx, qy, qz, qw;            /* sp+0xc quaternion */
    float axis[3];                   /* sp+0x1c */
    float colY[3];                   /* sp+0x28 */
    float up[3];                     /* sp+0x34 */
    float mOut[16];                  /* sp+0x40 */
    float mB[16];                    /* sp+0x80 */
    float mA[16];                    /* sp+0xc0 */
} MainUpdateScratch;

/* MSL-style inline sqrtf (frsqrte + 3 NR steps, volatile store-reload). */
static inline float MainUpdate_sqrtf(float x) {
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
void CarObject_MainUpdate(CarObjMainView *self, void *arg) { /* 0x8004D404 size:0xAC8 */
    MainUpdateScratch s;
    ItemEffectBusView *bus;
    CarObjGuardView *guard;
    int state;

    bus = self->renderObj->bus;
    ItemEffectBus_SnapshotAndFullReset(bus);
    CarObject_ProcessWarpAndDash(self);
    if (self->coinCount < self->renderObj->coinCount) {
        TornadoEffect_TriggerFlagD2WithTimer(self->kartBody);
    }
    self->coinCount = self->renderObj->coinCount;
    self->spd0 = EffectSpeed_TickAndGet(self->effSpeedA);
    self->spd0 = Saturate_Double(self->spd0, lbl_806D26E4, lbl_806D26FC);
    EffectSpeed_TickTimer(self->effSpeedB);
    if (self->timerD0 > 0 || ItemStateGuard_IsActive(self->guard->composite) == 1) {
        if (self->timerD0 > 0) {
            self->timerD0--;
        }
        ItemEffectBus_OrMask(bus, 0x0080000000000000ULL);
    } else {
        ItemEffectBus_ClearMask(bus, 0x0080000000000000ULL);
    }
    if (self->timerC4 > 0) {
        self->timerC4--;
        ItemEffectBus_OrMask(bus, 0x0040000000000000ULL);
    } else {
        ItemEffectBus_ClearMask(bus, 0x0040000000000000ULL);
    }
    if (self->timerC0 > 0) {
        self->timerC0--;
    }
    guard = self->guard;
    if (guard->itemId < 0) {
        state = 0;
    } else if (ItemStateGuard_PruneIfDeadAndReport(guard->composite) == 0) {
        ShadowBillboard_SetField0x6CAndComputeAxis(guard->obj->billboard, 0);
        {
            KartItemObjView *obj;
            int id = guard->itemId;
            if (id >= 0) {
                obj = guard->obj;
                TornadoEffect_ApplyItemVisual_Primary(obj->kartBody, id);
                KartItemAudio_StopSEByItemId(obj->soundCtrl, id);
                ItemEffectBus_ApplyItemEventClear(obj->driver->bus, id);
                guard->itemId = -1;
            }
        }
        state = 2;
    } else {
        state = 1;
    }
    switch (state) {
    case 1:
        self->spd0 = lbl_806D26EC;
        self->spd1 = lbl_806D26EC;
        self->spd2 = lbl_806D26EC;
        MediaBoard_PollCompletion(self->soundCtrl);
        KartAudioChannel_PlayColorMatchSE(self->soundCtrl, 0, lbl_806D26EC, 0);
        TornadoEffect_SetColorPairC8CC(self->kartBody, 0, 0);
        TireEffect_ResetSpin(self->kartBody, lbl_806D26EC, lbl_806D26EC);
        self->timerD0 = 0x2d;
        break;
    case 2: {
        switch (ItemEffect_SelectAndDispatch_Wrap(self->kartItem, self->guard->param0c, 0, self->guard->param10)) {
        case 0: {
            KartItemEventView *it;
            int ev;
            unsigned char hasObj;
            CarObjSlotView *sl2;
            self->flagB0 = 0;
            it = self->kartItem;
            ev = it->eventId;
            hasObj = it->hasObjField >= 0;
            ItemEffectBus_ApplyItemEventSet(bus, ev, (hasObj == 1) ? it->eventObj : 0);
            TornadoEffect_ApplyItemVisual_Secondary(self->kartBody, ev, 1);
            KartItemAudio_PlayHitConfirmSE(self->soundCtrl, ev);
            sl2 = self->slot;
            if (sl2->itemId >= 0) {
                TornadoEffect_ApplyItemVisual_Primary(sl2->obj->kartBody, sl2->itemId);
                KartItemAudio_StopSEByItemId(sl2->obj->soundCtrl, sl2->itemId);
                ItemEffectBus_ApplyItemEventClear(sl2->obj->driver->bus, sl2->itemId);
                sl2->itemId = -1;
                sl2->timer = lbl_806D26EC;
            }
            break;
        }
        }
        break;
    }
    case 0: {
        KartMovementMtxView *m = self->movement;
        s.mA[0] = m->mtx[0];
        s.mA[1] = m->mtx[1];
        s.mA[2] = m->mtx[2];
        s.mA[3] = m->mtx[3];
        s.mA[4] = m->mtx[4];
        s.mA[5] = m->mtx[5];
        s.mA[6] = m->mtx[6];
        s.mA[7] = m->mtx[7];
        s.mA[8] = m->mtx[8];
        s.mA[9] = m->mtx[9];
        s.mA[10] = m->mtx[10];
        s.mA[11] = m->mtx[11];
        s.mA[12] = m->mtx[12];
        s.mA[13] = m->mtx[13];
        s.mA[14] = m->mtx[14];
        s.mA[15] = m->mtx[15];
        if (s.mA[5] < (float)fn_8027E480(lbl_806D27A0)) {
            float mag;
            float sinv;
            float az, ay, ax;
            float x, y, z, w2;
            float xx, yy, zz, xy, wz, xz, wy, yz, wx;
            float *pa;
            float *out;
            int k;
            int i;

            s.axis[0] = lbl_806D26EC;
            s.axis[1] = lbl_806D26FC;
            s.axis[2] = lbl_806D26EC;
            s.colY[0] = s.mA[4];
            s.colY[1] = s.mA[5];
            s.colY[2] = s.mA[6];
            s.up[0] = lbl_806D26EC;
            s.up[1] = lbl_806D26FC;
            s.up[2] = lbl_806D26EC;
            s.axis[0] = s.colY[1] * (float)(double)s.up[2] - s.colY[2] * (float)(double)s.up[1];
            s.axis[1] = s.colY[2] * (float)(double)s.up[0] - s.colY[0] * (float)(double)s.up[2];
            s.axis[2] = s.colY[0] * (float)(double)s.up[1] - s.colY[1] * (float)(double)s.up[0];
            mag = MainUpdate_sqrtf(s.axis[2] * s.axis[2] + (s.axis[0] * s.axis[0] + s.axis[1] * s.axis[1]));
            if (mag <= lbl_806D26EC) {
                s.axis[0] = s.axis[1] = s.axis[2] = lbl_806D26EC;
            } else {
                float inv = lbl_806D26FC / mag;
                s.axis[0] = s.axis[0] * inv;
                s.axis[1] = s.axis[1] * inv;
                s.axis[2] = s.axis[2] * inv;
            }
            s.qx = s.qy = s.qz = s.qw = lbl_806D26EC;
            az = s.axis[2];
            ay = s.axis[1];
            ax = s.axis[0];
            sinv = (float)fn_8027E9E8(lbl_806D27A8);
            s.qx = ax * sinv;
            s.qy = ay * sinv;
            s.qz = az * sinv;
            s.qw = (float)fn_8027E480(lbl_806D27A8);
            x = s.qx;
            y = s.qy;
            z = s.qz;
            w2 = (float)(double)s.qw;
            xx = x * x;
            yy = y * y;
            zz = z * z;
            xy = x * y;
            wz = w2 * z;
            xz = x * z;
            wy = w2 * y;
            yz = y * z;
            wx = w2 * x;
            s.mB[0] = lbl_806D26EC;
            s.mB[1] = lbl_806D26EC;
            s.mB[2] = lbl_806D26EC;
            s.mB[3] = lbl_806D26EC;
            s.mB[4] = lbl_806D26EC;
            s.mB[5] = lbl_806D26EC;
            s.mB[6] = lbl_806D26EC;
            s.mB[7] = lbl_806D26EC;
            s.mB[8] = lbl_806D26EC;
            s.mB[9] = lbl_806D26EC;
            s.mB[10] = lbl_806D26EC;
            s.mB[11] = lbl_806D26EC;
            s.mB[12] = lbl_806D26EC;
            s.mB[13] = lbl_806D26EC;
            s.mB[14] = lbl_806D26EC;
            s.mB[15] = lbl_806D26EC;
            s.mB[0] = lbl_806D26FC;
            s.mB[5] = lbl_806D26FC;
            s.mB[10] = lbl_806D26FC;
            s.mB[15] = lbl_806D26FC;
            s.mB[0] = lbl_806D26FC - lbl_806D2744 * (yy + zz);
            s.mB[4] = lbl_806D2744 * (xy - wz);
            s.mB[8] = lbl_806D2744 * (xz + wy);
            s.mB[1] = lbl_806D2744 * (xy + wz);
            s.mB[5] = lbl_806D26FC - lbl_806D2744 * (xx + zz);
            s.mB[9] = lbl_806D2744 * (yz - wx);
            s.mB[2] = lbl_806D2744 * (xz - wy);
            s.mB[6] = lbl_806D2744 * (yz + wx);
            s.mB[10] = lbl_806D26FC - lbl_806D2744 * (xx + yy);
            k = 0;
            i = 0;
            pa = s.mA;
            out = s.mOut;
            do {
                out[k] = pa[0] * s.mB[0] + pa[1] * s.mB[4] + pa[2] * s.mB[8] + pa[3] * s.mB[12];
                out[k + 1] = pa[0] * s.mB[1] + pa[1] * s.mB[5] + pa[2] * s.mB[9] + pa[3] * s.mB[13];
                out[k + 2] = pa[0] * s.mB[2] + pa[1] * s.mB[6] + pa[2] * s.mB[10] + pa[3] * s.mB[14];
                out[k + 3] = pa[0] * s.mB[3] + pa[1] * s.mB[7] + pa[2] * s.mB[11] + pa[3] * s.mB[15];
                k += 4;
                out[k] = pa[4] * s.mB[0] + pa[5] * s.mB[4] + pa[6] * s.mB[8] + pa[7] * s.mB[12];
                out[k + 1] = pa[4] * s.mB[1] + pa[5] * s.mB[5] + pa[6] * s.mB[9] + pa[7] * s.mB[13];
                out[k + 2] = pa[4] * s.mB[2] + pa[5] * s.mB[6] + pa[6] * s.mB[10] + pa[7] * s.mB[14];
                out[k + 3] = pa[4] * s.mB[3] + pa[5] * s.mB[7] + pa[6] * s.mB[11] + pa[7] * s.mB[15];
                k += 4;
                pa += 8;
                i += 1;
            } while (i < 2);
            s.mA[0] = s.mOut[0];
            s.mA[1] = s.mOut[1];
            s.mA[2] = s.mOut[2];
            s.mA[3] = s.mOut[3];
            s.mA[4] = s.mOut[4];
            s.mA[5] = s.mOut[5];
            s.mA[6] = s.mOut[6];
            s.mA[7] = s.mOut[7];
            s.mA[8] = s.mOut[8];
            s.mA[9] = s.mOut[9];
            s.mA[10] = s.mOut[10];
            s.mA[11] = s.mOut[11];
            s.mA[12] = s.mOut[12];
            s.mA[13] = s.mOut[13];
            s.mA[14] = s.mOut[14];
            s.mA[15] = s.mOut[15];
            fn_8019A6A4(self->movement, s.mA);
        }
        break;
    }
    default:
        DebugPrintf((char *)lbl_802EDA20);
        break;
    }
    KartItem_TickActiveEffectsTwoLane(self->kartItem);
    {
        CarObjSlotView *slot = self->slot;
        if (slot->itemId >= 0) {
            unsigned char expired = 0;
            int id;
            slot->timer = slot->timer - lbl_806D2730;
            id = slot->itemId;
            switch (id) {
            case 0x9b: {
                unsigned char hit;
                if ((slot->obj->driver->bus->flags & 0x0400000000000000ULL) == 0) {
                    hit = expired;
                } else {
                    hit = 1;
                }
                if (hit == 1) {
                    expired = 1;
                }
                break;
            }
            }
            if (slot->timer < lbl_806D26EC || expired == 1) {
                if (id >= 0) {
                    TornadoEffect_ApplyItemVisual_Primary(slot->obj->kartBody, id);
                    KartItemAudio_StopSEByItemId(slot->obj->soundCtrl, slot->itemId);
                    ItemEffectBus_ApplyItemEventClear(slot->obj->driver->bus, slot->itemId);
                    slot->itemId = -1;
                    slot->timer = lbl_806D26EC;
                }
            }
        }
    }
    CarObject_UpdateCoinSpeedBonus(self);
    InputCmd_PushSample(self->inputCmd, 0, self->spd0, self->spd1, self->spd2);
    InputCmd_TickAndDetectAndClear(self->inputCmd);
    if (self->gateA8 == 1) {
        if (InputCmd_GetDetectedFlag(self->inputCmd) == 1) {
            if ((self->renderObj->bus->flags & 0x0000000000800000ULL) == 0) {
                SoundObj_PlaySE(self->soundCtrl, 1);
                if (fn_8019A8A4(self->movement, lbl_806D26FC) != 0) {
                    unsigned int t = lbl_806D10A0;
                    if (t != lbl_806D10A0) {
                    } else if (t == 0) {
                        t = 0;
                    }
                    if (t != 0) {
                        TitleStats_IncTotalRaces(t, self->kartSlot);
                    }
                    SoundObj_PlaySE_Direct(self->soundCtrl, 0x56);
                    SetAnimSpin(self->renderObj);
                    TornadoEffect_SetFlagC0(self->kartBody);
                    self->flagB0 = 1;
                }
            } else if (self->isPlayer != 0) {
                SoundObj_PlaySE_Direct(self->soundCtrl, 0x9e);
            }
        }
    }
    KartItem_PerFrameStep(self, arg);
    KartItem_Tick(self);
    InputMgr_GetPlayer(GetInputManager(), 0);
    {
        unsigned int mgr = g_carObjectList;
        if (mgr != g_carObjectList) {
        } else if (mgr == 0) {
            mgr = 0;
        }
        CarObjectManager_RunKartKartCollisionSweep(mgr);
    }
    ItemEffectBus_TickTornadoCooldown(bus);
}
#pragma exceptions reset
```
