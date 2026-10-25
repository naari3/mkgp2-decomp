extern void AnimState_GetTotalScaleX();
extern void AnimState_GetTotalScaleY();
extern void AnimState_GetTotalScaleZ();
extern void AnimState_SetEnabledTimers();
extern void AnimState_SetGlobalScale();
extern void AnimState_Step();
extern void BuildOrientationFromYaw();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void DrawEffect_SpawnDirect();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void FindNearestDriverWithinConeAndRadius();
extern void GetSpawnPosition();
extern void ItemObject_SpawnWithAlias();
extern void JointByName_GetWorldPosition();
extern void KartBurstShard_SpawnSet();
extern void KartCharacterParam_GetIdentityIndex();
extern void KartDriver_GetJointByIdx();
extern void KartDriver_GetKartRootMtx();
extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotY();
extern void Matrix4_PreMultiplyTranslation();
extern void Mtx44_GetPitchOfPosZ_Padded();
extern void Mtx44_GetTranslation_ColMajor();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_GetYawOfPosZ_Padded();
extern void Mtx44_Lerp();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_TransformVec3();
extern void Mtx44_Translate();
extern void Mtx_TransposeToMtx44();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetJointScaleByName();
extern void SpriteSlot_TickAnim();
extern void fn_800D4174();
extern unsigned int lbl_806CF410;
extern unsigned int lbl_806CF414;
extern unsigned int lbl_806CF418;
extern unsigned int lbl_806CF41C;
extern unsigned int lbl_806D6A18;
extern unsigned int lbl_806D6A1C;
extern unsigned int lbl_806D6A20;
extern unsigned int lbl_806D6A60;
extern unsigned int lbl_806D6A64;
extern unsigned int lbl_80332498[];
extern unsigned int lbl_803324AC[];
extern unsigned int lbl_80421F20[];
asm void fn_80114990(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80114990[8] = {
    0x20, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80114990 = {
    (void *)&fn_80114990, 0x00000788, (void *)extab_fn_80114990
};



asm void fn_80114990(void) { /* 0x80114990 size:0x788 */
    nofralloc
    stwu r1, -0x1e0(r1)
    mflr r0
    stw r0, 0x1e4(r1)
    stfd f31, 0x1d0(r1)
    psq_st f31, 0x1d8(r1), 0, 0
    stfd f30, 0x1c0(r1)
    psq_st f30, 0x1c8(r1), 0, 0
    stw r31, 0x1bc(r1)
    stw r30, 0x1b8(r1)
    stw r29, 0x1b4(r1)
    stw r28, 0x1b0(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xca(r3)
    extsb r0, r0
    cmpwi r0, 0x3
    beq fn_80114990_L_80114A90
    bge fn_80114990_L_801149F0
    cmpwi r0, 0x1
    beq fn_80114990_L_80114A38
    bge fn_80114990_L_80114A6C
    cmpwi r0, 0x0
    bge fn_80114990_L_80114A00
    b fn_80114990_L_80114C3C
    fn_80114990_L_801149F0:
    cmpwi r0, 0x5
    beq fn_80114990_L_80114C04
    bge fn_80114990_L_80114C3C
    b fn_80114990_L_80114BEC
    fn_80114990_L_80114A00:
    li r0, 0x258
    lfs f0, lbl_806D6A20(r2)
    stw r0, 0x4(r31)
    li r3, 0x0
    li r0, 0x3c
    stfs f0, 0x14(r31)
    stb r3, 0x0(r31)
    stfs f0, 0x18(r31)
    stfs f0, 0x1c(r31)
    stb r3, 0x1(r31)
    stw r0, 0xc(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    fn_80114990_L_80114A38:
    lfs f2, 0x18(r31)
    lfs f0, lbl_806D6A1C(r2)
    lfs f1, lbl_806D6A18(r2)
    fadds f0, f2, f0
    stfs f0, 0x18(r31)
    lfs f0, 0x18(r31)
    fcmpo cr0, f1, f0
    bge fn_80114990_L_80114C3C
    stfs f1, 0x18(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b fn_80114990_L_80114C3C
    fn_80114990_L_80114A6C:
    li r0, 0xa
    lfs f1, lbl_806D6A20(r2)
    stw r0, 0x8(r31)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    fn_80114990_L_80114A90:
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq fn_80114990_L_80114ACC
    lfs f1, 0x14(r31)
    lfs f0, lbl_806CF410(r13)
    fadds f0, f1, f0
    stfs f0, 0x14(r31)
    lfs f1, lbl_806CF414(r13)
    lfs f0, 0x14(r31)
    fcmpo cr0, f1, f0
    bge fn_80114990_L_80114AFC
    stfs f1, 0x14(r31)
    li r0, 0x0
    stb r0, 0x0(r31)
    b fn_80114990_L_80114AFC
    fn_80114990_L_80114ACC:
    lfs f1, 0x14(r31)
    lfs f0, lbl_806CF410(r13)
    fsubs f0, f1, f0
    stfs f0, 0x14(r31)
    lfs f0, lbl_806CF414(r13)
    lfs f1, 0x14(r31)
    fneg f0, f0
    fcmpo cr0, f1, f0
    bge fn_80114990_L_80114AFC
    stfs f0, 0x14(r31)
    li r0, 0x1
    stb r0, 0x0(r31)
    fn_80114990_L_80114AFC:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_80114990_L_80114BD4
    lwz r3, 0x98(r31)
    bl KartDriver_GetKartRootMtx
    bl Mtx44_GetYawOfPosZ_Padded
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    fmr f30, f1
    lwz r3, 0x98(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x5c
    bl Mtx44_GetTranslation_RowMajor
    lwz r6, 0x5c(r1)
    fmr f1, f30
    lwz r4, 0x60(r1)
    addi r3, r1, 0x50
    lwz r0, 0x64(r1)
    li r5, 0x1
    stw r6, 0x50(r1)
    lfs f2, lbl_806CF41C(r13)
    stw r4, 0x54(r1)
    lfs f3, lbl_806CF418(r13)
    stw r0, 0x58(r1)
    lwz r4, 0x98(r31)
    bl FindNearestDriverWithinConeAndRadius
    stw r3, 0x9c(r31)
    lwz r3, 0x9c(r31)
    cmplwi r3, 0x0
    beq fn_80114990_L_80114BAC
    lwz r5, 0x304(r3)
    li r4, 0x0
    lis r0, 0x80
    lwz r3, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    beq fn_80114990_L_80114BAC
    stw r4, 0x9c(r31)
    fn_80114990_L_80114BAC:
    li r0, 0x1
    lfs f1, lbl_806D6A20(r2)
    stb r0, 0x1(r31)
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b fn_80114990_L_80114C3C
    fn_80114990_L_80114BD4:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne fn_80114990_L_80114C3C
    li r0, 0x5
    stb r0, 0xca(r30)
    b fn_80114990_L_80114C3C
    fn_80114990_L_80114BEC:
    lbz r0, 0x1e(r30)
    cmpwi r0, 0x1
    bne fn_80114990_L_80114C3C
    li r0, 0x2
    stb r0, 0xca(r30)
    b fn_80114990_L_80114C3C
    fn_80114990_L_80114C04:
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D6A1C(r2)
    lfs f0, lbl_806D6A20(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge fn_80114990_L_80114C3C
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b fn_80114990_L_801150E8
    fn_80114990_L_80114C3C:
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq fn_80114990_L_80114C58
    li r0, 0x0
    stb r0, 0x28(r30)
    b fn_80114990_L_80114C60
    fn_80114990_L_80114C58:
    li r0, 0x1
    stb r0, 0x28(r30)
    fn_80114990_L_80114C60:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_80114990_L_80114CA0
    lwz r3, 0x98(r31)
    li r4, 0x0
    li r0, 0x400
    lwz r5, 0x304(r3)
    lwz r3, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne fn_80114990_L_80114CA0
    stw r4, 0x4(r31)
    fn_80114990_L_80114CA0:
    lwz r3, 0x98(r31)
    li r4, 0xf
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r1, 0x168
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x128
    bl Matrix4_Identity
    addi r3, r1, 0x128
    lfs f1, lbl_806D6A60(r2)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    lwz r3, 0x98(r31)
    bl KartCharacterParam_GetIdentityIndex
    mulli r5, r3, 0xc
    lis r4, lbl_80421F20@ha
    addi r3, r1, 0x128
    addi r0, r4, lbl_80421F20@l
    add r8, r0, r5
    mr r4, r3
    lwz r7, 0x0(r8)
    addi r5, r1, 0x44
    lwz r6, 0x4(r8)
    lwz r0, 0x8(r8)
    stw r7, 0x44(r1)
    stw r6, 0x48(r1)
    stw r0, 0x4c(r1)
    bl Mtx44_Translate
    addi r3, r1, 0x128
    addi r5, r1, 0x168
    mr r4, r3
    bl Matrix4_Multiply
    lbz r0, 0xca(r30)
    cmpwi r0, 0x1
    bne fn_80114990_L_80114D68
    lwz r4, 0x5c(r31)
    cmplwi r4, 0x0
    beq fn_80114990_L_80114D48
    addi r3, r1, 0xe8
    addi r4, r4, 0x48
    bl Mtx_TransposeToMtx44
    b fn_80114990_L_80114D54
    fn_80114990_L_80114D48:
    addi r3, r1, 0xe8
    addi r4, r30, 0x48
    bl Mtx_TransposeToMtx44
    fn_80114990_L_80114D54:
    addi r3, r1, 0x128
    lfs f1, 0x18(r31)
    mr r4, r3
    addi r5, r1, 0xe8
    bl Mtx44_Lerp
    fn_80114990_L_80114D68:
    lwz r3, 0x5c(r31)
    cmplwi r3, 0x0
    beq fn_80114990_L_80114DA8
    addi r3, r3, 0x48
    addi r4, r1, 0x128
    bl DbgScene_CopyMatrix3x4Transpose
    lwz r4, 0x5c(r31)
    addi r3, r4, 0xa0
    addi r4, r4, 0x48
    bl Mtx44_GetTranslation_RowMajor
    lbz r0, 0x28(r30)
    lwz r3, 0x5c(r31)
    stb r0, 0x28(r3)
    lfs f0, 0x2c(r30)
    lwz r3, 0x5c(r31)
    stfs f0, 0x2c(r3)
    fn_80114990_L_80114DA8:
    addi r3, r1, 0x128
    bl fn_800D4174
    stfs f1, 0xc4(r30)
    addi r3, r30, 0xa0
    lfs f1, lbl_806D6A20(r2)
    lfs f2, lbl_806D6A18(r2)
    fmr f3, f1
    bl GetSpawnPosition
    lwz r6, 0xa0(r30)
    addi r3, r30, 0xa0
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x128
    addi r5, r1, 0x38
    stw r6, 0x38(r1)
    stw r0, 0x3c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x40(r1)
    bl Mtx44_TransformVec3
    lwz r3, 0x98(r31)
    bl KartDriver_GetKartRootMtx
    bl Mtx44_GetPitchOfPosZ_Padded
    stfs f1, 0xac(r30)
    lwz r3, 0x98(r31)
    bl KartDriver_GetKartRootMtx
    bl Mtx44_GetYawOfPosZ_Padded
    stfs f1, 0xb0(r30)
    addi r3, r1, 0xa8
    bl Matrix4_Identity
    lfs f1, lbl_806D6A20(r2)
    addi r3, r1, 0xa8
    lfs f2, lbl_806D6A64(r2)
    mr r4, r3
    fmr f3, f1
    bl Matrix4_PreMultiplyTranslation
    addi r3, r1, 0xa8
    lfs f1, lbl_806D6A60(r2)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    addi r3, r1, 0xa8
    lfs f1, 0x14(r31)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    addi r3, r1, 0xa8
    lfs f1, 0xc4(r30)
    mr r4, r3
    bl Mtx44_Scale_Uniform
    addi r3, r1, 0xa8
    lfs f1, 0xac(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    addi r3, r1, 0xa8
    lfs f1, 0xb0(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    lwz r6, 0xa0(r30)
    addi r3, r1, 0xa8
    lwz r0, 0xa4(r30)
    mr r4, r3
    addi r5, r1, 0x2c
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x34(r1)
    bl Mtx44_Translate
    addi r3, r30, 0x48
    addi r4, r1, 0xa8
    bl DbgScene_CopyMatrix3x4Transpose
    lbz r0, 0x1d(r30)
    cmpwi r0, 0x1
    bne fn_80114990_L_80114F8C
    lwz r3, 0x6c(r31)
    cmplwi r3, 0x0
    beq fn_80114990_L_80114F8C
    lwz r0, 0x70(r31)
    cmplwi r0, 0x0
    beq fn_80114990_L_80114F8C
    lfs f1, lbl_806D6A20(r2)
    mr r29, r3
    mr r28, r0
    bl AnimState_SetGlobalScale
    lfs f1, lbl_806D6A20(r2)
    mr r3, r28
    bl AnimState_SetGlobalScale
    lfs f1, 0x20(r30)
    mr r3, r29
    bl AnimState_SetEnabledTimers
    lfs f1, 0x20(r30)
    mr r3, r28
    bl AnimState_SetEnabledTimers
    mr r3, r29
    bl AnimState_Step
    mr r3, r28
    bl AnimState_Step
    mr r3, r29
    bl AnimState_GetTotalScaleZ
    fmr f31, f1
    mr r3, r29
    bl AnimState_GetTotalScaleY
    fmr f30, f1
    mr r3, r29
    bl AnimState_GetTotalScaleX
    fmr f2, f30
    lis r3, lbl_803324AC@ha
    fmr f3, f31
    addi r4, r3, lbl_803324AC@l
    addi r3, r30, 0x14
    bl SpriteSlot_SetJointScaleByName
    mr r3, r28
    bl AnimState_GetTotalScaleZ
    fmr f30, f1
    mr r3, r28
    bl AnimState_GetTotalScaleY
    fmr f31, f1
    mr r3, r28
    bl AnimState_GetTotalScaleX
    fmr f2, f31
    lis r3, lbl_80332498@ha
    fmr f3, f30
    addi r4, r3, lbl_80332498@l
    addi r3, r30, 0x14
    bl SpriteSlot_SetJointScaleByName
    fn_80114990_L_80114F8C:
    lbz r28, 0x28(r30)
    li r0, 0x1
    addi r3, r30, 0x14
    stb r0, 0x28(r30)
    extsb r28, r28
    bl SpriteSlot_TickAnim
    stb r28, 0x28(r30)
    lbz r0, 0x1(r31)
    cmplwi r0, 0x0
    beq fn_80114990_L_801150E8
    li r3, 0x9e
    li r4, 0xff
    bl ItemObject_SpawnWithAlias
    mr. r29, r3
    beq fn_80114990_L_80115018
    lis r4, lbl_80332498@ha
    addi r3, r29, 0xa0
    addi r5, r4, lbl_80332498@l
    addi r4, r30, 0x14
    bl JointByName_GetWorldPosition
    lwz r3, 0x98(r31)
    bl KartDriver_GetKartRootMtx
    bl Mtx44_GetYawOfPosZ_Padded
    stfs f1, 0xb0(r29)
    lfs f1, 0xb0(r29)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r29)
    lwz r0, 0x94(r31)
    stw r0, 0x180(r29)
    lwz r0, 0x98(r31)
    stw r0, 0x184(r29)
    lwz r0, 0x9c(r31)
    stw r0, 0x168(r29)
    fn_80114990_L_80115018:
    lbz r0, 0x28(r30)
    extsb. r0, r0
    beq fn_80114990_L_801150B8
    lis r3, KartBurstShard_SpawnSet@ha
    addi r3, r3, KartBurstShard_SpawnSet@l
    bl DrawEffect_SpawnDirect
    lis r4, lbl_80332498@ha
    mr r29, r3
    addi r5, r4, lbl_80332498@l
    addi r3, r1, 0x8
    addi r4, r30, 0x14
    bl JointByName_GetWorldPosition
    addi r3, r1, 0x68
    addi r4, r30, 0x48
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x14
    addi r4, r1, 0x68
    bl Mtx44_GetTranslation_ColMajor
    lfs f2, 0x14(r1)
    addi r3, r1, 0x68
    lfs f1, 0x18(r1)
    mr r4, r3
    lfs f0, 0x1c(r1)
    fneg f6, f2
    lfs f5, 0x8(r1)
    fneg f4, f1
    lfs f2, 0xc(r1)
    fneg f3, f0
    lfs f0, 0x10(r1)
    fadds f1, f6, f5
    fadds f2, f4, f2
    fadds f3, f3, f0
    bl Matrix4_PreMultiplyTranslation
    addi r3, r29, 0x48
    addi r4, r1, 0x68
    bl DbgScene_CopyMatrix3x4Transpose
    lwz r0, 0x98(r31)
    mr r3, r29
    stw r0, 0x11c(r29)
    bl KartBurstShard_SpawnSet
    fn_80114990_L_801150B8:
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x20
    lwz r0, 0xa4(r30)
    li r3, 0xd0
    li r5, 0x0
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x28(r1)
    bl SoundMgr_PlaySE_Positional
    li r0, 0x0
    stb r0, 0x1(r31)
    fn_80114990_L_801150E8:
    psq_l f31, 0x1d8(r1), 0, 0
    lfd f31, 0x1d0(r1)
    psq_l f30, 0x1c8(r1), 0, 0
    lfd f30, 0x1c0(r1)
    lwz r31, 0x1bc(r1)
    lwz r30, 0x1b8(r1)
    lwz r29, 0x1b4(r1)
    lwz r0, 0x1e4(r1)
    lwz r28, 0x1b0(r1)
    mtlr r0
    addi r1, r1, 0x1e0
    blr
}
