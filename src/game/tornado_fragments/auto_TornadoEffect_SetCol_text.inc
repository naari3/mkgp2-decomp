/* === extracted from auto_TornadoEffect_SetCol_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- function index (1 fns, .text 0x80057738..0x8005778C) ---
 * [  0] 0x80057738 size:0x54    global TornadoEffect_SetColorPairC8CC
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x80057738 size:0x54 */
void TornadoEffect_SetColorPairC8CC(void *e, unsigned int a, unsigned int b) {
    TE_S32(e, 0xC8) = Terrain_FlagsToTypeId(Terrain_ApplyCup2FlagPatch(a));
    TE_S32(e, 0xCC) = Terrain_FlagsToTypeId(Terrain_ApplyCup2FlagPatch(b));
}

