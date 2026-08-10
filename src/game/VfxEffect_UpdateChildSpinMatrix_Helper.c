/* === extracted from auto_VfxEffect_UpdateChil_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Matrix4_PreMultiplyRotZ();
extern void Matrix4_PreMultiplyTranslation();
extern void Mtx44_GetTranslation_ColMajor();
extern void Mtx44_Scale_Uniform();
extern void Mtx_TransposeToMtx44();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D555C;
extern unsigned int lbl_806D5584;
extern unsigned int lbl_806D55A0;
extern unsigned int lbl_806D55E8;
extern unsigned int lbl_806D55EC;
extern unsigned int lbl_806D55F0;

/* --- function index (1 fns, .text 0x800C7F38..0x800C8038) ---
 * [  0] 0x800C7F38 size:0x100   global VfxEffect_UpdateChildSpinMatrix_Helper
 */

/* --- forward decls --- */
asm void VfxEffect_UpdateChildSpinMatrix_Helper(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxEffect_UpdateChildSpinMatrix_Helper[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxEffect_UpdateChildSpinMatrix_Helper = {
    (void *)&VfxEffect_UpdateChildSpinMatrix_Helper, 0x00000100, (void *)extab_VfxEffect_UpdateChildSpinMatrix_Helper
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxEffect_UpdateChildSpinMatrix_Helper(void) { /* 0x800C7F38 size:0x100 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stw r31, 0x8c(r1)
    stw r30, 0x88(r1)
    mr. r30, r3
    mr r31, r4
    beq VfxEffect_UpdateChildSpinMatrix_Helper_L_800C8018
    lfs f1, lbl_806D55E8(r2)
    lfs f0, 0xa0(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xa0(r30)
    lfs f1, lbl_806D55EC(r2)
    lfs f0, 0x150(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x150(r30)
    lfs f1, 0x150(r30)
    bl fn_8027E9E8
    frsp f31, f1
    mr r4, r31
    addi r3, r1, 0x48
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x8
    bl Matrix4_Identity
    lfs f1, lbl_806D555C(r2)
    addi r3, r1, 0x8
    lfs f3, lbl_806D55F0(r2)
    mr r4, r3
    fmr f2, f1
    bl Matrix4_PreMultiplyTranslation
    addi r3, r1, 0x8
    lfs f1, 0xa0(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotZ
    lfs f1, lbl_806D55A0(r2)
    addi r3, r1, 0x8
    lfs f0, lbl_806D5584(r2)
    mr r4, r3
    fmadds f1, f1, f31, f0
    bl Mtx44_Scale_Uniform
    addi r3, r1, 0x48
    addi r4, r1, 0x8
    mr r5, r3
    bl Matrix4_Multiply
    addi r3, r30, 0x48
    addi r4, r1, 0x48
    bl DbgScene_CopyMatrix3x4Transpose
    addi r3, r30, 0x8c
    addi r4, r1, 0x48
    bl Mtx44_GetTranslation_ColMajor
    li r0, 0x1
    stb r0, 0x28(r30)
    VfxEffect_UpdateChildSpinMatrix_Helper_L_800C8018:
    psq_l f31, 0x98(r1), 0, 0
    lwz r0, 0xa4(r1)
    lfd f31, 0x90(r1)
    lwz r31, 0x8c(r1)
    lwz r30, 0x88(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

