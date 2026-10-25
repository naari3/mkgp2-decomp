extern void BuildOrientationFromYaw();
extern void DrawEffect_SpawnDirect();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHitRegistry_AddEntry();
extern void ItemHitRegistry_RemoveEntry();
extern void ItemHit_Dispatch();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AdvanceFallingDrop();
extern void Item_CheckWallCollision();
extern void Item_DecayVelocityScalar();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void Vec3_HorizontalDistance();
extern void cos();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();
extern void sin();
extern unsigned int lbl_806D6B38;
extern unsigned int lbl_806D6B3C;
extern unsigned int lbl_806D6B44;
extern unsigned int lbl_806D6B48;
extern unsigned int lbl_806D6B4C;
extern unsigned int lbl_806D6B50;
extern unsigned int lbl_806D6B54;
extern unsigned int lbl_806D6B58;
extern unsigned int lbl_806D6B5C;
extern unsigned int lbl_806D6B60;
extern unsigned int Effect_TwoChild_Res8F_Update[];
asm void fn_80117494(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80117494[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80117494 = {
    (void *)&fn_80117494, 0x00000488, (void *)extab_fn_80117494
};



asm void fn_80117494(void) { /* 0x80117494 size:0x488 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r27, 0x2c(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xca(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq fn_80117494_L_80117540
    bge fn_80117494_L_801174CC
    cmpwi r0, 0x0
    bge fn_80117494_L_801174D8
    b fn_80117494_L_80117654
    fn_80117494_L_801174CC:
    cmpwi r0, 0x3
    bge fn_80117494_L_80117654
    b fn_80117494_L_80117578
    fn_80117494_L_801174D8:
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    lfs f1, lbl_806D6B38(r2)
    stb r0, 0x8d(r30)
    addi r3, r30, 0x14
    li r4, 0x3
    stb r0, 0x3c(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lis r3, Effect_TwoChild_Res8F_Update@ha
    addi r3, r3, Effect_TwoChild_Res8F_Update@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r31)
    li r3, 0x384
    li r4, 0x0
    li r0, 0xa
    stw r3, 0x4(r31)
    mr r3, r30
    stw r4, 0x8(r31)
    stw r0, 0xc(r31)
    lbz r4, 0xca(r30)
    addi r0, r4, 0x1
    stb r0, 0xca(r30)
    bl ItemHitRegistry_AddEntry
    fn_80117494_L_80117540:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_80117494_L_80117654
    lfs f0, lbl_806D6B38(r2)
    stfs f0, 0x14(r31)
    stfs f0, 0x18(r31)
    lfs f0, 0xa0(r30)
    stfs f0, 0x34(r31)
    lfs f0, 0xa8(r30)
    stfs f0, 0x3c(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b fn_80117494_L_80117654
    fn_80117494_L_80117578:
    lfs f1, lbl_806D6B44(r2)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x14(r31)
    lfs f1, lbl_806D6B48(r2)
    lfs f0, 0x18(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x18(r31)
    lfs f1, 0x18(r31)
    bl sin
    frsp f2, f1
    lfs f1, lbl_806D6B4C(r2)
    lfs f0, 0x14(r31)
    fmadds f0, f1, f2, f0
    stfs f0, 0xb0(r30)
    lfs f1, 0xb0(r30)
    bl sin
    frsp f1, f1
    lfs f0, lbl_806D6B3C(r2)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r30)
    lfs f1, 0xb0(r30)
    bl cos
    frsp f1, f1
    lfs f0, lbl_806D6B3C(r2)
    addi r3, r30, 0xa0
    addi r4, r31, 0x34
    fmuls f0, f0, f1
    stfs f0, 0xc0(r30)
    bl Vec3_HorizontalDistance
    lfs f4, lbl_806D6B50(r2)
    fcmpo cr0, f4, f1
    bge fn_80117494_L_80117654
    lfs f0, 0xa0(r30)
    lfs f6, 0x34(r31)
    lfs f3, 0xa8(r30)
    fsubs f5, f0, f6
    lfs f0, 0x3c(r31)
    lfs f2, lbl_806D6B54(r2)
    fsubs f0, f3, f0
    fdivs f3, f5, f1
    fdivs f0, f0, f1
    fmuls f1, f4, f3
    fmuls f3, f4, f0
    fadds f0, f6, f1
    stfs f0, 0xa0(r30)
    lfs f0, 0x3c(r31)
    fadds f0, f0, f3
    stfs f0, 0xa8(r30)
    lfs f0, 0x14(r31)
    fadds f1, f2, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x14(r31)
    fn_80117494_L_80117654:
    lfs f2, 0xbc(r30)
    mr r3, r30
    lfs f0, lbl_806D6B58(r2)
    lfs f1, lbl_806D6B3C(r2)
    fadds f0, f2, f0
    stfs f0, 0xbc(r30)
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq fn_80117494_L_8011775C
    bge fn_80117494_L_80117698
    cmpwi r28, 0x1
    beq fn_80117494_L_801176A4
    bge fn_80117494_L_801176E8
    b fn_80117494_L_801177A8
    fn_80117494_L_80117698:
    cmpwi r28, 0x5
    beq fn_80117494_L_8011779C
    b fn_80117494_L_801177A8
    fn_80117494_L_801176A4:
    lbz r0, 0xca(r30)
    lwz r3, 0x8(r30)
    extsb r0, r0
    subfic r0, r0, 0x2
    cntlzw r0, r0
    srwi r27, r0, 5
    bl ItemAlias_HitRemapLookup
    extsh r29, r3
    mr r3, r30
    bl ItemTracker_GetTargetKart
    neg r0, r27
    mr r4, r3
    or r0, r0, r27
    lwz r3, 0x98(r31)
    srwi r6, r0, 31
    mr r5, r29
    bl fn_801B1D5C
    fn_80117494_L_801176E8:
    cmpwi r28, 0x2
    bne fn_80117494_L_80117704
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    fn_80117494_L_80117704:
    cmpwi r28, 0x1
    bne fn_80117494_L_80117720
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    fn_80117494_L_80117720:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6B38(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc8(r30)
    stb r0, 0xc9(r30)
    stb r0, 0xcb(r30)
    b fn_80117494_L_80117908
    fn_80117494_L_8011775C:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    lfs f1, lbl_806D6B5C(r2)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x14(r31)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0x8(r31)
    b fn_80117494_L_801177A8
    fn_80117494_L_8011779C:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_80117494_L_801177A8:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_80117494_L_801177C0
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_80117494_L_801177C0:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne fn_80117494_L_80117834
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6B38(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne fn_80117494_L_80117818
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x4
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b fn_80117494_L_80117908
    fn_80117494_L_80117818:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x6
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b fn_80117494_L_80117908
    fn_80117494_L_80117834:
    mr r3, r30
    addi r4, r1, 0x18
    addi r5, r1, 0xc
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq fn_80117494_L_80117870
    lfs f1, lbl_806D6B60(r2)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x14(r31)
    lfs f0, 0xc(r1)
    stfs f0, 0xa0(r30)
    lfs f0, 0x14(r1)
    stfs f0, 0xa8(r30)
    fn_80117494_L_80117870:
    lfs f1, lbl_806D6B38(r2)
    mr r3, r30
    addi r4, r1, 0x8
    li r5, 0x0
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq fn_80117494_L_801178A0
    lwz r0, 0x8(r1)
    cmpwi r0, 0x0
    beq fn_80117494_L_801178A0
    lfs f0, lbl_806D6B38(r2)
    stfs f0, 0xbc(r30)
    fn_80117494_L_801178A0:
    lwz r4, 0x4(r31)
    mr r3, r30
    li r5, 0x0
    bl ItemHitRegistry_RemoveEntry
    clrlwi. r0, r3, 24
    beq fn_80117494_L_80117908
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6B38(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq fn_80117494_L_801178F0
    li r0, 0x1
    stb r0, 0xc9(r3)
    fn_80117494_L_801178F0:
    li r0, 0x0
    mr r3, r30
    stw r0, 0x4c(r31)
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    fn_80117494_L_80117908:
    lmw r27, 0x2c(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
