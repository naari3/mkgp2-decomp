/* === extracted from auto_fn_80057960_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int TornadoEffect_rodata_802EDC30[];

/* --- function index (1 fns, .text 0x80057960..0x800579D8) ---
 * [  0] 0x80057960 size:0x78    global fn_80057960
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x80057960 size:0x78 */
void fn_80057960(void *e, float x, float y, float z) {
    if (TE_PTR(e, 0x14)) {
        TornadoSpawnPos pos = TE_SPAWN_POS;
        pos.x = x;
        pos.y = y;
        pos.z = z;
        DrawEffect_SpawnWithDescriptor(0, pos);
    }
}

