/* === extracted from auto_CardRW_DataRepair_Pa_text === */
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
extern void fn_80270C48();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;
extern char lbl_806D2DBC[8];

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FCC60[];
extern unsigned int lbl_803FDD38[];

/* --- function index (1 fns, .text 0x8006C810..0x8006D308) ---
 * [  0] 0x8006C810 size:0xAF8   global CardRW_DataRepair_Page
 */

/* --- forward decls --- */
asm void CardRW_DataRepair_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_DataRepair_Page[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_DataRepair_Page = {
    (void *)&CardRW_DataRepair_Page, 0x00000AF8, (void *)extab_CardRW_DataRepair_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_DataRepair_Page(void) { /* 0x8006C810 size:0xAF8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r28, r4
    lis r4, lbl_8030E598@ha
    mr r27, r3
    addi r30, r4, lbl_8030E598@l
    bne CardRW_DataRepair_Page_L_8006C850
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x1c(r27)
    stw r0, 0x2c(r27)
    stw r0, 0x27c(r27)
    stw r3, 0x284(r27)
    stb r0, 0x5b(r27)
    CardRW_DataRepair_Page_L_8006C850:
    cmpwi r28, 0x1
    bne CardRW_DataRepair_Page_L_8006D008
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r4, 0x2c(r27)
    mr r29, r3
    cmpwi r4, 0x0
    bne CardRW_DataRepair_Page_L_8006CCE8
    lwz r0, 0x284(r27)
    cmpwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006C8C0
    lwz r12, 0x0(r3)
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_DataRepair_Page_L_8006C8C0
    li r0, 0x1f
    stw r0, 0x8(r27)
    lwz r3, 0x1c(r27)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x1c(r27)
    ble CardRW_DataRepair_Page_L_8006C8C0
    li r0, 0x0
    stw r0, 0x1c(r27)
    CardRW_DataRepair_Page_L_8006C8C0:
    mr r3, r29
    li r4, 0x1000
    lwz r12, 0x0(r29)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_DataRepair_Page_L_8006D008
    lwz r0, 0x1c(r27)
    cmpwi r0, 0x0
    bne CardRW_DataRepair_Page_L_8006CCCC
    lwz r3, 0x274(r27)
    lbz r0, 0x64(r3)
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CCC0
    li r0, 0x64
    lis r4, lbl_803FDD38@ha
    stw r0, 0x1c(r27)
    li r7, 0x1
    lis r3, g_playerData@ha
    li r5, 0x0
    stw r7, 0x2c(r27)
    addi r4, r4, lbl_803FDD38@l
    addi r6, r3, g_playerData@l
    stw r5, 0x8(r27)
    lwz r0, 0x2c(r27)
    slwi r0, r0, 3
    lwzx r0, r4, r0
    stw r0, 0x27c(r27)
    stw r7, 0x284(r27)
    stb r5, 0x5b(r27)
    lwz r31, 0x274(r27)
    lwz r3, 0x90(r31)
    lwz r0, 0x94(r31)
    stw r3, 0x0(r6)
    stw r0, 0x4(r6)
    lwz r0, 0x98(r31)
    stw r0, 0x8(r6)
    lbz r0, 0x9c(r31)
    stb r0, 0xc(r6)
    lbz r0, 0x9d(r31)
    stb r0, 0xd(r6)
    lhz r0, 0x9e(r31)
    sth r0, 0xe(r6)
    lhz r0, 0xa0(r31)
    sth r0, 0x10(r6)
    lwz r0, 0xa4(r31)
    stw r0, 0x14(r6)
    lbz r0, 0xa8(r31)
    stb r0, 0x18(r6)
    lbz r0, 0xa9(r31)
    stb r0, 0x19(r6)
    lbz r0, 0xaa(r31)
    stb r0, 0x1a(r6)
    lwz r0, 0xac(r31)
    stw r0, 0x1c(r6)
    lwz r0, 0xb0(r31)
    stw r0, 0x20(r6)
    lwz r0, 0xb4(r31)
    stw r0, 0x24(r6)
    lwz r3, 0xb8(r31)
    lwz r0, 0xbc(r31)
    stw r3, 0x28(r6)
    stw r0, 0x2c(r6)
    lwz r3, 0xc0(r31)
    lwz r0, 0xc4(r31)
    stw r3, 0x30(r6)
    stw r0, 0x34(r6)
    lwz r3, 0xc8(r31)
    lwz r0, 0xcc(r31)
    stw r3, 0x38(r6)
    stw r0, 0x3c(r6)
    lwz r3, 0xd0(r31)
    lwz r0, 0xd4(r31)
    stw r3, 0x40(r6)
    stw r0, 0x44(r6)
    lwz r3, 0xd8(r31)
    lwz r0, 0xdc(r31)
    stw r3, 0x48(r6)
    stw r0, 0x4c(r6)
    lwz r3, 0xe0(r31)
    lwz r0, 0xe4(r31)
    stw r3, 0x50(r6)
    stw r0, 0x54(r6)
    lwz r3, 0xe8(r31)
    lwz r0, 0xec(r31)
    stw r3, 0x58(r6)
    stw r0, 0x5c(r6)
    lwz r3, 0xf0(r31)
    lwz r0, 0xf4(r31)
    stw r3, 0x60(r6)
    stw r0, 0x64(r6)
    lwz r7, 0xf8(r31)
    addi r3, r6, 0xa8
    lwz r0, 0xfc(r31)
    addi r4, r31, 0x138
    li r5, 0x79
    stw r7, 0x68(r6)
    stw r0, 0x6c(r6)
    lwz r7, 0x100(r31)
    lwz r0, 0x104(r31)
    stw r7, 0x70(r6)
    stw r0, 0x74(r6)
    lwz r7, 0x108(r31)
    lwz r0, 0x10c(r31)
    stw r7, 0x78(r6)
    stw r0, 0x7c(r6)
    lwz r7, 0x110(r31)
    lwz r0, 0x114(r31)
    stw r7, 0x80(r6)
    stw r0, 0x84(r6)
    lwz r7, 0x118(r31)
    lwz r0, 0x11c(r31)
    stw r7, 0x88(r6)
    stw r0, 0x8c(r6)
    lwz r7, 0x120(r31)
    lwz r0, 0x124(r31)
    stw r7, 0x90(r6)
    stw r0, 0x94(r6)
    lwz r7, 0x128(r31)
    lwz r0, 0x12c(r31)
    stw r7, 0x98(r6)
    stw r0, 0x9c(r6)
    lwz r7, 0x130(r31)
    lwz r0, 0x134(r31)
    stw r7, 0xa0(r6)
    stw r0, 0xa4(r6)
    bl fn_80270C48
    lis r3, g_playerData@ha
    addi r4, r31, 0x1b1
    addi r3, r3, g_playerData@l
    li r5, 0x69
    addi r3, r3, 0x121
    bl fn_80270C48
    lis r3, g_playerData@ha
    lwz r4, 0x21c(r31)
    lwz r0, 0x220(r31)
    addi r3, r3, g_playerData@l
    li r29, 0x1
    stw r4, 0x18c(r3)
    stw r0, 0x190(r3)
    lwz r0, 0x224(r31)
    stw r0, 0x194(r3)
    lbz r0, 0x228(r31)
    stb r0, 0x198(r3)
    lbz r0, 0x229(r31)
    stb r0, 0x199(r3)
    lbz r0, 0x22a(r31)
    stb r0, 0x19a(r3)
    lbz r0, 0x22b(r31)
    stb r0, 0x19b(r3)
    lbz r0, 0x22c(r31)
    stb r0, 0x19c(r3)
    lbz r0, 0x22d(r31)
    stb r0, 0x19d(r3)
    lbz r0, 0x22e(r31)
    stb r0, 0x19e(r3)
    lbz r0, 0x22f(r31)
    stb r0, 0x19f(r3)
    lbz r0, 0x230(r31)
    stb r0, 0x1a0(r3)
    lwz r0, 0x234(r31)
    stw r0, 0x1a4(r3)
    lbz r0, 0x238(r31)
    stb r0, 0x1a8(r3)
    lwz r0, 0x23c(r31)
    stw r0, 0x1ac(r3)
    lbz r0, 0x240(r31)
    stb r0, 0x1b0(r3)
    lbz r0, 0x241(r31)
    stb r0, 0x1b1(r3)
    lwz r0, 0x244(r31)
    stw r0, 0x1b4(r3)
    lbz r0, 0x248(r31)
    stb r0, 0x1b8(r3)
    lbz r0, 0x249(r31)
    stb r0, 0x1b9(r3)
    lwz r4, 0x24a(r31)
    lwz r0, 0x24e(r31)
    stw r4, 0x1ba(r3)
    stw r0, 0x1be(r3)
    lwz r4, 0x252(r31)
    lwz r0, 0x256(r31)
    stw r4, 0x1c2(r3)
    stw r0, 0x1c6(r3)
    lwz r4, 0x25a(r31)
    lwz r0, 0x25e(r31)
    stw r4, 0x1ca(r3)
    stw r0, 0x1ce(r3)
    lwz r0, 0x264(r31)
    stw r0, 0x1d4(r3)
    lbz r0, 0x268(r31)
    stb r0, 0x1d8(r3)
    lbz r0, 0x269(r31)
    stb r0, 0x1d9(r3)
    lbz r0, 0x26a(r31)
    stb r0, 0x1da(r3)
    bl Sci2Card_Singleton_Get
    mr r31, r3
    bl Sci2Card_IsRetryExhausted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CBF4
    li r29, 0x65
    b CardRW_DataRepair_Page_L_8006CC7C
    CardRW_DataRepair_Page_L_8006CBF4:
    mr r3, r31
    bl Sci2Card_IsStatus2Two
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CC10
    li r29, 0x66
    b CardRW_DataRepair_Page_L_8006CC7C
    CardRW_DataRepair_Page_L_8006CC10:
    mr r3, r31
    bl Sci2Card_IsStatus2Three
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CC2C
    li r29, 0x68
    b CardRW_DataRepair_Page_L_8006CC7C
    CardRW_DataRepair_Page_L_8006CC2C:
    mr r3, r31
    bl Sci2Card_IsStatus2Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CC48
    li r29, 0x69
    b CardRW_DataRepair_Page_L_8006CC7C
    CardRW_DataRepair_Page_L_8006CC48:
    mr r3, r31
    bl Sci2Card_IsStatus2A
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CC64
    li r29, 0x6a
    b CardRW_DataRepair_Page_L_8006CC7C
    CardRW_DataRepair_Page_L_8006CC64:
    mr r3, r31
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CC7C
    li r29, 0x2
    CardRW_DataRepair_Page_L_8006CC7C:
    stw r29, 0x284(r27)
    lwz r0, 0x284(r27)
    cmpwi r0, 0x1
    beq CardRW_DataRepair_Page_L_8006D008
    li r0, 0x1
    lis r3, lbl_803FDD38@ha
    stb r0, 0x5b(r27)
    li r4, 0x6
    li r0, 0x1f
    addi r3, r3, lbl_803FDD38@l
    stw r4, 0x2c(r27)
    stw r0, 0x8(r27)
    lwz r0, 0x2c(r27)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r27)
    b CardRW_DataRepair_Page_L_8006D008
    CardRW_DataRepair_Page_L_8006CCC0:
    li r0, 0x64
    stw r0, 0x2c(r27)
    b CardRW_DataRepair_Page_L_8006D008
    CardRW_DataRepair_Page_L_8006CCCC:
    li r0, 0x5
    mr r3, r27
    stw r0, 0x10(r27)
    li r4, 0x0
    li r5, 0x6
    bl CardRW_TestTopMenu_Page
    b CardRW_DataRepair_Page_L_8006D008
    CardRW_DataRepair_Page_L_8006CCE8:
    cmpwi r4, 0x64
    blt CardRW_DataRepair_Page_L_8006CD1C
    addi r0, r4, 0x1
    cmpwi r0, 0x118
    stw r0, 0x2c(r27)
    blt CardRW_DataRepair_Page_L_8006D008
    li r0, 0x5
    mr r3, r27
    stw r0, 0x10(r27)
    li r4, 0x0
    li r5, 0x6
    bl CardRW_TestTopMenu_Page
    b CardRW_DataRepair_Page_L_8006D008
    CardRW_DataRepair_Page_L_8006CD1C:
    lwz r12, 0x27c(r27)
    cmplwi r12, 0x0
    beq CardRW_DataRepair_Page_L_8006CED0
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006CDE4
    lbz r0, 0x5b(r27)
    cmplwi r0, 0x0
    bne CardRW_DataRepair_Page_L_8006CD9C
    lwz r0, 0x2c(r27)
    lis r3, lbl_803FDD38@ha
    addi r3, r3, lbl_803FDD38@l
    slwi r0, r0, 3
    add r3, r3, r0
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq CardRW_DataRepair_Page_L_8006CD9C
    bl Sci2Card_GetPrintErrorCode
    stw r3, 0x284(r27)
    mr r3, r27
    li r4, 0x0
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    beq CardRW_DataRepair_Page_L_8006CD9C
    li r3, 0x6
    li r0, 0x1
    stw r3, 0x2c(r27)
    stb r0, 0x5b(r27)
    CardRW_DataRepair_Page_L_8006CD9C:
    lwz r0, 0x2c(r27)
    cmpwi r0, 0x2
    bne CardRW_DataRepair_Page_L_8006CDC0
    bl Sci2Card_GetByteFlag1224
    clrlwi. r0, r3, 24
    bne CardRW_DataRepair_Page_L_8006CDC0
    li r0, 0x0
    stw r0, 0x2c(r27)
    stb r0, 0x5b(r27)
    CardRW_DataRepair_Page_L_8006CDC0:
    lwz r4, 0x2c(r27)
    lis r3, lbl_803FDD38@ha
    addi r3, r3, lbl_803FDD38@l
    addi r0, r4, 0x1
    stw r0, 0x2c(r27)
    lwz r0, 0x2c(r27)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r27)
    CardRW_DataRepair_Page_L_8006CDE4:
    lbz r0, 0x5b(r27)
    cmplwi r0, 0x0
    beq CardRW_DataRepair_Page_L_8006D008
    lwz r3, 0x284(r27)
    cmpwi r3, 0x1
    bne CardRW_DataRepair_Page_L_8006CE04
    li r0, 0x0
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE04:
    lwz r0, 0x270(r27)
    cmplwi r0, 0x0
    bne CardRW_DataRepair_Page_L_8006CE18
    li r0, 0x0
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE18:
    cmpwi r3, 0x65
    bne CardRW_DataRepair_Page_L_8006CE28
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE28:
    cmpwi r3, 0x66
    bne CardRW_DataRepair_Page_L_8006CE38
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE38:
    cmpwi r3, 0x68
    bne CardRW_DataRepair_Page_L_8006CE48
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE48:
    cmpwi r3, 0x64
    bne CardRW_DataRepair_Page_L_8006CE58
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE58:
    cmpwi r3, 0x69
    bne CardRW_DataRepair_Page_L_8006CE68
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE68:
    cmpwi r3, 0x6a
    bne CardRW_DataRepair_Page_L_8006CE78
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE78:
    cmpwi r3, 0x2
    bne CardRW_DataRepair_Page_L_8006CE88
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE88:
    cmpwi r3, 0x6
    bne CardRW_DataRepair_Page_L_8006CE98
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CE98:
    cmpwi r3, 0x7
    bne CardRW_DataRepair_Page_L_8006CEA8
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CEA8:
    cmpwi r3, 0xff
    bne CardRW_DataRepair_Page_L_8006CEB8
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CEBC
    CardRW_DataRepair_Page_L_8006CEB8:
    li r0, 0x0
    CardRW_DataRepair_Page_L_8006CEBC:
    clrlwi. r0, r0, 24
    beq CardRW_DataRepair_Page_L_8006D008
    li r0, 0x1f
    stw r0, 0x8(r27)
    b CardRW_DataRepair_Page_L_8006D008
    CardRW_DataRepair_Page_L_8006CED0:
    mr r3, r27
    li r31, 0x1
    li r4, 0x0
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    beq CardRW_DataRepair_Page_L_8006CF14
    mr r3, r29
    li r4, 0x1000
    lwz r12, 0x0(r29)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne CardRW_DataRepair_Page_L_8006CF14
    li r31, 0x0
    CardRW_DataRepair_Page_L_8006CF14:
    lwz r3, 0x284(r27)
    cmpwi r3, 0x1
    bne CardRW_DataRepair_Page_L_8006CF28
    li r0, 0x0
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF28:
    lwz r0, 0x270(r27)
    cmplwi r0, 0x0
    bne CardRW_DataRepair_Page_L_8006CF3C
    li r0, 0x0
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF3C:
    cmpwi r3, 0x65
    bne CardRW_DataRepair_Page_L_8006CF4C
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF4C:
    cmpwi r3, 0x66
    bne CardRW_DataRepair_Page_L_8006CF5C
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF5C:
    cmpwi r3, 0x68
    bne CardRW_DataRepair_Page_L_8006CF6C
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF6C:
    cmpwi r3, 0x64
    bne CardRW_DataRepair_Page_L_8006CF7C
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF7C:
    cmpwi r3, 0x69
    bne CardRW_DataRepair_Page_L_8006CF8C
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF8C:
    cmpwi r3, 0x6a
    bne CardRW_DataRepair_Page_L_8006CF9C
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CF9C:
    cmpwi r3, 0x2
    bne CardRW_DataRepair_Page_L_8006CFAC
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CFAC:
    cmpwi r3, 0x6
    bne CardRW_DataRepair_Page_L_8006CFBC
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CFBC:
    cmpwi r3, 0x7
    bne CardRW_DataRepair_Page_L_8006CFCC
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CFCC:
    cmpwi r3, 0xff
    bne CardRW_DataRepair_Page_L_8006CFDC
    li r0, 0x1
    b CardRW_DataRepair_Page_L_8006CFE0
    CardRW_DataRepair_Page_L_8006CFDC:
    li r0, 0x0
    CardRW_DataRepair_Page_L_8006CFE0:
    clrlwi. r0, r0, 24
    beq CardRW_DataRepair_Page_L_8006CFF0
    clrlwi. r0, r31, 24
    beq CardRW_DataRepair_Page_L_8006D008
    CardRW_DataRepair_Page_L_8006CFF0:
    li r0, 0x5
    mr r3, r27
    stw r0, 0x10(r27)
    li r4, 0x0
    li r5, 0x6
    bl CardRW_TestTopMenu_Page
    CardRW_DataRepair_Page_L_8006D008:
    cmpwi r28, 0x2
    bne CardRW_DataRepair_Page_L_8006D2F0
    lwz r4, 0x1c(r27)
    lis r3, lbl_803FCC60@ha
    addi r31, r3, lbl_803FCC60@l
    li r28, 0x0
    addi r29, r4, 0x4
    b CardRW_DataRepair_Page_L_8006D070
    CardRW_DataRepair_Page_L_8006D028:
    cmpw r28, r29
    bne CardRW_DataRepair_Page_L_8006D03C
    lwz r0, 0x8(r27)
    cmpwi r0, 0x1e
    bgt CardRW_DataRepair_Page_L_8006D068
    CardRW_DataRepair_Page_L_8006D03C:
    lwz r3, 0x270(r27)
    cmplwi r3, 0x0
    beq CardRW_DataRepair_Page_L_8006D068
    lwz r4, 0x0(r31)
    li r6, 0x7
    lwz r0, 0x4(r31)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_DataRepair_Page_L_8006D068:
    addi r31, r31, 0xc
    addi r28, r28, 0x1
    CardRW_DataRepair_Page_L_8006D070:
    lwz r7, 0x8(r31)
    cmplwi r7, 0x0
    bne CardRW_DataRepair_Page_L_8006D028
    lwz r0, 0x270(r27)
    cmplwi r0, 0x0
    beq CardRW_DataRepair_Page_L_8006D0C8
    bl Sci2Card_Singleton_Get
    addi r4, r1, 0x10
    addi r5, r1, 0x11
    addi r6, r1, 0x12
    bl Sci2Card_GetResponseStatus
    lwz r3, 0x270(r27)
    addi r7, r30, 0x1c78
    lfs f1, lbl_806D2D44(r2)
    li r4, 0xa8
    lbz r8, 0x10(r1)
    li r5, 0x48
    lbz r9, 0x11(r1)
    li r6, 0x7
    lbz r10, 0x12(r1)
    creqv 6, 6, 6
    bl DrawText
    CardRW_DataRepair_Page_L_8006D0C8:
    lwz r3, 0x270(r27)
    cmplwi r3, 0x0
    beq CardRW_DataRepair_Page_L_8006D2F0
    lwz r10, 0x274(r27)
    lbz r0, 0x64(r10)
    cmplwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006D124
    lwz r0, 0x70(r10)
    addi r7, r30, 0x2148
    lfs f1, lbl_806D2D44(r2)
    li r4, 0xfc
    stw r0, 0x8(r1)
    li r5, 0x60
    li r6, 0x7
    lwz r0, 0x6c(r10)
    stw r0, 0xc(r1)
    lwz r9, 0x78(r10)
    lwz r8, 0x7c(r10)
    lwz r10, 0x74(r10)
    addi r9, r9, 0x1
    creqv 6, 6, 6
    bl DrawText
    b CardRW_DataRepair_Page_L_8006D14C
    CardRW_DataRepair_Page_L_8006D124:
    lwz r0, 0x8(r27)
    cmpwi r0, 0x1e
    bgt CardRW_DataRepair_Page_L_8006D14C
    lfs f1, lbl_806D2D44(r2)
    li r4, 0xfc
    li r5, 0x60
    li r6, 0x7
    la r7, lbl_806D2DBC(r2)
    creqv 6, 6, 6
    bl DrawText
    CardRW_DataRepair_Page_L_8006D14C:
    mr r3, r27
    li r4, 0x1
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    bne CardRW_DataRepair_Page_L_8006D2F0
    lwz r0, 0x2c(r27)
    cmpwi r0, 0x64
    blt CardRW_DataRepair_Page_L_8006D1D0
    lwz r0, 0x8(r27)
    cmpwi r0, 0x1e
    bgt CardRW_DataRepair_Page_L_8006D1A0
    lwz r3, 0x270(r27)
    addi r7, r30, 0x2164
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_DataRepair_Page_L_8006D1A0:
    lwz r0, 0x8(r27)
    cmpwi r0, 0x1e
    bgt CardRW_DataRepair_Page_L_8006D2F0
    lwz r3, 0x270(r27)
    addi r7, r30, 0x2184
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_DataRepair_Page_L_8006D2F0
    CardRW_DataRepair_Page_L_8006D1D0:
    cmpwi r0, 0x7
    bge CardRW_DataRepair_Page_L_8006D1EC
    cmpwi r0, 0x3
    bge CardRW_DataRepair_Page_L_8006D248
    cmpwi r0, 0x1
    bge CardRW_DataRepair_Page_L_8006D1F8
    b CardRW_DataRepair_Page_L_8006D2F0
    CardRW_DataRepair_Page_L_8006D1EC:
    cmpwi r0, 0x9
    bge CardRW_DataRepair_Page_L_8006D2F0
    b CardRW_DataRepair_Page_L_8006D298
    CardRW_DataRepair_Page_L_8006D1F8:
    lwz r3, 0x270(r27)
    addi r7, r30, 0x21a0
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r27)
    cmpwi r0, 0x1e
    bgt CardRW_DataRepair_Page_L_8006D2F0
    lwz r3, 0x270(r27)
    addi r7, r30, 0x2038
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_DataRepair_Page_L_8006D2F0
    CardRW_DataRepair_Page_L_8006D248:
    lwz r3, 0x270(r27)
    addi r7, r30, 0x21bc
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r27)
    cmpwi r0, 0x1e
    bgt CardRW_DataRepair_Page_L_8006D2F0
    lwz r3, 0x270(r27)
    addi r7, r30, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_DataRepair_Page_L_8006D2F0
    CardRW_DataRepair_Page_L_8006D298:
    lwz r0, 0x284(r27)
    cmpwi r0, 0x1
    bne CardRW_DataRepair_Page_L_8006D2C4
    lwz r3, 0x270(r27)
    addi r7, r30, 0x21d4
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_DataRepair_Page_L_8006D2C4:
    lwz r0, 0x8(r27)
    cmpwi r0, 0x1e
    bgt CardRW_DataRepair_Page_L_8006D2F0
    lwz r3, 0x270(r27)
    addi r7, r30, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_DataRepair_Page_L_8006D2F0:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

