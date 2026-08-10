/* === extracted from auto_NetDiag_PacketPage_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void Stats_PacketStats_UI();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;
extern unsigned int lbl_806D2D70;
extern unsigned int lbl_806D2D74;
extern unsigned int lbl_806D2D78;
extern const char lbl_806D2D80[5];

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80310478[];
extern unsigned int lbl_8031049C[];
extern unsigned int lbl_803FBF80[];

/* --- function index (1 fns, .text 0x80068D00..0x80069720) ---
 * [  0] 0x80068D00 size:0xA20   global NetDiag_PacketPage
 */

/* --- forward decls --- */
asm void NetDiag_PacketPage(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NetDiag_PacketPage[8] = {
    0x34, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NetDiag_PacketPage = {
    (void *)&NetDiag_PacketPage, 0x00000A20, (void *)extab_NetDiag_PacketPage
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NetDiag_PacketPage(void) { /* 0x80068D00 size:0xA20 */
    nofralloc
    stwu r1, -0x290(r1)
    mflr r0
    stw r0, 0x294(r1)
    stfd f31, 0x280(r1)
    psq_st f31, 0x288(r1), 0, 0
    stfd f30, 0x270(r1)
    psq_st f30, 0x278(r1), 0, 0
    stfd f29, 0x260(r1)
    psq_st f29, 0x268(r1), 0, 0
    stfd f28, 0x250(r1)
    psq_st f28, 0x258(r1), 0, 0
    stfd f27, 0x240(r1)
    psq_st f27, 0x248(r1), 0, 0
    stfd f26, 0x230(r1)
    psq_st f26, 0x238(r1), 0, 0
    stfd f25, 0x220(r1)
    psq_st f25, 0x228(r1), 0, 0
    stfd f24, 0x210(r1)
    psq_st f24, 0x218(r1), 0, 0
    stfd f23, 0x200(r1)
    psq_st f23, 0x208(r1), 0, 0
    stfd f22, 0x1f0(r1)
    psq_st f22, 0x1f8(r1), 0, 0
    stfd f21, 0x1e0(r1)
    psq_st f21, 0x1e8(r1), 0, 0
    stfd f20, 0x1d0(r1)
    psq_st f20, 0x1d8(r1), 0, 0
    stfd f19, 0x1c0(r1)
    psq_st f19, 0x1c8(r1), 0, 0
    stfd f18, 0x1b0(r1)
    psq_st f18, 0x1b8(r1), 0, 0
    stfd f17, 0x1a0(r1)
    psq_st f17, 0x1a8(r1), 0, 0
    stfd f16, 0x190(r1)
    psq_st f16, 0x198(r1), 0, 0
    stfd f15, 0x180(r1)
    psq_st f15, 0x188(r1), 0, 0
    stfd f14, 0x170(r1)
    psq_st f14, 0x178(r1), 0, 0
    stmw r26, 0x158(r1)
    mr. r27, r4
    lis r4, lbl_803FBF80@ha
    mr r31, r3
    addi r30, r4, lbl_803FBF80@l
    bne NetDiag_PacketPage_L_80068DBC
    li r0, 0x0
    stw r0, 0x18(r31)
    NetDiag_PacketPage_L_80068DBC:
    cmpwi r27, 0x1
    bne NetDiag_PacketPage_L_80068E64
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r26, r3
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq NetDiag_PacketPage_L_80068E14
    li r0, 0x1f
    stw r0, 0x8(r31)
    lwz r3, 0x18(r31)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x18(r31)
    ble NetDiag_PacketPage_L_80068E14
    li r0, 0x0
    stw r0, 0x18(r31)
    NetDiag_PacketPage_L_80068E14:
    mr r3, r26
    li r4, 0x1000
    lwz r12, 0x0(r26)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq NetDiag_PacketPage_L_80068E64
    lwz r0, 0x18(r31)
    cmpwi r0, 0x0
    bne NetDiag_PacketPage_L_80068E5C
    li r0, 0x1d
    mr r3, r31
    stw r0, 0x10(r31)
    li r4, 0x0
    li r5, -0x1
    bl Stats_PacketStats_UI
    b NetDiag_PacketPage_L_80068E64
    NetDiag_PacketPage_L_80068E5C:
    li r0, 0x0
    stw r0, 0x10(r31)
    NetDiag_PacketPage_L_80068E64:
    cmpwi r27, 0x2
    bne NetDiag_PacketPage_L_80069678
    lwz r3, 0x274(r31)
    lis r0, 0x4330
    stw r0, 0x8(r1)
    lwz r5, 0x2b4(r3)
    lwz r4, 0x2b0(r3)
    lwz r27, 0x2e0(r3)
    add r4, r4, r5
    lwz r5, 0x2ac(r3)
    lwz r26, 0x2f4(r3)
    add r28, r5, r4
    lwz r11, 0x2fc(r3)
    stw r28, 0xc(r1)
    lfd f0, lbl_806D2D78(r2)
    lfd f1, 0x8(r1)
    stw r27, 0x14(r1)
    fsubs f31, f1, f0
    lwz r12, 0x2f8(r3)
    stw r0, 0x10(r1)
    lwz r9, 0x304(r3)
    lfd f1, 0x10(r1)
    lwz r6, 0x310(r3)
    fsubs f1, f1, f0
    lwz r10, 0x300(r3)
    lwz r7, 0x30c(r3)
    lwz r8, 0x308(r3)
    fdivs f1, f1, f31
    lwz r5, 0x314(r3)
    lwz r4, 0x318(r3)
    stw r26, 0x1c(r1)
    stw r0, 0x18(r1)
    lfd f3, 0x18(r1)
    stw r11, 0x2c(r1)
    fsubs f3, f3, f0
    stw r0, 0x28(r1)
    stfs f1, 0x154(r1)
    lfd f1, 0x28(r1)
    stw r12, 0x24(r1)
    fsubs f9, f1, f0
    fdivs f1, f3, f31
    stw r0, 0x20(r1)
    lfd f2, 0x20(r1)
    stw r9, 0x3c(r1)
    stw r0, 0x38(r1)
    stw r6, 0x54(r1)
    stfs f1, 0x150(r1)
    fsubs f4, f2, f0
    lfd f1, 0x38(r1)
    stw r0, 0x50(r1)
    fsubs f7, f1, f0
    fdivs f1, f4, f31
    stw r10, 0x34(r1)
    stw r0, 0x30(r1)
    lfd f2, 0x30(r1)
    stw r7, 0x4c(r1)
    stw r0, 0x48(r1)
    stfs f1, 0x14c(r1)
    fsubs f8, f2, f0
    lfd f1, 0x50(r1)
    lfd f2, 0x48(r1)
    fsubs f4, f1, f0
    stw r8, 0x44(r1)
    fdivs f1, f9, f31
    stw r0, 0x40(r1)
    lfd f3, 0x40(r1)
    stw r5, 0x5c(r1)
    stw r0, 0x58(r1)
    stw r4, 0x64(r1)
    fsubs f5, f2, f0
    stw r0, 0x60(r1)
    lfd f2, 0x58(r1)
    fsubs f6, f3, f0
    stfs f1, 0x148(r1)
    lfd f1, 0x60(r1)
    fsubs f3, f2, f0
    fsubs f2, f1, f0
    fdivs f1, f8, f31
    stfs f1, 0x144(r1)
    fdivs f1, f7, f31
    stfs f1, 0x140(r1)
    fdivs f1, f6, f31
    stfs f1, 0x13c(r1)
    fdivs f1, f5, f31
    stfs f1, 0x138(r1)
    fdivs f1, f4, f31
    stfs f1, 0x134(r1)
    fdivs f1, f3, f31
    stfs f1, 0x130(r1)
    fdivs f1, f2, f31
    stfs f1, 0x12c(r1)
    lwz r26, 0x31c(r3)
    lwz r27, 0x320(r3)
    stw r26, 0x6c(r1)
    lwz r29, 0x328(r3)
    stw r0, 0x68(r1)
    lwz r28, 0x324(r3)
    lfd f1, 0x68(r1)
    lwz r11, 0x330(r3)
    fsubs f1, f1, f0
    lwz r8, 0x33c(r3)
    lwz r12, 0x32c(r3)
    lwz r10, 0x334(r3)
    fdivs f1, f1, f31
    lwz r6, 0x344(r3)
    lwz r9, 0x338(r3)
    lwz r7, 0x340(r3)
    lwz r5, 0x348(r3)
    lwz r4, 0x34c(r3)
    stw r27, 0x74(r1)
    stw r0, 0x70(r1)
    lfd f3, 0x70(r1)
    stw r29, 0x84(r1)
    fsubs f3, f3, f0
    stw r0, 0x80(r1)
    stfs f1, 0x128(r1)
    lfd f1, 0x80(r1)
    stw r28, 0x7c(r1)
    fsubs f4, f1, f0
    fdivs f1, f3, f31
    stw r0, 0x78(r1)
    lfd f2, 0x78(r1)
    stw r11, 0x94(r1)
    stw r0, 0x90(r1)
    stw r8, 0xac(r1)
    stfs f1, 0x124(r1)
    fsubs f5, f2, f0
    lfd f1, 0x90(r1)
    stw r0, 0xa8(r1)
    fsubs f8, f1, f0
    fdivs f1, f5, f31
    stw r12, 0x8c(r1)
    stw r0, 0x88(r1)
    lfd f2, 0x88(r1)
    stw r10, 0x9c(r1)
    stw r0, 0x98(r1)
    stfs f1, 0x120(r1)
    fsubs f9, f2, f0
    lfd f1, 0xa8(r1)
    fdivs f30, f8, f31
    lfd f3, 0x98(r1)
    stw r6, 0xbc(r1)
    stw r0, 0xb8(r1)
    stw r9, 0xa4(r1)
    stw r0, 0xa0(r1)
    fsubs f5, f1, f0
    lfd f2, 0xa0(r1)
    fdivs f1, f4, f31
    stw r7, 0xb4(r1)
    stw r0, 0xb0(r1)
    stw r5, 0xc4(r1)
    stw r0, 0xc0(r1)
    stw r4, 0xcc(r1)
    fsubs f6, f2, f0
    stfs f1, 0x11c(r1)
    fsubs f7, f3, f0
    lfd f1, 0xb8(r1)
    lfd f2, 0xb0(r1)
    fdivs f27, f5, f31
    stw r0, 0xc8(r1)
    fsubs f3, f1, f0
    fsubs f4, f2, f0
    lfd f2, 0xc0(r1)
    fdivs f1, f9, f31
    stfs f1, 0x118(r1)
    fsubs f2, f2, f0
    lfd f1, 0xc8(r1)
    fdivs f29, f7, f31
    fsubs f1, f1, f0
    fdivs f28, f6, f31
    fdivs f26, f4, f31
    fdivs f25, f3, f31
    fdivs f24, f2, f31
    fdivs f23, f1, f31
    lwz r11, 0x350(r3)
    lwz r10, 0x354(r3)
    lwz r9, 0x358(r3)
    lwz r8, 0x35c(r3)
    lwz r7, 0x360(r3)
    lwz r6, 0x364(r3)
    lwz r5, 0x368(r3)
    lwz r4, 0x36c(r3)
    lwz r3, 0x370(r3)
    stw r11, 0xd4(r1)
    lfs f1, lbl_806D2D70(r2)
    stw r0, 0xd0(r1)
    fcmpu cr0, f1, f31
    lfd f2, 0xd0(r1)
    stw r10, 0xdc(r1)
    fsubs f2, f2, f0
    stw r0, 0xd8(r1)
    lfd f4, 0xd8(r1)
    fdivs f22, f2, f31
    stw r9, 0xe4(r1)
    stw r0, 0xe0(r1)
    lfd f3, 0xe0(r1)
    stw r8, 0xec(r1)
    stw r0, 0xe8(r1)
    lfd f2, 0xe8(r1)
    fsubs f4, f4, f0
    fsubs f8, f3, f0
    stw r7, 0xf4(r1)
    fsubs f7, f2, f0
    stw r0, 0xf0(r1)
    fdivs f21, f4, f31
    lfd f3, 0xf0(r1)
    stw r6, 0xfc(r1)
    stw r0, 0xf8(r1)
    lfd f2, 0xf8(r1)
    stw r5, 0x104(r1)
    stw r0, 0x100(r1)
    fsubs f6, f3, f0
    fsubs f5, f2, f0
    lfd f4, 0x100(r1)
    fdivs f20, f8, f31
    stw r4, 0x10c(r1)
    stw r0, 0x108(r1)
    lfd f3, 0x108(r1)
    stw r3, 0x114(r1)
    stw r0, 0x110(r1)
    lfd f2, 0x110(r1)
    fsubs f4, f4, f0
    fsubs f3, f3, f0
    fsubs f0, f2, f0
    fdivs f19, f7, f31
    fdivs f18, f6, f31
    fdivs f17, f5, f31
    fdivs f16, f4, f31
    fdivs f15, f3, f31
    fdivs f14, f0, f31
    bne NetDiag_PacketPage_L_80069284
    fmr f30, f1
    stfs f1, 0x154(r1)
    fmr f22, f1
    fmr f23, f1
    stfs f1, 0x134(r1)
    fmr f24, f1
    fmr f25, f1
    stfs f1, 0x138(r1)
    fmr f26, f1
    fmr f27, f1
    stfs f1, 0x13c(r1)
    fmr f28, f1
    fmr f29, f1
    stfs f1, 0x140(r1)
    fmr f14, f1
    fmr f15, f1
    stfs f1, 0x144(r1)
    fmr f16, f1
    fmr f17, f1
    stfs f1, 0x148(r1)
    fmr f18, f1
    fmr f19, f1
    stfs f1, 0x14c(r1)
    fmr f20, f1
    fmr f21, f1
    stfs f1, 0x150(r1)
    stfs f1, 0x118(r1)
    stfs f1, 0x11c(r1)
    stfs f1, 0x120(r1)
    stfs f1, 0x124(r1)
    stfs f1, 0x128(r1)
    stfs f1, 0x12c(r1)
    stfs f1, 0x130(r1)
    NetDiag_PacketPage_L_80069284:
    lwz r0, 0x34(r31)
    cmpwi r0, 0x2
    beq NetDiag_PacketPage_L_800693D0
    cmpwi r0, 0x0
    bne NetDiag_PacketPage_L_80069304
    lwz r3, 0x18(r31)
    addi r28, r30, 0x12a4
    li r26, 0x0
    addi r27, r3, 0xd
    b NetDiag_PacketPage_L_800692F4
    NetDiag_PacketPage_L_800692AC:
    cmpw r26, r27
    bne NetDiag_PacketPage_L_800692C0
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_PacketPage_L_800692EC
    NetDiag_PacketPage_L_800692C0:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_PacketPage_L_800692EC
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_PacketPage_L_800692EC:
    addi r28, r28, 0xc
    addi r26, r26, 0x1
    NetDiag_PacketPage_L_800692F4:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_PacketPage_L_800692AC
    b NetDiag_PacketPage_L_8006936C
    NetDiag_PacketPage_L_80069304:
    lwz r3, 0x18(r31)
    addi r28, r30, 0x137c
    li r26, 0x0
    addi r27, r3, 0xd
    b NetDiag_PacketPage_L_80069360
    NetDiag_PacketPage_L_80069318:
    cmpw r26, r27
    bne NetDiag_PacketPage_L_8006932C
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_PacketPage_L_80069358
    NetDiag_PacketPage_L_8006932C:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_PacketPage_L_80069358
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_PacketPage_L_80069358:
    addi r28, r28, 0xc
    addi r26, r26, 0x1
    NetDiag_PacketPage_L_80069360:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_PacketPage_L_80069318
    NetDiag_PacketPage_L_8006936C:
    fctiwz f0, f31
    lwz r3, 0x270(r31)
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x1a4
    li r5, 0x48
    li r6, 0x7
    stfd f0, 0x110(r1)
    la r7, lbl_806D2D80(r2)
    lwz r8, 0x114(r1)
    creqv 6, 6, 6
    bl DrawText
    lfs f1, lbl_806D2D74(r2)
    lis r3, lbl_80310478@ha
    lfs f0, 0x154(r1)
    addi r7, r3, lbl_80310478@l
    lwz r3, 0x270(r31)
    li r4, 0x1a4
    fmuls f2, f1, f0
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x60
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    li r30, 0x8
    b NetDiag_PacketPage_L_80069460
    NetDiag_PacketPage_L_800693D0:
    lwz r3, 0x18(r31)
    addi r28, r30, 0x1454
    li r26, 0x0
    addi r27, r3, 0xc
    b NetDiag_PacketPage_L_8006942C
    NetDiag_PacketPage_L_800693E4:
    cmpw r26, r27
    bne NetDiag_PacketPage_L_800693F8
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_PacketPage_L_80069424
    NetDiag_PacketPage_L_800693F8:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_PacketPage_L_80069424
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_PacketPage_L_80069424:
    addi r28, r28, 0xc
    addi r26, r26, 0x1
    NetDiag_PacketPage_L_8006942C:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_PacketPage_L_800693E4
    fmr f2, f31
    lwz r3, 0x270(r31)
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x1a4
    li r5, 0x48
    li r6, 0x7
    la r7, lbl_806D2D80(r2)
    creqv 6, 6, 6
    bl DrawText
    li r30, 0x6
    NetDiag_PacketPage_L_80069460:
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_8031049C@ha
    addi r7, r3, lbl_8031049C@l
    lwz r3, 0x270(r31)
    mulli r5, r30, 0x18
    fmuls f2, f0, f21
    fmuls f3, f0, f20
    lfs f1, lbl_806D2D44(r2)
    fmuls f4, f0, f19
    li r4, 0x7e
    fmuls f5, f0, f18
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f5, lbl_806D2D74(r2)
    addi r0, r30, 0x1
    lfs f0, 0x150(r1)
    lis r4, lbl_8031049C@ha
    addi r7, r4, lbl_8031049C@l
    lwz r3, 0x270(r31)
    fmuls f2, f5, f0
    lfs f0, 0x14c(r1)
    mulli r5, r0, 0x18
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f5, f0
    lfs f0, 0x148(r1)
    fmuls f4, f5, f0
    lfs f0, 0x144(r1)
    li r4, 0x7e
    li r6, 0x7
    fmuls f5, f5, f0
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x2
    lis r4, lbl_8031049C@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f17
    fmuls f3, f0, f16
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_8031049C@l
    fmuls f4, f0, f15
    fmuls f5, f0, f14
    li r4, 0x7e
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f5, lbl_806D2D74(r2)
    addi r0, r30, 0x3
    lfs f0, 0x140(r1)
    lis r4, lbl_8031049C@ha
    addi r7, r4, lbl_8031049C@l
    lwz r3, 0x270(r31)
    fmuls f2, f5, f0
    lfs f0, 0x13c(r1)
    mulli r5, r0, 0x18
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f5, f0
    lfs f0, 0x138(r1)
    fmuls f4, f5, f0
    lfs f0, 0x134(r1)
    li r4, 0x7e
    li r6, 0x7
    fmuls f5, f5, f0
    creqv 6, 6, 6
    bl DrawText
    lfs f5, lbl_806D2D74(r2)
    addi r0, r30, 0x4
    lfs f0, 0x130(r1)
    lis r4, lbl_8031049C@ha
    addi r7, r4, lbl_8031049C@l
    lwz r3, 0x270(r31)
    fmuls f2, f5, f0
    lfs f0, 0x12c(r1)
    mulli r5, r0, 0x18
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f5, f0
    lfs f0, 0x128(r1)
    fmuls f4, f5, f0
    lfs f0, 0x124(r1)
    li r4, 0x7e
    li r6, 0x7
    fmuls f5, f5, f0
    creqv 6, 6, 6
    bl DrawText
    lfs f5, lbl_806D2D74(r2)
    addi r0, r30, 0x5
    lfs f0, 0x120(r1)
    lis r4, lbl_8031049C@ha
    addi r7, r4, lbl_8031049C@l
    lwz r3, 0x270(r31)
    fmuls f2, f5, f0
    lfs f0, 0x11c(r1)
    mulli r5, r0, 0x18
    lfs f1, lbl_806D2D44(r2)
    fmuls f3, f5, f0
    lfs f0, 0x118(r1)
    fmuls f4, f5, f0
    li r4, 0x7e
    fmuls f5, f5, f30
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x6
    lis r4, lbl_8031049C@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f29
    fmuls f3, f0, f28
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_8031049C@l
    fmuls f4, f0, f27
    fmuls f5, f0, f26
    li r4, 0x7e
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x7
    lis r4, lbl_8031049C@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f25
    fmuls f3, f0, f24
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_8031049C@l
    fmuls f4, f0, f23
    fmuls f5, f0, f22
    li r4, 0x7e
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    NetDiag_PacketPage_L_80069678:
    li r3, 0x1
    psq_l f31, 0x288(r1), 0, 0
    lfd f31, 0x280(r1)
    psq_l f30, 0x278(r1), 0, 0
    lfd f30, 0x270(r1)
    psq_l f29, 0x268(r1), 0, 0
    lfd f29, 0x260(r1)
    psq_l f28, 0x258(r1), 0, 0
    lfd f28, 0x250(r1)
    psq_l f27, 0x248(r1), 0, 0
    lfd f27, 0x240(r1)
    psq_l f26, 0x238(r1), 0, 0
    lfd f26, 0x230(r1)
    psq_l f25, 0x228(r1), 0, 0
    lfd f25, 0x220(r1)
    psq_l f24, 0x218(r1), 0, 0
    lfd f24, 0x210(r1)
    psq_l f23, 0x208(r1), 0, 0
    lfd f23, 0x200(r1)
    psq_l f22, 0x1f8(r1), 0, 0
    lfd f22, 0x1f0(r1)
    psq_l f21, 0x1e8(r1), 0, 0
    lfd f21, 0x1e0(r1)
    psq_l f20, 0x1d8(r1), 0, 0
    lfd f20, 0x1d0(r1)
    psq_l f19, 0x1c8(r1), 0, 0
    lfd f19, 0x1c0(r1)
    psq_l f18, 0x1b8(r1), 0, 0
    lfd f18, 0x1b0(r1)
    psq_l f17, 0x1a8(r1), 0, 0
    lfd f17, 0x1a0(r1)
    psq_l f16, 0x198(r1), 0, 0
    lfd f16, 0x190(r1)
    psq_l f15, 0x188(r1), 0, 0
    lfd f15, 0x180(r1)
    psq_l f14, 0x178(r1), 0, 0
    lfd f14, 0x170(r1)
    lmw r26, 0x158(r1)
    lwz r0, 0x294(r1)
    mtlr r0
    addi r1, r1, 0x290
    blr
}
