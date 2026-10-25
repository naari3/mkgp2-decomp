#include "texp.h"

#include <string.h>

#include "class.h"
#include "debug.h"
#include "tev.h"
#include "texpdag.h"
#include "tobj.h"

HSD_TExpType HSD_TExpGetType(HSD_TExp* texp)
{
    if (texp == NULL) {
        return HSD_TE_ZERO;
    }
    if (texp == HSD_TEXP_TEX) {
        return HSD_TE_TEX;
    }
    if (texp == HSD_TEXP_RAS) {
        return HSD_TE_RAS;
    }
    return texp->type;
}

static HSD_TExp* TevAlloc(void)
{
    HSD_TExp* texp = hsdAllocMemPiece(sizeof(HSD_TETev));
    HSD_ASSERT(0x3F, texp);
    return texp;
}

static HSD_TExp* CnstAlloc(void)
{
    HSD_TExp* texp = hsdAllocMemPiece(sizeof(HSD_TECnst));
    HSD_ASSERT(0x47, texp);
    return texp;
}

void HSD_TExpFree(HSD_TExp* texp)
{
    switch (HSD_TExpGetType(texp)) {
    case HSD_TE_TEV:
        hsdFreeMemPiece(texp, sizeof(HSD_TETev));
        break;
    case HSD_TE_CNST:
        hsdFreeMemPiece(texp, sizeof(HSD_TECnst));
        break;
    default:
        break;
    }
}

void HSD_TExpRef(HSD_TExp* texp, u8 sel)
{
    HSD_TExpType type = HSD_TExpGetType(texp);
    switch (type) {
    case HSD_TE_TEV:
        if (sel == true) {
            texp->tev.c_ref += 1;
            return;
        } else {
            texp->tev.a_ref += 1;
            return;
        }
        break;
    case HSD_TE_CNST:
        texp->cnst.ref += 1;
        break;
    default:
        break;
    }
}

void HSD_TExpUnref(HSD_TExp* texp, u8 sel)
{
    s32 i;

    switch (HSD_TExpGetType(texp)) {
    case HSD_TE_TEV:
        if (sel == true) {
            if (texp->tev.c_ref != 0) {
                texp->tev.c_ref -= 1;
            }
        } else if (texp->tev.a_ref != 0) {
            texp->tev.a_ref -= 1;
        }
        if (texp->tev.c_ref == 0 && texp->tev.a_ref == 0) {
            for (i = 0; i < 4; i++) {
                HSD_TExpUnref(texp->tev.c_in[i].exp, texp->tev.c_in[i].sel);
                HSD_TExpUnref(texp->tev.a_in[i].exp, texp->tev.a_in[i].sel);
            }
        }
        break;
    case HSD_TE_CNST:
        if (texp->cnst.ref != 0) {
            texp->cnst.ref -= 1;
        }
        break;
    }
}

HSD_TExp* HSD_TExpFreeList(HSD_TExp* texp_list, HSD_TExpType type, s32 all)
{
    HSD_TExp** handle;
    HSD_TExp* ptr;
    HSD_TExp* next;

    handle = &texp_list;

    if (all != 0) {
        while (*handle != NULL) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    HSD_ASSERT(0xDC, 0);
                }
            }
            handle = &(*handle)->tev.next;
        }
    } else {
        if (type == HSD_TE_ALL || type == HSD_TE_TEV) {
            for (ptr = texp_list; ptr != NULL; ptr = ptr->tev.next) {
                switch (ptr->type) {
                case HSD_TE_TEV:
                    if (ptr->tev.c_ref == 0 && ptr->tev.c_ref == 0) {
                        HSD_TExpUnref(ptr, 1);
                        HSD_TExpUnref(ptr, 5);
                    }
                    break;
                default:
                    break;
                }
            }
        }

        while (*handle != NULL) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    if ((*handle)->tev.c_ref != 0 || (*handle)->tev.a_ref != 0)
                    {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    if ((*handle)->cnst.ref != 0) {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    HSD_ASSERT(0x10C, 0);
                }
            }
            handle = &(*handle)->tev.next;
        }
    }

    return texp_list;
}

