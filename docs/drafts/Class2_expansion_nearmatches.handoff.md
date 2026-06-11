# HANDOFF batch_promote_class2_expansion

All 4 functions parked; TU restored to all-asm, `build/GNLJ82/ok` sha1 OK.
Best percentages, trial matrices and recipe findings: see `docs_notes` content and appendices below.

```json
{
  "batch_id": "batch_promote_class2_expansion",
  "sub_summary": "4 fns attempted in existing TU game/auto_ONKARTHIT_block.c; all parked (register-identity-only residue): OnKartHit 96.38%, Tick 98.83%, Trap 85.34%, Projectile 88.40%. Asm bodies restored, TU back at 100%, sha1 OK. Paste-ready bodies + header reapply diff in appendices; recipe knowledge in docs_notes.",
  "results": [
    {
      "addr": "0x8004A238",
      "name": "KartItem_OnKartHit",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 96.38% (134/422 rows) after 8 builds; residue: GPR callee-saved partition (locals-top vs params-bottom), callee-saved-bool li coalescing failure x4, vcall r6-vs-r12 x6, fp f3/f5 swap. Paste-ready C in Appendix B."
    },
    {
      "addr": "0x8004BAAC",
      "name": "KartItem_Tick",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 98.83% (65/542 rows) after 6 builds; residue: fp callee-saved partition family (velY<->0.0, velZ<->1.0 swaps, invariant across 4 probe shapes) + cascaded volatile fp numbering + 1 mr-vs-li pair. Paste-ready C in Appendix C."
    },
    {
      "addr": "0x80051834",
      "name": "ItemEffect_Trap",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 85.34% after 12 builds; escape-split recipe solved block 1; region-2 target batched 3-frsp+3-muls scheduling not reproduced across 5 probe shapes. Paste-ready C in Appendix D."
    },
    {
      "addr": "0x80051A70",
      "name": "ItemEffect_Projectile",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 88.40% (55/153 rows) after 6 builds; residue: &vecA addi hoist, eager per-component scheduling, fp naming mirror. Paste-ready C in Appendix E."
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
      "path": "docs/notes/cw132-class2-expansion.md",
      "content": "# CW1.3.2 class-2 / loop-copy recipe expansion (batch_promote_class2_expansion, 2026-06-10/11)\n\nBatch: KartItem_OnKartHit 0x8004A238, KartItem_Tick 0x8004BAAC, ItemEffect_Trap 0x80051834,\nItemEffect_Projectile 0x80051A70 (TU src/game/auto_ONKARTHIT_block.c, -use_lmw_stmw on).\nResult: 4/4 parked (96.38% / 98.83% / 85.34% / 88.40%), all residue register-identity or\ninstruction-selection-identity. Paste-ready bodies + reapply diff in the batch HANDOFF appendix.\n\n## Observations (facts, reproduced in builds)\n\n### Class-2 / struct copy mechanics\n- ESCAPE-SERIALIZATION (Trap): if any member address of a struct escapes via call arg\n  (s.vecA passed to ItemEffectDamp_TryArm), the backend serializes the same struct's\n  16-float loop copy into single-register lfs/stfs pairs. Splitting the escaping vec into a\n  separate struct object restores the parallel unrolled form.\n- Escape also blocks FE store-forwarding: read-backs of escaped-struct slots survive to the\n  late pass and become frsp; a fully non-escaped struct gets raw forwarding, and in one\n  Projectile probe its stores were entirely DSE'd.\n- `(float)(double)` cast forces frsp on a FORWARDED read-back, but is ELIDED on a direct\n  field load (Projectile build 4). Lever only works on forwarded values.\n- (Tick) A 16-float zero-fill loop + 4 diagonal const stores + 12 transpose stores all\n  survive (no same-slot DSE) and interleave by scheduler; plain `for (i=0;i<16;i++) s.m[i]=lbl;`\n  followed by straight-line overwrites reproduces the target store soup byte-pattern (only\n  callee-saved reg names differed; see partition family below).\n- 3-iteration loops FE-unroll with no class-2 disturbance; 16-iteration loops backend-unroll.\n\n### Control flow / locals recipes (new, verified in Tick build steps)\n- Join-variable coalescing: `spdJ = lbl; if (spd <= spdJ) { s.v[2]=spdJ; ... } else { spdJ = spd; ... }`\n  coalesces the join home with the compare-constant register: then-arm emits NOTHING\n  (stores reuse the const reg), else-arm emits exactly one `fmr`. Writing the const\n  assignment inside the then-arm instead produces an extra fmr.\n- Float call-result through a 4-way branch join: assign `vol = Saturate_Double(...)` in each\n  arm and call `SoundCtrl_SetVolume(snd, vol)` once after the join; vol stays in f1, no fmr.\n- Wrap-loop reload asymmetry: `while (x > 1.0f) x -= 1.0f;` target reloads the field in the\n  body (needs `self->f = VF(self->f) - lbl;` volatile read), while `while (x < 0.0f) x = lbl + x;`\n  target CSEs the check load into the body (plain spelling). Same field, opposite discipline.\n- GPR scratch/callee assignment follows LOCAL DECLARATION ORDER: declaring `int i2; int off;\n  KartMovementTickView *mv5;` then `SpeedTableEntry *e;` in an inner scope yielded the target\n  r4/r5/r6/r7 assignment; with `e` declared before `mv5` the two swapped. Strong, cheap lever.\n- Cap-up form `if (best >= K) { best = K; }` (then-assign, NO else) = fcmpo + cror ge + bne-skip\n  + fmr. The empty-then/else-assign form inverts the branch (beq) and does not match.\n- Named temp controls fmuls operand order: `float rr = a / b - c; f(rr * drift, ...)` puts rr\n  first (target); inlining `(a / b - c) * drift` got commuted to drift-first.\n- Hoisting `void *snd = self->soundCtrl;` before a call whose later arg contains another call\n  forces snd into a callee-saved reg before the inner call (target r30 pattern); passing\n  `self->soundCtrl` inline loads it AFTER the inner call (volatile reg) instead.\n- Empty-paren extern decls promote float args to double (K&R); typed prototypes are required\n  for any callee taking float in f1.. (e.g. KartAudioChannel_PlayColorMatchSE(void*,int,int,float)).\n- class-1 u64-flag recipe `if ((flags & MASK) == 0) { b = 0; } else { b = 1; }` reproduces the\n  bne/b/li-1 diamond with the li-0 arm coalescing into the mask-hi zero register, for bools that\n  live in VOLATILE regs (Tick 0x30ULL site matched). For callee-saved bools (OnKartHit b27/b28)\n  the coalescing FAILS: 4 extra li residue. Volatility of the bool is the precondition.\n- Cross-call product-only-callee-saved (mulli idx*stride kept callee-saved, lis/addi table base\n  rematerialized after the call) is what plain `tbl[idx].field` spelling produces NATURALLY.\n  The earlier hard-block classification of this pattern was wrong.\n- Volatile aux-pointer reload lever: `(*(View * volatile *)&drv->itemBus)->flags` forces the\n  pointer reload without disturbing the u64 field access.\n\n### fp callee-saved partition family (source-closed, new instance)\nTick entry has five long-range fp values: 0.0 const, velX, velY, velZ, 1.0 const.\nTarget: f31=0.0, f30=velX, f29=velY, f28=velZ, f13(volatile)=1.0 (= plain statement order).\nMine, across FOUR probe shapes (statement reorder; zero-loop before/after stores; named locals\nk0/vx/vyv/vz/k1; named k0 only + compare via k0; reads+squares moved before/after transpose):\nalways a pairwise swap velY<->0.0 and velZ<->1.0 (f31=velY, f29=0.0, f28=1.0, f13=velZ),\nwith velX=f30 a fixed point. Source-closed like the StlList GPR partition family; ~32 rows\n+ ~30 cascaded volatile-numbering rows. Cast-read values (ty/tx/tz read-back order) rank top\nin my builds; constants rank top in target.\n\n### Instruction-selection residue (source-closed in this batch)\n- `mr r5, r4` for `off = i2` (i2 just set to 0): every spelling tried (`off = i2;`,\n  `off = i2 = 0;`, `off = (unsigned int)i2;`) constant-propagates to `li r5, 0`. 1-row pair.\n\n## Hypotheses (not established)\n- fp callee-saved priority appears related to the order in which (float)(double) read-back\n  rewrites touch values (first-read ranks f31), but no model tried predicted all four probe\n  outcomes; possibly the target source produced frsp-on-register read-backs WITHOUT explicit\n  casts (its priorities look like natural creation order), via a mechanism not yet identified.\n- `one`(=1.0f) loop-invariant compare constant: removing the named local and comparing against\n  the lbl directly changed nothing fundamental; its f0-vs-f2 placement is believed to be part\n  of the same numbering cascade.\n\n## Trial matrices\n- KartItem_Tick (6 builds): 96.82 -> 98.31 (operand orders, snd hoist, VF wrap loops, cap form,\n  decl order) -> 97.77 (named-locals probe, regression) -> 98.73 (revert + spdJ coalesce) ->\n  98.79 (k0 probe, one removal) -> 98.83 (reads-early probe; alloc invariant). Park.\n- KartItem_OnKartHit (8 builds): 77.90 -> 96.38. Parked on GPR partition + callee-saved bool li\n  + vcall r6-vs-r12 x6 + f3/f5 swap.\n- ItemEffect_Trap (12 builds): 44.94 -> 85.34. Escape-split solved block 1; region-2 eager\n  per-component scheduling vs target batched 3-frsp+3-muls never matched across 5 shapes.\n- ItemEffect_Projectile (6 builds): 85.42 -> 88.40. Remaining: &vecA addi hoist, eager\n  scheduling, fp naming mirror.\n"
    }
  ],
  "build_verified": {
    "command": "python configure.py && ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },
  "blocked_reason": "All 4 fns parked at register-identity-only (or single instruction-selection) residue per the fp/GPR-numbering family rule; no SoT changes to merge. Worktree TU edits (view structs, typed prototypes) are codegen-neutral with asm bodies restored and are reproducible from Appendix A.",
  "user_attention": null
}
```

