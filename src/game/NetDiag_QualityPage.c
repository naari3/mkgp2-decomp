/* === extracted from auto_NetDiag_QualityPage_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void OperationTime_Page();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;
extern unsigned int lbl_806D2D70;
extern unsigned int lbl_806D2D74;
extern unsigned int lbl_806D2D78;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80310448[];
extern unsigned int lbl_80310478[];
extern unsigned int lbl_803FBF80[];

/* --- function index (1 fns, .text 0x80067494..0x80067F74) ---
 * [  0] 0x80067494 size:0xAE0   global NetDiag_QualityPage
 */

/* --- forward decls --- */
asm void NetDiag_QualityPage(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NetDiag_QualityPage[8] = {
    0x24, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NetDiag_QualityPage = {
    (void *)&NetDiag_QualityPage, 0x00000AE0, (void *)extab_NetDiag_QualityPage
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NetDiag_QualityPage(void) { /* 0x80067494 size:0xAE0 */
    nofralloc
    stwu r1, -0x230(r1)
    mflr r0
    stw r0, 0x234(r1)
    stfd f31, 0x220(r1)
    psq_st f31, 0x228(r1), 0, 0
    stfd f30, 0x210(r1)
    psq_st f30, 0x218(r1), 0, 0
    stfd f29, 0x200(r1)
    psq_st f29, 0x208(r1), 0, 0
    stfd f28, 0x1f0(r1)
    psq_st f28, 0x1f8(r1), 0, 0
    stfd f27, 0x1e0(r1)
    psq_st f27, 0x1e8(r1), 0, 0
    stfd f26, 0x1d0(r1)
    psq_st f26, 0x1d8(r1), 0, 0
    stfd f25, 0x1c0(r1)
    psq_st f25, 0x1c8(r1), 0, 0
    stfd f24, 0x1b0(r1)
    psq_st f24, 0x1b8(r1), 0, 0
    stfd f23, 0x1a0(r1)
    psq_st f23, 0x1a8(r1), 0, 0
    stfd f22, 0x190(r1)
    psq_st f22, 0x198(r1), 0, 0
    stfd f21, 0x180(r1)
    psq_st f21, 0x188(r1), 0, 0
    stfd f20, 0x170(r1)
    psq_st f20, 0x178(r1), 0, 0
    stfd f19, 0x160(r1)
    psq_st f19, 0x168(r1), 0, 0
    stfd f18, 0x150(r1)
    psq_st f18, 0x158(r1), 0, 0
    stfd f17, 0x140(r1)
    psq_st f17, 0x148(r1), 0, 0
    stfd f16, 0x130(r1)
    psq_st f16, 0x138(r1), 0, 0
    stfd f15, 0x120(r1)
    psq_st f15, 0x128(r1), 0, 0
    stfd f14, 0x110(r1)
    psq_st f14, 0x118(r1), 0, 0
    stw r31, 0x10c(r1)
    stw r30, 0x108(r1)
    stw r29, 0x104(r1)
    stw r28, 0x100(r1)
    mr. r29, r4
    lis r4, lbl_803FBF80@ha
    mr r31, r3
    addi r30, r4, lbl_803FBF80@l
    bne NetDiag_QualityPage_L_8006755C
    li r0, 0x0
    stw r0, 0x18(r31)
    NetDiag_QualityPage_L_8006755C:
    cmpwi r29, 0x1
    bne NetDiag_QualityPage_L_80067604
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r28, r3
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq NetDiag_QualityPage_L_800675B4
    li r0, 0x1f
    stw r0, 0x8(r31)
    lwz r3, 0x18(r31)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x18(r31)
    ble NetDiag_QualityPage_L_800675B4
    li r0, 0x0
    stw r0, 0x18(r31)
    NetDiag_QualityPage_L_800675B4:
    mr r3, r28
    li r4, 0x1000
    lwz r12, 0x0(r28)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq NetDiag_QualityPage_L_80067604
    lwz r0, 0x18(r31)
    cmpwi r0, 0x0
    bne NetDiag_QualityPage_L_800675FC
    li r0, 0x8
    mr r3, r31
    stw r0, 0x10(r31)
    li r4, 0x0
    li r5, -0x1
    bl OperationTime_Page
    b NetDiag_QualityPage_L_80067604
    NetDiag_QualityPage_L_800675FC:
    li r0, 0x0
    stw r0, 0x10(r31)
    NetDiag_QualityPage_L_80067604:
    cmpwi r29, 0x2
    bne NetDiag_QualityPage_L_80067EC0
    lwz r3, 0x274(r31)
    lis r9, 0x4330
    stw r9, 0x8(r1)
    lwz r11, 0x288(r3)
    lwz r10, 0x47c(r3)
    lwz r8, 0x484(r3)
    lwz r7, 0x48c(r3)
    lwz r6, 0x494(r3)
    lwz r5, 0x49c(r3)
    lwz r4, 0x4a4(r3)
    lwz r0, 0x4ac(r3)
    stw r10, 0xc(r1)
    lfd f0, lbl_806D2D78(r2)
    lfd f1, 0x8(r1)
    stw r11, 0x14(r1)
    fsubs f2, f1, f0
    stw r9, 0x10(r1)
    lfd f1, 0x10(r1)
    stw r8, 0x1c(r1)
    fsubs f1, f1, f0
    stw r9, 0x18(r1)
    lfd f3, 0x18(r1)
    fdivs f31, f2, f1
    stw r11, 0x24(r1)
    stw r9, 0x20(r1)
    lfd f2, 0x20(r1)
    stw r7, 0x2c(r1)
    stw r9, 0x28(r1)
    lfd f1, 0x28(r1)
    fsubs f3, f3, f0
    fsubs f2, f2, f0
    stw r11, 0x34(r1)
    fsubs f5, f1, f0
    stw r9, 0x30(r1)
    fdivs f30, f3, f2
    lfd f2, 0x30(r1)
    stw r6, 0x3c(r1)
    stw r9, 0x38(r1)
    lfd f1, 0x38(r1)
    stw r11, 0x44(r1)
    stw r9, 0x40(r1)
    fsubs f2, f2, f0
    fsubs f4, f1, f0
    lfd f3, 0x40(r1)
    stw r5, 0x4c(r1)
    fdivs f29, f5, f2
    stw r9, 0x48(r1)
    lfd f2, 0x48(r1)
    stw r11, 0x54(r1)
    stw r9, 0x50(r1)
    lfd f1, 0x50(r1)
    fsubs f3, f3, f0
    stw r4, 0x5c(r1)
    fsubs f6, f2, f0
    stw r9, 0x58(r1)
    fsubs f5, f1, f0
    fdivs f28, f4, f3
    lfd f2, 0x58(r1)
    stw r11, 0x64(r1)
    stw r9, 0x60(r1)
    lfd f1, 0x60(r1)
    stw r0, 0x6c(r1)
    stw r9, 0x68(r1)
    fsubs f4, f2, f0
    fsubs f3, f1, f0
    lfd f2, 0x68(r1)
    fdivs f27, f6, f5
    stw r11, 0x74(r1)
    stw r9, 0x70(r1)
    lfd f1, 0x70(r1)
    fsubs f2, f2, f0
    fsubs f1, f1, f0
    fdivs f26, f4, f3
    fdivs f25, f2, f1
    lwz r8, 0x4b4(r3)
    cmplwi r11, 0x0
    lwz r7, 0x4bc(r3)
    lwz r6, 0x4c4(r3)
    lwz r5, 0x4cc(r3)
    lwz r4, 0x4d4(r3)
    lwz r0, 0x4dc(r3)
    stw r8, 0x7c(r1)
    stw r9, 0x78(r1)
    lfd f1, 0x78(r1)
    stw r11, 0x84(r1)
    fsubs f2, f1, f0
    stw r9, 0x80(r1)
    lfd f1, 0x80(r1)
    stw r7, 0x8c(r1)
    fsubs f1, f1, f0
    stw r9, 0x88(r1)
    lfd f3, 0x88(r1)
    fdivs f24, f2, f1
    stw r11, 0x94(r1)
    stw r9, 0x90(r1)
    lfd f2, 0x90(r1)
    stw r6, 0x9c(r1)
    stw r9, 0x98(r1)
    lfd f1, 0x98(r1)
    fsubs f3, f3, f0
    fsubs f2, f2, f0
    stw r11, 0xa4(r1)
    fsubs f4, f1, f0
    stw r9, 0xa0(r1)
    fdivs f23, f3, f2
    lfd f2, 0xa0(r1)
    stw r5, 0xac(r1)
    stw r9, 0xa8(r1)
    lfd f1, 0xa8(r1)
    stw r11, 0xb4(r1)
    stw r9, 0xb0(r1)
    fsubs f2, f2, f0
    fsubs f6, f1, f0
    lfd f3, 0xb0(r1)
    stw r4, 0xbc(r1)
    fdivs f22, f4, f2
    stw r9, 0xb8(r1)
    lfd f2, 0xb8(r1)
    stw r11, 0xc4(r1)
    stw r9, 0xc0(r1)
    lfd f1, 0xc0(r1)
    fsubs f5, f3, f0
    stw r0, 0xcc(r1)
    fsubs f4, f2, f0
    stw r9, 0xc8(r1)
    fsubs f3, f1, f0
    fdivs f21, f6, f5
    lfd f2, 0xc8(r1)
    stw r11, 0xd4(r1)
    stw r9, 0xd0(r1)
    lfd f1, 0xd0(r1)
    fsubs f2, f2, f0
    fsubs f0, f1, f0
    fdivs f20, f4, f3
    fdivs f19, f2, f0
    bne NetDiag_QualityPage_L_80067860
    lfs f19, lbl_806D2D70(r2)
    fmr f20, f19
    fmr f21, f19
    fmr f22, f19
    fmr f23, f19
    fmr f24, f19
    fmr f25, f19
    fmr f26, f19
    fmr f27, f19
    fmr f28, f19
    fmr f29, f19
    fmr f30, f19
    fmr f31, f19
    NetDiag_QualityPage_L_80067860:
    lwz r28, 0x34(r31)
    cmpwi r28, 0x2
    beq NetDiag_QualityPage_L_80067D84
    lwz r11, 0x478(r3)
    lis r10, 0x4330
    lwz r12, 0x290(r3)
    stw r11, 0xd4(r1)
    lwz r9, 0x480(r3)
    stw r10, 0xd0(r1)
    lfd f0, lbl_806D2D78(r2)
    lfd f1, 0xd0(r1)
    stw r12, 0xcc(r1)
    fsubs f2, f1, f0
    lwz r8, 0x488(r3)
    stw r10, 0xc8(r1)
    lwz r7, 0x490(r3)
    lfd f1, 0xc8(r1)
    lwz r6, 0x498(r3)
    fsubs f1, f1, f0
    lwz r5, 0x4a0(r3)
    lwz r4, 0x4a8(r3)
    lwz r0, 0x4b0(r3)
    fdivs f1, f2, f1
    stw r9, 0xc4(r1)
    stw r10, 0xc0(r1)
    lfd f3, 0xc0(r1)
    stw r12, 0xbc(r1)
    stw r10, 0xb8(r1)
    lfd f2, 0xb8(r1)
    fsubs f3, f3, f0
    stw r8, 0xb4(r1)
    fsubs f2, f2, f0
    stw r10, 0xb0(r1)
    stfs f1, 0xf4(r1)
    lfd f1, 0xb0(r1)
    stw r12, 0xac(r1)
    fsubs f4, f1, f0
    fdivs f1, f3, f2
    stw r10, 0xa8(r1)
    lfd f2, 0xa8(r1)
    stw r7, 0xa4(r1)
    stw r10, 0xa0(r1)
    stw r12, 0x9c(r1)
    stfs f1, 0xf0(r1)
    fsubs f2, f2, f0
    lfd f1, 0xa0(r1)
    stw r10, 0x98(r1)
    fsubs f6, f1, f0
    fdivs f1, f4, f2
    lfd f3, 0x98(r1)
    stw r12, 0x8c(r1)
    stw r10, 0x88(r1)
    stw r6, 0x94(r1)
    stw r10, 0x90(r1)
    stfs f1, 0xec(r1)
    fsubs f3, f3, f0
    lfd f1, 0x88(r1)
    lfd f2, 0x90(r1)
    fsubs f4, f1, f0
    stw r12, 0x7c(r1)
    fdivs f1, f6, f3
    stw r10, 0x78(r1)
    stw r5, 0x84(r1)
    stw r10, 0x80(r1)
    stw r4, 0x74(r1)
    stw r10, 0x70(r1)
    fsubs f5, f2, f0
    stfs f1, 0xe8(r1)
    lfd f1, 0x78(r1)
    lfd f2, 0x80(r1)
    fsubs f6, f1, f0
    stw r0, 0x64(r1)
    fdivs f1, f5, f4
    lfd f3, 0x70(r1)
    stw r10, 0x60(r1)
    stw r12, 0x6c(r1)
    stw r10, 0x68(r1)
    stw r12, 0x5c(r1)
    fsubs f7, f2, f0
    stfs f1, 0xe4(r1)
    lfd f2, 0x68(r1)
    fsubs f5, f3, f0
    lfd f1, 0x60(r1)
    stw r10, 0x58(r1)
    fsubs f3, f1, f0
    fdivs f1, f7, f6
    stfs f1, 0xe0(r1)
    fsubs f4, f2, f0
    lfd f1, 0x58(r1)
    fsubs f2, f1, f0
    fdivs f1, f5, f4
    stfs f1, 0xdc(r1)
    fdivs f1, f3, f2
    stfs f1, 0xd8(r1)
    lwz r7, 0x4b8(r3)
    cmplwi r12, 0x0
    lwz r6, 0x4c0(r3)
    lwz r5, 0x4c8(r3)
    lwz r4, 0x4d0(r3)
    lwz r0, 0x4d8(r3)
    stw r7, 0x54(r1)
    stw r10, 0x50(r1)
    lfd f1, 0x50(r1)
    stw r12, 0x4c(r1)
    fsubs f2, f1, f0
    stw r10, 0x48(r1)
    lfd f1, 0x48(r1)
    stw r6, 0x44(r1)
    fsubs f1, f1, f0
    stw r10, 0x40(r1)
    lfd f3, 0x40(r1)
    fdivs f18, f2, f1
    stw r12, 0x3c(r1)
    stw r10, 0x38(r1)
    lfd f2, 0x38(r1)
    stw r5, 0x34(r1)
    stw r10, 0x30(r1)
    lfd f1, 0x30(r1)
    fsubs f3, f3, f0
    fsubs f2, f2, f0
    stw r12, 0x2c(r1)
    fsubs f5, f1, f0
    stw r10, 0x28(r1)
    fdivs f17, f3, f2
    lfd f2, 0x28(r1)
    stw r4, 0x24(r1)
    stw r10, 0x20(r1)
    lfd f1, 0x20(r1)
    stw r12, 0x1c(r1)
    stw r10, 0x18(r1)
    fsubs f2, f2, f0
    fsubs f4, f1, f0
    lfd f3, 0x18(r1)
    stw r0, 0x14(r1)
    fdivs f16, f5, f2
    stw r10, 0x10(r1)
    lfd f2, 0x10(r1)
    stw r12, 0xc(r1)
    stw r10, 0x8(r1)
    lfd f1, 0x8(r1)
    fsubs f3, f3, f0
    fsubs f2, f2, f0
    fsubs f0, f1, f0
    fdivs f15, f4, f3
    fdivs f14, f2, f0
    bne NetDiag_QualityPage_L_80067ADC
    lfs f14, lbl_806D2D70(r2)
    fmr f15, f14
    stfs f14, 0xd8(r1)
    fmr f16, f14
    fmr f17, f14
    stfs f14, 0xdc(r1)
    fmr f18, f14
    stfs f14, 0xe0(r1)
    stfs f14, 0xe4(r1)
    stfs f14, 0xe8(r1)
    stfs f14, 0xec(r1)
    stfs f14, 0xf0(r1)
    stfs f14, 0xf4(r1)
    NetDiag_QualityPage_L_80067ADC:
    cmpwi r28, 0x0
    bne NetDiag_QualityPage_L_80067B50
    lwz r3, 0x18(r31)
    addi r28, r30, 0x191c
    li r30, 0x0
    addi r29, r3, 0xc
    b NetDiag_QualityPage_L_80067B40
    NetDiag_QualityPage_L_80067AF8:
    cmpw r30, r29
    bne NetDiag_QualityPage_L_80067B0C
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_QualityPage_L_80067B38
    NetDiag_QualityPage_L_80067B0C:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_QualityPage_L_80067B38
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_QualityPage_L_80067B38:
    addi r28, r28, 0xc
    addi r30, r30, 0x1
    NetDiag_QualityPage_L_80067B40:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_QualityPage_L_80067AF8
    b NetDiag_QualityPage_L_80067BB8
    NetDiag_QualityPage_L_80067B50:
    lwz r3, 0x18(r31)
    addi r28, r30, 0x19dc
    li r29, 0x0
    addi r30, r3, 0xc
    b NetDiag_QualityPage_L_80067BAC
    NetDiag_QualityPage_L_80067B64:
    cmpw r29, r30
    bne NetDiag_QualityPage_L_80067B78
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_QualityPage_L_80067BA4
    NetDiag_QualityPage_L_80067B78:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_QualityPage_L_80067BA4
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_QualityPage_L_80067BA4:
    addi r28, r28, 0xc
    addi r29, r29, 0x1
    NetDiag_QualityPage_L_80067BAC:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_QualityPage_L_80067B64
    NetDiag_QualityPage_L_80067BB8:
    lfs f5, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    lfs f0, 0xf4(r1)
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    li r4, 0x62
    fmuls f2, f5, f0
    lfs f0, 0xf0(r1)
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x78
    fmuls f3, f5, f0
    lfs f0, 0xec(r1)
    fmuls f4, f5, f0
    lfs f0, 0xe8(r1)
    li r6, 0x7
    fmuls f5, f5, f0
    creqv 6, 6, 6
    bl DrawText
    lfs f5, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    lfs f0, 0xe4(r1)
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    li r4, 0x62
    fmuls f2, f5, f0
    lfs f0, 0xe0(r1)
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x90
    fmuls f3, f5, f0
    lfs f0, 0xdc(r1)
    fmuls f4, f5, f0
    lfs f0, 0xd8(r1)
    li r6, 0x7
    fmuls f5, f5, f0
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f18
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f0, f17
    li r4, 0x62
    fmuls f4, f0, f16
    li r5, 0xa8
    fmuls f5, f0, f15
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310478@ha
    addi r7, r3, lbl_80310478@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f14
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x62
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f31
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f0, f30
    li r4, 0x62
    fmuls f4, f0, f29
    li r5, 0xf0
    fmuls f5, f0, f28
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f27
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f0, f26
    li r4, 0x62
    fmuls f4, f0, f25
    li r5, 0x108
    fmuls f5, f0, f24
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f23
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f0, f22
    li r4, 0x62
    fmuls f4, f0, f21
    li r5, 0x120
    fmuls f5, f0, f20
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310478@ha
    addi r7, r3, lbl_80310478@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f19
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x62
    li r5, 0x138
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b NetDiag_QualityPage_L_80067EC0
    NetDiag_QualityPage_L_80067D84:
    lwz r3, 0x18(r31)
    addi r28, r30, 0x1a9c
    li r29, 0x0
    addi r30, r3, 0x6
    b NetDiag_QualityPage_L_80067DE0
    NetDiag_QualityPage_L_80067D98:
    cmpw r29, r30
    bne NetDiag_QualityPage_L_80067DAC
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_QualityPage_L_80067DD8
    NetDiag_QualityPage_L_80067DAC:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_QualityPage_L_80067DD8
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_QualityPage_L_80067DD8:
    addi r28, r28, 0xc
    addi r29, r29, 0x1
    NetDiag_QualityPage_L_80067DE0:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_QualityPage_L_80067D98
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f31
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f0, f30
    li r4, 0x62
    fmuls f4, f0, f29
    li r5, 0x60
    fmuls f5, f0, f28
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f27
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f0, f26
    li r4, 0x62
    fmuls f4, f0, f25
    li r5, 0x78
    fmuls f5, f0, f24
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310448@ha
    addi r7, r3, lbl_80310448@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f23
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f0, f22
    li r4, 0x62
    fmuls f4, f0, f21
    li r5, 0x90
    fmuls f5, f0, f20
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310478@ha
    addi r7, r3, lbl_80310478@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f19
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x62
    li r5, 0xa8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    NetDiag_QualityPage_L_80067EC0:
    li r3, 0x1
    psq_l f31, 0x228(r1), 0, 0
    lfd f31, 0x220(r1)
    psq_l f30, 0x218(r1), 0, 0
    lfd f30, 0x210(r1)
    psq_l f29, 0x208(r1), 0, 0
    lfd f29, 0x200(r1)
    psq_l f28, 0x1f8(r1), 0, 0
    lfd f28, 0x1f0(r1)
    psq_l f27, 0x1e8(r1), 0, 0
    lfd f27, 0x1e0(r1)
    psq_l f26, 0x1d8(r1), 0, 0
    lfd f26, 0x1d0(r1)
    psq_l f25, 0x1c8(r1), 0, 0
    lfd f25, 0x1c0(r1)
    psq_l f24, 0x1b8(r1), 0, 0
    lfd f24, 0x1b0(r1)
    psq_l f23, 0x1a8(r1), 0, 0
    lfd f23, 0x1a0(r1)
    psq_l f22, 0x198(r1), 0, 0
    lfd f22, 0x190(r1)
    psq_l f21, 0x188(r1), 0, 0
    lfd f21, 0x180(r1)
    psq_l f20, 0x178(r1), 0, 0
    lfd f20, 0x170(r1)
    psq_l f19, 0x168(r1), 0, 0
    lfd f19, 0x160(r1)
    psq_l f18, 0x158(r1), 0, 0
    lfd f18, 0x150(r1)
    psq_l f17, 0x148(r1), 0, 0
    lfd f17, 0x140(r1)
    psq_l f16, 0x138(r1), 0, 0
    lfd f16, 0x130(r1)
    psq_l f15, 0x128(r1), 0, 0
    lfd f15, 0x120(r1)
    psq_l f14, 0x118(r1), 0, 0
    lfd f14, 0x110(r1)
    lwz r31, 0x10c(r1)
    lwz r30, 0x108(r1)
    lwz r29, 0x104(r1)
    lwz r0, 0x234(r1)
    lwz r28, 0x100(r1)
    mtlr r0
    addi r1, r1, 0x230
    blr
}

