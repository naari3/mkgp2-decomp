#include "texp.h"

#include <string.h>

#include "class.h"
#include "debug.h"
#include "tev.h"
#include "texpdag.h"
#include "tobj.h"

#include "texp_inline.h"
#undef __FILE__
#define __FILE__ lbl_806D0F38
extern char lbl_806D0F38[7];
extern int AssignColorReg(HSD_TETev*, int, HSD_TExpRes*);
extern int AssignColorKonst(HSD_TETev*, int, HSD_TExpRes*);
extern int AssignAlphaKonst(HSD_TETev*, int, HSD_TExpRes*);

char lbl_804FDC64[] = "val >= 0";

static inline u32 TEUndef(u8 v, u32 def)
{
    u32 r = v;
    if (r == HSD_TE_UNDEF) {
        r = def;
    }
    return r;
}

void TExp2TevDesc(HSD_TExp* texp, HSD_TExpTevDesc* desc,
                         int* init_cprev, int* init_aprev)
{
    static GXTevRegID dst[4] = { GX_TEVREG0, GX_TEVREG1, GX_TEVREG2,
                                 GX_TEVPREV };

    HSD_TETev* tev;

    HSD_ASSERT(0x509, texp);
    HSD_ASSERT(0x50A, desc);
    HSD_ASSERT(0x50B, HSD_TExpGetType(texp) == HSD_TE_TEV);

    tev = &texp->tev;
    desc->desc.next = NULL;
    desc->desc.flags = 1;
    desc->tobj = tev->tex;
    if (tev->tex == NULL) {
        desc->desc.coord = HSD_TE_UNDEF;
        desc->desc.map = HSD_TE_UNDEF;
    }
    desc->desc.color = TEUndef(tev->chan, HSD_TE_UNDEF);
    desc->desc.u.tevconf.ras_swap =
        TEUndef(tev->ras_swap, 0);
    desc->desc.u.tevconf.tex_swap =
        TEUndef(tev->tex_swap, 0);
    desc->desc.u.tevconf.kcsel = TEUndef(tev->kcsel, 0);
    desc->desc.u.tevconf.kasel = TEUndef(tev->kasel, 0);

    if ((tev->c_op == HSD_TE_UNDEF) ||
        (tev->c_ref == 0 && tev->a_op != 8 && tev->a_op != 9 &&
         tev->a_op != 0xA && tev->a_op != 0xB && tev->a_op != 0xC &&
         tev->a_op != 0xD))
    {
        desc->desc.u.tevconf.clr_op = GX_TEV_ADD;
        desc->desc.u.tevconf.clr_a = GX_CC_ZERO;
        desc->desc.u.tevconf.clr_b = GX_CC_ZERO;
        desc->desc.u.tevconf.clr_c = GX_CC_ZERO;
        if (*init_cprev != 0) {
            *init_cprev = 0;
            desc->desc.u.tevconf.clr_d = GX_CC_ZERO;
        } else {
            desc->desc.u.tevconf.clr_d = GX_CC_CPREV;
        }
        desc->desc.u.tevconf.clr_scale = 0;
        desc->desc.u.tevconf.clr_bias = 0;
        desc->desc.u.tevconf.clr_clamp = 0;
        desc->desc.u.tevconf.clr_out_reg = 0;
    } else {
        desc->desc.u.tevconf.clr_op = tev->c_op;
        desc->desc.u.tevconf.clr_a =
            TEUndef(tev->c_in[0].arg, GX_CC_ZERO);
        desc->desc.u.tevconf.clr_b =
            TEUndef(tev->c_in[1].arg, GX_CC_ZERO);
        desc->desc.u.tevconf.clr_c =
            TEUndef(tev->c_in[2].arg, GX_CC_ZERO);
        desc->desc.u.tevconf.clr_d =
            TEUndef(tev->c_in[3].arg, GX_CC_ZERO);
        desc->desc.u.tevconf.clr_scale =
            TEUndef(tev->c_scale, 0);
        desc->desc.u.tevconf.clr_bias =
            TEUndef(tev->c_bias, 0);
        desc->desc.u.tevconf.clr_clamp = tev->c_clamp != 0 ? GX_TRUE : GX_FALSE;

        HSD_ASSERT(0x54A, tev->c_dst != HSD_TE_UNDEF);
        desc->desc.u.tevconf.clr_out_reg = dst[tev->c_dst];
        if (desc->desc.u.tevconf.clr_out_reg == 0) {
            *init_cprev = 0;
        }
    }

    if (tev->a_op == HSD_TE_UNDEF || tev->a_ref == 0) {
        desc->desc.u.tevconf.alpha_op = GX_TEV_ADD;
        desc->desc.u.tevconf.alpha_a = GX_CA_ZERO;
        desc->desc.u.tevconf.alpha_b = GX_CA_ZERO;
        desc->desc.u.tevconf.alpha_c = GX_CA_ZERO;
        if (*init_aprev != 0) {
            *init_aprev = 0;
            desc->desc.u.tevconf.alpha_d = GX_CA_ZERO;
        } else {
            desc->desc.u.tevconf.alpha_d = GX_CA_APREV;
        }
        desc->desc.u.tevconf.alpha_scale = 0;
        desc->desc.u.tevconf.alpha_bias = 0;
        desc->desc.u.tevconf.alpha_clamp = 0;
        desc->desc.u.tevconf.alpha_out_reg = 0;
    } else {
        desc->desc.u.tevconf.alpha_op = tev->a_op;
        desc->desc.u.tevconf.alpha_a =
            TEUndef(tev->a_in[0].arg, GX_CA_ZERO);
        desc->desc.u.tevconf.alpha_b =
            TEUndef(tev->a_in[1].arg, GX_CA_ZERO);
        desc->desc.u.tevconf.alpha_c =
            TEUndef(tev->a_in[2].arg, GX_CA_ZERO);
        desc->desc.u.tevconf.alpha_d =
            TEUndef(tev->a_in[3].arg, GX_CA_ZERO);
        desc->desc.u.tevconf.alpha_scale =
            TEUndef(tev->a_scale, 0);
        desc->desc.u.tevconf.alpha_bias =
            TEUndef(tev->a_bias, 0);
        desc->desc.u.tevconf.alpha_clamp =
            tev->a_clamp != 0 ? GX_TRUE : GX_FALSE;

        HSD_ASSERT(0x56E, tev->a_dst != HSD_TE_UNDEF);
        desc->desc.u.tevconf.alpha_out_reg = dst[tev->a_dst];
        if (desc->desc.u.tevconf.alpha_out_reg == 0) {
            *init_aprev = 0;
        }
    }
    desc->desc.u.tevconf.mode = GX_TC_LINEAR;
}

