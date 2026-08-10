/* === extracted from auto_CardRW_HardwareInit_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CardPrintJob_KickFontTransfer();
extern void CardPrintJob_TickFontTransfer();
extern void CardRW_ErrorDisplay();
extern void CardRW_TestTopMenu_Page();
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void Sci2Card_GetResponseStatus();
extern void Sci2Card_IsIdleOrExhausted();
extern void Sci2Card_IsRetryExhausted();
extern void Sci2Card_IsStatus2A();
extern void Sci2Card_IsStatus2Five();
extern void Sci2Card_IsStatus2Three();
extern void Sci2Card_IsStatus2Two();
extern void Sci2Card_IsStatus3Five();
extern void Sci2Card_IsStatusOkNonTerm();
extern void Sci2Card_SendCmdRetry();
extern void Sci2Card_Singleton_Get();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;
extern char lbl_806D2DB4[5];

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FCD2C[];

/* --- function index (1 fns, .text 0x8006BB04..0x8006C0F4) ---
 * [  0] 0x8006BB04 size:0x5F0   global CardRW_HardwareInit_Page
 */

/* --- forward decls --- */
asm void CardRW_HardwareInit_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_HardwareInit_Page[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_HardwareInit_Page = {
    (void *)&CardRW_HardwareInit_Page, 0x000005F0, (void *)extab_CardRW_HardwareInit_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_HardwareInit_Page(void) { /* 0x8006BB04 size:0x5F0 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r30, r4
    lis r4, lbl_8030E598@ha
    mr r29, r3
    addi r31, r4, lbl_8030E598@l
    bne CardRW_HardwareInit_Page_L_8006BB40
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x1c(r29)
    stw r0, 0x2c(r29)
    stw r0, 0x30(r29)
    stw r0, 0x27c(r29)
    CardRW_HardwareInit_Page_L_8006BB40:
    cmpwi r30, 0x1
    bne CardRW_HardwareInit_Page_L_8006BE04
    lwz r3, 0x2c(r29)
    cmpwi r3, 0x0
    bne CardRW_HardwareInit_Page_L_8006BC08
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r27, r3
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_HardwareInit_Page_L_8006BBA4
    li r0, 0x1f
    stw r0, 0x8(r29)
    lwz r3, 0x1c(r29)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x1c(r29)
    ble CardRW_HardwareInit_Page_L_8006BBA4
    li r0, 0x0
    stw r0, 0x1c(r29)
    CardRW_HardwareInit_Page_L_8006BBA4:
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_HardwareInit_Page_L_8006BE04
    lwz r0, 0x1c(r29)
    cmpwi r0, 0x0
    bne CardRW_HardwareInit_Page_L_8006BBEC
    li r0, 0x64
    li r3, 0x1
    stw r0, 0x1c(r29)
    li r0, 0x0
    stw r3, 0x2c(r29)
    stw r0, 0x8(r29)
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BBEC:
    li r0, 0x5
    mr r3, r29
    stw r0, 0x10(r29)
    li r4, 0x0
    li r5, 0x8
    bl CardRW_TestTopMenu_Page
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BC08:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x0
    beq CardRW_HardwareInit_Page_L_8006BC58
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x1000
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_HardwareInit_Page_L_8006BE04
    li r0, 0x5
    mr r3, r29
    stw r0, 0x10(r29)
    li r4, 0x0
    li r5, 0x8
    bl CardRW_TestTopMenu_Page
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BC58:
    cmpwi r3, 0x1
    bne CardRW_HardwareInit_Page_L_8006BC7C
    bl Sci2Card_Singleton_Get
    li r4, 0x1
    bl Sci2Card_SendCmdRetry
    lwz r3, 0x2c(r29)
    addi r0, r3, 0x1
    stw r0, 0x2c(r29)
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BC7C:
    cmpwi r3, 0x2
    bne CardRW_HardwareInit_Page_L_8006BD8C
    bl Sci2Card_Singleton_Get
    mr r27, r3
    bl Sci2Card_IsIdleOrExhausted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BE04
    mr r3, r27
    bl Sci2Card_IsStatusOkNonTerm
    clrlwi. r0, r3, 24
    beq CardRW_HardwareInit_Page_L_8006BCBC
    lwz r3, 0x2c(r29)
    addi r0, r3, 0x1
    stw r0, 0x2c(r29)
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BCBC:
    mr r3, r27
    bl Sci2Card_IsRetryExhausted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BCDC
    li r0, 0x1
    stw r0, 0x30(r29)
    b CardRW_HardwareInit_Page_L_8006BD78
    CardRW_HardwareInit_Page_L_8006BCDC:
    mr r3, r27
    bl Sci2Card_IsStatus2Two
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BCFC
    li r0, 0x2
    stw r0, 0x30(r29)
    b CardRW_HardwareInit_Page_L_8006BD78
    CardRW_HardwareInit_Page_L_8006BCFC:
    mr r3, r27
    bl Sci2Card_IsStatus2Three
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BD1C
    li r0, 0x3
    stw r0, 0x30(r29)
    b CardRW_HardwareInit_Page_L_8006BD78
    CardRW_HardwareInit_Page_L_8006BD1C:
    mr r3, r27
    bl Sci2Card_IsStatus2Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BD3C
    li r0, 0x4
    stw r0, 0x30(r29)
    b CardRW_HardwareInit_Page_L_8006BD78
    CardRW_HardwareInit_Page_L_8006BD3C:
    mr r3, r27
    bl Sci2Card_IsStatus2A
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BD5C
    li r0, 0x5
    stw r0, 0x30(r29)
    b CardRW_HardwareInit_Page_L_8006BD78
    CardRW_HardwareInit_Page_L_8006BD5C:
    mr r3, r27
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BD78
    li r0, 0x6
    stw r0, 0x30(r29)
    CardRW_HardwareInit_Page_L_8006BD78:
    li r3, 0x5
    li r0, 0x1
    stw r3, 0x2c(r29)
    stw r0, 0x1c(r29)
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BD8C:
    cmpwi r3, 0x3
    bne CardRW_HardwareInit_Page_L_8006BDB4
    bl CardPrintJob_KickFontTransfer
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BE04
    lwz r3, 0x2c(r29)
    addi r0, r3, 0x1
    stw r0, 0x2c(r29)
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BDB4:
    cmpwi r3, 0x4
    bne CardRW_HardwareInit_Page_L_8006BDDC
    bl CardPrintJob_TickFontTransfer
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BE04
    lwz r3, 0x2c(r29)
    addi r0, r3, 0x1
    stw r0, 0x2c(r29)
    b CardRW_HardwareInit_Page_L_8006BE04
    CardRW_HardwareInit_Page_L_8006BDDC:
    addi r0, r3, 0x1
    cmpwi r0, 0x3f
    stw r0, 0x2c(r29)
    blt CardRW_HardwareInit_Page_L_8006BE04
    li r0, 0x5
    mr r3, r29
    stw r0, 0x10(r29)
    li r4, 0x0
    li r5, 0x8
    bl CardRW_TestTopMenu_Page
    CardRW_HardwareInit_Page_L_8006BE04:
    cmpwi r30, 0x2
    bne CardRW_HardwareInit_Page_L_8006C0DC
    lwz r4, 0x1c(r29)
    lis r3, lbl_803FCD2C@ha
    addi r27, r3, lbl_803FCD2C@l
    li r30, 0x0
    addi r28, r4, 0x3
    b CardRW_HardwareInit_Page_L_8006BE6C
    CardRW_HardwareInit_Page_L_8006BE24:
    cmpw r30, r28
    bne CardRW_HardwareInit_Page_L_8006BE38
    lwz r0, 0x8(r29)
    cmpwi r0, 0x1e
    bgt CardRW_HardwareInit_Page_L_8006BE64
    CardRW_HardwareInit_Page_L_8006BE38:
    lwz r3, 0x270(r29)
    cmplwi r3, 0x0
    beq CardRW_HardwareInit_Page_L_8006BE64
    lwz r4, 0x0(r27)
    li r6, 0x7
    lwz r0, 0x4(r27)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006BE64:
    addi r27, r27, 0xc
    addi r30, r30, 0x1
    CardRW_HardwareInit_Page_L_8006BE6C:
    lwz r7, 0x8(r27)
    cmplwi r7, 0x0
    bne CardRW_HardwareInit_Page_L_8006BE24
    lwz r0, 0x270(r29)
    cmplwi r0, 0x0
    beq CardRW_HardwareInit_Page_L_8006BEC4
    bl Sci2Card_Singleton_Get
    addi r4, r1, 0x8
    addi r5, r1, 0x9
    addi r6, r1, 0xa
    bl Sci2Card_GetResponseStatus
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1c78
    lfs f1, lbl_806D2D44(r2)
    li r4, 0xa8
    lbz r8, 0x8(r1)
    li r5, 0x48
    lbz r9, 0x9(r1)
    li r6, 0x7
    lbz r10, 0xa(r1)
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006BEC4:
    mr r3, r29
    li r4, 0x1
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    bne CardRW_HardwareInit_Page_L_8006C0DC
    lwz r3, 0x270(r29)
    cmplwi r3, 0x0
    beq CardRW_HardwareInit_Page_L_8006C0DC
    lwz r4, 0x2c(r29)
    cmpwi r4, 0x1
    beq CardRW_HardwareInit_Page_L_8006BF0C
    subi r0, r4, 0x2
    cmplwi r0, 0x1
    ble CardRW_HardwareInit_Page_L_8006BF0C
    cmpwi r4, 0x4
    bne CardRW_HardwareInit_Page_L_8006BF58
    CardRW_HardwareInit_Page_L_8006BF0C:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x20bc
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r29)
    cmpwi r0, 0x1e
    bgt CardRW_HardwareInit_Page_L_8006C0DC
    lwz r3, 0x270(r29)
    addi r7, r31, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_HardwareInit_Page_L_8006C0DC
    CardRW_HardwareInit_Page_L_8006BF58:
    cmpwi r4, 0x5
    blt CardRW_HardwareInit_Page_L_8006C0DC
    lwz r8, 0x30(r29)
    cmpwi r8, 0x0
    bne CardRW_HardwareInit_Page_L_8006BF8C
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x20d0
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_HardwareInit_Page_L_8006C0DC
    CardRW_HardwareInit_Page_L_8006BF8C:
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xa8
    li r6, 0x7
    la r7, lbl_806D2DB4(r2)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x30(r29)
    cmpwi r0, 0x1
    bne CardRW_HardwareInit_Page_L_8006BFD4
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1b6c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006BFD4:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x2
    bne CardRW_HardwareInit_Page_L_8006C000
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1b9c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006C000:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x3
    bne CardRW_HardwareInit_Page_L_8006C02C
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1bb8
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006C02C:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x4
    bne CardRW_HardwareInit_Page_L_8006C058
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1bd0
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006C058:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x5
    bne CardRW_HardwareInit_Page_L_8006C084
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1be8
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006C084:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x6
    bne CardRW_HardwareInit_Page_L_8006C0B0
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1c00
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006C0B0:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x1e
    bgt CardRW_HardwareInit_Page_L_8006C0DC
    lwz r3, 0x270(r29)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_HardwareInit_Page_L_8006C0DC:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

