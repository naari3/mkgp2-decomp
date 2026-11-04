#ifndef MKGP2_TEXP_INLINE_H
#define MKGP2_TEXP_INLINE_H
#include "texp.h"
static inline HSD_TExpType TExpGetTypeInline(HSD_TExp* texp)
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

static inline void TExpRefInline(HSD_TExp* texp, u8 sel)
{
    HSD_TExpType type = TExpGetTypeInline(texp);
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

static inline void TExpUnrefInline(HSD_TExp* texp, u8 sel)
{
    s32 i;

    switch (TExpGetTypeInline(texp)) {
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
                TExpUnrefInline(texp->tev.c_in[i].exp, texp->tev.c_in[i].sel);
                TExpUnrefInline(texp->tev.a_in[i].exp, texp->tev.a_in[i].sel);
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


#define HSD_TExpGetType TExpGetTypeInline
#define HSD_TExpRef TExpRefInline
#define HSD_TExpUnref TExpUnrefInline
#endif
