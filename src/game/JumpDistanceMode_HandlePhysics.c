/* === extracted from auto_JumpDistanceMode_Han_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CarObject_ApplyDriftBoost();
extern void CarObject_ApplyInput();
extern void CarObject_FrameUpdate();
extern void CarObject_GetRenderObj();
extern void ChallengeGoalCamera_Update();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void Input_IsItemButtonPressed();
extern void IsRaceStarted();
extern void KartDriver_GetKartRootMtx();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_GetVelocityMagnitude();
extern void KartMovement_GetVelocityPtr();
extern void NokoNokoChallenge_HandleBrakeInput();
extern void RenderObj_UseItem();
extern void Vec3_Dot();
extern void Vec3_Subtract();
extern void fn_801699D8();
extern void fn_8023E1E4();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceEnded;
extern unsigned int g_reverseRoundFlag;
extern unsigned int lbl_806D1290;
extern unsigned int lbl_806DAD70;
extern unsigned int lbl_806DAD7C;
extern unsigned int lbl_806DAD84;
extern unsigned int lbl_806DAD88;
extern unsigned int lbl_806DAD8C;
extern unsigned int lbl_806DADAC;
extern unsigned int lbl_806DADB0;
extern unsigned int lbl_806DADB4;
extern unsigned int lbl_806DADB8;
extern unsigned int lbl_806DADBC;
extern unsigned int lbl_806DADC0;
extern unsigned int lbl_806DADC4;
extern unsigned int lbl_806DADC8;
extern unsigned int lbl_806DADCC;
extern unsigned int lbl_806DADD0;
extern unsigned int lbl_806DCF68;
extern unsigned int lbl_806DCF6C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803C3D64[];
extern unsigned int lbl_803C3D80[];

/* --- function index (1 fns, .text 0x80211550..0x80211B10) ---
 * [  0] 0x80211550 size:0x5C0   global JumpDistanceMode_HandlePhysics
 */

