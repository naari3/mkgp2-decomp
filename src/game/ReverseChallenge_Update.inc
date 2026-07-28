/* === extracted from auto_ReverseChallenge_Upd_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BananaField_CheckCollision();
extern void CObj_ApplyScissor();
extern void CObj_ApplyViewport();
extern void CObj_LoadIntoGX();
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
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void KartMovement_SetSpeedScale();
extern void LakituStart_UpdateCountdown();
extern void MiniGame_GetTimerValue();
extern void Mtx44_GetTranslation_RowMajor();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void NokoNokoChallenge_HandleBrakeInput();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void Object_SetByte10_Return1();
extern void SetCoinCount();
extern void TransitionEffect_Tick();
extern void Vec2_RotateY();
extern void Vec3_Add_DestFirst();
extern void Vec3_Dot();
extern void Vec3_Subtract();
extern void Vec3_Subtract_DestFirst();
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
extern unsigned int lbl_806D4F48;
extern unsigned int lbl_806D4F4C;
extern unsigned int lbl_806D4F50;
extern unsigned int lbl_806D4F54;
extern unsigned int lbl_806D4F58;
extern unsigned int lbl_806D4F5C;
extern unsigned int lbl_806D4F60;
extern unsigned int lbl_806D4F64;
extern unsigned int lbl_806D4F68;
extern unsigned int lbl_806D4F70;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80328DD8[];
extern unsigned int lbl_805DF338[];
extern unsigned int lbl_805DF344[];

/* --- function index (1 fns, .text 0x800AD134..0x800AD910) ---
 * [  0] 0x800AD134 size:0x7DC   global ReverseChallenge_Update
 */

