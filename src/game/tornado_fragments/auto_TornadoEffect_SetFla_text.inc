/* === extracted from auto_TornadoEffect_SetFla_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_SetBytePairD4D5();

/* --- function index (1 fns, .text 0x800577C8..0x800577FC) ---
 * [  0] 0x800577C8 size:0x34    global TornadoEffect_SetFlagC0
 */

/* --- forward decls --- */
asm void TornadoEffect_SetFlagC0(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_SetFlagC0[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_SetFlagC0 = {
    (void *)&TornadoEffect_SetFlagC0, 0x00000034, (void *)extab_TornadoEffect_SetFlagC0
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_SetFlagC0(void) { /* 0x800577C8 size:0x34 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x0
    li r5, 0x0
    stw r0, 0x14(r1)
    li r0, 0x1
    stb r0, 0xc0(r3)
    lwz r3, 0x10(r3)
    bl DrawEffect_SetBytePairD4D5
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

