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
