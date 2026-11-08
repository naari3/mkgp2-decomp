/* === extracted from auto_TornadoEffect_ApplyI_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_SetColorAlphaOnly(void *obj, int idx, float a);
extern void Object_SetJObjPositionXYZ(void *obj, float x, float y, float z);

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D28D0;
extern const float lbl_806D28D4;
extern const float lbl_806D28D8;
extern const float lbl_806D28F4;
extern const float lbl_806D2900;
extern const float lbl_806D2938;

/* --- function index (1 fns, .text 0x80058994..0x80058C80) ---
 * [  0] 0x80058994 size:0x2EC   global TornadoEffect_ApplyItemVisual_Secondary
 */

/* --- forward decls --- */


#pragma use_lmw_stmw on
void TornadoEffect_ApplyItemVisual_Secondary(void *e, int item, int flag)
{
    int prev = TE_S32(e, 0x150);
    int eq = item == prev;
    unsigned char same = eq != 0;
    int r;
    if (prev != -1) {
        TornadoEffect_ApplyItemVisual_Primary(e, prev, eq);
    }
    TE_S32(e, 0x150) = item;
    r = 0;
    switch (item) {
    case 0x36:
    case 0x11E:
    case 0x11F:
    case 0x121:
        r = 6;
        break;
    case 0x120:
        break;
    }
    if (r == 0) {
        switch (item) {
        case 0x5C:
            if (TE_U8(e, 0x0) == 0 && !same) {
                TE_S32(e, 0x104) = 2;
                TE_F(e, 0x110) = lbl_806D28D0;
            }
            r = 6;
            break;
        case 0x5D:
            if (!same) {
                TE_F(e, 0x10C) = lbl_806D2938;
            }
            r = 6;
            break;
        case 0x51:
        case 0x67:
        case 0x117:
        case 0x119:
        case 0x11D:
            r = 6;
            break;
        case 0x53:
            r = 5;
            break;
        case 0x2B:
        case 0x2D:
        case 0x36:
        case 0x46:
        case 0x47:
        case 0x4A:
        case 0x4B:
        case 0x5B:
            r = 6;
            break;
        case 0x8:
        case 0x116:
        case 0x118:
        case 0x11C:
            r = 1;
            break;
        case 0x92:
            if (!same) {
                TE_S32(e, 0xD4) = 2;
                TE_F(e, 0xE0) = lbl_806D28F4;
                TE_F(e, 0xE4) = lbl_806D28F4;
                TE_F(e, 0xE8) = lbl_806D28F4;
            }
            break;
        case 0x4F:
            Object_SetJObjPositionXYZ(TE_PTR(e, 0xA8), TE_F(e, 0x4C), TE_F(e, 0x50), TE_F(e, 0x54));
            if (TE_U8(e, 0x8) == 1) {
                Object_SetColorAlphaOnly(TE_PTR(e, 0xA8), 0, lbl_806D28D4);
            } else {
                Object_SetColorAlphaOnly(TE_PTR(e, 0xA8), 0, lbl_806D28D8);
            }
            TE_S32(e, 0x100) = 0x3C;
            break;
        case 0x6B:
            if (!same) {
                TE_S32(e, 0xD4) = 2;
                TE_F(e, 0xE0) = lbl_806D2900;
                TE_F(e, 0xE4) = lbl_806D2900;
                TE_F(e, 0xE8) = lbl_806D2900;
            }
            break;
        case 0x50:
            break;
        case 0x95:
            break;
        }
    }
    if (r != 0) {
        TE_SetVisualState(e, r, flag);
    } else if (!same) {
        TE_S32(e, 0x138) = 0x1E;
    }
}
#pragma use_lmw_stmw reset

