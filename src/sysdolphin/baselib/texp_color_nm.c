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

static void HSD_TExpColorInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx)
{
    HSD_TEArg prev;
    u8 ksel;

    prev = tev->c_in[idx];
    tev->c_in[idx].type = HSD_TExpGetType(exp);
    tev->c_in[idx].sel = sel;
    tev->c_in[idx].exp = exp;
    tev->c_in[idx].arg = 0xFF;

    switch (sel) {
    case HSD_TE_0:
        tev->c_in[idx].arg = GX_CC_ZERO;
        tev->c_in[idx].type = HSD_TE_ZERO;
        tev->c_in[idx].exp = NULL;
        break;
    case HSD_TE_1:
        tev->c_in[idx].arg = GX_CC_ONE;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = NULL;
        break;
    case HSD_TE_4_8:
        tev->c_in[idx].arg = GX_CC_HALF;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = NULL;
        break;
    case HSD_TE_1_8:
    case HSD_TE_2_8:
    case HSD_TE_3_8:
    case HSD_TE_5_8:
    case HSD_TE_6_8:
    case HSD_TE_7_8:
        tev->c_in[idx].arg = GX_CC_KONST;
        switch (sel) {
        case HSD_TE_1_8:
            ksel = GX_TEV_KCSEL_1_8;
            break;
        case HSD_TE_2_8:
            ksel = GX_TEV_KCSEL_1_4;
            break;
        case HSD_TE_3_8:
            ksel = GX_TEV_KCSEL_3_8;
            break;
        case HSD_TE_5_8:
            ksel = GX_TEV_KCSEL_5_8;
            break;
        case HSD_TE_6_8:
            ksel = GX_TEV_KCSEL_3_4;
            break;
        case HSD_TE_7_8:
            ksel = GX_TEV_KCSEL_7_8;
            break;
        default:
            HSD_ASSERT(0x1F4, 0);
            break;
        }

        if (tev->kcsel == HSD_TE_UNDEF) {
            tev->kcsel = ksel;
        } else if (tev->kcsel == ksel) {
            HSD_Panic(__FILE__, 0x1F9,
                      "tev can't select multiple konst input.\n");
        }
        tev->c_in[idx].type = HSD_TE_KONST;
        break;

    default: {
        switch (tev->c_in[idx].type) {
        case HSD_TE_ZERO:
            tev->c_in[idx].type = HSD_TE_ZERO;
            tev->c_in[idx].sel = HSD_TE_0;
            tev->c_in[idx].arg = GX_CC_ZERO;
            break;
        case HSD_TE_TEV: {
            u8 swap;
            HSD_ASSERT(0x209,
                        sel == HSD_TE_RGB || sel == HSD_TE_A);
            HSD_ASSERT(0x20B,
                        idx == 3 || sel != HSD_TE_RGB || exp->tev.c_clamp);
            HSD_ASSERT(0x20C,
                        idx == 3 || sel != HSD_TE_A || exp->tev.a_clamp);
            swap = tev->c_in[idx].sel;
            switch (HSD_TExpGetType(tev->c_in[idx].exp)) {
            case HSD_TE_TEV:
                if (swap == 1) {
                    tev->c_in[idx].exp->tev.c_ref += 1;
                } else {
                    tev->c_in[idx].exp->tev.a_ref += 1;
                }
                break;
            case HSD_TE_CNST:
                tev->c_in[idx].exp->cnst.ref += 1;
                break;
            default:
                break;
            }
        } break;
        case HSD_TE_CNST: {
            u8 swap;
            tev->c_in[idx].sel = exp->cnst.comp;
            swap = tev->c_in[idx].sel;
            switch (HSD_TExpGetType(tev->c_in[idx].exp)) {
            case HSD_TE_TEV:
                if (swap == 1) {
                    tev->c_in[idx].exp->tev.c_ref += 1;
                } else {
                    tev->c_in[idx].exp->tev.a_ref += 1;
                }
                break;
            case HSD_TE_CNST:
                tev->c_in[idx].exp->cnst.ref += 1;
                break;
            default:
                break;
            }
        } break;
        case HSD_TE_TEX: {
            u8 swap = HSD_TE_UNDEF;
            switch (sel) {
            case HSD_TE_RGB:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP0;
                break;
            case HSD_TE_R:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP1;
                break;
            case HSD_TE_G:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP2;
                break;
            case HSD_TE_B:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP3;
                break;
            case HSD_TE_A:
                tev->c_in[idx].arg = GX_CC_TEXA;
                break;
            default:
                HSD_ASSERT(0x22F, 0);
                break;
            }
            if (tev->tex_swap == HSD_TE_UNDEF) {
                tev->tex_swap = swap;
            } else {
                HSD_ASSERT(0x234,
                            swap == HSD_TE_UNDEF || tev->tex_swap == swap);
            }
        } break;
        case HSD_TE_RAS: {
            u8 swap = HSD_TE_UNDEF;
            switch (sel) {
            case HSD_TE_RGB:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP0;
                break;
            case HSD_TE_R:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP1;
                break;
            case HSD_TE_G:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP2;
                break;
            case HSD_TE_B:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP3;
                break;
            case HSD_TE_A:
                tev->c_in[idx].arg = GX_CC_RASA;
                break;
            default:
                HSD_ASSERT(0x25F, 0);
                break;
            }
            if (tev->ras_swap == HSD_TE_UNDEF) {
                tev->ras_swap = swap;
            } else {
                HSD_ASSERT(0x264,
                            swap == HSD_TE_UNDEF || tev->ras_swap == swap);
            }
        } break;
        default:
            HSD_ASSERT(0x276, 0);
            break;
        }
    }
    }
    HSD_TExpUnref(prev.exp, prev.sel);
}
