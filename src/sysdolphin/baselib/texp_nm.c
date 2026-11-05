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
extern char lbl_806D0F40[5];
extern char lbl_806D0F4C[5];
extern char lbl_804FDC64[9];
extern int AssignColorReg(HSD_TETev*, int, HSD_TExpRes*);
extern int AssignColorKonst(HSD_TETev*, int, HSD_TExpRes*);
extern int AssignAlphaKonst(HSD_TETev*, int, HSD_TExpRes*);
extern GXTevAlphaArg lbl_804FDBC4[4];

static inline int AssignAlphaReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->a_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg < 4) {
            return -1;
        }
        tev->a_in[idx].type = HSD_TE_IMM;
        tev->a_in[idx].arg = lbl_804FDBC4[cnst->reg - 4];
        return 0;
    } else {
        for (j = 4; j < 8; ++j) {
            if (res->reg[j].alpha == 0) {
                res->reg[j].alpha = 1;
                cnst->reg = j;
                cnst->idx = 3;
                tev->a_in[idx].type = HSD_TE_IMM;
                tev->a_in[idx].arg = lbl_804FDBC4[j - 4];
                return 0;
            }
        }
    }
    return -1;
}

int TExpAssignReg(HSD_TExp* texp, HSD_TExpRes* res)
{
    HSD_TETev* tev = (HSD_TETev*) texp;
    int i, val;

    if (tev->c_ref > 0) {
        if (tev->kcsel != HSD_TE_UNDEF) {
            for (i = 0; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    val = AssignColorReg(tev, i, res);
                    if (val < 0) {
                        HSD_ASSERTMSG(0x47D, val >= 0, lbl_804FDC64);
                        return val;
                    }
                }
            }
        } else if (IsThroughColor((HSD_TExp*) tev) &&
                   tev->c_in[3].type == HSD_TE_CNST)
        {
            if (AssignColorReg(tev, 3, res) < 0) {
                val = AssignColorKonst(tev, 3, res);
                if (val < 0) {
                    HSD_ASSERTMSG(0x489, val >= 0, lbl_804FDC64);
                    return val;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    if (AssignColorKonst(tev, i, res) < 0) {
                        val = AssignColorReg(tev, i, res);
                        if (val < 0) {
                            HSD_ASSERTMSG(0x496, val >= 0, lbl_804FDC64);
                            return val;
                        }
                    }
                }
            }
            for (; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    val = AssignColorReg(tev, i, res);
                    if (val < 0) {
                        HSD_ASSERTMSG(0x49F, val >= 0, lbl_804FDC64);
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
                        HSD_ASSERTMSG(0x4AF, val >= 0, lbl_804FDC64);
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
                        HSD_ASSERTMSG(0x4BB, val >= 0, lbl_804FDC64);
                        return val;
                    }
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST) {
                        if (AssignAlphaKonst(tev, i, res) < 0) {
                            val = AssignAlphaReg(tev, i, res);
                            if (val < 0) {
                                HSD_ASSERTMSG(0x4C8, val >= 0, lbl_804FDC64);
                                return val;
                            }
                        }
                    }
                }
                for (; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST) {
                        val = AssignAlphaReg(tev, i, res);
                        if (val < 0) {
                            HSD_ASSERTMSG(0x4D1, val >= 0, lbl_804FDC64);
                            return val;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
