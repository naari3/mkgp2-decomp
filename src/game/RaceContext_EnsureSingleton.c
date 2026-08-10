/* === extracted from auto_RaceContext_EnsureSi_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void MemoryManager_TimedFree();
extern void RaceContext_InitDefaults();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D12DC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8040E4DC[];

/* --- function index (2 fns, .text 0x8009DC80..0x8009DD28) ---
 * [  0] 0x8009DC80 size:0x60    global RaceContext_EnsureSingleton
 * [  1] 0x8009DCE0 size:0x48    global dtor_8009DCE0
 */

/* --- forward decls --- */
asm void RaceContext_EnsureSingleton(void);
asm void dtor_8009DCE0(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_dtor_8009DCE0[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_RaceContext_EnsureSingleton = { 0x08080000, 0x0000003C, 0x00000010, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RaceContext_EnsureSingleton = {
    (void *)&RaceContext_EnsureSingleton, 0x00000060, (void *)&extab_RaceContext_EnsureSingleton
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_8009DCE0 = {
    (void *)&dtor_8009DCE0, 0x00000048, (void *)extab_dtor_8009DCE0
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RaceContext_EnsureSingleton(void) { /* 0x8009DC80 size:0x60 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lwz r0, lbl_806D12DC(r13)
    cmplwi r0, 0x0
    bne RaceContext_EnsureSingleton_L_8009DCA0
    li r0, 0x0
    RaceContext_EnsureSingleton_L_8009DCA0:
    cmplwi r0, 0x0
    bne RaceContext_EnsureSingleton_L_8009DCBC
    li r3, 0x4
    bl Alloc
    mr. r31, r3
    beq RaceContext_EnsureSingleton_L_8009DCBC
    bl RaceContext_InitDefaults
    RaceContext_EnsureSingleton_L_8009DCBC:
    lwz r3, lbl_806D12DC(r13)
    cmplwi r3, 0x0
    bne RaceContext_EnsureSingleton_L_8009DCCC
    li r3, 0x0
    RaceContext_EnsureSingleton_L_8009DCCC:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void dtor_8009DCE0(void) { /* 0x8009DCE0 size:0x48 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq dtor_8009DCE0_L_8009DD10
    lis r5, lbl_8040E4DC@ha
    extsh. r0, r4
    addi r0, r5, lbl_8040E4DC@l
    stw r0, 0x0(r31)
    ble dtor_8009DCE0_L_8009DD10
    bl MemoryManager_TimedFree
    dtor_8009DCE0_L_8009DD10:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

