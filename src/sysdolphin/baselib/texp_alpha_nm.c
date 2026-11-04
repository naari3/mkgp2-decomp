#include "texp.h"

#include <string.h>

#include "class.h"
#include "debug.h"
#include "tev.h"
#include "texpdag.h"
#include "tobj.h"

#include "texp_inline.h"
#undef __FILE__
#define __FILE__ "texp.c"

static void HSD_TExpAlphaInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx)
{
    HSD_TEArg prev;
    u8 ksel;

    prev = tev->a_in[idx];
    tev->a_in[idx].sel = sel;
    tev->a_in[idx].exp = exp;
    tev->a_in[idx].type = HSD_TExpGetType(exp);
    tev->a_in[idx].arg = 0xFF;

    switch (sel) {
    case HSD_TE_0:
        tev->a_in[idx].type = HSD_TE_ZERO;
        tev->a_in[idx].arg = GX_CA_ZERO;
        tev->a_in[idx].exp = NULL;
        break;

    case HSD_TE_1:
    case HSD_TE_1_8:
    case HSD_TE_2_8:
    case HSD_TE_3_8:
    case HSD_TE_4_8:
    case HSD_TE_5_8:
    case HSD_TE_6_8:
    case HSD_TE_7_8:
        tev->a_in[idx].exp = NULL;
        tev->a_in[idx].arg = GX_CA_KONST;
        switch (sel) {
        case HSD_TE_1_8:
            ksel = GX_TEV_KASEL_1_8;
            break;
        case HSD_TE_2_8:
            ksel = GX_TEV_KASEL_1_4;
            break;
        case HSD_TE_3_8:
            ksel = GX_TEV_KASEL_3_8;
            break;
        case HSD_TE_4_8:
            ksel = GX_TEV_KASEL_1_2;
            break;
        case HSD_TE_5_8:
            ksel = GX_TEV_KASEL_5_8;
            break;
        case HSD_TE_6_8:
            ksel = GX_TEV_KASEL_3_4;
            break;
        case HSD_TE_7_8:
            ksel = GX_TEV_KASEL_7_8;
            break;
        default:
            ksel = GX_TEV_KASEL_1;
            break;
        }

        if (tev->kasel == HSD_TE_UNDEF) {
            tev->kasel = ksel;
        } else {
            HSD_ASSERT(0x2EE, tev->kasel == ksel);
        }
        tev->a_in[idx].type = HSD_TE_KONST;
        break;

    default: {
        switch (tev->a_in[idx].type) {
        case HSD_TE_ZERO:
            tev->a_in[idx].exp = NULL;
            tev->a_in[idx].type = HSD_TE_ZERO;
            tev->a_in[idx].sel = HSD_TE_0;
            tev->a_in[idx].arg = GX_CA_ZERO;
            break;
        case HSD_TE_TEV:
            HSD_ASSERT(0x305, sel == HSD_TE_A);
            HSD_ASSERT(0x306, idx == 3 || exp->tev.a_clamp);
            HSD_TExpRef(tev->a_in[idx].exp, tev->a_in[idx].sel);
            break;
        case HSD_TE_CNST:
            HSD_ASSERT(0x30A,
                        sel == HSD_TE_A || sel == HSD_TE_X);
            HSD_ASSERT(0x30B, exp->cnst.comp == HSD_TE_X);
            tev->a_in[idx].sel = HSD_TE_X;
            HSD_TExpRef(tev->a_in[idx].exp, tev->a_in[idx].sel);
            break;
        case HSD_TE_TEX:
            HSD_ASSERT(0x310, sel == HSD_TE_A);
            tev->a_in[idx].arg = GX_CA_TEXA;
            break;
        case HSD_TE_RAS:
            HSD_ASSERT(0x314, sel == HSD_TE_A);
            tev->a_in[idx].arg = GX_CA_RASA;
            break;
        default:
            HSD_ASSERT(0x318, 0);
            break;
        }
    }
    }
    HSD_TExpUnref(prev.exp, prev.sel);
}
