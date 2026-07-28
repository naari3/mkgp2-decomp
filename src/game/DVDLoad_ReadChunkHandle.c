/* === extracted from auto_DVDLoad_ReadChunkHan_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DVDReadAsync();
extern void OSGetTick();
extern void fn_80297B98();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1140;
extern unsigned int lbl_806D1144;
extern unsigned int lbl_806D2238;

/* --- function index (1 fns, .text 0x8007E178..0x8007E28C) ---
 * [  0] 0x8007E178 size:0x114   global DVDLoad_ReadChunkHandle
 */

/* --- forward decls --- */
asm void DVDLoad_ReadChunkHandle(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_DVDLoad_ReadChunkHandle[8] = {
    0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_DVDLoad_ReadChunkHandle = {
    (void *)&DVDLoad_ReadChunkHandle, 0x00000114, (void *)extab_DVDLoad_ReadChunkHandle
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void DVDLoad_ReadChunkHandle(void) { /* 0x8007E178 size:0x114 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r24, 0x10(r1)
    mr r27, r3
    mr r28, r4
    mr r29, r5
    mr r30, r6
    mr r31, r7
    lwz r8, 0x30(r27)
    lwz r3, lbl_806D1140(r13)
    lwz r4, 0x34(r27)
    srwi r0, r8, 10
    cmplw r3, r0
    subi r24, r4, 0x1
    add r24, r8, r24
    bne DVDLoad_ReadChunkHandle_L_8007E1F4
    lis r3, 0x431c
    lis r26, 0x8000
    subi r25, r3, 0x217d
    DVDLoad_ReadChunkHandle_L_8007E1C8:
    bl OSGetTick
    lwz r0, 0xf8(r26)
    lwz r4, lbl_806D1144(r13)
    srwi r0, r0, 2
    mulhwu r0, r25, r0
    subf r3, r4, r3
    slwi r3, r3, 3
    srwi r0, r0, 15
    divwu r0, r3, r0
    cmplwi r0, 0x42
    blt DVDLoad_ReadChunkHandle_L_8007E1C8
    DVDLoad_ReadChunkHandle_L_8007E1F4:
    mr r3, r27
    mr r4, r28
    mr r5, r29
    mr r6, r30
    li r7, 0x0
    li r8, 0x2
    bl DVDReadAsync
    cmpwi r3, 0x0
    bne DVDLoad_ReadChunkHandle_L_8007E220
    li r3, 0x0
    b DVDLoad_ReadChunkHandle_L_8007E278
    DVDLoad_ReadChunkHandle_L_8007E220:
    li r25, 0x10
    b DVDLoad_ReadChunkHandle_L_8007E244
    DVDLoad_ReadChunkHandle_L_8007E228:
    subic. r25, r25, 0x1
    bge DVDLoad_ReadChunkHandle_L_8007E244
    lwz r12, lbl_806D2238(r13)
    mr r3, r31
    mtctr r12
    bctrl
    li r25, 0x10
    DVDLoad_ReadChunkHandle_L_8007E244:
    mr r3, r27
    bl fn_80297B98
    cmpwi r3, 0x1
    beq DVDLoad_ReadChunkHandle_L_8007E228
    lwz r12, lbl_806D2238(r13)
    mr r3, r31
    mtctr r12
    bctrl
    srwi r0, r24, 10
    stw r0, lbl_806D1140(r13)
    bl OSGetTick
    stw r3, lbl_806D1144(r13)
    li r3, 0x1
    DVDLoad_ReadChunkHandle_L_8007E278:
    lmw r24, 0x10(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

