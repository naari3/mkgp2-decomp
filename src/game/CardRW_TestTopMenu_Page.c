/* === extracted from auto_CardRW_TestTopMenu_P_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CardPrintJob_KickFontTransfer();
extern void CardPrintJob_TickFontTransfer();
extern void CardRW_ErrorDisplay();
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void Sci2Card_BeginSpace();
extern void Sci2Card_GetByteFlag1224();
extern void Sci2Card_GetPrintErrorCode();
extern void Sci2Card_WaitPingStatus();
extern void UI_PageDispatcher();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1108;
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80310118[];
extern unsigned int lbl_80310A0C[];
extern unsigned int lbl_803FC8B8[];
extern unsigned int lbl_803FDB18[];

/* --- function index (1 fns, .text 0x8006F608..0x8006FA1C) ---
 * [  0] 0x8006F608 size:0x414   global CardRW_TestTopMenu_Page
 */

/* --- forward decls --- */
asm void CardRW_TestTopMenu_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_TestTopMenu_Page[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_TestTopMenu_Page = {
    (void *)&CardRW_TestTopMenu_Page, 0x00000414, (void *)extab_CardRW_TestTopMenu_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_TestTopMenu_Page(void) { /* 0x8006F608 size:0x414 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr. r31, r4
    stw r30, 0x18(r1)
    mr r30, r3
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    bne CardRW_TestTopMenu_Page_L_8006F668
    li r0, 0x0
    cmpwi r5, -0x1
    stw r0, 0x27c(r30)
    li r0, 0x1
    stw r0, 0x284(r30)
    bne CardRW_TestTopMenu_Page_L_8006F654
    li r0, 0x9
    stw r0, 0x18(r30)
    b CardRW_TestTopMenu_Page_L_8006F658
    CardRW_TestTopMenu_Page_L_8006F654:
    stw r5, 0x18(r30)
    CardRW_TestTopMenu_Page_L_8006F658:
    lwz r0, lbl_806D1108(r13)
    cmpwi r0, 0x0
    bne CardRW_TestTopMenu_Page_L_8006F668
    bl CardPrintJob_KickFontTransfer
    CardRW_TestTopMenu_Page_L_8006F668:
    cmpwi r31, 0x1
    bne CardRW_TestTopMenu_Page_L_8006F8E0
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r0, 0x284(r30)
    mr r28, r3
    cmpwi r0, 0x1
    beq CardRW_TestTopMenu_Page_L_8006F6B8
    lwz r12, 0x0(r3)
    li r4, 0x1000
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_TestTopMenu_Page_L_8006F6B0
    li r0, 0x0
    stw r0, 0x10(r30)
    CardRW_TestTopMenu_Page_L_8006F6B0:
    li r3, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F6B8:
    lwz r0, lbl_806D1108(r13)
    cmpwi r0, 0x0
    bne CardRW_TestTopMenu_Page_L_8006F744
    bl CardPrintJob_TickFontTransfer
    clrlwi. r0, r3, 24
    bne CardRW_TestTopMenu_Page_L_8006F6D8
    li r3, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F6D8:
    bl Sci2Card_GetPrintErrorCode
    stw r3, 0x284(r30)
    lwz r0, 0x284(r30)
    cmpwi r0, 0x1
    beq CardRW_TestTopMenu_Page_L_8006F6F8
    li r0, -0x2
    stw r0, 0x38(r30)
    b CardRW_TestTopMenu_Page_L_8006F724
    CardRW_TestTopMenu_Page_L_8006F6F8:
    lwz r0, 0x38(r30)
    cmpwi r0, -0x2
    bne CardRW_TestTopMenu_Page_L_8006F724
    bl Sci2Card_BeginSpace
    clrlwi. r0, r3, 24
    bne CardRW_TestTopMenu_Page_L_8006F71C
    li r0, -0x1
    stw r0, 0x38(r30)
    b CardRW_TestTopMenu_Page_L_8006F724
    CardRW_TestTopMenu_Page_L_8006F71C:
    li r0, 0x0
    stw r0, 0x38(r30)
    CardRW_TestTopMenu_Page_L_8006F724:
    lwz r0, 0x284(r30)
    cmpwi r0, 0x65
    beq CardRW_TestTopMenu_Page_L_8006F73C
    li r0, 0x1
    stw r0, lbl_806D1108(r13)
    stw r0, 0x284(r30)
    CardRW_TestTopMenu_Page_L_8006F73C:
    li r3, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F744:
    lwz r0, 0x38(r30)
    cmpwi r0, -0x1
    bne CardRW_TestTopMenu_Page_L_8006F770
    bl Sci2Card_BeginSpace
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_TestTopMenu_Page_L_8006F768
    li r0, 0x0
    stw r0, 0x38(r30)
    CardRW_TestTopMenu_Page_L_8006F768:
    li r3, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F770:
    cmpwi r0, 0x0
    bne CardRW_TestTopMenu_Page_L_8006F7E8
    bl Sci2Card_WaitPingStatus
    clrlwi. r0, r3, 24
    bne CardRW_TestTopMenu_Page_L_8006F78C
    li r3, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F78C:
    bl Sci2Card_GetPrintErrorCode
    cmpwi r3, 0x1
    beq CardRW_TestTopMenu_Page_L_8006F7A8
    li r0, -0x2
    li r3, 0x1
    stw r0, 0x38(r30)
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F7A8:
    bl Sci2Card_GetByteFlag1224
    clrlwi. r0, r3, 24
    bne CardRW_TestTopMenu_Page_L_8006F7C0
    li r0, -0x2
    stw r0, 0x38(r30)
    b CardRW_TestTopMenu_Page_L_8006F7E0
    CardRW_TestTopMenu_Page_L_8006F7C0:
    li r0, 0x5
    lis r3, lbl_803FDB18@ha
    stw r0, 0x38(r30)
    addi r3, r3, lbl_803FDB18@l
    lwz r0, 0x38(r30)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r30)
    CardRW_TestTopMenu_Page_L_8006F7E0:
    li r3, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F7E8:
    cmpwi r0, 0x1
    blt CardRW_TestTopMenu_Page_L_8006F848
    lwz r12, 0x27c(r30)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_TestTopMenu_Page_L_8006F840
    lwz r4, 0x38(r30)
    lis r3, lbl_803FDB18@ha
    addi r3, r3, lbl_803FDB18@l
    addi r0, r4, 0x1
    stw r0, 0x38(r30)
    lwz r0, 0x38(r30)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r30)
    lwz r0, 0x27c(r30)
    cmplwi r0, 0x0
    bne CardRW_TestTopMenu_Page_L_8006F840
    li r0, -0x2
    stw r0, 0x38(r30)
    CardRW_TestTopMenu_Page_L_8006F840:
    li r3, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9FC
    CardRW_TestTopMenu_Page_L_8006F848:
    lwz r12, 0x0(r3)
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_TestTopMenu_Page_L_8006F888
    li r0, 0x1f
    stw r0, 0x8(r30)
    lwz r3, 0x18(r30)
    addi r0, r3, 0x1
    cmpwi r0, 0x9
    stw r0, 0x18(r30)
    ble CardRW_TestTopMenu_Page_L_8006F888
    li r0, 0x0
    stw r0, 0x18(r30)
    CardRW_TestTopMenu_Page_L_8006F888:
    mr r3, r28
    li r4, 0x1000
    lwz r12, 0x0(r28)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_TestTopMenu_Page_L_8006F8E0
    lwz r0, 0x18(r30)
    cmpwi r0, 0x9
    bne CardRW_TestTopMenu_Page_L_8006F8C0
    li r0, 0x0
    stw r0, 0x10(r30)
    b CardRW_TestTopMenu_Page_L_8006F8E0
    CardRW_TestTopMenu_Page_L_8006F8C0:
    li r0, 0x0
    mr r3, r30
    stw r0, 0x2c(r30)
    li r4, 0x0
    lwz r5, 0x18(r30)
    addi r0, r5, 0xf
    stw r0, 0x10(r30)
    bl UI_PageDispatcher
    CardRW_TestTopMenu_Page_L_8006F8E0:
    cmpwi r31, 0x2
    bne CardRW_TestTopMenu_Page_L_8006F9F8
    lwz r0, 0x284(r30)
    cmpwi r0, 0x1
    beq CardRW_TestTopMenu_Page_L_8006F94C
    lwz r28, 0x8(r30)
    li r0, 0x1f
    mr r3, r30
    li r4, 0x1
    stw r0, 0x8(r30)
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    stw r28, 0x8(r30)
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_TestTopMenu_Page_L_8006F9F8
    lis r4, lbl_80310118@ha
    lwz r3, 0x270(r30)
    addi r7, r4, lbl_80310118@l
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_TestTopMenu_Page_L_8006F9F8
    CardRW_TestTopMenu_Page_L_8006F94C:
    lwz r0, lbl_806D1108(r13)
    cmpwi r0, 0x0
    bne CardRW_TestTopMenu_Page_L_8006F98C
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_TestTopMenu_Page_L_8006F9F8
    lis r4, lbl_80310A0C@ha
    lwz r3, 0x270(r30)
    addi r7, r4, lbl_80310A0C@l
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x9a
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_TestTopMenu_Page_L_8006F9F8
    CardRW_TestTopMenu_Page_L_8006F98C:
    lwz r4, 0x18(r30)
    lis r3, lbl_803FC8B8@ha
    addi r28, r3, lbl_803FC8B8@l
    li r31, 0x0
    addi r29, r4, 0x1
    b CardRW_TestTopMenu_Page_L_8006F9EC
    CardRW_TestTopMenu_Page_L_8006F9A4:
    cmpw r31, r29
    bne CardRW_TestTopMenu_Page_L_8006F9B8
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_TestTopMenu_Page_L_8006F9E4
    CardRW_TestTopMenu_Page_L_8006F9B8:
    lwz r3, 0x270(r30)
    cmplwi r3, 0x0
    beq CardRW_TestTopMenu_Page_L_8006F9E4
    lwz r4, 0x0(r28)
    li r6, 0x7
    lwz r0, 0x4(r28)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_TestTopMenu_Page_L_8006F9E4:
    addi r28, r28, 0xc
    addi r31, r31, 0x1
    CardRW_TestTopMenu_Page_L_8006F9EC:
    lwz r7, 0x8(r28)
    cmplwi r7, 0x0
    bne CardRW_TestTopMenu_Page_L_8006F9A4
    CardRW_TestTopMenu_Page_L_8006F9F8:
    li r3, 0x1
    CardRW_TestTopMenu_Page_L_8006F9FC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

