/* === extracted from auto_Jyugemu_Flag_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();
extern void Object_DtorWithGXSync();

/* --- function index (1 fns, .text 0x80080A14..0x80080A74) ---
 * [  0] 0x80080A14 size:0x60    global Jyugemu_Flag_Dtor
 */

/* --- forward decls --- */
asm void Jyugemu_Flag_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Jyugemu_Flag_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Jyugemu_Flag_Dtor = {
    (void *)&Jyugemu_Flag_Dtor, 0x00000060, (void *)extab_Jyugemu_Flag_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Jyugemu_Flag_Dtor(void) { /* 0x80080A14 size:0x60 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq Jyugemu_Flag_Dtor_L_80080A58
    lwz r3, 0x0(r30)
    li r4, 0x1
    bl Object_DtorWithGXSync
    li r3, 0x0
    extsh. r0, r31
    stw r3, 0x0(r30)
    ble Jyugemu_Flag_Dtor_L_80080A58
    mr r3, r30
    bl MemoryManager_TimedFree
    Jyugemu_Flag_Dtor_L_80080A58:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