HSD_TExp* HSD_TExpTev(HSD_TExp** texp_list)
{
    int i;
    HSD_TExp* texp;

    HSD_ASSERT(0x127, texp_list);
    texp = TevAlloc();
    memset(texp, 0xFF, sizeof(HSD_TETev));
    texp->type = HSD_TE_TEV;
    texp->tev.next = *texp_list;
    *texp_list = texp;
    texp->tev.c_ref = 0;
    texp->tev.a_ref = 0;
    texp->tev.tex = NULL;
    for (i = 0; i < 4; i++) {
        texp->tev.c_in[i].exp = NULL;
        texp->tev.a_in[i].exp = NULL;
    }
    return texp;
}

HSD_TExp* HSD_TExpCnst(void* val, HSD_TEInput comp, HSD_TEType type,
                       HSD_TExp** texp_list)
{
    HSD_TExp* texp;

    HSD_ASSERT(0x16A, texp_list);

    texp = *texp_list;
    do {
        while (texp) {
            if (texp->type == HSD_TE_CNST && texp->cnst.val == val &&
                texp->cnst.comp == comp)
            {
                HSD_ASSERT(0x171, texp->cnst.ctype == type);
                return texp;
            }
            texp = texp->cnst.next;
        }

        if (comp == HSD_TE_0) {
            return NULL;
        }
        texp = CnstAlloc();
        texp->cnst.type = HSD_TE_CNST;
        texp->cnst.next = (*texp_list);
        *texp_list = texp;
        texp->cnst.ref = 0;
        texp->cnst.val = val;
        texp->cnst.comp = comp;
        texp->cnst.ctype = type;
        texp->cnst.reg = 0xFF;
        texp->cnst.idx = 0xFF;
        texp->cnst.range = 0;
        return texp;
    } while (true);

    return texp;
}

void HSD_TExpColorOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp)
{
    HSD_ASSERT(0x19A, texp);
    HSD_ASSERT(0x19B, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.c_op = op;
    texp->tev.c_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if (op == GX_TEV_ADD || op == GX_TEV_SUB) {
        texp->tev.c_bias = bias;
        texp->tev.c_scale = scale;
    } else {
        texp->tev.c_bias = 0;
        texp->tev.c_scale = 0;
    }
}

void HSD_TExpAlphaOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp)
{
    HSD_ASSERT(0x1B4, texp);
    HSD_ASSERT(0x1B5, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.a_op = op;
    texp->tev.a_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if (op == GX_TEV_ADD || op == GX_TEV_SUB) {
        texp->tev.a_bias = bias;
        texp->tev.a_scale = scale;
    } else {
        texp->tev.a_bias = 0;
        texp->tev.a_scale = 0;
    }
}

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
            HSD_ASSERT(0x20B,
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

void HSD_TExpColorIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    HSD_ASSERT(0x2B5, texp);
    HSD_ASSERT(0x2B6, HSD_TExpGetType(texp) == HSD_TE_TEV);

    tev = &texp->tev;
    HSD_TExpColorInSub(tev, sel_a, exp_a, 0);
    HSD_TExpColorInSub(tev, sel_b, exp_b, 1);
    HSD_TExpColorInSub(tev, sel_c, exp_c, 2);
    HSD_TExpColorInSub(tev, sel_d, exp_d, 3);
}

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

void HSD_TExpAlphaIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    HSD_ASSERT(0x337, texp);
    HSD_ASSERT(0x338, HSD_TExpGetType(texp) == HSD_TE_TEV);

    tev = &texp->tev;
    HSD_TExpAlphaInSub(tev, sel_a, exp_a, 0);
    HSD_TExpAlphaInSub(tev, sel_b, exp_b, 1);
    HSD_TExpAlphaInSub(tev, sel_c, exp_c, 2);
    HSD_TExpAlphaInSub(tev, sel_d, exp_d, 3);
}

