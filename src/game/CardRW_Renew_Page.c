/* === extracted from auto_CardRW_Renew_Page_text === */
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
extern void Sci2Card_GetByteFlag1224();
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
extern unsigned int g_playerData[];
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FCD8C[];
extern unsigned int lbl_803FDDD8[];

/* --- function index (1 fns, .text 0x8006B32C..0x8006BB04) ---
 * [  0] 0x8006B32C size:0x7D8   global CardRW_Renew_Page
 */

/* --- forward decls --- */
asm void CardRW_Renew_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_Renew_Page[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_Renew_Page = {
    (void *)&CardRW_Renew_Page, 0x000007D8, (void *)extab_CardRW_Renew_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_Renew_Page(void) { /* 0x8006B32C size:0x7D8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r29, r4
    lis r4, lbl_8030E598@ha
    mr r28, r3
    addi r31, r4, lbl_8030E598@l
    bne CardRW_Renew_Page_L_8006B36C
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x1c(r28)
    stw r0, 0x2c(r28)
    stw r0, 0x27c(r28)
    stw r3, 0x284(r28)
    stb r0, 0x5b(r28)
    CardRW_Renew_Page_L_8006B36C:
    cmpwi r29, 0x1
    bne CardRW_Renew_Page_L_8006B840
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r0, 0x2c(r28)
    mr r27, r3
    cmpwi r0, 0x0
    bne CardRW_Renew_Page_L_8006B530
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B3DC
    lwz r12, 0x0(r3)
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_Renew_Page_L_8006B3DC
    li r0, 0x1f
    stw r0, 0x8(r28)
    lwz r3, 0x1c(r28)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x1c(r28)
    ble CardRW_Renew_Page_L_8006B3DC
    li r0, 0x0
    stw r0, 0x1c(r28)
    CardRW_Renew_Page_L_8006B3DC:
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_Renew_Page_L_8006B840
    lwz r0, 0x1c(r28)
    cmpwi r0, 0x0
    bne CardRW_Renew_Page_L_8006B514
    li r0, 0x64
    lis r3, lbl_803FDDD8@ha
    stw r0, 0x1c(r28)
    li r30, 0x1
    li r4, 0x0
    addi r3, r3, lbl_803FDDD8@l
    stw r30, 0x2c(r28)
    stw r4, 0x8(r28)
    lwz r0, 0x2c(r28)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r28)
    stw r30, 0x284(r28)
    stb r4, 0x5b(r28)
    bl Sci2Card_Singleton_Get
    mr r27, r3
    bl Sci2Card_IsRetryExhausted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B460
    li r30, 0x65
    b CardRW_Renew_Page_L_8006B4E8
    CardRW_Renew_Page_L_8006B460:
    mr r3, r27
    bl Sci2Card_IsStatus2Two
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B47C
    li r30, 0x66
    b CardRW_Renew_Page_L_8006B4E8
    CardRW_Renew_Page_L_8006B47C:
    mr r3, r27
    bl Sci2Card_IsStatus2Three
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B498
    li r30, 0x68
    b CardRW_Renew_Page_L_8006B4E8
    CardRW_Renew_Page_L_8006B498:
    mr r3, r27
    bl Sci2Card_IsStatus2Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B4B4
    li r30, 0x69
    b CardRW_Renew_Page_L_8006B4E8
    CardRW_Renew_Page_L_8006B4B4:
    mr r3, r27
    bl Sci2Card_IsStatus2A
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B4D0
    li r30, 0x6a
    b CardRW_Renew_Page_L_8006B4E8
    CardRW_Renew_Page_L_8006B4D0:
    mr r3, r27
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B4E8
    li r30, 0x2
    CardRW_Renew_Page_L_8006B4E8:
    stw r30, 0x284(r28)
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    beq CardRW_Renew_Page_L_8006B840
    li r0, 0x1
    li r3, 0x1f
    stb r0, 0x5b(r28)
    li r0, 0x0
    stw r3, 0x8(r28)
    stw r0, 0x2c(r28)
    b CardRW_Renew_Page_L_8006B840
    CardRW_Renew_Page_L_8006B514:
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x9
    bl CardRW_TestTopMenu_Page
    b CardRW_Renew_Page_L_8006B840
    CardRW_Renew_Page_L_8006B530:
    lwz r12, 0x27c(r28)
    cmplwi r12, 0x0
    beq CardRW_Renew_Page_L_8006B708
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Renew_Page_L_8006B61C
    lbz r0, 0x5b(r28)
    cmplwi r0, 0x0
    bne CardRW_Renew_Page_L_8006B5B0
    lwz r0, 0x2c(r28)
    lis r3, lbl_803FDDD8@ha
    addi r3, r3, lbl_803FDDD8@l
    slwi r0, r0, 3
    add r3, r3, r0
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq CardRW_Renew_Page_L_8006B5B0
    bl Sci2Card_GetPrintErrorCode
    stw r3, 0x284(r28)
    mr r3, r28
    li r4, 0x0
    li r5, 0x1
    li r6, 0x1
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    beq CardRW_Renew_Page_L_8006B5B0
    li r3, 0xc
    li r0, 0x1
    stw r3, 0x2c(r28)
    stb r0, 0x5b(r28)
    CardRW_Renew_Page_L_8006B5B0:
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x2
    bne CardRW_Renew_Page_L_8006B5D4
    bl Sci2Card_GetByteFlag1224
    clrlwi. r0, r3, 24
    bne CardRW_Renew_Page_L_8006B5D4
    li r0, 0x0
    stw r0, 0x2c(r28)
    stb r0, 0x5b(r28)
    CardRW_Renew_Page_L_8006B5D4:
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x4
    bne CardRW_Renew_Page_L_8006B5F8
    lis r4, g_playerData@ha
    li r3, 0x32
    addi r4, r4, g_playerData@l
    li r0, 0x0
    stb r3, 0x198(r4)
    stb r0, 0x199(r4)
    CardRW_Renew_Page_L_8006B5F8:
    lwz r4, 0x2c(r28)
    lis r3, lbl_803FDDD8@ha
    addi r3, r3, lbl_803FDDD8@l
    addi r0, r4, 0x1
    stw r0, 0x2c(r28)
    lwz r0, 0x2c(r28)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r28)
    CardRW_Renew_Page_L_8006B61C:
    lbz r0, 0x5b(r28)
    cmplwi r0, 0x0
    beq CardRW_Renew_Page_L_8006B840
    lwz r3, 0x284(r28)
    cmpwi r3, 0x1
    bne CardRW_Renew_Page_L_8006B63C
    li r0, 0x0
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B63C:
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    bne CardRW_Renew_Page_L_8006B650
    li r0, 0x0
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B650:
    cmpwi r3, 0x65
    bne CardRW_Renew_Page_L_8006B660
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B660:
    cmpwi r3, 0x66
    bne CardRW_Renew_Page_L_8006B670
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B670:
    cmpwi r3, 0x68
    bne CardRW_Renew_Page_L_8006B680
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B680:
    cmpwi r3, 0x64
    bne CardRW_Renew_Page_L_8006B690
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B690:
    cmpwi r3, 0x69
    bne CardRW_Renew_Page_L_8006B6A0
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B6A0:
    cmpwi r3, 0x6a
    bne CardRW_Renew_Page_L_8006B6B0
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B6B0:
    cmpwi r3, 0x2
    bne CardRW_Renew_Page_L_8006B6C0
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B6C0:
    cmpwi r3, 0x6
    bne CardRW_Renew_Page_L_8006B6D0
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B6D0:
    cmpwi r3, 0x7
    bne CardRW_Renew_Page_L_8006B6E0
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B6E0:
    cmpwi r3, 0xff
    bne CardRW_Renew_Page_L_8006B6F0
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B6F4
    CardRW_Renew_Page_L_8006B6F0:
    li r0, 0x0
    CardRW_Renew_Page_L_8006B6F4:
    clrlwi. r0, r0, 24
    beq CardRW_Renew_Page_L_8006B840
    li r0, 0x1f
    stw r0, 0x8(r28)
    b CardRW_Renew_Page_L_8006B840
    CardRW_Renew_Page_L_8006B708:
    mr r3, r28
    li r30, 0x1
    li r4, 0x0
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    beq CardRW_Renew_Page_L_8006B74C
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne CardRW_Renew_Page_L_8006B74C
    li r30, 0x0
    CardRW_Renew_Page_L_8006B74C:
    lwz r3, 0x284(r28)
    cmpwi r3, 0x1
    bne CardRW_Renew_Page_L_8006B760
    li r0, 0x0
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B760:
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    bne CardRW_Renew_Page_L_8006B774
    li r0, 0x0
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B774:
    cmpwi r3, 0x65
    bne CardRW_Renew_Page_L_8006B784
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B784:
    cmpwi r3, 0x66
    bne CardRW_Renew_Page_L_8006B794
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B794:
    cmpwi r3, 0x68
    bne CardRW_Renew_Page_L_8006B7A4
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B7A4:
    cmpwi r3, 0x64
    bne CardRW_Renew_Page_L_8006B7B4
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B7B4:
    cmpwi r3, 0x69
    bne CardRW_Renew_Page_L_8006B7C4
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B7C4:
    cmpwi r3, 0x6a
    bne CardRW_Renew_Page_L_8006B7D4
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B7D4:
    cmpwi r3, 0x2
    bne CardRW_Renew_Page_L_8006B7E4
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B7E4:
    cmpwi r3, 0x6
    bne CardRW_Renew_Page_L_8006B7F4
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B7F4:
    cmpwi r3, 0x7
    bne CardRW_Renew_Page_L_8006B804
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B804:
    cmpwi r3, 0xff
    bne CardRW_Renew_Page_L_8006B814
    li r0, 0x1
    b CardRW_Renew_Page_L_8006B818
    CardRW_Renew_Page_L_8006B814:
    li r0, 0x0
    CardRW_Renew_Page_L_8006B818:
    clrlwi. r0, r0, 24
    beq CardRW_Renew_Page_L_8006B828
    clrlwi. r0, r30, 24
    beq CardRW_Renew_Page_L_8006B840
    CardRW_Renew_Page_L_8006B828:
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x9
    bl CardRW_TestTopMenu_Page
    CardRW_Renew_Page_L_8006B840:
    cmpwi r29, 0x2
    bne CardRW_Renew_Page_L_8006BAEC
    lwz r4, 0x1c(r28)
    lis r3, lbl_803FCD8C@ha
    addi r30, r3, lbl_803FCD8C@l
    li r27, 0x0
    addi r29, r4, 0x3
    b CardRW_Renew_Page_L_8006B8A8
    CardRW_Renew_Page_L_8006B860:
    cmpw r27, r29
    bne CardRW_Renew_Page_L_8006B874
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Renew_Page_L_8006B8A0
    CardRW_Renew_Page_L_8006B874:
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_Renew_Page_L_8006B8A0
    lwz r4, 0x0(r30)
    li r6, 0x7
    lwz r0, 0x4(r30)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_Renew_Page_L_8006B8A0:
    addi r30, r30, 0xc
    addi r27, r27, 0x1
    CardRW_Renew_Page_L_8006B8A8:
    lwz r7, 0x8(r30)
    cmplwi r7, 0x0
    bne CardRW_Renew_Page_L_8006B860
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    beq CardRW_Renew_Page_L_8006B900
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
    CardRW_Renew_Page_L_8006B900:
    mr r3, r28
    li r4, 0x1
    li r5, 0x1
    li r6, 0x1
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    bne CardRW_Renew_Page_L_8006BAEC
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_Renew_Page_L_8006BAEC
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x7
    bge CardRW_Renew_Page_L_8006B954
    cmpwi r0, 0x3
    bge CardRW_Renew_Page_L_8006B948
    cmpwi r0, 0x1
    bge CardRW_Renew_Page_L_8006B968
    b CardRW_Renew_Page_L_8006BAEC
    CardRW_Renew_Page_L_8006B948:
    cmpwi r0, 0x5
    bge CardRW_Renew_Page_L_8006BA00
    b CardRW_Renew_Page_L_8006B9B4
    CardRW_Renew_Page_L_8006B954:
    cmpwi r0, 0xf
    bge CardRW_Renew_Page_L_8006BAEC
    cmpwi r0, 0xd
    bge CardRW_Renew_Page_L_8006BA98
    b CardRW_Renew_Page_L_8006BA4C
    CardRW_Renew_Page_L_8006B968:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2024
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Renew_Page_L_8006BAEC
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2038
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x138
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_Renew_Page_L_8006BAEC
    CardRW_Renew_Page_L_8006B9B4:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x204c
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Renew_Page_L_8006BAEC
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x138
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_Renew_Page_L_8006BAEC
    CardRW_Renew_Page_L_8006BA00:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x207c
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Renew_Page_L_8006BAEC
    lwz r3, 0x270(r28)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x138
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_Renew_Page_L_8006BAEC
    CardRW_Renew_Page_L_8006BA4C:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2090
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Renew_Page_L_8006BAEC
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x120
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_Renew_Page_L_8006BAEC
    CardRW_Renew_Page_L_8006BA98:
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    bne CardRW_Renew_Page_L_8006BAC0
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x20a4
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_Renew_Page_L_8006BAC0:
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Renew_Page_L_8006BAEC
    lwz r3, 0x270(r28)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x120
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_Renew_Page_L_8006BAEC:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


