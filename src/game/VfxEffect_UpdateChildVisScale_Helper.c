/* === extracted from auto_VfxEffect_UpdateChil_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Copy();
extern void VfxSlot_SetPositionFromVec();
extern void VfxSlot_SetScaleVec3();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D555C;
extern unsigned int lbl_806D5584;
extern unsigned int lbl_806D55A0;
extern unsigned int lbl_806D55AC;
extern unsigned int lbl_806D55B4;
extern unsigned int lbl_806D55E0;

/* --- function index (1 fns, .text 0x800C7D80..0x800C7E8C) ---
 * [  0] 0x800C7D80 size:0x10C   global VfxEffect_UpdateChildVisScale_Helper
 */

/* --- forward decls --- */
asm void VfxEffect_UpdateChildVisScale_Helper(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxEffect_UpdateChildVisScale_Helper[8] = {
    0x08, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxEffect_UpdateChildVisScale_Helper = {
    (void *)&VfxEffect_UpdateChildVisScale_Helper, 0x0000010C, (void *)extab_VfxEffect_UpdateChildVisScale_Helper
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxEffect_UpdateChildVisScale_Helper(void) { /* 0x800C7D80 size:0x10C */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    mr. r31, r3
    fmr f30, f1
    fmr f31, f2
    beq VfxEffect_UpdateChildVisScale_Helper_L_800C7E68
    lbz r0, 0x190(r31)
    extsb. r0, r0
    beq VfxEffect_UpdateChildVisScale_Helper_L_800C7DE4
    lfs f2, 0x150(r31)
    lfs f0, lbl_806D55A0(r2)
    lfs f1, lbl_806D5584(r2)
    fadds f0, f2, f0
    stfs f0, 0x150(r31)
    lfs f0, 0x150(r31)
    fcmpo cr0, f1, f0
    bge VfxEffect_UpdateChildVisScale_Helper_L_800C7E08
    stfs f1, 0x150(r31)
    b VfxEffect_UpdateChildVisScale_Helper_L_800C7E08
    VfxEffect_UpdateChildVisScale_Helper_L_800C7DE4:
    lfs f2, 0x150(r31)
    lfs f1, lbl_806D55B4(r2)
    lfs f0, lbl_806D555C(r2)
    fsubs f1, f2, f1
    stfs f1, 0x150(r31)
    lfs f1, 0x150(r31)
    fcmpo cr0, f1, f0
    bge VfxEffect_UpdateChildVisScale_Helper_L_800C7E08
    stfs f0, 0x150(r31)
    VfxEffect_UpdateChildVisScale_Helper_L_800C7E08:
    addi r3, r31, 0x8c
    bl Vec3_Copy
    lwz r5, 0x8c(r31)
    addi r3, r31, 0x14
    lwz r0, 0x90(r31)
    addi r4, r1, 0x8
    stw r5, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0x94(r31)
    stw r0, 0x10(r1)
    bl VfxSlot_SetPositionFromVec
    stfs f30, 0xb0(r31)
    addi r3, r31, 0x14
    lfs f1, lbl_806D55AC(r2)
    lfs f3, 0xb0(r31)
    lfs f0, lbl_806D55E0(r2)
    fmuls f1, f1, f3
    fmuls f2, f0, f3
    bl VfxSlot_SetScaleVec3
    lfs f0, 0x150(r31)
    li r0, 0x1
    fmuls f0, f0, f31
    stfs f0, 0x2c(r31)
    stb r0, 0x28(r31)
    VfxEffect_UpdateChildVisScale_Helper_L_800C7E68:
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lwz r0, 0x44(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}