void HSD_TExpOrder(HSD_TExp* texp, HSD_TObj* tex, GXChannelID chan)
{
    HSD_ASSERT(0x347, texp);
    HSD_ASSERT(0x348, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.tex = tex;
    if (chan == GX_COLOR_NULL) {
        texp->tev.chan = GX_COLOR_NULL;
        return;
    }
    texp->tev.chan = chan;
}

static int AssignColorReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevColorArg a_in[4] = { GX_CC_A0, GX_CC_A1, GX_CC_A2,
                                     GX_CC_APREV };
    static GXTevColorArg c_in[4] = { GX_CC_C0, GX_CC_C1, GX_CC_C2,
                                     GX_CC_CPREV };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->c_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg < 4) {
            return -1;
        }
        tev->c_in[idx].type = HSD_TE_IMM;
        if (cnst->comp == HSD_TE_X) {
            tev->c_in[idx].arg = a_in[cnst->reg - 4];
        } else {
            tev->c_in[idx].arg = c_in[cnst->reg - 4];
        }
        return 0;
    } else {
        if (cnst->comp == HSD_TE_X) {
            for (j = 4; j < 8; ++j) {
                if (res->reg[j].alpha == 0) {
                    res->reg[j].alpha = 1;
                    cnst->reg = j;
                    cnst->idx = 3;
                    tev->c_in[idx].type = HSD_TE_IMM;
                    tev->c_in[idx].arg = a_in[j - 4];
                    return 0;
                }
            }
        } else {
            for (j = 4; j < 8; ++j) {
                if (res->reg[j].color == 0) {
                    res->reg[j].color = 3;
                    cnst->reg = j;
                    cnst->idx = 0;
                    tev->c_in[idx].type = HSD_TE_IMM;
                    tev->c_in[idx].arg = c_in[j - 4];
                    return 0;
                }
            }
        }
    }
    return -1;
}

static int AssignAlphaReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevAlphaArg in[4] = { GX_CA_A0, GX_CA_A1, GX_CA_A2, GX_CA_APREV };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->a_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg < 4) {
            return -1;
        }
        tev->a_in[idx].type = HSD_TE_IMM;
        tev->a_in[idx].arg = in[cnst->reg - 4];
        return 0;
    } else {
        for (j = 4; j < 8; ++j) {
            if (res->reg[j].alpha == 0) {
                res->reg[j].alpha = 1;
                cnst->reg = j;
                cnst->idx = 3;
                tev->a_in[idx].type = HSD_TE_IMM;
                tev->a_in[idx].arg = in[j - 4];
                return 0;
            }
        }
    }
    return -1;
}

