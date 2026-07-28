/* === extracted from auto_GameSetting_Page_Var_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Backup_PublishShadowCopy_Inline();
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void PcbIdToIpAndModify();
extern void PcbSlot_GetByIndex();
extern void PcbSlot_IsReadyByIndex();
extern void PcbSync_CountJoinedPcbs();
extern void VBlankValue_Set();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FC444[];

/* --- function index (1 fns, .text 0x80072074..0x8007270C) ---
 * [  0] 0x80072074 size:0x698   global GameSetting_Page_VariantA
 */

/* --- forward decls --- */
asm void GameSetting_Page_VariantA(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GameSetting_Page_VariantA[8] = {
    0x30, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GameSetting_Page_VariantA = {
    (void *)&GameSetting_Page_VariantA, 0x00000698, (void *)extab_GameSetting_Page_VariantA
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GameSetting_Page_VariantA(void) { /* 0x80072074 size:0x698 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr. r29, r4
    lis r4, lbl_8030E598@ha
    mr r28, r3
    addi r31, r4, lbl_8030E598@l
    bne GameSetting_Page_VariantA_L_800720A0
    li r0, 0x6
    stw r0, 0x18(r28)
    GameSetting_Page_VariantA_L_800720A0:
    cmpwi r29, 0x1
    bne GameSetting_Page_VariantA_L_80072308
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r30, r3
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq GameSetting_Page_VariantA_L_8007211C
    li r0, 0x1f
    stw r0, 0x8(r28)
    lwz r3, 0x18(r28)
    addi r0, r3, 0x1
    cmpwi r0, 0x6
    stw r0, 0x18(r28)
    ble GameSetting_Page_VariantA_L_800720F8
    li r0, 0x0
    stw r0, 0x18(r28)
    GameSetting_Page_VariantA_L_800720F8:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    beq GameSetting_Page_VariantA_L_8007211C
    lwz r3, 0x18(r28)
    cmpwi r3, 0x4
    bne GameSetting_Page_VariantA_L_8007211C
    addi r0, r3, 0x1
    stw r0, 0x18(r28)
    GameSetting_Page_VariantA_L_8007211C:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    beq GameSetting_Page_VariantA_L_80072160
    li r3, 0x0
    bl PcbSlot_IsReadyByIndex
    clrlwi. r0, r3, 24
    beq GameSetting_Page_VariantA_L_80072160
    li r3, 0x0
    bl PcbSlot_GetByIndex
    lbz r0, 0x3(r3)
    lwz r3, 0x274(r28)
    clrlwi r4, r0, 31
    neg r0, r4
    or r0, r0, r4
    srwi r0, r0, 31
    stb r0, 0x29(r3)
    GameSetting_Page_VariantA_L_80072160:
    mr r3, r30
    li r4, 0x1000
    lwz r12, 0x0(r30)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq GameSetting_Page_VariantA_L_80072308
    lwz r0, 0x18(r28)
    cmpwi r0, 0x0
    bne GameSetting_Page_VariantA_L_800721B4
    lwz r4, 0x274(r28)
    lbz r3, 0x21(r4)
    addi r3, r3, 0x1
    extsb r0, r3
    stb r3, 0x21(r4)
    cmpwi r0, 0x4
    ble GameSetting_Page_VariantA_L_800721B4
    lwz r3, 0x274(r28)
    li r0, 0x1
    stb r0, 0x21(r3)
    GameSetting_Page_VariantA_L_800721B4:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantA_L_800721F0
    lwz r5, 0x274(r28)
    lis r3, 0x5555
    addi r0, r3, 0x5556
    lbz r3, 0x22(r5)
    extsb r3, r3
    addi r4, r3, 0x1
    mulhw r3, r0, r4
    srwi r0, r3, 31
    add r0, r3, r0
    mulli r0, r0, 0x3
    subf r0, r0, r4
    stb r0, 0x22(r5)
    GameSetting_Page_VariantA_L_800721F0:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x2
    bne GameSetting_Page_VariantA_L_80072220
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_80072218
    li r0, 0x0
    stb r0, 0x25(r3)
    b GameSetting_Page_VariantA_L_80072220
    GameSetting_Page_VariantA_L_80072218:
    li r0, 0x1
    stb r0, 0x25(r3)
    GameSetting_Page_VariantA_L_80072220:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x3
    bne GameSetting_Page_VariantA_L_80072250
    lwz r3, 0x274(r28)
    lbz r0, 0x26(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_80072248
    li r0, 0x0
    stb r0, 0x26(r3)
    b GameSetting_Page_VariantA_L_80072250
    GameSetting_Page_VariantA_L_80072248:
    li r0, 0x1
    stb r0, 0x26(r3)
    GameSetting_Page_VariantA_L_80072250:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x4
    bne GameSetting_Page_VariantA_L_80072280
    lwz r3, 0x274(r28)
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_80072278
    li r0, 0x0
    stb r0, 0x29(r3)
    b GameSetting_Page_VariantA_L_80072280
    GameSetting_Page_VariantA_L_80072278:
    li r0, 0x1
    stb r0, 0x29(r3)
    GameSetting_Page_VariantA_L_80072280:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x5
    bne GameSetting_Page_VariantA_L_800722D4
    lwz r4, 0x274(r28)
    lbz r0, 0x44(r4)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_800722CC
    lbz r0, 0x45(r4)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_800722B4
    li r0, 0x0
    stb r0, 0x45(r4)
    b GameSetting_Page_VariantA_L_800722D4
    GameSetting_Page_VariantA_L_800722B4:
    li r3, 0x0
    li r0, 0x1
    stb r3, 0x44(r4)
    lwz r3, 0x274(r28)
    stb r0, 0x45(r3)
    b GameSetting_Page_VariantA_L_800722D4
    GameSetting_Page_VariantA_L_800722CC:
    li r0, 0x1
    stb r0, 0x44(r4)
    GameSetting_Page_VariantA_L_800722D4:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x6
    bne GameSetting_Page_VariantA_L_80072308
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cntlzw r0, r0
    srwi r3, r0, 5
    bl VBlankValue_Set
    bl Backup_PublishShadowCopy_Inline
    li r3, 0x0
    bl PcbIdToIpAndModify
    li r0, 0x0
    stw r0, 0x10(r28)
    GameSetting_Page_VariantA_L_80072308:
    cmpwi r29, 0x2
    bne GameSetting_Page_VariantA_L_800726F4
    bl PcbSync_CountJoinedPcbs
    lwz r5, 0x18(r28)
    lis r4, lbl_803FC444@ha
    li r29, 0x0
    mr r26, r3
    addi r27, r4, lbl_803FC444@l
    addi r30, r5, 0x3
    b GameSetting_Page_VariantA_L_80072378
    GameSetting_Page_VariantA_L_80072330:
    cmpw r29, r30
    bne GameSetting_Page_VariantA_L_80072344
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_VariantA_L_80072370
    GameSetting_Page_VariantA_L_80072344:
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq GameSetting_Page_VariantA_L_80072370
    lwz r4, 0x0(r27)
    li r6, 0x7
    lwz r0, 0x4(r27)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_80072370:
    addi r27, r27, 0xc
    addi r29, r29, 0x1
    GameSetting_Page_VariantA_L_80072378:
    lwz r7, 0x8(r27)
    cmplwi r7, 0x0
    bne GameSetting_Page_VariantA_L_80072330
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq GameSetting_Page_VariantA_L_800726F4
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x16c
    li r5, 0x30
    li r6, 0x2
    addi r7, r2, -0x74BC  /* lbl_806D2DA4 */
    creqv 6, 6, 6
    bl DrawText
    cmpwi r26, 0x1
    bgt GameSetting_Page_VariantA_L_800723D8
    lwz r3, 0x270(r28)
    li r4, 0x150
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x60
    li r6, 0x7
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_800723FC
    GameSetting_Page_VariantA_L_800723D8:
    lwz r3, 0x270(r28)
    mr r8, r26
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x150
    li r5, 0x60
    li r6, 0x7
    addi r7, r2, -0x73F0  /* lbl_806D2E70 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_800723FC:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    extsb r8, r0
    cmpwi r8, 0x1
    bne GameSetting_Page_VariantA_L_80072434
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x90
    li r6, 0x2
    addi r7, r2, -0x7494  /* lbl_806D2DCC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_80072454
    GameSetting_Page_VariantA_L_80072434:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x90
    li r6, 0x4
    addi r7, r2, -0x7494  /* lbl_806D2DCC */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_80072454:
    lwz r3, 0x274(r28)
    lbz r3, 0x22(r3)
    extsb. r0, r3
    bne GameSetting_Page_VariantA_L_80072488
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xc0
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_800724D8
    GameSetting_Page_VariantA_L_80072488:
    extsb r0, r3
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantA_L_800724B8
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2708
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xc0
    li r6, 0x4
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_800724D8
    GameSetting_Page_VariantA_L_800724B8:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2714
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xc0
    li r6, 0x2
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_800724D8:
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_8007250C
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xd8
    li r6, 0x2
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_8007252C
    GameSetting_Page_VariantA_L_8007250C:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xd8
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_8007252C:
    lwz r3, 0x274(r28)
    lbz r0, 0x26(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_80072560
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xf0
    li r6, 0x4
    addi r7, r2, -0x73E8  /* lbl_806D2E78 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_80072580
    GameSetting_Page_VariantA_L_80072560:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xf0
    li r6, 0x2
    addi r7, r2, -0x73E0  /* lbl_806D2E80 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_80072580:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantA_L_80072620
    lwz r0, 0x18(r28)
    cmpwi r0, 0x4
    bne GameSetting_Page_VariantA_L_800725A8
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_VariantA_L_800725C8
    GameSetting_Page_VariantA_L_800725A8:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2720
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_800725C8:
    lwz r3, 0x274(r28)
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_800725FC
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x108
    li r6, 0x4
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_80072670
    GameSetting_Page_VariantA_L_800725FC:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x108
    li r6, 0x2
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_80072670
    GameSetting_Page_VariantA_L_80072620:
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_80072650
    lwz r3, 0x270(r28)
    addi r7, r31, 0x272c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x108
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_80072670
    GameSetting_Page_VariantA_L_80072650:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2748
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x108
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_80072670:
    lwz r3, 0x274(r28)
    lbz r0, 0x44(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_800726D4
    lbz r0, 0x45(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantA_L_800726B0
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2764
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0x120
    li r6, 0x2
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_800726F4
    GameSetting_Page_VariantA_L_800726B0:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x120
    li r6, 0x4
    addi r7, r2, -0x73DC  /* lbl_806D2E84 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantA_L_800726F4
    GameSetting_Page_VariantA_L_800726D4:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x120
    li r6, 0x4
    addi r7, r2, -0x7410  /* lbl_806D2E50 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantA_L_800726F4:
    lmw r26, 0x8(r1)
    li r3, 0x1
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

/* === extracted from auto_GameSetting_Page_Var_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Backup_PublishShadowCopy_Inline();
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void PcbIdToIpAndModify();
extern void PcbSlot_GetByIndex();
extern void PcbSlot_IsReadyByIndex();
extern void PcbSync_CountJoinedPcbs();
extern void ServiceEnable_Set();
extern void ServiceValue_Set();
extern void VBlankValue_Set();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FC2D0[];

/* --- function index (1 fns, .text 0x8007270C..0x8007307C) ---
 * [  0] 0x8007270C size:0x970   global GameSetting_Page_VariantB
 */

/* --- forward decls --- */
asm void GameSetting_Page_VariantB(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GameSetting_Page_VariantB[8] = {
    0x30, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GameSetting_Page_VariantB = {
    (void *)&GameSetting_Page_VariantB, 0x00000970, (void *)extab_GameSetting_Page_VariantB
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GameSetting_Page_VariantB(void) { /* 0x8007270C size:0x970 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr. r29, r4
    lis r4, lbl_8030E598@ha
    mr r28, r3
    addi r31, r4, lbl_8030E598@l
    bne GameSetting_Page_VariantB_L_80072738
    li r0, 0x8
    stw r0, 0x18(r28)
    GameSetting_Page_VariantB_L_80072738:
    cmpwi r29, 0x1
    bne GameSetting_Page_VariantB_L_80072A98
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r30, r3
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq GameSetting_Page_VariantB_L_800727FC
    li r0, 0x1f
    stw r0, 0x8(r28)
    lwz r3, 0x18(r28)
    addi r0, r3, 0x1
    cmpwi r0, 0x8
    stw r0, 0x18(r28)
    ble GameSetting_Page_VariantB_L_80072790
    li r0, 0x0
    stw r0, 0x18(r28)
    GameSetting_Page_VariantB_L_80072790:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    beq GameSetting_Page_VariantB_L_800727B4
    lwz r3, 0x18(r28)
    cmpwi r3, 0x1
    bne GameSetting_Page_VariantB_L_800727B4
    addi r0, r3, 0x1
    stw r0, 0x18(r28)
    GameSetting_Page_VariantB_L_800727B4:
    lwz r3, 0x274(r28)
    lbz r0, 0x23(r3)
    cmplwi r0, 0x0
    bne GameSetting_Page_VariantB_L_800727D8
    lwz r3, 0x18(r28)
    cmpwi r3, 0x2
    bne GameSetting_Page_VariantB_L_800727D8
    addi r0, r3, 0x1
    stw r0, 0x18(r28)
    GameSetting_Page_VariantB_L_800727D8:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    beq GameSetting_Page_VariantB_L_800727FC
    lwz r3, 0x18(r28)
    cmpwi r3, 0x6
    bne GameSetting_Page_VariantB_L_800727FC
    addi r0, r3, 0x1
    stw r0, 0x18(r28)
    GameSetting_Page_VariantB_L_800727FC:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    beq GameSetting_Page_VariantB_L_80072864
    li r3, 0x0
    bl PcbSlot_IsReadyByIndex
    clrlwi. r0, r3, 24
    beq GameSetting_Page_VariantB_L_80072864
    li r3, 0x0
    bl PcbSlot_GetByIndex
    lbz r0, 0x3(r3)
    li r3, 0x0
    lwz r4, 0x274(r28)
    extrwi r5, r0, 1, 27
    neg r0, r5
    or r0, r0, r5
    srwi r0, r0, 31
    stb r0, 0x23(r4)
    bl PcbSlot_GetByIndex
    lbz r0, 0x3(r3)
    lwz r3, 0x274(r28)
    clrlwi r4, r0, 31
    neg r0, r4
    or r0, r0, r4
    srwi r0, r0, 31
    stb r0, 0x29(r3)
    GameSetting_Page_VariantB_L_80072864:
    mr r3, r30
    li r4, 0x1000
    lwz r12, 0x0(r30)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq GameSetting_Page_VariantB_L_80072A98
    lwz r0, 0x18(r28)
    cmpwi r0, 0x0
    bne GameSetting_Page_VariantB_L_800728B8
    lwz r4, 0x274(r28)
    lbz r3, 0x21(r4)
    addi r3, r3, 0x1
    extsb r0, r3
    stb r3, 0x21(r4)
    cmpwi r0, 0x4
    ble GameSetting_Page_VariantB_L_800728B8
    lwz r3, 0x274(r28)
    li r0, 0x1
    stb r0, 0x21(r3)
    GameSetting_Page_VariantB_L_800728B8:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantB_L_800728F4
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantB_L_800728F4
    lbz r0, 0x23(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_800728EC
    li r0, 0x0
    stb r0, 0x23(r3)
    b GameSetting_Page_VariantB_L_800728F4
    GameSetting_Page_VariantB_L_800728EC:
    li r0, 0x1
    stb r0, 0x23(r3)
    GameSetting_Page_VariantB_L_800728F4:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x2
    bne GameSetting_Page_VariantB_L_80072924
    lwz r3, 0x274(r28)
    lbz r0, 0x24(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_8007291C
    li r0, 0x0
    stb r0, 0x24(r3)
    b GameSetting_Page_VariantB_L_80072924
    GameSetting_Page_VariantB_L_8007291C:
    li r0, 0x1
    stb r0, 0x24(r3)
    GameSetting_Page_VariantB_L_80072924:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x3
    bne GameSetting_Page_VariantB_L_80072960
    lwz r5, 0x274(r28)
    lis r3, 0x5555
    addi r0, r3, 0x5556
    lbz r3, 0x22(r5)
    extsb r3, r3
    addi r4, r3, 0x1
    mulhw r3, r0, r4
    srwi r0, r3, 31
    add r0, r3, r0
    mulli r0, r0, 0x3
    subf r0, r0, r4
    stb r0, 0x22(r5)
    GameSetting_Page_VariantB_L_80072960:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x4
    bne GameSetting_Page_VariantB_L_80072990
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072988
    li r0, 0x0
    stb r0, 0x25(r3)
    b GameSetting_Page_VariantB_L_80072990
    GameSetting_Page_VariantB_L_80072988:
    li r0, 0x1
    stb r0, 0x25(r3)
    GameSetting_Page_VariantB_L_80072990:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x5
    bne GameSetting_Page_VariantB_L_800729C0
    lwz r3, 0x274(r28)
    lbz r0, 0x26(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_800729B8
    li r0, 0x0
    stb r0, 0x26(r3)
    b GameSetting_Page_VariantB_L_800729C0
    GameSetting_Page_VariantB_L_800729B8:
    li r0, 0x1
    stb r0, 0x26(r3)
    GameSetting_Page_VariantB_L_800729C0:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x6
    bne GameSetting_Page_VariantB_L_800729F0
    lwz r3, 0x274(r28)
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_800729E8
    li r0, 0x0
    stb r0, 0x29(r3)
    b GameSetting_Page_VariantB_L_800729F0
    GameSetting_Page_VariantB_L_800729E8:
    li r0, 0x1
    stb r0, 0x29(r3)
    GameSetting_Page_VariantB_L_800729F0:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x7
    bne GameSetting_Page_VariantB_L_80072A44
    lwz r4, 0x274(r28)
    lbz r0, 0x44(r4)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072A3C
    lbz r0, 0x45(r4)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072A24
    li r0, 0x0
    stb r0, 0x45(r4)
    b GameSetting_Page_VariantB_L_80072A44
    GameSetting_Page_VariantB_L_80072A24:
    li r3, 0x0
    li r0, 0x1
    stb r3, 0x44(r4)
    lwz r3, 0x274(r28)
    stb r0, 0x45(r3)
    b GameSetting_Page_VariantB_L_80072A44
    GameSetting_Page_VariantB_L_80072A3C:
    li r0, 0x1
    stb r0, 0x44(r4)
    GameSetting_Page_VariantB_L_80072A44:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x8
    bne GameSetting_Page_VariantB_L_80072A98
    lwz r3, 0x274(r28)
    lbz r3, 0x23(r3)
    bl ServiceEnable_Set
    lwz r3, 0x274(r28)
    lbz r0, 0x24(r3)
    cntlzw r0, r0
    srwi r3, r0, 5
    bl ServiceValue_Set
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cntlzw r0, r0
    srwi r3, r0, 5
    bl VBlankValue_Set
    bl Backup_PublishShadowCopy_Inline
    li r3, 0x0
    bl PcbIdToIpAndModify
    li r0, 0x0
    stw r0, 0x10(r28)
    GameSetting_Page_VariantB_L_80072A98:
    cmpwi r29, 0x2
    bne GameSetting_Page_VariantB_L_80073064
    bl PcbSync_CountJoinedPcbs
    lwz r5, 0x18(r28)
    lis r4, lbl_803FC2D0@ha
    li r29, 0x0
    mr r26, r3
    addi r27, r4, lbl_803FC2D0@l
    addi r30, r5, 0x3
    b GameSetting_Page_VariantB_L_80072B08
    GameSetting_Page_VariantB_L_80072AC0:
    cmpw r29, r30
    bne GameSetting_Page_VariantB_L_80072AD4
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_VariantB_L_80072B00
    GameSetting_Page_VariantB_L_80072AD4:
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq GameSetting_Page_VariantB_L_80072B00
    lwz r4, 0x0(r27)
    li r6, 0x7
    lwz r0, 0x4(r27)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072B00:
    addi r27, r27, 0xc
    addi r29, r29, 0x1
    GameSetting_Page_VariantB_L_80072B08:
    lwz r7, 0x8(r27)
    cmplwi r7, 0x0
    bne GameSetting_Page_VariantB_L_80072AC0
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq GameSetting_Page_VariantB_L_80073064
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x16c
    li r5, 0x30
    li r6, 0x2
    addi r7, r2, -0x74BC  /* lbl_806D2DA4 */
    creqv 6, 6, 6
    bl DrawText
    cmpwi r26, 0x1
    bgt GameSetting_Page_VariantB_L_80072B68
    lwz r3, 0x270(r28)
    li r4, 0x150
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x60
    li r6, 0x7
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072B8C
    GameSetting_Page_VariantB_L_80072B68:
    lwz r3, 0x270(r28)
    mr r8, r26
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x150
    li r5, 0x60
    li r6, 0x7
    addi r7, r2, -0x73F0  /* lbl_806D2E70 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072B8C:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    extsb r8, r0
    cmpwi r8, 0x1
    bne GameSetting_Page_VariantB_L_80072BC4
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x90
    li r6, 0x2
    addi r7, r2, -0x7494  /* lbl_806D2DCC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072BE4
    GameSetting_Page_VariantB_L_80072BC4:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x90
    li r6, 0x4
    addi r7, r2, -0x7494  /* lbl_806D2DCC */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072BE4:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantB_L_80072C84
    lwz r0, 0x18(r28)
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantB_L_80072C0C
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_VariantB_L_80072C2C
    GameSetting_Page_VariantB_L_80072C0C:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2770
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072C2C:
    lwz r3, 0x274(r28)
    lbz r0, 0x23(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072C60
    lwz r3, 0x270(r28)
    addi r7, r31, 0x277c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xc0
    li r6, 0x2
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072CD4
    GameSetting_Page_VariantB_L_80072C60:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2788
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xc0
    li r6, 0x4
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072CD4
    GameSetting_Page_VariantB_L_80072C84:
    lbz r0, 0x23(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072CB4
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2798
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xc0
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072CD4
    GameSetting_Page_VariantB_L_80072CB4:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x27b8
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xc0
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072CD4:
    lwz r3, 0x274(r28)
    lbz r0, 0x23(r3)
    cmplwi r0, 0x1
    bne GameSetting_Page_VariantB_L_80072D74
    lwz r0, 0x18(r28)
    cmpwi r0, 0x2
    bne GameSetting_Page_VariantB_L_80072CFC
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_VariantB_L_80072D1C
    GameSetting_Page_VariantB_L_80072CFC:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x27dc
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072D1C:
    lwz r3, 0x274(r28)
    lbz r0, 0x24(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072D50
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xd8
    li r6, 0x2
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072DC4
    GameSetting_Page_VariantB_L_80072D50:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xd8
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072DC4
    GameSetting_Page_VariantB_L_80072D74:
    lbz r0, 0x24(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072DA4
    lwz r3, 0x270(r28)
    addi r7, r31, 0x27e8
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xd8
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072DC4
    GameSetting_Page_VariantB_L_80072DA4:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2804
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xd8
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072DC4:
    lwz r3, 0x274(r28)
    lbz r3, 0x22(r3)
    extsb. r0, r3
    bne GameSetting_Page_VariantB_L_80072DF8
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xf0
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072E48
    GameSetting_Page_VariantB_L_80072DF8:
    extsb r0, r3
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantB_L_80072E28
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2708
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xf0
    li r6, 0x4
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072E48
    GameSetting_Page_VariantB_L_80072E28:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2714
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xf0
    li r6, 0x2
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072E48:
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072E7C
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x108
    li r6, 0x2
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072E9C
    GameSetting_Page_VariantB_L_80072E7C:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x108
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072E9C:
    lwz r3, 0x274(r28)
    lbz r0, 0x26(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072ED0
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x120
    li r6, 0x2
    addi r7, r2, -0x73E8  /* lbl_806D2E78 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072EF0
    GameSetting_Page_VariantB_L_80072ED0:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x120
    li r6, 0x4
    addi r7, r2, -0x73E0  /* lbl_806D2E80 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072EF0:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    bne GameSetting_Page_VariantB_L_80072F90
    lwz r0, 0x18(r28)
    cmpwi r0, 0x6
    bne GameSetting_Page_VariantB_L_80072F18
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_VariantB_L_80072F38
    GameSetting_Page_VariantB_L_80072F18:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2720
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x138
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072F38:
    lwz r3, 0x274(r28)
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072F6C
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x138
    li r6, 0x4
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072FE0
    GameSetting_Page_VariantB_L_80072F6C:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x138
    li r6, 0x2
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072FE0
    GameSetting_Page_VariantB_L_80072F90:
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80072FC0
    lwz r3, 0x270(r28)
    addi r7, r31, 0x272c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x138
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80072FE0
    GameSetting_Page_VariantB_L_80072FC0:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2748
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x138
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80072FE0:
    lwz r3, 0x274(r28)
    lbz r0, 0x44(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80073044
    lbz r0, 0x45(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_VariantB_L_80073020
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2764
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0x150
    li r6, 0x2
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80073064
    GameSetting_Page_VariantB_L_80073020:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x150
    li r6, 0x4
    addi r7, r2, -0x73DC  /* lbl_806D2E84 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_VariantB_L_80073064
    GameSetting_Page_VariantB_L_80073044:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x150
    li r6, 0x4
    addi r7, r2, -0x7410  /* lbl_806D2E50 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_VariantB_L_80073064:
    lmw r26, 0x8(r1)
    li r3, 0x1
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

/* === extracted from auto_GameSetting_Page_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Backup_PublishShadowCopy_Inline();
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void PcbIdToIpAndModify();
extern void PcbSlot_GetByIndex();
extern void PcbSlot_IsReadyByIndex();
extern void PcbSync_CountJoinedPcbs();
extern void ServiceEnable_Set();
extern void ServiceValue_Set();
extern void VBlankValue_Set();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8030E598[];
extern unsigned int lbl_803FC174[];

/* --- function index (1 fns, .text 0x8007307C..0x80073878) ---
 * [  0] 0x8007307C size:0x7FC   global GameSetting_Page
 */

/* --- forward decls --- */
asm void GameSetting_Page(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GameSetting_Page[8] = {
    0x30, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GameSetting_Page = {
    (void *)&GameSetting_Page, 0x000007FC, (void *)extab_GameSetting_Page
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GameSetting_Page(void) { /* 0x8007307C size:0x7FC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr. r29, r4
    lis r4, lbl_8030E598@ha
    mr r28, r3
    addi r31, r4, lbl_8030E598@l
    bne GameSetting_Page_L_800730A8
    li r0, 0x7
    stw r0, 0x18(r28)
    GameSetting_Page_L_800730A8:
    cmpwi r29, 0x1
    bne GameSetting_Page_L_80073384
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r30, r3
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq GameSetting_Page_L_80073124
    li r0, 0x1f
    stw r0, 0x8(r28)
    lwz r3, 0x18(r28)
    addi r0, r3, 0x1
    cmpwi r0, 0x7
    stw r0, 0x18(r28)
    ble GameSetting_Page_L_80073100
    li r0, 0x0
    stw r0, 0x18(r28)
    GameSetting_Page_L_80073100:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    beq GameSetting_Page_L_80073124
    lwz r3, 0x18(r28)
    cmpwi r3, 0x5
    bne GameSetting_Page_L_80073124
    addi r0, r3, 0x1
    stw r0, 0x18(r28)
    GameSetting_Page_L_80073124:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    beq GameSetting_Page_L_8007318C
    li r3, 0x0
    bl PcbSlot_IsReadyByIndex
    clrlwi. r0, r3, 24
    beq GameSetting_Page_L_8007318C
    li r3, 0x0
    bl PcbSlot_GetByIndex
    lbz r0, 0x3(r3)
    li r3, 0x0
    lwz r4, 0x274(r28)
    extrwi r5, r0, 1, 27
    neg r0, r5
    or r0, r0, r5
    srwi r0, r0, 31
    stb r0, 0x23(r4)
    bl PcbSlot_GetByIndex
    lbz r0, 0x3(r3)
    lwz r3, 0x274(r28)
    clrlwi r4, r0, 31
    neg r0, r4
    or r0, r0, r4
    srwi r0, r0, 31
    stb r0, 0x29(r3)
    GameSetting_Page_L_8007318C:
    mr r3, r30
    li r4, 0x1000
    lwz r12, 0x0(r30)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq GameSetting_Page_L_80073384
    lwz r0, 0x18(r28)
    cmpwi r0, 0x0
    bne GameSetting_Page_L_800731E0
    lwz r4, 0x274(r28)
    lbz r3, 0x21(r4)
    addi r3, r3, 0x1
    extsb r0, r3
    stb r3, 0x21(r4)
    cmpwi r0, 0x4
    ble GameSetting_Page_L_800731E0
    lwz r3, 0x274(r28)
    li r0, 0x1
    stb r0, 0x21(r3)
    GameSetting_Page_L_800731E0:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x1
    bne GameSetting_Page_L_80073210
    lwz r3, 0x274(r28)
    lbz r0, 0x24(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_80073208
    li r0, 0x0
    stb r0, 0x24(r3)
    b GameSetting_Page_L_80073210
    GameSetting_Page_L_80073208:
    li r0, 0x1
    stb r0, 0x24(r3)
    GameSetting_Page_L_80073210:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x2
    bne GameSetting_Page_L_8007324C
    lwz r5, 0x274(r28)
    lis r3, 0x5555
    addi r0, r3, 0x5556
    lbz r3, 0x22(r5)
    extsb r3, r3
    addi r4, r3, 0x1
    mulhw r3, r0, r4
    srwi r0, r3, 31
    add r0, r3, r0
    mulli r0, r0, 0x3
    subf r0, r0, r4
    stb r0, 0x22(r5)
    GameSetting_Page_L_8007324C:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x3
    bne GameSetting_Page_L_8007327C
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_80073274
    li r0, 0x0
    stb r0, 0x25(r3)
    b GameSetting_Page_L_8007327C
    GameSetting_Page_L_80073274:
    li r0, 0x1
    stb r0, 0x25(r3)
    GameSetting_Page_L_8007327C:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x4
    bne GameSetting_Page_L_800732AC
    lwz r3, 0x274(r28)
    lbz r0, 0x27(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_800732A4
    li r0, 0x0
    stb r0, 0x27(r3)
    b GameSetting_Page_L_800732AC
    GameSetting_Page_L_800732A4:
    li r0, 0x1
    stb r0, 0x27(r3)
    GameSetting_Page_L_800732AC:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x5
    bne GameSetting_Page_L_800732DC
    lwz r3, 0x274(r28)
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_800732D4
    li r0, 0x0
    stb r0, 0x29(r3)
    b GameSetting_Page_L_800732DC
    GameSetting_Page_L_800732D4:
    li r0, 0x1
    stb r0, 0x29(r3)
    GameSetting_Page_L_800732DC:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x6
    bne GameSetting_Page_L_80073330
    lwz r4, 0x274(r28)
    lbz r0, 0x44(r4)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_80073328
    lbz r0, 0x45(r4)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_80073310
    li r0, 0x0
    stb r0, 0x45(r4)
    b GameSetting_Page_L_80073330
    GameSetting_Page_L_80073310:
    li r3, 0x0
    li r0, 0x1
    stb r3, 0x44(r4)
    lwz r3, 0x274(r28)
    stb r0, 0x45(r3)
    b GameSetting_Page_L_80073330
    GameSetting_Page_L_80073328:
    li r0, 0x1
    stb r0, 0x44(r4)
    GameSetting_Page_L_80073330:
    lwz r0, 0x18(r28)
    cmpwi r0, 0x7
    bne GameSetting_Page_L_80073384
    lwz r3, 0x274(r28)
    lbz r3, 0x23(r3)
    bl ServiceEnable_Set
    lwz r3, 0x274(r28)
    lbz r0, 0x24(r3)
    cntlzw r0, r0
    srwi r3, r0, 5
    bl ServiceValue_Set
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cntlzw r0, r0
    srwi r3, r0, 5
    bl VBlankValue_Set
    bl Backup_PublishShadowCopy_Inline
    li r3, 0x0
    bl PcbIdToIpAndModify
    li r0, 0x0
    stw r0, 0x10(r28)
    GameSetting_Page_L_80073384:
    cmpwi r29, 0x2
    bne GameSetting_Page_L_80073860
    bl PcbSync_CountJoinedPcbs
    lwz r5, 0x18(r28)
    lis r4, lbl_803FC174@ha
    li r29, 0x0
    mr r26, r3
    addi r27, r4, lbl_803FC174@l
    addi r30, r5, 0x3
    b GameSetting_Page_L_800733F4
    GameSetting_Page_L_800733AC:
    cmpw r29, r30
    bne GameSetting_Page_L_800733C0
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_L_800733EC
    GameSetting_Page_L_800733C0:
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq GameSetting_Page_L_800733EC
    lwz r4, 0x0(r27)
    li r6, 0x7
    lwz r0, 0x4(r27)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_800733EC:
    addi r27, r27, 0xc
    addi r29, r29, 0x1
    GameSetting_Page_L_800733F4:
    lwz r7, 0x8(r27)
    cmplwi r7, 0x0
    bne GameSetting_Page_L_800733AC
    lwz r3, 0x270(r28)
    cmplwi r3, 0x0
    beq GameSetting_Page_L_80073860
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x16c
    li r5, 0x30
    li r6, 0x2
    addi r7, r2, -0x74BC  /* lbl_806D2DA4 */
    creqv 6, 6, 6
    bl DrawText
    cmpwi r26, 0x1
    bgt GameSetting_Page_L_80073454
    lwz r3, 0x270(r28)
    li r4, 0x150
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x60
    li r6, 0x7
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_80073478
    GameSetting_Page_L_80073454:
    lwz r3, 0x270(r28)
    mr r8, r26
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x150
    li r5, 0x60
    li r6, 0x7
    addi r7, r2, -0x73F0  /* lbl_806D2E70 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_80073478:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    extsb r8, r0
    cmpwi r8, 0x1
    bne GameSetting_Page_L_800734B0
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x90
    li r6, 0x2
    addi r7, r2, -0x7494  /* lbl_806D2DCC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800734D0
    GameSetting_Page_L_800734B0:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x90
    li r6, 0x4
    addi r7, r2, -0x7494  /* lbl_806D2DCC */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_800734D0:
    lwz r3, 0x274(r28)
    lbz r0, 0x23(r3)
    cmplwi r0, 0x1
    bne GameSetting_Page_L_80073570
    lwz r0, 0x18(r28)
    cmpwi r0, 0x1
    bne GameSetting_Page_L_800734F8
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_L_80073518
    GameSetting_Page_L_800734F8:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x27dc
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xc0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_80073518:
    lwz r3, 0x274(r28)
    lbz r0, 0x24(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_8007354C
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xc0
    li r6, 0x2
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800735C0
    GameSetting_Page_L_8007354C:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xc0
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800735C0
    GameSetting_Page_L_80073570:
    lbz r0, 0x24(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_800735A0
    lwz r3, 0x270(r28)
    addi r7, r31, 0x27e8
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xc0
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800735C0
    GameSetting_Page_L_800735A0:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2804
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0xc0
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_800735C0:
    lwz r3, 0x274(r28)
    lbz r3, 0x22(r3)
    extsb. r0, r3
    bne GameSetting_Page_L_800735F4
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xd8
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_80073644
    GameSetting_Page_L_800735F4:
    extsb r0, r3
    cmpwi r0, 0x1
    bne GameSetting_Page_L_80073624
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2708
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xd8
    li r6, 0x4
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_80073644
    GameSetting_Page_L_80073624:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2714
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0xd8
    li r6, 0x2
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_80073644:
    lwz r3, 0x274(r28)
    lbz r0, 0x25(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_80073678
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xf0
    li r6, 0x2
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_80073698
    GameSetting_Page_L_80073678:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0xf0
    li r6, 0x4
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_80073698:
    lwz r3, 0x274(r28)
    lbz r0, 0x27(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_800736CC
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x108
    li r6, 0x2
    addi r7, r2, -0x73D4  /* lbl_806D2E8C */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800736EC
    GameSetting_Page_L_800736CC:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x108
    li r6, 0x4
    addi r7, r2, -0x73CC  /* lbl_806D2E94 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_800736EC:
    lwz r3, 0x274(r28)
    lbz r0, 0x21(r3)
    cmpwi r0, 0x1
    bne GameSetting_Page_L_8007378C
    lwz r0, 0x18(r28)
    cmpwi r0, 0x5
    bne GameSetting_Page_L_80073714
    lwz r0, 0x8(r28)
    cmpwi r0, 0x1e
    bgt GameSetting_Page_L_80073734
    GameSetting_Page_L_80073714:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2720
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x120
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_80073734:
    lwz r3, 0x274(r28)
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_80073768
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x120
    li r6, 0x4
    addi r7, r2, -0x74B4  /* lbl_806D2DAC */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800737DC
    GameSetting_Page_L_80073768:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x120
    li r6, 0x2
    addi r7, r2, -0x74CC  /* lbl_806D2D94 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800737DC
    GameSetting_Page_L_8007378C:
    lbz r0, 0x29(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_800737BC
    lwz r3, 0x270(r28)
    addi r7, r31, 0x272c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x120
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_800737DC
    GameSetting_Page_L_800737BC:
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2748
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x2a
    li r5, 0x120
    li r6, 0x3
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_800737DC:
    lwz r3, 0x274(r28)
    lbz r0, 0x44(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_80073840
    lbz r0, 0x45(r3)
    cmplwi r0, 0x0
    beq GameSetting_Page_L_8007381C
    lwz r3, 0x270(r28)
    addi r7, r31, 0x2764
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x15e
    li r5, 0x138
    li r6, 0x2
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_80073860
    GameSetting_Page_L_8007381C:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x138
    li r6, 0x4
    addi r7, r2, -0x73DC  /* lbl_806D2E84 */
    creqv 6, 6, 6
    bl DrawText
    b GameSetting_Page_L_80073860
    GameSetting_Page_L_80073840:
    lwz r3, 0x270(r28)
    li r4, 0x15e
    lfs f1, lbl_806D2D44(r2)
    li r5, 0x138
    li r6, 0x4
    addi r7, r2, -0x7410  /* lbl_806D2E50 */
    creqv 6, 6, 6
    bl DrawText
    GameSetting_Page_L_80073860:
    lmw r26, 0x8(r1)
    li r3, 0x1
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
