/* === extracted from auto_BananaField_TestHitB_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Dot();
extern void Vec3_Magnitude();
extern void fn_8025E2AC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D95B8;
extern unsigned int lbl_806D95BC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8037D9E0[];

/* --- function index (1 fns, .text 0x80196F60..0x80197130) ---
 * [  0] 0x80196F60 size:0x1D0   global BananaField_TestHitBox
 */

/* --- forward decls --- */
asm void BananaField_TestHitBox(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BananaField_TestHitBox[8] = {
    0x10, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BananaField_TestHitBox = {
    (void *)&BananaField_TestHitBox, 0x000001D0, (void *)extab_BananaField_TestHitBox
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BananaField_TestHitBox(void) { /* 0x80196F60 size:0x1D0 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stfd f30, 0x30(r1)
    psq_st f30, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r4
    lis r4, lbl_8037D9E0@ha
    lfs f2, 0x0(r5)
    mulli r6, r3, 0xc
    lfs f0, 0xc(r30)
    addi r0, r4, lbl_8037D9E0@l
    fmr f31, f1
    addi r3, r1, 0x14
    fsubs f0, f2, f0
    add r31, r0, r6
    addi r4, r1, 0x8
    stfs f0, 0x14(r1)
    lfs f1, 0x4(r5)
    lfs f0, 0x1c(r30)
    fsubs f0, f1, f0
    stfs f0, 0x18(r1)
    lfs f1, 0x8(r5)
    lfs f0, 0x2c(r30)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r1)
    lfs f0, 0x4(r30)
    stfs f0, 0x8(r1)
    lfs f0, 0x14(r30)
    stfs f0, 0xc(r1)
    lfs f0, 0x24(r30)
    stfs f0, 0x10(r1)
    bl Vec3_Dot
    fneg f0, f31
    fcmpo cr0, f1, f0
    bge BananaField_TestHitBox_L_80197004
    li r3, 0x0
    b BananaField_TestHitBox_L_80197108
    BananaField_TestHitBox_L_80197004:
    lfs f0, 0x0(r30)
    addi r3, r1, 0x8
    stfs f0, 0x8(r1)
    lfs f0, 0x10(r30)
    stfs f0, 0xc(r1)
    lfs f0, 0x20(r30)
    stfs f0, 0x10(r1)
    bl Vec3_Magnitude
    fmr f30, f1
    lfs f0, lbl_806D95B8(r2)
    fcmpu cr0, f0, f30
    beq BananaField_TestHitBox_L_80197048
    lfs f0, lbl_806D95BC(r2)
    addi r3, r1, 0x8
    mr r4, r3
    fdivs f1, f0, f30
    bl fn_8025E2AC
    BananaField_TestHitBox_L_80197048:
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    bl Vec3_Dot
    lfs f0, 0x8(r31)
    fmadds f0, f0, f30, f31
    fcmpo cr0, f1, f0
    ble BananaField_TestHitBox_L_8019706C
    li r3, 0x0
    b BananaField_TestHitBox_L_80197108
    BananaField_TestHitBox_L_8019706C:
    fneg f0, f0
    fcmpo cr0, f1, f0
    bge BananaField_TestHitBox_L_80197080
    li r3, 0x0
    b BananaField_TestHitBox_L_80197108
    BananaField_TestHitBox_L_80197080:
    lfs f0, 0x8(r30)
    addi r3, r1, 0x8
    stfs f0, 0x8(r1)
    lfs f0, 0x18(r30)
    stfs f0, 0xc(r1)
    lfs f0, 0x28(r30)
    stfs f0, 0x10(r1)
    bl Vec3_Magnitude
    fmr f30, f1
    lfs f0, lbl_806D95B8(r2)
    fcmpu cr0, f0, f30
    beq BananaField_TestHitBox_L_801970C4
    lfs f0, lbl_806D95BC(r2)
    addi r3, r1, 0x8
    mr r4, r3
    fdivs f1, f0, f30
    bl fn_8025E2AC
    BananaField_TestHitBox_L_801970C4:
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    bl Vec3_Dot
    lfs f0, 0x0(r31)
    fmadds f0, f0, f30, f31
    fcmpo cr0, f1, f0
    ble BananaField_TestHitBox_L_801970E8
    li r3, 0x0
    b BananaField_TestHitBox_L_80197108
    BananaField_TestHitBox_L_801970E8:
    lfs f0, 0x4(r31)
    fmuls f0, f0, f30
    fneg f0, f0
    fcmpo cr0, f1, f0
    mfcr r0
    srwi r0, r0, 31
    cntlzw r0, r0
    srwi r3, r0, 5
    BananaField_TestHitBox_L_80197108:
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    psq_l f30, 0x38(r1), 0, 0
    lfd f30, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r0, 0x54(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}
