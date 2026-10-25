extern void BuildOrientationFromYaw();
extern void ItemCollision_Check();
extern void ItemObject_GetGroundTypeAt();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void Vec3_ToYaw();
extern void sin();
extern unsigned int lbl_806D6AC0;
extern unsigned int lbl_806D6AC4;
extern unsigned int lbl_806D6ACC;
extern unsigned int lbl_806D6AD8;
extern unsigned int lbl_806D6AE4;
extern unsigned int lbl_806D6AE8;
extern unsigned int lbl_806D6B0C;
extern unsigned int lbl_806D6B10;
extern unsigned int lbl_806D6B14;
asm void fn_80116640(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80116640[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80116640 = {
    (void *)&fn_80116640, 0x00000320, (void *)extab_fn_80116640
};



asm void fn_80116640(void) { /* 0x80116640 size:0x320 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    mr r31, r4
    stw r30, 0x58(r1)
    mr r30, r3
    stw r29, 0x54(r1)
    lbz r0, 0xca(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq fn_80116640_L_801166C8
    bge fn_80116640_L_801166C8
    cmpwi r0, 0x0
    bge fn_80116640_L_80116680
    b fn_80116640_L_801166C8
    fn_80116640_L_80116680:
    lfs f1, lbl_806D6AC0(r2)
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetAnimFrameAndApplyScale
    mr r3, r30
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x3c(r30)
    lfs f0, lbl_806D6AC0(r2)
    stw r0, 0x8(r31)
    stfs f0, 0x14(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    fn_80116640_L_801166C8:
    lfs f1, lbl_806D6AC4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D6ACC(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lfs f1, 0x14(r31)
    bl sin
    frsp f3, f1
    lfs f1, lbl_806D6B0C(r2)
    lfs f0, lbl_806D6AD8(r2)
    lfs f2, 0xc4(r30)
    fmadds f0, f1, f3, f0
    lfs f1, lbl_806D6B10(r2)
    fdivs f0, f2, f0
    stfs f0, 0xc4(r30)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x14(r31)
    lfs f1, 0x14(r31)
    bl sin
    frsp f3, f1
    lfs f1, lbl_806D6AE8(r2)
    lfs f0, lbl_806D6AD8(r2)
    mr r3, r30
    lfs f2, 0xc4(r30)
    fmadds f0, f1, f3, f0
    fmuls f0, f2, f0
    stfs f0, 0xc4(r30)
    bl ItemCollision_Check
    mr r29, r3
    cmpwi r29, 0x3
    beq fn_80116640_L_801167C0
    bge fn_80116640_L_80116768
    cmpwi r29, 0x0
    beq fn_80116640_L_80116844
    bge fn_80116640_L_80116774
    b fn_80116640_L_80116844
    fn_80116640_L_80116768:
    cmpwi r29, 0x5
    beq fn_80116640_L_80116838
    b fn_80116640_L_80116844
    fn_80116640_L_80116774:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    cmpwi r29, 0x1
    stb r0, 0x8d(r30)
    bne fn_80116640_L_801167A4
    li r0, 0x1
    stb r0, 0x0(r31)
    b fn_80116640_L_801167A8
    fn_80116640_L_801167A4:
    stb r0, 0x0(r31)
    fn_80116640_L_801167A8:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc8(r30)
    stb r0, 0xc9(r30)
    stb r0, 0xcb(r30)
    b fn_80116640_L_80116944
    fn_80116640_L_801167C0:
    li r0, 0x0
    mr r3, r30
    stw r0, 0x7c(r31)
    lwz r4, 0xb8(r30)
    lwz r0, 0xbc(r30)
    stw r4, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x2c(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x30(r1)
    stw r0, 0x34(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x38(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0x30
    addi r6, r1, 0x24
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0x8(r31)
    b fn_80116640_L_80116844
    fn_80116640_L_80116838:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_80116640_L_80116844:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_80116640_L_8011685C
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_80116640_L_8011685C:
    mr r3, r30
    addi r4, r1, 0x3c
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq fn_80116640_L_801168B4
    lwz r6, 0x3c(r1)
    mr r3, r30
    lwz r7, 0x40(r1)
    addi r4, r1, 0x18
    lwz r0, 0x44(r1)
    li r5, 0xcb
    stw r6, 0x18(r1)
    li r6, 0x2
    lfs f1, lbl_806D6AE4(r2)
    stw r7, 0x1c(r1)
    lfs f2, lbl_806D6AC4(r2)
    stw r0, 0x20(r1)
    bl Item_BounceOffWall
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    fn_80116640_L_801168B4:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0xc
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x8
    li r5, 0x0
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x14(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq fn_80116640_L_80116924
    lfs f0, 0xa4(r30)
    lfs f1, 0x8(r1)
    fcmpo cr0, f0, f1
    bge fn_80116640_L_80116944
    stfs f1, 0xa4(r30)
    mr r3, r30
    lfs f0, lbl_806D6B14(r2)
    stfs f0, 0xbc(r30)
    bl ItemTracker_ReleaseLock
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x8
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b fn_80116640_L_80116944
    fn_80116640_L_80116924:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x9
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    fn_80116640_L_80116944:
    lwz r0, 0x64(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    lwz r29, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}