## Appendix A: TU header re-apply diff (view structs, typed prototypes, retyped externs)
Apply to src/game/auto_ONKARTHIT_block.c before pasting any appendix body. Codegen-neutral while bodies stay asm.
```diff
diff --git a/src/game/auto_ONKARTHIT_block.c b/src/game/auto_ONKARTHIT_block.c
index 3ccec05..a8797c5 100644
--- a/src/game/auto_ONKARTHIT_block.c
+++ b/src/game/auto_ONKARTHIT_block.c
@@ -21,7 +21,7 @@
 /* refine if the real prototype matters for header consumers. */
 extern void *Alloc(unsigned long);
 extern void AudioChannel_DtorWithSeStop();
-extern void CObj_GetViewMatrix_Cached();
+extern float *CObj_GetViewMatrix_Cached(void *scene);
 extern void CameraEffect_Apply();
 extern void Camera_RotateByYaw();
 extern void CarObject_Dtor();
@@ -50,7 +50,7 @@ extern void EffectSteering_InputViscosity_SetFieldC();
 extern void *FUN_8003b120(unsigned long);
 extern unsigned char Field4NotMinusOne(void *ctx);
 extern void Free_IfOwnedShort();
-extern void GetCourseScene3D();
+extern void *GetCourseScene3D(void);
 extern void GetInputManager();
 extern void GetKartParamBlock();
 extern int GetKartStartSlot();
@@ -63,7 +63,7 @@ extern void InputCmd_TickAndDetectAndClear();
 extern void InputMgr_GetPlayer();
 extern void InterpolationStep();
 extern unsigned char IsAudioMutedItem(void *soundCtrl, int channel);
-extern void IsRaceStarted();
+extern unsigned char IsRaceStarted(void);
 extern int ItemClass_GetFlagByte1(int id);
 extern void ItemEffectBus_ApplyItemConfirm();
 extern void ItemEffectBus_ApplyItemEventClear();
@@ -76,8 +76,8 @@ extern void ItemEffectBus_RegisterBonkPosition();
 extern void ItemEffectBus_SnapshotAndClearSpawnFlags();
 extern void ItemEffectBus_SnapshotAndFullReset();
 extern void ItemEffectBus_TickTornadoCooldown();
-extern void ItemEffectDamp_TryArm();
-extern void ItemEffectImpact_TryArm();
+extern void ItemEffectDamp_TryArm(void *guard, float *vec, int mode, float accel, float scale, float k);
+extern void ItemEffectImpact_TryArm(void *guard, float *vec, float *mtx, int mode);
 extern void ItemEffect_BossGrab(void *guard, float *mtx, void *arg, int param);
 extern void ItemEffect_TornadoLift(void *guard, float *mtx);
 extern int ItemObject_GetByteAt0xEC(void *itemObj, int idx);
@@ -88,13 +88,13 @@ extern unsigned char ItemStateGuard_IsActive(void *guard);
 extern void ItemStateGuard_PruneIfDeadAndReport();
 extern void ItemStateSlotC_TryArm();
 extern void KartAudioChannel_Init();
-extern void KartAudioChannel_PlayColorMatchSE();
-extern void KartAudioChannel_PlayJumpSE();
+extern void KartAudioChannel_PlayColorMatchSE(void *snd, int a, int b, float spd);
+extern void KartAudioChannel_PlayJumpSE(void *snd, int mode);
 extern void KartAudioChannel_Set24WithSeStop();
-extern void KartAudioChannel_StopSE8a();
+extern void KartAudioChannel_StopSE8a(void *snd, int a);
 extern void KartBody_SetWarpTransitFlag();
 extern void KartDriver_Dtor();
-extern void KartDriver_GetKartRootMtx();
+extern void *KartDriver_GetKartRootMtx(void *driver);
 extern void KartDriver_New_Full();
 extern void KartDriver_RenderTimed();
 extern void KartDriver_SetJointPosY_Slot3a();
@@ -106,7 +106,7 @@ extern void KartDriver_TickAction_79268_AndSetSlot5aEulerZ();
 extern void KartEffectFadeTransit_Dtor();
 extern float KartEffectFadeTransit_GetActiveValue();
 extern void KartEffectFadeTransit_Init();
-extern unsigned char KartEffectFadeTransit_IsActive();
+extern unsigned char KartEffectFadeTransit_IsActive(void *obj);
 extern void KartEffectFadeTransit_Tick();
 extern void KartItemAudio_PlayHitConfirmSE();
 extern void KartItemAudio_PlayThrowConfirmSE();
@@ -122,7 +122,7 @@ extern void KartItem_SetVec3At338();
 extern void KartItem_Stub_Returns0();
 extern void KartMovement_CalcCurrentSpeed();
 extern void KartMovement_CalcMaxSpeed();
-extern float KartMovement_CalcSpeedWithCoinBonus();
+extern float KartMovement_CalcSpeedWithCoinBonus(void *mv, int flag);
 extern int KartMovement_GetCurrentItemId(void *driver);
 extern void KartMovement_Init();
 extern void KartMovement_PhysicsStep();
@@ -131,7 +131,7 @@ extern void KartMovement_SetPosition();
 extern void KartMovement_SetTravelProgress(void *mov, float v);
 extern void KartReaction_Front();
 extern void KartReaction_Side();
-extern void MediaBoard_PollCompletion();
+extern void MediaBoard_PollCompletion(void *snd, float v);
 extern void MediaBoard_SendAndCheck();
 extern void MemoryManager_AllocTagged();
 extern void MemoryManager_TimedFree();
@@ -148,7 +148,7 @@ extern void RenderObj_ToggleLapSegment();
 extern float Saturate_Double(float v, float lo, float hi);
 extern void SceneRender_SetViewportRect();
 extern void SetAnimSpin();
-extern void ShadowAreaMgr_QueryPoint();
+extern unsigned char ShadowAreaMgr_QueryPoint(void *mgr, float x, float y, float z);
 extern unsigned char ShadowBillboard_IsRenderReady(void *billboard);
 extern void ShadowBillboard_SetField0x6CAndComputeAxis(void *bb, int mode);
 extern void ShadowBillboard_SetField0xA4();
@@ -158,10 +158,10 @@ extern void ShadowBillboard_StepSimple();
 extern void ShadowBillboard_Tick();
 extern void ShadowBillboard_TriggerSpinFlash();
 extern void SharedPtr_Init();
-extern void SoundCtrl_SetVolume();
+extern void SoundCtrl_SetVolume(void *snd, float v);
 extern void SoundObj_PlaySE(void *snd, int id);
 extern void SoundObj_PlaySE_Direct(void *snd, int id);
-extern void SoundVolumePan_Update();
+extern void SoundVolumePan_Update(void *snd);
 extern void SpeedBoost_Apply(void *obj, int id, float v);
 extern void StrPcb_ForceRun_Neutral();
 extern void *StrPcb_GetInstance(void);
@@ -184,25 +184,25 @@ extern void TitleTracker_Empty_PreFinalizeHook();
 extern void TornadoEffect_ApplyItemVisual_Compact();
 extern void TornadoEffect_ApplyItemVisual_Primary();
 extern void TornadoEffect_ApplyItemVisual_Secondary();
-extern void TornadoEffect_ClearFlagC0AndSetC4();
+extern void TornadoEffect_ClearFlagC0AndSetC4(void *obj, float v);
 extern void TornadoEffect_ComposeRenderMatrix();
 extern void TornadoEffect_Ctor();
 extern void TornadoEffect_GetField114();
-extern void TornadoEffect_SetColorPairC8CC();
+extern void TornadoEffect_SetColorPairC8CC(void *obj, int a, int b);
 extern void TornadoEffect_SetColorRGBLerp();
 extern void TornadoEffect_SetColorY(); /* K&R on purpose: matched C calls it with 1 arg (StopCarObjectSE) and 2 args (OnApply_Freeze) */
 extern void TornadoEffect_SetField114();
 extern void TornadoEffect_SetField11c();
 extern void TornadoEffect_SetField128AndMaybeClear134();
-extern void TornadoEffect_SetFieldAc();
+extern void TornadoEffect_SetFieldAc(void *obj, float v);
 extern void TornadoEffect_SetFlagB4();
-extern void TornadoEffect_SetFlagC0();
-extern void TornadoEffect_SetMatrix1c();
-extern void TornadoEffect_SetMatrixRow0_5c();
-extern void TornadoEffect_SetScalePairB0BC();
+extern void TornadoEffect_SetFlagC0(void *obj);
+extern void TornadoEffect_SetMatrix1c(void *obj, float *m);
+extern void TornadoEffect_SetMatrixRow0_5c(void *obj, float x, float y, float z);
+extern void TornadoEffect_SetScalePairB0BC(void *obj, float a, float b);
 extern void TornadoEffect_SubmitRender();
-extern void TornadoEffect_Tick();
-extern void TornadoEffect_TriggerField140();
+extern void TornadoEffect_Tick(void *obj, int score);
+extern void TornadoEffect_TriggerField140(void *obj);
 extern void TornadoEffect_TriggerFlagD2WithTimer();
 extern void TornadoEffect_TriggerWheelScaleAnim();
 extern void TwoSubDtor_Pending_80064f58();
@@ -253,7 +253,7 @@ extern void *g_objCollChecker;
 extern unsigned int g_playerCarObject;
 extern unsigned int g_raceCamera;
 extern unsigned int lbl_806D0051;
-extern unsigned int lbl_806D1060;
+extern void *lbl_806D1060;
 extern float lbl_806D1080;
 extern float lbl_806D1084;
 extern unsigned int lbl_806D109C;
@@ -283,14 +283,14 @@ extern const float lbl_806D273C;
 extern const float lbl_806D2740;
 extern const float lbl_806D2744;
 extern unsigned int lbl_806D2748;
-extern unsigned int lbl_806D274C;
-extern unsigned int lbl_806D2750;
-extern unsigned int lbl_806D2754;
-extern unsigned int lbl_806D2758;
-extern unsigned int lbl_806D275C;
-extern unsigned int lbl_806D2760;
-extern unsigned int lbl_806D2764;
-extern unsigned int lbl_806D2768;
+extern const float lbl_806D274C;
+extern const float lbl_806D2750;
+extern const float lbl_806D2754;
+extern const float lbl_806D2758;
+extern const float lbl_806D275C;
+extern const float lbl_806D2760;
+extern const float lbl_806D2764;
+extern const float lbl_806D2768;
 extern const float lbl_806D276C;
 extern const float lbl_806D2770;
 extern unsigned int lbl_806D2774;
@@ -327,8 +327,7 @@ extern unsigned int jumptable_803F7640[];
 extern unsigned int jumptable_803F7668[];
 extern unsigned int lbl_802EBA18[];
 extern const float lbl_802EBE14[]; /* 8-float boost blend color table */
-extern unsigned int lbl_802ED5B4[];
-extern unsigned int lbl_802ED7BC[];
+
 extern unsigned int lbl_802ED94C[];
 extern unsigned int lbl_802ED9E4[];
 extern unsigned int lbl_802ED9F4[];
@@ -942,6 +941,175 @@ typedef struct SweepCfgView {
     Vec3 centerB;           /* 0x440 */
 } SweepCfgView;
 
+/* --- views for ItemEffect_Trap / ItemEffect_Projectile --- */
+
+/* trap effect table entry (stride 0x18, lbl_802ED7BC) */
+typedef struct TrapFxEntry {
+    int id;             /* 0x0 */
+    float scaleA;       /* 0x4: TryArm vector scale */
+    float scaleB;       /* 0x8: bus scale factor */
+    int mode;           /* 0xc */
+    int valC;           /* 0x10 */
+    int valD;           /* 0x14 */
+} TrapFxEntry;
+
+extern TrapFxEntry lbl_802ED7BC[];
+
+/* projectile effect table entry (stride 0x14, lbl_802ED5B4) */
+typedef struct ProjFxEntry {
+    int id;             /* 0x0 */
+    float scaleA;       /* 0x4 */
+    int mode8;          /* 0x8 */
+    int valC;           /* 0xc */
+    int valD;           /* 0x10 */
+} ProjFxEntry;
+
+extern ProjFxEntry lbl_802ED5B4[];
+
+/* item bus view exposing the trap scale slot at +0x28 */
+typedef struct ItemBusTrapView {
+    char pad_0x0[0x28];
+    float trapScale28;  /* 0x28 */
+} ItemBusTrapView;
+
+/* --- views for KartItem_OnKartHit --- */
+
+/* 0x1EC-byte hit event record built on the stack and dispatched virtually */
+typedef struct OnHitEvent {
+    char pad_0x0[0x8];
+    int kind;               /* 0x8 */
+    char pad_0xc[0x94];
+    float posX;             /* 0xa0: impact midpoint */
+    float posY;             /* 0xa4 */
+    float posZ;             /* 0xa8 */
+    char pad_0xac[0x140];   /* total 0x1ec */
+} OnHitEvent;
+
+typedef struct HitDispatcher HitDispatcher;
+typedef struct HitDispatcherVt {
+    char pad_0x0[0x8];
+    void (*onHitEvent)(HitDispatcher *self, OnHitEvent *ev, int param); /* 0x8 */
+} HitDispatcherVt;
+struct HitDispatcher {
+    HitDispatcherVt *vt;    /* 0x0 */
+};
+
+struct KartDriverHitView;
+
+/* item bus view with the last-victim slot at +0x8 exposed */
+typedef struct OnHitBusView {
+    char pad_0x0[0x8];
+    struct KartDriverHitView *lastVictim;   /* 0x8 */
+    char pad_0xc[0x4];
+    unsigned long long flags;               /* 0x10 */
+} OnHitBusView;
+
+typedef struct KartDriverHitView {
+    char pad_0x0[0x1f4];
+    int state1f4;               /* 0x1f4 */
+    char pad_0x1f8[0xd4];
+    int coins2cc;               /* 0x2cc */
+    char pad_0x2d0[0x34];
+    OnHitBusView *itemBus;      /* 0x304 */
+    HitDispatcher *dispatcher;  /* 0x308 */
+} KartDriverHitView;
+
+typedef struct KartItemHit KartItemHit;
+typedef struct KartItemHitVt {
+    char pad_0x0[0x34];
+    void (*applyEffect)(KartItemHit *self, OnHitEvent *ev, int param);  /* 0x34 */
+} KartItemHitVt;
+struct KartItemHit {
+    KartItemHitVt *vt;                  /* 0x0 */
+    char pad_0x4[0xc];
+    int raceScore10;                    /* 0x10 */
+    char pad_0x14[0x10];
+    void *soundCtrl;                    /* 0x24 */
+    KartMovementSpeedView *movement;    /* 0x28 */
+    KartDriverHitView *ownerDriver;     /* 0x2c */
+    char pad_0x30[0x94];
+    int hitTimerC4;                     /* 0xc4 */
+    int coinSnapC8;                     /* 0xc8 */
+    char pad_0xcc[0x31];
+    unsigned char coinPenaltyFD;        /* 0xfd */
+    char pad_0xfe[0xb];
+    unsigned char hitState109;          /* 0x109 */
+};
+
+/* --- views for KartItem_Tick --- */
+
+typedef struct KartMovementTickView {
+    char pad_0x0[0x8];
+    int tableIdx;               /* 0x8 */
+    float speed;                /* 0xc */
+    char pad_0x10[0x10];
+    unsigned char byte20;       /* 0x20 */
+    char pad_0x21[0x1];
+    unsigned char capFlag22;    /* 0x22 */
+    char pad_0x23[0x1];
+    SpeedTableEntry *table;     /* 0x24 */
+    char pad_0x28[0x70];
+    float mtx98[16];            /* 0x98: 3x4 transform + position row */
+    char pad_0xd8[0xa4];
+    float velX;                 /* 0x17c */
+    float velY;                 /* 0x180 */
+    float velZ;                 /* 0x184 */
+    char pad_0x188[0x134];
+    unsigned char state2bc;     /* 0x2bc */
+    unsigned char airborne2bd;  /* 0x2bd */
+    unsigned char flag2be;      /* 0x2be */
+    char pad_0x2bf[0x5];
+    int col2c4;                 /* 0x2c4 */
+    int col2c8;                 /* 0x2c8 */
+    char pad_0x2cc[0x8];
+    float steer2d4;             /* 0x2d4 */
+    char pad_0x2d8[0x4];
+    unsigned char flag2dc;      /* 0x2dc */
+} KartMovementTickView;
+
+typedef struct KartItemTickView {
+    char pad_0x0[0x10];
+    int raceScore10;                /* 0x10 */
+    char pad_0x14[0xc];
+    unsigned char strPcbGate20;     /* 0x20 */
+    char pad_0x21[0x3];
+    void *soundCtrl;                /* 0x24 */
+    KartMovementTickView *movement; /* 0x28 */
+    KartDriverBusView *ownerDriver; /* 0x2c */
+    char pad_0x30[0x4];
+    void *effectObj;                /* 0x34 */
+    char pad_0x38[0x4];
+    void *boostObj;                 /* 0x3c */
+    ItemStateBlock *stateBlock;     /* 0x40 */
+    char pad_0x44[0x58];
+    float spd9C;                    /* 0x9c */
+    char pad_0xa0[0x8];
+    unsigned char gateA8;           /* 0xa8 */
+    char pad_0xa9[0xf];
+    float airTimerB8;               /* 0xb8 */
+    float airCapBC;                 /* 0xbc */
+    char pad_0xc0[0x4c];
+    float driftTimer10C;            /* 0x10c */
+    float postFxU;                  /* 0x110 */
+    float postFxV;                  /* 0x114 */
+} KartItemTickView;
+
+typedef struct TornadoStateView {
+    char pad_0x0[0x148];
+    int state148;                   /* 0x148 */
+} TornadoStateView;
+
+/* kart root matrix view (3x4 row-major, translation at column 3) */
+typedef struct KartRootMtxView {
+    char pad_0x0[0xc];
+    float posX;             /* 0xc */
+    char pad_0x10[0xc];
+    float posY;             /* 0x1c */
+    char pad_0x20[0xc];
+    float posZ;             /* 0x2c */
+} KartRootMtxView;
+
+
 /* --- forward decls --- */
 asm void KartItem_OnKartHit(void);
 void KartItem_PlayHitSE_DifferentVictim(KartItemHitSEView *self, void *victim, int channel);
@@ -3033,6 +3201,7 @@ void KartItem_RenderPipelinedWithEffects(KartItemRenderView *self) { /* 0x8004B9
 }
 #pragma exceptions reset
 
+#define VF(x) (*(volatile float *)&(x))
 asm void KartItem_Tick(void) { /* 0x8004BAAC size:0x874 */
     nofralloc
     stwu r1, -0xc0(r1)
@@ -3617,6 +3786,7 @@ asm void KartItem_Tick(void) { /* 0x8004BAAC size:0x874 */
     addi r1, r1, 0xc0
     blr
 }
+#undef VF
 
 asm void KartItem_PerFrameStep(void) { /* 0x8004C320 size:0xC44 */
     nofralloc
@@ -9035,6 +9205,7 @@ asm void ItemEffect_Explosion(ItemStateBlock *self, int idx, void *arg) { /* 0x8
  * across the ItemEffectDamp_TryArm call while the lbl_802ED7BC table base is
  * rematerialized (lis/addi) per use region - the TryStartByCategory
  * addressing-reassociation family; CW saves the full pointer instead. */
+#define VF(x) (*(volatile float *)&(x))
 asm void ItemEffect_Trap(ItemStateBlock *self, int idx, void *arg) { /* 0x80051834 size:0x23C */
     nofralloc
     stwu r1, -0xb0(r1)
@@ -9183,6 +9354,7 @@ asm void ItemEffect_Trap(ItemStateBlock *self, int idx, void *arg) { /* 0x800518
     addi r1, r1, 0xb0
     blr
 }
+#undef VF
 
 /* Precan park (2026-06-10, batch_promote_80051648_effectsrun, 0 probes):
  * ItemEffect_Projectile has the same two classes as ItemEffect_Trap above:
@@ -9191,6 +9363,7 @@ asm void ItemEffect_Trap(ItemStateBlock *self, int idx, void *arg) { /* 0x800518
  * mulli r31,r4,0x14 kept callee-saved across ItemEffectImpact_TryArm with
  * the lbl_802ED5B4 base rematerialized per region. The first normalize
  * block (from arg+0xb8, no frsp) is solvable with the Explosion recipe. */
+#define VF(x) (*(volatile float *)&(x))
 asm void ItemEffect_Projectile(ItemStateBlock *self, int idx, void *arg) { /* 0x80051A70 size:0x248 */
     nofralloc
     stwu r1, -0x40(r1)
@@ -9344,6 +9517,7 @@ asm void ItemEffect_Projectile(ItemStateBlock *self, int idx, void *arg) { /* 0x
     addi r1, r1, 0x40
     blr
 }
+#undef VF
 
 #pragma exceptions off
 int ItemTable_FindEntryByIdStride16(ItemCatEntry16 *tbl, int count, int itemId) { /* 0x80051CB8 size:0x38 */
```

