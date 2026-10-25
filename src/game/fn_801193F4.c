extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemEffectBus_OrMask();
extern void ItemHit_Dispatch();
extern void ItemObject_AllocFromPool();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AdvanceFallingDrop();
extern void Item_DecayVelocityScalar();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_TransformVec3();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_SetTransform();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_HorizontalYawTo();
extern void Vec3_Magnitude_Wrapper();
extern void Vec3_Scale();
extern void Vec3_Subtract_DestFirst();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();
extern unsigned int lbl_806D6BF8;
extern unsigned int lbl_806D6BFC;
extern unsigned int lbl_806D6C00;
extern unsigned int lbl_806D6C04;
extern unsigned int lbl_806D6C08;
extern unsigned int lbl_806D6C0C;
extern unsigned int lbl_806D6C10;
extern unsigned int lbl_806D6C14;
extern unsigned int lbl_806D6C18;
extern unsigned int CourseInteractMover_Update[];
extern unsigned int KartAttachedSpin_Update[];
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern void Item_BendVelocityByGroundProbe();
extern void JointByName_GetLocalMatrix4x3();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_GetYawOfPosZ();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_TickAnim();
extern void Vec3_ToYaw();
extern void fn_800D4174();
extern unsigned int lbl_806D6C1C;
extern unsigned int lbl_806D6C20;
extern unsigned int lbl_806D6C24;
extern unsigned int lbl_803324F0[];
extern unsigned int lbl_804220C8[];
extern void ItemObject_SpawnWithAlias();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
asm void fn_801193F4(void);
asm void fn_80119AB4(void);
asm void fn_80119D44(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_801193F4[8] = {
    0x30, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80119AB4[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80119D44[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801193F4 = {
    (void *)&fn_801193F4, 0x000006C0, (void *)extab_fn_801193F4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80119AB4 = {
    (void *)&fn_80119AB4, 0x00000290, (void *)extab_fn_80119AB4
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80119D44 = {
    (void *)&fn_80119D44, 0x0000023C, (void *)extab_fn_80119D44
};



asm void fn_801193F4(void) { /* 0x801193F4 size:0x6C0 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stmw r26, 0x98(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xca(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq fn_801193F4_L_801194A4
    bge fn_801193F4_L_801194A4
    cmpwi r0, 0x0
    bge fn_801193F4_L_80119434
    b fn_801193F4_L_801194A4
    fn_801193F4_L_80119434:
    mr r28, r31
    li r29, 0x0
    li r27, 0x1
    li r26, 0x0
    fn_801193F4_L_80119444:
    lwz r3, 0x5c(r28)
    cmplwi r3, 0x0
    beq fn_801193F4_L_80119478
    bl ItemTracker_AcquireLock
    lwz r3, 0x5c(r28)
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    lwz r3, 0x5c(r28)
    stb r27, 0x8d(r3)
    lwz r3, 0x5c(r28)
    stb r27, 0x3c(r3)
    lwz r3, 0x5c(r28)
    stw r26, 0xf0(r3)
    fn_801193F4_L_80119478:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x3
    blt fn_801193F4_L_80119444
    li r3, 0x258
    li r0, 0x3c
    stw r3, 0x4(r31)
    stw r0, 0x8(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    fn_801193F4_L_801194A4:
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq fn_801193F4_L_801194C0
    li r0, 0x0
    stb r0, 0x28(r30)
    b fn_801193F4_L_801194C8
    fn_801193F4_L_801194C0:
    li r0, 0x1
    stb r0, 0x28(r30)
    fn_801193F4_L_801194C8:
    li r29, 0x0
    mr r28, r31
    fn_801193F4_L_801194D0:
    lwz r3, 0x5c(r28)
    cmplwi r3, 0x0
    beq fn_801193F4_L_8011999C
    lbz r0, 0x28(r30)
    stb r0, 0x28(r3)
    lwz r3, 0x5c(r28)
    bl ItemCollision_Check
    mr r27, r3
    cmpwi r27, 0x3
    beq fn_801193F4_L_8011962C
    bge fn_801193F4_L_8011950C
    cmpwi r27, 0x1
    beq fn_801193F4_L_80119518
    bge fn_801193F4_L_80119540
    b fn_801193F4_L_80119668
    fn_801193F4_L_8011950C:
    cmpwi r27, 0x5
    beq fn_801193F4_L_8011965C
    b fn_801193F4_L_80119668
    fn_801193F4_L_80119518:
    lwz r3, 0x8(r30)
    bl ItemAlias_HitRemapLookup
    extsh r26, r3
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    mr r5, r26
    li r6, 0x0
    bl fn_801B1D5C
    fn_801193F4_L_80119540:
    cmpwi r27, 0x2
    bne fn_801193F4_L_8011955C
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    fn_801193F4_L_8011955C:
    slwi r0, r29, 2
    add r26, r31, r0
    lwz r3, 0x5c(r26)
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0x5c(r26)
    bl ItemHit_Dispatch
    li r28, 0x0
    mr r27, r31
    fn_801193F4_L_8011958C:
    lwz r0, 0x5c(r27)
    cmplwi r0, 0x0
    beq fn_801193F4_L_801195FC
    lis r3, KartAttachedSpin_Update@ha
    addi r3, r3, KartAttachedSpin_Update@l
    bl ItemObject_AllocFromPool
    mr. r26, r3
    beq fn_801193F4_L_801195E0
    lwz r4, 0x5c(r27)
    addi r3, r26, 0xa0
    addi r4, r4, 0xa0
    bl Vec3_Copy
    lwz r4, 0x5c(r27)
    addi r3, r26, 0xac
    addi r4, r4, 0xac
    bl Vec3_Copy
    lwz r3, 0x5c(r27)
    lfs f0, 0xc4(r3)
    stfs f0, 0xc4(r26)
    lwz r0, 0x9c(r31)
    stw r0, 0x188(r26)
    fn_801193F4_L_801195E0:
    lwz r3, 0x5c(r27)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r27)
    li r0, 0x0
    stb r0, 0x8d(r3)
    lwz r3, 0x5c(r27)
    stb r0, 0x28(r3)
    fn_801193F4_L_801195FC:
    addi r28, r28, 0x1
    addi r27, r27, 0x4
    cmpwi r28, 0x3
    blt fn_801193F4_L_8011958C
    lwz r3, 0x98(r31)
    li r6, 0x0
    lis r5, 0x400
    lwz r3, 0x304(r3)
    bl ItemEffectBus_OrMask
    li r0, 0x3
    stb r0, 0xc8(r30)
    b fn_801193F4_L_80119A98
    fn_801193F4_L_8011962C:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    lwz r3, 0x5c(r28)
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    lwz r3, 0x5c(r28)
    li r0, 0x5
    stw r0, 0xf0(r3)
    b fn_801193F4_L_80119668
    fn_801193F4_L_8011965C:
    lwz r3, 0x5c(r28)
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_801193F4_L_80119668:
    lwz r3, 0x5c(r28)
    lwz r0, 0xf0(r3)
    cmplwi r0, 0x0
    bne fn_801193F4_L_80119680
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_801193F4_L_80119680:
    lwz r4, 0x5c(r28)
    lwz r3, 0xf0(r4)
    cmplwi r3, 0x0
    beq fn_801193F4_L_80119698
    subi r0, r3, 0x1
    stw r0, 0xf0(r4)
    fn_801193F4_L_80119698:
    lwz r3, 0x5c(r28)
    lbz r0, 0x8d(r3)
    cmpwi r0, 0x2
    bne fn_801193F4_L_801197B0
    slwi r3, r29, 2
    mr r29, r31
    addi r28, r3, 0x5c
    li r27, 0x0
    fn_801193F4_L_801196B8:
    lwz r0, 0x5c(r29)
    cmplwi r0, 0x0
    beq fn_801193F4_L_80119780
    lwzx r3, r31, r28
    lbz r0, 0x8e(r3)
    cmpwi r0, 0x1
    bne fn_801193F4_L_80119718
    lis r3, KartAttachedSpin_Update@ha
    addi r3, r3, KartAttachedSpin_Update@l
    bl ItemObject_AllocFromPool
    mr. r26, r3
    beq fn_801193F4_L_80119764
    lwz r4, 0x5c(r29)
    addi r3, r26, 0xa0
    addi r4, r4, 0xa0
    bl Vec3_Copy
    lwz r4, 0x5c(r29)
    addi r3, r26, 0xac
    addi r4, r4, 0xac
    bl Vec3_Copy
    lwz r3, 0x5c(r29)
    lfs f0, 0xc4(r3)
    stfs f0, 0xc4(r26)
    b fn_801193F4_L_80119764
    fn_801193F4_L_80119718:
    lis r3, CourseInteractMover_Update@ha
    addi r3, r3, CourseInteractMover_Update@l
    bl ItemObject_AllocFromPool
    mr. r26, r3
    beq fn_801193F4_L_80119764
    lwz r4, 0x5c(r29)
    addi r3, r26, 0xa0
    addi r4, r4, 0xa0
    bl Vec3_Copy
    lwz r4, 0x5c(r29)
    addi r3, r26, 0xac
    addi r4, r4, 0xac
    bl Vec3_Copy
    lwz r3, 0x5c(r29)
    lfs f0, 0xc4(r3)
    stfs f0, 0xc4(r26)
    lwzx r3, r31, r28
    lwz r0, 0x9c(r3)
    stw r0, 0x9c(r26)
    fn_801193F4_L_80119764:
    lwz r3, 0x5c(r29)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r29)
    li r0, 0x0
    stb r0, 0x8d(r3)
    lwz r3, 0x5c(r29)
    stb r0, 0x28(r3)
    fn_801193F4_L_80119780:
    addi r27, r27, 0x1
    addi r29, r29, 0x4
    cmpwi r27, 0x3
    blt fn_801193F4_L_801196B8
    lwz r3, 0x98(r31)
    li r6, 0x0
    lis r5, 0x400
    lwz r3, 0x304(r3)
    bl ItemEffectBus_OrMask
    li r0, 0x3
    stb r0, 0xc8(r30)
    b fn_801193F4_L_80119A98
    fn_801193F4_L_801197B0:
    lfs f1, lbl_806D6BF8(r2)
    bl Item_DecayVelocityScalar
    lwz r3, 0x5c(r28)
    addi r4, r1, 0x8
    lfs f3, lbl_806D6BFC(r2)
    li r5, 0x0
    lfs f1, 0xb8(r3)
    lfs f0, lbl_806D6C00(r2)
    fmuls f2, f1, f3
    lfs f1, lbl_806D6C04(r2)
    stfs f2, 0xb8(r3)
    lwz r3, 0x5c(r28)
    lfs f2, 0xc0(r3)
    fmuls f2, f2, f3
    stfs f2, 0xc0(r3)
    lwz r3, 0x5c(r28)
    lfs f2, 0xbc(r3)
    fadds f0, f2, f0
    stfs f0, 0xbc(r3)
    lwz r3, 0x5c(r28)
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq fn_801193F4_L_80119824
    lwz r0, 0x8(r1)
    cmpwi r0, 0x0
    beq fn_801193F4_L_80119824
    lfs f0, lbl_806D6C04(r2)
    lwz r3, 0x5c(r28)
    stfs f0, 0xbc(r3)
    fn_801193F4_L_80119824:
    lwz r4, 0x5c(r28)
    addi r3, r4, 0xa0
    addi r5, r4, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    cmpwi r29, 0x0
    beq fn_801193F4_L_8011985C
    lwz r4, 0x58(r28)
    cmplwi r4, 0x0
    beq fn_801193F4_L_8011985C
    addi r3, r1, 0x48
    addi r4, r4, 0xa0
    bl Vec3_Copy
    b fn_801193F4_L_801198AC
    fn_801193F4_L_8011985C:
    lwz r3, 0x98(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x54
    bl Mtx_TransposeToMtx44
    lfs f1, lbl_806D6C04(r2)
    addi r3, r1, 0x48
    lfs f3, lbl_806D6C08(r2)
    fmr f2, f1
    bl GetSpawnPosition
    lwz r7, 0x48(r1)
    addi r3, r1, 0x48
    lwz r6, 0x4c(r1)
    addi r4, r1, 0x54
    lwz r0, 0x50(r1)
    addi r5, r1, 0x24
    stw r7, 0x24(r1)
    stw r6, 0x28(r1)
    stw r0, 0x2c(r1)
    bl Mtx44_TransformVec3
    fn_801193F4_L_801198AC:
    lwz r4, 0x5c(r28)
    addi r3, r1, 0x3c
    addi r5, r1, 0x48
    addi r4, r4, 0xa0
    bl Vec3_Subtract_DestFirst
    addi r3, r1, 0x3c
    bl Vec3_Magnitude_Wrapper
    fmr f31, f1
    lfs f0, lbl_806D6C0C(r2)
    fcmpo cr0, f0, f31
    bge fn_801193F4_L_80119954
    lwz r4, 0x5c(r28)
    addi r3, r1, 0x30
    addi r4, r4, 0xa0
    bl Vec3_Copy
    lfs f0, lbl_806D6C10(r2)
    addi r4, r1, 0x3c
    lwz r3, 0x5c(r28)
    fdivs f1, f0, f31
    lfs f0, lbl_806D6C0C(r2)
    addi r3, r3, 0xa0
    fmuls f1, f1, f0
    bl Vec3_Scale
    lwz r3, 0x5c(r28)
    addi r5, r1, 0x48
    addi r3, r3, 0xa0
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D6C14(r2)
    fcmpo cr0, f0, f31
    bge fn_801193F4_L_80119940
    lwz r4, 0x5c(r28)
    addi r3, r1, 0x30
    addi r4, r4, 0xa0
    bl Vec3_HorizontalYawTo
    lwz r3, 0x5c(r28)
    stfs f1, 0xb0(r3)
    fn_801193F4_L_80119940:
    lwz r3, 0x5c(r28)
    lfs f0, lbl_806D6C18(r2)
    lfs f1, 0xbc(r3)
    fmuls f0, f1, f0
    stfs f0, 0xbc(r3)
    fn_801193F4_L_80119954:
    lwz r7, 0x5c(r28)
    addi r4, r1, 0x18
    addi r5, r1, 0xc
    lwz r6, 0xac(r7)
    addi r3, r7, 0x14
    lwz r0, 0xb0(r7)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r0, 0xb4(r7)
    stw r0, 0x14(r1)
    lwz r6, 0xa0(r7)
    lwz r0, 0xa4(r7)
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    lwz r0, 0xa8(r7)
    stw r0, 0x20(r1)
    lfs f1, 0xc4(r7)
    bl SpriteSlot_SetTransform
    fn_801193F4_L_8011999C:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x3
    blt fn_801193F4_L_801194D0
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_801193F4_L_801199EC
    lwz r3, 0x98(r31)
    li r4, 0x0
    li r0, 0x2000
    lwz r5, 0x304(r3)
    lwz r3, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne fn_801193F4_L_801199EC
    stw r4, 0x4(r31)
    fn_801193F4_L_801199EC:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne fn_801193F4_L_80119A98
    li r28, 0x0
    mr r26, r31
    fn_801193F4_L_80119A00:
    lwz r0, 0x5c(r26)
    cmplwi r0, 0x0
    beq fn_801193F4_L_80119A80
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    bne fn_801193F4_L_80119A64
    lis r3, KartAttachedSpin_Update@ha
    addi r3, r3, KartAttachedSpin_Update@l
    bl ItemObject_AllocFromPool
    mr. r27, r3
    beq fn_801193F4_L_80119A64
    lwz r4, 0x5c(r26)
    addi r3, r27, 0xa0
    addi r4, r4, 0xa0
    bl Vec3_Copy
    lwz r4, 0x5c(r26)
    addi r3, r27, 0xac
    addi r4, r4, 0xac
    bl Vec3_Copy
    lwz r3, 0x5c(r26)
    lfs f0, 0xc4(r3)
    stfs f0, 0xc4(r27)
    lwz r0, 0x98(r31)
    stw r0, 0x188(r27)
    fn_801193F4_L_80119A64:
    lwz r3, 0x5c(r26)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r26)
    li r0, 0x0
    stb r0, 0x8d(r3)
    lwz r3, 0x5c(r26)
    stb r0, 0x28(r3)
    fn_801193F4_L_80119A80:
    addi r28, r28, 0x1
    addi r26, r26, 0x4
    cmpwi r28, 0x3
    blt fn_801193F4_L_80119A00
    li r0, 0x3
    stb r0, 0xc8(r30)
    fn_801193F4_L_80119A98:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    lmw r26, 0x98(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

asm void fn_80119AB4(void) { /* 0x80119AB4 size:0x290 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stmw r27, 0x5c(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xca(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq fn_80119AB4_L_80119B58
    bge fn_80119AB4_L_80119D30
    cmpwi r0, 0x0
    bge fn_80119AB4_L_80119AEC
    b fn_80119AB4_L_80119D30
    fn_80119AB4_L_80119AEC:
    lfs f0, lbl_806D6C04(r2)
    lis r3, lbl_803324F0@ha
    mr r28, r31
    li r27, 0x0
    stfs f0, 0x2c(r30)
    addi r29, r3, lbl_803324F0@l
    fn_80119AB4_L_80119B04:
    lwz r3, 0x5c(r28)
    cmplwi r3, 0x0
    beq fn_80119AB4_L_80119B3C
    addi r3, r3, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    cmpwi r27, 0x0
    beq fn_80119AB4_L_80119B3C
    lwz r3, 0x5c(r28)
    mr r4, r29
    li r5, 0x10
    li r6, 0x1
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    fn_80119AB4_L_80119B3C:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0x3
    blt fn_80119AB4_L_80119B04
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    fn_80119AB4_L_80119B58:
    lfs f1, lbl_806D6C04(r2)
    mr r3, r30
    lfs f2, lbl_806D6C1C(r2)
    li r4, 0x1
    lfs f3, lbl_806D6C10(r2)
    bl GabyouItem_BuildLocalTransformFromHandJoint
    li r0, 0x1
    addi r3, r30, 0x14
    stb r0, 0x28(r30)
    bl SpriteSlot_TickAnim
    li r0, 0x0
    stb r0, 0x28(r30)
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq fn_80119AB4_L_80119BA4
    li r0, 0x0
    stb r0, 0x28(r30)
    b fn_80119AB4_L_80119BAC
    fn_80119AB4_L_80119BA4:
    li r0, 0x1
    stb r0, 0x28(r30)
    fn_80119AB4_L_80119BAC:
    lis r3, lbl_804220C8@ha
    mr r28, r31
    addi r29, r3, lbl_804220C8@l
    li r27, 0x0
    fn_80119AB4_L_80119BBC:
    lwz r3, 0x5c(r28)
    cmplwi r3, 0x0
    beq fn_80119AB4_L_80119C00
    mr r5, r29
    addi r3, r3, 0x48
    addi r4, r30, 0x14
    bl JointByName_GetLocalMatrix4x3
    lwz r4, 0x5c(r28)
    addi r3, r4, 0xa0
    addi r4, r4, 0x48
    bl Mtx44_GetTranslation_RowMajor
    lfs f0, 0x2c(r30)
    lwz r3, 0x5c(r28)
    stfs f0, 0x2c(r3)
    lbz r0, 0x28(r30)
    lwz r3, 0x5c(r28)
    stb r0, 0x28(r3)
    fn_80119AB4_L_80119C00:
    addi r27, r27, 0x1
    addi r29, r29, 0x40
    cmpwi r27, 0x3
    addi r28, r28, 0x4
    blt fn_80119AB4_L_80119BBC
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq fn_80119AB4_L_80119D1C
    bge fn_80119AB4_L_80119D30
    cmpwi r0, 0x1
    bge fn_80119AB4_L_80119C34
    b fn_80119AB4_L_80119D30
    fn_80119AB4_L_80119C34:
    li r0, 0x0
    addi r3, r31, 0xa4
    stb r0, 0xa0(r31)
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r28, r31
    li r29, 0x0
    fn_80119AB4_L_80119C50:
    lwz r3, 0x5c(r28)
    cmplwi r3, 0x0
    beq fn_80119AB4_L_80119CF4
    addi r3, r3, 0x14
    li r4, 0x0
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lwz r6, 0x5c(r28)
    lis r3, lbl_803324F0@ha
    addi r4, r3, lbl_803324F0@l
    li r5, 0x10
    addi r3, r6, 0x14
    li r6, 0x0
    bl SpriteSlot_SetJointVisibilityByName
    lfs f0, lbl_806D6C10(r2)
    addi r3, r1, 0x14
    lwz r4, 0x5c(r28)
    stfs f0, 0x2c(r4)
    lwz r4, 0x5c(r28)
    addi r4, r4, 0x48
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x14
    bl Mtx44_GetYawOfPosZ
    lwz r4, 0x5c(r28)
    addi r3, r1, 0x14
    stfs f1, 0xb0(r4)
    bl fn_800D4174
    lwz r3, 0x5c(r28)
    addi r4, r1, 0x8
    lfs f2, lbl_806D6C20(r2)
    stfs f1, 0xc4(r3)
    lfs f3, lbl_806D6C24(r2)
    lwz r6, 0x5c(r28)
    lwz r5, 0xa0(r6)
    addi r3, r6, 0xb8
    lwz r0, 0xa4(r6)
    stw r5, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r6)
    stw r0, 0x10(r1)
    lfs f1, 0xb0(r30)
    bl Item_BendVelocityByGroundProbe
    fn_80119AB4_L_80119CF4:
    addi r29, r29, 0x1
    addi r28, r28, 0x4
    cmpwi r29, 0x3
    blt fn_80119AB4_L_80119C50
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b fn_80119AB4_L_80119D30
    fn_80119AB4_L_80119D1C:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    fn_80119AB4_L_80119D30:
    lmw r27, 0x5c(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

asm void fn_80119D44(void) { /* 0x80119D44 size:0x23C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    addi r31, r30, 0xec
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq fn_80119D44_L_80119EE4
    bge fn_80119D44_L_80119D8C
    cmpwi r0, 0x0
    beq fn_80119D44_L_80119D98
    bge fn_80119D44_L_80119E68
    b fn_80119D44_L_80119EE4
    fn_80119D44_L_80119D8C:
    cmpwi r0, 0x4
    bge fn_80119D44_L_80119EE4
    b fn_80119D44_L_80119EA8
    fn_80119D44_L_80119D98:
    addi r3, r30, 0x14
    li r4, 0x95
    bl SpriteSlot_InitNonLoop
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D6C04(r2)
    addi r3, r30, 0x14
    li r4, 0x3
    bl SpriteSlot_SetAnimFrameAndApplyScale
    li r3, 0x4
    li r0, 0x0
    stb r3, 0x14(r30)
    mr r29, r31
    li r28, 0x0
    stb r0, 0x28(r30)
    fn_80119D44_L_80119DD8:
    li r3, 0x9c
    li r4, 0xff
    bl ItemObject_SpawnWithAlias
    stw r3, 0x5c(r29)
    lwz r3, 0x5c(r29)
    cmplwi r3, 0x0
    beq fn_80119D44_L_80119E44
    lwz r0, 0x94(r31)
    li r4, 0x96
    stw r0, 0x180(r3)
    lwz r0, 0x98(r31)
    lwz r3, 0x5c(r29)
    stw r0, 0x184(r3)
    lwz r3, 0x5c(r29)
    stw r30, 0xe4(r3)
    lwz r3, 0x5c(r29)
    addi r3, r3, 0x14
    bl SpriteSlot_InitNonLoop
    lwz r3, 0x5c(r29)
    li r5, 0x4
    li r4, 0x3
    li r0, 0x0
    stb r5, 0x14(r3)
    lwz r3, 0x5c(r29)
    stb r4, 0x8c(r3)
    lwz r3, 0x5c(r29)
    stb r0, 0x8d(r3)
    fn_80119D44_L_80119E44:
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x3
    blt fn_80119D44_L_80119DD8
    li r3, 0x1
    li r0, 0x0
    stb r3, 0xc8(r30)
    stb r0, 0xc9(r30)
    stb r0, 0xca(r30)
    fn_80119D44_L_80119E68:
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq fn_80119D44_L_80119E98
    bge fn_80119D44_L_80119EE4
    cmpwi r0, 0x0
    bge fn_80119D44_L_80119E88
    b fn_80119D44_L_80119EE4
    fn_80119D44_L_80119E88:
    mr r3, r30
    mr r4, r31
    bl fn_80119AB4
    b fn_80119D44_L_80119EE4
    fn_80119D44_L_80119E98:
    mr r3, r30
    mr r4, r31
    bl fn_801193F4
    b fn_80119D44_L_80119EE4
    fn_80119D44_L_80119EA8:
    li r28, 0x0
    mr r29, r31
    mr r31, r28
    fn_80119D44_L_80119EB4:
    lwz r3, 0x5c(r29)
    cmplwi r3, 0x0
    beq fn_80119D44_L_80119EC4
    bl SpriteSlot_Container_Free
    fn_80119D44_L_80119EC4:
    addi r28, r28, 0x1
    stw r31, 0x5c(r29)
    cmpwi r28, 0x3
    addi r29, r29, 0x4
    blt fn_80119D44_L_80119EB4
    mr r3, r30
    bl SpriteSlot_Container_Free
    b fn_80119D44_L_80119F60
    fn_80119D44_L_80119EE4:
    li r30, 0x0
    mr r29, r31
    fn_80119D44_L_80119EEC:
    lwz r3, 0x5c(r29)
    cmplwi r3, 0x0
    beq fn_80119D44_L_80119F00
    addi r3, r3, 0x14
    bl SpriteSlot_TickAnim
    fn_80119D44_L_80119F00:
    addi r30, r30, 0x1
    addi r29, r29, 0x4
    cmpwi r30, 0x3
    blt fn_80119D44_L_80119EEC
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq fn_80119D44_L_80119F24
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    fn_80119D44_L_80119F24:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq fn_80119D44_L_80119F38
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    fn_80119D44_L_80119F38:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq fn_80119D44_L_80119F4C
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    fn_80119D44_L_80119F4C:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq fn_80119D44_L_80119F60
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    fn_80119D44_L_80119F60:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
