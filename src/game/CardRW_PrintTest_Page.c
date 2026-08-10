/* === extracted from auto_CardRW_PrintTest_Pag_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CardRW_ErrorDisplay();
extern void CardRW_TestTopMenu_Page();
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void Sci2Card_GetPrintErrorCode();
extern void Sci2Card_GetResponseStatus();
extern void Sci2Card_IsRetryExhausted();
extern void Sci2Card_IsStatus2A();
extern void Sci2Card_IsStatus2Five();
extern void Sci2Card_IsStatus2Three();
extern void Sci2Card_IsStatus2Two();
extern void Sci2Card_IsStatus3Five();
extern void Sci2Card_Singleton_Get();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FCB40[];
extern unsigned int lbl_803FDC18[];

/* --- function index (1 fns, .text 0x8006E308..0x8006E7D0) ---
 * [  0] 0x8006E308 size:0x4C8   global CardRW_PrintTest_Page
 */

/* --- forward decls --- */
asm void CardRW_PrintTest_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_PrintTest_Page[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_PrintTest_Page = {
    (void *)&CardRW_PrintTest_Page, 0x000004C8, (void *)extab_CardRW_PrintTest_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_PrintTest_Page(void) { /* 0x8006E308 size:0x4C8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r29, r4
    lis r4, lbl_8030E598@ha
    mr r28, r3
    addi r31, r4, lbl_8030E598@l
    bne CardRW_PrintTest_Page_L_8006E344
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x1c(r28)
    stw r0, 0x2c(r28)
    stw r0, 0x27c(r28)
    stw r3, 0x284(r28)
    CardRW_PrintTest_Page_L_8006E344:
    cmpwi r29, 0x1
    bne CardRW_PrintTest_Page_L_8006E5A4
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x0
    bne CardRW_PrintTest_Page_L_8006E504
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r0, 0x284(r28)
    mr r27, r3
    cmpwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E3B4
    lwz r12, 0x0(r3)
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_PrintTest_Page_L_8006E3B4
    li r0, 0x1f
    stw r0, 0x8(r28)
    lwz r3, 0x1c(r28)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x1c(r28)
    ble CardRW_PrintTest_Page_L_8006E3B4
    li r0, 0x0
    stw r0, 0x1c(r28)
    CardRW_PrintTest_Page_L_8006E3B4:
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_PrintTest_Page_L_8006E5A4
    lwz r0, 0x1c(r28)
    cmpwi r0, 0x0
    bne CardRW_PrintTest_Page_L_8006E4E8
    li r0, 0x64
    lis r3, lbl_803FDC18@ha
    stw r0, 0x1c(r28)
    li r30, 0x1
    li r0, 0x0
    addi r3, r3, lbl_803FDC18@l
    stw r30, 0x2c(r28)
    stw r0, 0x8(r28)
    lwz r0, 0x2c(r28)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r28)
    stw r30, 0x284(r28)
    bl Sci2Card_Singleton_Get
    mr r27, r3
    bl Sci2Card_IsRetryExhausted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E434
    li r30, 0x65
    b CardRW_PrintTest_Page_L_8006E4BC
    CardRW_PrintTest_Page_L_8006E434:
    mr r3, r27
    bl Sci2Card_IsStatus2Two
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E450
    li r30, 0x66
    b CardRW_PrintTest_Page_L_8006E4BC
    CardRW_PrintTest_Page_L_8006E450:
    mr r3, r27
    bl Sci2Card_IsStatus2Three
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E46C
    li r30, 0x68
    b CardRW_PrintTest_Page_L_8006E4BC
    CardRW_PrintTest_Page_L_8006E46C:
    mr r3, r27
    bl Sci2Card_IsStatus2Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E488
    li r30, 0x69
    b CardRW_PrintTest_Page_L_8006E4BC
    CardRW_PrintTest_Page_L_8006E488:
    mr r3, r27
    bl Sci2Card_IsStatus2A
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E4A4
    li r30, 0x6a
    b CardRW_PrintTest_Page_L_8006E4BC
    CardRW_PrintTest_Page_L_8006E4A4:
    mr r3, r27
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E4BC
    li r30, 0x2
    CardRW_PrintTest_Page_L_8006E4BC:
    stw r30, 0x284(r28)
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    beq CardRW_PrintTest_Page_L_8006E5A4
    li r0, 0x1
    li r3, 0x1f
    stb r0, 0x5b(r28)
    li r0, 0x0
    stw r3, 0x8(r28)
    stw r0, 0x2c(r28)
    b CardRW_PrintTest_Page_L_8006E5A4
    CardRW_PrintTest_Page_L_8006E4E8:
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x3
    bl CardRW_TestTopMenu_Page
    b CardRW_PrintTest_Page_L_8006E5A4
    CardRW_PrintTest_Page_L_8006E504:
    lwz r12, 0x27c(r28)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_PrintTest_Page_L_8006E5A4
    lwz r0, 0x2c(r28)
    lis r3, lbl_803FDC18@ha
    addi r3, r3, lbl_803FDC18@l
    slwi r0, r0, 3
    add r3, r3, r0
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq CardRW_PrintTest_Page_L_8006E544
    bl Sci2Card_GetPrintErrorCode
    stw r3, 0x284(r28)
    CardRW_PrintTest_Page_L_8006E544:
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    beq CardRW_PrintTest_Page_L_8006E55C
    li r0, 0x0
    stw r0, 0x2c(r28)
    b CardRW_PrintTest_Page_L_8006E5A4
    CardRW_PrintTest_Page_L_8006E55C:
    lwz r4, 0x2c(r28)
    lis r3, lbl_803FDC18@ha
    addi r3, r3, lbl_803FDC18@l
    addi r0, r4, 0x1
    stw r0, 0x2c(r28)
    lwz r0, 0x2c(r28)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r28)
    lwz r0, 0x27c(r28)
    cmplwi r0, 0x0
    bne CardRW_PrintTest_Page_L_8006E5A4
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x3
    bl CardRW_TestTopMenu_Page
    CardRW_PrintTest_Page_L_8006E5A4:
    cmpwi r29, 0x2
    bne CardRW_PrintTest_Page_L_8006E7B8
    lwz r4, 0x1c(r28)
    lis r3, lbl_803FCB40@ha
    addi r30, r3, lbl_803FCB40@l
    li r27, 0x0
    addi r29, r4, 0x3
    b CardRW_PrintTest_Page_L_8006E60C
    CardRW_PrintTest_Page_L_8006E5C4:
    cmpw r27, r29
    bne CardRW_PrintTest_Page_L_8006E5D8
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_PrintTest_Page_L_8006E604
    CardRW_PrintTest_Page_L_8006E5D8:
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_PrintTest_Page_L_8006E604
    lwz r4, 0x0(r30)
    li r6, 0x7
    lwz r0, 0x4(r30)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_PrintTest_Page_L_8006E604:
    addi r30, r30, 0xc
    addi r27, r27, 0x1
    CardRW_PrintTest_Page_L_8006E60C:
    lwz r7, 0x8(r30)
    cmplwi r7, 0x0
    bne CardRW_PrintTest_Page_L_8006E5C4
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    beq CardRW_PrintTest_Page_L_8006E664
    bl Sci2Card_Singleton_Get
    addi r4, r1, 0x8
    addi r5, r1, 0x9
    addi r6, r1, 0xa
    bl Sci2Card_GetResponseStatus
    lwz r3, 0x270(r28)
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
    CardRW_PrintTest_Page_L_8006E664:
    mr r3, r28
    li r4, 0x1
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    bne CardRW_PrintTest_Page_L_8006E7B8
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_PrintTest_Page_L_8006E7B8
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x5
    bge CardRW_PrintTest_Page_L_8006E6AC
    cmpwi r0, 0x3
    bge CardRW_PrintTest_Page_L_8006E704
    cmpwi r0, 0x1
    bge CardRW_PrintTest_Page_L_8006E6B8
    b CardRW_PrintTest_Page_L_8006E7B8
    CardRW_PrintTest_Page_L_8006E6AC:
    cmpwi r0, 0x7
    bge CardRW_PrintTest_Page_L_8006E7B8
    b CardRW_PrintTest_Page_L_8006E750
    CardRW_PrintTest_Page_L_8006E6B8:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2314
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_PrintTest_Page_L_8006E7B8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2334
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_PrintTest_Page_L_8006E7B8
    CardRW_PrintTest_Page_L_8006E704:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2104
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_PrintTest_Page_L_8006E7B8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_PrintTest_Page_L_8006E7B8
    CardRW_PrintTest_Page_L_8006E750:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2348
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_PrintTest_Page_L_8006E798
    lwz r3, 0x270(r28)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_PrintTest_Page_L_8006E798:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x212c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x120
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_PrintTest_Page_L_8006E7B8:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