static int AssignColorKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevKColorSel xsel[4][4] = {
        { GX_TEV_KCSEL_K0_R, GX_TEV_KCSEL_K0_G, GX_TEV_KCSEL_K0_B,
          GX_TEV_KCSEL_K0_A },
        { GX_TEV_KCSEL_K1_R, GX_TEV_KCSEL_K1_G, GX_TEV_KCSEL_K1_B,
          GX_TEV_KCSEL_K1_A },
        { GX_TEV_KCSEL_K2_R, GX_TEV_KCSEL_K2_G, GX_TEV_KCSEL_K2_B,
          GX_TEV_KCSEL_K2_A },
        { GX_TEV_KCSEL_K3_R, GX_TEV_KCSEL_K3_G, GX_TEV_KCSEL_K3_B,
          GX_TEV_KCSEL_K3_A }
    };

    static GXTevKColorSel csel[4] = { GX_TEV_KCSEL_K0, GX_TEV_KCSEL_K1,
                                      GX_TEV_KCSEL_K2, GX_TEV_KCSEL_K3 };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->c_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg >= 4) {
            return -1;
        }
        if (cnst->comp == HSD_TE_X) {
            tev->kcsel = xsel[cnst->reg][cnst->idx];
            tev->c_in[idx].type = HSD_TE_KONST;
            tev->c_in[idx].arg = GX_CC_KONST;
        } else {
            tev->kcsel = csel[cnst->reg];
            tev->c_in[idx].type = HSD_TE_KONST;
            tev->c_in[idx].arg = GX_CC_KONST;
        }
        return 0;
    } else {
        if (cnst->comp == HSD_TE_X) {
            for (j = 1; j < 4; j++) {
                if (res->reg[j].alpha == 0) {
                    res->reg[j].alpha = 1;
                    cnst->reg = j;
                    cnst->idx = 3;
                    tev->kcsel = xsel[cnst->reg][cnst->idx];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }

            for (j = 0; j < 4; j++) {
                if (res->reg[j].color < 3) {
                    cnst->reg = j;
                    cnst->idx = res->reg[j].color++;
                    tev->kcsel = xsel[cnst->reg][cnst->idx];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }
        } else {
            for (j = 0; j < 4; j++) {
                if (res->reg[j].color == 0) {
                    res->reg[j].color = 3;
                    cnst->reg = j;
                    cnst->idx = 0;
                    tev->kcsel = csel[cnst->reg];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }
        }
    }
    return -1;
}

static int AssignAlphaKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevKAlphaSel sel[4][4] = {
        { GX_TEV_KASEL_K0_R, GX_TEV_KASEL_K0_G, GX_TEV_KASEL_K0_B,
          GX_TEV_KASEL_K0_A },
        { GX_TEV_KASEL_K1_R, GX_TEV_KASEL_K1_G, GX_TEV_KASEL_K1_B,
          GX_TEV_KASEL_K1_A },
        { GX_TEV_KASEL_K2_R, GX_TEV_KASEL_K2_G, GX_TEV_KASEL_K2_B,
          GX_TEV_KASEL_K2_A },
        { GX_TEV_KASEL_K3_R, GX_TEV_KASEL_K3_G, GX_TEV_KASEL_K3_B,
          GX_TEV_KASEL_K3_A }
    };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->a_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg >= 4) {
            return -1;
        }
        tev->kasel = sel[cnst->reg][cnst->idx];
        tev->a_in[idx].type = HSD_TE_KONST;
        tev->a_in[idx].arg = GX_CA_KONST;
        return 0;
    } else {
        for (j = 1; j < 4; j++) {
            if (res->reg[j].alpha == 0) {
                res->reg[j].alpha = 1;
                cnst->reg = j;
                cnst->idx = 3;
                tev->kasel = sel[cnst->reg][cnst->idx];
                tev->a_in[idx].type = HSD_TE_KONST;
                tev->a_in[idx].arg = GX_CA_KONST;
                return 0;
            }
        }

        for (j = 0; j < 4; j++) {
            if (res->reg[j].color < 3) {
                cnst->reg = j;
                cnst->idx = res->reg[j].color++;
                tev->kasel = sel[cnst->reg][cnst->idx];
                tev->a_in[idx].type = HSD_TE_KONST;
                tev->a_in[idx].arg = GX_CA_KONST;
                return 0;
            }
        }
    }
    return -1;
}

