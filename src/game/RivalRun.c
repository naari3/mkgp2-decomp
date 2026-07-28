/* Exact asm_fn implementation for the remaining RivalRun unit members. */
/* Generated from the nine dtk auto_RivalRun_* target assembly fragments. */
/* Keep function/extab/extabindex order aligned with the target ranges. */

/* === extracted from auto_RivalRun_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_DebugVizPathFlush();
extern void CourseEnvironment_RenderObjects_Timed();
extern void DrawEffect_TickAndCull();
extern void ItemObjectManager_Render();
extern void KartItem_RenderPipelinedWithEffects();
extern void Object_RenderJObjIfWithinRange();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void clItemBoxManager_Draw();
extern void fn_8016B0C4();
extern void fn_80253448();
extern void fn_802535D4();
extern void fn_802C14B8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B8;

/* --- function index (1 fns, .text 0x8013558C..0x80135734) ---
 * [  0] 0x8013558C size:0x1A8   global RivalRun_Draw
 */

/* --- forward decls --- */
asm void RivalRun_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_Draw[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_Draw = {
    (void *)&RivalRun_Draw, 0x000001A8, (void *)extab_RivalRun_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_Draw(void) { /* 0x8013558C size:0x1A8 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lbz r0, 0x34(r3)
    cmplwi r0, 0x0
    beq RivalRun_Draw_L_80135720
    lwz r3, 0x14(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne RivalRun_Draw_L_801356EC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_801355DC
    li r3, 0x0
    RivalRun_Draw_L_801355DC:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x14(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl KartItem_RenderPipelinedWithEffects
    lwz r3, 0xc(r31)
    bl Object_RenderJObjIfWithinRange
    lwz r3, 0x10(r31)
    bl CourseEnvironment_RenderObjects_Timed
    lwz r3, 0x10(r31)
    bl Subsystem36c_DispatchPass2_Timed
    lwz r3, 0x30(r31)
    li r4, 0x0
    lwz r3, 0x4(r3)
    bl KartItem_RenderPipelinedWithEffects
    bl ItemObjectManager_Render
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_80135638
    li r3, 0x0
    RivalRun_Draw_L_80135638:
    bl clItemBoxManager_Draw
    lwz r3, 0x28(r31)
    lwz r4, lbl_806DC190(r2)
    bl fn_80253448
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_8013565C
    li r3, 0x0
    RivalRun_Draw_L_8013565C:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_80135670
    li r3, 0x0
    RivalRun_Draw_L_80135670:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x10(r31)
    bl Subsystem36c_DispatchPass4_Timed
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_8013568C
    li r3, 0x0
    RivalRun_Draw_L_8013568C:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_801356A4
    li r3, 0x0
    RivalRun_Draw_L_801356A4:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_801356BC
    li r3, 0x0
    RivalRun_Draw_L_801356BC:
    li r4, 0x6
    bl TransitionEffect_RenderPass
    lwz r4, lbl_806DC1B0(r2)
    lwz r0, lbl_806DC190(r2)
    lwz r3, 0x28(r31)
    or r4, r4, r0
    bl fn_80253448
    lwz r3, 0x14(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    RivalRun_Draw_L_801356EC:
    lwz r3, 0x28(r31)
    lwz r4, lbl_806DC1B8(r2)
    bl fn_80253448
    lwz r3, 0x28(r31)
    bl fn_802535D4
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne RivalRun_Draw_L_80135710
    li r3, 0x0
    RivalRun_Draw_L_80135710:
    li r4, 0x1
    bl TransitionEffect_RenderPass
    li r3, 0x7f
    bl fn_802C14B8
    RivalRun_Draw_L_80135720:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_RivalRun_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void CarObject_ApplyInput();
extern void CarObject_FrameUpdate();
extern void CarObject_GetRenderObj();
extern void ChallengeGoalCamera_Update();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void Fog_UpdateFromCourseScene3D();
extern void GetInputManager();
extern void GetRaceContextPtr();
extern void HUD_FrameUpdate();
extern void InputMgr_GetPlayer();
extern void IsRaceStarted();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern void KartDriver_GetKartRootMtx();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void KartMovement_SetSpeedScale();
extern void LakituStart_UpdateCountdown();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void NokoNokoChallenge_HandleBrakeInput();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void PathManager_UpdateAll();
extern void RivalRun_RivalAIUpdate();
extern void SetCoinCount();
extern void TransitionEffect_Tick();
extern void VfxSlotMgr_Update();
extern void clItemBoxManager_Update();
extern void fn_8016B32C();
extern void fn_8016C554();
extern void fn_801A1280();
extern void fn_80253C40();
extern void fn_80253C74();
extern void fn_80253FD8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_806D1290;
extern unsigned int lbl_806D7380;
extern unsigned int lbl_806D7384;
extern unsigned int lbl_806D7388;
extern unsigned int lbl_806D738C;
extern unsigned int lbl_806D7390;
extern unsigned int lbl_806D7394;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80677CA0[];
extern unsigned int lbl_80677CAC[];

/* --- function index (1 fns, .text 0x80135734..0x80135B7C) ---
 * [  0] 0x80135734 size:0x448   global RivalRun_Update
 */

/* --- forward decls --- */
asm void RivalRun_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_Update[8] = {
    0x18, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_Update = {
    (void *)&RivalRun_Update, 0x00000448, (void *)extab_RivalRun_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_Update(void) { /* 0x80135734 size:0x448 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stfd f30, 0x30(r1)
    psq_st f30, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    mr r31, r3
    lbz r0, 0x34(r3)
    cmplwi r0, 0x0
    bne RivalRun_Update_L_80135774
    li r0, 0x1
    stb r0, 0x34(r31)
    RivalRun_Update_L_80135774:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    mr r29, r3
    cmplwi r0, 0x1
    beq RivalRun_Update_L_8013586C
    lbz r0, lbl_806D1290(r13)
    cmplwi r0, 0x0
    bne RivalRun_Update_L_801357BC
    lwz r12, 0x0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fmr f31, f1
    b RivalRun_Update_L_801357C0
    RivalRun_Update_L_801357BC:
    lfs f31, lbl_806D7380(r2)
    RivalRun_Update_L_801357C0:
    lwz r12, 0x0(r29)
    mr r3, r29
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D7388(r2)
    fmr f30, f1
    li r30, 0x0
    fcmpo cr0, f31, f0
    bge RivalRun_Update_L_80135800
    fcmpo cr0, f30, f0
    bge RivalRun_Update_L_80135800
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq RivalRun_Update_L_80135800
    li r30, 0x1
    RivalRun_Update_L_80135800:
    mr r3, r31
    mr r4, r30
    bl NokoNokoChallenge_HandleBrakeInput
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne RivalRun_Update_L_8013581C
    lfs f31, lbl_806D7384(r2)
    RivalRun_Update_L_8013581C:
    bl IsRaceStarted
    mr r30, r3
    mr r3, r29
    lwz r12, 0x0(r29)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fmr f2, f31
    lwz r3, 0x8(r31)
    fmr f3, f30
    mr r4, r30
    bl CarObject_ApplyInput
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r31)
    li r5, 0x0
    lwz r4, 0x14(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    b RivalRun_Update_L_801358B8
    RivalRun_Update_L_8013586C:
    lfs f1, lbl_806D738C(r2)
    li r4, 0x1
    lwz r3, 0x8(r31)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D7390(r2)
    bl KartMovement_SetSpeedScale
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r5, r3
    lwz r3, 0x18(r31)
    lwz r4, 0x14(r31)
    bl ChallengeGoalCamera_Update
    RivalRun_Update_L_801358B8:
    lwz r3, 0x30(r31)
    bl RivalRun_RivalAIUpdate
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0x24(r31)
    bl PathManager_UpdateAll
    lwz r3, 0xc(r31)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x10(r31)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lis r4, lbl_80677CA0@ha
    lwz r3, 0x14(r31)
    addi r4, r4, lbl_80677CA0@l
    bl CObj_LoadProjMatrix
    lis r4, lbl_80677CAC@ha
    lwz r3, 0x14(r31)
    addi r4, r4, lbl_80677CAC@l
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lis r3, lbl_80677CAC@ha
    lis r4, lbl_80677CA0@ha
    addi r5, r3, lbl_80677CAC@l
    addi r3, r1, 0x14
    addi r7, r4, lbl_80677CA0@l
    lwz r10, 0x0(r5)
    lwz r9, 0x4(r5)
    addi r4, r1, 0x8
    lwz r8, 0x8(r5)
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r10, 0x8(r1)
    stw r9, 0xc(r1)
    stw r8, 0x10(r1)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    bl VfxSlotMgr_Update
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq RivalRun_Update_L_80135A0C
    lbz r0, 0x36(r31)
    cmplwi r0, 0x0
    bne RivalRun_Update_L_80135A0C
    lfs f1, g_raceTimeRemaining(r13)
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne RivalRun_Update_L_80135A0C
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    lwz r4, 0x30(r31)
    lwz r30, 0x240(r3)
    lwz r3, 0x4(r4)
    bl CarObject_GetRenderObj
    cmpwi r30, 0x0
    lwz r0, 0x240(r3)
    bgt RivalRun_Update_L_801359B8
    li r0, 0x1
    stb r0, 0x36(r31)
    stb r0, 0x37(r31)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnGoal
    b RivalRun_Update_L_80135A0C
    RivalRun_Update_L_801359B8:
    cmpwi r0, 0x0
    bgt RivalRun_Update_L_801359D8
    li r0, 0x1
    stb r0, 0x36(r31)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    b RivalRun_Update_L_80135A0C
    RivalRun_Update_L_801359D8:
    lfs f2, g_raceTimeRemaining(r13)
    lfs f1, lbl_806D7394(r2)
    lfs f0, lbl_806D738C(r2)
    fsubs f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, g_raceTimeRemaining(r13)
    bge RivalRun_Update_L_80135A0C
    stfs f0, g_raceTimeRemaining(r13)
    li r0, 0x1
    stb r0, 0x36(r31)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    RivalRun_Update_L_80135A0C:
    bl fn_801A1280
    lwz r3, 0x28(r31)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x28(r31)
    bl HUD_FrameUpdate
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne RivalRun_Update_L_80135A34
    li r3, 0x0
    RivalRun_Update_L_80135A34:
    bl TransitionEffect_Tick
    lbz r0, 0x36(r31)
    cmplwi r0, 0x0
    beq RivalRun_Update_L_80135B28
    lwz r0, 0x38(r31)
    cmpwi r0, 0x0
    bne RivalRun_Update_L_80135B00
    lbz r0, 0x37(r31)
    cmplwi r0, 0x0
    beq RivalRun_Update_L_80135A98
    bl NokoNokoChallenge_GetCoinDivisor
    lwz r3, 0x0(r3)
    bl SetCoinCount
    mr r3, r31
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x28(r31)
    li r4, 0x1
    li r6, 0xf
    bl fn_80253C74
    li r3, 0x1
    bl fn_8016C554
    b RivalRun_Update_L_80135ACC
    RivalRun_Update_L_80135A98:
    li r3, 0x0
    bl SetCoinCount
    mr r3, r31
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x28(r31)
    li r4, 0x0
    li r6, 0x0
    bl fn_80253C74
    li r3, 0x0
    bl fn_8016C554
    RivalRun_Update_L_80135ACC:
    lbz r5, 0x37(r31)
    li r0, 0xf
    mr r3, r31
    neg r4, r5
    or r4, r4, r5
    srawi r4, r4, 31
    and r4, r0, r4
    bl NokoNokoChallenge_SaveResult
    li r3, 0x1
    li r0, 0x0
    stb r3, g_raceEnded(r13)
    stb r0, g_lakituStartAnimDone(r13)
    b RivalRun_Update_L_80135B1C
    RivalRun_Update_L_80135B00:
    lwz r3, 0x28(r31)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq RivalRun_Update_L_80135B1C
    mr r3, r31
    bl NokoNokoChallenge_TransitionToResult
    b RivalRun_Update_L_80135B50
    RivalRun_Update_L_80135B1C:
    lwz r3, 0x38(r31)
    addi r0, r3, 0x1
    stw r0, 0x38(r31)
    RivalRun_Update_L_80135B28:
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne RivalRun_Update_L_80135B38
    li r3, 0x0
    RivalRun_Update_L_80135B38:
    bl clItemBoxManager_Update
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq RivalRun_Update_L_80135B4C
    bl fn_8016B32C
    RivalRun_Update_L_80135B4C:
    li r3, -0x2
    RivalRun_Update_L_80135B50:
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    psq_l f30, 0x38(r1), 0, 0
    lfd f30, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r0, 0x54(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

/* === extracted from auto_RivalRun_RivalAIUpda_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CarObject_ApplyInput();
extern void CarObject_FrameUpdate();
extern void CarObject_GetRenderObj();
extern void CarObject_IsAirborne();
extern void IsRaceStarted();
extern void ItemEffectBus_OrMask();
extern void KartDriver_GetKartRootMtx();
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartItem_TryArmBoostOnLanding();
extern void RivalRun_RivalTactics();
extern void RivalRun_UpdatePathFollower();
extern void Saturate_Double();
extern void Vec3_Dot();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void WarpDashMgr_GetInstance();
extern void WarpZone_FindContaining();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CF610;
extern unsigned int lbl_806CF614;
extern unsigned int lbl_806CF618;
extern unsigned int lbl_806CF61C;
extern unsigned int lbl_806CF620;
extern unsigned int lbl_806D7384;
extern unsigned int lbl_806D738C;
extern unsigned int lbl_806D7398;
extern unsigned int lbl_806D739C;

/* --- function index (1 fns, .text 0x80135B7C..0x80135EFC) ---
 * [  0] 0x80135B7C size:0x380   global RivalRun_RivalAIUpdate
 */

/* --- forward decls --- */
asm void RivalRun_RivalAIUpdate(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_RivalAIUpdate[8] = {
    0x10, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_RivalAIUpdate = {
    (void *)&RivalRun_RivalAIUpdate, 0x00000380, (void *)extab_RivalRun_RivalAIUpdate
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_RivalAIUpdate(void) { /* 0x80135B7C size:0x380 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stfd f30, 0x50(r1)
    psq_st f30, 0x58(r1), 0, 0
    stfd f29, 0x40(r1)
    psq_st f29, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    lfs f30, lbl_806D738C(r2)
    mr r30, r3
    lwz r3, 0x4(r3)
    fmr f29, f30
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r31, r3
    lwz r3, 0x4(r30)
    bl KartItem_GetCurrentSpeedWithBonus
    fmr f31, f1
    mr r3, r30
    bl RivalRun_RivalTactics
    addi r3, r30, 0x28
    addi r4, r30, 0x8
    addi r5, r1, 0x20
    bl Vec3_Subtract
    lfs f0, lbl_806D738C(r2)
    addi r3, r1, 0x20
    mr r4, r3
    stfs f0, 0x24(r1)
    bl Vec3_Normalize
    lfs f0, 0x0(r31)
    addi r3, r1, 0x8
    lfs f1, lbl_806D738C(r2)
    mr r4, r3
    stfs f0, 0x8(r1)
    stfs f1, 0xc(r1)
    lfs f0, 0x20(r31)
    stfs f0, 0x10(r1)
    lfs f0, 0x8(r31)
    stfs f0, 0x14(r1)
    stfs f1, 0x18(r1)
    lfs f0, 0x28(r31)
    stfs f0, 0x1c(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x14
    mr r4, r3
    bl Vec3_Normalize
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne RivalRun_RivalAIUpdate_L_80135DE8
    lwz r3, 0x3c(r30)
    cmpwi r3, 0x0
    ble RivalRun_RivalAIUpdate_L_80135C64
    subi r0, r3, 0x1
    stw r0, 0x3c(r30)
    RivalRun_RivalAIUpdate_L_80135C64:
    addi r3, r1, 0x20
    addi r4, r1, 0x8
    bl Vec3_Dot
    fmr f29, f1
    addi r3, r1, 0x20
    addi r4, r1, 0x14
    bl Vec3_Dot
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne RivalRun_RivalAIUpdate_L_80135CA4
    fcmpo cr0, f29, f0
    ble RivalRun_RivalAIUpdate_L_80135CA0
    lfs f29, lbl_806D7384(r2)
    b RivalRun_RivalAIUpdate_L_80135CA4
    RivalRun_RivalAIUpdate_L_80135CA0:
    lfs f29, lbl_806D7398(r2)
    RivalRun_RivalAIUpdate_L_80135CA4:
    fneg f1, f29
    lfs f0, lbl_806CF610(r13)
    lfs f2, lbl_806D7398(r2)
    lfs f3, lbl_806D7384(r2)
    fmuls f1, f1, f0
    bl Saturate_Double
    lfs f2, lbl_806CF618(r13)
    fmr f30, f1
    lfs f3, lbl_806CF614(r13)
    fsubs f2, f31, f2
    lfs f0, lbl_806CF61C(r13)
    fcmpo cr0, f30, f3
    fdivs f1, f2, f0
    ble RivalRun_RivalAIUpdate_L_80135CF8
    fsubs f0, f30, f3
    lfs f3, lbl_806D7384(r2)
    lfs f2, lbl_806D738C(r2)
    fnmsubs f1, f1, f0, f3
    bl Saturate_Double
    fmr f29, f1
    b RivalRun_RivalAIUpdate_L_80135D24
    RivalRun_RivalAIUpdate_L_80135CF8:
    fneg f0, f3
    fcmpo cr0, f30, f0
    bge RivalRun_RivalAIUpdate_L_80135D20
    fadds f0, f30, f3
    lfs f3, lbl_806D7384(r2)
    lfs f2, lbl_806D738C(r2)
    fmadds f1, f1, f0, f3
    bl Saturate_Double
    fmr f29, f1
    b RivalRun_RivalAIUpdate_L_80135D24
    RivalRun_RivalAIUpdate_L_80135D20:
    lfs f29, lbl_806D7384(r2)
    RivalRun_RivalAIUpdate_L_80135D24:
    lfs f0, 0x4c(r30)
    lwz r0, 0x34(r30)
    fmuls f29, f29, f0
    cmpwi r0, 0x0
    bne RivalRun_RivalAIUpdate_L_80135DA4
    lfs f0, lbl_806D739C(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalAIUpdate_L_80135DE8
    lwz r3, 0x4(r30)
    bl CarObject_IsAirborne
    clrlwi. r0, r3, 24
    bne RivalRun_RivalAIUpdate_L_80135DE8
    lfs f0, lbl_806CF620(r13)
    fcmpo cr0, f30, f0
    cror eq, gt, eq
    beq RivalRun_RivalAIUpdate_L_80135D74
    fneg f0, f0
    fcmpo cr0, f30, f0
    cror eq, lt, eq
    bne RivalRun_RivalAIUpdate_L_80135DE8
    RivalRun_RivalAIUpdate_L_80135D74:
    lwz r3, 0x4(r30)
    li r4, 0x1
    bl KartItem_TryArmBoostOnLanding
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f30, f0
    ble RivalRun_RivalAIUpdate_L_80135D98
    li r0, 0x1
    stw r0, 0x34(r30)
    b RivalRun_RivalAIUpdate_L_80135DE8
    RivalRun_RivalAIUpdate_L_80135D98:
    li r0, -0x1
    stw r0, 0x34(r30)
    b RivalRun_RivalAIUpdate_L_80135DE8
    RivalRun_RivalAIUpdate_L_80135DA4:
    cmpwi r0, 0x1
    bne RivalRun_RivalAIUpdate_L_80135DC4
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f30, f0
    cror eq, lt, eq
    bne RivalRun_RivalAIUpdate_L_80135DC4
    li r0, 0x0
    stw r0, 0x34(r30)
    RivalRun_RivalAIUpdate_L_80135DC4:
    lwz r0, 0x34(r30)
    cmpwi r0, -0x1
    bne RivalRun_RivalAIUpdate_L_80135DE8
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f30, f0
    cror eq, gt, eq
    bne RivalRun_RivalAIUpdate_L_80135DE8
    li r0, 0x0
    stw r0, 0x34(r30)
    RivalRun_RivalAIUpdate_L_80135DE8:
    lwz r0, 0x3c(r30)
    cmpwi r0, 0x0
    beq RivalRun_RivalAIUpdate_L_80135E14
    bl IsRaceStarted
    lfs f1, lbl_806D738C(r2)
    mr r4, r3
    lwz r3, 0x4(r30)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    b RivalRun_RivalAIUpdate_L_80135E30
    RivalRun_RivalAIUpdate_L_80135E14:
    bl IsRaceStarted
    fmr f1, f30
    mr r4, r3
    fmr f2, f29
    lwz r3, 0x4(r30)
    lfs f3, lbl_806D738C(r2)
    bl CarObject_ApplyInput
    RivalRun_RivalAIUpdate_L_80135E30:
    lwz r3, 0x4(r30)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r3, 0x304(r3)
    li r6, 0x0
    lis r5, 0x80
    bl ItemEffectBus_OrMask
    lfs f0, 0xc(r31)
    li r3, 0x0
    stfs f0, 0x8(r30)
    lfs f0, 0x1c(r31)
    stfs f0, 0xc(r30)
    lfs f0, 0x2c(r31)
    stfs f0, 0x10(r30)
    bl WarpDashMgr_GetInstance
    lfs f1, 0x8(r30)
    lfs f2, 0xc(r30)
    lfs f3, 0x10(r30)
    bl WarpZone_FindContaining
    cmpwi r3, -0x1
    beq RivalRun_RivalAIUpdate_L_80135EB8
    lwz r4, 0x20(r30)
    lwz r3, 0x8(r4)
    addi r0, r3, 0x1
    cmpwi r0, 0x2
    stw r0, 0x8(r4)
    blt RivalRun_RivalAIUpdate_L_80135EAC
    li r0, 0x0
    stw r0, 0x8(r4)
    RivalRun_RivalAIUpdate_L_80135EAC:
    li r0, 0x0
    stw r0, 0xc(r4)
    b RivalRun_RivalAIUpdate_L_80135ECC
    RivalRun_RivalAIUpdate_L_80135EB8:
    lwz r3, 0x20(r30)
    addi r4, r30, 0x8
    stfs f31, 0x28(r3)
    lwz r3, 0x20(r30)
    bl RivalRun_UpdatePathFollower
    RivalRun_RivalAIUpdate_L_80135ECC:
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 0x58(r1), 0, 0
    lfd f30, 0x50(r1)
    psq_l f29, 0x48(r1), 0, 0
    lfd f29, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r0, 0x74(r1)
    lwz r30, 0x38(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

/* === extracted from auto_RivalRun_UpdatePathF_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Dot();
extern void Vec3_Normalize();
extern void fn_8025E30C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D738C;
extern unsigned int lbl_806D73A0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8035C1E4[];

/* --- function index (1 fns, .text 0x80135EFC..0x80136148) ---
 * [  0] 0x80135EFC size:0x24C   global RivalRun_UpdatePathFollower
 */

/* --- forward decls --- */
asm void RivalRun_UpdatePathFollower(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_UpdatePathFollower[8] = {
    0x39, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_UpdatePathFollower = {
    (void *)&RivalRun_UpdatePathFollower, 0x0000024C, (void *)extab_RivalRun_UpdatePathFollower
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_UpdatePathFollower(void) { /* 0x80135EFC size:0x24C */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stfd f30, 0x60(r1)
    psq_st f30, 0x68(r1), 0, 0
    stfd f29, 0x50(r1)
    psq_st f29, 0x58(r1), 0, 0
    stfd f28, 0x40(r1)
    psq_st f28, 0x48(r1), 0, 0
    stmw r25, 0x24(r1)
    mr r30, r3
    lis r3, lbl_8035C1E4@ha
    lwz r0, 0x4(r30)
    addi r5, r3, lbl_8035C1E4@l
    lwz r3, 0x8(r30)
    mr r25, r4
    slwi r4, r0, 4
    lbz r0, 0x0(r30)
    add r4, r5, r4
    slwi r5, r3, 3
    add r3, r4, r5
    cmplwi r0, 0x0
    lwzx r31, r4, r5
    lwz r26, 0x4(r3)
    beq RivalRun_UpdatePathFollower_L_80135FE4
    li r28, 0x0
    lfs f31, lbl_806D738C(r2)
    stb r28, 0x0(r30)
    mr r29, r28
    lfs f30, 0x0(r25)
    mr r27, r31
    lfs f29, 0x4(r25)
    lfs f28, 0x8(r25)
    b RivalRun_UpdatePathFollower_L_80135FD8
    RivalRun_UpdatePathFollower_L_80135F8C:
    lfs f0, 0x0(r27)
    addi r3, r1, 0x8
    fsubs f0, f0, f30
    stfs f0, 0x8(r1)
    lfs f0, 0x4(r27)
    fsubs f0, f0, f29
    stfs f0, 0xc(r1)
    lfs f0, 0x8(r27)
    fsubs f0, f0, f28
    stfs f0, 0x10(r1)
    bl fn_8025E30C
    cmpwi r29, 0x0
    beq RivalRun_UpdatePathFollower_L_80135FC8
    fcmpo cr0, f1, f31
    bge RivalRun_UpdatePathFollower_L_80135FD0
    RivalRun_UpdatePathFollower_L_80135FC8:
    mr r28, r29
    fmr f31, f1
    RivalRun_UpdatePathFollower_L_80135FD0:
    addi r27, r27, 0xc
    addi r29, r29, 0x1
    RivalRun_UpdatePathFollower_L_80135FD8:
    cmpw r29, r26
    blt RivalRun_UpdatePathFollower_L_80135F8C
    stw r28, 0xc(r30)
    RivalRun_UpdatePathFollower_L_80135FE4:
    lfs f28, 0x0(r25)
    subi r29, r26, 0x1
    lfs f29, lbl_806D738C(r2)
    lfs f30, 0x8(r25)
    lfs f31, lbl_806D73A0(r2)
    RivalRun_UpdatePathFollower_L_80135FF8:
    lwz r0, 0xc(r30)
    mulli r0, r0, 0xc
    lfsx f0, r31, r0
    stfs f0, 0x10(r30)
    stfs f29, 0x14(r30)
    lwz r0, 0xc(r30)
    mulli r3, r0, 0xc
    addi r0, r3, 0x8
    lfsx f0, r31, r0
    stfs f0, 0x18(r30)
    lwz r0, 0xc(r30)
    cmpw r0, r29
    bne RivalRun_UpdatePathFollower_L_8013605C
    mulli r0, r0, 0xc
    add r3, r31, r0
    lfs f1, 0x0(r3)
    lfs f0, -0xc(r3)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r30)
    stfs f29, 0x20(r30)
    lfs f1, 0x8(r3)
    lfs f0, -0x4(r3)
    fsubs f0, f1, f0
    stfs f0, 0x24(r30)
    b RivalRun_UpdatePathFollower_L_80136088
    RivalRun_UpdatePathFollower_L_8013605C:
    mulli r0, r0, 0xc
    add r3, r31, r0
    lfs f1, 0xc(r3)
    lfs f0, 0x0(r3)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r30)
    stfs f29, 0x20(r30)
    lfs f1, 0x14(r3)
    lfs f0, 0x8(r3)
    fsubs f0, f1, f0
    stfs f0, 0x24(r30)
    RivalRun_UpdatePathFollower_L_80136088:
    addi r3, r30, 0x1c
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x10(r30)
    addi r3, r1, 0x14
    addi r4, r30, 0x1c
    fsubs f0, f0, f28
    stfs f29, 0x18(r1)
    stfs f0, 0x14(r1)
    lfs f0, 0x18(r30)
    fsubs f0, f0, f30
    stfs f0, 0x1c(r1)
    bl Vec3_Dot
    lwz r3, 0xc(r30)
    cmpw r3, r29
    bne RivalRun_UpdatePathFollower_L_80136100
    lfs f0, 0x28(r30)
    fcmpo cr0, f1, f0
    bge RivalRun_UpdatePathFollower_L_80136114
    lfs f0, lbl_806D73A0(r2)
    lfs f2, 0x1c(r30)
    fsubs f3, f0, f1
    lfs f0, 0x10(r30)
    fmadds f0, f2, f3, f0
    stfs f0, 0x10(r30)
    lfs f1, 0x24(r30)
    lfs f0, 0x18(r30)
    fmadds f0, f1, f3, f0
    stfs f0, 0x18(r30)
    b RivalRun_UpdatePathFollower_L_80136114
    RivalRun_UpdatePathFollower_L_80136100:
    fcmpo cr0, f1, f31
    bge RivalRun_UpdatePathFollower_L_80136114
    addi r0, r3, 0x1
    stw r0, 0xc(r30)
    b RivalRun_UpdatePathFollower_L_80135FF8
    RivalRun_UpdatePathFollower_L_80136114:
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    psq_l f28, 0x48(r1), 0, 0
    lfd f28, 0x40(r1)
    lmw r25, 0x24(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

/* === extracted from auto_RivalRun_RivalTactic_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CarObject_ApplyDriftBoost();
extern void CarObject_GetRenderObj();
extern void GetRaceContextPtr();
extern void IsRaceStarted();
extern void KartDriver_GetKartRootMtx();
extern void KartItem_CancelAndQueueDefault();
extern void KartItem_CancelIfNotForced();
extern void KartMovement_EquipItem();
extern void OSGetTick();
extern void RaceContextSlot_GetIfAlive();
extern void RenderObj_UseItem();
extern void RivalRun_CalcPathDistance();
extern void Terrain_RaycastWall();
extern void Vec3_Dot();
extern void Vec3_Normalize();
extern void Vec3_Subtract();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceEnded;
extern unsigned int lbl_806D738C;
extern unsigned int lbl_806D73A4;
extern unsigned int lbl_806D73A8;
extern unsigned int lbl_806D73AC;
extern unsigned int lbl_806D73B0;
extern unsigned int lbl_806D73B4;
extern unsigned int lbl_806D73B8;
extern unsigned int lbl_806D73BC;
extern unsigned int lbl_806D73C0;
extern unsigned int lbl_806D73C4;
extern unsigned int lbl_806D73C8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80495994[];

/* --- function index (1 fns, .text 0x80136148..0x801367F4) ---
 * [  0] 0x80136148 size:0x6AC   global RivalRun_RivalTactics
 */

/* --- forward decls --- */
asm void RivalRun_RivalTactics(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_RivalTactics[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_RivalTactics = {
    (void *)&RivalRun_RivalTactics, 0x000006AC, (void *)extab_RivalRun_RivalTactics
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_RivalTactics(void) { /* 0x80136148 size:0x6AC */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stw r31, 0x7c(r1)
    stw r30, 0x78(r1)
    mr r30, r3
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq RivalRun_RivalTactics_L_801367D4
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_801367D4
    lwz r0, 0x3c(r30)
    cmpwi r0, 0x0
    ble RivalRun_RivalTactics_L_80136190
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136190:
    lbz r0, 0x38(r30)
    cmplwi r0, 0x0
    beq RivalRun_RivalTactics_L_801361C0
    lwz r5, 0x0(r30)
    li r4, 0x4
    lwz r3, 0x4(r30)
    lfs f1, 0x4(r5)
    bl CarObject_ApplyDriftBoost
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_801361C0
    li r0, 0x0
    stb r0, 0x38(r30)
    RivalRun_RivalTactics_L_801361C0:
    lwz r3, 0x20(r30)
    lfs f0, 0x10(r3)
    stfs f0, 0x28(r30)
    lfs f0, 0x14(r3)
    stfs f0, 0x2c(r30)
    lfs f0, 0x18(r3)
    stfs f0, 0x30(r30)
    lwz r3, 0x20(r30)
    lfs f0, 0x1c(r3)
    stfs f0, 0x38(r1)
    fneg f0, f0
    lfs f2, 0x20(r3)
    stfs f2, 0x3c(r1)
    lfs f1, 0x24(r3)
    stfs f1, 0x40(r1)
    stfs f1, 0x44(r1)
    stfs f2, 0x48(r1)
    stfs f0, 0x4c(r1)
    lwz r0, 0x50(r30)
    cmplwi r0, 0x0
    beq RivalRun_RivalTactics_L_801367D4
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r4, 0x50(r30)
    lwz r0, 0x24c(r3)
    lwz r3, 0x24c(r4)
    cmpw r3, r0
    bne RivalRun_RivalTactics_L_801367D4
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r31, r3
    lwz r3, 0x50(r30)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r31)
    addi r4, r1, 0x5c
    addi r5, r1, 0x50
    stfs f0, 0x50(r1)
    lfs f0, 0x1c(r31)
    stfs f0, 0x54(r1)
    lfs f0, 0x2c(r31)
    stfs f0, 0x58(r1)
    lfs f0, 0xc(r3)
    stfs f0, 0x5c(r1)
    lfs f0, 0x1c(r3)
    stfs f0, 0x60(r1)
    lfs f0, 0x2c(r3)
    stfs f0, 0x64(r1)
    lwz r3, 0x20(r30)
    bl RivalRun_CalcPathDistance
    fmr f31, f1
    addi r3, r1, 0x5c
    addi r4, r1, 0x50
    addi r5, r1, 0x38
    bl Vec3_Subtract
    addi r3, r1, 0x38
    addi r4, r1, 0x2c
    bl Vec3_Normalize
    addi r3, r1, 0x38
    addi r4, r1, 0x44
    bl Vec3_Dot
    lfs f2, lbl_806D73A4(r2)
    fcmpo cr0, f31, f2
    ble RivalRun_RivalTactics_L_801362D0
    lwz r3, 0x0(r30)
    lfs f0, 0x10(r3)
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_801362D0:
    lfs f0, lbl_806D73A8(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136304
    fsubs f2, f31, f0
    lwz r3, 0x0(r30)
    lfs f0, lbl_806D73AC(r2)
    lfs f3, 0xc(r3)
    fdivs f2, f2, f0
    lfs f0, 0x10(r3)
    fsubs f0, f0, f3
    fmadds f0, f2, f0, f3
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_80136304:
    lfs f0, lbl_806D73B0(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136320
    lwz r3, 0x0(r30)
    lfs f0, 0xc(r3)
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_80136320:
    lfs f0, lbl_806D73B4(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136354
    fadds f2, f2, f31
    lwz r3, 0x0(r30)
    lfs f0, lbl_806D73AC(r2)
    lfs f3, 0x8(r3)
    fdivs f2, f2, f0
    lfs f0, 0xc(r3)
    fsubs f0, f0, f3
    fmadds f0, f2, f0, f3
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_80136354:
    lwz r3, 0x0(r30)
    lfs f0, 0x8(r3)
    stfs f0, 0x4c(r30)
    RivalRun_RivalTactics_L_80136360:
    lwz r4, 0x20(r30)
    lfs f0, lbl_806D73AC(r2)
    lwz r3, 0x4(r4)
    fcmpo cr0, f31, f0
    mr r5, r3
    bgt RivalRun_RivalTactics_L_80136384
    lfs f0, lbl_806D73B8(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_801363B4
    RivalRun_RivalTactics_L_80136384:
    lwz r0, 0x24(r30)
    cmpwi r0, 0x0
    bne RivalRun_RivalTactics_L_80136414
    lwz r0, 0x4(r4)
    cmpwi r0, 0x1
    beq RivalRun_RivalTactics_L_801363A8
    li r0, 0x1
    stw r0, 0x4(r4)
    stb r0, 0x0(r4)
    RivalRun_RivalTactics_L_801363A8:
    li r0, 0x78
    stw r0, 0x24(r30)
    b RivalRun_RivalTactics_L_80136414
    RivalRun_RivalTactics_L_801363B4:
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136414
    fcmpo cr0, f1, f0
    ble RivalRun_RivalTactics_L_801363E8
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f1, f0
    bge RivalRun_RivalTactics_L_801363E8
    cmpwi r3, 0x2
    bne RivalRun_RivalTactics_L_801363E4
    subi r5, r3, 0x1
    b RivalRun_RivalTactics_L_801363E8
    RivalRun_RivalTactics_L_801363E4:
    addi r5, r3, 0x1
    RivalRun_RivalTactics_L_801363E8:
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f1, f0
    bge RivalRun_RivalTactics_L_80136414
    lfs f0, lbl_806D73C0(r2)
    fcmpo cr0, f1, f0
    ble RivalRun_RivalTactics_L_80136414
    cmpwi r5, 0x0
    bne RivalRun_RivalTactics_L_80136410
    addi r5, r5, 0x1
    b RivalRun_RivalTactics_L_80136414
    RivalRun_RivalTactics_L_80136410:
    subi r5, r5, 0x1
    RivalRun_RivalTactics_L_80136414:
    lwz r3, 0x24(r30)
    cmpwi r3, 0x0
    ble RivalRun_RivalTactics_L_8013642C
    subi r0, r3, 0x1
    stw r0, 0x24(r30)
    b RivalRun_RivalTactics_L_80136468
    RivalRun_RivalTactics_L_8013642C:
    lwz r3, 0x20(r30)
    lwz r0, 0x4(r3)
    cmpw r5, r0
    beq RivalRun_RivalTactics_L_80136468
    cmpwi r5, 0x0
    blt RivalRun_RivalTactics_L_80136460
    cmpwi r5, 0x3
    bge RivalRun_RivalTactics_L_80136460
    cmpw r0, r5
    beq RivalRun_RivalTactics_L_80136460
    stw r5, 0x4(r3)
    li r0, 0x1
    stb r0, 0x0(r3)
    RivalRun_RivalTactics_L_80136460:
    li r0, 0x78
    stw r0, 0x24(r30)
    RivalRun_RivalTactics_L_80136468:
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x0
    bne RivalRun_RivalTactics_L_801367D4
    lwz r3, 0x40(r30)
    cmpwi r3, 0x0
    ble RivalRun_RivalTactics_L_8013648C
    subi r0, r3, 0x1
    stw r0, 0x40(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_8013648C:
    lwz r0, 0x44(r30)
    cmpwi r0, 0x0
    bne RivalRun_RivalTactics_L_80136618
    lfs f0, lbl_806D73C0(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_801364B0
    li r0, 0x32
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_801364B0:
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_801365C4
    lfs f0, lbl_806D73A8(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_80136548
    bl OSGetTick
    lis r4, 0x8000
    lwz r7, 0x0(r30)
    lwz r5, 0xf8(r4)
    lis r4, 0x1062
    addi r6, r4, 0x4dd3
    lwz r0, 0x24(r7)
    srwi r4, r5, 2
    lwz r8, 0x20(r7)
    mulhwu r5, r6, r4
    lwz r6, 0x1c(r7)
    add r0, r8, r0
    add r4, r6, r0
    srwi r0, r5, 6
    divwu r3, r3, r0
    divw r0, r3, r4
    mullw r0, r0, r4
    subf r0, r0, r3
    cmpw r0, r6
    bge RivalRun_RivalTactics_L_80136524
    li r0, 0x3e
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_80136524:
    subf r0, r6, r0
    cmpw r0, r8
    bge RivalRun_RivalTactics_L_8013653C
    li r0, 0x6c
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_8013653C:
    li r0, 0x3d
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_80136548:
    bl OSGetTick
    lis r4, 0x8000
    lwz r7, 0x0(r30)
    lwz r5, 0xf8(r4)
    lis r4, 0x1062
    addi r6, r4, 0x4dd3
    lwz r0, 0x30(r7)
    srwi r4, r5, 2
    lwz r8, 0x2c(r7)
    mulhwu r5, r6, r4
    lwz r6, 0x28(r7)
    add r0, r8, r0
    add r4, r6, r0
    srwi r0, r5, 6
    divwu r3, r3, r0
    divw r0, r3, r4
    mullw r0, r0, r4
    subf r0, r0, r3
    cmpw r0, r6
    bge RivalRun_RivalTactics_L_801365A4
    li r0, 0x3e
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_801365A4:
    subf r0, r6, r0
    cmpw r0, r8
    bge RivalRun_RivalTactics_L_801365BC
    li r0, 0x6c
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_801365BC:
    li r0, 0x3d
    stw r0, 0x44(r30)
    RivalRun_RivalTactics_L_801365C4:
    lwz r0, 0x44(r30)
    cmpwi r0, 0x0
    beq RivalRun_RivalTactics_L_801367D4
    bl GetRaceContextPtr
    lwz r4, 0x1c(r30)
    bl RaceContextSlot_GetIfAlive
    li r0, 0x0
    stw r0, 0x90(r3)
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r4, 0x44(r30)
    bl KartMovement_EquipItem
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_8013660C
    lwz r3, 0x0(r30)
    lwz r0, 0x18(r3)
    stw r0, 0x48(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_8013660C:
    li r0, 0x0
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136618:
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_801366AC
    lfs f0, lbl_806D73C0(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_801366AC
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    bl KartItem_CancelIfNotForced
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    bl KartItem_CancelAndQueueDefault
    li r0, 0x0
    stw r0, 0x44(r30)
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x1062
    lwz r0, 0xf8(r4)
    lis r5, lbl_80495994@ha
    lwz r4, 0x0(r30)
    addi r6, r6, 0x4dd3
    srwi r0, r0, 2
    addi r5, r5, lbl_80495994@l
    mulhwu r0, r6, r0
    lfs f0, lbl_806D73C4(r2)
    lwz r4, 0x14(r4)
    srwi r0, r0, 6
    divwu r0, r3, r0
    clrlslwi r0, r0, 26, 2
    lfsx f1, r5, r0
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x68(r1)
    lwz r0, 0x6c(r1)
    add r0, r4, r0
    stw r0, 0x40(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_801366AC:
    lwz r3, 0x48(r30)
    cmpwi r3, 0x0
    ble RivalRun_RivalTactics_L_80136758
    subi r0, r3, 0x1
    addi r3, r1, 0x20
    stw r0, 0x48(r30)
    mr r4, r3
    lfs f0, lbl_806D738C(r2)
    lfs f1, 0x8(r31)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    lfs f0, 0x28(r31)
    stfs f0, 0x28(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x2c
    addi r4, r1, 0x20
    bl Vec3_Dot
    lfs f0, lbl_806D73C8(r2)
    fcmpo cr0, f1, f0
    ble RivalRun_RivalTactics_L_80136708
    li r0, 0x0
    stw r0, 0x48(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136708:
    lwz r0, 0x44(r30)
    cmpwi r0, 0x32
    beq RivalRun_RivalTactics_L_801367D4
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_801367D4
    addi r3, r1, 0x5c
    addi r4, r1, 0x50
    addi r5, r1, 0x14
    addi r6, r1, 0x8
    bl Terrain_RaycastWall
    clrlwi. r0, r3, 24
    bne RivalRun_RivalTactics_L_801367D4
    lfs f0, 0x5c(r1)
    stfs f0, 0x28(r30)
    lfs f0, 0x60(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x64(r1)
    stfs f0, 0x30(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136758:
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r5, 0x0
    bl RenderObj_UseItem
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_801367D4
    li r0, 0x0
    stw r0, 0x44(r30)
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x1062
    lwz r0, 0xf8(r4)
    lis r5, lbl_80495994@ha
    lwz r4, 0x0(r30)
    addi r6, r6, 0x4dd3
    srwi r0, r0, 2
    addi r5, r5, lbl_80495994@l
    mulhwu r0, r6, r0
    lfs f0, lbl_806D73C4(r2)
    lwz r4, 0x14(r4)
    srwi r0, r0, 6
    divwu r0, r3, r0
    clrlslwi r0, r0, 26, 2
    lfsx f1, r5, r0
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x68(r1)
    lwz r0, 0x6c(r1)
    add r0, r4, r0
    stw r0, 0x40(r30)
    RivalRun_RivalTactics_L_801367D4:
    psq_l f31, 0x88(r1), 0, 0
    lwz r0, 0x94(r1)
    lfd f31, 0x80(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

/* === extracted from auto_RivalRun_CalcPathDis_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Dot();
extern void Vec3_Magnitude();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void fn_8025E30C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D738C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8035C1E4[];

/* --- function index (1 fns, .text 0x801367F4..0x80136BA8) ---
 * [  0] 0x801367F4 size:0x3B4   global RivalRun_CalcPathDistance
 */

/* --- forward decls --- */
asm void RivalRun_CalcPathDistance(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_CalcPathDistance[8] = {
    0x41, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_CalcPathDistance = {
    (void *)&RivalRun_CalcPathDistance, 0x000003B4, (void *)extab_RivalRun_CalcPathDistance
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_CalcPathDistance(void) { /* 0x801367F4 size:0x3B4 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stfd f30, 0x90(r1)
    psq_st f30, 0x98(r1), 0, 0
    stfd f29, 0x80(r1)
    psq_st f29, 0x88(r1), 0, 0
    stfd f28, 0x70(r1)
    psq_st f28, 0x78(r1), 0, 0
    stfd f27, 0x60(r1)
    psq_st f27, 0x68(r1), 0, 0
    stmw r24, 0x40(r1)
    lwz r6, 0x4(r3)
    mr r28, r4
    lwz r0, 0x8(r3)
    lis r3, lbl_8035C1E4@ha
    lfs f31, lbl_806D738C(r2)
    slwi r4, r6, 4
    addi r3, r3, lbl_8035C1E4@l
    slwi r0, r0, 3
    add r4, r3, r4
    fmr f27, f31
    add r3, r4, r0
    lwzx r31, r4, r0
    li r26, 0x0
    lwz r30, 0x4(r3)
    lfs f30, 0x0(r28)
    lfs f29, 0x4(r28)
    mr r29, r5
    lfs f28, 0x8(r28)
    mr r27, r26
    mr r25, r31
    b RivalRun_CalcPathDistance_L_801368CC
    RivalRun_CalcPathDistance_L_80136880:
    lfs f0, 0x0(r25)
    addi r3, r1, 0x14
    fsubs f0, f0, f30
    stfs f0, 0x14(r1)
    lfs f0, 0x4(r25)
    fsubs f0, f0, f29
    stfs f0, 0x18(r1)
    lfs f0, 0x8(r25)
    fsubs f0, f0, f28
    stfs f0, 0x1c(r1)
    bl fn_8025E30C
    cmpwi r27, 0x0
    beq RivalRun_CalcPathDistance_L_801368BC
    fcmpo cr0, f1, f27
    bge RivalRun_CalcPathDistance_L_801368C4
    RivalRun_CalcPathDistance_L_801368BC:
    mr r26, r27
    fmr f27, f1
    RivalRun_CalcPathDistance_L_801368C4:
    addi r25, r25, 0xc
    addi r27, r27, 0x1
    RivalRun_CalcPathDistance_L_801368CC:
    cmpw r27, r30
    blt RivalRun_CalcPathDistance_L_80136880
    li r25, 0x0
    lfs f27, lbl_806D738C(r2)
    lfs f28, 0x0(r29)
    mr r27, r25
    lfs f29, 0x4(r29)
    mr r24, r31
    lfs f30, 0x8(r29)
    b RivalRun_CalcPathDistance_L_80136940
    RivalRun_CalcPathDistance_L_801368F4:
    lfs f0, 0x0(r24)
    addi r3, r1, 0x8
    fsubs f0, f0, f28
    stfs f0, 0x8(r1)
    lfs f0, 0x4(r24)
    fsubs f0, f0, f29
    stfs f0, 0xc(r1)
    lfs f0, 0x8(r24)
    fsubs f0, f0, f30
    stfs f0, 0x10(r1)
    bl fn_8025E30C
    cmpwi r27, 0x0
    beq RivalRun_CalcPathDistance_L_80136930
    fcmpo cr0, f1, f27
    bge RivalRun_CalcPathDistance_L_80136938
    RivalRun_CalcPathDistance_L_80136930:
    mr r25, r27
    fmr f27, f1
    RivalRun_CalcPathDistance_L_80136938:
    addi r24, r24, 0xc
    addi r27, r27, 0x1
    RivalRun_CalcPathDistance_L_80136940:
    cmpw r27, r30
    blt RivalRun_CalcPathDistance_L_801368F4
    cmpw r26, r25
    beq RivalRun_CalcPathDistance_L_80136A10
    ble RivalRun_CalcPathDistance_L_801369B4
    mulli r0, r25, 0xc
    mr r27, r25
    add r24, r31, r0
    b RivalRun_CalcPathDistance_L_801369A8
    RivalRun_CalcPathDistance_L_80136964:
    lfs f1, 0xc(r24)
    addi r3, r1, 0x2c
    lfs f0, 0x0(r24)
    fsubs f0, f1, f0
    stfs f0, 0x2c(r1)
    lfs f1, 0x10(r24)
    lfs f0, 0x4(r24)
    fsubs f0, f1, f0
    stfs f0, 0x30(r1)
    lfs f1, 0x14(r24)
    lfs f0, 0x8(r24)
    fsubs f0, f1, f0
    stfs f0, 0x34(r1)
    bl Vec3_Magnitude
    fadds f31, f31, f1
    addi r24, r24, 0xc
    addi r27, r27, 0x1
    RivalRun_CalcPathDistance_L_801369A8:
    cmpw r27, r26
    blt RivalRun_CalcPathDistance_L_80136964
    b RivalRun_CalcPathDistance_L_80136A10
    RivalRun_CalcPathDistance_L_801369B4:
    mulli r0, r26, 0xc
    mr r27, r26
    add r24, r31, r0
    b RivalRun_CalcPathDistance_L_80136A08
    RivalRun_CalcPathDistance_L_801369C4:
    lfs f1, 0xc(r24)
    addi r3, r1, 0x2c
    lfs f0, 0x0(r24)
    fsubs f0, f1, f0
    stfs f0, 0x2c(r1)
    lfs f1, 0x10(r24)
    lfs f0, 0x4(r24)
    fsubs f0, f1, f0
    stfs f0, 0x30(r1)
    lfs f1, 0x14(r24)
    lfs f0, 0x8(r24)
    fsubs f0, f1, f0
    stfs f0, 0x34(r1)
    bl Vec3_Magnitude
    fsubs f31, f31, f1
    addi r24, r24, 0xc
    addi r27, r27, 0x1
    RivalRun_CalcPathDistance_L_80136A08:
    cmpw r27, r25
    blt RivalRun_CalcPathDistance_L_801369C4
    RivalRun_CalcPathDistance_L_80136A10:
    mulli r24, r26, 0xc
    addi r4, r1, 0x2c
    mr r3, r28
    mr r5, r4
    add r27, r31, r24
    lfs f0, 0x0(r27)
    stfs f0, 0x2c(r1)
    lfs f0, 0x4(r27)
    stfs f0, 0x30(r1)
    lfs f0, 0x8(r27)
    stfs f0, 0x34(r1)
    bl Vec3_Subtract
    subi r0, r30, 0x1
    cmpw r26, r0
    bne RivalRun_CalcPathDistance_L_80136A78
    lfs f2, 0x0(r27)
    lfs f1, -0xc(r27)
    lfs f0, lbl_806D738C(r2)
    fsubs f1, f2, f1
    stfs f0, 0x24(r1)
    stfs f1, 0x20(r1)
    lfs f1, 0x8(r27)
    lfs f0, -0x4(r27)
    fsubs f0, f1, f0
    stfs f0, 0x28(r1)
    b RivalRun_CalcPathDistance_L_80136AA0
    RivalRun_CalcPathDistance_L_80136A78:
    lfs f1, 0x0(r27)
    lfs f2, 0xc(r27)
    lfs f0, lbl_806D738C(r2)
    fsubs f1, f2, f1
    stfs f0, 0x24(r1)
    stfs f1, 0x20(r1)
    lfs f1, 0x14(r27)
    lfs f0, 0x8(r27)
    fsubs f0, f1, f0
    stfs f0, 0x28(r1)
    RivalRun_CalcPathDistance_L_80136AA0:
    addi r3, r1, 0x20
    mr r4, r3
    bl Vec3_Normalize
    addi r3, r1, 0x2c
    addi r4, r1, 0x20
    bl Vec3_Dot
    mulli r24, r25, 0xc
    addi r4, r1, 0x2c
    fadds f31, f31, f1
    mr r3, r29
    mr r5, r4
    add r26, r31, r24
    lfs f0, 0x0(r26)
    stfs f0, 0x2c(r1)
    lfs f0, 0x4(r26)
    stfs f0, 0x30(r1)
    lfs f0, 0x8(r26)
    stfs f0, 0x34(r1)
    bl Vec3_Subtract
    subi r0, r30, 0x1
    cmpw r25, r0
    bne RivalRun_CalcPathDistance_L_80136B24
    lfs f2, 0x0(r26)
    lfs f1, -0xc(r26)
    lfs f0, lbl_806D738C(r2)
    fsubs f1, f2, f1
    stfs f0, 0x24(r1)
    stfs f1, 0x20(r1)
    lfs f1, 0x8(r26)
    lfs f0, -0x4(r26)
    fsubs f0, f1, f0
    stfs f0, 0x28(r1)
    b RivalRun_CalcPathDistance_L_80136B4C
    RivalRun_CalcPathDistance_L_80136B24:
    lfs f1, 0x0(r26)
    lfs f2, 0xc(r26)
    lfs f0, lbl_806D738C(r2)
    fsubs f1, f2, f1
    stfs f0, 0x24(r1)
    stfs f1, 0x20(r1)
    lfs f1, 0x14(r26)
    lfs f0, 0x8(r26)
    fsubs f0, f1, f0
    stfs f0, 0x28(r1)
    RivalRun_CalcPathDistance_L_80136B4C:
    addi r3, r1, 0x20
    mr r4, r3
    bl Vec3_Normalize
    addi r3, r1, 0x2c
    addi r4, r1, 0x20
    bl Vec3_Dot
    fsubs f31, f31, f1
    fmr f1, f31
    psq_l f31, 0xa8(r1), 0, 0
    lfd f31, 0xa0(r1)
    psq_l f30, 0x98(r1), 0, 0
    lfd f30, 0x90(r1)
    psq_l f29, 0x88(r1), 0, 0
    lfd f29, 0x80(r1)
    psq_l f28, 0x78(r1), 0, 0
    lfd f28, 0x70(r1)
    psq_l f27, 0x68(r1), 0, 0
    lfd f27, 0x60(r1)
    lmw r24, 0x40(r1)
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

/* === extracted from auto_RivalRun_Destroy_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void GetRaceContextPtr();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor();
extern void MemoryManager_TimedFree();
extern void PathParticipantArray_Dtor();
extern void Path_ResetCursorForKart();
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_80124C84();
extern void fn_8016C634();
extern void fn_80208FE4();
extern void fn_80254134();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_courseData;
extern unsigned int g_objCollChecker;
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8048E4A0[];

/* --- function index (1 fns, .text 0x80136BA8..0x80136EA0) ---
 * [  0] 0x80136BA8 size:0x2F8   global RivalRun_Destroy
 */

/* --- forward decls --- */
asm void RivalRun_Destroy(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_Destroy[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_Destroy = {
    (void *)&RivalRun_Destroy, 0x000002F8, (void *)extab_RivalRun_Destroy
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_Destroy(void) { /* 0x80136BA8 size:0x2F8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr. r30, r3
    stw r29, 0x14(r1)
    beq RivalRun_Destroy_L_80136E80
    lis r3, lbl_8048E4A0@ha
    addi r0, r3, lbl_8048E4A0@l
    stw r0, 0x0(r30)
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136BF4
    li r4, 0x1
    bl fn_8016C634
    li r0, 0x0
    stw r0, g_weatherSystem(r13)
    RivalRun_Destroy_L_80136BF4:
    li r3, 0x0
    li r4, 0x0
    bl SetActiveCamera
    li r0, 0x0
    li r4, 0x1
    stw r0, g_objCollChecker(r13)
    lwz r3, 0x2c(r30)
    bl fn_80208FE4
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136C34
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136C34:
    lwz r3, 0xc(r30)
    li r4, 0x1
    bl LakituStart_Dtor
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl fn_80124C84
    li r3, 0x0
    bl SetPlayerCarObject
    lwz r3, 0x8(r30)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136C74
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136C74:
    lwz r29, 0x30(r30)
    cmplwi r29, 0x0
    beq RivalRun_Destroy_L_80136CD4
    lwz r3, 0x14(r29)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136C9C
    lwz r4, 0x18(r29)
    cmpwi r4, 0x0
    blt RivalRun_Destroy_L_80136C9C
    bl Path_ResetCursorForKart
    RivalRun_Destroy_L_80136C9C:
    lwz r3, 0x4(r29)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136CBC
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136CBC:
    lwz r3, 0x20(r29)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136CCC
    bl MemoryManager_TimedFree
    RivalRun_Destroy_L_80136CCC:
    mr r3, r29
    bl MemoryManager_TimedFree
    RivalRun_Destroy_L_80136CD4:
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    lwz r3, 0x1c(r30)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136D00
    beq RivalRun_Destroy_L_80136D00
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136D00:
    lwz r29, 0x20(r30)
    cmplwi r29, 0x0
    beq RivalRun_Destroy_L_80136D7C
    beq RivalRun_Destroy_L_80136D7C
    lis r3, 0x1
    lhz r4, 0x4(r29)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq RivalRun_Destroy_L_80136D34
    b RivalRun_Destroy_L_80136D44
    RivalRun_Destroy_L_80136D34:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r29)
    extrwi r0, r0, 8, 19
    RivalRun_Destroy_L_80136D44:
    cmpwi r0, 0x0
    beq RivalRun_Destroy_L_80136D7C
    cmplwi r29, 0x0
    beq RivalRun_Destroy_L_80136D7C
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136D7C:
    lwz r3, 0x10(r30)
    li r4, 0x1
    bl CourseEnvironment_Dtor
    lwz r3, 0x28(r30)
    li r4, 0x1
    bl fn_80254134
    lwz r3, 0x24(r30)
    li r4, 0x1
    bl PathParticipantArray_Dtor
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl GetRaceContextPtr
    bl RankingTable_Init
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136DD4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136DD4:
    li r0, 0x0
    stw r0, lbl_806D10D0(r13)
    bl SceneDrawList_Reset
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136E00
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136E00:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D109C(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    lwz r3, g_courseData(r13)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136E34
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136E34:
    lwz r3, lbl_806D10AC(r13)
    li r0, 0x0
    stw r0, g_courseData(r13)
    cmplwi r3, 0x0
    beq RivalRun_Destroy_L_80136E5C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    RivalRun_Destroy_L_80136E5C:
    li r0, 0x0
    mr r3, r30
    stw r0, lbl_806D10AC(r13)
    li r4, 0x0
    bl dtor_80122FD8
    extsh. r0, r31
    ble RivalRun_Destroy_L_80136E80
    mr r3, r30
    bl MemoryManager_TimedFree
    RivalRun_Destroy_L_80136E80:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

/* === extracted from auto_RivalRun_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Camera_Create();
extern void CarObject_GetRenderObj();
extern void CarObject_GetTransformMatrix();
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern void ChallengeGoalCamera_Init();
extern void CourseData_GetDefaultPathKey_Safe();
extern void CourseData_GetOrCreate();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GameMode_BaseInit();
extern void GetCourseDataPtr();
extern void GetCourseStartYaw();
extern void GetDisplayBufferIndex();
extern void GetKartModelNameEntry();
extern void GetRaceContextPtr();
extern void GetStartPosition();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void InputManager_Init();
extern void ItemObjectManager_Init();
extern void LakituStart_Init();
extern void MiniGame_GetCourseData();
extern void MiniGame_GetTimerValue();
extern void PathManager_Init();
extern void PreloadEffectResources();
extern void PreloadItemResources();
extern void ProcessSystemTick();
extern void RankingTable_Init();
extern void RenderTarget_Create();
extern void RivalRun_RivalInit();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SetActiveCamera();
extern void SetCourseScene3D();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void SetReverseRoundFlag();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void TransitionEffect_GetOrCreate();
extern void WeatherSystem_Init();
extern void fn_802090A8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_characterId;
extern unsigned int g_kartStartSlot;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_objCollChecker;
extern unsigned int g_playerRenderObj;
extern unsigned int g_raceCamera;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_totalLaps;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D12BC;
extern unsigned int lbl_806D7388;
extern unsigned int lbl_806D738C;
extern unsigned int lbl_806D73CC;
extern unsigned int lbl_806D73D0;
extern unsigned int lbl_806D73D8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8035C22C[];
extern unsigned int lbl_8048E144[];
extern unsigned int lbl_8048E4A0[];

/* --- function index (1 fns, .text 0x80136EA0..0x8013732C) ---
 * [  0] 0x80136EA0 size:0x48C   global RivalRun_Init
 */

/* --- forward decls --- */
asm void RivalRun_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80122FD8();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; void *f49; unsigned int f50; unsigned int f51; void *f52; unsigned int f53; void *f54; unsigned int f55; unsigned int f56; void *f57; unsigned int f58; void *f59; unsigned int f60; unsigned int f61; void *f62; unsigned int f63; void *f64; unsigned int f65; unsigned int f66; void *f67; unsigned int f68; void *f69; unsigned int f70; unsigned int f71; void *f72; unsigned int f73; void *f74; unsigned int f75; unsigned int f76; void *f77; unsigned int f78; void *f79; unsigned int f80; unsigned int f81; void *f82; unsigned int f83; void *f84; unsigned int f85; unsigned int f86; void *f87; unsigned int f88; void *f89; unsigned int f90; unsigned int f91; void *f92; unsigned int f93; void *f94; unsigned int f95; unsigned int f96; void *f97; unsigned int f98; void *f99; unsigned int f100; unsigned int f101; void *f102; } extab_RivalRun_Init = { 0x284A0000, 0x00000090, 0x000D00C8, 0x000000D0, 0x000000C0, 0x000000E4, 0x000500C8, 0x00000118, 0x000000D4, 0x00000128, 0x001300C8, 0x00000188, 0x001000E8, 0x000001D8, 0x000E00C8, 0x00000220, 0x000A00FC, 0x00000254, 0x000000C8, 0x00000260, 0x00000110, 0x00000274, 0x000000C8, 0x0000028C, 0x00000124, 0x00000298, 0x000400C8, 0x000002CC, 0x00000138, 0x000002D8, 0x000000C8, 0x000002EC, 0x0004014C, 0x00000308, 0x000000C8, 0x00000314, 0x00000160, 0x00000320, 0x000D00C8, 0x00000364, 0x00000174, 0x00000378, 0x003600C8, 0x00000460, 0x00000188, 0x0000046C, 0x000000C8, 0x00000000, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_Init = {
    (void *)&RivalRun_Init, 0x0000048C, (void *)&extab_RivalRun_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_Init(void) { /* 0x80136EA0 size:0x48C */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stmw r27, 0x3c(r1)
    mr r31, r3
    mr r0, r31
    mr r28, r0
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_8048E4A0@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D738C(r2)
    stw r0, 0x0(r28)
    addi r3, r3, lbl_8048E4A0@l
    li r0, 0x0
    stfs f0, 0x4(r28)
    stw r3, 0x0(r31)
    stw r0, 0x8(r31)
    stw r0, 0xc(r31)
    stw r0, 0x10(r31)
    stw r0, 0x14(r31)
    stw r0, 0x18(r31)
    stw r0, 0x1c(r31)
    stw r0, 0x20(r31)
    stw r0, 0x24(r31)
    stw r0, 0x28(r31)
    stw r0, 0x2c(r31)
    stw r0, 0x30(r31)
    stb r0, 0x34(r31)
    stb r0, 0x35(r31)
    stb r0, 0x36(r31)
    stb r0, 0x37(r31)
    stw r0, 0x38(r31)
    bl MiniGame_GetCourseData
    mr r30, r3
    bl DrawManager_GetOrCreate
    li r3, 0x0
    bl SetResourceLoadingFlag
    bl DMAChannelManager_Init
    bl TransitionEffect_GetOrCreate
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r3, 0x0
    bl SetReverseRoundFlag
    li r3, 0x37c
    bl Alloc
    mr. r28, r3
    beq RivalRun_Init_L_80136F70
    bl InputManager_Init
    RivalRun_Init_L_80136F70:
    stw r28, 0x10(r31)
    li r3, 0x6
    li r4, 0x0
    li r5, 0x0
    bl CourseData_GetOrCreate
    bl GetCourseDataPtr
    bl RenderTarget_Create
    stw r3, 0x20(r31)
    li r3, 0x2c
    bl Alloc
    mr. r28, r3
    beq RivalRun_Init_L_80136FB8
    lfs f1, lbl_806D73CC(r2)
    li r4, 0x100
    lfs f2, lbl_806D7388(r2)
    li r5, 0x100
    lwz r6, 0x20(r31)
    bl Camera_Create
    RivalRun_Init_L_80136FB8:
    stw r28, 0x1c(r31)
    li r3, 0x0
    lwz r4, 0x1c(r31)
    bl SetActiveCamera
    lwz r0, 0x1c(r31)
    li r3, 0x0
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    bl GetRaceContextPtr
    bl RankingTable_Init
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D12BC(r13)
    bl SoundDriver_GetOrCreate
    li r0, 0x0
    addi r6, r1, 0x20
    stw r0, g_kartStartSlot(r13)
    addi r4, r1, 0x18
    addi r5, r1, 0x1c
    li r3, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_80137068
    lwz r28, g_ccClass(r13)
    lwz r29, g_characterId(r13)
    bl GetCourseStartYaw
    fmr f31, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f31
    mr r3, r27
    mr r5, r29
    lfs f1, 0x18(r1)
    mr r6, r28
    lfs f2, 0x20(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, -0x1
    li r10, 0x0
    bl CarObject_Init
    RivalRun_Init_L_80137068:
    stw r27, 0x8(r31)
    addi r4, r1, 0x18
    lwz r3, 0x8(r31)
    bl CarObject_SetPosition
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    stw r3, g_playerRenderObj(r13)
    lwz r3, 0x8(r31)
    bl SetPlayerCarObject
    lwz r3, 0x8(r31)
    bl CarObject_GetTransformMatrix
    mr r28, r3
    li r3, 0x4e8
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_801370E8
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    mr r29, r3
    bl CourseData_GetDefaultPathKey_Safe
    lwz r5, 0x8(r31)
    mr r4, r3
    mr r3, r27
    mr r6, r29
    addi r7, r28, 0x30
    addi r8, r28, 0x34
    addi r9, r28, 0x38
    bl PathManager_Init
    RivalRun_Init_L_801370E8:
    stw r27, 0x24(r31)
    li r3, 0x18
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_80137100
    bl fn_802090A8
    RivalRun_Init_L_80137100:
    stw r27, 0x2c(r31)
    li r3, 0x54
    lwz r0, 0x2c(r31)
    stw r0, g_objCollChecker(r13)
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_8013712C
    lwz r4, 0x24(r31)
    mr r6, r30
    li r5, 0x1
    bl RivalRun_RivalInit
    RivalRun_Init_L_8013712C:
    stw r27, 0x30(r31)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    lwz r4, 0x30(r31)
    stw r3, 0x50(r4)
    li r3, 0x58
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_8013716C
    lfs f1, lbl_806D738C(r2)
    lis r4, lbl_8035C22C@ha
    addi r4, r4, lbl_8035C22C@l
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    RivalRun_Init_L_8013716C:
    stw r27, 0xc(r31)
    li r3, 0x3084
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_8013719C
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r27
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    RivalRun_Init_L_8013719C:
    stw r27, 0x14(r31)
    li r3, 0x8
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_801371B4
    bl ChallengeGoalCamera_Init
    RivalRun_Init_L_801371B4:
    stw r27, 0x18(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x14(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D73D0(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x14(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_80137204
    lwz r4, 0x24(r31)
    bl HUD_Init
    RivalRun_Init_L_80137204:
    stw r27, 0x28(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x28(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0xa
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0xc
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x14(r31)
    bl SetCourseScene3D
    li r0, 0x0
    stb r0, g_raceEnded(r13)
    bl MiniGame_GetTimerValue
    xoris r0, r3, 0x8000
    lis r4, 0x4330
    stw r0, 0x2c(r1)
    li r0, 0x1
    lfd f1, lbl_806D73D8(r2)
    li r3, 0x9
    stw r4, 0x28(r1)
    lfd f0, 0x28(r1)
    stw r0, g_totalLaps(r13)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    li r3, 0x32
    bl PreloadItemResources
    li r3, 0x3d
    bl PreloadItemResources
    li r3, 0x3e
    bl PreloadItemResources
    li r3, 0x6c
    bl PreloadItemResources
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne RivalRun_Init_L_80137304
    li r3, 0x1b4
    bl Alloc
    mr. r27, r3
    beq RivalRun_Init_L_80137300
    li r4, 0x1
    bl WeatherSystem_Init
    RivalRun_Init_L_80137300:
    stw r27, g_weatherSystem(r13)
    RivalRun_Init_L_80137304:
    li r3, 0x1
    bl SetResourceLoadingFlag
    mr r3, r31
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    lmw r27, 0x3c(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

/* === extracted from auto_RivalRun_RivalInit_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void CarObject_GetRenderObj();
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern void GetCourseStartYaw();
extern void GetRaceContextPtr();
extern void GetStartPosition();
extern void ItemEffectBus_OrMask();
extern void PathManager_RegisterCarObject();
extern void RaceContextSlot_GetIfAlive();
extern void RivalRun_PathFollowerInit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D738C;

/* --- function index (1 fns, .text 0x8013732C..0x80137588) ---
 * [  0] 0x8013732C size:0x25C   global RivalRun_RivalInit
 */

/* --- forward decls --- */
asm void RivalRun_RivalInit(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_RivalRun_RivalInit = { 0x200A0000, 0x0000006C, 0x000E0020, 0x000000C4, 0x000E0028, 0x00000178, 0x00000030, 0x00000000, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_RivalInit = {
    (void *)&RivalRun_RivalInit, 0x0000025C, (void *)&extab_RivalRun_RivalInit
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_RivalInit(void) { /* 0x8013732C size:0x25C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    li r0, 0x0
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r3
    addi r6, r30, 0x10
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    stw r31, 0x0(r3)
    mr r3, r5
    addi r5, r30, 0xc
    stw r0, 0x4(r30)
    stw r4, 0x14(r30)
    addi r4, r30, 0x8
    bl GetStartPosition
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x2
    bne RivalRun_RivalInit_L_801373D8
    li r3, 0x118
    bl Alloc
    mr. r28, r3
    beq RivalRun_RivalInit_L_801373D0
    lwz r29, g_ccClass(r13)
    bl GetCourseStartYaw
    li r0, 0x0
    fmr f3, f1
    stw r0, 0x8(r1)
    mr r3, r28
    mr r6, r29
    li r4, 0x6
    lfs f1, 0x8(r30)
    lfs f2, 0x10(r30)
    li r5, 0x0
    li r7, 0x0
    li r8, 0x0
    li r9, 0x5
    li r10, 0x0
    bl CarObject_Init
    RivalRun_RivalInit_L_801373D0:
    stw r28, 0x4(r30)
    b RivalRun_RivalInit_L_8013742C
    RivalRun_RivalInit_L_801373D8:
    li r3, 0x118
    bl Alloc
    mr. r28, r3
    beq RivalRun_RivalInit_L_80137428
    lwz r29, g_ccClass(r13)
    bl GetCourseStartYaw
    li r0, 0x0
    fmr f3, f1
    stw r0, 0x8(r1)
    mr r3, r28
    mr r6, r29
    li r4, 0x6
    lfs f1, 0x8(r30)
    lfs f2, 0x10(r30)
    li r5, 0x0
    li r7, 0x0
    li r8, 0x0
    li r9, -0x1
    li r10, 0x0
    bl CarObject_Init
    RivalRun_RivalInit_L_80137428:
    stw r28, 0x4(r30)
    RivalRun_RivalInit_L_8013742C:
    lwz r3, 0x4(r30)
    addi r4, r30, 0x8
    bl CarObject_SetPosition
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r3, 0x304(r3)
    li r6, 0x0
    lis r5, 0x80
    bl ItemEffectBus_OrMask
    li r0, -0x1
    stw r0, 0x18(r30)
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    mr r8, r3
    lwz r3, 0x14(r30)
    lwz r7, 0x4(r30)
    addi r4, r30, 0x8
    addi r5, r30, 0xc
    addi r6, r30, 0x10
    li r9, -0x1
    bl PathManager_RegisterCarObject
    stw r3, 0x18(r30)
    li r0, 0x0
    li r3, 0x2c
    stw r0, 0x1c(r30)
    bl Alloc
    mr. r28, r3
    beq RivalRun_RivalInit_L_801374A4
    addi r4, r30, 0x8
    bl RivalRun_PathFollowerInit
    RivalRun_RivalInit_L_801374A4:
    stw r28, 0x20(r30)
    li r3, 0x0
    lfs f0, lbl_806D738C(r2)
    li r0, 0xb4
    stw r3, 0x24(r30)
    li r28, 0x0
    stfs f0, 0x28(r30)
    stfs f0, 0x2c(r30)
    stfs f0, 0x30(r30)
    stw r3, 0x34(r30)
    stb r3, 0x38(r30)
    stw r3, 0x3c(r30)
    stw r0, 0x40(r30)
    stw r3, 0x44(r30)
    stfs f0, 0x4c(r30)
    stw r3, 0x50(r30)
    RivalRun_RivalInit_L_801374E4:
    bl GetRaceContextPtr
    mr r4, r28
    bl RaceContextSlot_GetIfAlive
    mr. r29, r3
    beq RivalRun_RivalInit_L_80137514
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r0, 0xb4(r29)
    cmplw r0, r3
    bne RivalRun_RivalInit_L_80137514
    stw r28, 0x1c(r30)
    b RivalRun_RivalInit_L_80137520
    RivalRun_RivalInit_L_80137514:
    addi r28, r28, 0x1
    cmpwi r28, 0x80
    blt RivalRun_RivalInit_L_801374E4
    RivalRun_RivalInit_L_80137520:
    lwz r3, 0x0(r30)
    cmplwi r3, 0x0
    beq RivalRun_RivalInit_L_80137564
    lwz r0, 0x0(r3)
    lfs f1, 0x4(r31)
    stw r0, 0x3c(r30)
    lfs f0, lbl_806D738C(r2)
    lwz r3, 0x0(r30)
    fcmpo cr0, f1, f0
    lwz r0, 0x14(r3)
    stw r0, 0x40(r30)
    ble RivalRun_RivalInit_L_8013755C
    li r0, 0x1
    stb r0, 0x38(r30)
    b RivalRun_RivalInit_L_80137564
    RivalRun_RivalInit_L_8013755C:
    li r0, 0x0
    stb r0, 0x38(r30)
    RivalRun_RivalInit_L_80137564:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
