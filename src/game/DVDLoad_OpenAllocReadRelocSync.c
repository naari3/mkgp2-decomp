/* === extracted from auto_DVDLoad_OpenAllocRea_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DVDOpen();
extern void FUN_8007dfe4();
extern void fn_8029530C();
extern void fn_802DB304();
extern void fn_802DC964();
extern void memcpy();
extern void memset();
extern void strlen();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2238;

/* --- function index (1 fns, .text 0x8007DD00..0x8007DFD4) ---
 * [  0] 0x8007DD00 size:0x2D4   global DVDLoad_OpenAllocReadRelocSync
 */

/* --- forward decls --- */
asm void DVDLoad_OpenAllocReadRelocSync(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_DVDLoad_OpenAllocReadRelocSync[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_DVDLoad_OpenAllocReadRelocSync = {
    (void *)&DVDLoad_OpenAllocReadRelocSync, 0x000002D4, (void *)extab_DVDLoad_OpenAllocReadRelocSync
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void DVDLoad_OpenAllocReadRelocSync(void) { /* 0x8007DD00 size:0x2D4 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stmw r27, 0x4c(r1)
    mr r29, r3
    li r3, 0x0
    lwz r12, lbl_806D2238(r13)
    mtctr r12
    bctrl
    lwz r12, lbl_806D2238(r13)
    li r3, 0x1
    mtctr r12
    bctrl
    li r3, 0x44
    bl fn_802DB304
    mr. r31, r3
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    li r4, 0x0
    li r5, 0x44
    bl memset
    mr r3, r29
    mr r4, r31
    li r5, 0x20
    li r6, 0x0
    li r7, 0x2
    bl FUN_8007dfe4
    clrlwi. r0, r3, 24
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    mr r3, r29
    addi r4, r1, 0x8
    bl DVDOpen
    cmpwi r3, 0x0
    bne DVDLoad_OpenAllocReadRelocSync_L_8007DD8C
    li r3, 0x0
    b DVDLoad_OpenAllocReadRelocSync_L_8007DFC0
    DVDLoad_OpenAllocReadRelocSync_L_8007DD8C:
    lwz r27, 0x3c(r1)
    addi r3, r1, 0x8
    bl fn_8029530C
    lwz r0, 0x0(r31)
    cmplw r0, r27
    bne DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    lwz r27, 0x4(r31)
    addi r0, r27, 0x1f
    clrrwi r30, r0, 5
    mr r3, r30
    bl fn_802DB304
    stw r3, 0x20(r31)
    lwz r0, 0x20(r31)
    cmplwi r0, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    li r0, 0x0
    mr r3, r29
    stw r0, 0x40(r31)
    mr r5, r30
    li r6, 0x20
    li r7, 0x3
    lwz r4, 0x20(r31)
    bl FUN_8007dfe4
    clrlwi. r0, r3, 24
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    lwz r0, 0x8(r31)
    addi r30, r27, 0x20
    cmplwi r0, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DE44
    slwi r27, r0, 2
    addi r0, r27, 0x1f
    clrrwi r28, r0, 5
    mr r3, r28
    bl fn_802DB304
    stw r3, 0x24(r31)
    lwz r4, 0x24(r31)
    cmplwi r4, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    mr r3, r29
    mr r5, r28
    mr r6, r30
    li r7, 0x4
    bl FUN_8007dfe4
    clrlwi. r0, r3, 24
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    add r30, r30, r27
    DVDLoad_OpenAllocReadRelocSync_L_8007DE44:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DE94
    slwi r27, r0, 3
    addi r0, r27, 0x1f
    clrrwi r28, r0, 5
    mr r3, r28
    bl fn_802DB304
    stw r3, 0x28(r31)
    lwz r4, 0x28(r31)
    cmplwi r4, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    mr r3, r29
    mr r5, r28
    mr r6, r30
    li r7, 0x5
    bl FUN_8007dfe4
    clrlwi. r0, r3, 24
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    add r30, r30, r27
    DVDLoad_OpenAllocReadRelocSync_L_8007DE94:
    lwz r0, 0x10(r31)
    cmplwi r0, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DEE4
    slwi r27, r0, 3
    addi r0, r27, 0x1f
    clrrwi r28, r0, 5
    mr r3, r28
    bl fn_802DB304
    stw r3, 0x2c(r31)
    lwz r4, 0x2c(r31)
    cmplwi r4, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    mr r3, r29
    mr r5, r28
    mr r6, r30
    li r7, 0x6
    bl FUN_8007dfe4
    clrlwi. r0, r3, 24
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    add r30, r30, r27
    DVDLoad_OpenAllocReadRelocSync_L_8007DEE4:
    lwz r0, 0x0(r31)
    subf. r3, r30, r0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DF2C
    addi r0, r3, 0x1f
    clrrwi r28, r0, 5
    mr r3, r28
    bl fn_802DB304
    stw r3, 0x30(r31)
    lwz r4, 0x30(r31)
    cmplwi r4, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    mr r3, r29
    mr r5, r28
    mr r6, r30
    li r7, 0x7
    bl FUN_8007dfe4
    clrlwi. r0, r3, 24
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    DVDLoad_OpenAllocReadRelocSync_L_8007DF2C:
    mr r3, r29
    bl strlen
    mr r30, r3
    addi r3, r30, 0x1
    bl fn_802DB304
    stw r3, 0x38(r31)
    lwz r3, 0x38(r31)
    cmplwi r3, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFAC
    mr r4, r29
    addi r5, r30, 0x1
    bl memcpy
    li r4, 0x0
    mr r5, r4
    b DVDLoad_OpenAllocReadRelocSync_L_8007DF88
    DVDLoad_OpenAllocReadRelocSync_L_8007DF68:
    lwz r3, 0x24(r31)
    addi r4, r4, 0x1
    lwz r6, 0x20(r31)
    lwzx r3, r3, r5
    addi r5, r5, 0x4
    lwzx r0, r6, r3
    add r0, r0, r6
    stwx r0, r6, r3
    DVDLoad_OpenAllocReadRelocSync_L_8007DF88:
    lwz r0, 0x8(r31)
    cmplw r4, r0
    blt DVDLoad_OpenAllocReadRelocSync_L_8007DF68
    lwz r12, lbl_806D2238(r13)
    li r3, 0x8
    mtctr r12
    bctrl
    mr r3, r31
    b DVDLoad_OpenAllocReadRelocSync_L_8007DFC0
    DVDLoad_OpenAllocReadRelocSync_L_8007DFAC:
    cmplwi r31, 0x0
    beq DVDLoad_OpenAllocReadRelocSync_L_8007DFBC
    mr r3, r31
    bl fn_802DC964
    DVDLoad_OpenAllocReadRelocSync_L_8007DFBC:
    li r3, 0x0
    DVDLoad_OpenAllocReadRelocSync_L_8007DFC0:
    lmw r27, 0x4c(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

