/* === extracted from auto_Backup_ClearHiScores_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8027B3F4();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1120;
extern unsigned int lbl_806D1128;
extern unsigned int lbl_806D2EB4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8031128C[];
extern unsigned int lbl_803FDF70[];
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x8007502C..0x800751F0) ---
 * [  0] 0x8007502C size:0x1C4   global Backup_ClearHiScores
 */

/* --- forward decls --- */
asm void Backup_ClearHiScores(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Backup_ClearHiScores[8] = {
    0x90, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Backup_ClearHiScores = {
    (void *)&Backup_ClearHiScores, 0x000001C4, (void *)extab_Backup_ClearHiScores
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Backup_ClearHiScores(void) { /* 0x8007502C size:0x1C4 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stmw r14, 0x18(r1)
    lbz r0, lbl_806D1120(r13)
    cmplwi r0, 0x0
    bne Backup_ClearHiScores_L_80075058
    li r3, 0x0
    b Backup_ClearHiScores_L_800751D4
    Backup_ClearHiScores_L_80075058:
    lwz r0, lbl_806D1128(r13)
    cmpwi r0, 0x0
    beq Backup_ClearHiScores_L_8007506C
    li r3, 0x0
    b Backup_ClearHiScores_L_800751D4
    Backup_ClearHiScores_L_8007506C:
    lis r3, lbl_80598A60@ha
    lis r4, lbl_803FDF70@ha
    addi r14, r3, lbl_80598A60@l
    lfs f31, lbl_806D2EB4(r2)
    addi r0, r4, lbl_803FDF70@l
    lis r3, lbl_8031128C@ha
    stw r0, 0x10(r1)
    addi r0, r3, lbl_8031128C@l
    stw r0, 0x14(r1)
    li r0, 0x0
    stw r14, 0xc(r1)
    stw r0, 0x8(r1)
    Backup_ClearHiScores_L_8007509C:
    lwz r22, 0xc(r1)
    mr r23, r14
    lwz r21, 0x10(r1)
    li r19, 0x0
    lwz r20, 0x14(r1)
    Backup_ClearHiScores_L_800750B0:
    mr r25, r23
    mr r24, r22
    li r18, 0x0
    Backup_ClearHiScores_L_800750BC:
    mr r27, r25
    mr r26, r24
    li r17, 0x0
    Backup_ClearHiScores_L_800750C8:
    addi r29, r26, 0x31e0
    addi r28, r27, 0x4e0
    li r16, 0x0
    Backup_ClearHiScores_L_800750D4:
    cmpwi r16, 0xa
    stfs f31, 0x0(r29)
    bge Backup_ClearHiScores_L_80075150
    li r31, 0x0
    mr r30, r28
    sth r31, 0x0(r28)
    li r15, 0x0
    sth r31, 0x2(r28)
    sth r31, 0x4(r28)
    sth r31, 0x6(r28)
    sth r31, 0x8(r28)
    sth r31, 0xa(r28)
    b Backup_ClearHiScores_L_80075120
    Backup_ClearHiScores_L_80075108:
    lwz r3, 0x0(r21)
    addi r15, r15, 0x1
    lhzx r0, r3, r31
    addi r31, r31, 0x2
    sth r0, 0x0(r30)
    addi r30, r30, 0x2
    Backup_ClearHiScores_L_80075120:
    lwz r3, 0x0(r21)
    bl fn_8027B3F4
    cmplw r15, r3
    bge Backup_ClearHiScores_L_80075138
    cmpwi r15, 0x5
    blt Backup_ClearHiScores_L_80075108
    Backup_ClearHiScores_L_80075138:
    lwz r3, 0x0(r20)
    li r0, 0x0
    stb r3, 0xc(r28)
    stb r0, 0xd(r28)
    stb r0, 0xe(r28)
    stb r0, 0xf(r28)
    Backup_ClearHiScores_L_80075150:
    addi r16, r16, 0x1
    addi r28, r28, 0x10
    cmpwi r16, 0x32
    addi r29, r29, 0x4
    blt Backup_ClearHiScores_L_800750D4
    addi r17, r17, 0x1
    addi r26, r26, 0xc8
    cmpwi r17, 0x2
    addi r27, r27, 0xa0
    blt Backup_ClearHiScores_L_800750C8
    addi r18, r18, 0x1
    addi r24, r24, 0x190
    cmpwi r18, 0x2
    addi r25, r25, 0x140
    blt Backup_ClearHiScores_L_800750BC
    addi r19, r19, 0x1
    addi r22, r22, 0x320
    cmpwi r19, 0x9
    addi r21, r21, 0x4
    addi r20, r20, 0x4
    addi r23, r23, 0x280
    blt Backup_ClearHiScores_L_800750B0
    lwz r3, 0x8(r1)
    addi r14, r14, 0x1680
    addi r3, r3, 0x1
    mr r0, r3
    stw r3, 0x8(r1)
    lwz r3, 0xc(r1)
    cmpwi r0, 0x2
    addi r3, r3, 0x1c20
    stw r3, 0xc(r1)
    blt Backup_ClearHiScores_L_8007509C
    li r3, 0x1
    Backup_ClearHiScores_L_800751D4:
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    lmw r14, 0x18(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

