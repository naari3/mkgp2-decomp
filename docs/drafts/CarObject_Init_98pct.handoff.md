# HANDOFF batch_promote_carobject_init

CarObject_Init 0x8004E618 (0x7BC, TU src/game/auto_ONKARTHIT_block.c) promote attempt.
Best 98.23% (28/498 diff rows), structurally blocked at -1 insn (WarpAutoRun new-expr join)
plus a register-web tie-break family. Asm body restored; build SHA-1 green at HEAD state.
Paste-ready full diff of the best state in Appendix A. Trial matrix in Appendix B.

```json
{
  "batch_id": "batch_promote_carobject_init",
  "sub_summary": "CarObject_Init 0x8004E618: parked at 98.23 pct after 14 builds; ScopedTimer recipe transferred cleanly; blocked by new-expr r0-join (-1 insn, new precan class) + register-web tie-break family (ch/blk/sub/mgr webs); asm body restored, build green",
  "results": [
    {
      "addr": "0x8004E618",
      "name": "CarObject_Init",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 98.23 pct, 28 diff rows / 498 insns, size 1976 vs 1980. Residue: (a) WarpAutoRun guarded-ctor join in r3 (cmpwi) vs target mr.-r0 + post-call mr (one insn shorter, 6 spellings probed, copy-prop always wins - structural, new precan class); (b) ch/blk/sub/mgr callee-saved web identity (o1/o2 family merge solved drv/cam/snd+mov webs, the rest interlock and never aligned across 7 probes); (c) 2-row lwz/li scheduler swap at TornadoEffect args; (d) 11 rows mgr-home cascade (lis/addi schedule). Paste-ready C in HANDOFF Appendix A; retry only after a web-tiebreak or new-expr-join lever exists"
    }
  ],
  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "set_attr": [], "rename": [] },
  "docs_notes": [
    {
      "path": "docs/notes/cw132-carobject-init-park.md",
      "content": "# CarObject_Init 0x8004E618 promote attempt: 98.23% park (2026-06-11, batch_promote_carobject_init)\n\n14 builds, asm body restored (build green). Best state 98.23% / 28 diff rows of 498 insns,\nsizes 1976 vs target 1980 (one structural -1 insn at the WarpAutoRun site). Paste-ready full\ndiff in the batch HANDOFF appendix.\n\n## Confirmed transfers (matched on first/second build, zero residue in their regions)\n- ScopedTimer Phase 2d recipe transfers as-is to the sp+0x14/0x18 flavor: volatile-id ctor\n  struct + one-expression dtor tail matched byte-exact inside a 0x7BC fn on build 1.\n- void*-t / uint-t null idiom (`t = g; if (t != g) {} else if (t == 0) t = 0;`) works for\n  `unsigned int` globals (g_carObjectList x2, lbl_806D10A0) with casts only at use sites.\n- class-1 style flag (`b = 0; if (c1 && c2 && c3) b = 1; self->f108 = b != 0;`) coalesces with\n  the member-store zero/one const webs as predicted (li r5,0 shared / mr r5,r3 from const-1 web).\n\n## New verified levers (facts)\n- volatile aux-pointer hoist `x = *(void * volatile *)&self->field;` before a call whose later\n  arg contains another call: forces the lwz to statement position into a callee-saved reg\n  (plain spelling gets copy-propagated and reloads AFTER the inner call). Verified x3\n  (soundCtrl before GetKartParamBlock, movement before GetKartStartSlot, camera38 load order\n  in the FadeTransit arg block).\n- u8-typed callee prototype args remove clrlwi when the source is a u8 param (16.9 inverse):\n  KartAudioChannel_Init(r5/r6), PlayCamera_Init(r8), KartEffectFadeTransit_Init(r7).\n- Inline-init through a may-alias pointer (tbl/sec blocks): preload self-fields into locals\n  BEFORE the first store through the new object, else stores serialize the loads\n  (lwz/stw ping-pong on one scratch). Preloads reproduce the batched r5/r6/r7 load head.\n- Long-range addi CSE: `(char *)self + 0xc` at fn head (base ctor arg) + at the dispatcher\n  store got CSE'd into an extra callee-saved reg (stmw r22 cascade). Fix: second site as\n  `char *disp = (char *)self; if (self != 0) disp += 0xc;` - the += on a copy is not\n  value-numbered with the original addi; target cmplwi/mr r0/addi r0 shape reproduced.\n- `(int)g_gameMode == 1` cast needed for cmpwi (unsigned global gets cmplwi).\n- Stack locals: 4-byte locals are laid out in REVERSE declaration order (last declared at the\n  lowest offset); the 8-byte tm struct (declared last) sits above them. To get\n  itRet@0x8/pos@0xc/val@0x10/tm@0x14, declare val, pos, itRet, tm.\n- Double same-slot vtable store with interleaved global store: source order\n  `m->vt = A; g_list = m; m->vt = B;` reproduces target store order (no DSE).\n- Prototype int/float interleave moves scheduler emission of arg loads: moving the int\n  isPlayer arg after the floats in TornadoEffect_Ctor moved the lfs f2 emission ahead of the\n  lbz (2-row residual swap of lwz r6 / li r4 remains).\n- Struct-return call via explicit out-param: StlList_InsertBefore (iterator return) callable\n  from C as `asm void StlList_InsertBefore(Iter *ret, StlList *l, Iter *pos, void **val)` -\n  retyping the asm fn signature is codegen-neutral and gives the addi r3,r1,8 hidden-ret shape.\n\n## New structural blocker (precan class): new-expr guard with non-trivial pre-ctor cond\nSite shape: `p = AllocTagged(...); if (p) { <flag cond, ~8 insns>; p = Ctor(p, flag != 0); }\nself->f = p;`. Target joins the result in r0: `mr. r0, r3 ... bl ctor; mr r0, r3; L: stw r0`\n(CW new-expr temp). CW 1.3.2 C with ANY spelling keeps the join in r3 (`cmpwi/cmplwi r3,0`,\nno copies, ONE INSN SHORTER -> size mismatch, not parkable in place). Probed: 1-var, 2-var\ncopy (p=q), assign-in-cond, shared int w (flag+result one var, Ghidra-suggested), explicit\npost-call copy, test-on-w (flips cmplwi->cmpwi, confirming the original tested an int temp),\nstatic-inline helper for the flag. All copy-propagated. The 6 sibling sites with TRIVIAL\nguard bodies reproduce the target mr.-r0 form from plain C - the blocker triggers only when\nextra cond code sits between the test and the ctor call. Precan: if a guarded-ctor site has\nnon-trivial code before the ctor call AND the target uses the mr.-r0 join, expect -1 insn\nin C; park or solve at binary level.\nSide-effect: routing the flag through a static inline helper broke the OTHER site's flag\ncoalescing (member-init li r5,0 web) -> keep one named u8 flag var used by both sites.\n\n## Register-web tie-break family (park reason)\nTwo interlocked web families: A={audio ch, movement, movement-reload}=r26,\nB={sound-reload, driver, camera}=r25 in target. Merging B into one C var locks all of B\n(and mov/mvL) correctly, but the ch web then flips r25<->r26 depending on UNRELATED\ndownstream variable binding (matrix: all-distinct -> ch ok / drv+cam wrong; A+B merged ->\nonly ch wrong; partial merges -> other permutations). blk/sub (target r27/r23, mine r29/r27)\nand mgr (=sub home in both) never matched across decl-order, block-scope, and merge probes.\nSource-closed in the same sense as the fp-numbering family; lever discovery would\nself-correct ch/blk/sub/mgr (plus 11 rows of lis/addi scheduling that follow mgr's home).\n"
    }
  ],
  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },
  "blocked_reason": "Two blockers: (1) structural -1 insn: the WarpAutoRun guarded-ctor site needs the compiler new-expr temp join (mr. r0,r3 / mr r0,r3) but CW 1.3.2 C copy-propagates every spelling to a r3 join (cmpwi, no copies) when non-trivial cond code precedes the ctor call; (2) register-identity web family: ch/blk/sub/mgr callee-saved homes never aligned (source-closed tie-break, same family as fp-numbering parks).",
  "user_attention": null
}
```

