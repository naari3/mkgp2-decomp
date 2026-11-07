/* === extracted from auto_TornadoEffect_SetFla_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- function index (1 fns, .text 0x800577C8..0x800577FC) ---
 * [  0] 0x800577C8 size:0x34    global TornadoEffect_SetFlagC0
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x800577C8 size:0x34 */
void TornadoEffect_SetFlagC0(void *e) {
    TE_U8(e, 0xC0) = 1;
    DrawEffect_SetBytePairD4D5(TE_PTR(e, 0x10), 0, 0);
}