/* --- forward decls --- */
asm void ReverseChallenge_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ReverseChallenge_Update[8] = {
    0x18, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ReverseChallenge_Update = {
    (void *)&ReverseChallenge_Update, 0x000007DC, (void *)extab_ReverseChallenge_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ReverseChallenge_Update(void) { /* 0x800AD134 size:0x7DC */
    nofralloc
    stwu r1, -0x2e0(r1)
    mflr r0
    stw r0, 0x2e4(r1)
    stfd f31, 0x2d0(r1)
    psq_st f31, 0x2d8(r1), 0, 0
    stfd f30, 0x2c0(r1)
    psq_st f30, 0x2c8(r1), 0, 0
    stfd f29, 0x2b0(r1)
    psq_st f29, 0x2b8(r1), 0, 0
    stw r31, 0x2ac(r1)
    stw r30, 0x2a8(r1)
    stw r29, 0x2a4(r1)
    mr r31, r3
    lbz r0, 0x40(r3)
    cmplwi r0, 0x0
    bne ReverseChallenge_Update_L_800AD17C
    li r0, 0x1
    stb r0, 0x40(r31)
    ReverseChallenge_Update_L_800AD17C:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    mr r30, r3
    cmplwi r0, 0x1
    beq ReverseChallenge_Update_L_800AD4AC
    lbz r0, lbl_806D1290(r13)
    cmplwi r0, 0x0
    bne ReverseChallenge_Update_L_800AD1C4
    lwz r12, 0x0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fmr f29, f1
    b ReverseChallenge_Update_L_800AD1C8
    ReverseChallenge_Update_L_800AD1C4:
    lfs f29, lbl_806D4F48(r2)
    ReverseChallenge_Update_L_800AD1C8:
    mr r3, r30
    fmr f31, f29
    lwz r12, 0x0(r30)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lwz r12, 0x0(r30)
    fmr f30, f1
    mr r3, r30
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D4F50(r2)
    li r30, 0x0
    fcmpo cr0, f29, f0
    fmr f29, f1
    bge ReverseChallenge_Update_L_800AD224
    fcmpo cr0, f30, f0
    bge ReverseChallenge_Update_L_800AD224
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq ReverseChallenge_Update_L_800AD224
    li r30, 0x1
    ReverseChallenge_Update_L_800AD224:
    mr r3, r31
    mr r4, r30
    bl NokoNokoChallenge_HandleBrakeInput
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne ReverseChallenge_Update_L_800AD240
    lfs f31, lbl_806D4F4C(r2)
    ReverseChallenge_Update_L_800AD240:
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x8c
    bl Mtx44_GetTranslation_RowMajor
    lis r3, lbl_80328DD8@ha
    lwz r4, 0x2c(r31)
    addi r3, r3, lbl_80328DD8@l
    lfs f5, 0x8c(r1)
    lfs f0, 0x8(r3)
    lfs f6, 0x94(r1)
    lfs f1, 0xc(r3)
    fsubs f4, f5, f0
    lfs f0, 0x4(r4)
    fsubs f2, f6, f1
    lfs f1, 0x0(r4)
    fmuls f0, f4, f0
    lfs f3, lbl_806D4F54(r2)
    fneg f2, f2
    fmadds f0, f2, f1, f0
    fcmpo cr0, f0, f3
    ble ReverseChallenge_Update_L_800AD2A4
    li r0, 0x0
    b ReverseChallenge_Update_L_800AD31C
    ReverseChallenge_Update_L_800AD2A4:
    lfs f0, 0xc(r4)
    lfs f1, 0x8(r4)
    fmuls f0, f4, f0
    fmadds f0, f2, f1, f0
    fcmpo cr0, f0, f3
    ble ReverseChallenge_Update_L_800AD2C4
    li r0, 0x0
    b ReverseChallenge_Update_L_800AD31C
    ReverseChallenge_Update_L_800AD2C4:
    lfs f0, 0x18(r3)
    lfs f1, 0x1c(r3)
    fsubs f4, f5, f0
    lfs f0, 0x14(r4)
    fsubs f2, f6, f1
    lfs f1, 0x10(r4)
    fmuls f0, f4, f0
    fneg f2, f2
    fmadds f0, f2, f1, f0
    fcmpo cr0, f0, f3
    ble ReverseChallenge_Update_L_800AD2F8
    li r0, 0x0
    b ReverseChallenge_Update_L_800AD31C
    ReverseChallenge_Update_L_800AD2F8:
    lfs f0, 0x1c(r4)
    lfs f1, 0x18(r4)
    fmuls f0, f4, f0
    fmadds f0, f2, f1, f0
    fcmpo cr0, f0, f3
    ble ReverseChallenge_Update_L_800AD318
    li r0, 0x0
    b ReverseChallenge_Update_L_800AD31C
    ReverseChallenge_Update_L_800AD318:
    li r0, 0x1
    ReverseChallenge_Update_L_800AD31C:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne ReverseChallenge_Update_L_800AD3C8
    lwz r3, 0x14(r31)
    lwz r3, 0x28(r3)
    lfs f0, 0x1c8(r3)
    fctiwz f0, f0
    stfd f0, 0x288(r1)
    lwz r4, 0x28c(r1)
    cmpwi r4, 0x0
    bge ReverseChallenge_Update_L_800AD378
    lis r3, 0xb60b
    neg r4, r4
    addi r0, r3, 0x60b7
    mulhw r0, r0, r4
    add r0, r0, r4
    srawi r0, r0, 8
    srwi r3, r0, 31
    add r0, r0, r3
    mulli r0, r0, 0x168
    subf r3, r0, r4
    subi r4, r3, 0x168
    b ReverseChallenge_Update_L_800AD39C
    ReverseChallenge_Update_L_800AD378:
    lis r3, 0xb60b
    addi r0, r3, 0x60b7
    mulhw r0, r0, r4
    add r0, r0, r4
    srawi r0, r0, 8
    srwi r3, r0, 31
    add r0, r0, r3
    mulli r0, r0, 0x168
    subf r4, r0, r4
    ReverseChallenge_Update_L_800AD39C:
    cmpwi r4, 0x0
    blt ReverseChallenge_Update_L_800AD3B0
    cmpwi r4, 0xaa
    bge ReverseChallenge_Update_L_800AD3B0
    lfs f29, lbl_806D4F4C(r2)
    ReverseChallenge_Update_L_800AD3B0:
    cmpwi r4, 0xbe
    ble ReverseChallenge_Update_L_800AD3C4
    cmpwi r4, 0x168
    bge ReverseChallenge_Update_L_800AD3C4
    lfs f29, lbl_806D4F58(r2)
    ReverseChallenge_Update_L_800AD3C4:
    lfs f31, lbl_806D4F4C(r2)
    ReverseChallenge_Update_L_800AD3C8:
    bl IsRaceStarted
    fmr f1, f29
    mr r4, r3
    fmr f2, f31
    lwz r3, 0x14(r31)
    fmr f3, f30
    bl CarObject_ApplyInput
    lwz r3, 0x14(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x14(r31)
    li r5, 0x0
    lwz r4, 0x1c(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    lwz r3, 0x1c(r31)
    addi r4, r1, 0x80
    bl CObj_LoadProjMatrix
    lwz r3, 0x1c(r31)
    addi r4, r1, 0x74
    bl CObj_ApplyScissor
    addi r3, r1, 0x68
    addi r4, r1, 0x74
    addi r5, r1, 0x80
    bl Vec3_Subtract_DestFirst
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x5c
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r1, 0x50
    addi r4, r1, 0x80
    addi r5, r1, 0x5c
    bl Vec3_Subtract_DestFirst
    addi r3, r1, 0x50
    lfs f1, lbl_806D4F5C(r2)
    mr r4, r3
    bl Vec2_RotateY
    addi r3, r1, 0x80
    addi r4, r1, 0x5c
    addi r5, r1, 0x50
    bl Vec3_Add_DestFirst
    addi r3, r1, 0x68
    lfs f1, lbl_806D4F5C(r2)
    mr r4, r3
    bl Vec2_RotateY
    addi r3, r1, 0x74
    addi r4, r1, 0x80
    addi r5, r1, 0x68
    bl Vec3_Add_DestFirst
    lwz r3, 0x1c(r31)
    addi r4, r1, 0x80
    bl CObj_LoadIntoGX
    lwz r3, 0x1c(r31)
    addi r4, r1, 0x74
    bl CObj_ApplyViewport
    b ReverseChallenge_Update_L_800AD4F8
    ReverseChallenge_Update_L_800AD4AC:
    lfs f1, lbl_806D4F54(r2)
    li r4, 0x1
    lwz r3, 0x14(r31)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0x14(r31)
    lfs f1, lbl_806D4F60(r2)
    bl KartMovement_SetSpeedScale
    lwz r3, 0x14(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r5, r3
    lwz r3, 0x20(r31)
    lwz r4, 0x1c(r31)
    bl ChallengeGoalCamera_Update
    ReverseChallenge_Update_L_800AD4F8:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0x18(r31)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x8(r31)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r0, r3
    addi r3, r1, 0x38
    mr r30, r0
    addi r4, r31, 0x34
    lfs f0, 0xc(r30)
    addi r5, r1, 0x44
    stfs f0, 0x38(r1)
    lfs f0, 0x1c(r30)
    stfs f0, 0x3c(r1)
    lfs f0, 0x2c(r30)
    stfs f0, 0x40(r1)
    bl Vec3_Subtract
    lfs f0, 0x38(r1)
    mr r4, r30
    addi r5, r1, 0x44
    stfs f0, 0x34(r31)
    lfs f0, 0x3c(r1)
    stfs f0, 0x38(r31)
    lfs f0, 0x40(r1)
    stfs f0, 0x3c(r31)
    lwz r3, 0x30(r31)
    bl BananaField_CheckCollision
    lwz r3, 0x30(r31)
    lbz r0, 0xc(r3)
    cmplwi r0, 0x0
    beq ReverseChallenge_Update_L_800AD5BC
    addi r3, r1, 0x98
    li r4, 0x0
    li r5, 0x1ec
    bl memset
    lfs f2, 0x38(r1)
    li r0, 0x32
    lfs f1, 0x3c(r1)
    addi r4, r1, 0x98
    lfs f0, 0x40(r1)
    stfs f2, 0x138(r1)
    stfs f1, 0x13c(r1)
    stfs f0, 0x140(r1)
    stw r0, 0xa0(r1)
    lwz r3, 0x14(r31)
    bl CarObject_HandleObstacleHit
    ReverseChallenge_Update_L_800AD5BC:
    lbz r0, 0x41(r31)
    cmplwi r0, 0x0
    bne ReverseChallenge_Update_L_800AD624
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x2c
    bl Mtx44_GetTranslation_RowMajor
    lwz r30, 0x28(r31)
    addi r3, r1, 0x2c
    addi r5, r1, 0x8
    mr r4, r30
    bl Vec3_Subtract
    addi r3, r1, 0x8
    addi r4, r30, 0x24
    bl Vec3_Dot
    lfs f0, lbl_806D4F54(r2)
    fcmpo cr0, f1, f0
    ble ReverseChallenge_Update_L_800AD624
    li r0, 0x1
    stb r0, 0x42(r31)
    stb r0, 0x41(r31)
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnGoal
    ReverseChallenge_Update_L_800AD624:
    lis r4, lbl_805DF338@ha
    lwz r3, 0x1c(r31)
    addi r4, r4, lbl_805DF338@l
    bl CObj_LoadProjMatrix
    lis r4, lbl_805DF344@ha
    lwz r3, 0x1c(r31)
    addi r4, r4, lbl_805DF344@l
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lis r3, lbl_805DF344@ha
    lis r4, lbl_805DF338@ha
    addi r5, r3, lbl_805DF344@l
    addi r3, r1, 0x20
    addi r7, r4, lbl_805DF338@l
    lwz r10, 0x0(r5)
    lwz r9, 0x4(r5)
    addi r4, r1, 0x14
    lwz r8, 0x8(r5)
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r10, 0x14(r1)
    stw r9, 0x18(r1)
    stw r8, 0x1c(r1)
    stw r6, 0x20(r1)
    stw r5, 0x24(r1)
    stw r0, 0x28(r1)
    bl VfxSlotMgr_Update
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq ReverseChallenge_Update_L_800AD6EC
    lbz r0, 0x41(r31)
    cmplwi r0, 0x0
    bne ReverseChallenge_Update_L_800AD6EC
    lfs f2, lbl_806D4F54(r2)
    lfs f1, g_raceTimeRemaining(r13)
    fcmpo cr0, f2, f1
    cror eq, lt, eq
    bne ReverseChallenge_Update_L_800AD6EC
    lfs f0, lbl_806D4F64(r2)
    fsubs f0, f1, f0
    fcmpo cr0, f0, f2
    stfs f0, g_raceTimeRemaining(r13)
    bge ReverseChallenge_Update_L_800AD6EC
    stfs f2, g_raceTimeRemaining(r13)
    li r0, 0x1
    stb r0, 0x41(r31)
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    ReverseChallenge_Update_L_800AD6EC:
    lwz r3, 0x24(r31)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x14(r31)
    bl CarObject_CalcSpeedRatio
    lfs f0, lbl_806D4F68(r2)
    lwz r3, 0x24(r31)
    fmuls f1, f0, f1
    bl fn_80253EBC
    lwz r3, 0x14(r31)
    bl KartItem_GetCurrentSpeedWithBonus
    lwz r3, 0x24(r31)
    bl fn_80253EC0
    lwz r3, 0x24(r31)
    bl HUD_FrameUpdate
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ReverseChallenge_Update_L_800AD738
    li r3, 0x0
    ReverseChallenge_Update_L_800AD738:
    bl TransitionEffect_Tick
    lbz r0, 0x41(r31)
    cmplwi r0, 0x0
    beq ReverseChallenge_Update_L_800AD8C8
    lwz r0, 0x44(r31)
    cmpwi r0, 0x0
    bne ReverseChallenge_Update_L_800AD8A0
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x28c(r1)
    li r29, 0x0
    lfd f2, lbl_806D4F70(r2)
    stw r0, 0x288(r1)
    lfs f0, g_raceTimeRemaining(r13)
    lfd f1, 0x288(r1)
    fsubs f1, f1, f2
    fsubs f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x290(r1)
    lwz r30, 0x294(r1)
    bl NokoNokoChallenge_GetCoinDivisor
    cmplwi r3, 0x0
    beq ReverseChallenge_Update_L_800AD7EC
    lbz r0, 0x42(r31)
    cmplwi r0, 0x1
    bne ReverseChallenge_Update_L_800AD7EC
    lwz r5, 0x0(r3)
    li r6, 0x0
    mr r4, r5
    mr r3, r5
    b ReverseChallenge_Update_L_800AD7E0
    ReverseChallenge_Update_L_800AD7B8:
    lwz r0, 0x0(r3)
    cmpw r30, r0
    bgt ReverseChallenge_Update_L_800AD7D4
    slwi r0, r6, 3
    add r3, r5, r0
    lwz r29, 0x4(r3)
    b ReverseChallenge_Update_L_800AD7EC
    ReverseChallenge_Update_L_800AD7D4:
    addi r3, r3, 0x8
    addi r4, r4, 0x8
    addi r6, r6, 0x1
    ReverseChallenge_Update_L_800AD7E0:
    lwz r0, 0x4(r4)
    cmpwi r0, 0x0
    bgt ReverseChallenge_Update_L_800AD7B8
    ReverseChallenge_Update_L_800AD7EC:
    mr r3, r29
    bl SetCoinCount
    lbz r0, 0x42(r31)
    cmplwi r0, 0x0
    beq ReverseChallenge_Update_L_800AD840
    mr r3, r31
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    lfs f0, g_raceTimeRemaining(r13)
    mr r5, r3
    lwz r3, 0x24(r31)
    li r4, 0x1
    fctiwz f0, f0
    stfd f0, 0x290(r1)
    lwz r6, 0x294(r1)
    bl fn_80253C74
    lwz r3, 0x1c(r31)
    li r4, 0x1
    bl Object_SetByte10_Return1
    b ReverseChallenge_Update_L_800AD87C
    ReverseChallenge_Update_L_800AD840:
    mr r3, r31
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    lfs f0, g_raceTimeRemaining(r13)
    mr r5, r3
    lwz r3, 0x24(r31)
    li r4, 0x0
    fctiwz f0, f0
    stfd f0, 0x290(r1)
    lwz r6, 0x294(r1)
    bl fn_80253C74
    lwz r3, 0x1c(r31)
    li r4, 0x1
    bl Object_SetByte10_Return1
    ReverseChallenge_Update_L_800AD87C:
    lbz r5, 0x42(r31)
    mr r3, r31
    mr r4, r29
    bl NokoNokoChallenge_SaveResult
    li r3, 0x1
    li r0, 0x0
    stb r3, g_raceEnded(r13)
    stb r0, g_lakituStartAnimDone(r13)
    b ReverseChallenge_Update_L_800AD8BC
    ReverseChallenge_Update_L_800AD8A0:
    lwz r3, 0x24(r31)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq ReverseChallenge_Update_L_800AD8BC
    mr r3, r31
    bl NokoNokoChallenge_TransitionToResult
    b ReverseChallenge_Update_L_800AD8DC
    ReverseChallenge_Update_L_800AD8BC:
    lwz r3, 0x44(r31)
    addi r0, r3, 0x1
    stw r0, 0x44(r31)
    ReverseChallenge_Update_L_800AD8C8:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq ReverseChallenge_Update_L_800AD8D8
    bl fn_8016B32C
    ReverseChallenge_Update_L_800AD8D8:
    li r3, -0x2
    ReverseChallenge_Update_L_800AD8DC:
    psq_l f31, 0x2d8(r1), 0, 0
    lfd f31, 0x2d0(r1)
    psq_l f30, 0x2c8(r1), 0, 0
    lfd f30, 0x2c0(r1)
    psq_l f29, 0x2b8(r1), 0, 0
    lfd f29, 0x2b0(r1)
    lwz r31, 0x2ac(r1)
    lwz r30, 0x2a8(r1)
    lwz r0, 0x2e4(r1)
    lwz r29, 0x2a4(r1)
    mtlr r0
    addi r1, r1, 0x2e0
    blr
}

