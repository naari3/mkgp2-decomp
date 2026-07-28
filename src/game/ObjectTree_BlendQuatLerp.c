/* === extracted from auto_ObjectTree_BlendQuat_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_8025E440();
extern void fn_8025E464();
extern void fn_8025E488();
extern void fn_8025E4A8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2344;
extern unsigned char lbl_806D2348[];
extern unsigned char lbl_806D2350[];

/* --- function index (1 fns, .text 0x800326D0..0x800328A8) ---
 * [  0] 0x800326D0 size:0x1D8   global ObjectTree_BlendQuatLerp
 */

/* --- forward decls --- */
asm void ObjectTree_BlendQuatLerp(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ObjectTree_BlendQuatLerp[8] = {
    0x18, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ObjectTree_BlendQuatLerp = {
    (void *)&ObjectTree_BlendQuatLerp, 0x000001D8, (void *)extab_ObjectTree_BlendQuatLerp
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ObjectTree_BlendQuatLerp(void) { /* 0x800326D0 size:0x1D8 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stfd f30, 0x50(r1)
    psq_st f30, 0x58(r1), 0, 0
    stw r31, 0x4c(r1)
    stw r30, 0x48(r1)
    stw r29, 0x44(r1)
    fmr f31, f1
    lfs f1, lbl_806D2344(r2)
    lfs f0, 0x38(r5)
    mr. r29, r4
    mr r30, r5
    mr r31, r6
    fsubs f2, f1, f31
    lfs f1, 0x38(r4)
    fmuls f0, f0, f31
    fmadds f0, f1, f2, f0
    stfs f0, 0x38(r6)
    lfs f0, 0x3c(r5)
    lfs f1, 0x3c(r4)
    fmuls f0, f0, f31
    fmadds f0, f1, f2, f0
    stfs f0, 0x3c(r6)
    lfs f0, 0x40(r5)
    lfs f1, 0x40(r4)
    fmuls f0, f0, f31
    fmadds f0, f1, f2, f0
    stfs f0, 0x40(r6)
    lfs f0, 0x2c(r5)
    lfs f1, 0x2c(r4)
    fmuls f0, f0, f31
    fmadds f0, f1, f2, f0
    stfs f0, 0x2c(r6)
    lfs f0, 0x30(r5)
    lfs f1, 0x30(r4)
    fmuls f0, f0, f31
    fmadds f0, f1, f2, f0
    stfs f0, 0x30(r6)
    lfs f0, 0x34(r5)
    lfs f1, 0x34(r4)
    fmuls f0, f0, f31
    fmadds f0, f1, f2, f0
    stfs f0, 0x34(r6)
    bne ObjectTree_BlendQuatLerp_L_8003279C
    addi r3, r2, -0x7F18  /* lbl_806D2348 */
    li r4, 0x2dd
    addi r5, r2, -0x7F10  /* lbl_806D2350 */
    bl __assert
    ObjectTree_BlendQuatLerp_L_8003279C:
    lfs f0, 0x1c(r29)
    cmplwi r30, 0x0
    stfs f0, 0x28(r1)
    lfs f0, 0x20(r29)
    stfs f0, 0x2c(r1)
    lfs f0, 0x24(r29)
    stfs f0, 0x30(r1)
    lfs f0, 0x28(r29)
    stfs f0, 0x34(r1)
    bne ObjectTree_BlendQuatLerp_L_800327D4
    addi r3, r2, -0x7F18  /* lbl_806D2348 */
    li r4, 0x2dd
    addi r5, r2, -0x7F10  /* lbl_806D2350 */
    bl __assert
    ObjectTree_BlendQuatLerp_L_800327D4:
    lfs f0, 0x1c(r30)
    addi r3, r1, 0x28
    addi r4, r1, 0x18
    addi r5, r1, 0x8
    stfs f0, 0x18(r1)
    lfs f0, 0x20(r30)
    stfs f0, 0x1c(r1)
    lfs f0, 0x24(r30)
    stfs f0, 0x20(r1)
    lfs f0, 0x28(r30)
    stfs f0, 0x24(r1)
    bl fn_8025E464
    addi r3, r1, 0x8
    mr r4, r3
    bl fn_8025E488
    fmr f30, f1
    addi r3, r1, 0x28
    addi r4, r1, 0x18
    addi r5, r1, 0x8
    bl fn_8025E440
    addi r3, r1, 0x8
    mr r4, r3
    bl fn_8025E488
    fcmpo cr0, f30, f1
    ble ObjectTree_BlendQuatLerp_L_80032868
    lfs f0, 0x18(r1)
    lfs f2, 0x1c(r1)
    lfs f1, 0x20(r1)
    fneg f3, f0
    lfs f0, 0x24(r1)
    fneg f2, f2
    fneg f1, f1
    fneg f0, f0
    stfs f3, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    ObjectTree_BlendQuatLerp_L_80032868:
    fmr f1, f31
    addi r3, r1, 0x28
    addi r4, r1, 0x18
    addi r5, r31, 0x1c
    bl fn_8025E4A8
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 0x58(r1), 0, 0
    lfd f30, 0x50(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r0, 0x74(r1)
    lwz r29, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

