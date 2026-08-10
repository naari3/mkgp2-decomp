/* === extracted from auto_ItemObjectManager_Pe_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void IsRaceStarted();
extern void ItemClass_GetFlagByte1();
extern void ItemObject_TryAcquireTarget();
extern void MTXIdentity();
extern void fn_8025D1B8();
extern void fn_8025D560();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D4868;
extern unsigned int lbl_806D486C;
extern unsigned int lbl_806D4870;
extern unsigned int lbl_806D4874;
extern unsigned int lbl_806D4878;
extern unsigned int lbl_806D487C;
extern unsigned int lbl_806D4880;
extern unsigned int lbl_806D4888;
extern unsigned int lbl_806D4890;

/* --- function index (1 fns, .text 0x800A45B8..0x800A4A30) ---
 * [  0] 0x800A45B8 size:0x478   global ItemObjectManager_PerFrameUpdate
 */

/* --- forward decls --- */
asm void ItemObjectManager_PerFrameUpdate(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemObjectManager_PerFrameUpdate[8] = {
    0x38, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemObjectManager_PerFrameUpdate = {
    (void *)&ItemObjectManager_PerFrameUpdate, 0x00000478, (void *)extab_ItemObjectManager_PerFrameUpdate
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemObjectManager_PerFrameUpdate(void) { /* 0x800A45B8 size:0x478 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r25, 0x14(r1)
    mr r26, r3
    li r29, 0x0
    mr r31, r26
    ItemObjectManager_PerFrameUpdate_L_800A45D4:
    lwz r4, 0x0(r31)
    subfic r3, r4, -0x1
    addi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ItemObjectManager_PerFrameUpdate_L_800A469C
    lwz r3, 0x70(r31)
    cmplwi r3, 0x0
    beq ItemObjectManager_PerFrameUpdate_L_800A4644
    addi r4, r31, 0x40
    bl fn_8025D1B8
    lfs f0, lbl_806D4868(r2)
    addi r3, r31, 0x40
    addi r4, r31, 0x10
    stfs f0, 0x4c(r31)
    stfs f0, 0x5c(r31)
    stfs f0, 0x6c(r31)
    bl fn_8025D560
    lwz r3, 0x70(r31)
    lfs f0, 0xc(r3)
    stfs f0, 0x74(r31)
    lwz r3, 0x70(r31)
    lfs f0, 0x1c(r3)
    stfs f0, 0x78(r31)
    lwz r3, 0x70(r31)
    lfs f0, 0x2c(r3)
    stfs f0, 0x7c(r31)
    ItemObjectManager_PerFrameUpdate_L_800A4644:
    lwz r0, 0x80(r31)
    cmplwi r0, 0x0
    beq ItemObjectManager_PerFrameUpdate_L_800A4684
    addi r3, r31, 0x10
    bl MTXIdentity
    addi r3, r31, 0x40
    bl MTXIdentity
    lwz r3, 0x80(r31)
    lfs f0, 0x0(r3)
    stfs f0, 0x74(r31)
    lwz r3, 0x80(r31)
    lfs f0, 0x4(r3)
    stfs f0, 0x78(r31)
    lwz r3, 0x80(r31)
    lfs f0, 0x8(r3)
    stfs f0, 0x7c(r31)
    ItemObjectManager_PerFrameUpdate_L_800A4684:
    lfs f0, lbl_806D486C(r2)
    li r3, -0x1
    li r0, 0x0
    stfs f0, 0xa0(r31)
    stw r3, 0x90(r31)
    stw r0, 0x98(r31)
    ItemObjectManager_PerFrameUpdate_L_800A469C:
    addi r29, r29, 0x1
    addi r31, r31, 0xbc
    cmpwi r29, 0x7f
    blt ItemObjectManager_PerFrameUpdate_L_800A45D4
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq ItemObjectManager_PerFrameUpdate_L_800A4A1C
    li r28, 0x0
    mr r30, r26
    ItemObjectManager_PerFrameUpdate_L_800A46C0:
    lwz r4, 0x0(r30)
    subfic r3, r4, -0x1
    addi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ItemObjectManager_PerFrameUpdate_L_800A4A0C
    li r27, 0x0
    mr r31, r26
    ItemObjectManager_PerFrameUpdate_L_800A46E4:
    cmpw r28, r27
    beq ItemObjectManager_PerFrameUpdate_L_800A49D4
    lwz r29, 0x0(r31)
    subfic r3, r29, -0x1
    addi r0, r29, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ItemObjectManager_PerFrameUpdate_L_800A49D4
    lwz r25, 0x0(r30)
    cmpwi r25, 0x0
    blt ItemObjectManager_PerFrameUpdate_L_800A4740
    cmpwi r25, 0x3
    bgt ItemObjectManager_PerFrameUpdate_L_800A4740
    cmpwi r29, 0x6
    bne ItemObjectManager_PerFrameUpdate_L_800A4740
    lfs f1, lbl_806D4870(r2)
    mr r3, r30
    lfs f2, lbl_806D4874(r2)
    mr r4, r28
    mr r5, r27
    mr r6, r31
    bl ItemObject_TryAcquireTarget
    ItemObjectManager_PerFrameUpdate_L_800A4740:
    cmpwi r29, 0x0
    blt ItemObjectManager_PerFrameUpdate_L_800A4774
    cmpwi r29, 0x3
    bgt ItemObjectManager_PerFrameUpdate_L_800A4774
    cmpwi r25, 0x6
    bne ItemObjectManager_PerFrameUpdate_L_800A4774
    lfs f1, lbl_806D4878(r2)
    mr r3, r30
    lfs f2, lbl_806D487C(r2)
    mr r4, r28
    mr r5, r27
    mr r6, r31
    bl ItemObject_TryAcquireTarget
    ItemObjectManager_PerFrameUpdate_L_800A4774:
    cmpwi r25, 0x7
    bne ItemObjectManager_PerFrameUpdate_L_800A49D4
    lwz r0, 0xac(r30)
    cmpw r27, r0
    bne ItemObjectManager_PerFrameUpdate_L_800A47CC
    lwz r3, 0xa8(r30)
    cmplwi r3, 0x0
    beq ItemObjectManager_PerFrameUpdate_L_800A47A8
    lwz r3, 0x8(r3)
    bl ItemClass_GetFlagByte1
    extsb r0, r3
    cmpwi r0, 0x1
    beq ItemObjectManager_PerFrameUpdate_L_800A49D4
    ItemObjectManager_PerFrameUpdate_L_800A47A8:
    lwz r3, 0xb0(r30)
    subi r0, r3, 0x1
    stw r0, 0xb0(r30)
    lwz r0, 0xb0(r30)
    cmpwi r0, 0x0
    bgt ItemObjectManager_PerFrameUpdate_L_800A49D4
    li r0, -0x1
    stw r0, 0xac(r30)
    b ItemObjectManager_PerFrameUpdate_L_800A49D4
    ItemObjectManager_PerFrameUpdate_L_800A47CC:
    cmpwi r29, 0x0
    blt ItemObjectManager_PerFrameUpdate_L_800A48D4
    cmpwi r29, 0x3
    bgt ItemObjectManager_PerFrameUpdate_L_800A48D4
    lwz r0, 0x8(r30)
    lfs f4, lbl_806D4880(r2)
    cmpwi r0, 0x3
    beq ItemObjectManager_PerFrameUpdate_L_800A48D4
    lfs f1, 0x78(r31)
    lfs f0, 0x78(r30)
    lfs f2, 0xa4(r30)
    fsubs f6, f1, f0
    lfs f1, 0x74(r31)
    lfs f0, 0x74(r30)
    fmuls f4, f4, f2
    lfs f3, 0x7c(r31)
    lfs f2, 0x7c(r30)
    fsubs f5, f1, f0
    lfs f0, lbl_806D4868(r2)
    fmuls f1, f6, f6
    fsubs f2, f3, f2
    fmadds f1, f5, f5, f1
    fmadds f5, f2, f2, f1
    fcmpo cr0, f5, f0
    ble ItemObjectManager_PerFrameUpdate_L_800A487C
    frsqrte f1, f5
    lfd f3, lbl_806D4888(r2)
    lfd f2, lbl_806D4890(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f5, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f5, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f5, f0, f2
    fmul f0, f1, f0
    fmul f0, f5, f0
    frsp f0, f0
    stfs f0, 0xc(r1)
    lfs f5, 0xc(r1)
    ItemObjectManager_PerFrameUpdate_L_800A487C:
    fcmpo cr0, f4, f5
    blt ItemObjectManager_PerFrameUpdate_L_800A48D4
    stw r27, 0x90(r30)
    li r0, 0x3
    stw r31, 0x9c(r30)
    lwz r3, 0xb4(r31)
    stw r3, 0xb8(r30)
    stw r0, 0x8(r30)
    lwz r0, 0x4(r30)
    cmpwi r0, 0xd
    bne ItemObjectManager_PerFrameUpdate_L_800A48B8
    li r3, 0x1e0
    li r0, 0x1
    stw r3, 0xc(r31)
    stw r0, 0x8(r31)
    ItemObjectManager_PerFrameUpdate_L_800A48B8:
    lwz r0, 0x4(r30)
    cmpwi r0, 0xe
    bne ItemObjectManager_PerFrameUpdate_L_800A48D4
    li r3, 0x0
    li r0, 0x2
    stw r3, 0xc(r31)
    stw r0, 0x8(r31)
    ItemObjectManager_PerFrameUpdate_L_800A48D4:
    cmpwi r29, 0x6
    bne ItemObjectManager_PerFrameUpdate_L_800A49D4
    lwz r0, 0x8(r30)
    lfs f4, lbl_806D487C(r2)
    cmpwi r0, 0x3
    beq ItemObjectManager_PerFrameUpdate_L_800A49D4
    lfs f1, 0x78(r31)
    lfs f0, 0x78(r30)
    lfs f2, 0xa4(r30)
    fsubs f6, f1, f0
    lfs f1, 0x74(r31)
    lfs f0, 0x74(r30)
    fmuls f4, f4, f2
    lfs f3, 0x7c(r31)
    lfs f2, 0x7c(r30)
    fsubs f5, f1, f0
    lfs f0, lbl_806D4868(r2)
    fmuls f1, f6, f6
    fsubs f2, f3, f2
    fmadds f1, f5, f5, f1
    fmadds f5, f2, f2, f1
    fcmpo cr0, f5, f0
    ble ItemObjectManager_PerFrameUpdate_L_800A497C
    frsqrte f1, f5
    lfd f3, lbl_806D4888(r2)
    lfd f2, lbl_806D4890(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f5, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f5, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f5, f0, f2
    fmul f0, f1, f0
    fmul f0, f5, f0
    frsp f0, f0
    stfs f0, 0x8(r1)
    lfs f5, 0x8(r1)
    ItemObjectManager_PerFrameUpdate_L_800A497C:
    fcmpo cr0, f4, f5
    blt ItemObjectManager_PerFrameUpdate_L_800A49D4
    stw r27, 0x90(r30)
    li r0, 0x3
    stw r31, 0x9c(r30)
    lwz r3, 0xb4(r31)
    stw r3, 0xb8(r30)
    stw r0, 0x8(r30)
    lwz r0, 0x4(r30)
    cmpwi r0, 0xd
    bne ItemObjectManager_PerFrameUpdate_L_800A49B8
    li r3, 0x1e0
    li r0, 0x1
    stw r3, 0xc(r31)
    stw r0, 0x8(r31)
    ItemObjectManager_PerFrameUpdate_L_800A49B8:
    lwz r0, 0x4(r30)
    cmpwi r0, 0xe
    bne ItemObjectManager_PerFrameUpdate_L_800A49D4
    li r3, 0x0
    li r0, 0x2
    stw r3, 0xc(r31)
    stw r0, 0x8(r31)
    ItemObjectManager_PerFrameUpdate_L_800A49D4:
    addi r27, r27, 0x1
    addi r31, r31, 0xbc
    cmpwi r27, 0x80
    blt ItemObjectManager_PerFrameUpdate_L_800A46E4
    lwz r3, 0xc(r30)
    cmpwi r3, 0x0
    ble ItemObjectManager_PerFrameUpdate_L_800A4A0C
    subi r0, r3, 0x1
    stw r0, 0xc(r30)
    lwz r0, 0xc(r30)
    cmpwi r0, 0x0
    bgt ItemObjectManager_PerFrameUpdate_L_800A4A0C
    li r0, 0x0
    stw r0, 0x8(r30)
    ItemObjectManager_PerFrameUpdate_L_800A4A0C:
    addi r28, r28, 0x1
    addi r30, r30, 0xbc
    cmpwi r28, 0x7f
    blt ItemObjectManager_PerFrameUpdate_L_800A46C0
    ItemObjectManager_PerFrameUpdate_L_800A4A1C:
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
