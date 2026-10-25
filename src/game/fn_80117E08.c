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
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();
extern void sin();
extern unsigned int lbl_806D6B70;
extern unsigned int lbl_806D6B74;
extern unsigned int lbl_806D6B78;
extern unsigned int lbl_806D6B7C;
extern unsigned int lbl_806D6B80;
extern unsigned int lbl_806D6B84;
extern unsigned int lbl_806D6B88;
extern unsigned int lbl_806D6B8C;
extern unsigned int lbl_806D6B90;
extern unsigned int lbl_806D6B94;
extern unsigned int lbl_806D6BA0;
extern unsigned int lbl_806D6BA4;
asm void fn_80117E08(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80117E08[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80117E08 = {
    (void *)&fn_80117E08, 0x00000428, (void *)extab_fn_80117E08
};



asm void fn_80117E08(void) { /* 0x80117E08 size:0x428 */
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
    beq fn_80117E08_L_80117E94
    bge fn_80117E08_L_80117EB8
    cmpwi r0, 0x0
    bge fn_80117E08_L_80117E44
    b fn_80117E08_L_80117EB8
    b fn_80117E08_L_80117EB8
    fn_80117E08_L_80117E44:
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r3, 0x1
    li r5, 0x384
    stb r3, 0x8d(r30)
    li r4, 0x0
    li r0, 0xa
    lfs f0, lbl_806D6B88(r2)
    stb r3, 0x3c(r30)
    mr r3, r30
    stw r5, 0x4(r31)
    stw r4, 0x8(r31)
    stw r0, 0xc(r31)
    stfs f0, 0x14(r31)
    lbz r4, 0xca(r30)
    addi r0, r4, 0x1
    stb r0, 0xca(r30)
    bl ItemHitRegistry_AddEntry
    fn_80117E08_L_80117E94:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_80117E08_L_80117EB8
    lfs f0, lbl_806D6B88(r2)
    stfs f0, 0xb8(r30)
    stfs f0, 0xc0(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    fn_80117E08_L_80117EB8:
    lfs f0, lbl_806D6BA0(r2)
    mr r3, r30
    lfs f1, lbl_806D6B70(r2)
    stfs f0, 0xbc(r30)
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq fn_80117E08_L_80117FB8
    bge fn_80117E08_L_80117EF4
    cmpwi r28, 0x1
    beq fn_80117E08_L_80117F00
    bge fn_80117E08_L_80117F44
    b fn_80117E08_L_80117FF0
    fn_80117E08_L_80117EF4:
    cmpwi r28, 0x5
    beq fn_80117E08_L_80117FE4
    b fn_80117E08_L_80117FF0
    fn_80117E08_L_80117F00:
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
    fn_80117E08_L_80117F44:
    cmpwi r28, 0x2
    bne fn_80117E08_L_80117F60
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    fn_80117E08_L_80117F60:
    cmpwi r28, 0x1
    bne fn_80117E08_L_80117F7C
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    fn_80117E08_L_80117F7C:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6B88(r2)
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
    b fn_80117E08_L_8011821C
    fn_80117E08_L_80117FB8:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0x8(r31)
    b fn_80117E08_L_80117FF0
    fn_80117E08_L_80117FE4:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_80117E08_L_80117FF0:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_80117E08_L_80118008
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    fn_80117E08_L_80118008:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne fn_80117E08_L_8011807C
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6B88(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne fn_80117E08_L_80118060
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x4
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b fn_80117E08_L_8011821C
    fn_80117E08_L_80118060:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x6
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b fn_80117E08_L_8011821C
    fn_80117E08_L_8011807C:
    mr r3, r30
    addi r4, r1, 0x18
    addi r5, r1, 0xc
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq fn_80117E08_L_801180A4
    lfs f0, 0xc(r1)
    stfs f0, 0xa0(r30)
    lfs f0, 0x14(r1)
    stfs f0, 0xa8(r30)
    fn_80117E08_L_801180A4:
    lfs f1, lbl_806D6B88(r2)
    mr r3, r30
    addi r5, r1, 0x8
    li r4, 0x0
    bl Item_AdvanceFallingDrop
    lfs f1, lbl_806D6B78(r2)
    lfs f0, 0x14(r31)
    lfs f2, lbl_806D6B74(r2)
    fmuls f0, f1, f0
    fmuls f1, f2, f0
    bl sin
    frsp f3, f1
    lfs f0, lbl_806D6B7C(r2)
    lfs f2, 0xa4(r30)
    lfs f1, lbl_806D6BA4(r2)
    fmadds f0, f0, f3, f0
    fsubs f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    lfs f3, 0xa4(r30)
    lfs f2, 0xbc(r30)
    fadds f1, f1, f0
    fadds f0, f3, f2
    fcmpo cr0, f0, f1
    bge fn_80117E08_L_80118114
    stfs f1, 0xa4(r30)
    lfs f0, lbl_806D6B88(r2)
    stfs f0, 0xbc(r30)
    fn_80117E08_L_80118114:
    lfs f2, 0x14(r31)
    lfs f0, lbl_806D6B80(r2)
    lfs f1, lbl_806D6B84(r2)
    fadds f0, f2, f0
    stfs f0, 0x14(r31)
    lfs f0, 0x14(r31)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne fn_80117E08_L_80118140
    lfs f0, lbl_806D6B88(r2)
    stfs f0, 0x14(r31)
    fn_80117E08_L_80118140:
    lfs f1, lbl_806D6B78(r2)
    lfs f0, 0x14(r31)
    lfs f2, lbl_806D6B74(r2)
    fmuls f0, f1, f0
    fmuls f1, f2, f0
    bl sin
    frsp f2, f1
    lfs f0, lbl_806D6B7C(r2)
    lfs f3, 0xa4(r30)
    lfs f1, lbl_806D6B8C(r2)
    fmadds f0, f0, f2, f0
    lfs f2, lbl_806D6B74(r2)
    fadds f0, f3, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x14(r31)
    fmuls f0, f1, f0
    fmuls f1, f2, f0
    bl sin
    frsp f3, f1
    lfs f2, lbl_806D6B90(r2)
    lfs f1, 0xb0(r30)
    lfs f0, lbl_806D6B94(r2)
    fmadds f1, f2, f3, f1
    stfs f1, 0xb0(r30)
    lfs f1, 0xb0(r30)
    fcmpo cr0, f1, f0
    bge fn_80117E08_L_801181B4
    fadds f0, f1, f0
    stfs f0, 0xb0(r30)
    fn_80117E08_L_801181B4:
    lfs f1, lbl_806D6B94(r2)
    lfs f0, 0xb0(r30)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne fn_80117E08_L_801181D0
    fsubs f0, f0, f1
    stfs f0, 0xb0(r30)
    fn_80117E08_L_801181D0:
    lwz r4, 0x4(r31)
    mr r3, r30
    li r5, 0x0
    bl ItemHitRegistry_RemoveEntry
    clrlwi. r0, r3, 24
    beq fn_80117E08_L_8011821C
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6B88(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    mr r3, r30
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    fn_80117E08_L_8011821C:
    lmw r27, 0x2c(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
