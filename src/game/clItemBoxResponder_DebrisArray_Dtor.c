/* === extracted from auto_clItemBoxResponder_D_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();
extern void fn_80270CF4();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int clItemBoxResponder_DebrisParticle_Dtor[];

/* --- function index (1 fns, .text 0x8005D954..0x8005D9D4) ---
 * [  0] 0x8005D954 size:0x80    global clItemBoxResponder_DebrisArray_Dtor
 */

/* --- forward decls --- */
asm void clItemBoxResponder_DebrisArray_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBoxResponder_DebrisArray_Dtor[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_DebrisArray_Dtor = {
    (void *)&clItemBoxResponder_DebrisArray_Dtor, 0x00000080, (void *)extab_clItemBoxResponder_DebrisArray_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_DebrisArray_Dtor(void) { /* 0x8005D954 size:0x80 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr. r29, r3
    beq clItemBoxResponder_DebrisArray_Dtor_L_8005D9B4
    lwz r31, 0x0(r29)
    cmplwi r31, 0x0
    beq clItemBoxResponder_DebrisArray_Dtor_L_8005D9A4
    lis r4, clItemBoxResponder_DebrisParticle_Dtor@ha
    addi r3, r31, 0x4
    addi r4, r4, clItemBoxResponder_DebrisParticle_Dtor@l
    li r5, 0x2c
    li r6, 0xf
    bl fn_80270CF4
    mr r3, r31
    bl MemoryManager_TimedFree
    clItemBoxResponder_DebrisArray_Dtor_L_8005D9A4:
    extsh. r0, r30
    ble clItemBoxResponder_DebrisArray_Dtor_L_8005D9B4
    mr r3, r29
    bl MemoryManager_TimedFree
    clItemBoxResponder_DebrisArray_Dtor_L_8005D9B4:
    lwz r0, 0x24(r1)
    mr r3, r29
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

