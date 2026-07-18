/* Exact asm_fn implementation for the BiribiriLand unit. */

/* === extracted from auto_BiribiriLand_Render_text === */
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
extern void Object_RenderJObjTree();
extern void Object_SetJObjField40();
extern void Object_SetJObjPositionVec();
extern void Object_SetJObjPositionX();
extern void Object_SetJObjPositionY();
extern void Object_SetJObjRotationY();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void fn_8016B0C4();
extern void fn_80253448();
extern void fn_802535D4();
extern void fn_802C14B8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CF5F0;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D7320;
extern unsigned int lbl_806DC1B8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80357F6C[];

/* --- function index (1 fns, .text 0x801341E4..0x8013449C) ---
 * [  0] 0x801341E4 size:0x2B8   global BiribiriLand_Render
 */

/* --- forward decls --- */
asm void BiribiriLand_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BiribiriLand_Render[8] = {
    0x30, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BiribiriLand_Render = {
    (void *)&BiribiriLand_Render, 0x000002B8, (void *)extab_BiribiriLand_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BiribiriLand_Render(void) { /* 0x801341E4 size:0x2B8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stmw r26, 0x8(r1)
    mr r31, r3
    lbz r0, 0x28(r3)
    cmplwi r0, 0x0
    beq BiribiriLand_Render_L_80134480
    lwz r3, 0x14(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne BiribiriLand_Render_L_8013444C
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne BiribiriLand_Render_L_8013423C
    li r3, 0x0
    BiribiriLand_Render_L_8013423C:
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
    lwz r28, 0x30(r31)
    lis r3, lbl_80357F6C@ha
    addi r27, r3, lbl_80357F6C@l
    li r29, 0x0
    mr r26, r28
    BiribiriLand_Render_L_80134288:
    lwz r0, 0x1c(r27)
    lfs f31, 0x18(r27)
    cmpwi r0, 0x0
    beq BiribiriLand_Render_L_801342A0
    lfs f0, lbl_806D7320(r2)
    fadds f31, f31, f0
    BiribiriLand_Render_L_801342A0:
    slwi r30, r0, 2
    addi r4, r26, 0x1c
    lwzx r3, r28, r30
    bl Object_SetJObjPositionVec
    fmr f1, f31
    lwzx r3, r28, r30
    bl Object_SetJObjRotationY
    lwzx r3, r28, r30
    li r4, 0x7
    bl Object_RenderJObjTree
    lbz r0, 0x20(r27)
    cmplwi r0, 0x0
    beq BiribiriLand_Render_L_80134318
    lwz r3, 0x14(r28)
    lfs f1, 0x1c(r26)
    bl Object_SetJObjPositionX
    lfs f1, 0x20(r26)
    lfs f0, lbl_806CF5F0(r13)
    lwz r3, 0x14(r28)
    fadds f1, f1, f0
    bl Object_SetJObjPositionY
    lwz r3, 0x14(r28)
    lfs f1, 0x24(r26)
    bl Object_SetJObjField40
    fmr f1, f31
    lwz r3, 0x14(r28)
    bl Object_SetJObjRotationY
    lwz r3, 0x14(r28)
    li r4, 0x7
    bl Object_RenderJObjTree
    BiribiriLand_Render_L_80134318:
    lwzx r3, r28, r30
    addi r4, r26, 0x28
    bl Object_SetJObjPositionVec
    fmr f1, f31
    lwzx r3, r28, r30
    bl Object_SetJObjRotationY
    lwzx r3, r28, r30
    li r4, 0x7
    bl Object_RenderJObjTree
    lbz r0, 0x20(r27)
    cmplwi r0, 0x0
    beq BiribiriLand_Render_L_8013438C
    lwz r3, 0x14(r28)
    lfs f1, 0x28(r26)
    bl Object_SetJObjPositionX
    lfs f1, 0x2c(r26)
    lfs f0, lbl_806CF5F0(r13)
    lwz r3, 0x14(r28)
    fadds f1, f1, f0
    bl Object_SetJObjPositionY
    lwz r3, 0x14(r28)
    lfs f1, 0x30(r26)
    bl Object_SetJObjField40
    fmr f1, f31
    lwz r3, 0x14(r28)
    bl Object_SetJObjRotationY
    lwz r3, 0x14(r28)
    li r4, 0x7
    bl Object_RenderJObjTree
    BiribiriLand_Render_L_8013438C:
    lbz r0, 0x50(r26)
    cmplwi r0, 0x0
    bne BiribiriLand_Render_L_801343BC
    lwz r3, 0x18(r28)
    addi r4, r26, 0x34
    bl Object_SetJObjPositionVec
    fmr f1, f31
    lwz r3, 0x18(r28)
    bl Object_SetJObjRotationY
    lwz r3, 0x18(r28)
    li r4, 0x7
    bl Object_RenderJObjTree
    BiribiriLand_Render_L_801343BC:
    addi r29, r29, 0x1
    addi r26, r26, 0x38
    cmplwi r29, 0x9
    addi r27, r27, 0x24
    blt BiribiriLand_Render_L_80134288
    bl ItemObjectManager_Render
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne BiribiriLand_Render_L_801343E8
    li r3, 0x0
    BiribiriLand_Render_L_801343E8:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne BiribiriLand_Render_L_801343FC
    li r3, 0x0
    BiribiriLand_Render_L_801343FC:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x10(r31)
    bl Subsystem36c_DispatchPass4_Timed
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BiribiriLand_Render_L_80134418
    li r3, 0x0
    BiribiriLand_Render_L_80134418:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BiribiriLand_Render_L_80134430
    li r3, 0x0
    BiribiriLand_Render_L_80134430:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r3, 0x14(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    BiribiriLand_Render_L_8013444C:
    lwz r3, 0x24(r31)
    lwz r4, lbl_806DC1B8(r2)
    bl fn_80253448
    lwz r3, 0x24(r31)
    bl fn_802535D4
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BiribiriLand_Render_L_80134470
    li r3, 0x0
    BiribiriLand_Render_L_80134470:
    li r4, 0x1
    bl TransitionEffect_RenderPass
    li r3, 0x7f
    bl fn_802C14B8
    BiribiriLand_Render_L_80134480:
    psq_l f31, 0x28(r1), 0, 0
    lfd f31, 0x20(r1)
    lmw r26, 0x8(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


/* === extracted from auto_BiribiriLand_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BiribiriLand_UpdateObstacles();
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void CarObject_ApplyInput();
extern void CarObject_CalcSpeedRatio();
extern void CarObject_FrameUpdate();
extern void CarObject_GetRenderObj();
extern void CarObject_HandleObstacleHit();
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
extern void KartItem_CancelActiveEffect();
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void KartMovement_SetSpeedScale();
extern void KartReaction_Rear();
extern void LakituStart_UpdateCountdown();
extern void MiniGame_GetTimerValue();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void NokoNokoChallenge_HandleBrakeInput();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void Object_SetByte10_Return1();
extern void SetCoinCount();
extern void SoundMgr_PlaySE();
extern void TransitionEffect_Tick();
extern void Vec3_Dot();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void fn_8016B32C();
extern void fn_80253C40();
extern void fn_80253C74();
extern void fn_80253EBC();
extern void fn_80253EC0();
extern void fn_80253FD8();
extern void memset();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D1290;
extern unsigned int lbl_806D7324;
extern unsigned int lbl_806D7328;
extern unsigned int lbl_806D732C;
extern unsigned int lbl_806D7330;
extern unsigned int lbl_806D7334;
extern unsigned int lbl_806D7338;
extern unsigned int lbl_806D733C;
extern unsigned int lbl_806D7340;
extern unsigned int lbl_806D7344;
extern unsigned int lbl_806D7348;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80677C88[];
extern unsigned int lbl_80677C94[];

/* --- function index (1 fns, .text 0x8013449C..0x80134A8C) ---
 * [  0] 0x8013449C size:0x5F0   global BiribiriLand_Update
 */

/* --- forward decls --- */
asm void BiribiriLand_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BiribiriLand_Update[8] = {
    0x20, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BiribiriLand_Update = {
    (void *)&BiribiriLand_Update, 0x000005F0, (void *)extab_BiribiriLand_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BiribiriLand_Update(void) { /* 0x8013449C size:0x5F0 */
    nofralloc
    stwu r1, -0x270(r1)
    mflr r0
    stw r0, 0x274(r1)
    stfd f31, 0x260(r1)
    psq_st f31, 0x268(r1), 0, 0
    stfd f30, 0x250(r1)
    psq_st f30, 0x258(r1), 0, 0
    stw r31, 0x24c(r1)
    stw r30, 0x248(r1)
    stw r29, 0x244(r1)
    stw r28, 0x240(r1)
    mr r31, r3
    lbz r0, 0x28(r3)
    cmplwi r0, 0x0
    bne BiribiriLand_Update_L_801344E0
    li r0, 0x1
    stb r0, 0x28(r31)
    BiribiriLand_Update_L_801344E0:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    mr r28, r3
    cmplwi r0, 0x1
    beq BiribiriLand_Update_L_801345D8
    lbz r0, lbl_806D1290(r13)
    cmplwi r0, 0x0
    bne BiribiriLand_Update_L_80134528
    lwz r12, 0x0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fmr f30, f1
    b BiribiriLand_Update_L_8013452C
    BiribiriLand_Update_L_80134528:
    lfs f30, lbl_806D7324(r2)
    BiribiriLand_Update_L_8013452C:
    lwz r12, 0x0(r28)
    mr r3, r28
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D732C(r2)
    fmr f31, f1
    li r30, 0x0
    fcmpo cr0, f30, f0
    bge BiribiriLand_Update_L_8013456C
    fcmpo cr0, f31, f0
    bge BiribiriLand_Update_L_8013456C
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq BiribiriLand_Update_L_8013456C
    li r30, 0x1
    BiribiriLand_Update_L_8013456C:
    mr r3, r31
    mr r4, r30
    bl NokoNokoChallenge_HandleBrakeInput
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne BiribiriLand_Update_L_80134588
    lfs f30, lbl_806D7328(r2)
    BiribiriLand_Update_L_80134588:
    bl IsRaceStarted
    mr r30, r3
    mr r3, r28
    lwz r12, 0x0(r28)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fmr f2, f30
    lwz r3, 0x8(r31)
    fmr f3, f31
    mr r4, r30
    bl CarObject_ApplyInput
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r31)
    li r5, 0x0
    lwz r4, 0x14(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    b BiribiriLand_Update_L_80134624
    BiribiriLand_Update_L_801345D8:
    lfs f1, lbl_806D7330(r2)
    li r4, 0x1
    lwz r3, 0x8(r31)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D7334(r2)
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
    BiribiriLand_Update_L_80134624:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0xc(r31)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x10(r31)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lwz r3, 0x30(r31)
    bl BiribiriLand_UpdateObstacles
    lbz r0, 0x2a(r31)
    cmplwi r0, 0x0
    bne BiribiriLand_Update_L_8013479C
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r3)
    li r30, 0x0
    lfs f30, lbl_806D7338(r2)
    stfs f0, 0x38(r1)
    lfs f31, lbl_806D733C(r2)
    lfs f0, 0x1c(r3)
    stfs f0, 0x3c(r1)
    lfs f0, 0x2c(r3)
    stfs f0, 0x40(r1)
    lwz r29, 0x30(r31)
    mr r28, r29
    BiribiriLand_Update_L_80134684:
    lbz r0, 0x50(r28)
    cmplwi r0, 0x0
    bne BiribiriLand_Update_L_801346EC
    addi r3, r1, 0x38
    addi r4, r28, 0x1c
    addi r5, r1, 0x14
    bl Vec3_Subtract
    addi r3, r1, 0x14
    addi r4, r28, 0x40
    bl Vec3_Dot
    fcmpo cr0, f1, f30
    bge BiribiriLand_Update_L_801346EC
    fcmpo cr0, f1, f31
    ble BiribiriLand_Update_L_801346EC
    lfs f1, 0x3c(r1)
    lfs f0, 0x38(r28)
    fcmpo cr0, f1, f0
    bge BiribiriLand_Update_L_801346EC
    mulli r0, r30, 0x38
    li r5, 0x1
    li r3, 0x90
    add r4, r29, r0
    stb r5, 0x50(r4)
    bl SoundMgr_PlaySE
    li r0, 0x1
    b BiribiriLand_Update_L_80134700
    BiribiriLand_Update_L_801346EC:
    addi r30, r30, 0x1
    addi r28, r28, 0x38
    cmplwi r30, 0x9
    blt BiribiriLand_Update_L_80134684
    li r0, 0x0
    BiribiriLand_Update_L_80134700:
    clrlwi. r0, r0, 24
    beq BiribiriLand_Update_L_80134750
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartReaction_Rear
    addi r3, r1, 0x44
    li r4, 0x0
    li r5, 0x1ec
    bl memset
    lfs f2, 0x38(r1)
    li r0, 0x8
    lfs f1, 0x3c(r1)
    addi r4, r1, 0x44
    lfs f0, 0x40(r1)
    stfs f2, 0xe4(r1)
    stfs f1, 0xe8(r1)
    stfs f0, 0xec(r1)
    stw r0, 0x4c(r1)
    lwz r3, 0x8(r31)
    bl CarObject_HandleObstacleHit
    BiribiriLand_Update_L_80134750:
    lwz r29, 0x34(r31)
    addi r3, r1, 0x38
    addi r5, r1, 0x8
    mr r4, r29
    bl Vec3_Subtract
    addi r3, r1, 0x8
    addi r4, r29, 0x24
    bl Vec3_Dot
    lfs f0, lbl_806D7330(r2)
    fcmpo cr0, f1, f0
    ble BiribiriLand_Update_L_8013479C
    li r0, 0x1
    stb r0, 0x2b(r31)
    stb r0, 0x2a(r31)
    lwz r3, 0x8(r31)
    bl KartItem_CancelActiveEffect
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnGoal
    BiribiriLand_Update_L_8013479C:
    lis r4, lbl_80677C88@ha
    lwz r3, 0x14(r31)
    addi r4, r4, lbl_80677C88@l
    bl CObj_LoadProjMatrix
    lis r4, lbl_80677C94@ha
    lwz r3, 0x14(r31)
    addi r4, r4, lbl_80677C94@l
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lis r3, lbl_80677C94@ha
    lis r4, lbl_80677C88@ha
    addi r5, r3, lbl_80677C94@l
    addi r3, r1, 0x2c
    addi r7, r4, lbl_80677C88@l
    lwz r10, 0x0(r5)
    lwz r9, 0x4(r5)
    addi r4, r1, 0x20
    lwz r8, 0x8(r5)
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r10, 0x20(r1)
    stw r9, 0x24(r1)
    stw r8, 0x28(r1)
    stw r6, 0x2c(r1)
    stw r5, 0x30(r1)
    stw r0, 0x34(r1)
    bl VfxSlotMgr_Update
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq BiribiriLand_Update_L_8013486C
    lbz r0, 0x2a(r31)
    cmplwi r0, 0x0
    bne BiribiriLand_Update_L_8013486C
    lfs f2, g_raceTimeRemaining(r13)
    lfs f1, lbl_806D7330(r2)
    fcmpo cr0, f2, f1
    cror eq, gt, eq
    bne BiribiriLand_Update_L_8013486C
    lfs f0, lbl_806D7340(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bge BiribiriLand_Update_L_8013486C
    stfs f1, g_raceTimeRemaining(r13)
    li r0, 0x1
    stb r0, 0x2a(r31)
    lwz r3, 0x8(r31)
    bl KartItem_CancelActiveEffect
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    BiribiriLand_Update_L_8013486C:
    lwz r3, 0x24(r31)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x8(r31)
    bl CarObject_CalcSpeedRatio
    lfs f0, lbl_806D7344(r2)
    lwz r3, 0x24(r31)
    fmuls f1, f0, f1
    bl fn_80253EBC
    lwz r3, 0x8(r31)
    bl KartItem_GetCurrentSpeedWithBonus
    lwz r3, 0x24(r31)
    bl fn_80253EC0
    lwz r3, 0x24(r31)
    bl HUD_FrameUpdate
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BiribiriLand_Update_L_801348B8
    li r3, 0x0
    BiribiriLand_Update_L_801348B8:
    bl TransitionEffect_Tick
    lbz r0, 0x2a(r31)
    cmplwi r0, 0x0
    beq BiribiriLand_Update_L_80134A48
    lwz r0, 0x2c(r31)
    cmpwi r0, 0x0
    bne BiribiriLand_Update_L_80134A20
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x234(r1)
    li r29, 0x0
    lfd f2, lbl_806D7348(r2)
    stw r0, 0x230(r1)
    lfs f0, g_raceTimeRemaining(r13)
    lfd f1, 0x230(r1)
    fsubs f1, f1, f2
    fsubs f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x238(r1)
    lwz r28, 0x23c(r1)
    bl NokoNokoChallenge_GetCoinDivisor
    cmplwi r3, 0x0
    beq BiribiriLand_Update_L_8013496C
    lbz r0, 0x2b(r31)
    cmplwi r0, 0x1
    bne BiribiriLand_Update_L_8013496C
    lwz r5, 0x0(r3)
    li r6, 0x0
    mr r4, r5
    mr r3, r5
    b BiribiriLand_Update_L_80134960
    BiribiriLand_Update_L_80134938:
    lwz r0, 0x0(r3)
    cmpw r28, r0
    bgt BiribiriLand_Update_L_80134954
    slwi r0, r6, 3
    add r3, r5, r0
    lwz r29, 0x4(r3)
    b BiribiriLand_Update_L_8013496C
    BiribiriLand_Update_L_80134954:
    addi r3, r3, 0x8
    addi r4, r4, 0x8
    addi r6, r6, 0x1
    BiribiriLand_Update_L_80134960:
    lwz r0, 0x4(r4)
    cmpwi r0, 0x0
    bgt BiribiriLand_Update_L_80134938
    BiribiriLand_Update_L_8013496C:
    mr r3, r29
    bl SetCoinCount
    lbz r0, 0x2b(r31)
    cmplwi r0, 0x0
    beq BiribiriLand_Update_L_801349C0
    mr r3, r31
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    lfs f0, g_raceTimeRemaining(r13)
    mr r5, r3
    lwz r3, 0x24(r31)
    li r4, 0x1
    fctiwz f0, f0
    stfd f0, 0x238(r1)
    lwz r6, 0x23c(r1)
    bl fn_80253C74
    lwz r3, 0x14(r31)
    li r4, 0x1
    bl Object_SetByte10_Return1
    b BiribiriLand_Update_L_801349FC
    BiribiriLand_Update_L_801349C0:
    mr r3, r31
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    lfs f0, g_raceTimeRemaining(r13)
    mr r5, r3
    lwz r3, 0x24(r31)
    li r4, 0x0
    fctiwz f0, f0
    stfd f0, 0x238(r1)
    lwz r6, 0x23c(r1)
    bl fn_80253C74
    lwz r3, 0x14(r31)
    li r4, 0x1
    bl Object_SetByte10_Return1
    BiribiriLand_Update_L_801349FC:
    lbz r5, 0x2b(r31)
    mr r3, r31
    mr r4, r29
    bl NokoNokoChallenge_SaveResult
    li r3, 0x1
    li r0, 0x0
    stb r3, g_raceEnded(r13)
    stb r0, g_lakituStartAnimDone(r13)
    b BiribiriLand_Update_L_80134A3C
    BiribiriLand_Update_L_80134A20:
    lwz r3, 0x24(r31)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq BiribiriLand_Update_L_80134A3C
    mr r3, r31
    bl NokoNokoChallenge_TransitionToResult
    b BiribiriLand_Update_L_80134A5C
    BiribiriLand_Update_L_80134A3C:
    lwz r3, 0x2c(r31)
    addi r0, r3, 0x1
    stw r0, 0x2c(r31)
    BiribiriLand_Update_L_80134A48:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq BiribiriLand_Update_L_80134A58
    bl fn_8016B32C
    BiribiriLand_Update_L_80134A58:
    li r3, -0x2
    BiribiriLand_Update_L_80134A5C:
    psq_l f31, 0x268(r1), 0, 0
    lfd f31, 0x260(r1)
    psq_l f30, 0x258(r1), 0, 0
    lfd f30, 0x250(r1)
    lwz r31, 0x24c(r1)
    lwz r30, 0x248(r1)
    lwz r29, 0x244(r1)
    lwz r0, 0x274(r1)
    lwz r28, 0x240(r1)
    mtlr r0
    addi r1, r1, 0x270
    blr
}


/* === extracted from auto_BiribiriLand_UpdateO_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_LoadProjMatrix();
extern void GetCourseScene3D();
extern void LUT_Sin12Bit();
extern void SoundMgr_PlaySE();
extern void Vec3_Subtract();
extern void clNormal3D_Exec();
extern void fn_8016C288();
extern void fn_8016C360();
extern void fn_8016C394();
extern void fn_8025E30C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D7328;
extern unsigned int lbl_806D7330;
extern unsigned int lbl_806D7334;
extern unsigned int lbl_806D7350;
extern unsigned int lbl_806D7354;
extern unsigned int lbl_806D7358;
extern unsigned int lbl_806D735C;
extern unsigned int lbl_806D7360;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80357B00[];

/* --- function index (1 fns, .text 0x80134A8C..0x80134D68) ---
 * [  0] 0x80134A8C size:0x2DC   global BiribiriLand_UpdateObstacles
 */

/* --- forward decls --- */
asm void BiribiriLand_UpdateObstacles(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BiribiriLand_UpdateObstacles[8] = {
    0x21, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BiribiriLand_UpdateObstacles = {
    (void *)&BiribiriLand_UpdateObstacles, 0x000002DC, (void *)extab_BiribiriLand_UpdateObstacles
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BiribiriLand_UpdateObstacles(void) { /* 0x80134A8C size:0x2DC */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stfd f30, 0x80(r1)
    psq_st f30, 0x88(r1), 0, 0
    stfd f29, 0x70(r1)
    psq_st f29, 0x78(r1), 0, 0
    stfd f28, 0x60(r1)
    psq_st f28, 0x68(r1), 0, 0
    stfd f27, 0x50(r1)
    psq_st f27, 0x58(r1), 0, 0
    stfd f26, 0x40(r1)
    psq_st f26, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    stw r29, 0x34(r1)
    stw r28, 0x30(r1)
    lis r4, lbl_80357B00@ha
    lfs f27, lbl_806D7350(r2)
    addi r31, r4, lbl_80357B00@l
    mr r28, r3
    lwz r7, 0x5b0(r31)
    lwz r6, 0x5b4(r31)
    lwz r5, 0x5b8(r31)
    lwz r4, 0x5bc(r31)
    lwz r3, 0x5c0(r31)
    lwz r0, 0x5c4(r31)
    stw r7, 0x20(r1)
    stw r6, 0x24(r1)
    stw r5, 0x28(r1)
    stw r4, 0x14(r1)
    stw r3, 0x18(r1)
    stw r0, 0x1c(r1)
    bl GetCourseScene3D
    cmplwi r3, 0x0
    beq BiribiriLand_UpdateObstacles_L_80134B30
    bl GetCourseScene3D
    addi r4, r1, 0x14
    bl CObj_LoadProjMatrix
    BiribiriLand_UpdateObstacles_L_80134B30:
    lfs f28, lbl_806D7328(r2)
    mr r30, r28
    lfs f29, lbl_806D7354(r2)
    addi r31, r31, 0x46c
    lfs f30, lbl_806D7334(r2)
    li r29, 0x0
    lfs f31, lbl_806D7360(r2)
    BiribiriLand_UpdateObstacles_L_80134B4C:
    lfs f0, 0x4c(r30)
    fadds f0, f0, f28
    stfs f0, 0x4c(r30)
    lfs f0, 0x4c(r30)
    fcmpo cr0, f0, f29
    cror eq, gt, eq
    bne BiribiriLand_UpdateObstacles_L_80134B70
    lfs f0, lbl_806D7330(r2)
    stfs f0, 0x4c(r30)
    BiribiriLand_UpdateObstacles_L_80134B70:
    lbz r0, 0x20(r31)
    lfs f2, lbl_806D7330(r2)
    cmplwi r0, 0x0
    beq BiribiriLand_UpdateObstacles_L_80134B98
    lfs f1, lbl_806D735C(r2)
    lfs f0, 0x4c(r30)
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f0, lbl_806D7358(r2)
    fmadds f2, f0, f1, f0
    BiribiriLand_UpdateObstacles_L_80134B98:
    lfs f1, 0x0(r31)
    lfs f0, 0x4(r31)
    stfs f1, 0x1c(r30)
    lfs f1, 0x8(r31)
    stfs f0, 0x20(r30)
    lfs f0, 0xc(r31)
    stfs f1, 0x24(r30)
    lfs f1, 0x10(r31)
    stfs f0, 0x28(r30)
    lfs f0, 0x14(r31)
    stfs f1, 0x2c(r30)
    stfs f0, 0x30(r30)
    lfs f0, 0x20(r30)
    fadds f0, f0, f2
    stfs f0, 0x20(r30)
    lfs f0, 0x2c(r30)
    fadds f0, f0, f2
    stfs f0, 0x2c(r30)
    lfs f1, 0x1c(r30)
    lfs f0, 0x28(r30)
    fadds f0, f1, f0
    fmuls f0, f30, f0
    stfs f0, 0x34(r30)
    lfs f1, 0x20(r30)
    lfs f0, 0x2c(r30)
    fadds f0, f1, f0
    fmadds f0, f30, f0, f31
    stfs f0, 0x38(r30)
    lfs f1, 0x24(r30)
    lfs f0, 0x30(r30)
    fadds f0, f1, f0
    fmuls f0, f30, f0
    stfs f0, 0x3c(r30)
    lbz r0, 0x50(r30)
    cmplwi r0, 0x0
    bne BiribiriLand_UpdateObstacles_L_80134CAC
    lfs f0, lbl_806D7330(r2)
    fcmpo cr0, f27, f0
    bge BiribiriLand_UpdateObstacles_L_80134C6C
    lfs f0, 0x34(r30)
    addi r3, r1, 0x20
    addi r4, r1, 0x14
    addi r5, r1, 0x8
    stfs f0, 0x20(r1)
    lfs f0, 0x38(r30)
    stfs f0, 0x24(r1)
    lfs f0, 0x3c(r30)
    stfs f0, 0x28(r1)
    bl Vec3_Subtract
    addi r3, r1, 0x8
    bl fn_8025E30C
    fmr f27, f1
    b BiribiriLand_UpdateObstacles_L_80134CAC
    BiribiriLand_UpdateObstacles_L_80134C6C:
    addi r3, r30, 0x34
    addi r4, r1, 0x14
    addi r5, r1, 0x8
    bl Vec3_Subtract
    addi r3, r1, 0x8
    bl fn_8025E30C
    fmr f26, f1
    fcmpo cr0, f26, f27
    bge BiribiriLand_UpdateObstacles_L_80134CAC
    lfs f0, 0x34(r30)
    fmr f27, f26
    stfs f0, 0x20(r1)
    lfs f0, 0x38(r30)
    stfs f0, 0x24(r1)
    lfs f0, 0x3c(r30)
    stfs f0, 0x28(r1)
    BiribiriLand_UpdateObstacles_L_80134CAC:
    addi r29, r29, 0x1
    addi r31, r31, 0x24
    cmplwi r29, 0x9
    addi r30, r30, 0x38
    blt BiribiriLand_UpdateObstacles_L_80134B4C
    lwz r3, 0x18(r28)
    bl clNormal3D_Exec
    lfs f0, lbl_806D7330(r2)
    fcmpo cr0, f26, f0
    cror eq, gt, eq
    bne BiribiriLand_UpdateObstacles_L_80134D00
    li r3, 0x91
    bl fn_8016C360
    clrlwi. r0, r3, 24
    bne BiribiriLand_UpdateObstacles_L_80134CF0
    li r3, 0x91
    bl SoundMgr_PlaySE
    BiribiriLand_UpdateObstacles_L_80134CF0:
    addi r4, r1, 0x20
    li r3, 0x91
    bl fn_8016C288
    b BiribiriLand_UpdateObstacles_L_80134D18
    BiribiriLand_UpdateObstacles_L_80134D00:
    li r3, 0x91
    bl fn_8016C360
    clrlwi. r0, r3, 24
    beq BiribiriLand_UpdateObstacles_L_80134D18
    li r3, 0x91
    bl fn_8016C394
    BiribiriLand_UpdateObstacles_L_80134D18:
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    psq_l f30, 0x88(r1), 0, 0
    lfd f30, 0x80(r1)
    psq_l f29, 0x78(r1), 0, 0
    lfd f29, 0x70(r1)
    psq_l f28, 0x68(r1), 0, 0
    lfd f28, 0x60(r1)
    psq_l f27, 0x58(r1), 0, 0
    lfd f27, 0x50(r1)
    psq_l f26, 0x48(r1), 0, 0
    lfd f26, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    lwz r29, 0x34(r1)
    lwz r0, 0xa4(r1)
    lwz r28, 0x30(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}


/* === extracted from auto_BiribiriLand_Destroy_text === */
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
extern void Object_DtorWithGXSync();
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
extern void fn_80254134();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8048E46C[];

/* --- function index (1 fns, .text 0x80134D68..0x80134FF0) ---
 * [  0] 0x80134D68 size:0x288   global BiribiriLand_Destroy
 */

/* --- forward decls --- */
asm void BiribiriLand_Destroy(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BiribiriLand_Destroy[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BiribiriLand_Destroy = {
    (void *)&BiribiriLand_Destroy, 0x00000288, (void *)extab_BiribiriLand_Destroy
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BiribiriLand_Destroy(void) { /* 0x80134D68 size:0x288 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr. r30, r3
    mr r31, r4
    beq BiribiriLand_Destroy_L_80134FD8
    lis r3, lbl_8048E46C@ha
    addi r0, r3, lbl_8048E46C@l
    stw r0, 0x0(r30)
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq BiribiriLand_Destroy_L_80134DAC
    li r4, 0x1
    bl fn_8016C634
    li r0, 0x0
    stw r0, g_weatherSystem(r13)
    BiribiriLand_Destroy_L_80134DAC:
    li r3, 0x0
    li r4, 0x0
    bl SetActiveCamera
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq BiribiriLand_Destroy_L_80134DD8
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BiribiriLand_Destroy_L_80134DD8:
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
    beq BiribiriLand_Destroy_L_80134E18
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    BiribiriLand_Destroy_L_80134E18:
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    lwz r3, 0x1c(r30)
    cmplwi r3, 0x0
    beq BiribiriLand_Destroy_L_80134E44
    beq BiribiriLand_Destroy_L_80134E44
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BiribiriLand_Destroy_L_80134E44:
    lwz r27, 0x20(r30)
    cmplwi r27, 0x0
    beq BiribiriLand_Destroy_L_80134EC0
    beq BiribiriLand_Destroy_L_80134EC0
    lis r3, 0x1
    lhz r4, 0x4(r27)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq BiribiriLand_Destroy_L_80134E78
    b BiribiriLand_Destroy_L_80134E88
    BiribiriLand_Destroy_L_80134E78:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r27)
    extrwi r0, r0, 8, 19
    BiribiriLand_Destroy_L_80134E88:
    cmpwi r0, 0x0
    beq BiribiriLand_Destroy_L_80134EC0
    cmplwi r27, 0x0
    beq BiribiriLand_Destroy_L_80134EC0
    lwz r4, 0x0(r27)
    mr r3, r27
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r27)
    mr r3, r27
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    BiribiriLand_Destroy_L_80134EC0:
    lwz r3, 0x10(r30)
    li r4, 0x1
    bl CourseEnvironment_Dtor
    lwz r3, 0x24(r30)
    li r4, 0x1
    bl fn_80254134
    lwz r28, 0x30(r30)
    cmplwi r28, 0x0
    beq BiribiriLand_Destroy_L_80134F10
    li r29, 0x0
    mr r27, r28
    BiribiriLand_Destroy_L_80134EEC:
    lwz r3, 0x0(r27)
    li r4, 0x1
    bl Object_DtorWithGXSync
    addi r29, r29, 0x1
    addi r27, r27, 0x4
    cmpwi r29, 0x7
    blt BiribiriLand_Destroy_L_80134EEC
    mr r3, r28
    bl MemoryManager_TimedFree
    BiribiriLand_Destroy_L_80134F10:
    lwz r3, 0x34(r30)
    cmplwi r3, 0x0
    beq BiribiriLand_Destroy_L_80134F20
    bl MemoryManager_TimedFree
    BiribiriLand_Destroy_L_80134F20:
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl GetRaceContextPtr
    bl RankingTable_Init
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    beq BiribiriLand_Destroy_L_80134F54
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BiribiriLand_Destroy_L_80134F54:
    li r0, 0x0
    stw r0, lbl_806D10D0(r13)
    bl SceneDrawList_Reset
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    beq BiribiriLand_Destroy_L_80134F80
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BiribiriLand_Destroy_L_80134F80:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D109C(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq BiribiriLand_Destroy_L_80134FB4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BiribiriLand_Destroy_L_80134FB4:
    li r0, 0x0
    mr r3, r30
    stw r0, lbl_806D10AC(r13)
    li r4, 0x0
    bl dtor_80122FD8
    extsh. r0, r31
    ble BiribiriLand_Destroy_L_80134FD8
    mr r3, r30
    bl MemoryManager_TimedFree
    BiribiriLand_Destroy_L_80134FD8:
    mr r3, r30
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_BiribiriLand_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Camera_Create();
extern void CarObject_GetRenderObj();
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern void ChallengeGoalCamera_Init();
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
extern void MiniGame_GetTimerValue();
extern void Object_SetJObjScaleXYZ();
extern void PreloadEffectResources();
extern void ProcessSystemTick();
extern void RankingTable_Init();
extern void RenderTarget_Create();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SetActiveCamera();
extern void SetCourseScene3D();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void TransitionEffect_GetOrCreate();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void WeatherSystem_Init();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceCamera;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D12BC;
extern unsigned int lbl_806D7328;
extern unsigned int lbl_806D732C;
extern unsigned int lbl_806D7330;
extern unsigned int lbl_806D7334;
extern unsigned int lbl_806D7338;
extern unsigned int lbl_806D7348;
extern unsigned int lbl_806D7360;
extern unsigned int lbl_806D7364;
extern unsigned int lbl_806D7368;
extern unsigned int lbl_806D736C;
extern unsigned int lbl_806D7370;
extern unsigned int lbl_806D7374;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80357F6C[];
extern unsigned int lbl_803580E0[];
extern unsigned int lbl_8048E144[];
extern unsigned int lbl_8048E430[];
extern unsigned int lbl_8048E46C[];

/* --- function index (1 fns, .text 0x80134FF0..0x8013558C) ---
 * [  0] 0x80134FF0 size:0x59C   global BiribiriLand_Init
 */

/* --- forward decls --- */
asm void BiribiriLand_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80122FD8();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; void *f49; unsigned int f50; unsigned int f51; void *f52; unsigned int f53; void *f54; unsigned int f55; unsigned int f56; void *f57; unsigned int f58; void *f59; unsigned int f60; unsigned int f61; void *f62; unsigned int f63; void *f64; unsigned int f65; unsigned int f66; void *f67; unsigned int f68; void *f69; unsigned int f70; unsigned int f71; void *f72; unsigned int f73; void *f74; unsigned int f75; unsigned int f76; void *f77; unsigned int f78; void *f79; unsigned int f80; unsigned int f81; void *f82; unsigned int f83; void *f84; unsigned int f85; void *f86; unsigned int f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; unsigned int f93; void *f94; unsigned int f95; void *f96; unsigned int f97; unsigned int f98; void *f99; } extab_BiribiriLand_Init = { 0x30CA0000, 0x000000A8, 0x000900C8, 0x000000D8, 0x000000C0, 0x000000E0, 0x000400C8, 0x00000110, 0x000000D4, 0x00000120, 0x001100C8, 0x00000174, 0x001000E8, 0x000001C4, 0x000800C8, 0x00000208, 0x000000FC, 0x00000214, 0x000000C8, 0x00000228, 0x00040110, 0x00000244, 0x000000C8, 0x00000250, 0x00000124, 0x0000025C, 0x000D00C8, 0x000002A0, 0x00000138, 0x000002B4, 0x002300C8, 0x00000360, 0x00000154, 0x00000374, 0x0000014C, 0x00000394, 0x003D0154, 0x000004D0, 0x000000C8, 0x00000510, 0x00030168, 0x00000550, 0x000000C8, 0x00000560, 0x0000017C, 0x0000056C, 0x000000C8, 0x00000000, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BiribiriLand_Init = {
    (void *)&BiribiriLand_Init, 0x0000059C, (void *)&extab_BiribiriLand_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BiribiriLand_Init(void) { /* 0x80134FF0 size:0x59C */
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
    stmw r26, 0x38(r1)
    mr r31, r3
    mr r0, r31
    mr r28, r0
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_8048E46C@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D7330(r2)
    stw r0, 0x0(r28)
    addi r3, r3, lbl_8048E46C@l
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
    stb r0, 0x28(r31)
    stb r0, 0x29(r31)
    stb r0, 0x2a(r31)
    stb r0, 0x2b(r31)
    stw r0, 0x2c(r31)
    stw r0, 0x30(r31)
    stw r0, 0x34(r31)
    stfs f0, 0x38(r31)
    stfs f0, 0x3c(r31)
    stfs f0, 0x40(r31)
    bl DrawManager_GetOrCreate
    li r3, 0x0
    bl SetResourceLoadingFlag
    bl DMAChannelManager_Init
    bl TransitionEffect_GetOrCreate
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r3, 0x37c
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_801350C8
    bl InputManager_Init
    BiribiriLand_Init_L_801350C8:
    stw r28, 0x10(r31)
    bl GetCourseDataPtr
    bl RenderTarget_Create
    stw r3, 0x20(r31)
    li r3, 0x2c
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135100
    lfs f1, lbl_806D7364(r2)
    li r4, 0x100
    lfs f2, lbl_806D732C(r2)
    li r5, 0x100
    lwz r6, 0x20(r31)
    bl Camera_Create
    BiribiriLand_Init_L_80135100:
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
    addi r6, r1, 0x2c
    addi r4, r1, 0x24
    addi r5, r1, 0x28
    li r3, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_801351A4
    lwz r30, g_characterId(r13)
    bl GetCourseStartYaw
    fmr f29, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f29
    mr r3, r28
    mr r5, r30
    lfs f1, 0x24(r1)
    li r6, 0x0
    lfs f2, 0x2c(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, 0x3
    li r10, 0x0
    bl CarObject_Init
    BiribiriLand_Init_L_801351A4:
    stw r28, 0x8(r31)
    addi r4, r1, 0x24
    lwz r3, 0x8(r31)
    bl CarObject_SetPosition
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0x8(r31)
    bl SetPlayerCarObject
    li r3, 0x58
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_801351F8
    lfs f1, lbl_806D7330(r2)
    lis r4, lbl_803580E0@ha
    addi r4, r4, lbl_803580E0@l
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    BiribiriLand_Init_L_801351F8:
    stw r28, 0xc(r31)
    li r3, 0x3084
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135228
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r28
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    BiribiriLand_Init_L_80135228:
    stw r28, 0x14(r31)
    li r3, 0x8
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135240
    bl ChallengeGoalCamera_Init
    BiribiriLand_Init_L_80135240:
    stw r28, 0x18(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x14(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D7338(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x14(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135290
    li r4, 0x0
    bl HUD_Init
    BiribiriLand_Init_L_80135290:
    stw r28, 0x24(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x24(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
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
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x34(r1)
    li r3, 0x1
    lfd f1, lbl_806D7348(r2)
    stw r0, 0x30(r1)
    lfd f0, 0x30(r1)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    li r3, 0x214
    bl Alloc
    mr. r27, r3
    beq BiribiriLand_Init_L_801354B4
    lis r3, lbl_8048E430@ha
    mr r28, r27
    addi r29, r3, lbl_8048E430@l
    li r30, 0x0
    BiribiriLand_Init_L_80135348:
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq BiribiriLand_Init_L_80135364
    lwz r4, 0x0(r29)
    li r5, 0x0
    bl clNormal3D_Construct
    BiribiriLand_Init_L_80135364:
    cmpwi r30, 0x5
    stw r26, 0x0(r28)
    bgt BiribiriLand_Init_L_80135384
    lfs f1, lbl_806D7368(r2)
    lwz r3, 0x0(r28)
    fmr f2, f1
    fmr f3, f1
    bl Object_SetJObjScaleXYZ
    BiribiriLand_Init_L_80135384:
    addi r30, r30, 0x1
    addi r28, r28, 0x4
    cmpwi r30, 0x7
    addi r29, r29, 0x4
    blt BiribiriLand_Init_L_80135348
    lfs f1, lbl_806D7330(r2)
    li r4, 0x0
    lwz r3, 0x18(r27)
    fmr f3, f1
    lfs f2, lbl_806D7328(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lis r3, lbl_80357F6C@ha
    lfs f30, lbl_806D7334(r2)
    lfs f31, lbl_806D7360(r2)
    addi r28, r3, lbl_80357F6C@l
    lfs f29, lbl_806D7330(r2)
    mr r29, r27
    li r30, 0x0
    BiribiriLand_Init_L_801353D0:
    lfs f1, 0x0(r28)
    addi r3, r1, 0x18
    lfs f0, 0x4(r28)
    mr r4, r3
    stfs f1, 0x1c(r29)
    lfs f1, 0x8(r28)
    stfs f0, 0x20(r29)
    lfs f0, 0xc(r28)
    stfs f1, 0x24(r29)
    lfs f1, 0x10(r28)
    stfs f0, 0x28(r29)
    lfs f0, 0x14(r28)
    stfs f1, 0x2c(r29)
    stfs f0, 0x30(r29)
    lfs f1, 0x1c(r29)
    lfs f0, 0x28(r29)
    fadds f0, f1, f0
    fmuls f0, f30, f0
    stfs f0, 0x34(r29)
    lfs f1, 0x20(r29)
    lfs f0, 0x2c(r29)
    fadds f0, f1, f0
    fmadds f0, f30, f0, f31
    stfs f0, 0x38(r29)
    lfs f1, 0x24(r29)
    lfs f0, 0x30(r29)
    fadds f0, f1, f0
    fmuls f0, f30, f0
    stfs f0, 0x3c(r29)
    lfs f1, 0x28(r29)
    lfs f0, 0x1c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x18(r1)
    lfs f1, 0x2c(r29)
    lfs f0, 0x20(r29)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r1)
    lfs f1, 0x30(r29)
    lfs f0, 0x24(r29)
    fsubs f0, f1, f0
    stfs f0, 0x20(r1)
    bl Vec3_Normalize
    lfs f0, 0x20(r1)
    addi r30, r30, 0x1
    cmplwi r30, 0x9
    li r0, 0x0
    fneg f0, f0
    addi r28, r28, 0x24
    stfs f0, 0x40(r29)
    lfs f0, 0x1c(r1)
    stfs f0, 0x44(r29)
    lfs f0, 0x18(r1)
    stfs f0, 0x48(r29)
    stfs f29, 0x4c(r29)
    stb r0, 0x50(r29)
    addi r29, r29, 0x38
    blt BiribiriLand_Init_L_801353D0
    BiribiriLand_Init_L_801354B4:
    stw r27, 0x30(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq BiribiriLand_Init_L_80135528
    lfs f3, lbl_806D736C(r2)
    mr r4, r26
    lfs f2, lbl_806D7330(r2)
    addi r3, r26, 0xc
    stfs f3, 0x0(r26)
    addi r5, r26, 0x18
    lfs f1, lbl_806D7370(r2)
    stfs f2, 0x4(r26)
    lfs f0, lbl_806D7374(r2)
    stfs f1, 0x8(r26)
    stfs f3, 0xc(r26)
    stfs f2, 0x10(r26)
    stfs f0, 0x14(r26)
    bl Vec3_Subtract
    addi r3, r26, 0x18
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r26)
    fneg f0, f0
    stfs f0, 0x24(r26)
    lfs f0, 0x1c(r26)
    stfs f0, 0x28(r26)
    lfs f0, 0x18(r26)
    stfs f0, 0x2c(r26)
    BiribiriLand_Init_L_80135528:
    stw r26, 0x34(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne BiribiriLand_Init_L_80135554
    li r3, 0x1b4
    bl Alloc
    mr. r26, r3
    beq BiribiriLand_Init_L_80135550
    li r4, 0x1
    bl WeatherSystem_Init
    BiribiriLand_Init_L_80135550:
    stw r26, g_weatherSystem(r13)
    BiribiriLand_Init_L_80135554:
    li r3, 0x1
    bl SetResourceLoadingFlag
    mr r3, r31
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    lmw r26, 0x38(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}


