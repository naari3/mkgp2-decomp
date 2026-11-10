/*
 * GXChannel_PushChannelColors @ 0x8007D2AC: the game's copy of sysdolphin's
 * HSD_TExpSetReg (texp.c), built in extlib.cpp. Collects the constant
 * colour registers of a TEV constant list and pushes the changed ones with
 * GXSetTevKColor / GXSetTevColor.
 *
 * Matching notes: the one-component clamps are written
 * `val = (clamp) & 0xFF` with an int `val` (the target clamps into a temp,
 * then clrlwi into val), and the r/g/b broadcast stores `g = r = val` so .r
 * uses the early-loaded register index. The TU owns its .rodata (string
 * pool at 0x80311C68, -rostr).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct GXColor { u8 r, g, b, a; } GXColor;

/* HSD_TECnst (sysdolphin texp.h) */
typedef struct TECnst {
    int type;         /* 0x00 */
    struct TECnst *next; /* 0x04 */
    void *val;        /* 0x08 */
    u8 comp;          /* 0x0C */
    u8 ctype;         /* 0x0D */
    u8 reg;           /* 0x0E */
    u8 idx;           /* 0x0F */
} TECnst;


extern void __assert(const char *file, int line, const char *cond);
extern void GXPixModeSync(void);
extern void GXSetTevColor(int id, GXColor color);
extern void GXSetTevKColor(int id, GXColor color);
extern void HSD_StateInvalidate(int state);
extern const float lbl_806D2FB8;   /* 255.0f */
extern const double lbl_806D2FC0;  /* 255.0 */
extern int GXChannel_PushChannelColors_data_803FE0E0[4];        /* GX_KCOLOR0..3 */

/* --- function index (1 fns, .text 0x8007D2AC..0x8007D7BC) ---
 * [  0] 0x8007D2AC size:0x510   global GXChannel_PushChannelColors
 */

/* --- forward decls --- */
void GXChannel_PushChannelColors(TECnst *clist);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GXChannel_PushChannelColors[8] = {
    0x30, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GXChannel_PushChannelColors = {
    (void *)&GXChannel_PushChannelColors, 0x00000510, (void *)extab_GXChannel_PushChannelColors
};

static const int id2[3] = { 1, 2, 3 }; /* GX_TEVREG0..2 */

#pragma use_lmw_stmw on
/* Game-side copy of sysdolphin's HSD_TExpSetReg (texp.c), built in extlib.cpp. */
void GXChannel_PushChannelColors(TECnst *clist)
{
    int i;
    GXColor reg[8];
    u32 changed;

    changed = 0;
    while (clist != 0) {
        if (!(clist->type == 4)) {
            __assert("extlib.cpp", 0x368, "clist->type == HSD_TE_CNST");
        }
        if (clist->reg < 8) {
            changed |= 1 << clist->reg;
            if (clist->comp == 1) {
                switch (clist->ctype) {
                case 0: {
                    GXColor col;
                    col = *(GXColor *)clist->val;
                    col.a = reg[clist->reg].a;
                    {
                        GXColor *dst = &reg[clist->reg];
                        dst->r = col.r;
                        dst->g = col.g;
                        dst->b = col.b;
                        dst->a = col.a;
                    }
                    break;
                }
                case 2: {
                    u32 *ptr = clist->val;
                    reg[clist->reg].r = ptr[0] < 0x100 ? ptr[0] : 0xFF;
                    reg[clist->reg].g = ptr[1] < 0x100 ? ptr[1] : 0xFF;
                    reg[clist->reg].b = ptr[2] < 0x100 ? ptr[2] : 0xFF;
                    break;
                }
                default: {
                    int r;
                    int g;
                    int b;
                    switch (clist->ctype) {
                    case 1: {
                        u16 *ptr = clist->val;
                        r = ptr[0];
                        g = ptr[1];
                        b = ptr[2];
                        break;
                    }
                    case 3: {
                        float *ptr = clist->val;
                        r = lbl_806D2FB8 * ptr[0];
                        g = lbl_806D2FB8 * ptr[1];
                        b = lbl_806D2FB8 * ptr[2];
                        break;
                    }
                    default: {
                        double *ptr = clist->val;
                        r = lbl_806D2FC0 * ptr[0];
                        g = lbl_806D2FC0 * ptr[1];
                        b = lbl_806D2FC0 * ptr[2];
                        break;
                    }
                    }
                    reg[clist->reg].r = r > 0xFF ? 0xFF : r < 0 ? 0 : r;
                    reg[clist->reg].g = g > 0xFF ? 0xFF : g < 0 ? 0 : g;
                    reg[clist->reg].b = b > 0xFF ? 0xFF : b < 0 ? 0 : b;
                }
                }
            } else {
                int x;
                int val;
                switch (clist->ctype) {
                case 0:
                    x = *(u8 *)clist->val;
                    val = x;
                    break;
                case 1:
                    x = *(u16 *)clist->val;
                    val = (x > 0xFF ? 0xFF : x < 0 ? 0 : x) & 0xFF;
                    break;
                case 2:
                    x = *(u32 *)clist->val;
                    val = (x > 0xFF ? 0xFF : x < 0 ? 0 : x) & 0xFF;
                    break;
                case 3:
                    x = lbl_806D2FB8 * *(float *)clist->val;
                    val = (x > 0xFF ? 0xFF : x < 0 ? 0 : x) & 0xFF;
                    break;
                default:
                    x = lbl_806D2FC0 * *(double *)clist->val;
                    val = (x > 0xFF ? 0xFF : x < 0 ? 0 : x) & 0xFF;
                    break;
                }
                if (clist->reg < 4) {
                    switch (clist->idx) {
                    case 0:
                        reg[clist->reg].r = val;
                        break;
                    case 1:
                        reg[clist->reg].g = val;
                        break;
                    case 2:
                        reg[clist->reg].b = val;
                        break;
                    default:
                        reg[clist->reg].a = val;
                        break;
                    }
                } else if (clist->idx == 3) {
                    reg[clist->reg].a = val;
                } else {
                    reg[clist->reg].g = reg[clist->reg].r = val;
                    reg[clist->reg].b = val;
                }
            }
        }
        clist = clist->next;
    }
    if (changed != 0) {
        GXPixModeSync();
        for (i = 0; i < 4; i++) {
            if (changed & (1 << i)) {
                GXSetTevKColor(GXChannel_PushChannelColors_data_803FE0E0[i], reg[i]);
            }
        }
        for (i = 4; i < 7; i++) {
            if (changed & (1 << i)) {
                GXSetTevColor(id2[i - 4], reg[i]);
            }
        }
        HSD_StateInvalidate(0x10);
        GXPixModeSync();
    }
}
#pragma use_lmw_stmw reset
