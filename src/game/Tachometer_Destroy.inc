/* === extracted from auto_Tachometer_Destroy_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void SpriteHandle_Destroy(unsigned int);
extern void fn_80120A08(unsigned int);

/* --- extern decls: sda21-referenced data --- */
extern unsigned char g_tachometer_isInitialized;
extern unsigned int Tachometer_bss_806D1459;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int Tachometer_data_80411E20[];
extern unsigned int Tachometer_bss_805D3320[];

/* --- function index (1 fns, .text 0x800AB6BC..0x800AB77C) ---
 * [  0] 0x800AB6BC size:0xC0    global Tachometer_Destroy
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x800AB6BC size:0xC0 */
#pragma exceptions on
int Tachometer_Destroy(void) {
    int i;
    if (!g_tachometer_isInitialized) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        SpriteHandle_Destroy(Tachometer_bss_805D3320[i]);
    }
    fn_80120A08(Tachometer_data_80411E20[*(unsigned char *)&Tachometer_bss_806D1459]);
    fn_80120A08(Tachometer_data_80411E20[*(unsigned char *)&Tachometer_bss_806D1459 + 4]);
    fn_80120A08(Tachometer_data_80411E20[*(unsigned char *)&Tachometer_bss_806D1459 + 0x38]);
    g_tachometer_isInitialized = 0;
    return 1;
}
#pragma exceptions reset

