/* === extracted from auto_KartDriver_New_Full_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DisplayStruct_Init();
extern void KartDriver_InitFull();

/* --- function index (1 fns, .text 0x80045E20..0x80045E88) ---
 * [  0] 0x80045E20 size:0x68    global KartDriver_New_Full
 */

/* --- forward decls --- */
asm void KartDriver_New_Full(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_New_Full[8] = {
    0x38, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_New_Full = {
    (void *)&KartDriver_New_Full, 0x00000068, (void *)extab_KartDriver_New_Full
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_New_Full(void) { /* 0x80045E20 size:0x68 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r25, 0x14(r1)
    mr r25, r3
    mr r26, r4
    mr r27, r5
    mr r28, r6
    mr r29, r7
    mr r30, r8
    mr r31, r9
    bl DisplayStruct_Init
    mr r3, r25
    mr r4, r26
    mr r5, r27
    mr r6, r28
    mr r7, r29
    mr r8, r30
    mr r9, r31
    bl KartDriver_InitFull
    mr r3, r25
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


