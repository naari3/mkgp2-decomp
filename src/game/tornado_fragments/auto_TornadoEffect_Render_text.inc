/* === extracted from auto_TornadoEffect_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- function index (1 fns, .text 0x80056F1C..0x80056F40) ---
 * [  0] 0x80056F1C size:0x24    global TornadoEffect_RenderCallback
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x80056F1C size:0x24 */
void TornadoEffect_RenderCallback(void *e) {
    Object_RenderJObjTree(e, 7);
}