## Appendix B: KartItem_OnKartHit best C (96.38%)
```c
#pragma exceptions off
unsigned char KartItem_OnKartHit(KartItemHit *self, KartDriverHitView *victim) { /* 0x8004A238 size:0x680 */
    struct {
        float d[3];         /* sp+0x8 */
        float mB[16];       /* sp+0x14 */
        float mA[16];       /* sp+0x54 */
    } s;
    OnHitEvent ev;              /* sp+0x94 */
    OnHitBusView *bus;          /* r25 */
    unsigned char fresh;        /* r26 */
    unsigned char b27;          /* r27 */
    unsigned char b28;          /* r28 */
    KartRootMtxView *rm;        /* r29 */
    unsigned char b26;          /* r26 (reuse) */
    unsigned char b25;          /* r25 (reuse) */
    unsigned char ok;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    KartDriverHitView *drv;
    KartDriverHitView *drv2;
    unsigned long long vf;
    float mx;
    float my;
    float mz;

    bus = self->ownerDriver->itemBus;
    ok = IsRaceStarted();
    if (ok != 0) {
        if (self->hitState109 == 0) {
            if ((bus->flags & 0x80ULL) == 0) {
                b1 = 0;
            } else {
                b1 = 1;
            }
            if (b1 == 1) {
                return 0;
            }
            if ((victim->itemBus->flags & 0x80ULL) == 0) {
                b2 = 0;
            } else {
                b2 = 1;
            }
            if (b2 == 1) {
                return 0;
            }
        }
        rm = KartDriver_GetKartRootMtx(victim);
        drv = self->ownerDriver;
        if ((drv->itemBus->flags & 0x30000000ULL) == 0) {
            float *t;
            int i;

            t = self->movement->transform;
            for (i = 0; i < 16; i++) {
                s.mA[i] = t[i];
            }
            {
                float dir0;
                float dir1;
                float dir2;
                float dot;
                s.d[0] = rm->posX - s.mA[12];
                s.d[1] = rm->posY - s.mA[13];
                s.d[2] = rm->posZ - s.mA[14];
                dir0 = s.mA[0];
                dir1 = s.mA[1];
                dir2 = *(volatile float *)&s.mA[2];         /* reload-mode slot */
                dot = s.d[0] * dir0 + s.d[1] * dir1 + s.d[2] * dir2;
                if (dot > lbl_806D26EC) {
                    KartReaction_Side(drv);
                } else {
                    KartReaction_Front(drv);
                }
            }
        }
        fresh = 0;
        if (bus->lastVictim == 0) {
            if ((self->ownerDriver->itemBus->flags & 0x30000000ULL) == 0) {
                SoundObj_PlaySE_Direct(self->soundCtrl, 0x58);
                SoundObj_PlaySE(self->soundCtrl, 0x11);
                fn_801B1458(self->ownerDriver, victim);
                if (self->hitTimerC4 <= 0) {
                    void *rank;

                    fresh = 1;
                    if ((rank = lbl_806D10A0) == 0) {
                        rank = 0;
                    }
                    if (rank != 0) {
                        RankLog_OnMatchEnd(rank, self->raceScore10, self->ownerDriver, victim);
                    }
                }
            }
            if ((self->ownerDriver->itemBus->flags & 0x10000000ULL) == 0) {
                b3 = 0;
            } else {
                b3 = 1;
            }
            if (b3 == 1) {
                SoundObj_PlaySE_Direct(self->soundCtrl, 0xc6);
            }
            self->hitTimerC4 = 0x3c;
        }
        bus->lastVictim = victim;
        if (fresh == 1) {
            if (self->coinPenaltyFD != 0) {
                if (self->raceScore10 != 4) {
                    CoinSystem_RemoveCoins(self->ownerDriver, 1);
                } else {
                    KartDriverHitView *d2 = self->ownerDriver;
                    int n = d2->coins2cc - 1;
                    if (n < 0) {
                        n = 0;
                    }
                    d2->coins2cc = n;
                }
                self->coinSnapC8 = self->ownerDriver->coins2cc;
            }
        }
        KartItem_ApplyImpactImpulseAndRumble((KartItemOpsView *)self, 1, rm->posX, rm->posY, rm->posZ);
        if (self->hitState109 == 1) {
            return 1;
        }
        drv2 = self->ownerDriver;
        b28 = 0;
        if (((*(OnHitBusView * volatile *)&drv2->itemBus)->flags & 0x20000000ULL) == 0) {
            b28 = 0;
        } else {
            b28 = 1;
        }
        vf = victim->itemBus->flags;
        b27 = 0;
        if ((vf & 0x20000000ULL) == 0) {
            b27 = 0;
        } else {
            b27 = 1;
        }
        b26 = 0;
        if (((*(OnHitBusView * volatile *)&drv2->itemBus)->flags & 0x10000000ULL) == 0) {
            b26 = 0;
        } else {
            b26 = 1;
        }
        b25 = 0;
        if ((vf & 0x10000000ULL) == 0) {
            b25 = 0;
        } else {
            b25 = 1;
        }
        memset(&ev, 0, 0x1ec);
        {
            float *t2;
            int j;

            t2 = self->movement->transform;
            for (j = 0; j < 16; j++) {
                s.mB[j] = t2[j];
            }
            {
                float mb12 = s.mB[12];
                float mb13 = s.mB[13];
                float mb14 = s.mB[14];
                float sy = rm->posY + mb13;
                float sx = rm->posX + mb12;
                float sz = rm->posZ + mb14;
                my = lbl_806D2700 * sy;
                mx = lbl_806D2700 * sx;
                mz = lbl_806D2700 * sz;
            }
            ev.posX = mx;
            ev.posY = my;
            ev.posZ = mz;
        }
        if (b28 == 1 && b27 == 0) {
            if (victim->state1f4 >= 0 && victim->state1f4 <= 3) {
                ev.kind = 2;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, 0x122);
            } else {
                ev.kind = 0x3d;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, -1);
            }
        } else if (b28 == 0 && b27 == 1) {
            ev.kind = 2;
            self->vt->applyEffect(self, &ev, -1);
        } else if (b26 == 1 && b25 == 0) {
            if (victim->state1f4 >= 0 && victim->state1f4 <= 3) {
                ev.kind = 2;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, 0x123);
            } else {
                ev.kind = 0x3d;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, -1);
            }
        } else if (b26 == 0 && b25 == 1) {
            ev.kind = 2;
            self->vt->applyEffect(self, &ev, 0x123);
        }
        return 1;
    }
    return ok;
}
#pragma exceptions reset
```

