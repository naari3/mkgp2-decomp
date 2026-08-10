/* === extracted from auto_CardTaskManager_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_Free();
extern void MemoryManager_TimedFree();

/* --- function index (1 fns, .text 0x80089FA4..0x8008A058) ---
 * [  0] 0x80089FA4 size:0xB4    global CardTaskManager_Dtor
 */

/* --- forward decls --- */
asm void CardTaskManager_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardTaskManager_Dtor[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardTaskManager_Dtor = {
    (void *)&CardTaskManager_Dtor, 0x000000B4, (void *)extab_CardTaskManager_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardTaskManager_Dtor(void) { /* 0x80089FA4 size:0xB4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr. r28, r3
    beq CardTaskManager_Dtor_L_8008A034
    lwz r0, 0x0(r28)
    cmplwi r0, 0x0
    beq CardTaskManager_Dtor_L_8008A01C
    li r30, 0x0
    li r31, 0x0
    b CardTaskManager_Dtor_L_8008A010
    CardTaskManager_Dtor_L_80089FE4:
    lwz r3, 0x0(r28)
    lwzx r3, r3, r31
    cmplwi r3, 0x0
    beq CardTaskManager_Dtor_L_8008A008
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    CardTaskManager_Dtor_L_8008A008:
    addi r31, r31, 0x8
    addi r30, r30, 0x1
    CardTaskManager_Dtor_L_8008A010:
    lwz r0, 0x4(r28)
    cmpw r30, r0
    blt CardTaskManager_Dtor_L_80089FE4
    CardTaskManager_Dtor_L_8008A01C:
    lwz r3, 0x0(r28)
    bl MemoryManager_Free
    extsh. r0, r29
    ble CardTaskManager_Dtor_L_8008A034
    mr r3, r28
    bl MemoryManager_TimedFree
    CardTaskManager_Dtor_L_8008A034:
    lwz r0, 0x24(r1)
    mr r3, r28
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
