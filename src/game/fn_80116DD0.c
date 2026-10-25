extern void AnimStatePool_Alloc();
extern void AnimStatePool_Free();
extern void AnimState_GetTotalScaleX();
extern void AnimState_GetTotalScaleY();
extern void AnimState_GetTotalScaleZ();
extern void AnimState_SetGlobalScale();
extern void AnimState_Step();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern void Item_InitLaunchFromKart();
extern void KartDriver_GetJointByIdx();
extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_Scale_PerAxis();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern unsigned int lbl_806D6AC0;
extern unsigned int lbl_806D6B14;
extern unsigned int lbl_806D6B24;
extern unsigned int lbl_806D6B28;
extern unsigned int lbl_80422064[];
asm void fn_80116DD0(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80116DD0[8] = {
    0x18, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80116DD0 = {
    (void *)&fn_80116DD0, 0x00000250, (void *)extab_fn_80116DD0
};



asm void fn_80116DD0(void) { /* 0x80116DD0 size:0x250 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    stw r29, 0x94(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xca(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq fn_80116DD0_L_80116E74
    bge fn_80116DD0_L_80116FDC
    cmpwi r0, 0x0
    bge fn_80116DD0_L_80116E20
    b fn_80116DD0_L_80116FDC
    fn_80116DD0_L_80116E20:
    lfs f1, lbl_806D6AC0(r2)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lis r3, lbl_80422064@ha
    addi r3, r3, lbl_80422064@l
    bl AnimStatePool_Alloc
    stw r3, 0x6c(r31)
    lfs f1, lbl_806D6B14(r2)
    lwz r3, 0x6c(r31)
    bl AnimState_SetGlobalScale
    li r0, 0x1
    lfs f0, lbl_806D6AC0(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    fn_80116DD0_L_80116E74:
    lfs f1, lbl_806D6AC0(r2)
    mr r3, r30
    lfs f2, lbl_806D6B24(r2)
    li r4, 0x1
    lfs f3, lbl_806D6B14(r2)
    bl GabyouItem_BuildLocalTransformFromHandJoint
    lwz r3, 0x6c(r31)
    cmplwi r3, 0x0
    beq fn_80116DD0_L_80116F04
    mr r29, r3
    bl AnimState_Step
    addi r3, r1, 0x48
    bl Matrix4_Identity
    mr r3, r29
    bl AnimState_GetTotalScaleZ
    fmr f30, f1
    mr r3, r29
    bl AnimState_GetTotalScaleY
    fmr f31, f1
    mr r3, r29
    bl AnimState_GetTotalScaleX
    fmr f2, f31
    addi r3, r1, 0x48
    fmr f3, f30
    mr r4, r3
    bl Mtx44_Scale_PerAxis
    addi r3, r1, 0x8
    addi r4, r30, 0x48
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x8
    addi r4, r1, 0x48
    mr r5, r3
    bl Matrix4_Multiply
    addi r3, r30, 0x48
    addi r4, r1, 0x8
    bl DbgScene_CopyMatrix3x4Transpose
    fn_80116DD0_L_80116F04:
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq fn_80116DD0_L_80116F20
    li r0, 0x0
    stb r0, 0x28(r30)
    b fn_80116DD0_L_80116F28
    fn_80116DD0_L_80116F20:
    li r0, 0x1
    stb r0, 0x28(r30)
    fn_80116DD0_L_80116F28:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq fn_80116DD0_L_80116FA8
    bge fn_80116DD0_L_80116FDC
    cmpwi r0, 0x1
    bge fn_80116DD0_L_80116F48
    b fn_80116DD0_L_80116FDC
    fn_80116DD0_L_80116F48:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    stb r0, 0xa0(r31)
    lwz r3, 0x6c(r31)
    cmplwi r3, 0x0
    beq fn_80116DD0_L_80116F68
    bl AnimStatePool_Free
    fn_80116DD0_L_80116F68:
    li r0, 0x0
    addi r3, r30, 0x14
    stw r0, 0x6c(r31)
    li r4, 0x0
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D6B28(r2)
    mr r3, r30
    lfs f2, lbl_806D6AC0(r2)
    addi r4, r31, 0x34
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b fn_80116DD0_L_80116FF4
    fn_80116DD0_L_80116FA8:
    li r0, 0x0
    stb r0, 0xa0(r31)
    lwz r3, 0x6c(r31)
    cmplwi r3, 0x0
    beq fn_80116DD0_L_80116FC0
    bl AnimStatePool_Free
    fn_80116DD0_L_80116FC0:
    li r3, 0x0
    li r0, 0x3
    stw r3, 0x6c(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b fn_80116DD0_L_80116FF4
    fn_80116DD0_L_80116FDC:
    lwz r3, 0x98(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    fn_80116DD0_L_80116FF4:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    lwz r0, 0xc4(r1)
    lwz r29, 0x94(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}
