/* === extracted from auto_TornadoEffect_SetSca_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D28C8;
extern const float lbl_806D28CC;

/* --- function index (1 fns, .text 0x800577FC..0x8005785C) ---
 * [  0] 0x800577FC size:0x60    global TornadoEffect_SetScalePairB0BC
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x800577FC size:0x60 */
void TornadoEffect_SetScalePairB0BC(void *e, float a, float b) {
    TE_F(e, 0xB0) = Saturate_Double(a, lbl_806D28C8, lbl_806D28CC);
    TE_F(e, 0xBC) = Saturate_Double(b, lbl_806D28C8, lbl_806D28CC);
}

