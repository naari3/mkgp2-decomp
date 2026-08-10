/* === extracted from auto_CardRW_Reprint_Page_text === */
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
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FCCCC[];
extern unsigned int lbl_803FDD88[];

/* --- function index (1 fns, .text 0x8006C0F4..0x8006C810) ---
 * [  0] 0x8006C0F4 size:0x71C   global CardRW_Reprint_Page
 */

/* --- forward decls --- */
asm void CardRW_Reprint_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_Reprint_Page[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_Reprint_Page = {
    (void *)&CardRW_Reprint_Page, 0x0000071C, (void *)extab_CardRW_Reprint_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_Reprint_Page(void) { /* 0x8006C0F4 size:0x71C */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r29, r4
    lis r4, lbl_8030E598@ha
    mr r28, r3
    addi r31, r4, lbl_8030E598@l
    bne CardRW_Reprint_Page_L_8006C134
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x1c(r28)
    stw r0, 0x2c(r28)
    stw r0, 0x27c(r28)
    stw r3, 0x284(r28)
    stb r0, 0x5b(r28)
    CardRW_Reprint_Page_L_8006C134:
    cmpwi r29, 0x1
    bne CardRW_Reprint_Page_L_8006C5E4
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r0, 0x2c(r28)
    mr r27, r3
    cmpwi r0, 0x0
    bne CardRW_Reprint_Page_L_8006C2F8
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    bne CardRW_Reprint_Page_L_8006C1A4
    lwz r12, 0x0(r3)
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_Reprint_Page_L_8006C1A4
    li r0, 0x1f
    stw r0, 0x8(r28)
    lwz r3, 0x1c(r28)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x1c(r28)
    ble CardRW_Reprint_Page_L_8006C1A4
    li r0, 0x0
    stw r0, 0x1c(r28)
    CardRW_Reprint_Page_L_8006C1A4:
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq CardRW_Reprint_Page_L_8006C5E4
    lwz r0, 0x1c(r28)
    cmpwi r0, 0x0
    bne CardRW_Reprint_Page_L_8006C2DC
    li r0, 0x64
    lis r3, lbl_803FDD88@ha
    stw r0, 0x1c(r28)
    li r30, 0x1
    li r4, 0x0
    addi r3, r3, lbl_803FDD88@l
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
    bne CardRW_Reprint_Page_L_8006C228
    li r30, 0x65
    b CardRW_Reprint_Page_L_8006C2B0
    CardRW_Reprint_Page_L_8006C228:
    mr r3, r27
    bl Sci2Card_IsStatus2Two
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Reprint_Page_L_8006C244
    li r30, 0x66
    b CardRW_Reprint_Page_L_8006C2B0
    CardRW_Reprint_Page_L_8006C244:
    mr r3, r27
    bl Sci2Card_IsStatus2Three
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Reprint_Page_L_8006C260
    li r30, 0x68
    b CardRW_Reprint_Page_L_8006C2B0
    CardRW_Reprint_Page_L_8006C260:
    mr r3, r27
    bl Sci2Card_IsStatus2Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Reprint_Page_L_8006C27C
    li r30, 0x69
    b CardRW_Reprint_Page_L_8006C2B0
    CardRW_Reprint_Page_L_8006C27C:
    mr r3, r27
    bl Sci2Card_IsStatus2A
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Reprint_Page_L_8006C298
    li r30, 0x6a
    b CardRW_Reprint_Page_L_8006C2B0
    CardRW_Reprint_Page_L_8006C298:
    mr r3, r27
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Reprint_Page_L_8006C2B0
    li r30, 0x2
    CardRW_Reprint_Page_L_8006C2B0:
    stw r30, 0x284(r28)
    lwz r0, 0x284(r28)
    cmpwi r0, 0x1
    beq CardRW_Reprint_Page_L_8006C5E4
    li r0, 0x1
    li r3, 0x1f
    stb r0, 0x5b(r28)
    li r0, 0x0
    stw r3, 0x8(r28)
    stw r0, 0x2c(r28)
    b CardRW_Reprint_Page_L_8006C5E4
    CardRW_Reprint_Page_L_8006C2DC:
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x7
    bl CardRW_TestTopMenu_Page
    b CardRW_Reprint_Page_L_8006C5E4
    CardRW_Reprint_Page_L_8006C2F8:
    lwz r12, 0x27c(r28)
    cmplwi r12, 0x0
    beq CardRW_Reprint_Page_L_8006C4AC
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardRW_Reprint_Page_L_8006C3C0
    lbz r0, 0x5b(r28)
    cmplwi r0, 0x0
    bne CardRW_Reprint_Page_L_8006C378
    lwz r0, 0x2c(r28)
    lis r3, lbl_803FDD88@ha
    addi r3, r3, lbl_803FDD88@l
    slwi r0, r0, 3
    add r3, r3, r0
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq CardRW_Reprint_Page_L_8006C378
    bl Sci2Card_GetPrintErrorCode
    stw r3, 0x284(r28)
    mr r3, r28
    li r4, 0x0
    li r5, 0x1
    li r6, 0x1
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    beq CardRW_Reprint_Page_L_8006C378
    li r3, 0x6
    li r0, 0x1
    stw r3, 0x2c(r28)
    stb r0, 0x5b(r28)
    CardRW_Reprint_Page_L_8006C378:
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x2
    bne CardRW_Reprint_Page_L_8006C39C
    bl Sci2Card_GetByteFlag1224
    clrlwi. r0, r3, 24
    bne CardRW_Reprint_Page_L_8006C39C
    li r0, 0x0
    stw r0, 0x2c(r28)
    stb r0, 0x5b(r28)
    CardRW_Reprint_Page_L_8006C39C:
    lwz r4, 0x2c(r28)
    lis r3, lbl_803FDD88@ha
    addi r3, r3, lbl_803FDD88@l
    addi r0, r4, 0x1
    stw r0, 0x2c(r28)
    lwz r0, 0x2c(r28)
    slwi r0, r0, 3
    lwzx r0, r3, r0
    stw r0, 0x27c(r28)
    CardRW_Reprint_Page_L_8006C3C0:
    lbz r0, 0x5b(r28)
    cmplwi r0, 0x0
    beq CardRW_Reprint_Page_L_8006C5E4
    lwz r3, 0x284(r28)
    cmpwi r3, 0x1
    bne CardRW_Reprint_Page_L_8006C3E0
    li r0, 0x0
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C3E0:
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    bne CardRW_Reprint_Page_L_8006C3F4
    li r0, 0x0
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C3F4:
    cmpwi r3, 0x65
    bne CardRW_Reprint_Page_L_8006C404
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C404:
    cmpwi r3, 0x66
    bne CardRW_Reprint_Page_L_8006C414
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C414:
    cmpwi r3, 0x68
    bne CardRW_Reprint_Page_L_8006C424
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C424:
    cmpwi r3, 0x64
    bne CardRW_Reprint_Page_L_8006C434
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C434:
    cmpwi r3, 0x69
    bne CardRW_Reprint_Page_L_8006C444
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C444:
    cmpwi r3, 0x6a
    bne CardRW_Reprint_Page_L_8006C454
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C454:
    cmpwi r3, 0x2
    bne CardRW_Reprint_Page_L_8006C464
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C464:
    cmpwi r3, 0x6
    bne CardRW_Reprint_Page_L_8006C474
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C474:
    cmpwi r3, 0x7
    bne CardRW_Reprint_Page_L_8006C484
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C484:
    cmpwi r3, 0xff
    bne CardRW_Reprint_Page_L_8006C494
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C498
    CardRW_Reprint_Page_L_8006C494:
    li r0, 0x0
    CardRW_Reprint_Page_L_8006C498:
    clrlwi. r0, r0, 24
    beq CardRW_Reprint_Page_L_8006C5E4
    li r0, 0x1f
    stw r0, 0x8(r28)
    b CardRW_Reprint_Page_L_8006C5E4
    CardRW_Reprint_Page_L_8006C4AC:
    mr r3, r28
    li r30, 0x1
    li r4, 0x0
    li r5, 0x1
    li r6, 0x0
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    beq CardRW_Reprint_Page_L_8006C4F0
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    bne CardRW_Reprint_Page_L_8006C4F0
    li r30, 0x0
    CardRW_Reprint_Page_L_8006C4F0:
    lwz r3, 0x284(r28)
    cmpwi r3, 0x1
    bne CardRW_Reprint_Page_L_8006C504
    li r0, 0x0
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C504:
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    bne CardRW_Reprint_Page_L_8006C518
    li r0, 0x0
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C518:
    cmpwi r3, 0x65
    bne CardRW_Reprint_Page_L_8006C528
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C528:
    cmpwi r3, 0x66
    bne CardRW_Reprint_Page_L_8006C538
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C538:
    cmpwi r3, 0x68
    bne CardRW_Reprint_Page_L_8006C548
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C548:
    cmpwi r3, 0x64
    bne CardRW_Reprint_Page_L_8006C558
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C558:
    cmpwi r3, 0x69
    bne CardRW_Reprint_Page_L_8006C568
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C568:
    cmpwi r3, 0x6a
    bne CardRW_Reprint_Page_L_8006C578
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C578:
    cmpwi r3, 0x2
    bne CardRW_Reprint_Page_L_8006C588
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C588:
    cmpwi r3, 0x6
    bne CardRW_Reprint_Page_L_8006C598
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C598:
    cmpwi r3, 0x7
    bne CardRW_Reprint_Page_L_8006C5A8
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C5A8:
    cmpwi r3, 0xff
    bne CardRW_Reprint_Page_L_8006C5B8
    li r0, 0x1
    b CardRW_Reprint_Page_L_8006C5BC
    CardRW_Reprint_Page_L_8006C5B8:
    li r0, 0x0
    CardRW_Reprint_Page_L_8006C5BC:
    clrlwi. r0, r0, 24
    beq CardRW_Reprint_Page_L_8006C5CC
    clrlwi. r0, r30, 24
    beq CardRW_Reprint_Page_L_8006C5E4
    CardRW_Reprint_Page_L_8006C5CC:
    li r0, 0x5
    mr r3, r28
    stw r0, 0x10(r28)
    li r4, 0x0
    li r5, 0x7
    bl CardRW_TestTopMenu_Page
    CardRW_Reprint_Page_L_8006C5E4:
    cmpwi r29, 0x2
    bne CardRW_Reprint_Page_L_8006C7F8
    lwz r4, 0x1c(r28)
    lis r3, lbl_803FCCCC@ha
    addi r30, r3, lbl_803FCCCC@l
    li r27, 0x0
    addi r29, r4, 0x3
    b CardRW_Reprint_Page_L_8006C64C
    CardRW_Reprint_Page_L_8006C604:
    cmpw r27, r29
    bne CardRW_Reprint_Page_L_8006C618
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Reprint_Page_L_8006C644
    CardRW_Reprint_Page_L_8006C618:
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_Reprint_Page_L_8006C644
    lwz r4, 0x0(r30)
    li r6, 0x7
    lwz r0, 0x4(r30)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    CardRW_Reprint_Page_L_8006C644:
    addi r30, r30, 0xc
    addi r27, r27, 0x1
    CardRW_Reprint_Page_L_8006C64C:
    lwz r7, 0x8(r30)
    cmplwi r7, 0x0
    bne CardRW_Reprint_Page_L_8006C604
    lwz r0, 0x270(r28)
    cmplwi r0, 0x0
    beq CardRW_Reprint_Page_L_8006C6A4
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
    CardRW_Reprint_Page_L_8006C6A4:
    mr r3, r28
    li r4, 0x1
    li r5, 0x1
    li r6, 0x1
    bl CardRW_ErrorDisplay
    clrlwi. r0, r3, 24
    bne CardRW_Reprint_Page_L_8006C7F8
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq CardRW_Reprint_Page_L_8006C7F8
    lwz r0, 0x2c(r28)
    cmpwi r0, 0x7
    bge CardRW_Reprint_Page_L_8006C6EC
    cmpwi r0, 0x3
    bge CardRW_Reprint_Page_L_8006C744
    cmpwi r0, 0x1
    bge CardRW_Reprint_Page_L_8006C6F8
    b CardRW_Reprint_Page_L_8006C7F8
    CardRW_Reprint_Page_L_8006C6EC:
    cmpwi r0, 0x9
    bge CardRW_Reprint_Page_L_8006C7F8
    b CardRW_Reprint_Page_L_8006C790
    CardRW_Reprint_Page_L_8006C6F8:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x20ec
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Reprint_Page_L_8006C7F8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2038
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_Reprint_Page_L_8006C7F8
    CardRW_Reprint_Page_L_8006C744:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2104
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Reprint_Page_L_8006C7F8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    b CardRW_Reprint_Page_L_8006C7F8
    CardRW_Reprint_Page_L_8006C790:
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x2114
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt CardRW_Reprint_Page_L_8006C7D8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_Reprint_Page_L_8006C7D8:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x212c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x120
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_Reprint_Page_L_8006C7F8:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

