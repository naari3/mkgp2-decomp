/* === extracted from auto_TornadoEffect_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_RenderJObjTree();

/* --- function index (1 fns, .text 0x80056F1C..0x80056F40) ---
 * [  0] 0x80056F1C size:0x24    global TornadoEffect_RenderCallback
 */

/* --- forward decls --- */
asm void TornadoEffect_RenderCallback(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_RenderCallback[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_RenderCallback = {
    (void *)&TornadoEffect_RenderCallback, 0x00000024, (void *)extab_TornadoEffect_RenderCallback
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_RenderCallback(void) { /* 0x80056F1C size:0x24 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x7
    stw r0, 0x14(r1)
    bl Object_RenderJObjTree
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