/* --- forward decls --- */
asm void JumpDistanceMode_HandlePhysics(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_JumpDistanceMode_HandlePhysics[8] = {
    0x18, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_JumpDistanceMode_HandlePhysics = {
    (void *)&JumpDistanceMode_HandlePhysics, 0x000005C0, (void *)extab_JumpDistanceMode_HandlePhysics
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void JumpDistanceMode_HandlePhysics(void) { /* 0x80211550 size:0x5C0 */
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
    stw r29, 0x34(r1)
    mr r31, r3
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    mr r29, r3
    cmplwi r0, 0x1
    beq JumpDistanceMode_HandlePhysics_L_80211738
    lwz r0, 0x50(r31)
    cmpwi r0, 0x1
    bge JumpDistanceMode_HandlePhysics_L_80211738
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r12, 0x0(r29)
    fmr f31, f1
    mr r3, r29
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lbz r0, lbl_806D1290(r13)
    fmr f30, f1
    cmplwi r0, 0x0
    bne JumpDistanceMode_HandlePhysics_L_802115FC
    mr r3, r29
    lwz r12, 0x0(r29)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    b JumpDistanceMode_HandlePhysics_L_80211600
    JumpDistanceMode_HandlePhysics_L_802115FC:
    lfs f1, lbl_806DADAC(r2)
    JumpDistanceMode_HandlePhysics_L_80211600:
    lfs f0, lbl_806DAD88(r2)
    fmr f29, f1
    li r30, 0x0
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_HandlePhysics_L_8021162C
    fcmpo cr0, f30, f0
    bge JumpDistanceMode_HandlePhysics_L_8021162C
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq JumpDistanceMode_HandlePhysics_L_8021162C
    li r30, 0x1
    JumpDistanceMode_HandlePhysics_L_8021162C:
    mr r3, r31
    mr r4, r30
    bl NokoNokoChallenge_HandleBrakeInput
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_HandlePhysics_L_80211648
    lfs f29, lbl_806DAD70(r2)
    JumpDistanceMode_HandlePhysics_L_80211648:
    bl IsRaceStarted
    fmr f1, f31
    mr r4, r3
    fmr f2, f29
    lwz r3, 0x8(r31)
    fmr f3, f30
    bl CarObject_ApplyInput
    li r30, 0x0
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_HandlePhysics_L_80211718
    mr r3, r29
    lis r4, 0x1
    lwz r12, 0x0(r29)
    subi r4, r4, 0x1801
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    mr r0, r3
    mr r3, r29
    lwz r12, 0x0(r29)
    lis r4, 0x1
    mr r30, r0
    lwz r12, 0x28(r12)
    subi r4, r4, 0x1c01
    mtctr r12
    bctrl
    bl Input_IsItemButtonPressed
    clrlwi. r0, r3, 24
    beq JumpDistanceMode_HandlePhysics_L_80211718
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r5, 0x0
    bl RenderObj_UseItem
    clrlwi. r0, r3, 24
    beq JumpDistanceMode_HandlePhysics_L_80211718
    lwz r3, 0x8(r31)
    li r4, 0x5
    lfs f1, lbl_806DADB0(r2)
    bl CarObject_ApplyDriftBoost
    lwz r3, 0x1c(r31)
    li r4, -0x1
    li r5, 0x0
    bl fn_8023E1E4
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    JumpDistanceMode_HandlePhysics_L_80211718:
    lwz r3, 0x8(r31)
    mr r4, r30
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r31)
    li r5, 0x0
    lwz r4, 0x14(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    b JumpDistanceMode_HandlePhysics_L_80211A44
    JumpDistanceMode_HandlePhysics_L_80211738:
    lwz r0, 0x50(r31)
    cmpwi r0, 0x1
    beq JumpDistanceMode_HandlePhysics_L_8021174C
    cmpwi r0, 0x2
    bne JumpDistanceMode_HandlePhysics_L_80211784
    JumpDistanceMode_HandlePhysics_L_8021174C:
    lfs f1, lbl_806DAD7C(r2)
    li r4, 0x1
    lwz r3, 0x8(r31)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r31)
    li r5, 0x0
    lwz r4, 0x14(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    b JumpDistanceMode_HandlePhysics_L_80211A44
    JumpDistanceMode_HandlePhysics_L_80211784:
    cmpwi r0, 0x3
    bne JumpDistanceMode_HandlePhysics_L_802118B8
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_GetVelocityMagnitude
    lfs f0, 0x68(r31)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_HandlePhysics_L_802117B4
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_GetVelocityMagnitude
    stfs f1, 0x68(r31)
    JumpDistanceMode_HandlePhysics_L_802117B4:
    lwz r3, 0x8(r31)
    lfs f1, lbl_806DAD7C(r2)
    lwz r4, 0x28(r3)
    lfs f0, lbl_806DADB4(r2)
    lfs f3, 0x1c8(r4)
    b JumpDistanceMode_HandlePhysics_L_802117D0
    JumpDistanceMode_HandlePhysics_L_802117CC:
    fsubs f3, f3, f0
    JumpDistanceMode_HandlePhysics_L_802117D0:
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    beq JumpDistanceMode_HandlePhysics_L_802117CC
    lfs f2, lbl_806DADB4(r2)
    lfs f0, lbl_806DAD7C(r2)
    b JumpDistanceMode_HandlePhysics_L_802117EC
    JumpDistanceMode_HandlePhysics_L_802117E8:
    fadds f3, f3, f2
    JumpDistanceMode_HandlePhysics_L_802117EC:
    fcmpo cr0, f3, f0
    blt JumpDistanceMode_HandlePhysics_L_802117E8
    lwz r0, g_reverseRoundFlag(r13)
    cmpwi r0, 0x0
    bne JumpDistanceMode_HandlePhysics_L_80211830
    lfs f0, lbl_806DADB8(r2)
    fcmpo cr0, f3, f0
    cror eq, lt, eq
    bne JumpDistanceMode_HandlePhysics_L_80211818
    lfs f1, lbl_806DADBC(r2)
    b JumpDistanceMode_HandlePhysics_L_8021186C
    JumpDistanceMode_HandlePhysics_L_80211818:
    lfs f0, lbl_806DADC0(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne JumpDistanceMode_HandlePhysics_L_8021186C
    lfs f1, lbl_806DAD8C(r2)
    b JumpDistanceMode_HandlePhysics_L_8021186C
    JumpDistanceMode_HandlePhysics_L_80211830:
    lfs f0, lbl_806DADC4(r2)
    fcmpo cr0, f3, f0
    cror eq, lt, eq
    bne JumpDistanceMode_HandlePhysics_L_80211858
    lfs f0, lbl_806DADC8(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne JumpDistanceMode_HandlePhysics_L_80211858
    lfs f1, lbl_806DADBC(r2)
    b JumpDistanceMode_HandlePhysics_L_8021186C
    JumpDistanceMode_HandlePhysics_L_80211858:
    lfs f0, lbl_806DAD84(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne JumpDistanceMode_HandlePhysics_L_8021186C
    lfs f1, lbl_806DAD8C(r2)
    JumpDistanceMode_HandlePhysics_L_8021186C:
    lfs f2, 0x68(r31)
    li r4, 0x1
    lfs f3, lbl_806DAD7C(r2)
    bl CarObject_ApplyInput
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r31)
    li r5, 0x0
    lwz r4, 0x14(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    lfs f1, 0x68(r31)
    lfs f0, lbl_806DADAC(r2)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_HandlePhysics_L_80211A44
    lfs f0, lbl_806DADCC(r2)
    fadds f0, f1, f0
    stfs f0, 0x68(r31)
    b JumpDistanceMode_HandlePhysics_L_80211A44
    JumpDistanceMode_HandlePhysics_L_802118B8:
    cmpwi r0, 0x4
    bne JumpDistanceMode_HandlePhysics_L_80211A04
    lfs f29, lbl_806DAD7C(r2)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    lwz r30, 0x38(r31)
    bl KartDriver_GetKartRootMtx
    lis r4, lbl_803C3D80@ha
    addi r5, r1, 0x1c
    addi r7, r4, lbl_803C3D80@l
    lwz r6, 0x0(r7)
    lwz r4, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r6, 0x10(r1)
    stw r4, 0x14(r1)
    stw r0, 0x18(r1)
    lfs f0, 0xc(r3)
    stfs f0, 0x10(r1)
    lfs f0, 0x2c(r3)
    addi r3, r1, 0x10
    stfs f0, 0x18(r1)
    lwz r4, 0x0(r30)
    bl Vec3_Subtract
    addi r3, r1, 0x1c
    addi r4, r30, 0x4
    bl Vec3_Dot
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_HandlePhysics_L_80211934
    li r0, 0x1
    b JumpDistanceMode_HandlePhysics_L_80211938
    JumpDistanceMode_HandlePhysics_L_80211934:
    li r0, 0x0
    JumpDistanceMode_HandlePhysics_L_80211938:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_HandlePhysics_L_8021199C
    lwz r0, g_reverseRoundFlag(r13)
    cmpwi r0, 0x0
    bne JumpDistanceMode_HandlePhysics_L_80211978
    lfs f29, lbl_806DAD7C(r2)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_GetVelocityPtr
    lfs f1, 0x8(r3)
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_HandlePhysics_L_8021199C
    fmr f29, f0
    b JumpDistanceMode_HandlePhysics_L_8021199C
    JumpDistanceMode_HandlePhysics_L_80211978:
    lfs f29, lbl_806DADD0(r2)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_GetVelocityPtr
    lfs f1, 0x8(r3)
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_HandlePhysics_L_8021199C
    fmr f29, f0
    JumpDistanceMode_HandlePhysics_L_8021199C:
    lfs f0, 0x68(r31)
    lfs f2, lbl_806DADAC(r2)
    fcmpo cr0, f0, f2
    ble JumpDistanceMode_HandlePhysics_L_802119B0
    b JumpDistanceMode_HandlePhysics_L_802119B4
    JumpDistanceMode_HandlePhysics_L_802119B0:
    fmr f2, f0
    JumpDistanceMode_HandlePhysics_L_802119B4:
    fmr f1, f29
    lwz r3, 0x8(r31)
    lfs f3, lbl_806DAD7C(r2)
    li r4, 0x1
    bl CarObject_ApplyInput
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r31)
    li r5, 0x0
    lwz r4, 0x14(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    lfs f1, 0x68(r31)
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_HandlePhysics_L_80211A44
    lfs f0, lbl_806DADCC(r2)
    fsubs f0, f1, f0
    stfs f0, 0x68(r31)
    b JumpDistanceMode_HandlePhysics_L_80211A44
    JumpDistanceMode_HandlePhysics_L_80211A04:
    lfs f1, lbl_806DAD7C(r2)
    li r4, 0x1
    lwz r3, 0x8(r31)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
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
    JumpDistanceMode_HandlePhysics_L_80211A44:
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lwz r5, lbl_806DCF68(r2)
    lis r4, lbl_803C3D64@ha
    lwz r0, lbl_806DCF6C(r2)
    lfs f2, 0xc(r3)
    lfsu f0, lbl_803C3D64@l(r4)
    stw r5, 0x8(r1)
    lfs f1, 0x2c(r3)
    fcmpo cr0, f2, f0
    stw r0, 0xc(r1)
    stfs f2, 0x8(r1)
    stfs f1, 0xc(r1)
    bge JumpDistanceMode_HandlePhysics_L_80211A88
    li r0, 0x0
    b JumpDistanceMode_HandlePhysics_L_80211AC8
    JumpDistanceMode_HandlePhysics_L_80211A88:
    lfs f0, 0x8(r4)
    fcmpo cr0, f2, f0
    ble JumpDistanceMode_HandlePhysics_L_80211A9C
    li r0, 0x0
    b JumpDistanceMode_HandlePhysics_L_80211AC8
    JumpDistanceMode_HandlePhysics_L_80211A9C:
    lfs f0, 0x4(r4)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_HandlePhysics_L_80211AB0
    li r0, 0x0
    b JumpDistanceMode_HandlePhysics_L_80211AC8
    JumpDistanceMode_HandlePhysics_L_80211AB0:
    lfs f0, 0xc(r4)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_HandlePhysics_L_80211AC4
    li r0, 0x0
    b JumpDistanceMode_HandlePhysics_L_80211AC8
    JumpDistanceMode_HandlePhysics_L_80211AC4:
    li r0, 0x1
    JumpDistanceMode_HandlePhysics_L_80211AC8:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_HandlePhysics_L_80211ADC
    li r0, 0x1
    stb r0, 0x88(r31)
    JumpDistanceMode_HandlePhysics_L_80211ADC:
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 0x58(r1), 0, 0
    lfd f30, 0x50(r1)
    psq_l f29, 0x48(r1), 0, 0
    lfd f29, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    lwz r0, 0x74(r1)
    lwz r29, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}
