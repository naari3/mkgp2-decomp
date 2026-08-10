/* === extracted from auto_CardRW_CleaningTest_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Backup_PublishShadowCopy();
extern void Backup_PublishShadowCopy_Inline();
extern void CardRW_ErrorDisplay();
extern void CardRW_TestTopMenu_Page();
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void Sci2Card_GetPrintErrorCode();
extern void Sci2Card_GetResponseStatus();
extern void Sci2Card_Singleton_Get();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FCA20[];
extern unsigned int lbl_803FDB58[];

/* --- function index (1 fns, .text 0x8006F200..0x8006F608) ---
 * [  0] 0x8006F200 size:0x408   global CardRW_CleaningTest_Page
 */

/* --- forward decls --- */
asm void CardRW_CleaningTest_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_CleaningTest_Page[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_CleaningTest_Page = {
    (void *)&CardRW_CleaningTest_Page, 0x00000408, (void *)extab_CardRW_CleaningTest_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_CleaningTest_Page(void) { /* 0x8006F200 size:0x408 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r30, r4
    lis r4, lbl_8030E598@ha
    mr r29, r3
    addi r31, r4, lbl_8030E598@l
    bne CardRW_CleaningTest_Page_L_8006F23C
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x1c(r29)
    stw r0, 0x2c(r29)
    stw r0, 0x27c(r29)
    stw r3, 0x284(r29)
    CardRW_CleaningTest_Page_L_8006F23C:
    cmpwi r30, 0x1
    bne CardRW_CleaningTest_Page_L_8006F3FC
    lwz r0, 0x2c(r29)
    cmpwi r0, 0x0
    bne CardRW_CleaningTest_Page_L_8006F32C
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r0, 0x284(r29)
    mr r27, r3
    cmpwi r0, 0x1
    bne CardRW_CleaningTest_Page_L_8006F2AC
    lwz r12, 0x0(r3)
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_CleaningTest_Page_L_8006F2AC
    li r0, 0x1f
    stw r0, 0x8(r29)
    lwz r3, 0x1c(r29)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x1c(r29)
    ble CardRW_CleaningTest_Page_L_8006F2AC
    li r0, 0x0
    stw r0, 0x1c(r29)
    CardRW_CleaningTest_Page_L_8006F2AC:
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_CleaningTest_Page_L_8006F3FC
    lwz r0, 0x1c(r29)
    cmpwi r0, 0x0
    bne CardRW_CleaningTest_Page_L_8006F310
    li r0, 0x64
    lis r3, lbl_803FDB58@ha
    stw r0, 0x1c(r29)
    li r4, 0x1
    li r0, 0x0
    addi r3, r3, lbl_803FDB58@l
    stw r4, 0x2c(r29)
    stw r0, 0x8(r29)
    lwz r0, 0x2c(r29)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r29)
    stw r4, 0x284(r29)
    b CardRW_CleaningTest_Page_L_8006F3FC
    CardRW_CleaningTest_Page_L_8006F310:
    li r0, 0x5
    mr r3, r29
    stw r0, 0x10(r29)
    li r4, 0x0
    li r5, 0x0
    bl CardRW_TestTopMenu_Page
    b CardRW_CleaningTest_Page_L_8006F3FC
    CardRW_CleaningTest_Page_L_8006F32C:
    lwz r12, 0x27c(r29)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_CleaningTest_Page_L_8006F3FC
    lwz r0, 0x2c(r29)
    lis r3, lbl_803FDB58@ha
    addi r3, r3, lbl_803FDB58@l
    slwi r0, r0, 3
    add r3, r3, r0
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq CardRW_CleaningTest_Page_L_8006F36C
    bl Sci2Card_GetPrintErrorCode
    stw r3, 0x284(r29)
    CardRW_CleaningTest_Page_L_8006F36C:
    lwz r0, 0x2c(r29)
    cmpwi r0, 0x2
    bne CardRW_CleaningTest_Page_L_8006F394
    lwz r0, 0x284(r29)
    cmpwi r0, 0x6
    bne CardRW_CleaningTest_Page_L_8006F394
    li r3, 0x0
    li r0, 0x1
    stw r3, 0x2c(r29)
    stw r0, 0x284(r29)
    CardRW_CleaningTest_Page_L_8006F394:
    lwz r0, 0x284(r29)
    cmpwi r0, 0x1
    beq CardRW_CleaningTest_Page_L_8006F3AC
    li r0, 0x0
    stw r0, 0x2c(r29)
    b CardRW_CleaningTest_Page_L_8006F3FC
    CardRW_CleaningTest_Page_L_8006F3AC:
    lwz r4, 0x2c(r29)
    lis r3, lbl_803FDB58@ha
    addi r3, r3, lbl_803FDB58@l
    addi r0, r4, 0x1
    stw r0, 0x2c(r29)
    lwz r0, 0x2c(r29)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r29)
    lwz r0, 0x27c(r29)
    cmplwi r0, 0x0
    bne CardRW_CleaningTest_Page_L_8006F3FC
    bl Backup_PublishShadowCopy
    bl Backup_PublishShadowCopy_Inline
    li r0, 0x5
    mr r3, r29
    stw r0, 0x10(r29)
    li r4, 0x0
    li r5, 0x0
    bl CardRW_TestTopMenu_Page
    CardRW_CleaningTest_Page_L_8006F3FC:
    cmpwi r30, 0x2
    bne CardRW_CleaningTest_Page_L_8006F5F0
    lwz r4, 0x1c(r29)
    lis r3, lbl_803FCA20@ha
    addi r27, r3, lbl_803FCA20@l
    li r30, 0x0
    addi r28, r4, 0x3
    b CardRW_CleaningTest_Page_L_8006F464
    CardRW_CleaningTest_Page_L_8006F41C:
    cmpw r30, r28
    bne CardRW_CleaningTest_Page_L_8006F430
    lwz r0, 0x8(r29)
    cmpwi r0, 0x1e
    bgt CardRW_CleaningTest_Page_L_8006F45C
    CardRW_CleaningTest_Page_L_8006F430:
    lwz r3, 0x270(r29)
    cmplwi r3, 0x0
    beq CardRW_CleaningTest_Page_L_8006F45C
    lwz r4, 0x0(r27)
    li r6, 0x7
    lwz r0, 0x4(r27)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_CleaningTest_Page_L_8006F45C:
    addi r27, r27, 0xc
    addi r30, r30, 0x1
    CardRW_CleaningTest_Page_L_8006F464:
    lwz r7, 0x8(r27)
    cmplwi r7, 0x0
    bne CardRW_CleaningTest_Page_L_8006F41C
    lwz r0, 0x270(r29)
    cmplwi r0, 0x0
    beq CardRW_CleaningTest_Page_L_8006F4BC
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
    CardRW_CleaningTest_Page_L_8006F4BC:
    mr r3, r29
    li r4, 0x1
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    bne CardRW_CleaningTest_Page_L_8006F5F0
    lwz r3, 0x270(r29)
    cmplwi r3, 0x0
    beq CardRW_CleaningTest_Page_L_8006F5F0
    lwz r0, 0x2c(r29)
    cmpwi r0, 0x5
    bge CardRW_CleaningTest_Page_L_8006F504
    cmpwi r0, 0x3
    bge CardRW_CleaningTest_Page_L_8006F55C
    cmpwi r0, 0x1
    bge CardRW_CleaningTest_Page_L_8006F510
    b CardRW_CleaningTest_Page_L_8006F5F0
    CardRW_CleaningTest_Page_L_8006F504:
    cmpwi r0, 0x7
    bge CardRW_CleaningTest_Page_L_8006F5F0
    b CardRW_CleaningTest_Page_L_8006F5A8
    CardRW_CleaningTest_Page_L_8006F510:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x23fc
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r29)
    cmpwi r0, 0x1e
    bgt CardRW_CleaningTest_Page_L_8006F5F0
    lwz r3, 0x270(r29)
    addi r7, r31, 0x2418
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_CleaningTest_Page_L_8006F5F0
    CardRW_CleaningTest_Page_L_8006F55C:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2434
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r29)
    cmpwi r0, 0x1e
    bgt CardRW_CleaningTest_Page_L_8006F5F0
    lwz r3, 0x270(r29)
    addi r7, r31, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_CleaningTest_Page_L_8006F5F0
    CardRW_CleaningTest_Page_L_8006F5A8:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2444
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r29)
    cmpwi r0, 0x1e
    bgt CardRW_CleaningTest_Page_L_8006F5F0
    lwz r3, 0x270(r29)
    addi r7, r31, 0x2458
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_CleaningTest_Page_L_8006F5F0:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


