/* === extracted from auto_SoundMgr_PlaySE_Posi_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Mtx44_TransformVec3();
extern void SoundMgr_PlaySE();
extern void Vec3_Magnitude_Wrapper();
extern void fn_8016C120();
extern void fn_8016C168();
extern void fn_8016C1B0();
extern void fn_8016C444();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5B98;
extern unsigned int lbl_806D5B9C;
extern unsigned int lbl_806D5BA0;
extern unsigned int lbl_806D5BA4;
extern unsigned int lbl_806D5BA8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_805DF3D0[];

/* --- function index (1 fns, .text 0x800DFD28..0x800DFEB8) ---
 * [  0] 0x800DFD28 size:0x190   global SoundMgr_PlaySE_Positional
 */

/* --- forward decls --- */
asm void SoundMgr_PlaySE_Positional(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SoundMgr_PlaySE_Positional[8] = {
    0x10, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SoundMgr_PlaySE_Positional = {
    (void *)&SoundMgr_PlaySE_Positional, 0x00000190, (void *)extab_SoundMgr_PlaySE_Positional
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SoundMgr_PlaySE_Positional(void) { /* 0x800DFD28 size:0x190 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stfd f30, 0x40(r1)
    psq_st f30, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    mr. r30, r3
    mr r31, r4
    beq SoundMgr_PlaySE_Positional_L_800DFE90
    cmplwi r30, 0xbf
    bne SoundMgr_PlaySE_Positional_L_800DFD6C
    li r3, 0x1
    bl fn_8016C444
    b SoundMgr_PlaySE_Positional_L_800DFE90
    SoundMgr_PlaySE_Positional_L_800DFD6C:
    cmpwi r5, 0x0
    ble SoundMgr_PlaySE_Positional_L_800DFD7C
    clrlslwi r0, r5, 28, 27
    or r30, r30, r0
    SoundMgr_PlaySE_Positional_L_800DFD7C:
    mr r3, r30
    bl SoundMgr_PlaySE
    lwz r5, 0x0(r31)
    lis r3, lbl_805DF3D0@ha
    lwz r6, 0x4(r31)
    addi r4, r3, lbl_805DF3D0@l
    lwz r0, 0x8(r31)
    addi r3, r1, 0x14
    stw r5, 0x8(r1)
    addi r4, r4, 0x40
    addi r5, r1, 0x8
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    addi r3, r1, 0x14
    bl Vec3_Magnitude_Wrapper
    lfs f3, lbl_806D5B9C(r2)
    lfs f2, lbl_806D5B98(r2)
    fsubs f1, f1, f3
    lfs f0, lbl_806D5BA0(r2)
    fdivs f1, f1, f3
    fnmsubs f4, f2, f1, f2
    fcmpo cr0, f4, f0
    bge SoundMgr_PlaySE_Positional_L_800DFDE0
    fmr f4, f0
    SoundMgr_PlaySE_Positional_L_800DFDE0:
    lfs f0, lbl_806D5B98(r2)
    fcmpo cr0, f0, f4
    bge SoundMgr_PlaySE_Positional_L_800DFDF0
    fmr f4, f0
    SoundMgr_PlaySE_Positional_L_800DFDF0:
    lfs f0, 0x14(r1)
    lfs f3, lbl_806D5BA8(r2)
    fneg f2, f0
    lfs f1, lbl_806D5BA4(r2)
    lfs f0, lbl_806D5BA0(r2)
    fmadds f31, f3, f2, f1
    fcmpo cr0, f31, f0
    bge SoundMgr_PlaySE_Positional_L_800DFE14
    fmr f31, f0
    SoundMgr_PlaySE_Positional_L_800DFE14:
    lfs f0, lbl_806D5B98(r2)
    fcmpo cr0, f0, f31
    bge SoundMgr_PlaySE_Positional_L_800DFE24
    fmr f31, f0
    SoundMgr_PlaySE_Positional_L_800DFE24:
    lfs f3, lbl_806D5BA8(r2)
    lfs f2, 0x1c(r1)
    lfs f1, lbl_806D5BA4(r2)
    lfs f0, lbl_806D5BA0(r2)
    fmadds f30, f3, f2, f1
    fcmpo cr0, f30, f0
    bge SoundMgr_PlaySE_Positional_L_800DFE44
    fmr f30, f0
    SoundMgr_PlaySE_Positional_L_800DFE44:
    lfs f0, lbl_806D5B98(r2)
    fcmpo cr0, f0, f30
    bge SoundMgr_PlaySE_Positional_L_800DFE54
    fmr f30, f0
    SoundMgr_PlaySE_Positional_L_800DFE54:
    fctiwz f0, f4
    mr r3, r30
    stfd f0, 0x20(r1)
    lwz r4, 0x24(r1)
    bl fn_8016C1B0
    fctiwz f0, f31
    mr r3, r30
    stfd f0, 0x28(r1)
    lwz r4, 0x2c(r1)
    bl fn_8016C168
    fctiwz f0, f30
    mr r3, r30
    stfd f0, 0x30(r1)
    lwz r4, 0x34(r1)
    bl fn_8016C120
    SoundMgr_PlaySE_Positional_L_800DFE90:
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    psq_l f30, 0x48(r1), 0, 0
    lfd f30, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r0, 0x64(r1)
    lwz r30, 0x38(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}


