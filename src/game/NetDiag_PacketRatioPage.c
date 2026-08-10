/* === extracted from auto_NetDiag_PacketRatioP_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void Stats_Display_UI();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;
extern unsigned int lbl_806D2D70;
extern unsigned int lbl_806D2D74;
extern unsigned int lbl_806D2D78;
extern unsigned char lbl_806D2D80[5];

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80310478[];
extern unsigned int lbl_803FCF24[];
extern unsigned int lbl_803FD014[];

/* --- function index (1 fns, .text 0x80069AB0..0x8006A160) ---
 * [  0] 0x80069AB0 size:0x6B0   global NetDiag_PacketRatioPage
 */

/* --- forward decls --- */
asm void NetDiag_PacketRatioPage(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NetDiag_PacketRatioPage[8] = {
    0x22, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NetDiag_PacketRatioPage = {
    (void *)&NetDiag_PacketRatioPage, 0x000006B0, (void *)extab_NetDiag_PacketRatioPage
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NetDiag_PacketRatioPage(void) { /* 0x80069AB0 size:0x6B0 */
    nofralloc
    stwu r1, -0x160(r1)
    mflr r0
    stw r0, 0x164(r1)
    stfd f31, 0x150(r1)
    psq_st f31, 0x158(r1), 0, 0
    stfd f30, 0x140(r1)
    psq_st f30, 0x148(r1), 0, 0
    stfd f29, 0x130(r1)
    psq_st f29, 0x138(r1), 0, 0
    stfd f28, 0x120(r1)
    psq_st f28, 0x128(r1), 0, 0
    stfd f27, 0x110(r1)
    psq_st f27, 0x118(r1), 0, 0
    stfd f26, 0x100(r1)
    psq_st f26, 0x108(r1), 0, 0
    stfd f25, 0xf0(r1)
    psq_st f25, 0xf8(r1), 0, 0
    stfd f24, 0xe0(r1)
    psq_st f24, 0xe8(r1), 0, 0
    stfd f23, 0xd0(r1)
    psq_st f23, 0xd8(r1), 0, 0
    stfd f22, 0xc0(r1)
    psq_st f22, 0xc8(r1), 0, 0
    stw r31, 0xbc(r1)
    stw r30, 0xb8(r1)
    stw r29, 0xb4(r1)
    stw r28, 0xb0(r1)
    mr. r29, r4
    mr r31, r3
    bne NetDiag_PacketRatioPage_L_80069B30
    li r0, 0x0
    stw r0, 0x18(r31)
    NetDiag_PacketRatioPage_L_80069B30:
    cmpwi r29, 0x1
    bne NetDiag_PacketRatioPage_L_80069BD8
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
    beq NetDiag_PacketRatioPage_L_80069B88
    li r0, 0x1f
    stw r0, 0x8(r31)
    lwz r3, 0x18(r31)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x18(r31)
    ble NetDiag_PacketRatioPage_L_80069B88
    li r0, 0x0
    stw r0, 0x18(r31)
    NetDiag_PacketRatioPage_L_80069B88:
    mr r3, r28
    li r4, 0x1000
    lwz r12, 0x0(r28)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq NetDiag_PacketRatioPage_L_80069BD8
    lwz r0, 0x18(r31)
    cmpwi r0, 0x0
    bne NetDiag_PacketRatioPage_L_80069BD0
    li r0, 0x1b
    mr r3, r31
    stw r0, 0x10(r31)
    li r4, 0x0
    li r5, -0x1
    bl Stats_Display_UI
    b NetDiag_PacketRatioPage_L_80069BD8
    NetDiag_PacketRatioPage_L_80069BD0:
    li r0, 0x0
    stw r0, 0x10(r31)
    NetDiag_PacketRatioPage_L_80069BD8:
    cmpwi r29, 0x2
    bne NetDiag_PacketRatioPage_L_8006A0EC
    lwz r11, 0x274(r31)
    lis r9, 0x4330
    stw r9, 0x8(r1)
    lwz r12, 0x27c(r11)
    lwz r10, 0x28c(r11)
    lwz r8, 0x294(r11)
    lwz r7, 0x2a0(r11)
    lwz r6, 0x2a4(r11)
    lwz r5, 0x2a8(r11)
    lwz r4, 0x2ac(r11)
    lwz r3, 0x2b0(r11)
    lwz r0, 0x2b4(r11)
    stw r10, 0xc(r1)
    lfd f0, lbl_806D2D78(r2)
    lfd f1, 0x8(r1)
    stw r12, 0x14(r1)
    fsubs f2, f1, f0
    stw r9, 0x10(r1)
    lfd f1, 0x10(r1)
    stw r8, 0x1c(r1)
    fsubs f1, f1, f0
    stw r9, 0x18(r1)
    lfd f3, 0x18(r1)
    fdivs f31, f2, f1
    stw r12, 0x24(r1)
    stw r9, 0x20(r1)
    lfd f2, 0x20(r1)
    stw r7, 0x2c(r1)
    stw r9, 0x28(r1)
    lfd f1, 0x28(r1)
    fsubs f3, f3, f0
    fsubs f2, f2, f0
    stw r12, 0x34(r1)
    fsubs f4, f1, f0
    stw r9, 0x30(r1)
    fdivs f30, f3, f2
    lfd f2, 0x30(r1)
    stw r6, 0x3c(r1)
    stw r9, 0x38(r1)
    lfd f1, 0x38(r1)
    stw r12, 0x44(r1)
    stw r9, 0x40(r1)
    fsubs f2, f2, f0
    fsubs f5, f1, f0
    lfd f3, 0x40(r1)
    stw r5, 0x4c(r1)
    fdivs f29, f4, f2
    stw r9, 0x48(r1)
    lfd f2, 0x48(r1)
    stw r12, 0x54(r1)
    stw r9, 0x50(r1)
    lfd f1, 0x50(r1)
    fsubs f3, f3, f0
    stw r4, 0x5c(r1)
    fsubs f7, f2, f0
    stw r9, 0x58(r1)
    fsubs f4, f1, f0
    fdivs f28, f5, f3
    lfd f2, 0x58(r1)
    stw r12, 0x64(r1)
    stw r9, 0x60(r1)
    lfd f1, 0x60(r1)
    stw r3, 0x6c(r1)
    stw r9, 0x68(r1)
    fsubs f6, f2, f0
    fsubs f5, f1, f0
    lfd f3, 0x68(r1)
    fdivs f27, f7, f4
    stw r12, 0x74(r1)
    stw r9, 0x70(r1)
    lfd f2, 0x70(r1)
    stw r0, 0x7c(r1)
    stw r9, 0x78(r1)
    lfd f1, 0x78(r1)
    fsubs f4, f3, f0
    fsubs f3, f2, f0
    stw r12, 0x84(r1)
    fsubs f2, f1, f0
    stw r9, 0x80(r1)
    fdivs f26, f6, f5
    lfd f1, 0x80(r1)
    fsubs f1, f1, f0
    fdivs f25, f4, f3
    fdivs f24, f2, f1
    lwz r3, 0x2b8(r11)
    cmplwi r12, 0x0
    lwz r0, 0x2bc(r11)
    stw r3, 0x8c(r1)
    stw r9, 0x88(r1)
    lfd f1, 0x88(r1)
    stw r12, 0x94(r1)
    fsubs f3, f1, f0
    stw r9, 0x90(r1)
    lfd f1, 0x90(r1)
    stw r0, 0x9c(r1)
    fsubs f1, f1, f0
    stw r9, 0x98(r1)
    lfd f2, 0x98(r1)
    fdivs f23, f3, f1
    stw r12, 0xa4(r1)
    stw r9, 0xa0(r1)
    lfd f1, 0xa0(r1)
    fsubs f2, f2, f0
    fsubs f0, f1, f0
    fdivs f22, f2, f0
    bne NetDiag_PacketRatioPage_L_80069DB0
    lfs f27, lbl_806D2D70(r2)
    fmr f28, f27
    fmr f29, f27
    fmr f24, f27
    fmr f25, f27
    fmr f26, f27
    fmr f22, f27
    fmr f23, f27
    fmr f30, f27
    fmr f31, f27
    NetDiag_PacketRatioPage_L_80069DB0:
    lwz r0, 0x34(r31)
    cmpwi r0, 0x2
    beq NetDiag_PacketRatioPage_L_80069F00
    lwz r4, 0x18(r31)
    lis r3, lbl_803FCF24@ha
    addi r28, r3, lbl_803FCF24@l
    li r30, 0x0
    addi r29, r4, 0xf
    b NetDiag_PacketRatioPage_L_80069E1C
    NetDiag_PacketRatioPage_L_80069DD4:
    cmpw r30, r29
    bne NetDiag_PacketRatioPage_L_80069DE8
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_PacketRatioPage_L_80069E14
    NetDiag_PacketRatioPage_L_80069DE8:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_PacketRatioPage_L_80069E14
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_PacketRatioPage_L_80069E14:
    addi r28, r28, 0xc
    addi r30, r30, 0x1
    NetDiag_PacketRatioPage_L_80069E1C:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_PacketRatioPage_L_80069DD4
    lwz r7, 0x274(r31)
    li r4, 0x1a4
    lwz r3, 0x270(r31)
    li r5, 0x30
    lfs f1, lbl_806D2D44(r2)
    li r6, 0x7
    lwz r8, 0x28c(r7)
    la r7, lbl_806D2D80(r2)
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310478@ha
    addi r7, r3, lbl_80310478@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f31
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x1a4
    li r5, 0x48
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r7, 0x274(r31)
    li r4, 0x1a4
    lwz r3, 0x270(r31)
    li r5, 0x60
    lfs f1, lbl_806D2D44(r2)
    li r6, 0x7
    lwz r8, 0x294(r7)
    la r7, lbl_806D2D80(r2)
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310478@ha
    addi r7, r3, lbl_80310478@l
    lwz r3, 0x270(r31)
    fmuls f2, f0, f30
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x1a4
    li r5, 0x78
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r7, 0x274(r31)
    li r4, 0x1a4
    lwz r3, 0x270(r31)
    li r5, 0x90
    lfs f1, lbl_806D2D44(r2)
    li r6, 0x7
    lwz r8, 0x29c(r7)
    la r7, lbl_806D2D80(r2)
    creqv 6, 6, 6
    bl DrawText
    li r30, 0x8
    b NetDiag_PacketRatioPage_L_80069F70
    NetDiag_PacketRatioPage_L_80069F00:
    lwz r4, 0x18(r31)
    lis r3, lbl_803FD014@ha
    addi r28, r3, lbl_803FD014@l
    li r29, 0x0
    addi r30, r4, 0xa
    b NetDiag_PacketRatioPage_L_80069F60
    NetDiag_PacketRatioPage_L_80069F18:
    cmpw r29, r30
    bne NetDiag_PacketRatioPage_L_80069F2C
    lwz r0, 0x8(r31)
    cmpwi r0, 0x1e
    bgt NetDiag_PacketRatioPage_L_80069F58
    NetDiag_PacketRatioPage_L_80069F2C:
    lwz r3, 0x270(r31)
    cmplwi r3, 0x0
    beq NetDiag_PacketRatioPage_L_80069F58
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_PacketRatioPage_L_80069F58:
    addi r28, r28, 0xc
    addi r29, r29, 0x1
    NetDiag_PacketRatioPage_L_80069F60:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne NetDiag_PacketRatioPage_L_80069F18
    li r30, 0x3
    NetDiag_PacketRatioPage_L_80069F70:
    lfs f0, lbl_806D2D74(r2)
    lis r3, lbl_80310478@ha
    addi r7, r3, lbl_80310478@l
    lwz r3, 0x270(r31)
    mulli r5, r30, 0x18
    fmuls f2, f0, f29
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x1
    lis r4, lbl_80310478@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f28
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_80310478@l
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x2
    lis r4, lbl_80310478@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f27
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_80310478@l
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x3
    lis r4, lbl_80310478@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f26
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_80310478@l
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x4
    lis r4, lbl_80310478@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f25
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_80310478@l
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x5
    lis r4, lbl_80310478@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f24
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_80310478@l
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x6
    lis r4, lbl_80310478@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f23
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_80310478@l
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f0, lbl_806D2D74(r2)
    addi r0, r30, 0x7
    lis r4, lbl_80310478@ha
    lwz r3, 0x270(r31)
    mulli r5, r0, 0x18
    fmuls f2, f0, f22
    lfs f1, lbl_806D2D44(r2)
    addi r7, r4, lbl_80310478@l
    li r4, 0x1a4
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    NetDiag_PacketRatioPage_L_8006A0EC:
    li r3, 0x1
    psq_l f31, 0x158(r1), 0, 0
    lfd f31, 0x150(r1)
    psq_l f30, 0x148(r1), 0, 0
    lfd f30, 0x140(r1)
    psq_l f29, 0x138(r1), 0, 0
    lfd f29, 0x130(r1)
    psq_l f28, 0x128(r1), 0, 0
    lfd f28, 0x120(r1)
    psq_l f27, 0x118(r1), 0, 0
    lfd f27, 0x110(r1)
    psq_l f26, 0x108(r1), 0, 0
    lfd f26, 0x100(r1)
    psq_l f25, 0xf8(r1), 0, 0
    lfd f25, 0xf0(r1)
    psq_l f24, 0xe8(r1), 0, 0
    lfd f24, 0xe0(r1)
    psq_l f23, 0xd8(r1), 0, 0
    lfd f23, 0xd0(r1)
    psq_l f22, 0xc8(r1), 0, 0
    lfd f22, 0xc0(r1)
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    lwz r29, 0xb4(r1)
    lwz r0, 0x164(r1)
    lwz r28, 0xb0(r1)
    mtlr r0
    addi r1, r1, 0x160
    blr
}
