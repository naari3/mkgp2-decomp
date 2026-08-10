/* === extracted from auto_CardRW_ReadWriteTest_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Backup_PublishShadowCopy_Inline();
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
extern unsigned int lbl_803FCA80[];
extern unsigned int lbl_803FDB98[];

/* --- function index (1 fns, .text 0x8006EC24..0x8006F200) ---
 * [  0] 0x8006EC24 size:0x5DC   global CardRW_ReadWriteTest_Page
 */

/* --- forward decls --- */
asm void CardRW_ReadWriteTest_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_ReadWriteTest_Page[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_ReadWriteTest_Page = {
    (void *)&CardRW_ReadWriteTest_Page, 0x000005DC, (void *)extab_CardRW_ReadWriteTest_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_ReadWriteTest_Page(void) { /* 0x8006EC24 size:0x5DC */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r29, r4
    lis r4, lbl_8030E598@ha
    mr r28, r3
    addi r31, r4, lbl_8030E598@l
    bne CardRW_ReadWriteTest_Page_L_8006ECF8
    li r4, 0x1
    li r3, 0x0
    stw r4, 0x1c(r28)
    li r0, 0x3b
    addi r5, r28, 0x88
    stw r3, 0x2c(r28)
    stw r3, 0x27c(r28)
    stw r4, 0x284(r28)
    lwz r7, 0x274(r28)
    lbz r3, 0x64(r7)
    addi r4, r7, 0x8c
    stb r3, 0x60(r28)
    lwz r6, 0x68(r7)
    lwz r3, 0x6c(r7)
    stw r6, 0x64(r28)
    stw r3, 0x68(r28)
    lwz r6, 0x70(r7)
    lwz r3, 0x74(r7)
    stw r6, 0x6c(r28)
    stw r3, 0x70(r28)
    lwz r6, 0x78(r7)
    lwz r3, 0x7c(r7)
    stw r6, 0x74(r28)
    stw r3, 0x78(r28)
    lwz r6, 0x80(r7)
    lwz r3, 0x84(r7)
    stw r6, 0x7c(r28)
    stw r3, 0x80(r28)
    lwz r6, 0x88(r7)
    lwz r3, 0x8c(r7)
    stw r6, 0x84(r28)
    stw r3, 0x88(r28)
    mtctr r0
    CardRW_ReadWriteTest_Page_L_8006ECCC:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz CardRW_ReadWriteTest_Page_L_8006ECCC
    lwz r0, 0x4(r4)
    stw r0, 0x4(r5)
    lwz r0, 0x26c(r7)
    stw r0, 0x268(r28)
    lbz r0, 0x270(r7)
    stb r0, 0x26c(r28)
    CardRW_ReadWriteTest_Page_L_8006ECF8:
    cmpwi r29, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006EFF4
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x0
    bne CardRW_ReadWriteTest_Page_L_8006EEB8
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r0, 0x284(r28)
    mr r27, r3
    cmpwi r0, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006ED68
    lwz r12, 0x0(r3)
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_ReadWriteTest_Page_L_8006ED68
    li r0, 0x1f
    stw r0, 0x8(r28)
    lwz r3, 0x1c(r28)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x1c(r28)
    ble CardRW_ReadWriteTest_Page_L_8006ED68
    li r0, 0x0
    stw r0, 0x1c(r28)
    CardRW_ReadWriteTest_Page_L_8006ED68:
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_ReadWriteTest_Page_L_8006EFF4
    lwz r0, 0x1c(r28)
    cmpwi r0, 0x0
    bne CardRW_ReadWriteTest_Page_L_8006EE9C
    li r0, 0x64
    lis r3, lbl_803FDB98@ha
    stw r0, 0x1c(r28)
    li r30, 0x1
    li r0, 0x0
    addi r3, r3, lbl_803FDB98@l
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
    bne CardRW_ReadWriteTest_Page_L_8006EDE8
    li r30, 0x65
    b CardRW_ReadWriteTest_Page_L_8006EE70
    CardRW_ReadWriteTest_Page_L_8006EDE8:
    mr r3, r27
    bl Sci2Card_IsStatus2Two
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006EE04
    li r30, 0x66
    b CardRW_ReadWriteTest_Page_L_8006EE70
    CardRW_ReadWriteTest_Page_L_8006EE04:
    mr r3, r27
    bl Sci2Card_IsStatus2Three
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006EE20
    li r30, 0x68
    b CardRW_ReadWriteTest_Page_L_8006EE70
    CardRW_ReadWriteTest_Page_L_8006EE20:
    mr r3, r27
    bl Sci2Card_IsStatus2Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006EE3C
    li r30, 0x69
    b CardRW_ReadWriteTest_Page_L_8006EE70
    CardRW_ReadWriteTest_Page_L_8006EE3C:
    mr r3, r27
    bl Sci2Card_IsStatus2A
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006EE58
    li r30, 0x6a
    b CardRW_ReadWriteTest_Page_L_8006EE70
    CardRW_ReadWriteTest_Page_L_8006EE58:
    mr r3, r27
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006EE70
    li r30, 0x2
    CardRW_ReadWriteTest_Page_L_8006EE70:
    stw r30, 0x284(r28)
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    beq CardRW_ReadWriteTest_Page_L_8006EFF4
    li r0, 0x1
    li r3, 0x1f
    stb r0, 0x5b(r28)
    li r0, 0x0
    stw r3, 0x8(r28)
    stw r0, 0x2c(r28)
    b CardRW_ReadWriteTest_Page_L_8006EFF4
    CardRW_ReadWriteTest_Page_L_8006EE9C:
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x1
    bl CardRW_TestTopMenu_Page
    b CardRW_ReadWriteTest_Page_L_8006EFF4
    CardRW_ReadWriteTest_Page_L_8006EEB8:
    lwz r12, 0x27c(r28)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_ReadWriteTest_Page_L_8006EFF4
    lwz r0, 0x2c(r28)
    lis r3, lbl_803FDB98@ha
    addi r3, r3, lbl_803FDB98@l
    slwi r0, r0, 3
    add r3, r3, r0
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq CardRW_ReadWriteTest_Page_L_8006EEF8
    bl Sci2Card_GetPrintErrorCode
    stw r3, 0x284(r28)
    CardRW_ReadWriteTest_Page_L_8006EEF8:
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    beq CardRW_ReadWriteTest_Page_L_8006EF10
    li r0, 0x0
    stw r0, 0x2c(r28)
    b CardRW_ReadWriteTest_Page_L_8006EFF4
    CardRW_ReadWriteTest_Page_L_8006EF10:
    lwz r4, 0x2c(r28)
    lis r3, lbl_803FDB98@ha
    addi r3, r3, lbl_803FDB98@l
    addi r0, r4, 0x1
    stw r0, 0x2c(r28)
    lwz r0, 0x2c(r28)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r28)
    lwz r0, 0x27c(r28)
    cmplwi r0, 0x0
    bne CardRW_ReadWriteTest_Page_L_8006EFF4
    lwz r7, 0x274(r28)
    li r0, 0x3b
    lbz r3, 0x60(r28)
    addi r4, r28, 0x88
    addi r5, r7, 0x8c
    stb r3, 0x64(r7)
    lwz r6, 0x64(r28)
    lwz r3, 0x68(r28)
    stw r6, 0x68(r7)
    stw r3, 0x6c(r7)
    lwz r6, 0x6c(r28)
    lwz r3, 0x70(r28)
    stw r6, 0x70(r7)
    stw r3, 0x74(r7)
    lwz r6, 0x74(r28)
    lwz r3, 0x78(r28)
    stw r6, 0x78(r7)
    stw r3, 0x7c(r7)
    lwz r6, 0x7c(r28)
    lwz r3, 0x80(r28)
    stw r6, 0x80(r7)
    stw r3, 0x84(r7)
    lwz r6, 0x84(r28)
    lwz r3, 0x88(r28)
    stw r6, 0x88(r7)
    stw r3, 0x8c(r7)
    mtctr r0
    CardRW_ReadWriteTest_Page_L_8006EFAC:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz CardRW_ReadWriteTest_Page_L_8006EFAC
    lwz r0, 0x4(r4)
    stw r0, 0x4(r5)
    lwz r0, 0x268(r28)
    stw r0, 0x26c(r7)
    lbz r0, 0x26c(r28)
    stb r0, 0x270(r7)
    bl Backup_PublishShadowCopy_Inline
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x1
    bl CardRW_TestTopMenu_Page
    CardRW_ReadWriteTest_Page_L_8006EFF4:
    cmpwi r29, 0x2
    bne CardRW_ReadWriteTest_Page_L_8006F1E8
    lwz r4, 0x1c(r28)
    lis r3, lbl_803FCA80@ha
    addi r30, r3, lbl_803FCA80@l
    li r27, 0x0
    addi r29, r4, 0x3
    b CardRW_ReadWriteTest_Page_L_8006F05C
    CardRW_ReadWriteTest_Page_L_8006F014:
    cmpw r27, r29
    bne CardRW_ReadWriteTest_Page_L_8006F028
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_ReadWriteTest_Page_L_8006F054
    CardRW_ReadWriteTest_Page_L_8006F028:
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_ReadWriteTest_Page_L_8006F054
    lwz r4, 0x0(r30)
    li r6, 0x7
    lwz r0, 0x4(r30)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_ReadWriteTest_Page_L_8006F054:
    addi r30, r30, 0xc
    addi r27, r27, 0x1
    CardRW_ReadWriteTest_Page_L_8006F05C:
    lwz r7, 0x8(r30)
    cmplwi r7, 0x0
    bne CardRW_ReadWriteTest_Page_L_8006F014
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    beq CardRW_ReadWriteTest_Page_L_8006F0B4
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
    CardRW_ReadWriteTest_Page_L_8006F0B4:
    mr r3, r28
    li r4, 0x1
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    bne CardRW_ReadWriteTest_Page_L_8006F1E8
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_ReadWriteTest_Page_L_8006F1E8
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x7
    bge CardRW_ReadWriteTest_Page_L_8006F0FC
    cmpwi r0, 0x3
    bge CardRW_ReadWriteTest_Page_L_8006F154
    cmpwi r0, 0x1
    bge CardRW_ReadWriteTest_Page_L_8006F108
    b CardRW_ReadWriteTest_Page_L_8006F1E8
    CardRW_ReadWriteTest_Page_L_8006F0FC:
    cmpwi r0, 0x9
    bge CardRW_ReadWriteTest_Page_L_8006F1E8
    b CardRW_ReadWriteTest_Page_L_8006F1A0
    CardRW_ReadWriteTest_Page_L_8006F108:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x23a0
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_ReadWriteTest_Page_L_8006F1E8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2334
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_ReadWriteTest_Page_L_8006F1E8
    CardRW_ReadWriteTest_Page_L_8006F154:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x23c0
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_ReadWriteTest_Page_L_8006F1E8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_ReadWriteTest_Page_L_8006F1E8
    CardRW_ReadWriteTest_Page_L_8006F1A0:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x23e0
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_ReadWriteTest_Page_L_8006F1E8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ReadWriteTest_Page_L_8006F1E8:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


