extern void BuildOrientationFromYaw();
extern void DrawEffect_Free();
extern void DrawEffect_SpawnDirect();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void ItemEffectBus_OrMask();
extern void Item_DecayVelocityScalar();
extern void KartDriver_GetKartRootMtx();
extern void KartFxParam_GetConst1p5();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_CountActiveSEInstances();
extern void SoundMgr_PlaySE_Positional();
extern void SoundMgr_PlaySE_WithChannel();
extern void SoundMgr_StopSE_OrSpecial();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetJointScaleByName();
extern void SpriteSlot_SetScale();
extern void Vec2_RotateY();
extern void Vec3_Add_DestFirst();
extern void Vec3_HorizontalYawTo();
extern void Vec3_Lerp();
extern void fn_8010BF20();
extern unsigned int lbl_806D6808;
extern unsigned int lbl_806D680C;
extern unsigned int lbl_806D6818;
extern unsigned int lbl_806D6838;
extern unsigned int lbl_806D683C;
extern unsigned int lbl_806D6840;
extern unsigned int lbl_806D6844;
extern unsigned int lbl_806D6848;
extern unsigned int lbl_806D684C;
extern unsigned int Effect_Res5F_Init[];
extern unsigned int Effect_Res7Eor62_Variant_Init[];
extern unsigned int lbl_80331698[];
extern unsigned int lbl_805DF3D0[];
asm void fn_8010C110(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8010C110[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8010C110 = {
    (void *)&fn_8010C110, 0x00000B30, (void *)extab_fn_8010C110
};



asm void fn_8010C110(void) { /* 0x8010C110 size:0xB30 */
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    stfd f31, 0x110(r1)
    psq_st f31, 0x118(r1), 0, 0
    stw r31, 0x10c(r1)
    stw r30, 0x108(r1)
    stw r29, 0x104(r1)
    stw r28, 0x100(r1)
    mr r29, r3
    lis r3, lbl_80331698@ha
    lbz r0, 0xc9(r29)
    mr r30, r4
    addi r31, r3, lbl_80331698@l
    extsb r0, r0
    cmpwi r0, 0x2
    beq fn_8010C110_L_8010C2B4
    bge fn_8010C110_L_8010C168
    cmpwi r0, 0x0
    beq fn_8010C110_L_8010C174
    bge fn_8010C110_L_8010C1E0
    b fn_8010C110_L_8010C414
    fn_8010C110_L_8010C168:
    cmpwi r0, 0x4
    bge fn_8010C110_L_8010C414
    b fn_8010C110_L_8010C3D0
    fn_8010C110_L_8010C174:
    lfs f1, lbl_806D6818(r2)
    addi r3, r29, 0x14
    li r4, 0x3
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6808(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    lfs f1, lbl_806D6818(r2)
    addi r3, r29, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r5, 0x0
    lfs f0, lbl_806D6818(r2)
    stb r5, 0x3c(r29)
    li r4, 0x708
    li r3, 0xa
    li r0, -0x1
    stfs f0, 0x14(r30)
    stw r4, 0x4(r30)
    stw r5, 0x8(r30)
    stw r3, 0xc(r30)
    stb r5, 0x0(r30)
    stw r0, 0x30(r30)
    lbz r3, 0xc9(r29)
    addi r0, r3, 0x1
    stb r0, 0xc9(r29)
    fn_8010C110_L_8010C1E0:
    lfs f2, 0x14(r30)
    lfs f0, lbl_806D6838(r2)
    lfs f1, lbl_806D6808(r2)
    fadds f0, f2, f0
    stfs f0, 0x14(r30)
    lfs f0, 0x14(r30)
    fcmpo cr0, f1, f0
    bge fn_8010C110_L_8010C414
    stfs f1, 0x14(r30)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x72
    beq fn_8010C110_L_8010C248
    bge fn_8010C110_L_8010C220
    cmpwi r0, 0x71
    bge fn_8010C110_L_8010C22C
    b fn_8010C110_L_8010C2A4
    fn_8010C110_L_8010C220:
    cmpwi r0, 0x74
    bge fn_8010C110_L_8010C2A4
    b fn_8010C110_L_8010C278
    fn_8010C110_L_8010C22C:
    lis r3, Effect_Res5F_Init@ha
    addi r3, r3, Effect_Res5F_Init@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r30)
    li r0, 0x1
    stb r0, 0x0(r30)
    b fn_8010C110_L_8010C2A4
    fn_8010C110_L_8010C248:
    lis r3, Effect_Res7Eor62_Variant_Init@ha
    addi r3, r3, Effect_Res7Eor62_Variant_Init@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r30)
    lwz r3, 0x4c(r30)
    cmplwi r3, 0x0
    beq fn_8010C110_L_8010C2A4
    li r0, 0x1
    stb r0, 0x190(r3)
    lwz r3, 0x4c(r30)
    stw r0, 0x10(r3)
    b fn_8010C110_L_8010C2A4
    fn_8010C110_L_8010C278:
    lis r3, Effect_Res7Eor62_Variant_Init@ha
    addi r3, r3, Effect_Res7Eor62_Variant_Init@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r30)
    lwz r3, 0x4c(r30)
    cmplwi r3, 0x0
    beq fn_8010C110_L_8010C29C
    li r0, 0x1
    stb r0, 0x190(r3)
    fn_8010C110_L_8010C29C:
    li r0, 0x1
    stb r0, 0x0(r30)
    fn_8010C110_L_8010C2A4:
    lbz r3, 0xc9(r29)
    addi r0, r3, 0x1
    stb r0, 0xc9(r29)
    b fn_8010C110_L_8010C414
    fn_8010C110_L_8010C2B4:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x71
    bne fn_8010C110_L_8010C32C
    lwz r0, 0x8(r30)
    cmplwi r0, 0x0
    bne fn_8010C110_L_8010C32C
    lwz r3, 0x9c(r30)
    lwz r3, 0x304(r3)
    cmplwi r3, 0x0
    beq fn_8010C110_L_8010C2E8
    li r6, 0x0
    lis r5, 0x4000
    bl ItemEffectBus_OrMask
    fn_8010C110_L_8010C2E8:
    lwz r3, 0x4c(r30)
    cmplwi r3, 0x0
    beq fn_8010C110_L_8010C2FC
    li r0, 0x1
    stb r0, 0x191(r3)
    fn_8010C110_L_8010C2FC:
    lwz r6, 0xa0(r29)
    addi r4, r1, 0x50
    lwz r0, 0xa4(r29)
    li r3, 0x93
    li r5, 0x0
    stw r6, 0x50(r1)
    stw r0, 0x54(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x58(r1)
    bl SoundMgr_PlaySE_Positional
    li r0, 0x3c
    stw r0, 0x8(r30)
    fn_8010C110_L_8010C32C:
    lwz r0, 0x4(r30)
    cmplwi r0, 0x0
    bne fn_8010C110_L_8010C414
    lwz r0, 0x8(r29)
    cmpwi r0, 0x73
    beq fn_8010C110_L_8010C34C
    cmpwi r0, 0x72
    bne fn_8010C110_L_8010C360
    fn_8010C110_L_8010C34C:
    lwz r3, 0x4c(r30)
    cmplwi r3, 0x0
    beq fn_8010C110_L_8010C360
    li r0, 0x0
    stb r0, 0x190(r3)
    fn_8010C110_L_8010C360:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x71
    bne fn_8010C110_L_8010C390
    lwz r4, 0x30(r30)
    cmpwi r4, 0x0
    blt fn_8010C110_L_8010C388
    li r3, 0x92
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r30)
    fn_8010C110_L_8010C388:
    li r0, 0x0
    stb r0, 0x0(r30)
    fn_8010C110_L_8010C390:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x73
    bne fn_8010C110_L_8010C3C0
    lwz r4, 0x30(r30)
    cmpwi r4, 0x0
    blt fn_8010C110_L_8010C3B8
    li r3, 0x9b
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r30)
    fn_8010C110_L_8010C3B8:
    li r0, 0x0
    stb r0, 0x0(r30)
    fn_8010C110_L_8010C3C0:
    lbz r3, 0xc9(r29)
    addi r0, r3, 0x1
    stb r0, 0xc9(r29)
    b fn_8010C110_L_8010C414
    fn_8010C110_L_8010C3D0:
    lfs f2, 0x2c(r29)
    lfs f1, lbl_806D6838(r2)
    lfs f0, lbl_806D6818(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r29)
    lfs f1, 0x2c(r29)
    fcmpo cr0, f1, f0
    bge fn_8010C110_L_8010C414
    lwz r3, 0x4c(r30)
    bl DrawEffect_Free
    li r3, 0x0
    li r0, 0x3
    stw r3, 0x4c(r30)
    stb r3, 0x28(r29)
    stb r0, 0xc8(r29)
    stb r3, 0xc9(r29)
    b fn_8010C110_L_8010CC18
    fn_8010C110_L_8010C414:
    lwz r3, 0x9c(r30)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq fn_8010C110_L_8010C430
    li r0, 0x0
    stb r0, 0x28(r29)
    b fn_8010C110_L_8010C438
    fn_8010C110_L_8010C430:
    li r0, 0x1
    stb r0, 0x28(r29)
    fn_8010C110_L_8010C438:
    lfs f1, lbl_806D6808(r2)
    lfs f0, 0x14(r30)
    fcmpu cr0, f1, f0
    bne fn_8010C110_L_8010C5B8
    lwz r3, 0x9c(r30)
    lwz r3, 0x304(r3)
    cmplwi r3, 0x0
    beq fn_8010C110_L_8010C5B8
    lwz r5, 0x10(r3)
    li r4, 0x0
    lwz r6, 0x14(r3)
    lis r3, 0x1
    and r0, r5, r4
    and r3, r6, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne fn_8010C110_L_8010C484
    b fn_8010C110_L_8010C488
    fn_8010C110_L_8010C484:
    li r4, 0x1
    fn_8010C110_L_8010C488:
    clrlwi. r0, r4, 24
    beq fn_8010C110_L_8010C51C
    mr r3, r29
    mr r4, r30
    bl fn_8010BF20
    lwz r3, 0x4c(r30)
    bl DrawEffect_Free
    li r0, 0x0
    stw r0, 0x4c(r30)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x71
    bne fn_8010C110_L_8010C4D8
    lbz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq fn_8010C110_L_8010C4D0
    li r3, 0x92
    li r4, 0x0
    bl SoundMgr_StopSE_OrSpecial
    fn_8010C110_L_8010C4D0:
    li r0, 0x0
    stb r0, 0x0(r30)
    fn_8010C110_L_8010C4D8:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x73
    bne fn_8010C110_L_8010C504
    lbz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq fn_8010C110_L_8010C4FC
    li r3, 0x9b
    li r4, 0x0
    bl SoundMgr_StopSE_OrSpecial
    fn_8010C110_L_8010C4FC:
    li r0, 0x0
    stb r0, 0x0(r30)
    fn_8010C110_L_8010C504:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r29)
    stb r0, 0xc8(r29)
    stb r3, 0xc9(r29)
    b fn_8010C110_L_8010CC18
    fn_8010C110_L_8010C51C:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x72
    beq fn_8010C110_L_8010C56C
    bge fn_8010C110_L_8010C538
    cmpwi r0, 0x71
    bge fn_8010C110_L_8010C544
    b fn_8010C110_L_8010C5B8
    fn_8010C110_L_8010C538:
    cmpwi r0, 0x74
    bge fn_8010C110_L_8010C5B8
    b fn_8010C110_L_8010C594
    fn_8010C110_L_8010C544:
    lis r0, 0x20
    li r4, 0x0
    and r3, r6, r0
    and r0, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne fn_8010C110_L_8010C5B8
    stw r4, 0x4(r30)
    b fn_8010C110_L_8010C5B8
    fn_8010C110_L_8010C56C:
    lis r0, 0x40
    li r4, 0x0
    and r3, r6, r0
    and r0, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne fn_8010C110_L_8010C5B8
    stw r4, 0x4(r30)
    b fn_8010C110_L_8010C5B8
    fn_8010C110_L_8010C594:
    lis r0, 0x10
    li r4, 0x0
    and r3, r6, r0
    and r0, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne fn_8010C110_L_8010C5B8
    stw r4, 0x4(r30)
    fn_8010C110_L_8010C5B8:
    lwz r3, 0x9c(r30)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x80
    bl Mtx44_GetTranslation_RowMajor
    lwz r4, 0x3fc(r31)
    lis r3, lbl_805DF3D0@ha
    lwz r5, 0x400(r31)
    addi r3, r3, lbl_805DF3D0@l
    lwz r0, 0x404(r31)
    addi r28, r3, 0x80
    stw r4, 0x74(r1)
    mr r4, r28
    addi r3, r1, 0x80
    stw r5, 0x78(r1)
    stw r0, 0x7c(r1)
    bl Vec3_HorizontalYawTo
    addi r3, r1, 0x74
    mr r4, r3
    bl Vec2_RotateY
    addi r3, r1, 0x68
    addi r4, r1, 0x80
    addi r5, r1, 0x74
    bl Vec3_Add_DestFirst
    lwz r6, 0xa0(r29)
    addi r3, r29, 0xa0
    lwz r0, 0xa4(r29)
    addi r4, r1, 0x44
    lwz r7, 0x68(r1)
    addi r5, r1, 0x38
    stw r6, 0x38(r1)
    lwz r6, 0x6c(r1)
    stw r0, 0x3c(r1)
    lwz r0, 0x70(r1)
    lwz r8, 0xa8(r29)
    stw r8, 0x40(r1)
    stw r7, 0x44(r1)
    stw r6, 0x48(r1)
    stw r0, 0x4c(r1)
    lfs f1, 0x14(r30)
    bl Vec3_Lerp
    mr r3, r28
    addi r4, r1, 0x68
    bl Vec3_HorizontalYawTo
    lfs f3, 0x14(r30)
    fmr f31, f1
    lfs f0, lbl_806D6808(r2)
    lfs f1, 0xac(r29)
    fsubs f0, f0, f3
    lfs f2, lbl_806D683C(r2)
    fmuls f0, f1, f0
    fmadds f1, f2, f3, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r29)
    lfs f0, lbl_806D6808(r2)
    lfs f2, 0x14(r30)
    lfs f1, 0xb0(r29)
    fsubs f0, f0, f2
    fmuls f0, f1, f0
    fmadds f1, f31, f2, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r29)
    lwz r3, 0x9c(r30)
    bl KartFxParam_GetConst1p5
    lfs f0, lbl_806D680C(r2)
    mr r3, r29
    fmuls f1, f0, f1
    bl Item_DecayVelocityScalar
    lbz r0, 0x1e(r29)
    cmpwi r0, 0x1
    bne fn_8010C110_L_8010C6F0
    lfs f1, lbl_806D6818(r2)
    addi r3, r29, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6808(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    fn_8010C110_L_8010C6F0:
    lwz r12, 0x408(r31)
    li r0, 0xa
    lwz r11, 0x40c(r31)
    addi r5, r1, 0xa8
    lwz r10, 0x410(r31)
    addi r4, r31, 0x424
    lwz r9, 0x414(r31)
    lwz r8, 0x418(r31)
    lwz r7, 0x41c(r31)
    lwz r6, 0x420(r31)
    lwz r3, 0x424(r31)
    stw r12, 0x8c(r1)
    stw r11, 0x90(r1)
    stw r10, 0x94(r1)
    stw r9, 0x98(r1)
    stw r8, 0x9c(r1)
    stw r7, 0xa0(r1)
    stw r6, 0xa4(r1)
    stw r3, 0xa8(r1)
    mtctr r0
    fn_8010C110_L_8010C740:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz fn_8010C110_L_8010C740
    lbz r0, 0x1d(r29)
    lwz r5, 0x478(r31)
    lwz r4, 0x47c(r31)
    cmpwi r0, 0x3
    lwz r3, 0x480(r31)
    stw r5, 0x5c(r1)
    lfs f1, lbl_806D6808(r2)
    stw r4, 0x60(r1)
    stw r3, 0x64(r1)
    bne fn_8010C110_L_8010C9DC
    lfs f0, 0x20(r29)
    lfs f5, 0x8c(r1)
    fcmpo cr0, f0, f5
    cror eq, lt, eq
    bne fn_8010C110_L_8010C798
    lfs f1, 0x9c(r1)
    b fn_8010C110_L_8010C870
    fn_8010C110_L_8010C798:
    lfs f2, 0x98(r1)
    fcmpo cr0, f2, f0
    cror eq, lt, eq
    bne fn_8010C110_L_8010C7B0
    lfs f1, 0xa8(r1)
    b fn_8010C110_L_8010C870
    fn_8010C110_L_8010C7B0:
    fcmpo cr0, f5, f0
    fmr f4, f1
    cror eq, lt, eq
    bne fn_8010C110_L_8010C7F0
    lfs f2, 0x90(r1)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8010C110_L_8010C7F0
    fsubs f3, f2, f5
    lfs f6, 0x9c(r1)
    lfs f2, 0xa0(r1)
    fsubs f5, f0, f5
    fdivs f1, f1, f3
    fmuls f3, f5, f1
    fsubs f1, f2, f6
    fmadds f1, f3, f1, f6
    fn_8010C110_L_8010C7F0:
    lfs f5, 0x90(r1)
    fcmpo cr0, f5, f0
    cror eq, lt, eq
    bne fn_8010C110_L_8010C830
    lfs f2, 0x94(r1)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8010C110_L_8010C830
    fsubs f3, f2, f5
    lfs f6, 0xa0(r1)
    lfs f2, 0xa4(r1)
    fsubs f5, f0, f5
    fdivs f1, f4, f3
    fmuls f3, f5, f1
    fsubs f1, f2, f6
    fmadds f1, f3, f1, f6
    fn_8010C110_L_8010C830:
    lfs f5, 0x94(r1)
    fcmpo cr0, f5, f0
    cror eq, lt, eq
    bne fn_8010C110_L_8010C870
    lfs f2, 0x98(r1)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8010C110_L_8010C870
    fsubs f3, f2, f5
    lfs f6, 0xa4(r1)
    lfs f2, 0xa8(r1)
    fsubs f5, f0, f5
    fdivs f1, f4, f3
    fmuls f3, f5, f1
    fsubs f1, f2, f6
    fmadds f1, f3, f1, f6
    fn_8010C110_L_8010C870:
    lfs f2, 0xac(r1)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8010C110_L_8010C89C
    lfs f4, 0xc0(r1)
    lfs f3, 0xd4(r1)
    lfs f2, 0xe8(r1)
    stfs f4, 0x5c(r1)
    stfs f3, 0x60(r1)
    stfs f2, 0x64(r1)
    b fn_8010C110_L_8010C9C4
    fn_8010C110_L_8010C89C:
    lfs f2, 0xbc(r1)
    fcmpo cr0, f2, f0
    cror eq, lt, eq
    bne fn_8010C110_L_8010C8C8
    lfs f4, 0xd0(r1)
    lfs f3, 0xe4(r1)
    lfs f2, 0xf8(r1)
    stfs f4, 0x5c(r1)
    stfs f3, 0x60(r1)
    stfs f2, 0x64(r1)
    b fn_8010C110_L_8010C9C4
    fn_8010C110_L_8010C8C8:
    li r0, 0x2
    addi r3, r1, 0xac
    li r4, 0x0
    mtctr r0
    fn_8010C110_L_8010C8D8:
    lfs f4, 0x0(r3)
    fcmpo cr0, f4, f0
    cror eq, lt, eq
    bne fn_8010C110_L_8010C948
    lfs f2, 0x4(r3)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8010C110_L_8010C948
    fsubs f2, f2, f4
    lfs f3, lbl_806D6808(r2)
    fsubs f6, f0, f4
    lfs f7, 0x14(r3)
    lfs f4, 0x18(r3)
    fdivs f5, f3, f2
    lfs f8, 0x28(r3)
    lfs f3, 0x2c(r3)
    lfs f9, 0x3c(r3)
    lfs f2, 0x40(r3)
    fmuls f5, f6, f5
    fsubs f4, f4, f7
    fsubs f3, f3, f8
    fsubs f2, f2, f9
    fmadds f4, f5, f4, f7
    fmadds f3, f5, f3, f8
    fmadds f2, f5, f2, f9
    stfs f4, 0x5c(r1)
    stfs f3, 0x60(r1)
    stfs f2, 0x64(r1)
    fn_8010C110_L_8010C948:
    lfs f4, 0x4(r3)
    fcmpo cr0, f4, f0
    cror eq, lt, eq
    bne fn_8010C110_L_8010C9B8
    lfs f2, 0x8(r3)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8010C110_L_8010C9B8
    fsubs f2, f2, f4
    lfs f3, lbl_806D6808(r2)
    fsubs f6, f0, f4
    lfs f7, 0x18(r3)
    lfs f4, 0x1c(r3)
    fdivs f5, f3, f2
    lfs f8, 0x2c(r3)
    lfs f3, 0x30(r3)
    lfs f9, 0x40(r3)
    lfs f2, 0x44(r3)
    fmuls f5, f6, f5
    fsubs f4, f4, f7
    fsubs f3, f3, f8
    fsubs f2, f2, f9
    fmadds f4, f5, f4, f7
    fmadds f3, f5, f3, f8
    fmadds f2, f5, f2, f9
    stfs f4, 0x5c(r1)
    stfs f3, 0x60(r1)
    stfs f2, 0x64(r1)
    fn_8010C110_L_8010C9B8:
    addi r3, r3, 0x8
    addi r4, r4, 0x1
    bdnz fn_8010C110_L_8010C8D8
    fn_8010C110_L_8010C9C4:
    lfs f2, lbl_806D6844(r2)
    lfs f3, lbl_806D6840(r2)
    fdivs f2, f0, f2
    lfs f0, lbl_806D6808(r2)
    fmadds f31, f3, f2, f0
    b fn_8010C110_L_8010C9FC
    fn_8010C110_L_8010C9DC:
    lfs f1, 0xd0(r1)
    lfs f2, 0xe4(r1)
    lfs f0, 0xf8(r1)
    stfs f1, 0x5c(r1)
    lfs f1, 0xa8(r1)
    stfs f2, 0x60(r1)
    lfs f31, lbl_806D6848(r2)
    stfs f0, 0x64(r1)
    fn_8010C110_L_8010C9FC:
    lfs f2, 0x5c(r1)
    lfs f0, lbl_806D684C(r2)
    lwz r0, 0x8(r29)
    fmuls f0, f2, f0
    cmpwi r0, 0x72
    stfs f0, 0x5c(r1)
    beq fn_8010C110_L_8010CA7C
    bge fn_8010C110_L_8010CA28
    cmpwi r0, 0x71
    bge fn_8010C110_L_8010CA34
    b fn_8010C110_L_8010CB08
    fn_8010C110_L_8010CA28:
    cmpwi r0, 0x74
    bge fn_8010C110_L_8010CB08
    b fn_8010C110_L_8010CAC4
    fn_8010C110_L_8010CA34:
    fmr f2, f1
    addi r3, r29, 0x14
    fmr f3, f1
    addi r4, r31, 0x4d8
    bl SpriteSlot_SetJointScaleByName
    lfs f1, 0x5c(r1)
    addi r3, r29, 0x14
    lfs f2, 0x60(r1)
    addi r4, r31, 0x4ec
    lfs f3, 0x64(r1)
    bl SpriteSlot_SetJointScaleByName
    fmr f1, f31
    lfs f3, lbl_806D6808(r2)
    fmr f2, f31
    addi r3, r29, 0x14
    addi r4, r31, 0x500
    bl SpriteSlot_SetJointScaleByName
    b fn_8010C110_L_8010CB08
    fn_8010C110_L_8010CA7C:
    fmr f2, f1
    addi r3, r29, 0x14
    fmr f3, f1
    addi r4, r31, 0x4d8
    bl SpriteSlot_SetJointScaleByName
    lfs f1, 0x5c(r1)
    addi r3, r29, 0x14
    lfs f2, 0x60(r1)
    addi r4, r31, 0x514
    lfs f3, 0x64(r1)
    bl SpriteSlot_SetJointScaleByName
    fmr f1, f31
    lfs f3, lbl_806D6808(r2)
    fmr f2, f31
    addi r3, r29, 0x14
    addi r4, r31, 0x500
    bl SpriteSlot_SetJointScaleByName
    b fn_8010C110_L_8010CB08
    fn_8010C110_L_8010CAC4:
    fmr f2, f1
    addi r3, r29, 0x14
    fmr f3, f1
    addi r4, r31, 0x4d8
    bl SpriteSlot_SetJointScaleByName
    lfs f1, 0x5c(r1)
    addi r3, r29, 0x14
    lfs f2, 0x60(r1)
    addi r4, r31, 0x528
    lfs f3, 0x64(r1)
    bl SpriteSlot_SetJointScaleByName
    fmr f1, f31
    lfs f3, lbl_806D6808(r2)
    fmr f2, f31
    addi r3, r29, 0x14
    addi r4, r31, 0x500
    bl SpriteSlot_SetJointScaleByName
    fn_8010C110_L_8010CB08:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x71
    bne fn_8010C110_L_8010CB90
    lwz r5, 0x30(r30)
    cmpwi r5, 0x0
    bge fn_8010C110_L_8010CB6C
    lbz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq fn_8010C110_L_8010CB90
    li r3, 0x92
    bl SoundMgr_CountActiveSEInstances
    stw r3, 0x30(r30)
    lwz r5, 0x30(r30)
    cmpwi r5, 0x0
    blt fn_8010C110_L_8010CB90
    lwz r6, 0xa0(r29)
    addi r4, r1, 0x2c
    lwz r0, 0xa4(r29)
    li r3, 0x92
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x34(r1)
    bl SoundMgr_PlaySE_Positional
    b fn_8010C110_L_8010CB90
    fn_8010C110_L_8010CB6C:
    lwz r6, 0xa0(r29)
    addi r4, r1, 0x20
    lwz r0, 0xa4(r29)
    li r3, 0x92
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x28(r1)
    bl SoundMgr_PlaySE_WithChannel
    fn_8010C110_L_8010CB90:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x73
    bne fn_8010C110_L_8010CC18
    lwz r5, 0x30(r30)
    cmpwi r5, 0x0
    bge fn_8010C110_L_8010CBF4
    lbz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq fn_8010C110_L_8010CC18
    li r3, 0x9b
    bl SoundMgr_CountActiveSEInstances
    stw r3, 0x30(r30)
    lwz r5, 0x30(r30)
    cmpwi r5, 0x0
    blt fn_8010C110_L_8010CC18
    lwz r6, 0xa0(r29)
    addi r4, r1, 0x14
    lwz r0, 0xa4(r29)
    li r3, 0x9b
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x1c(r1)
    bl SoundMgr_PlaySE_Positional
    b fn_8010C110_L_8010CC18
    fn_8010C110_L_8010CBF4:
    lwz r6, 0xa0(r29)
    addi r4, r1, 0x8
    lwz r0, 0xa4(r29)
    li r3, 0x9b
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x10(r1)
    bl SoundMgr_PlaySE_WithChannel
    fn_8010C110_L_8010CC18:
    psq_l f31, 0x118(r1), 0, 0
    lwz r0, 0x124(r1)
    lfd f31, 0x110(r1)
    lwz r31, 0x10c(r1)
    lwz r30, 0x108(r1)
    lwz r29, 0x104(r1)
    lwz r28, 0x100(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
}
