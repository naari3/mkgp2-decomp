/* === extracted from auto_TornadoEffect_ApplyI_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int TornadoEffect_bss_806D10A8;
extern const float lbl_806D28CC;
extern const float lbl_806D28D0;
extern const float lbl_806D28F8;
extern const float lbl_806D2914;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */

/* --- function index (1 fns, .text 0x80058534..0x80058994) ---
 * [  0] 0x80058534 size:0x460   global TornadoEffect_ApplyItemVisual_Primary
 */

/* --- forward decls --- */
void TornadoEffect_ApplyItemVisual_Secondary(void *e, int item, int flag);

static inline void TE_SetVisualState(void *e, int r, int flag)
{
    if (r == 0) {
        return;
    }
    if ((unsigned char)flag == 1) {
        TE_S32(e, 0x130) = 0;
    }
    TE_S32(e, 0x124) = r;
    if (TE_S32(e, 0x124) == 6) {
        TE_U8(e, 0x12C) = 1;
    }
}

static inline void TE_SetVisualState2(void *e, int r, int flag)
{
    if (r == 0) {
        return;
    }
    if ((unsigned char)flag == 1) {
        TE_S32(e, 0x134) = 0;
    }
    TE_S32(e, 0x128) = r;
}

#ifdef __MWERKS__
void TornadoEffect_ApplyItemVisual_Primary(); /* the call below passes two arguments */
#else
void TornadoEffect_ApplyItemVisual_Primary(void *e, int item, int eq);
#endif

/* ApplyItemVisual_Compact's steps, as inlined at the end of Primary (the
 * self-call there passes no eq). */
static inline void TE_ReapplyCompact(void *e, int item, int flag)
{
    int prev = TE_S32(e, 0x14C);
    int eq = item == prev;
    unsigned char same = eq != 0;
    int r;
    int r2;

    if (prev != -1) {
#ifdef __MWERKS__
        TornadoEffect_ApplyItemVisual_Primary(e, prev);
#else
        TornadoEffect_ApplyItemVisual_Primary(e, prev, 0); /* eq is never read */
#endif
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

/* Undoes the visual state of an item; then re-applies whichever item is
 * still active. */
void TornadoEffect_ApplyItemVisual_Primary(void *e, int item, int eq)
{
    int r = 0;
    int r2 = 0;
    int prev;

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
        case 0x51:
        case 0x67:
        case 0x117:
        case 0x119:
        case 0x11D:
            r = 6;
            break;
        case 0x19:
        case 0x92:
            TE_S32(e, 0xD4) = 2;
            TE_F(e, 0xE0) = lbl_806D28CC;
            TE_F(e, 0xE4) = lbl_806D28CC;
            TE_F(e, 0xE8) = lbl_806D28CC;
            break;
        case 0x98:
            TE_S32(e, 0xD4) = 3;
            TE_F(e, 0xE0) = lbl_806D28CC;
            TE_F(e, 0xE4) = lbl_806D28CC;
            TE_F(e, 0xE8) = lbl_806D28CC;
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
        case 0x1B:
            r = 4;
            break;
        case 0x2B:
        case 0x2D:
        case 0x36:
        case 0x46:
        case 0x47:
        case 0x4A:
        case 0x4B:
        case 0x5B:
        case 0x5C:
        case 0x5D:
            r = 6;
            break;
        case 0x53:
            r = 5;
            break;
        case 0x08:
        case 0x116:
        case 0x118:
        case 0x11C:
            r = 1;
            break;
        case 0x1D:
            r2 = 9;
            break;
        case 0x1C:
        case 0x21:
            r2 = 10;
            break;
        case 0x6B:
            TE_S32(e, 0xD4) = 2;
            TE_F(e, 0xE0) = lbl_806D28CC;
            TE_F(e, 0xE4) = lbl_806D28CC;
            TE_F(e, 0xE8) = lbl_806D28CC;
            break;
        }
    }
    if (r != 0) {
        if (r == 6) {
            if (TE_U8(e, 0x0) == 0) {
                TE_S32(e, 0x104) = 0;
            }
            TE_S32(e, 0x104) = 1;
            TE_F(e, 0x108) = lbl_806D28CC;
            if (TE_F(e, 0x108) > TE_F(e, 0x10C)) {
                TE_F(e, 0x110) = lbl_806D28D0;
            } else {
                TE_F(e, 0x110) = lbl_806D28F8;
            }
            TE_U8(e, 0x12C) = 0;
        }
        TE_S32(e, 0x124) = 0;
    }
    if (r2 != 0) {
        TE_S32(e, 0x128) = 0;
    }
    if (item == TE_S32(e, 0x14C)) {
        TE_S32(e, 0x14C) = -1;
    } else {
        TE_S32(e, 0x150) = -1;
    }
    prev = TE_S32(e, 0x14C);
    if (prev != -1) {
        TE_ReapplyCompact(e, prev, 1);
    } else if (TE_S32(e, 0x150) != -1) {
        TornadoEffect_ApplyItemVisual_Secondary(e, TE_S32(e, 0x150), 1);
    }
}