static int TExpAssignReg(HSD_TExp* texp, HSD_TExpRes* res)
{
    HSD_TETev* tev = (HSD_TETev*) texp;
    int i, val;

    if (tev->c_ref > 0) {
        if (tev->kcsel != HSD_TE_UNDEF) {
            for (i = 0; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    val = AssignColorReg(tev, i, res);
                    if (val < 0) {
                        HSD_ASSERT(0x47D, val >= 0);
                        return val;
                    }
                }
            }
        } else if (IsThroughColor((HSD_TExp*) tev) &&
                   tev->c_in[3].type == HSD_TE_CNST)
        {
            if (AssignColorKonst(tev, 3, res) < 0) {
                val = AssignColorReg(tev, 3, res);
                if (val < 0) {
                    HSD_ASSERT(0x489, val >= 0);
                    return val;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    if (AssignColorKonst(tev, i, res) < 0) {
                        val = AssignColorReg(tev, i, res);
                        if (val < 0) {
                            HSD_ASSERT(0x496, val >= 0);
                            return val;
                        }
                    }
                }
            }
            for (; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    val = AssignColorReg(tev, i, res);
                    if (val < 0) {
                        HSD_ASSERT(0x49F, val >= 0);
                        return val;
                    }
                }
            }
        }
    }

    if (tev->a_ref > 0) {
        if (tev->kasel != HSD_TE_UNDEF) {
            for (i = 0; i < 4; i++) {
                if (tev->a_in[i].type == HSD_TE_CNST) {
                    val = AssignAlphaReg(tev, i, res);
                    if (val < 0) {
                        HSD_ASSERT(0x4AF, val >= 0);
                        return val;
                    }
                }
            }
        } else {
            if (IsThroughAlpha((HSD_TExp*) tev) &&
                tev->a_in[3].type == HSD_TE_CNST)
            {
                if (AssignAlphaReg(tev, 3, res) < 0) {
                    val = AssignAlphaKonst(tev, 3, res);
                    if (val < 0) {
                        HSD_ASSERT(0x4BB, val >= 0);
                        return val;
                    }
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST) {
                        if (AssignAlphaKonst(tev, i, res) < 0) {
                            val = AssignAlphaReg(tev, i, res);
                            if (val < 0) {
                                HSD_ASSERT(0x4C8, val >= 0);
                                return val;
                            }
                        }
                    }
                }
                for (; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST) {
                        val = AssignAlphaReg(tev, i, res);
                        if (val < 0) {
                            HSD_ASSERT(0x4D1, val >= 0);
                            return val;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

static inline u32 TEUndef(u8 v, u32 def)
{
    u32 r = v;
    if (r == HSD_TE_UNDEF) {
        r = def;
    }
    return r;
}

static void TExp2TevDesc(HSD_TExp* texp, HSD_TExpTevDesc* desc,
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

void HSD_TExpSetupTev(HSD_TExpTevDesc* tevdesc, HSD_TExp* texp)
{
    HSD_TExpSetReg(texp);
    for (; tevdesc != NULL; tevdesc = (HSD_TExpTevDesc*) tevdesc->desc.next) {
        if (tevdesc->tobj != NULL) {
            tevdesc->desc.map = tevdesc->tobj->id;
            tevdesc->desc.coord = tevdesc->tobj->coord;
        }
        HSD_StateAssignTev();
        HSD_SetupTevStage(&tevdesc->desc);
    }
}

int HSD_TExpCompile(HSD_TExp* texp, HSD_TExpTevDesc** tevdesc,
                    HSD_TExp** texp_list)
{
    int num, i, val;
    HSD_TExpRes res;
    HSD_TExp* order[32];
    HSD_TExpDag list[32];
    int init_cprev = 1;
    int init_aprev = 1;

    HSD_ASSERT(0x650, tevdesc);
    HSD_ASSERT(0x651, texp_list);

    memset(&res, 0, sizeof(HSD_TExpRes));

    HSD_TExpRef(texp, HSD_TE_RGB);
    HSD_TExpRef(texp, HSD_TE_A);
    HSD_TExpSimplify(texp);

    num = HSD_TExpMakeDag(texp, list);
    HSD_TExpSchedule(num, list, order, &res);
    for (i = 0; i < num; ++i) {
        val = TExpAssignReg(order[i], &res);
        HSD_ASSERT(0x671, val >= 0);
    }

    for (i = num - 1; i >= 0; --i) {
        HSD_TExpSimplify2(order[i]);
    }

    num = HSD_TExpMakeDag(texp, list);
    HSD_TExpSchedule(num, list, order, &res);
    *tevdesc = NULL;
    for (i = 0; i < num; ++i) {
        HSD_TExpTevDesc* tdesc = hsdAllocMemPiece(sizeof(HSD_TExpTevDesc));
        tdesc->desc.stage = HSD_Index2TevStage(i);
        TExp2TevDesc(order[(num - i) - 1], tdesc, &init_cprev, &init_aprev);
        tdesc->desc.next = &(*tevdesc)->desc;
        *tevdesc = tdesc;
    }

    *texp_list = HSD_TExpFreeList(*texp_list, HSD_TE_TEV, 1);
    *texp_list = HSD_TExpFreeList(*texp_list, HSD_TE_CNST, 0);
    return num;
}

void HSD_TExpFreeTevDesc(HSD_TExpTevDesc* tdesc)
{
    HSD_TExpTevDesc* next = tdesc;
    while (next != NULL) {
        HSD_TExpTevDesc* temp = (HSD_TExpTevDesc*) next->desc.next;
        hsdFreeMemPiece(next, sizeof(HSD_TExpTevDesc));
        next = temp;
    }
}
