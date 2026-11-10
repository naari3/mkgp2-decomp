/* === extracted from auto_TornadoEffect_ApplyI_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int TornadoEffect_bss_806D10A8;
extern const float lbl_806D2914;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803F98F4[];

/* --- function index (1 fns, .text 0x80058C80..0x80058DDC) ---
 * [  0] 0x80058C80 size:0x15C   global TornadoEffect_ApplyItemVisual_Compact
 */

/* --- forward decls --- */



/* --- asm function bodies (.text order = fn address order) --- */
#pragma use_lmw_stmw on
void TornadoEffect_ApplyItemVisual_Compact(void *e, int item, int flag)
{
    int prev = TE_S32(e, 0x14C);
    int eq = item == prev;
    unsigned char same = eq != 0;
    int r;
    int r2;

    if (prev != -1) {
        TornadoEffect_ApplyItemVisual_Primary(e, prev, eq);
    }
    TE_S32(e, 0x14C) = item;
    r = 0;
    r2 = 0;
    switch (item) {
    case 0x19:
        if (!same) {
            TE_S32(e, 0xD4) = 2;
            TE_F(e, 0xE0) = lbl_806D2914;
            TE_F(e, 0xE4) = lbl_806D2914;
            TE_F(e, 0xE8) = lbl_806D2914;
        }
        break;
    case 0x1B:
        r = 4;
        break;
    case 0x0E:
    case 0x10:
    case 0x15:
    case 0x16:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x24:
    case 0x28:
        r = 2;
        break;
    case 0x0C:
    case 0x0D:
    case 0x0F:
    case 0x11:
    case 0x13:
    case 0x14:
    case 0x18:
    case 0x25:
    case 0x26:
    case 0x27:
        r = 5;
        break;
    case 0x1D:
        r2 = 9;
        TornadoEffect_bss_806D10A8++;
        break;
    case 0x1C:
    case 0x21:
        r2 = 10;
        TornadoEffect_bss_806D10A8++;
        break;
    }
    if (r != 0) {
        TE_SetVisualState(e, r, flag);
    }
    if (r2 != 0) {
        TE_SetVisualState2(e, r2, flag);
    }
}
#pragma use_lmw_stmw reset

