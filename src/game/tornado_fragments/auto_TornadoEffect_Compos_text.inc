/* === extracted from auto_TornadoEffect_Compos_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Saturate_Double();
extern void fn_8027E480();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28C8;
extern unsigned int lbl_806D28CC;
extern unsigned int lbl_806D2908;
extern unsigned int lbl_806D290C;
extern unsigned int lbl_806D2918;
extern unsigned int lbl_806D2938;

/* --- function index (1 fns, .text 0x80057A8C..0x80058510) ---
 * [  0] 0x80057A8C size:0xA84   global TornadoEffect_ComposeRenderMatrix
 */

/* --- forward decls --- */
asm void TornadoEffect_ComposeRenderMatrix(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_ComposeRenderMatrix[8] = {
    0x68, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_ComposeRenderMatrix = {
    (void *)&TornadoEffect_ComposeRenderMatrix, 0x00000A84, (void *)extab_TornadoEffect_ComposeRenderMatrix
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_ComposeRenderMatrix(void) { /* 0x80057A8C size:0xA84 */
    nofralloc
    stwu r1, -0x1b0(r1)
    mflr r0
    stw r0, 0x1b4(r1)
    stfd f31, 0x1a0(r1)
    psq_st f31, 0x1a8(r1), 0, 0
    stfd f30, 0x190(r1)
    psq_st f30, 0x198(r1), 0, 0
    stmw r19, 0x15c(r1)
    lfs f5, lbl_806D28C8(r2)
    mr r28, r3
    mr r29, r5
    li r6, 0x0
    stfs f5, 0x0(r5)
    li r0, 0x2
    lfs f4, lbl_806D28CC(r2)
    mr r5, r6
    stfs f5, 0x4(r29)
    mr r9, r29
    lfs f3, lbl_806D2938(r2)
    addi r7, r1, 0xd4
    stfs f5, 0x8(r29)
    lfs f0, 0xec(r3)
    stfs f5, 0xc(r29)
    lfs f1, 0xf0(r3)
    fmuls f2, f3, f0
    stfs f5, 0x10(r29)
    lfs f0, 0xf4(r3)
    fmuls f1, f3, f1
    stfs f5, 0x14(r29)
    fmuls f0, f3, f0
    stfs f5, 0x18(r29)
    stfs f5, 0x1c(r29)
    stfs f5, 0x20(r29)
    stfs f5, 0x24(r29)
    stfs f5, 0x28(r29)
    stfs f5, 0x2c(r29)
    stfs f5, 0x30(r29)
    stfs f5, 0x34(r29)
    stfs f5, 0x38(r29)
    stfs f5, 0x3c(r29)
    stfs f4, 0x3c(r29)
    stfs f4, 0x28(r29)
    stfs f4, 0x14(r29)
    stfs f4, 0x0(r29)
    lfs f3, 0x0(r29)
    fmuls f2, f3, f2
    stfs f2, 0x0(r29)
    lfs f2, 0x14(r29)
    fmuls f1, f2, f1
    stfs f1, 0x14(r29)
    lfs f1, 0x28(r29)
    fmuls f0, f1, f0
    stfs f0, 0x28(r29)
    mtctr r0
    TornadoEffect_ComposeRenderMatrix_L_80057B64:
    lfs f7, 0x0(r9)
    slwi r0, r6, 2
    lfs f6, 0x0(r4)
    addi r3, r6, 0x1
    lfs f5, 0x4(r9)
    addi r8, r4, 0x4
    fmuls f8, f7, f6
    lfs f4, 0x10(r4)
    lfs f3, 0x8(r9)
    lfs f2, 0x20(r4)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r9)
    lfs f0, 0x30(r4)
    lfs f6, 0x4(r4)
    fmadds f8, f3, f2, f8
    lfs f4, 0x14(r4)
    lfs f2, 0x24(r4)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r4)
    stfsx f8, r7, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x8(r4)
    addi r3, r6, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r4)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r4)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r4)
    stfsx f8, r7, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r6, 0x3
    lfs f6, 0xc(r4)
    addi r6, r6, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1c(r4)
    fmadds f8, f3, f2, f8
    lfs f2, 0x2c(r4)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3c(r4)
    stfsx f8, r7, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r7, r0
    lfs f7, 0x10(r9)
    slwi r0, r6, 2
    lfs f6, 0x0(r4)
    addi r3, r6, 0x1
    lfs f5, 0x14(r9)
    addi r5, r5, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x10(r4)
    lfs f3, 0x18(r9)
    lfs f1, 0x1c(r9)
    addi r9, r9, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x20(r4)
    lfs f0, 0x30(r4)
    fmadds f8, f3, f2, f8
    lfs f6, 0x0(r8)
    lfs f4, 0x10(r8)
    lfs f2, 0x20(r8)
    fmadds f8, f1, f0, f8
    lfs f0, 0x30(r8)
    stfsx f8, r7, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x4(r8)
    addi r3, r6, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x14(r8)
    fmadds f8, f3, f2, f8
    lfs f2, 0x24(r8)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r8)
    stfsx f8, r7, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r6, 0x3
    lfs f6, 0x8(r8)
    addi r6, r6, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r8)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r8)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r8)
    stfsx f8, r7, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r7, r0
    bdnz TornadoEffect_ComposeRenderMatrix_L_80057B64
    lfs f1, 0xd4(r1)
    addi r30, r1, 0x114
    lfs f4, lbl_806D28C8(r2)
    stfs f1, 0x0(r29)
    lfs f0, 0xd8(r1)
    lfs f1, 0xdc(r1)
    stfs f0, 0x4(r29)
    lfs f0, 0xe0(r1)
    stfs f1, 0x8(r29)
    lfs f1, 0xe4(r1)
    stfs f0, 0xc(r29)
    lfs f0, 0xe8(r1)
    stfs f1, 0x10(r29)
    lfs f1, 0xec(r1)
    stfs f0, 0x14(r29)
    lfs f0, 0xf0(r1)
    stfs f1, 0x18(r29)
    lfs f1, 0xf4(r1)
    stfs f0, 0x1c(r29)
    lfs f0, 0xf8(r1)
    stfs f1, 0x20(r29)
    lfs f1, 0xfc(r1)
    stfs f0, 0x24(r29)
    lfs f0, 0x100(r1)
    stfs f1, 0x28(r29)
    lfs f1, 0x104(r1)
    stfs f0, 0x2c(r29)
    lfs f0, 0x108(r1)
    stfs f1, 0x30(r29)
    lfs f1, 0x10c(r1)
    stfs f0, 0x34(r29)
    lfs f0, 0x110(r1)
    stfs f1, 0x38(r29)
    lwz r3, 0xc(r28)
    stfs f0, 0x3c(r29)
    lfs f0, lbl_806D28CC(r2)
    stfs f4, 0x114(r1)
    lwz r31, 0x304(r3)
    stfs f4, 0x128(r1)
    lfs f1, 0x120(r28)
    stfs f4, 0x13c(r1)
    lfs f2, lbl_806D2908(r2)
    stfs f4, 0x150(r1)
    lfs f3, lbl_806D290C(r2)
    stfs f4, 0x118(r1)
    stfs f4, 0x11c(r1)
    stfs f4, 0x120(r1)
    stfs f4, 0x124(r1)
    stfs f4, 0x12c(r1)
    stfs f4, 0x130(r1)
    stfs f4, 0x134(r1)
    stfs f4, 0x138(r1)
    stfs f4, 0x140(r1)
    stfs f4, 0x144(r1)
    stfs f4, 0x148(r1)
    stfs f4, 0x14c(r1)
    stfs f0, 0x150(r1)
    stfs f0, 0x13c(r1)
    stfs f0, 0x128(r1)
    stfs f0, 0x114(r1)
    bl Saturate_Double
    lfd f0, lbl_806D2918(r2)
    addi r19, r1, 0x94
    lfs f2, lbl_806D28C8(r2)
    fmul f31, f0, f1
    lfs f0, lbl_806D28CC(r2)
    stfs f2, 0x94(r1)
    stfs f2, 0xa8(r1)
    frsp f31, f31
    stfs f2, 0xbc(r1)
    stfs f2, 0xd0(r1)
    fmr f1, f31
    stfs f2, 0x98(r1)
    stfs f2, 0x9c(r1)
    stfs f2, 0xa0(r1)
    stfs f2, 0xa4(r1)
    stfs f2, 0xac(r1)
    stfs f2, 0xb0(r1)
    stfs f2, 0xb4(r1)
    stfs f2, 0xb8(r1)
    stfs f2, 0xc0(r1)
    stfs f2, 0xc4(r1)
    stfs f2, 0xc8(r1)
    stfs f2, 0xcc(r1)
    stfs f0, 0xd0(r1)
    stfs f0, 0xbc(r1)
    stfs f0, 0xa8(r1)
    stfs f0, 0x94(r1)
    bl fn_8027E480
    frsp f30, f1
    fmr f1, f31
    bl fn_8027E9E8
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f30, 0x94(r1)
    mr r4, r5
    addi r6, r1, 0x14
    fneg f0, f1
    stfs f1, 0x98(r1)
    stfs f30, 0xa8(r1)
    stfs f0, 0xa4(r1)
    mtctr r0
    TornadoEffect_ComposeRenderMatrix_L_80057E90:
    lfs f7, 0x0(r19)
    slwi r0, r5, 2
    lfs f6, 0x114(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r19)
    fmuls f8, f7, f6
    lfs f4, 0x124(r1)
    lfs f3, 0x8(r19)
    lfs f2, 0x134(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r19)
    lfs f0, 0x144(r1)
    lfs f6, 0x118(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x128(r1)
    lfs f2, 0x138(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x148(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x11c(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x12c(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x13c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x14c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x120(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x130(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x140(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x150(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r19)
    slwi r0, r5, 2
    lfs f6, 0x114(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r19)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x124(r1)
    lfs f3, 0x18(r19)
    lfs f1, 0x1c(r19)
    addi r19, r19, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x134(r1)
    lfs f0, 0x144(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x118(r1)
    lfs f4, 0x128(r1)
    lfs f2, 0x138(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x148(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x11c(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x12c(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x13c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x14c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x120(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x130(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x140(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x150(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz TornadoEffect_ComposeRenderMatrix_L_80057E90
    lfs f7, 0x14(r1)
    li r20, 0x0
    lfs f6, 0x18(r1)
    li r0, 0x2
    stfs f7, 0x94(r1)
    mr r21, r20
    lfs f5, 0x1c(r1)
    addi r19, r1, 0x54
    stfs f6, 0x98(r1)
    lfs f4, 0x20(r1)
    stfs f5, 0x9c(r1)
    lfs f3, 0x24(r1)
    stfs f4, 0xa0(r1)
    lfs f2, 0x28(r1)
    stfs f3, 0xa4(r1)
    lfs f1, 0x2c(r1)
    stfs f2, 0xa8(r1)
    lfs f0, 0x30(r1)
    stfs f1, 0xac(r1)
    lfs f7, 0x34(r1)
    stfs f0, 0xb0(r1)
    lfs f6, 0x38(r1)
    lfs f5, 0x3c(r1)
    lfs f4, 0x40(r1)
    lfs f3, 0x44(r1)
    lfs f2, 0x48(r1)
    lfs f1, 0x4c(r1)
    lfs f0, 0x50(r1)
    stfs f7, 0xb4(r1)
    lwz r22, 0x94(r1)
    stfs f6, 0xb8(r1)
    lwz r23, 0x98(r1)
    stfs f5, 0xbc(r1)
    lwz r24, 0x9c(r1)
    stfs f4, 0xc0(r1)
    lwz r25, 0xa0(r1)
    stfs f3, 0xc4(r1)
    lwz r26, 0xa4(r1)
    stfs f2, 0xc8(r1)
    lwz r27, 0xa8(r1)
    stfs f1, 0xcc(r1)
    lwz r12, 0xac(r1)
    stfs f0, 0xd0(r1)
    lwz r11, 0xb0(r1)
    lwz r10, 0xb4(r1)
    lwz r9, 0xb8(r1)
    lwz r8, 0xbc(r1)
    lwz r7, 0xc0(r1)
    lwz r6, 0xc4(r1)
    lwz r5, 0xc8(r1)
    lwz r4, 0xcc(r1)
    lwz r3, 0xd0(r1)
    stw r22, 0x114(r1)
    stw r23, 0x118(r1)
    stw r24, 0x11c(r1)
    stw r25, 0x120(r1)
    stw r26, 0x124(r1)
    stw r27, 0x128(r1)
    stw r12, 0x12c(r1)
    stw r11, 0x130(r1)
    stw r10, 0x134(r1)
    stw r9, 0x138(r1)
    stw r8, 0x13c(r1)
    stw r7, 0x140(r1)
    stw r6, 0x144(r1)
    stw r5, 0x148(r1)
    stw r4, 0x14c(r1)
    stw r3, 0x150(r1)
    mtctr r0
    TornadoEffect_ComposeRenderMatrix_L_80058130:
    lfs f7, 0x0(r30)
    slwi r0, r20, 2
    lfs f6, 0x0(r29)
    addi r3, r20, 0x1
    lfs f5, 0x4(r30)
    fmuls f8, f7, f6
    lfs f4, 0x10(r29)
    lfs f3, 0x8(r30)
    lfs f2, 0x20(r29)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r30)
    lfs f0, 0x30(r29)
    lfs f6, 0x4(r29)
    fmadds f8, f3, f2, f8
    lfs f4, 0x14(r29)
    lfs f2, 0x24(r29)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r29)
    stfsx f8, r19, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x8(r29)
    addi r3, r20, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r29)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r29)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r29)
    stfsx f8, r19, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r20, 0x3
    lfs f6, 0xc(r29)
    addi r20, r20, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1c(r29)
    fmadds f8, f3, f2, f8
    lfs f2, 0x2c(r29)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3c(r29)
    stfsx f8, r19, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r19, r0
    lfs f7, 0x10(r30)
    slwi r0, r20, 2
    lfs f6, 0x0(r29)
    addi r3, r20, 0x1
    lfs f5, 0x14(r30)
    addi r21, r21, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x10(r29)
    lfs f3, 0x18(r30)
    lfs f1, 0x1c(r30)
    addi r30, r30, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x20(r29)
    lfs f0, 0x30(r29)
    fmadds f8, f3, f2, f8
    lfs f6, 0x4(r29)
    lfs f4, 0x14(r29)
    lfs f2, 0x24(r29)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r29)
    stfsx f8, r19, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x8(r29)
    addi r3, r20, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r29)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r29)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r29)
    stfsx f8, r19, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r20, 0x3
    lfs f6, 0xc(r29)
    addi r20, r20, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1c(r29)
    fmadds f8, f3, f2, f8
    lfs f2, 0x2c(r29)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3c(r29)
    stfsx f8, r19, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r19, r0
    bdnz TornadoEffect_ComposeRenderMatrix_L_80058130
    lfs f30, 0x54(r1)
    li r3, 0x10
    lfs f31, 0x58(r1)
    li r4, 0x0
    frsp f7, f30
    lfs f13, 0x5c(r1)
    lfs f12, 0x60(r1)
    frsp f6, f31
    lfs f11, 0x64(r1)
    frsp f5, f13
    stfs f7, 0x0(r29)
    frsp f4, f12
    lfs f10, 0x68(r1)
    frsp f3, f11
    stfs f6, 0x4(r29)
    lfs f9, 0x6c(r1)
    frsp f2, f10
    stfs f5, 0x8(r29)
    lfs f8, 0x70(r1)
    frsp f1, f9
    stfs f4, 0xc(r29)
    frsp f0, f8
    stfs f3, 0x10(r29)
    stfs f2, 0x14(r29)
    stfs f30, 0x114(r1)
    lfs f30, 0x74(r1)
    stfs f1, 0x18(r29)
    frsp f7, f30
    stfs f31, 0x118(r1)
    lfs f31, 0x78(r1)
    stfs f0, 0x1c(r29)
    frsp f6, f31
    stfs f13, 0x11c(r1)
    lfs f13, 0x7c(r1)
    stfs f7, 0x20(r29)
    frsp f5, f13
    stfs f12, 0x120(r1)
    lfs f12, 0x80(r1)
    stfs f6, 0x24(r29)
    frsp f4, f12
    stfs f11, 0x124(r1)
    lfs f11, 0x84(r1)
    stfs f5, 0x28(r29)
    frsp f3, f11
    stfs f10, 0x128(r1)
    lfs f10, 0x88(r1)
    stfs f4, 0x2c(r29)
    frsp f2, f10
    stfs f9, 0x12c(r1)
    lfs f9, 0x8c(r1)
    stfs f3, 0x30(r29)
    frsp f1, f9
    stfs f8, 0x130(r1)
    lfs f8, 0x90(r1)
    stfs f2, 0x34(r29)
    frsp f0, f8
    stfs f1, 0x38(r29)
    stfs f0, 0x3c(r29)
    lwz r5, 0x10(r31)
    lwz r6, 0x14(r31)
    and r0, r5, r4
    stfs f30, 0x134(r1)
    and r3, r6, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    stfs f31, 0x138(r1)
    stfs f13, 0x13c(r1)
    stfs f12, 0x140(r1)
    stfs f11, 0x144(r1)
    stfs f10, 0x148(r1)
    stfs f9, 0x14c(r1)
    stfs f8, 0x150(r1)
    bne TornadoEffect_ComposeRenderMatrix_L_800583E8
    b TornadoEffect_ComposeRenderMatrix_L_800583EC
    TornadoEffect_ComposeRenderMatrix_L_800583E8:
    li r4, 0x1
    TornadoEffect_ComposeRenderMatrix_L_800583EC:
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    beq TornadoEffect_ComposeRenderMatrix_L_8005842C
    li r0, 0x8
    li r4, 0x0
    and r3, r6, r0
    and r0, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne TornadoEffect_ComposeRenderMatrix_L_8005841C
    b TornadoEffect_ComposeRenderMatrix_L_80058420
    TornadoEffect_ComposeRenderMatrix_L_8005841C:
    li r4, 0x1
    TornadoEffect_ComposeRenderMatrix_L_80058420:
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    bne TornadoEffect_ComposeRenderMatrix_L_800584B0
    TornadoEffect_ComposeRenderMatrix_L_8005842C:
    lwz r5, 0xc(r28)
    li r3, 0x10
    li r4, 0x0
    lfs f30, 0x10c(r28)
    lwz r5, 0x304(r5)
    lwz r0, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r0, r4
    and r3, r5, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne TornadoEffect_ComposeRenderMatrix_L_80058464
    b TornadoEffect_ComposeRenderMatrix_L_80058468
    TornadoEffect_ComposeRenderMatrix_L_80058464:
    li r4, 0x1
    TornadoEffect_ComposeRenderMatrix_L_80058468:
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    bne TornadoEffect_ComposeRenderMatrix_L_80058498
    lfs f1, 0x114(r28)
    bl fn_8027E9E8
    frsp f0, f1
    lfs f1, lbl_806D28CC(r2)
    fabs f0, f0
    frsp f0, f0
    fsubs f0, f1, f0
    fadds f0, f1, f0
    fmuls f30, f30, f0
    TornadoEffect_ComposeRenderMatrix_L_80058498:
    lfs f0, lbl_806D28CC(r2)
    lfs f2, 0x18(r28)
    fsubs f1, f30, f0
    lfs f0, 0x34(r29)
    fmadds f0, f2, f1, f0
    stfs f0, 0x34(r29)
    TornadoEffect_ComposeRenderMatrix_L_800584B0:
    lfs f3, 0x30(r31)
    lfs f0, 0x30(r29)
    lfs f2, 0x34(r31)
    lfs f1, 0x38(r31)
    fadds f0, f0, f3
    stfs f3, 0x10(r1)
    stfs f0, 0x30(r29)
    lfs f0, 0x34(r29)
    stfs f2, 0xc(r1)
    fadds f0, f0, f2
    stfs f1, 0x8(r1)
    stfs f0, 0x34(r29)
    lfs f0, 0x38(r29)
    fadds f0, f0, f1
    stfs f0, 0x38(r29)
    psq_l f31, 0x1a8(r1), 0, 0
    lfd f31, 0x1a0(r1)
    psq_l f30, 0x198(r1), 0, 0
    lfd f30, 0x190(r1)
    lmw r19, 0x15c(r1)
    lwz r0, 0x1b4(r1)
    mtlr r0
    addi r1, r1, 0x1b0
    blr
}