## Appendix C: KartItem_Tick best C (98.83%)
Replace the asm body (incl. surrounding #pragma exceptions off/reset) and change the forward decl to `void KartItem_Tick(KartItemTickView *self);`.
```c
#define VF(x) (*(volatile float *)&(x))
#pragma exceptions off
void KartItem_Tick(KartItemTickView *self) { /* 0x8004BAAC size:0x874 */
    struct {
        float sqD;          /* sp+0x8: sqrtf slot */
        int col2c8;         /* sp+0xc */
        int col2c4;         /* sp+0x10 */
        float row[3];       /* sp+0x14 */
        float vel[3];       /* sp+0x20 */
        float m[16];        /* sp+0x2c */
    } s;
    float *mtx;             /* r30: movement->mtx98 */
    double guess;
    float spd;
    float spdJ;
    float ratio;
    float ty;
    float tx;
    float tz;
    float py;
    float px;
    float sum;
    float pz;
    float o0;
    float o1;
    float o2;
    float u0;
    float u1;
    float u2;
    float drift;            /* f31 */
    float best;             /* f28 */
    float vol;
    unsigned char gate;
    unsigned char cond;
    unsigned char b;
    int mode;
    int st;

    mtx = self->movement->mtx98;
    if (GetCourseScene3D() != 0 && CObj_GetViewMatrix_Cached(GetCourseScene3D()) != 0) {
        float *vm;
        KartMovementTickView *mv2;
        int i;

        vm = CObj_GetViewMatrix_Cached(GetCourseScene3D());
        mv2 = self->movement;
        for (i = 0; i < 16; i++) {
            s.m[i] = lbl_806D26EC;
        }
        s.vel[0] = mv2->velX;
        s.vel[1] = mv2->velY;
        s.vel[2] = mv2->velZ;
        ty = (float)(double)s.vel[1];
        tx = (float)(double)s.vel[0];
        tz = (float)(double)s.vel[2];
        py = ty * ty;
        px = tx * tx;
        sum = px + py;
        pz = tz * tz;
        spd = pz + sum;
        s.m[0] = lbl_806D26FC;
        s.m[5] = lbl_806D26FC;
        s.m[10] = lbl_806D26FC;
        s.m[15] = lbl_806D26FC;
        s.m[0] = vm[0];
        s.m[4] = vm[1];
        s.m[8] = vm[2];
        s.m[12] = vm[3];
        s.m[1] = vm[4];
        s.m[5] = vm[5];
        s.m[9] = vm[6];
        s.m[13] = vm[7];
        s.m[2] = vm[8];
        s.m[6] = vm[9];
        s.m[10] = vm[10];
        s.m[14] = vm[11];
        if (spd > lbl_806D26EC) {
            guess = __frsqrte(spd);
            guess = lbl_806D2720 * guess * (lbl_806D2728 - spd * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - spd * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - spd * (guess * guess));
            VF(s.sqD) = (float)(spd * guess);
            spd = VF(s.sqD);
        }
        spdJ = lbl_806D26EC;
        if (spd <= spdJ) {
            s.vel[2] = spdJ;
            s.vel[1] = spdJ;
            s.vel[0] = spdJ;
        } else {
            float inv;
            spdJ = spd;
            inv = lbl_806D26FC / spd;
            s.vel[0] = s.vel[0] * inv;
            s.vel[1] = s.vel[1] * inv;
            s.vel[2] = s.vel[2] * inv;
        }
        ratio = spdJ / lbl_806D274C;
        o0 = s.m[0] * s.vel[0] + s.vel[1] * s.m[4] + s.vel[2] * s.m[8];
        o1 = s.m[1] * s.vel[0] + s.vel[1] * s.m[5] + s.vel[2] * s.m[9];
        o2 = s.vel[0] * s.m[2] + s.vel[1] * s.m[6] + s.vel[2] * s.m[10];
        s.vel[0] = o0;
        s.vel[1] = o1;
        s.vel[2] = o2;
        u0 = o0 * ratio;
        u1 = o1 * ratio;
        u2 = o2 * ratio;
        self->postFxU = self->postFxU + u0;
        s.vel[0] = u0;
        s.vel[1] = u1;
        s.vel[2] = u2;
        self->postFxV = self->postFxV - u1;
        while (self->postFxU > lbl_806D26FC) {
            self->postFxU = VF(self->postFxU) - lbl_806D26FC;
        }
        while (self->postFxU < lbl_806D26EC) {
            self->postFxU = lbl_806D26FC + self->postFxU;
        }
        while (self->postFxV > lbl_806D26FC) {
            self->postFxV = VF(self->postFxV) - lbl_806D26FC;
        }
        while (self->postFxV < lbl_806D26EC) {
            self->postFxV = lbl_806D26FC + self->postFxV;
        }
    }
    if (ShadowAreaMgr_QueryPoint(lbl_806D1060, mtx[12], mtx[13], mtx[14]) == 1) {
        TornadoEffect_TriggerField140(self->effectObj);
    }
    {
        float vy = lbl_806D2714;
        float k0 = lbl_806D26EC;
        float rx, ry, rz;

        s.row[0] = k0;
        s.row[1] = vy;
        s.row[2] = k0;
        rx = mtx[0] * k0 + vy * mtx[4] + k0 * mtx[8] + mtx[12];
        ry = mtx[1] * k0 + vy * mtx[5] + k0 * mtx[9] + mtx[13];
        rz = k0 * mtx[2] + vy * mtx[6] + k0 * mtx[10] + mtx[14];
        s.row[0] = rx;
        s.row[1] = ry;
        s.row[2] = rz;
        TornadoEffect_SetMatrixRow0_5c(self->effectObj, rx, ry, rz);
    }
    TornadoEffect_SetMatrix1c(self->effectObj, mtx);
    TornadoEffect_SetFieldAc(self->effectObj, self->spd9C);
    {
        KartMovementTickView *mv3;

        mv3 = self->movement;
        s.col2c4 = mv3->col2c4;
        s.col2c8 = mv3->col2c8;
        if (mv3->state2bc == 0 && mv3->airborne2bd == 0) {
            KartMovementTickView *mv4;

            if (ItemStateGuard_IsActive(self->stateBlock->guard) == 0) {
                TornadoEffect_SetColorPairC8CC(self->effectObj, s.col2c4, s.col2c8);
            }
            {
                void *snd = self->soundCtrl;
                KartAudioChannel_PlayColorMatchSE(snd, s.col2c4, s.col2c8,
                                                  KartMovement_CalcSpeedWithCoinBonus(self->movement, 0));
            }
            if (self->movement->flag2be == 1) {
                TornadoEffect_ClearFlagC0AndSetC4(self->effectObj, lbl_806D2750 * self->airTimerB8);
                if (self->strPcbGate20 != 0) {
                    StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 0xc, 2, lbl_806D26E4);
                }
            }
            mv4 = self->movement;
            cond = (mv4->airborne2bd == 1) ? 0 : mv4->flag2dc;
            if (cond == 1) {
                MediaBoard_PollCompletion(self->soundCtrl, lbl_806D26FC);
                TornadoEffect_SetScalePairB0BC(self->effectObj, lbl_806D26FC, lbl_806D26EC);
            } else {
                MediaBoard_PollCompletion(self->soundCtrl, lbl_806D26EC);
                TornadoEffect_SetScalePairB0BC(self->effectObj, lbl_806D26EC, lbl_806D26FC);
            }
        } else {
            if (ItemStateGuard_IsActive(self->stateBlock->guard) == 1) {
                TornadoEffect_SetColorPairC8CC(self->effectObj, 0, 0);
            }
            MediaBoard_PollCompletion(self->soundCtrl, lbl_806D26EC);
            KartAudioChannel_PlayColorMatchSE(self->soundCtrl, 0, 0, lbl_806D26EC);
            TireEffect_ResetSpin(self->effectObj, lbl_806D26EC, lbl_806D26EC);
            TornadoEffect_SetFlagC0(self->effectObj);
        }
    }
    if (self->movement->airborne2bd == 1) {
        self->airTimerB8 = self->airTimerB8 + lbl_806D2730;
        if (self->airCapBC > lbl_806D26EC && self->airTimerB8 > self->airCapBC) {
            self->movement->steer2d4 = lbl_806D2754;
        }
    } else {
        self->airTimerB8 = lbl_806D26EC;
        self->movement->steer2d4 = lbl_806D2758;
    }
    if (KartEffectFadeTransit_IsActive(self->boostObj) == 0) {
        if (self->driftTimer10C > lbl_806D275C) {
            self->driftTimer10C = self->driftTimer10C - lbl_806D2760;
            if (self->driftTimer10C < lbl_806D275C) {
                self->driftTimer10C = lbl_806D275C;
            }
        }
    }
    {
        int i2;
        int off;
        KartMovementTickView *mv5;

        gate = self->gateA8;
        drift = self->driftTimer10C;
        mv5 = self->movement;
        if (gate == 1) {
            if (mv5->airborne2bd == 1 && self->airTimerB8 > lbl_806D2764) {
                drift = drift * lbl_806D2768;
                vol = Saturate_Double(drift * (mv5->speed / mv5->table[mv5->tableIdx].refSpeed),
                                      lbl_806D26EC, drift);
            } else if (mv5->byte20 == 1) {
                SpeedTableEntry *e;

                i2 = 0;
                best = lbl_806D26EC;
                off = i2;
                while (i2 < (e = &mv5->table[mv5->tableIdx])->count) {
                    if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < lbl_806D26FC) {
                        best = mv5->table[mv5->tableIdx].pairs[i2].value;
                        break;
                    }
                    off += 8;
                    i2 += 1;
                }
                if (mv5->capFlag22 == 1) {
                    if (best >= lbl_806D276C) {
                        best = lbl_806D276C;
                    }
                }
                vol = Saturate_Double(drift * (KartMovement_CalcSpeedWithCoinBonus(self->movement, 0) / (lbl_806D2770 * best)),
                                      lbl_806D26EC, drift);
            } else {
                float rr2 = mv5->speed / mv5->table[mv5->tableIdx].refSpeed - lbl_806D26E8;
                vol = Saturate_Double(rr2 * drift, lbl_806D26EC, drift);
            }
        } else {
            float rr = mv5->speed / mv5->table[mv5->tableIdx].refSpeed;
            vol = Saturate_Double(rr * drift, lbl_806D26EC, drift);
        }
        SoundCtrl_SetVolume(self->soundCtrl, vol);
    }
    st = ((TornadoStateView *)self->effectObj)->state148;
    mode = -1;
    if (st != 0) {
        if (st == 1) {
            mode = 0;
        } else {
            mode = 1;
        }
    }
    b = 0;
    if ((self->ownerDriver->itemBus->flags & 0x30ULL) == 0) {
        b = 0;
    } else {
        b = 1;
    }
    if (b == 1) {
        mode = 2;
    }
    if (mode == -1) {
        KartAudioChannel_StopSE8a(self->soundCtrl, 1);
    } else {
        KartAudioChannel_PlayJumpSE(self->soundCtrl, mode);
    }
    TornadoEffect_Tick(self->effectObj, self->raceScore10);
    SoundVolumePan_Update(self->soundCtrl);
}
#pragma exceptions reset
#undef VF
```

### KartItem_Tick residue dump (build 6, 65 rows)
```
 6364: lfs f31, lbl_806D26EC@sda21           |  6364: lfs f29, lbl_806D26EC@sda21           ARG_MISMATCH
 6368: lfs f29, 0x180(r4)                    |  6368: lfs f30, 0x17c(r4)                    ARG_MISMATCH
 6372: lfs f30, 0x17c(r4)                    |  6372: lfs f31, 0x180(r4)                    ARG_MISMATCH
 6376: frsp f0, f29                          |  6376: frsp f1, f30                          ARG_MISMATCH
 6380: lfs f28, 0x184(r4)                    |  6380: lfs f13, 0x184(r4)                    ARG_MISMATCH
 6384: frsp f1, f30                          |  6384: frsp f0, f31                          ARG_MISMATCH
 6388: stfs f31, 0x2c(r1)                    |  6388: stfs f29, 0x2c(r1)                    ARG_MISMATCH
 6392: frsp f2, f28                          |  6392: frsp f2, f13                          ARG_MISMATCH
 6396: lfs f13, lbl_806D26FC@sda21           |  6396: lfs f28, lbl_806D26FC@sda21           ARG_MISMATCH
 6404: stfs f31, 0x40(r1)                    |  6404: stfs f29, 0x40(r1)                    ARG_MISMATCH
 6420: stfs f31, 0x54(r1)                    |  6420: stfs f29, 0x54(r1)                    ARG_MISMATCH
 6428: stfs f31, 0x68(r1)                    |  6428: stfs f29, 0x68(r1)                    ARG_MISMATCH
 6436: stfs f31, 0x3c(r1)                    |  6436: stfs f29, 0x3c(r1)                    ARG_MISMATCH
 6448: stfs f31, 0x4c(r1)                    |  6448: stfs f29, 0x4c(r1)                    ARG_MISMATCH
 6456: stfs f31, 0x5c(r1)                    |  6456: stfs f29, 0x5c(r1)                    ARG_MISMATCH
 6460: fcmpo cr0, f0, f31                    |  6460: fcmpo cr0, f0, f29                    ARG_MISMATCH
 6468: stfs f31, 0x30(r1)                    |  6468: stfs f29, 0x30(r1)                    ARG_MISMATCH
 6476: stfs f13, 0x40(r1)                    |  6476: stfs f28, 0x2c(r1)                    ARG_MISMATCH
 6484: stfs f31, 0x50(r1)                    |  6484: stfs f29, 0x50(r1)                    ARG_MISMATCH
 6492: stfs f31, 0x60(r1)                    |  6492: stfs f29, 0x60(r1)                    ARG_MISMATCH
 6500: stfs f31, 0x34(r1)                    |  6500: stfs f29, 0x34(r1)                    ARG_MISMATCH
 6508: stfs f31, 0x44(r1)                    |  6508: stfs f29, 0x44(r1)                    ARG_MISMATCH
 6516: stfs f13, 0x54(r1)                    |  6516: stfs f28, 0x40(r1)                    ARG_MISMATCH
 6524: stfs f31, 0x64(r1)                    |  6524: stfs f29, 0x64(r1)                    ARG_MISMATCH
 6528: stfs f13, 0x2c(r1)                    |  6528: stfs f28, 0x54(r1)                    ARG_MISMATCH
 6532: stfs f30, 0x20(r1)                    |  6532: stfs f29, 0x38(r1)                    ARG_MISMATCH
 6536: stfs f29, 0x24(r1)                    |  6536: stfs f29, 0x48(r1)                    ARG_MISMATCH
 6540: stfs f28, 0x28(r1)                    |  6540: stfs f29, 0x58(r1)                    ARG_MISMATCH
 6544: stfs f31, 0x38(r1)                    |  6544: stfs f30, 0x20(r1)                    ARG_MISMATCH
 6548: stfs f31, 0x48(r1)                    |  6548: stfs f31, 0x24(r1)                    ARG_MISMATCH
 6552: stfs f31, 0x58(r1)                    |  6552: stfs f13, 0x28(r1)                    ARG_MISMATCH
 6556: stfs f13, 0x68(r1)                    |  6556: stfs f28, 0x68(r1)                    ARG_MISMATCH
 6772: lfs f6, 0x24(r1)                      |  6772: lfs f7, 0x24(r1)                      ARG_MISMATCH
 6792: lfs f8, 0x20(r1)                      |  6792: lfs f5, 0x2c(r1)                      ARG_MISMATCH
 6796: lfs f5, 0x2c(r1)                      |  6796: lfs f8, 0x20(r1)                      ARG_MISMATCH
 6800: fmuls f2, f6, f2                      |  6800: fmuls f2, f7, f2                      ARG_MISMATCH
 6808: lfs f7, 0x4c(r1)                      |  6808: lfs f6, 0x4c(r1)                      ARG_MISMATCH
 6812: fmuls f3, f6, f1                      |  6812: fmuls f3, f7, f1                      ARG_MISMATCH
 6820: fmuls f1, f6, f0                      |  6820: fmuls f1, f7, f0                      ARG_MISMATCH
 6824: fmadds f6, f5, f8, f2                 |  6824: fmadds f5, f5, f8, f2                 ARG_MISMATCH
 6832: fmadds f4, f4, f8, f3                 |  6832: fmadds f3, f4, f8, f3                 ARG_MISMATCH
 6836: lfs f5, 0x50(r1)                      |  6836: lfs f4, 0x50(r1)                      ARG_MISMATCH
 6844: fmadds f2, f8, f2, f1                 |  6844: fmadds f1, f8, f2, f1                 ARG_MISMATCH
 6848: fmadds f7, f9, f7, f6                 |  6848: fmadds f5, f9, f6, f5                 ARG_MISMATCH
 6852: lfs f3, 0x54(r1)                      |  6852: lfs f2, 0x54(r1)                      ARG_MISMATCH
 6856: fmadds f6, f9, f5, f4                 |  6856: fmadds f4, f9, f4, f3                 ARG_MISMATCH
 6860: lfs f1, lbl_806D26FC@sda21            |  6860: lfs f3, lbl_806D26FC@sda21            ARG_MISMATCH
 6864: fmadds f5, f9, f3, f2                 |  6864: fmadds f2, f9, f2, f1                 ARG_MISMATCH
 6868: fmuls f4, f7, f10                     |  6868: fmuls f6, f5, f10                     ARG_MISMATCH
 6872: stfs f7, 0x20(r1)                     |  6872: stfs f5, 0x20(r1)                     ARG_MISMATCH
 6876: fmuls f3, f6, f10                     |  6876: fmuls f5, f4, f10                     ARG_MISMATCH
 6880: fmuls f2, f5, f10                     |  6880: fmuls f1, f2, f10                     ARG_MISMATCH
 6884: fadds f0, f0, f4                      |  6884: fadds f0, f0, f6                      ARG_MISMATCH
 6888: stfs f6, 0x24(r1)                     |  6888: stfs f4, 0x24(r1)                     ARG_MISMATCH
 6892: stfs f5, 0x28(r1)                     |  6892: stfs f2, 0x28(r1)                     ARG_MISMATCH
 6904: stfs f4, 0x20(r1)                     |  6904: stfs f6, 0x20(r1)                     ARG_MISMATCH
 6908: fsubs f0, f0, f3                      |  6908: fsubs f0, f0, f5                      ARG_MISMATCH
 6912: stfs f3, 0x24(r1)                     |  6912: stfs f5, 0x24(r1)                     ARG_MISMATCH
 6916: stfs f2, 0x28(r1)                     |  6916: stfs f1, 0x28(r1)                     ARG_MISMATCH
 6932: fsubs f0, f0, f1                      |  6932: fsubs f0, f0, f3                      ARG_MISMATCH
 6944: fcmpo cr0, f0, f1                     |  6944: fcmpo cr0, f0, f3                     ARG_MISMATCH
                                             |  7900: lfs f28, lbl_806D26EC@sda21           INSERT
 7904: lfs f28, lbl_806D26EC@sda21           |  7908: lfs f0, lbl_806D26FC@sda21            ARG_MISMATCH
 7908: lfs f0, lbl_806D26FC@sda21            |  7912: li r5, 0x0                            REPLACE
 7912: mr r5, r4                             |                                              DELETE
-- 65 diff rows / 542 total
```

## Appendix D: ItemEffect_Trap best C (85.34%)
```c
#define VF(x) (*(volatile float *)&(x))
#pragma exceptions off
void ItemEffect_Trap(ItemStateBlock *self, int idx, ItemObjectPosView *arg) { /* 0x80051834 size:0x23C */
    struct {
        float vecB[3];      /* sp+0x8 */
        float vecA[3];      /* sp+0x14 */
    } v;
    float xK;
    float yK;
    float zK;
    float x2;
    float y2;
    float z2;
    struct {
        float dir[3];       /* sp+0x20 */
        float d[3];         /* sp+0x2c */
        float m[16];        /* sp+0x38 */
    } s;
    float scale;            /* f31 */

    scale = lbl_806D26FC;
    if (arg != 0) {
        KartMovementSpeedView *mv;
        float *t;
        int i;

        mv = self->owner->movement;
        t = mv->transform;
        for (i = 0; i < 16; i++) {
            s.m[i] = t[i];
        }
        {
            float dx = arg->posX - s.m[12];
            float dy = arg->posY - s.m[13];
            float dz = arg->posZ - s.m[14];
            float t0, t1, sum, t2, dot;
            s.d[0] = dx;
            s.d[1] = dy;
            s.d[2] = dz;
            s.dir[0] = s.m[0];
            s.dir[1] = s.m[1];
            s.dir[2] = s.m[2];
            t0 = s.m[0] * dx;
            t1 = s.m[1] * dy;
            sum = t0 + t1;
            t2 = s.m[2] * dz;
            dot = t2 + sum;
            if (dot < lbl_806D26EC) {
                scale = lbl_806D26E4;
            }
        }
        scale = scale * lbl_802ED7BC[idx].scaleB;
    }
    {
        KartMovementSpeedView *mv2;

        mv2 = self->owner->movement;
        v.vecA[2] = mv2->velZ;
        v.vecA[1] = mv2->velY;
        v.vecA[0] = mv2->velX;
        v.vecA[0] = v.vecA[0] * lbl_806D2730;
        v.vecA[1] = v.vecA[1] * lbl_806D2730;
        v.vecA[2] = v.vecA[2] * lbl_806D2730;
        v.vecA[0] = v.vecA[0] * lbl_802ED7BC[idx].scaleA;
        v.vecA[1] = v.vecA[1] * lbl_802ED7BC[idx].scaleA;
        v.vecA[2] = v.vecA[2] * lbl_802ED7BC[idx].scaleA;
        v.vecB[0] = mv2->velX;
        v.vecB[1] = mv2->velY;
        v.vecB[2] = mv2->velZ;
        ItemEffectDamp_TryArm(self->guard, v.vecA, lbl_802ED7BC[idx].mode, mv2->accel1c8, scale, lbl_806D2730);
    }
    ((ItemBusTrapView *)self->owner->ownerDriver->itemBus)->trapScale28 = scale;
    *(IdFlagPair *)&self->activeId = *(const IdFlagPair *)&lbl_802ED7BC[idx].valC;
}
#pragma exceptions reset
#undef VF
```

## Appendix E: ItemEffect_Projectile best C (88.40%)
```c
#define VF(x) (*(volatile float *)&(x))
#pragma exceptions off
void ItemEffect_Projectile(ItemStateBlock *self, int idx, ItemObjectPosView *arg) { /* 0x80051A70 size:0x248 */
    struct {
        float sq2;          /* sp+0x8: block-2 sqrtf slot */
        float sq1;          /* sp+0xc: block-1 sqrtf slot */
    } q;
    struct {
        float vecB[3];      /* sp+0x10 */
        float vecC[3];      /* sp+0x1c */
        float vecA[3];      /* sp+0x28 */
    } s;
    double guess;
    float mag;
    float mag2;
    float py;
    float px;
    float sum;
    float pz;
    float ty;
    float tx;
    float tz;
    float py2;
    float px2;
    float sum2;
    float pz2;

    py = arg->velY * arg->velY;
    px = arg->velX * arg->velX;
    pz = arg->velZ * arg->velZ;
    s.vecA[0] = arg->velX;
    s.vecA[1] = arg->velY;
    s.vecA[2] = arg->velZ;
    sum = px + py;
    mag = pz + sum;
    if (mag > lbl_806D26EC) {
        guess = __frsqrte(mag);
        guess = lbl_806D2720 * guess * (lbl_806D2728 - mag * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - mag * (guess * guess));
        guess = lbl_806D2720 * guess * (lbl_806D2728 - mag * (guess * guess));
        VF(q.sq1) = (float)(mag * guess);
        mag = VF(q.sq1);
    }
    if (mag <= lbl_806D26EC) {
        s.vecA[2] = lbl_806D26EC;
        s.vecA[1] = lbl_806D26EC;
        s.vecA[0] = lbl_806D26EC;
    } else {
        float inv = lbl_806D26FC / mag;
        s.vecA[0] = s.vecA[0] * inv;
        s.vecA[1] = s.vecA[1] * inv;
        s.vecA[2] = s.vecA[2] * inv;
    }
    {
        KartMovementSpeedView *mv;

        mv = self->owner->movement;
        s.vecB[1] = mv->velY;
        s.vecB[0] = mv->velX;
        s.vecB[2] = mv->velZ;
        s.vecC[1] = mv->velY;
        s.vecC[0] = mv->velX;
        s.vecC[2] = mv->velZ;
        ty = (float)(double)s.vecB[1];
        tx = (float)(double)s.vecB[0];
        tz = (float)(double)s.vecB[2];
        py2 = ty * ty;
        px2 = tx * tx;
        sum2 = px2 + py2;
        pz2 = tz * tz;
        mag2 = pz2 + sum2;
        if (mag2 > *(volatile const float *)&lbl_806D26EC) {
            guess = __frsqrte(mag2);
            guess = lbl_806D2720 * guess * (lbl_806D2728 - mag2 * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - mag2 * (guess * guess));
            guess = lbl_806D2720 * guess * (lbl_806D2728 - mag2 * (guess * guess));
            VF(q.sq2) = (float)(mag2 * guess);
            mag2 = VF(q.sq2);
        }
    }
    s.vecA[0] = s.vecA[0] * mag2;
    s.vecA[1] = s.vecA[1] * mag2;
    s.vecA[2] = s.vecA[2] * mag2;
    s.vecA[0] = s.vecA[0] * lbl_806D2730;
    s.vecA[1] = s.vecA[1] * lbl_806D2730;
    s.vecA[2] = s.vecA[2] * lbl_806D2730;
    s.vecA[0] = s.vecA[0] * lbl_802ED5B4[idx].scaleA;
    s.vecA[1] = s.vecA[1] * lbl_802ED5B4[idx].scaleA;
    s.vecA[2] = s.vecA[2] * lbl_802ED5B4[idx].scaleA;
    ItemEffectImpact_TryArm(self->guard, s.vecA, self->owner->movement->transform, lbl_802ED5B4[idx].mode8);
    *(IdFlagPair *)&self->activeId = *(const IdFlagPair *)&lbl_802ED5B4[idx].valC;
}
#pragma exceptions reset
#undef VF
```
