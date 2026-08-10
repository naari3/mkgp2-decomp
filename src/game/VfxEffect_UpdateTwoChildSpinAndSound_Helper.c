/* === extracted from auto_VfxEffect_UpdateTwoC_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void Rand_RangeFloat();
extern void SoundMgr_CountActiveSEInstances();
extern void SoundMgr_PlaySE_Positional();
extern void SoundMgr_PlaySE_WithChannel();
extern void Vec3_Copy();
extern void VfxSlot_SetPositionFromVec();
extern void VfxSlot_SetRotationZ();
extern void VfxSlot_SetScaleUniform();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5560;
extern unsigned int lbl_806D5570;
extern unsigned int lbl_806D557C;
extern unsigned int lbl_806D5580;
extern unsigned int lbl_806D5584;
extern unsigned int lbl_806D5588;

/* --- function index (1 fns, .text 0x800C6A40..0x800C6CB0) ---
 * [  0] 0x800C6A40 size:0x270   global VfxEffect_UpdateTwoChildSpinAndSound_Helper
 */

/* --- forward decls --- */
asm void VfxEffect_UpdateTwoChildSpinAndSound_Helper(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxEffect_UpdateTwoChildSpinAndSound_Helper[8] = {
    0x28, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxEffect_UpdateTwoChildSpinAndSound_Helper = {
    (void *)&VfxEffect_UpdateTwoChildSpinAndSound_Helper, 0x00000270, (void *)extab_VfxEffect_UpdateTwoChildSpinAndSound_Helper
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxEffect_UpdateTwoChildSpinAndSound_Helper(void) { /* 0x800C6A40 size:0x270 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stfd f30, 0x50(r1)
    psq_st f30, 0x58(r1), 0, 0
    stmw r27, 0x3c(r1)
    mr. r27, r3
    fmr f31, f1
    fmr f30, f2
    mr r28, r4
    beq VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C8C
    addi r30, r27, 0xcc
    addi r3, r27, 0x8c
    bl Vec3_Copy
    lfs f1, lbl_806D557C(r2)
    lfs f0, 0x84(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    lfs f0, lbl_806D5560(r2)
    mr r31, r30
    stfs f1, 0x84(r30)
    li r29, 0x0
    fmuls f31, f0, f31
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6AA4:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C04
    mr r4, r28
    addi r3, r3, 0x8c
    bl Vec3_Copy
    lfs f1, lbl_806D5580(r2)
    lfs f2, lbl_806D5570(r2)
    bl Rand_RangeFloat
    lwz r3, 0x10(r31)
    lfs f2, lbl_806D5570(r2)
    lfs f0, 0x8c(r3)
    fadds f0, f0, f1
    lfs f1, lbl_806D5580(r2)
    stfs f0, 0x8c(r3)
    bl Rand_RangeFloat
    lwz r3, 0x10(r31)
    lfs f2, lbl_806D5570(r2)
    lfs f0, 0x90(r3)
    fadds f0, f0, f1
    lfs f1, lbl_806D5580(r2)
    stfs f0, 0x90(r3)
    bl Rand_RangeFloat
    lwz r3, 0x10(r31)
    cmpwi r29, 0x0
    lfs f0, 0x94(r3)
    fadds f0, f0, f1
    stfs f0, 0x94(r3)
    beq VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6B28
    lfs f0, 0x84(r30)
    lwz r3, 0x10(r31)
    stfs f0, 0xa0(r3)
    b VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6B38
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6B28:
    lfs f0, 0x84(r30)
    lwz r3, 0x10(r31)
    fneg f0, f0
    stfs f0, 0xa0(r3)
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6B38:
    lwz r3, 0x10(r31)
    cmpwi r29, 0x0
    stfs f31, 0xb0(r3)
    beq VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6B74
    lfs f1, 0x84(r30)
    bl fn_8027E9E8
    frsp f3, f1
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D5560(r2)
    lfs f0, lbl_806D5584(r2)
    lfs f2, 0xb0(r3)
    fmadds f0, f1, f3, f0
    fmuls f0, f2, f0
    stfs f0, 0xb0(r3)
    b VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6BA8
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6B74:
    lfs f1, lbl_806D5588(r2)
    lfs f0, 0x84(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    bl fn_8027E9E8
    frsp f3, f1
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D5560(r2)
    lfs f0, lbl_806D5584(r2)
    lfs f2, 0xb0(r3)
    fmadds f0, f1, f3, f0
    fmuls f0, f2, f0
    stfs f0, 0xb0(r3)
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6BA8:
    lwz r3, 0x10(r31)
    addi r4, r1, 0x20
    stfs f30, 0x2c(r3)
    lwz r6, 0x10(r31)
    lwz r5, 0x8c(r6)
    addi r3, r6, 0x14
    lwz r0, 0x90(r6)
    stw r5, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0x94(r6)
    stw r0, 0x28(r1)
    bl VfxSlot_SetPositionFromVec
    lwz r3, 0x10(r31)
    lfs f1, 0xa0(r3)
    addi r3, r3, 0x14
    bl VfxSlot_SetRotationZ
    lwz r3, 0x10(r31)
    lfs f1, 0xb0(r3)
    addi r3, r3, 0x14
    bl VfxSlot_SetScaleUniform
    lwz r3, 0x10(r31)
    li r0, 0x1
    stb r0, 0x28(r3)
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C04:
    addi r29, r29, 0x1
    addi r31, r31, 0x4
    cmpwi r29, 0x2
    blt VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6AA4
    lbz r5, 0xc4(r30)
    extsb. r0, r5
    bge VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C64
    li r3, 0xba
    bl SoundMgr_CountActiveSEInstances
    stb r3, 0xc4(r30)
    lbz r5, 0xc4(r30)
    extsb. r0, r5
    blt VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C8C
    lwz r6, 0x8c(r27)
    addi r4, r1, 0x14
    lwz r0, 0x90(r27)
    extsb r5, r5
    li r3, 0xba
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0x94(r27)
    stw r0, 0x1c(r1)
    bl SoundMgr_PlaySE_Positional
    b VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C8C
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C64:
    lwz r6, 0x8c(r27)
    addi r4, r1, 0x8
    lwz r0, 0x90(r27)
    extsb r5, r5
    li r3, 0xba
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0x94(r27)
    stw r0, 0x10(r1)
    bl SoundMgr_PlaySE_WithChannel
    VfxEffect_UpdateTwoChildSpinAndSound_Helper_L_800C6C8C:
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 0x58(r1), 0, 0
    lfd f30, 0x50(r1)
    lmw r27, 0x3c(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

