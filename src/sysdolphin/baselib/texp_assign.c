#include "texp.h"

#include <string.h>

#include "class.h"
#include "debug.h"
#include "tev.h"
#include "texpdag.h"
#include "tobj.h"

int AssignColorReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
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

GXTevAlphaArg lbl_804FDBC4[4] = { GX_CA_A0, GX_CA_A1, GX_CA_A2, GX_CA_APREV };

int AssignColorKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
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

int AssignAlphaKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
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
