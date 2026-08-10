/* === extracted from auto_RaceContext_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10A0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8040E4D0[];
extern unsigned int lbl_8040E4DC[];

/* --- function index (1 fns, .text 0x8009D638..0x8009D6CC) ---
 * [  0] 0x8009D638 size:0x94    global RaceContext_Dtor
 */

/* --- forward decls --- */
asm void RaceContext_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RaceContext_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RaceContext_Dtor = {
    (void *)&RaceContext_Dtor, 0x00000094, (void *)extab_RaceContext_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RaceContext_Dtor(void) { /* 0x8009D638 size:0x94 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq RaceContext_Dtor_L_8009D6B0
    lis r3, lbl_8040E4D0@ha
    addi r0, r3, lbl_8040E4D0@l
    stw r0, 0x0(r30)
    lwz r3, lbl_806D10A0(r13)
    cmplwi r3, 0x0
    beq RaceContext_Dtor_L_8009D684
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    RaceContext_Dtor_L_8009D684:
    li r0, 0x0
    cmplwi r30, 0x0
    stw r0, lbl_806D10A0(r13)
    beq RaceContext_Dtor_L_8009D6A0
    lis r3, lbl_8040E4DC@ha
    addi r0, r3, lbl_8040E4DC@l
    stw r0, 0x0(r30)
    RaceContext_Dtor_L_8009D6A0:
    extsh. r0, r31
    ble RaceContext_Dtor_L_8009D6B0
    mr r3, r30
    bl MemoryManager_TimedFree
    RaceContext_Dtor_L_8009D6B0:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

