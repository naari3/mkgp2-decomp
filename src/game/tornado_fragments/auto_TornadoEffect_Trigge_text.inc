/* === extracted from auto_TornadoEffect_Trigge_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- function index (1 fns, .text 0x800576D8..0x8005771C) ---
 * [  0] 0x800576D8 size:0x44    global TornadoEffect_TriggerFlagD2WithTimer
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x800576D8 size:0x44 */
void TornadoEffect_TriggerFlagD2WithTimer(void *e) {
    DrawEffect_SetByte10C(TE_PTR(e, 0x10), 0);
    TE_U8(e, 0xD2) = 1;
    TE_S32(e, 0x13C) = 15;
}