static GXTevKColorID id1[4] = { GX_KCOLOR0, GX_KCOLOR1, GX_KCOLOR2,
                                GX_KCOLOR3 };
static GXTevRegID id2[3] = { GX_TEVREG0, GX_TEVREG1, GX_TEVREG2 };

void HSD_TExpSetReg(HSD_TExp* texp)
{
    int i;
    GXColor reg[8];
    u32 changed;
    HSD_TECnst* clist;

    clist = &texp->cnst;
    changed = 0;

    while (clist != NULL) {
        HSD_ASSERT(0x586, clist->type == HSD_TE_CNST);
        if (clist->reg < 8) {
            changed |= 1 << clist->reg;
            if (clist->comp == HSD_TE_RGB) {
                switch (clist->ctype) {
                case HSD_TE_U8: {
                    GXColor col;
                    col = *(GXColor*) clist->val;
                    col.a = reg[clist->reg].a;
                    reg[clist->reg] = col;
                    break;
                }
                case HSD_TE_U32: {
                    u32* ptr = clist->val;
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
                    case HSD_TE_U16: {
                        u16* ptr = clist->val;
                        r = ptr[0];
                        g = ptr[1];
                        b = ptr[2];
                        break;
                    }
                    case HSD_TE_F32: {
                        f32* ptr = clist->val;
                        r = 0xFF * ptr[0];
                        g = 0xFF * ptr[1];
                        b = 0xFF * ptr[2];
                        break;
                    }
                    default: {
                        f64* ptr = clist->val;
                        r = 0xFF * ptr[0];
                        g = 0xFF * ptr[1];
                        b = 0xFF * ptr[2];
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
                u8 val;
                switch (clist->ctype) {
                case HSD_TE_U8:
                    x = *(u8*) clist->val;
                    val = x;
                    break;
                case HSD_TE_U16: {
                    x = *(u16*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
                    break;
                }
                case HSD_TE_U32:
                    x = *(u32*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
                    break;
                case HSD_TE_F32:
                    x = 0xFF * *(f32*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
                    break;
                default:
                    x = 0xFF * *(f64*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
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
                    reg[clist->reg].r = val;
                    reg[clist->reg].g = val;
                    reg[clist->reg].b = val;
                }
            }
        }
        clist = &clist->next->cnst;
    }
    if (changed != 0) {
        GXPixModeSync();
        for (i = 0; i < 4; i++) {
            if (changed & (1 << i)) {
                GXSetTevKColor(id1[i], reg[i]);
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
