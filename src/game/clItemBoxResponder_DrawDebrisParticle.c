/* === extracted from auto_clItemBoxResponder_D_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GXChannel_PushTransform();
extern void Mtx4x4_TransposeTo4x3();
extern void fn_8027E480();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10B8;
extern unsigned int lbl_806D29A8;
extern unsigned int lbl_806D29AC;

/* --- function index (1 fns, .text 0x8005DBA0..0x8005E330) ---
 * [  0] 0x8005DBA0 size:0x790   global clItemBoxResponder_DrawDebrisParticle
 */

/* --- forward decls --- */
asm void clItemBoxResponder_DrawDebrisParticle(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBoxResponder_DrawDebrisParticle[8] = {
    0x40, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_DrawDebrisParticle = {
    (void *)&clItemBoxResponder_DrawDebrisParticle, 0x00000790, (void *)extab_clItemBoxResponder_DrawDebrisParticle
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_DrawDebrisParticle(void) { /* 0x8005DBA0 size:0x790 */
    nofralloc
    stwu r1, -0x1c0(r1)
    mflr r0
    stw r0, 0x1c4(r1)
    stfd f31, 0x1b0(r1)
    psq_st f31, 0x1b8(r1), 0, 0
    stfd f30, 0x1a0(r1)
    psq_st f30, 0x1a8(r1), 0, 0
    stmw r24, 0x180(r1)
    lfs f2, lbl_806D29A8(r2)
    mr r30, r3
    lfs f0, lbl_806D29AC(r2)
    addi r24, r1, 0xc8
    stfs f2, 0x108(r1)
    stfs f2, 0x11c(r1)
    stfs f2, 0x130(r1)
    stfs f2, 0x144(r1)
    stfs f2, 0xc8(r1)
    stfs f2, 0xdc(r1)
    stfs f2, 0xf0(r1)
    stfs f2, 0x104(r1)
    stfs f2, 0x10c(r1)
    stfs f2, 0x110(r1)
    stfs f2, 0x114(r1)
    stfs f2, 0x118(r1)
    stfs f2, 0x120(r1)
    stfs f2, 0x124(r1)
    stfs f2, 0x128(r1)
    stfs f2, 0x12c(r1)
    stfs f2, 0x134(r1)
    stfs f2, 0x138(r1)
    stfs f2, 0x13c(r1)
    stfs f2, 0x140(r1)
    stfs f0, 0x144(r1)
    stfs f0, 0x130(r1)
    stfs f0, 0x11c(r1)
    stfs f0, 0x108(r1)
    lfs f31, 0x24(r3)
    stfs f2, 0xcc(r1)
    fmr f1, f31
    stfs f2, 0xd0(r1)
    stfs f2, 0xd4(r1)
    stfs f2, 0xd8(r1)
    stfs f2, 0xe0(r1)
    stfs f2, 0xe4(r1)
    stfs f2, 0xe8(r1)
    stfs f2, 0xec(r1)
    stfs f2, 0xf4(r1)
    stfs f2, 0xf8(r1)
    stfs f2, 0xfc(r1)
    stfs f2, 0x100(r1)
    stfs f0, 0x104(r1)
    stfs f0, 0xf0(r1)
    stfs f0, 0xdc(r1)
    stfs f0, 0xc8(r1)
    bl fn_8027E480
    frsp f30, f1
    fmr f1, f31
    bl fn_8027E9E8
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f30, 0xc8(r1)
    mr r4, r5
    addi r6, r1, 0x48
    fneg f0, f1
    stfs f1, 0xe8(r1)
    stfs f30, 0xf0(r1)
    stfs f0, 0xd0(r1)
    mtctr r0
    clItemBoxResponder_DrawDebrisParticle_L_8005DCB4:
    lfs f7, 0x0(r24)
    slwi r0, r5, 2
    lfs f6, 0x108(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r24)
    fmuls f8, f7, f6
    lfs f4, 0x118(r1)
    lfs f3, 0x8(r24)
    lfs f2, 0x128(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r24)
    lfs f0, 0x138(r1)
    lfs f6, 0x10c(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x11c(r1)
    lfs f2, 0x12c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x13c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x110(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x120(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x130(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x140(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x114(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x124(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x134(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x144(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r24)
    slwi r0, r5, 2
    lfs f6, 0x108(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r24)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x118(r1)
    lfs f3, 0x18(r24)
    lfs f1, 0x1c(r24)
    addi r24, r24, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x128(r1)
    lfs f0, 0x138(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x10c(r1)
    lfs f4, 0x11c(r1)
    lfs f2, 0x12c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x13c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x110(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x120(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x130(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x140(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x114(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x124(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x134(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x144(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz clItemBoxResponder_DrawDebrisParticle_L_8005DCB4
    lfs f8, 0x48(r1)
    addi r31, r1, 0x88
    lfs f7, 0x4c(r1)
    stfs f8, 0xc8(r1)
    lfs f6, 0x50(r1)
    stfs f7, 0xcc(r1)
    lfs f5, 0x54(r1)
    stfs f6, 0xd0(r1)
    lfs f4, 0x58(r1)
    stfs f5, 0xd4(r1)
    lfs f2, lbl_806D29A8(r2)
    stfs f4, 0xd8(r1)
    lfs f3, 0x5c(r1)
    lfs f1, 0x60(r1)
    stfs f3, 0xdc(r1)
    lfs f0, 0x64(r1)
    stfs f1, 0xe0(r1)
    lfs f8, 0x68(r1)
    stfs f0, 0xe4(r1)
    lfs f7, 0x6c(r1)
    lfs f6, 0x70(r1)
    lfs f5, 0x74(r1)
    lfs f4, 0x78(r1)
    lfs f3, 0x7c(r1)
    lfs f1, 0x80(r1)
    lfs f0, 0x84(r1)
    stfs f8, 0xe8(r1)
    lwz r28, 0xc8(r1)
    stfs f7, 0xec(r1)
    lwz r27, 0xcc(r1)
    stfs f6, 0xf0(r1)
    lwz r26, 0xd0(r1)
    stfs f5, 0xf4(r1)
    lwz r25, 0xd4(r1)
    stfs f4, 0xf8(r1)
    lwz r24, 0xd8(r1)
    stfs f3, 0xfc(r1)
    lwz r12, 0xdc(r1)
    stfs f1, 0x100(r1)
    lwz r11, 0xe0(r1)
    stfs f0, 0x104(r1)
    lwz r10, 0xe4(r1)
    lwz r9, 0xe8(r1)
    lwz r8, 0xec(r1)
    lwz r7, 0xf0(r1)
    lwz r6, 0xf4(r1)
    lwz r5, 0xf8(r1)
    lwz r4, 0xfc(r1)
    lwz r3, 0x100(r1)
    lwz r0, 0x104(r1)
    stw r28, 0x108(r1)
    lfs f0, lbl_806D29AC(r2)
    stfs f2, 0x88(r1)
    stfs f2, 0x9c(r1)
    stfs f2, 0xb0(r1)
    stfs f2, 0xc4(r1)
    stw r27, 0x10c(r1)
    stw r26, 0x110(r1)
    stw r25, 0x114(r1)
    stw r24, 0x118(r1)
    stw r12, 0x11c(r1)
    stw r11, 0x120(r1)
    stw r10, 0x124(r1)
    stw r9, 0x128(r1)
    stw r8, 0x12c(r1)
    stw r7, 0x130(r1)
    stw r6, 0x134(r1)
    stw r5, 0x138(r1)
    stw r4, 0x13c(r1)
    stw r3, 0x140(r1)
    stw r0, 0x144(r1)
    lfs f31, 0x28(r30)
    stfs f2, 0x8c(r1)
    fmr f1, f31
    stfs f2, 0x90(r1)
    stfs f2, 0x94(r1)
    stfs f2, 0x98(r1)
    stfs f2, 0xa0(r1)
    stfs f2, 0xa4(r1)
    stfs f2, 0xa8(r1)
    stfs f2, 0xac(r1)
    stfs f2, 0xb4(r1)
    stfs f2, 0xb8(r1)
    stfs f2, 0xbc(r1)
    stfs f2, 0xc0(r1)
    stfs f0, 0xc4(r1)
    stfs f0, 0xb0(r1)
    stfs f0, 0x9c(r1)
    stfs f0, 0x88(r1)
    bl fn_8027E480
    frsp f30, f1
    fmr f1, f31
    bl fn_8027E9E8
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f30, 0xb0(r1)
    mr r4, r5
    addi r6, r1, 0x8
    fneg f0, f1
    stfs f1, 0xa0(r1)
    stfs f30, 0x9c(r1)
    stfs f0, 0xac(r1)
    mtctr r0
    clItemBoxResponder_DrawDebrisParticle_L_8005DFE0:
    lfs f7, 0x0(r31)
    slwi r0, r5, 2
    lfs f6, 0x108(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r31)
    fmuls f8, f7, f6
    lfs f4, 0x118(r1)
    lfs f3, 0x8(r31)
    lfs f2, 0x128(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r31)
    lfs f0, 0x138(r1)
    lfs f6, 0x10c(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x11c(r1)
    lfs f2, 0x12c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x13c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x110(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x120(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x130(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x140(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x114(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x124(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x134(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x144(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r31)
    slwi r0, r5, 2
    lfs f6, 0x108(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r31)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x118(r1)
    lfs f3, 0x18(r31)
    lfs f1, 0x1c(r31)
    addi r31, r31, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x128(r1)
    lfs f0, 0x138(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x10c(r1)
    lfs f4, 0x11c(r1)
    lfs f2, 0x12c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x13c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x110(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x120(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x130(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x140(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x114(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x124(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x134(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x144(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz clItemBoxResponder_DrawDebrisParticle_L_8005DFE0
    lfs f7, 0x8(r1)
    lfs f6, 0xc(r1)
    lfs f5, 0x10(r1)
    lfs f4, 0x14(r1)
    lfs f3, 0x18(r1)
    lfs f2, 0x1c(r1)
    lfs f1, 0x20(r1)
    lfs f0, 0x24(r1)
    stfs f7, 0x88(r1)
    lfs f7, 0x28(r1)
    stfs f6, 0x8c(r1)
    lfs f6, 0x2c(r1)
    stfs f5, 0x90(r1)
    lfs f5, 0x30(r1)
    stfs f4, 0x94(r1)
    lfs f4, 0x34(r1)
    stfs f3, 0x98(r1)
    lfs f3, 0x38(r1)
    stfs f2, 0x9c(r1)
    lfs f2, 0x3c(r1)
    stfs f1, 0xa0(r1)
    lfs f1, 0x40(r1)
    stfs f0, 0xa4(r1)
    lfs f0, 0x44(r1)
    stfs f7, 0xa8(r1)
    stfs f6, 0xac(r1)
    stfs f5, 0xb0(r1)
    stfs f4, 0xb4(r1)
    stfs f3, 0xb8(r1)
    stfs f2, 0xbc(r1)
    stfs f1, 0xc0(r1)
    stfs f0, 0xc4(r1)
    lwz r24, 0x88(r1)
    addi r3, r1, 0x108
    lwz r25, 0x8c(r1)
    addi r4, r1, 0x148
    lwz r26, 0x90(r1)
    lwz r27, 0x94(r1)
    lwz r28, 0x98(r1)
    lwz r29, 0x9c(r1)
    lwz r31, 0xa0(r1)
    lwz r12, 0xa4(r1)
    lwz r11, 0xa8(r1)
    lwz r10, 0xac(r1)
    lwz r9, 0xb0(r1)
    lwz r8, 0xb4(r1)
    lwz r7, 0xb8(r1)
    lwz r6, 0xbc(r1)
    lwz r5, 0xc0(r1)
    lwz r0, 0xc4(r1)
    stw r24, 0x108(r1)
    stw r25, 0x10c(r1)
    lfs f8, 0x108(r1)
    stw r26, 0x110(r1)
    lfs f5, 0x10c(r1)
    stw r28, 0x118(r1)
    lfs f2, 0x110(r1)
    stw r29, 0x11c(r1)
    lfs f7, 0x118(r1)
    stw r31, 0x120(r1)
    lfs f4, 0x11c(r1)
    stw r11, 0x128(r1)
    lfs f1, 0x120(r1)
    stw r10, 0x12c(r1)
    lfs f6, 0x128(r1)
    stw r9, 0x130(r1)
    lfs f3, 0x12c(r1)
    stw r27, 0x114(r1)
    lfs f0, 0x130(r1)
    stw r12, 0x124(r1)
    stw r8, 0x134(r1)
    stw r7, 0x138(r1)
    stw r6, 0x13c(r1)
    stw r5, 0x140(r1)
    stw r0, 0x144(r1)
    lfs f11, 0x8(r30)
    lfs f10, 0x4(r30)
    lfs f9, 0x0(r30)
    stfs f9, 0x138(r1)
    stfs f10, 0x13c(r1)
    stfs f11, 0x140(r1)
    lfs f9, 0x20(r30)
    fmuls f8, f8, f9
    fmuls f7, f7, f9
    fmuls f6, f6, f9
    fmuls f5, f5, f9
    stfs f8, 0x108(r1)
    fmuls f4, f4, f9
    fmuls f3, f3, f9
    stfs f7, 0x118(r1)
    fmuls f2, f2, f9
    fmuls f1, f1, f9
    stfs f6, 0x128(r1)
    fmuls f0, f0, f9
    stfs f5, 0x10c(r1)
    stfs f4, 0x11c(r1)
    stfs f3, 0x12c(r1)
    stfs f2, 0x110(r1)
    stfs f1, 0x120(r1)
    stfs f0, 0x130(r1)
    bl Mtx4x4_TransposeTo4x3
    lwz r3, lbl_806D10B8(r13)
    addi r4, r1, 0x148
    bl GXChannel_PushTransform
    psq_l f31, 0x1b8(r1), 0, 0
    lfd f31, 0x1b0(r1)
    psq_l f30, 0x1a8(r1), 0, 0
    lfd f30, 0x1a0(r1)
    lmw r24, 0x180(r1)
    lwz r0, 0x1c4(r1)
    mtlr r0
    addi r1, r1, 0x1c0
    blr
}


