/* === extracted from auto_VfxEffect_UpdateChil_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Copy();
extern void VfxSlot_SetAnimFrame();
extern void VfxSlot_SetPositionFromVec();
extern void VfxSlot_SetScaleUniform();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D555C;
extern unsigned int lbl_806D55DC;

/* --- function index (1 fns, .text 0x800C7C0C..0x800C7D14) ---
 * [  0] 0x800C7C0C size:0x108   global VfxEffect_UpdateChildPosScaleAlpha_Helper
 */

/* --- forward decls --- */
asm void VfxEffect_UpdateChildPosScaleAlpha_Helper(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxEffect_UpdateChildPosScaleAlpha_Helper[8] = {
    0x10, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxEffect_UpdateChildPosScaleAlpha_Helper = {
    (void *)&VfxEffect_UpdateChildPosScaleAlpha_Helper, 0x00000108, (void *)extab_VfxEffect_UpdateChildPosScaleAlpha_Helper
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxEffect_UpdateChildPosScaleAlpha_Helper(void) { /* 0x800C7C0C size:0x108 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr. r30, r3
    fmr f30, f1
    fmr f31, f2
    mr r31, r4
    beq VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7CEC
    lbz r0, 0x191(r30)
    extsb. r0, r0
    beq VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7C78
    lbz r0, 0x190(r30)
    extsb. r0, r0
    bne VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7C78
    lfs f1, lbl_806D555C(r2)
    addi r3, r30, 0x14
    bl VfxSlot_SetAnimFrame
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    stb r0, 0x191(r30)
    VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7C78:
    lbz r0, 0x1e(r30)
    cmpwi r0, 0x1
    bne VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7C8C
    li r0, 0x0
    stb r0, 0x28(r30)
    VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7C8C:
    lbz r0, 0x190(r30)
    extsb. r0, r0
    beq VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7CA0
    li r0, 0x0
    stb r0, 0x28(r30)
    VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7CA0:
    mr r4, r31
    addi r3, r30, 0x8c
    bl Vec3_Copy
    lwz r5, 0x8c(r30)
    addi r3, r30, 0x14
    lwz r0, 0x90(r30)
    addi r4, r1, 0x8
    stw r5, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0x94(r30)
    stw r0, 0x10(r1)
    bl VfxSlot_SetPositionFromVec
    lfs f0, lbl_806D55DC(r2)
    addi r3, r30, 0x14
    fmuls f0, f0, f30
    stfs f0, 0xb0(r30)
    lfs f1, 0xb0(r30)
    bl VfxSlot_SetScaleUniform
    stfs f31, 0x2c(r30)
    VfxEffect_UpdateChildPosScaleAlpha_Helper_L_800C7CEC:
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r0, 0x44(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