## Appendix A: paste-ready best-state diff (98.23 pct, apply with git apply on main HEAD e084e23)

All header edits (typed externs, view structs, StlList_InsertBefore signature) are inert for
the existing asm/matched fns - no C caller of the retyped externs exists in the TU besides the
new fn. The fn replaces the asm body in place, approach B (#pragma exceptions off), manual
extab/extabindex kept untouched.

```diff
diff --git a/src/game/auto_ONKARTHIT_block.c b/src/game/auto_ONKARTHIT_block.c
index b65cbb3..8a5b548 100644
--- a/src/game/auto_ONKARTHIT_block.c
+++ b/src/game/auto_ONKARTHIT_block.c
@@ -30,12 +30,12 @@ extern float CollisionTest_CalcPenetration(void *checker, void *a, void *b);
 extern void DashZone_ProcessAutoRun();
 extern void DebugPrintf();
 extern void EffectSpeed_ApplySpeedScale(void *req, float a, float b);
-extern void EffectSpeed_Init();
+extern void *EffectSpeed_Init(void *p, void *self);
 extern void EffectSpeed_TickAndGet();
 extern void EffectSpeed_TickTimer();
 extern unsigned char EffectState_HasContent(void *effectState);
 extern void EffectState_ReleaseAndClear();
-extern void EffectSteering_Ctor();
+extern void *EffectSteering_Ctor(void *p, void *self, int isPlayer);
 extern void EffectSteering_Dtor();
 extern void EffectSteering_InitForDelay();
 extern void EffectSteering_InitForLock();
@@ -52,11 +52,11 @@ extern unsigned char Field4NotMinusOne(void *ctx);
 extern void Free_IfOwnedShort();
 extern void *GetCourseScene3D(void);
 extern void GetInputManager();
-extern void GetKartParamBlock();
+extern void *GetKartParamBlock(void *a, void *b, void *c, int idx);
 extern int GetKartStartSlot();
 extern void InputCmd_Dtor();
 extern void InputCmd_GetDetectedFlag();
-extern void InputCmd_Init();
+extern void *InputCmd_Init(void *p, int n);
 extern void InputCmd_PushSample();
 extern void InputCmd_SetCooldown();
 extern void InputCmd_TickAndDetectAndClear();
@@ -87,7 +87,7 @@ extern int ItemSelect_StartRouletteSpin();
 extern unsigned char ItemStateGuard_IsActive(void *guard);
 extern void ItemStateGuard_PruneIfDeadAndReport();
 extern void ItemStateSlotC_TryArm();
-extern void KartAudioChannel_Init();
+extern void *KartAudioChannel_Init(void *p, void *a, unsigned char b, unsigned char c, int slot, void *blk);
 extern void KartAudioChannel_PlayColorMatchSE(void *snd, int a, int b, float spd);
 extern void KartAudioChannel_PlayJumpSE(void *snd, int mode);
 extern void KartAudioChannel_Set24WithSeStop();
@@ -95,7 +95,7 @@ extern void KartAudioChannel_StopSE8a(void *snd, int a);
 extern void KartBody_SetWarpTransitFlag();
 extern void KartDriver_Dtor();
 extern void *KartDriver_GetKartRootMtx(void *driver);
-extern void KartDriver_New_Full();
+extern void *KartDriver_New_Full(void *p, int slot, void *a, void *blk, int startSlot, int e, void *f);
 extern void KartDriver_RenderTimed();
 extern void KartDriver_SetJointPosY_Slot3a();
 extern void KartDriver_SetJointPosY_Slot3b();
@@ -105,7 +105,7 @@ extern void KartDriver_TickAction_79260();
 extern void KartDriver_TickAction_79268_AndSetSlot5aEulerZ();
 extern void KartEffectFadeTransit_Dtor();
 extern float KartEffectFadeTransit_GetActiveValue();
-extern void KartEffectFadeTransit_Init();
+extern void *KartEffectFadeTransit_Init(void *p, void *mov, void *fx, void *cam, unsigned char isPlayer);
 extern unsigned char KartEffectFadeTransit_IsActive(void *obj);
 extern void KartEffectFadeTransit_Tick();
 extern void KartItemAudio_PlayHitConfirmSE();
@@ -124,7 +124,7 @@ extern float KartMovement_CalcCurrentSpeed(void *mov, int flag);
 extern float KartMovement_CalcMaxSpeed(void *mov, int flag);
 extern float KartMovement_CalcSpeedWithCoinBonus(void *mv, int flag);
 extern int KartMovement_GetCurrentItemId(void *driver);
-extern void KartMovement_Init();
+extern void *KartMovement_Init(void *p, int slot, void *pb, void *snd, float x, float y, float z);
 extern void KartMovement_PhysicsStep();
 extern void KartMovement_RotateByYaw();
 extern void KartMovement_SetPosition();
@@ -133,12 +133,12 @@ extern void KartReaction_Front();
 extern void KartReaction_Side();
 extern void MediaBoard_PollCompletion(void *snd, float v);
 extern void MediaBoard_SendAndCheck();
-extern void MemoryManager_AllocTagged();
+extern void *MemoryManager_AllocTagged(unsigned long size, const char *tag, int id);
 extern void MemoryManager_TimedFree();
 extern void Mtx4x4_TransposeTo4x3();
 extern unsigned long OSGetTick(void);
 extern void PlayCamera_Dtor();
-extern void PlayCamera_Init();
+extern void *PlayCamera_Init(void *p, void *a, void *b, int slot, void *mov, unsigned char isPlayer, int camArg, int g, float z);
 extern void Profiler_RecordFrame(unsigned int id, float ms);
 extern void RankLog_OnHit();
 extern void RankLog_OnMatchEnd();
@@ -186,7 +186,7 @@ extern void TornadoEffect_ApplyItemVisual_Primary();
 extern void TornadoEffect_ApplyItemVisual_Secondary();
 extern void TornadoEffect_ClearFlagC0AndSetC4(void *obj, float v);
 extern void TornadoEffect_ComposeRenderMatrix();
-extern void TornadoEffect_Ctor();
+extern void *TornadoEffect_Ctor(void *p, int mode, void *drv, void *a, float x, float zero, float y, int isPlayer);
 extern void TornadoEffect_GetField114();
 extern void TornadoEffect_SetColorPairC8CC(void *obj, int a, int b);
 extern void TornadoEffect_SetColorRGBLerp();
@@ -208,7 +208,7 @@ extern void TornadoEffect_TriggerWheelScaleAnim();
 extern void TwoSubDtor_Pending_80064f58();
 extern void VisualEffectHolder_Dtor();
 extern void WarpAutoRun_GetParam();
-extern void WarpAutoRun_Init();
+extern void *WarpAutoRun_Init(void *p, int b);
 extern void WarpAutoRun_OnEnter();
 extern void WarpDashMgr_GetInstance();
 extern void WarpZone_CalcExitPosition();
@@ -230,7 +230,7 @@ extern void fn_801B1410();
 extern void fn_801B1458();
 extern void fn_801B5B60();
 extern void fn_802090F0(void *obj, void *center, void *half, float f1, float f2, float f3);
-extern void fn_802091BC();
+extern void *fn_802091BC(void *p, int a, int b);
 extern void fn_80271EF4();
 extern void fn_802791BC();
 extern void fn_8027E480();
@@ -252,7 +252,7 @@ extern unsigned char g_lakituDropStarted;
 extern void *g_objCollChecker;
 extern unsigned int g_playerCarObject;
 extern unsigned int g_raceCamera;
-extern unsigned int lbl_806D0051;
+extern unsigned char lbl_806D0051;
 extern void *lbl_806D1060;
 extern float lbl_806D1080;
 extern float lbl_806D1084;
@@ -313,6 +313,7 @@ extern unsigned int lbl_806D27C4;
 extern const float lbl_806D27C8; /* 1000.0f (us -> ms divisor) */
 extern unsigned int lbl_806D27D0;
 extern const float lbl_806D27D8;
+extern const char lbl_806D27DC[8]; /* "carobj\0\0" alloc tag (sdata2) */
 extern const float lbl_806D27E4;
 extern const float lbl_806D27E8;
 extern const float lbl_806D27EC;
@@ -1122,6 +1123,102 @@ typedef struct CarObjFrameView {
 } CarObjFrameView;
 
 
+/* --- views for CarObject_Init (0x8004E618) --- */
+
+/* iterator value for the inlined std::list<CarObj*>::insert call */
+typedef struct StlListIterInit {
+    StlListNode *node;                 /* 0x0 */
+} StlListIterInit;
+
+/* driver view exposing the dispatcher back-pointer slot at +0x308 */
+typedef struct CarObjInitDriverView {
+    char pad_0x0[0x308];
+    void *dispatcher308;               /* 0x308 */
+} CarObjInitDriverView;
+
+/* secondary lane as initialized by CarObject_Init (byte at +0x4 exposed) */
+typedef struct CarObjSecLaneInit {
+    void *owner;                       /* 0x0 */
+    unsigned char isPlayer4;           /* 0x4 */
+    char pad_0x5[0x3];
+    int itemId;                        /* 0x8 */
+    float blend;                       /* 0xc */
+} CarObjSecLaneInit;
+
+/* ctor-side view of the full car object (KartItem) */
+typedef struct CarObjInitView {
+    void *vt0;                         /* 0x0 */
+    char pad_0x4[0x8];
+    void *vtC;                         /* 0xc */
+    int kartSlot;                      /* 0x10 */
+    void *param14;                     /* 0x14 */
+    void *param18;                     /* 0x18 */
+    void *param1C;                     /* 0x1c */
+    unsigned char isPlayer;            /* 0x20 */
+    unsigned char flag21;              /* 0x21 */
+    char pad_0x22[0x2];
+    void *soundCtrl;                   /* 0x24 */
+    void *movement;                    /* 0x28 */
+    CarObjInitDriverView *driver;      /* 0x2c */
+    void *input30;                     /* 0x30 */
+    void *effectObj;                   /* 0x34 */
+    void *camera38;                    /* 0x38 */
+    void *fade3C;                      /* 0x3c */
+    ItemStateBlock *stateBlock;        /* 0x40 */
+    void *steering44;                  /* 0x44 */
+    void *speed48;                     /* 0x48 */
+    ItemEffectTable *effectTable;      /* 0x4c */
+    CarObjSecLaneInit *secondary;      /* 0x50 */
+    void *warpCtx54;                   /* 0x54 */
+    void *probe58;                     /* 0x58 */
+    void *probe5C;                     /* 0x5c */
+    char audioBlock60[0x30];           /* 0x60 */
+    char responder90[0xc];             /* 0x90 */
+    float spd9C;                       /* 0x9c */
+    float spdA0;                       /* 0xa0 */
+    float spdA4;                       /* 0xa4 */
+    unsigned char gateA8;              /* 0xa8 */
+    char pad_0xa9[0x3];
+    float progressSnapAC;              /* 0xac */
+    unsigned char boostArmedB0;        /* 0xb0 */
+    unsigned char perfectGateB1;       /* 0xb1 */
+    char pad_0xb2[0x2];
+    float airTimerB4;                  /* 0xb4 */
+    float airTimerB8;                  /* 0xb8 */
+    float airCapBC;                    /* 0xbc */
+    int valC0;                         /* 0xc0 */
+    int valC4;                         /* 0xc4 */
+    int coinCountC8;                   /* 0xc8 */
+    float smoothBonusCC;               /* 0xcc */
+    int aiTimerD0;                     /* 0xd0 */
+    unsigned char flagD4;              /* 0xd4 */
+    unsigned char flagD5;              /* 0xd5 */
+    char pad_0xd6[0x2];
+    int aiTimerD8;                     /* 0xd8 */
+    unsigned char driftFlagDC;         /* 0xdc */
+    char pad_0xdd[0x3];
+    int valE0;                         /* 0xe0 */
+    float boostBlendE4;                /* 0xe4 */
+    float valE8;                       /* 0xe8 */
+    int valEC;                         /* 0xec */
+    int prevSyncF0;                    /* 0xf0 */
+    unsigned char byteF4;              /* 0xf4 */
+    char pad_0xf5[0x3];
+    int valF8;                         /* 0xf8 */
+    unsigned char fellOffFC;           /* 0xfc */
+    unsigned char coinPenaltyFD;       /* 0xfd */
+    unsigned char coinBonusEnabledFE;  /* 0xfe */
+    unsigned char byteFF;              /* 0xff */
+    int val100;                        /* 0x100 */
+    char pad_0x104[0x4];
+    unsigned char autoRun108;          /* 0x108 */
+    unsigned char byte109;             /* 0x109 */
+    char pad_0x10a[0x2];
+    float val10C;                      /* 0x10c */
+    float val110;                      /* 0x110 */
+    float val114;                      /* 0x114 */
+} CarObjInitView;
+
 /* --- forward decls --- */
 asm void KartItem_OnKartHit(void);
 void KartItem_PlayHitSE_DifferentVictim(KartItemHitSEView *self, void *victim, int channel);
@@ -1142,7 +1239,10 @@ void CarObject_FrameUpdate(CarObjFrameView *self, void *arg);
 void CarObject_ApplyInput_AI(CarObjInputAIView *self, unsigned char active, float in1, float in2, float in3, float in4);
 void CarObject_ApplyInput(CarObjInputAIView *self, unsigned char active, float in1, float in2, float in3);
 asm void *KartItem_Dtor(void *self, short flag);
-asm void CarObject_Init(void);
+CarObjInitView *CarObject_Init(CarObjInitView *self, float x, float y, float z,
+                               int kartSlot, void *a5, void *a6, void *a7,
+                               unsigned char isPlayer, int slotIdx, int camArg,
+                               unsigned char flag21);
 void KartItem_UpdateShadowBillboardAndViewport(KartItemOpsView *self, int arg2, int arg3);
 asm void KartItem_AdvanceAnim3c(void);
 asm void CarObject_CalcSpeedRatio(void);
@@ -1213,7 +1313,7 @@ asm void KartItem_ApplyEffectToVictim_AdjThunk(void);
 void *dtor_800524CC(void *self, short flag);
 asm void StlList_RemoveByValueField(void);
 asm void StlList_EraseRange(void *ret, StlList *l, StlListNode **beg, StlListNode **end);
-asm void StlList_InsertBefore(void);
+asm void StlList_InsertBefore(StlListIterInit *ret, StlList *l, StlListIterInit *pos, void **val);
 void StlList_InitEmpty(StlList *l);
 void *dtor_80052744(void *self, short flag);
 asm void dtor_8005278C(void);
@@ -5973,534 +6073,317 @@ asm void *KartItem_Dtor(void *self, short flag) { /* 0x8004E2B0 size:0x368 */
     blr
 }
 
-asm void CarObject_Init(void) { /* 0x8004E618 size:0x7BC */
-    nofralloc
-    stwu r1, -0x80(r1)
-    mflr r0
-    stw r0, 0x84(r1)
-    stfd f31, 0x70(r1)
-    psq_st f31, 0x78(r1), 0, 0
-    stfd f30, 0x60(r1)
-    psq_st f30, 0x68(r1), 0, 0
-    stfd f29, 0x50(r1)
-    psq_st f29, 0x58(r1), 0, 0
-    stmw r23, 0x2c(r1)
-    fmr f29, f1
-    mr r31, r3
-    fmr f30, f2
-    lbz r25, 0x8b(r1)
-    mr r23, r4
-    fmr f31, f3
-    mr r24, r5
-    mr r26, r6
-    mr r29, r7
-    mr r30, r8
-    mr r28, r9
-    mr r27, r10
-    addi r4, r31, 0x90
-    bl clItemBoxResponder_Ctor
-    addi r3, r31, 0xc
-    bl WarpZone_VtableTrim
-    lis r4, lbl_803F75F8@ha
-    li r3, 0x38
-    addi r5, r4, lbl_803F75F8@l
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    stw r5, 0x0(r31)
-    addi r0, r5, 0x10
-    li r5, 0x180
-    stw r0, 0xc(r31)
-    stw r23, 0x10(r31)
-    stw r24, 0x14(r31)
-    stw r26, 0x18(r31)
-    stw r29, 0x1c(r31)
-    stb r30, 0x20(r31)
-    stb r25, 0x21(r31)
-    bl MemoryManager_AllocTagged
-    mr. r26, r3
-    beq CarObject_Init_L_8004E6EC
-    lwz r3, 0x10(r31)
-    bl GetKartStartSlot
-    lwz r4, 0x14(r31)
-    mr r7, r3
-    mr r3, r26
-    mr r5, r30
-    mr r6, r30
-    addi r8, r31, 0x60
-    bl KartAudioChannel_Init
-    mr r26, r3
-    CarObject_Init_L_8004E6EC:
-    stw r26, 0x24(r31)
-    li r3, 0x324
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x181
-    bl MemoryManager_AllocTagged
-    mr. r26, r3
-    beq CarObject_Init_L_8004E744
-    lwz r25, 0x24(r31)
-    mr r6, r28
-    lwz r3, 0x14(r31)
-    lwz r4, 0x18(r31)
-    lwz r5, 0x1c(r31)
-    bl GetKartParamBlock
-    fmr f1, f29
-    mr r5, r3
-    fmr f2, f30
-    lwz r4, 0x10(r31)
-    fmr f3, f31
-    mr r3, r26
-    mr r6, r25
-    bl KartMovement_Init
-    mr r26, r3
-    CarObject_Init_L_8004E744:
-    stw r26, 0x28(r31)
-    li r3, 0x384
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x182
-    bl MemoryManager_AllocTagged
-    mr. r25, r3
-    beq CarObject_Init_L_8004E78C
-    lwz r3, 0x10(r31)
-    bl GetKartStartSlot
-    lwz r4, 0x10(r31)
-    mr r7, r3
-    lwz r5, 0x14(r31)
-    mr r3, r25
-    mr r9, r29
-    addi r6, r31, 0x60
-    li r8, 0x0
-    bl KartDriver_New_Full
-    mr r25, r3
-    CarObject_Init_L_8004E78C:
-    stw r25, 0x2c(r31)
-    li r3, 0x30
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x183
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004E7B4
-    li r4, 0x3c
-    bl InputCmd_Init
-    mr r0, r3
-    CarObject_Init_L_8004E7B4:
-    stw r0, 0x30(r31)
-    li r3, 0x154
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x184
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004E7F4
-    fmr f1, f29
-    lwz r5, 0x2c(r31)
-    fmr f3, f30
-    lfs f2, lbl_806D26EC(r2)
-    lwz r6, 0x14(r31)
-    li r4, 0x1
-    lbz r7, 0x20(r31)
-    bl TornadoEffect_Ctor
-    mr r0, r3
-    CarObject_Init_L_8004E7F4:
-    stw r0, 0x34(r31)
-    li r3, 0xd4
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x185
-    bl MemoryManager_AllocTagged
-    mr. r25, r3
-    beq CarObject_Init_L_8004E848
-    lwz r26, 0x28(r31)
-    lwz r3, 0x10(r31)
-    bl GetKartStartSlot
-    fmr f1, f31
-    mr r6, r3
-    lwz r4, 0x14(r31)
-    mr r3, r25
-    mr r5, r29
-    mr r7, r26
-    mr r8, r30
-    mr r9, r27
-    li r10, 0x0
-    bl PlayCamera_Init
-    mr r25, r3
-    CarObject_Init_L_8004E848:
-    stw r25, 0x38(r31)
-    li r3, 0x1c
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x186
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004E87C
-    lwz r6, 0x38(r31)
-    mr r7, r30
-    lwz r4, 0x28(r31)
-    lwz r5, 0x34(r31)
-    bl KartEffectFadeTransit_Init
-    mr r0, r3
-    CarObject_Init_L_8004E87C:
-    stw r0, 0x3c(r31)
-    li r3, 0x14
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x187
-    bl MemoryManager_AllocTagged
-    mr. r27, r3
-    beq CarObject_Init_L_8004E8CC
-    stw r31, 0x0(r27)
-    li r3, 0x1c
-    bl Alloc
-    mr. r23, r3
-    beq CarObject_Init_L_8004E8B4
-    mr r4, r31
-    bl KartItemSubObject_Ctor
-    CarObject_Init_L_8004E8B4:
-    stw r23, 0x4(r27)
-    li r3, -0x1
-    li r0, 0x0
-    stw r3, 0x8(r27)
-    stw r3, 0xc(r27)
-    stw r0, 0x10(r27)
-    CarObject_Init_L_8004E8CC:
-    stw r27, 0x40(r31)
-    li r3, 0x4c
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x188
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004E8F8
-    lbz r5, 0x20(r31)
-    mr r4, r31
-    bl EffectSteering_Ctor
-    mr r0, r3
-    CarObject_Init_L_8004E8F8:
-    stw r0, 0x44(r31)
-    li r3, 0x28
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x189
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004E920
-    mr r4, r31
-    bl EffectSpeed_Init
-    mr r0, r3
-    CarObject_Init_L_8004E920:
-    stw r0, 0x48(r31)
-    li r3, 0x58
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x18a
-    bl MemoryManager_AllocTagged
-    cmplwi r3, 0x0
-    beq CarObject_Init_L_8004E9AC
-    lwz r5, 0x44(r31)
-    li r4, 0x0
-    lwz r6, 0x48(r31)
-    li r0, -0x1
-    lbz r7, 0x20(r31)
-    lfs f1, lbl_806D26FC(r2)
-    stw r31, 0x0(r3)
-    lfs f0, lbl_806D26EC(r2)
-    stw r5, 0x4(r3)
-    stw r6, 0x8(r3)
-    stb r7, 0xc(r3)
-    stfs f1, 0x10(r3)
-    stw r4, 0x14(r3)
-    stw r4, 0x1c(r3)
-    stfs f0, 0x20(r3)
-    stfs f0, 0x24(r3)
-    stw r0, 0x28(r3)
-    stw r0, 0x2c(r3)
-    stw r4, 0x30(r3)
-    stw r4, 0x34(r3)
-    stw r4, 0x38(r3)
-    stfs f1, 0x3c(r3)
-    stw r0, 0x40(r3)
-    stw r0, 0x44(r3)
-    stw r4, 0x48(r3)
-    stw r4, 0x4c(r3)
-    stw r4, 0x50(r3)
-    stfs f1, 0x54(r3)
-    CarObject_Init_L_8004E9AC:
-    stw r3, 0x4c(r31)
-    li r3, 0x10
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x18c
-    bl MemoryManager_AllocTagged
-    cmplwi r3, 0x0
-    beq CarObject_Init_L_8004E9E4
-    lbz r4, 0x20(r31)
-    li r0, -0x1
-    lfs f0, lbl_806D26EC(r2)
-    stw r31, 0x0(r3)
-    stb r4, 0x4(r3)
-    stw r0, 0x8(r3)
-    stfs f0, 0xc(r3)
-    CarObject_Init_L_8004E9E4:
-    stw r3, 0x50(r31)
-    li r3, 0x24
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x18b
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004EA40
-    cmpwi r28, -0x1
-    li r4, 0x0
-    bne CarObject_Init_L_8004EA28
-    lwz r0, 0x10(r31)
-    cmpwi r0, 0x4
-    bne CarObject_Init_L_8004EA28
-    lwz r0, g_gameMode(r13)
-    cmpwi r0, 0x1
-    bne CarObject_Init_L_8004EA28
-    li r4, 0x1
-    CarObject_Init_L_8004EA28:
-    clrlwi r4, r4, 24
-    neg r0, r4
-    or r0, r0, r4
-    srwi r4, r0, 31
-    bl WarpAutoRun_Init
-    mr r0, r3
-    CarObject_Init_L_8004EA40:
-    stw r0, 0x54(r31)
-    li r3, 0x58
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x18d
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004EA6C
-    li r4, -0x1
-    li r5, 0x0
-    bl fn_802091BC
-    mr r0, r3
-    CarObject_Init_L_8004EA6C:
-    stw r0, 0x58(r31)
-    li r3, 0x58
-    addi r4, r2, -0x7A84  /* lbl_806D27DC */
-    li r5, 0x18e
-    bl MemoryManager_AllocTagged
-    mr. r0, r3
-    beq CarObject_Init_L_8004EA98
-    li r4, -0x1
-    li r5, 0x0
-    bl fn_802091BC
-    mr r0, r3
-    CarObject_Init_L_8004EA98:
-    stw r0, 0x5c(r31)
-    li r5, 0x0
-    lfs f1, lbl_806D26EC(r2)
-    li r4, 0x3c
-    lfs f0, lbl_806D26FC(r2)
-    li r3, 0x1
-    stfs f1, 0x9c(r31)
-    li r0, -0x1
-    cmpwi r28, -0x1
-    stfs f1, 0xa0(r31)
-    stfs f1, 0xa4(r31)
-    stb r5, 0xa8(r31)
-    stfs f1, 0xac(r31)
-    stb r5, 0xb0(r31)
-    stb r5, 0xb1(r31)
-    stfs f1, 0xb4(r31)
-    stfs f1, 0xb8(r31)
-    stfs f0, 0xbc(r31)
-    stw r4, 0xc0(r31)
-    stw r5, 0xc4(r31)
-    stw r5, 0xc8(r31)
-    stfs f1, 0xcc(r31)
-    stw r5, 0xd0(r31)
-    stb r3, 0xd4(r31)
-    stb r5, 0xd5(r31)
-    stw r5, 0xd8(r31)
-    stb r5, 0xdc(r31)
-    stw r5, 0xe0(r31)
-    stfs f0, 0xe4(r31)
-    stfs f1, 0xe8(r31)
-    stw r5, 0xec(r31)
-    stw r0, 0xf0(r31)
-    stb r5, 0xf4(r31)
-    stw r5, 0xf8(r31)
-    stb r5, 0xfc(r31)
-    stb r3, 0xfd(r31)
-    stb r3, 0xfe(r31)
-    stb r5, 0xff(r31)
-    stw r5, 0x100(r31)
-    bne CarObject_Init_L_8004EB54
-    lwz r0, 0x10(r31)
-    cmpwi r0, 0x4
-    bne CarObject_Init_L_8004EB54
-    lwz r0, g_gameMode(r13)
-    cmpwi r0, 0x1
-    bne CarObject_Init_L_8004EB54
-    mr r5, r3
-    CarObject_Init_L_8004EB54:
-    clrlwi r4, r5, 24
-    li r0, 0x0
-    neg r3, r4
-    lfs f1, lbl_806D275C(r2)
-    or r3, r3, r4
-    lfs f0, lbl_806D26EC(r2)
-    srwi r3, r3, 31
-    stb r3, 0x108(r31)
-    stb r0, 0x109(r31)
-    stfs f1, 0x10c(r31)
-    stfs f0, 0x110(r31)
-    stfs f0, 0x114(r31)
-    lbz r0, 0x20(r31)
-    cmplwi r0, 0x1
-    bne CarObject_Init_L_8004EBF8
-    lbz r0, 0x21(r31)
-    cmplwi r0, 0x0
-    bne CarObject_Init_L_8004EBF8
-    lbz r0, lbl_806D0051(r13)
-    cmplwi r0, 0x0
-    bne CarObject_Init_L_8004EBBC
-    bl StrPcb_GetInstance
-    bl StrPcb_ForceRun_Neutral
-    bl StrPcb_GetInstance
-    li r4, 0x1
-    bl StrPcb_ResetCommands_Neutral
-    CarObject_Init_L_8004EBBC:
-    lbz r0, 0x20(r31)
-    cmplwi r0, 0x0
-    beq CarObject_Init_L_8004EBF8
-    bl StrPcb_GetInstance
-    li r4, 0x28
-    bl StrPcb_SetCmdByte2d
-    bl StrPcb_GetInstance
-    li r4, 0x1e
-    bl StrPcb_SetCmdByte2e
-    bl StrPcb_GetInstance
-    li r4, 0x0
-    bl StrPcb_SetCounterField14
-    bl StrPcb_GetInstance
-    li r4, 0x0
-    bl StrPcb_SetCmdByte2f
-    CarObject_Init_L_8004EBF8:
-    cmplwi r31, 0x0
-    mr r0, r31
-    beq CarObject_Init_L_8004EC08
-    addi r0, r31, 0xc
-    CarObject_Init_L_8004EC08:
-    lwz r3, 0x2c(r31)
-    stw r0, 0x308(r3)
-    lwz r0, g_carObjectList(r13)
-    cmplwi r0, 0x0
-    bne CarObject_Init_L_8004EC20
-    li r0, 0x0
-    CarObject_Init_L_8004EC20:
-    cmplwi r0, 0x0
-    bne CarObject_Init_L_8004EC64
-    li r3, 0x14
-    bl Alloc
-    mr. r23, r3
-    beq CarObject_Init_L_8004EC64
-    lis r3, lbl_803F7690@ha
-    addi r0, r3, lbl_803F7690@l
-    stw r0, 0x0(r23)
-    lis r3, lbl_803F76A8@ha
-    addi r0, r3, lbl_803F76A8@l
-    stw r23, g_carObjectList(r13)
-    addi r3, r23, 0x4
-    stw r0, 0x0(r23)
-    bl StlList_InitEmpty
-    li r0, 0x0
-    stw r0, 0x10(r23)
-    CarObject_Init_L_8004EC64:
-    lwz r3, g_carObjectCount(r13)
-    lwz r0, g_gameMode(r13)
-    addi r3, r3, 0x1
-    cmpwi r0, 0x1
-    stw r3, g_carObjectCount(r13)
-    beq CarObject_Init_L_8004ECAC
-    lwz r4, g_carObjectList(r13)
-    stw r31, 0x10(r1)
-    cmplwi r4, 0x0
-    bne CarObject_Init_L_8004EC90
-    li r4, 0x0
-    CarObject_Init_L_8004EC90:
-    addi r0, r4, 0x8
-    addi r3, r1, 0x8
-    stw r0, 0xc(r1)
-    addi r4, r4, 0x4
-    addi r5, r1, 0xc
-    addi r6, r1, 0x10
-    bl StlList_InsertBefore
-    CarObject_Init_L_8004ECAC:
-    li r0, 0x28
-    stw r0, 0x18(r1)
-    bl OSGetTick
-    stw r3, 0x14(r1)
-    mr r3, r31
-    li r4, 0x0
-    bl CarObject_MainUpdate
-    lwz r3, lbl_806D10A0(r13)
-    cmplwi r3, 0x0
-    bne CarObject_Init_L_8004ECD8
-    li r3, 0x0
-    CarObject_Init_L_8004ECD8:
-    cmplwi r3, 0x0
-    beq CarObject_Init_L_8004ECE8
-    lwz r4, 0x10(r31)
-    bl TitleTracker_Empty_PreFinalizeHook
-    CarObject_Init_L_8004ECE8:
-    lbz r0, 0x20(r31)
-    cmplwi r0, 0x1
-    bne CarObject_Init_L_8004ED24
-    lwz r25, 0x28(r31)
-    li r4, 0x1
-    mr r3, r25
-    bl KartMovement_CalcMaxSpeed
-    fmr f31, f1
-    mr r3, r25
-    li r4, 0x1
-    bl KartMovement_CalcCurrentSpeed
-    fmr f2, f31
-    bl Tachometer_UpdateDisplaySpeed
-    lwz r3, 0xc8(r31)
-    bl Tachometer_SetCoinCount
-    CarObject_Init_L_8004ED24:
-    bl OSGetTick
-    lis r5, 0x8000
-    lis r4, 0x431c
-    lwz r5, 0xf8(r5)
-    lis r0, 0x4330
-    subi r6, r4, 0x217d
-    lwz r7, 0x14(r1)
-    srwi r4, r5, 2
-    stw r0, 0x20(r1)
-    mulhwu r0, r6, r4
-    subf r3, r7, r3
-    lfd f2, lbl_806D27D0(r2)
-    slwi r4, r3, 3
-    lfs f0, lbl_806D27C8(r2)
-    lwz r3, 0x18(r1)
-    srwi r0, r0, 15
-    divwu r0, r4, r0
-    stw r0, 0x24(r1)
-    lfd f1, 0x20(r1)
-    fsubs f1, f1, f2
-    fdivs f1, f1, f0
-    bl Profiler_RecordFrame
-    lwz r0, g_gameMode(r13)
-    cmpwi r0, 0x1
-    beq CarObject_Init_L_8004EDA0
-    lwz r3, g_carObjectList(r13)
-    cmplwi r3, 0x0
-    bne CarObject_Init_L_8004ED98
-    li r3, 0x0
-    CarObject_Init_L_8004ED98:
-    li r0, 0x0
-    stw r0, 0x10(r3)
-    CarObject_Init_L_8004EDA0:
-    stw r31, g_playerCarObject(r13)
-    mr r3, r31
-    psq_l f31, 0x78(r1), 0, 0
-    lfd f31, 0x70(r1)
-    psq_l f30, 0x68(r1), 0, 0
-    lfd f30, 0x60(r1)
-    psq_l f29, 0x58(r1), 0, 0
-    lfd f29, 0x50(r1)
-    lmw r23, 0x2c(r1)
-    lwz r0, 0x84(r1)
-    mtlr r0
-    addi r1, r1, 0x80
-    blr
+#pragma exceptions off
+/* CarObject (KartItem) constructor: builds every subobject via the
+ * alloc-then-ctor null-guard pattern, registers the object in the global
+ * manager list, runs one MainUpdate frame under an inline ScopedTimer
+ * (id 0x28, struct at sp+0x14), and publishes itself as the player car.
+ * ScopedTimer dtor tail must stay one expression (no integer temp), see
+ * docs/notes/cw132-scopedtimer-phase2d-research.md. */
+CarObjInitView *CarObject_Init(CarObjInitView *self, float x, float y, float z,
+                               int kartSlot, void *a5, void *a6, void *a7,
+                               unsigned char isPlayer, int slotIdx, int camArg,
+                               unsigned char flag21) { /* 0x8004E618 size:0x7BC */
+    void *val;                     /* sp+0x10 */
+    StlListIterInit pos;           /* sp+0xc */
+    StlListIterInit itRet;         /* sp+0x8 */
+    struct {
+        unsigned int start;        /* sp+0x14 */
+        volatile unsigned int id;  /* sp+0x18 */
+    } tm;
+    ItemStateBlock *blk;
+    void *sub;
+    void *o2;  /* sound reload / driver / camera (r25 web family) */
+    void *o1;  /* movement / movement reload (r26 web family) */
+    void *ch;
+    void *p;
+    void *t;
+    int w;
+    unsigned char b;
+
+    clItemBoxResponder_Ctor(self, self->responder90);
+    WarpZone_VtableTrim((char *)self + 0xc);
+    self->vt0 = lbl_803F75F8;
+    self->vtC = (void *)(lbl_803F75F8 + 4);
+    self->kartSlot = kartSlot;
+    self->param14 = a5;
+    self->param18 = a6;
+    self->param1C = a7;
+    self->isPlayer = isPlayer;
+    self->flag21 = flag21;
+
+    ch = MemoryManager_AllocTagged(0x38, lbl_806D27DC, 0x180);
+    if (ch != 0) {
+        ch = KartAudioChannel_Init(ch, self->param14, isPlayer, isPlayer,
+                                   GetKartStartSlot(self->kartSlot), self->audioBlock60);
+    }
+    self->soundCtrl = ch;
+
+    o1 = MemoryManager_AllocTagged(0x324, lbl_806D27DC, 0x181);
+    if (o1 != 0) {
+        o2 = *(void * volatile *)&self->soundCtrl;
+        o1 = KartMovement_Init(o1, self->kartSlot,
+                               GetKartParamBlock(self->param14, self->param18, self->param1C, slotIdx),
+                               o2, x, y, z);
+    }
+    self->movement = o1;
+
+    o2 = MemoryManager_AllocTagged(0x384, lbl_806D27DC, 0x182);
+    if (o2 != 0) {
+        o2 = KartDriver_New_Full(o2, self->kartSlot, self->param14, self->audioBlock60,
+                                 GetKartStartSlot(self->kartSlot), 0, a7);
+    }
+    self->driver = o2;
+
+    p = MemoryManager_AllocTagged(0x30, lbl_806D27DC, 0x183);
+    if (p != 0) {
+        p = InputCmd_Init(p, 0x3c);
+    }
+    self->input30 = p;
+
+    p = MemoryManager_AllocTagged(0x154, lbl_806D27DC, 0x184);
+    if (p != 0) {
+        p = TornadoEffect_Ctor(p, 1, self->driver, self->param14,
+                               x, lbl_806D26EC, y, self->isPlayer);
+    }
+    self->effectObj = p;
+
+    o2 = MemoryManager_AllocTagged(0xd4, lbl_806D27DC, 0x185);
+    if (o2 != 0) {
+        o1 = *(void * volatile *)&self->movement;
+        o2 = PlayCamera_Init(o2, self->param14, a7, GetKartStartSlot(self->kartSlot),
+                             o1, isPlayer, camArg, 0, z);
+    }
+    self->camera38 = o2;
+
+    p = MemoryManager_AllocTagged(0x1c, lbl_806D27DC, 0x186);
+    if (p != 0) {
+        void *c = *(void * volatile *)&self->camera38;
+        p = KartEffectFadeTransit_Init(p, self->movement, self->effectObj, c, isPlayer);
+    }
+    self->fade3C = p;
+
+    blk = MemoryManager_AllocTagged(0x14, lbl_806D27DC, 0x187);
+    if (blk != 0) {
+        blk->owner = (struct KartItemOpsView *)self;
+        sub = Alloc(0x1c);
+        if (sub != 0) {
+            KartItemSubObject_Ctor(sub, self);
+        }
+        blk->guard = sub;
+        blk->curItemId = -1;
+        blk->activeId = -1;
+        blk->activeFlag = 0;
+    }
+    self->stateBlock = blk;
+
+    p = MemoryManager_AllocTagged(0x4c, lbl_806D27DC, 0x188);
+    if (p != 0) {
+        p = EffectSteering_Ctor(p, self, self->isPlayer);
+    }
+    self->steering44 = p;
+
+    p = MemoryManager_AllocTagged(0x28, lbl_806D27DC, 0x189);
+    if (p != 0) {
+        p = EffectSpeed_Init(p, self);
+    }
+    self->speed48 = p;
+
+    {
+        ItemEffectTable *tbl = MemoryManager_AllocTagged(0x58, lbl_806D27DC, 0x18a);
+        if (tbl != 0) {
+            void *st = self->steering44;
+            void *sq = self->speed48;
+            unsigned char ip = self->isPlayer;
+            tbl->owner = (struct KartItemOpsView *)self;
+            tbl->effectState = st;
+            tbl->mediaReq = sq;
+            tbl->laneKindC = ip;
+            tbl->intensity10 = lbl_806D26FC;
+            tbl->run14 = 0;
+            tbl->run1c = 0;
+            tbl->runBlend20 = lbl_806D26EC;
+            tbl->runBlend24 = lbl_806D26EC;
+            tbl->lanes[0].itemId = -1;
+            tbl->lanes[0].itemKind = -1;
+            tbl->lanes[0].state8 = 0;
+            tbl->lanes[0].stateC = 0;
+            tbl->lanes[0].state10 = 0;
+            tbl->lanes[0].blend = lbl_806D26FC;
+            tbl->lanes[1].itemId = -1;
+            tbl->lanes[1].itemKind = -1;
+            tbl->lanes[1].state8 = 0;
+            tbl->lanes[1].stateC = 0;
+            tbl->lanes[1].state10 = 0;
+            tbl->lanes[1].blend = lbl_806D26FC;
+        }
+        self->effectTable = tbl;
+    }
+
+    {
+        CarObjSecLaneInit *sec = MemoryManager_AllocTagged(0x10, lbl_806D27DC, 0x18c);
+        if (sec != 0) {
+            unsigned char ip2 = self->isPlayer;
+            sec->owner = self;
+            sec->isPlayer4 = ip2;
+            sec->itemId = -1;
+            sec->blend = lbl_806D26EC;
+        }
+        self->secondary = sec;
+    }
+
+    p = MemoryManager_AllocTagged(0x24, lbl_806D27DC, 0x18b);
+    w = (int)p;
+    if (w != 0) {
+        b = 0;
+        if (slotIdx == -1 && self->kartSlot == 4 && (int)g_gameMode == 1) {
+            b = 1;
+        }
+        w = (int)WarpAutoRun_Init(p, b != 0);
+    }
+    self->warpCtx54 = (void *)w;
+
+    p = MemoryManager_AllocTagged(0x58, lbl_806D27DC, 0x18d);
+    if (p != 0) {
+        p = fn_802091BC(p, -1, 0);
+    }
+    self->probe58 = p;
+
+    p = MemoryManager_AllocTagged(0x58, lbl_806D27DC, 0x18e);
+    if (p != 0) {
+        p = fn_802091BC(p, -1, 0);
+    }
+    self->probe5C = p;
+
+    self->spd9C = lbl_806D26EC;
+    self->spdA0 = lbl_806D26EC;
+    self->spdA4 = lbl_806D26EC;
+    self->gateA8 = 0;
+    self->progressSnapAC = lbl_806D26EC;
+    self->boostArmedB0 = 0;
+    self->perfectGateB1 = 0;
+    self->airTimerB4 = lbl_806D26EC;
+    self->airTimerB8 = lbl_806D26EC;
+    self->airCapBC = lbl_806D26FC;
+    self->valC0 = 0x3c;
+    self->valC4 = 0;
+    self->coinCountC8 = 0;
+    self->smoothBonusCC = lbl_806D26EC;
+    self->aiTimerD0 = 0;
+    self->flagD4 = 1;
+    self->flagD5 = 0;
+    self->aiTimerD8 = 0;
+    self->driftFlagDC = 0;
+    self->valE0 = 0;
+    self->boostBlendE4 = lbl_806D26FC;
+    self->valE8 = lbl_806D26EC;
+    self->valEC = 0;
+    self->prevSyncF0 = -1;
+    self->byteF4 = 0;
+    self->valF8 = 0;
+    self->fellOffFC = 0;
+    self->coinPenaltyFD = 1;
+    self->coinBonusEnabledFE = 1;
+    self->byteFF = 0;
+    self->val100 = 0;
+    b = 0;
+    if (slotIdx == -1 && self->kartSlot == 4 && (int)g_gameMode == 1) {
+        b = 1;
+    }
+    self->autoRun108 = b != 0;
+    self->byte109 = 0;
+    self->val10C = lbl_806D275C;
+    self->val110 = lbl_806D26EC;
+    self->val114 = lbl_806D26EC;
+
+    if (self->isPlayer == 1 && self->flag21 == 0) {
+        if (lbl_806D0051 == 0) {
+            StrPcb_ForceRun_Neutral(StrPcb_GetInstance());
+            StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
+        }
+        if (self->isPlayer != 0) {
+            StrPcb_SetCmdByte2d(StrPcb_GetInstance(), 0x28);
+            StrPcb_SetCmdByte2e(StrPcb_GetInstance(), 0x1e);
+            StrPcb_SetCounterField14(StrPcb_GetInstance(), 0);
+            StrPcb_SetCmdByte2f(StrPcb_GetInstance(), 0);
+        }
+    }
+
+    {
+        char *disp = (char *)self;
+        if (self != 0) {
+            disp += 0xc;
+        }
+        self->driver->dispatcher308 = disp;
+    }
+
+    {
+        unsigned int m = g_carObjectList;
+        if (m != g_carObjectList) {
+        } else if (m == 0) {
+            m = 0;
+        }
+        if (m == 0) {
+            CarObjectManager *mgr = Alloc(0x14);
+            if (mgr != 0) {
+                mgr->vtable = lbl_803F7690;
+                g_carObjectList = (unsigned int)mgr;
+                mgr->vtable = lbl_803F76A8;
+                StlList_InitEmpty(&mgr->list);
+                mgr->frame = 0;
+            }
+        }
+    }
+
+    g_carObjectCount = g_carObjectCount + 1;
+    if ((int)g_gameMode != 1) {
+        unsigned int l = g_carObjectList;
+        val = self;
+        if (l != g_carObjectList) {
+        } else if (l == 0) {
+            l = 0;
+        }
+        pos.node = (StlListNode *)(l + 8);
+        StlList_InsertBefore(&itRet, (StlList *)(l + 4), &pos, &val);
+    }
+
+    tm.id = 0x28;
+    tm.start = OSGetTick();
+    CarObject_MainUpdate(self, 0);
+    t = lbl_806D10A0;
+    if (t != lbl_806D10A0) {
+    } else if (t == 0) {
+        t = 0;
+    }
+    if (t != 0) {
+        TitleTracker_Empty_PreFinalizeHook((unsigned int)t, self->kartSlot);
+    }
+    if (self->isPlayer == 1) {
+        void *mv2;
+        float maxSpd;
+        mv2 = self->movement;
+        maxSpd = KartMovement_CalcMaxSpeed(mv2, 1);
+        Tachometer_UpdateDisplaySpeed(KartMovement_CalcCurrentSpeed(mv2, 1), maxSpd);
+        Tachometer_SetCoinCount(self->coinCountC8);
+    }
+    Profiler_RecordFrame(
+        tm.id,
+        (float)(((OSGetTick() - tm.start) * 8) /
+                ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
+            lbl_806D27C8);
+
+    if ((int)g_gameMode != 1) {
+        unsigned int l2 = g_carObjectList;
+        if (l2 != g_carObjectList) {
+        } else if (l2 == 0) {
+            l2 = 0;
+        }
+        ((CarObjectManager *)l2)->frame = 0;
+    }
+    g_playerCarObject = (unsigned int)self;
+    return self;
 }
+#pragma exceptions reset
 
 static inline float KartItem_CalcKeySpeedFromTable(KartMovementSpeedView *mv) {
     SpeedTableEntry *e;
@@ -10126,7 +10009,7 @@ asm void StlList_EraseRange(void *ret, StlList *l, StlListNode **beg, StlListNod
  * node if the obj copy throws). Approach B cannot emit any of this; approach A
  * excluded by the 14.1 mix rule (manual-extab asm fns precede). Same class as
  * dtor_8005278C/800528B0 (exceptions-on-eh-scaffolding-unpromotable). */
-asm void StlList_InsertBefore(void) { /* 0x80052684 size:0xA8 */
+asm void StlList_InsertBefore(StlListIterInit *ret, StlList *l, StlListIterInit *pos, void **val) { /* 0x80052684 size:0xA8 */
     nofralloc
     stwu r1, -0x40(r1)
     mflr r0

```

## Appendix B: trial matrix (14 builds)

| # | change | result |
|---|---|---|
| 1 | full C: typed protos, ScopedTimer recipe, uint-t idioms, view structs | 92.71 (507 insn aligned; clrlwi cascade, +1 callee-saved from addi-CSE) |
| 2 | disp+=0xc CSE break, u8 proto args, volatile snd/mv hoists, tbl/sec preloads, (int)g_gameMode, vt/glist store order, reverse local decl | 97.80 |
| 3 | o1={ch,mov,mvL} o2={snd,drv,cam} merge | 98.20 (only ch web wrong r25) |
| 4 | ch/mov own vars, o2 merged, mvL block-local | 98.14 (ch ok, drv/cam/mvL flip) |
| 5 | ch own, mov={mov,mvL}, o2 | 98.14 (ch/mov/snd flip, drv/cam/mvL ok) |
| 6 | b3 + decl order o2-first | 98.20 no-op |
| 7 | b3 + ch own declared last | 98.20 no-op |
| 8 | warp 2-var (p=q) + fade cam preload | 98.20 no-op (copy-prop both) |
| 9 | warp assign-in-cond + fade volatile cam read | 98.23 (fade arg order fixed; warp no-op) |
| 10 | blk/sub declared first | 98.23 no-op |
| 11 | warp flag via static inline helper | 97.67 REGRESSION (member-site flag zero-web coalescing broke) |
| 12 | warp shared int w (flag+result one var, Ghidra hint) | 98.23 no-op (copy-prop) |
| 13 | warp explicit post-call copy w=(int)p | 98.23 no-op |
| 14 | warp test-on-w | 98.23 (cmplwi->cmpwi only; confirms original tested int temp) |

## Appendix C: final residue dump (build 14, target || mine)

```
  41 mr. r26, r3        || mr. r25, r3          (ch web)
  47 mr r3, r26         || mr r3, r25
  52 mr r26, r3         || mr r25, r3
  53 stw r26, 0x24(r31) || stw r25, 0x24(r31)
 113 ---                || lwz r6, 0x14(r31)    (Tornado arg sched: lwz r6 vs li r4 swap)
 115 lwz r6, 0x14(r31)  || ---
 159 mr. r27, r3        || mr. r29, r3          (blk web)
 161-174 (blk/sub stores: r27/r23 vs r29/r27)
 249 mr. r0, r3         || cmpwi r3, 0x0        (warp new-expr join, -1 insn)
 266 mr r0, r3          || ---
 267 stw r0, 0x54(r31)  || stw r3, 0x54(r31)
 391 mr. r23, r3        || mr. r27, r3          (mgr web + lis/addi schedule cascade, 11 rows)
 394-405 (vtable lis/addi/store schedule follows mgr home)
```
