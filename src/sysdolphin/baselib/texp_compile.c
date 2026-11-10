#include "texp.h"

#include <string.h>

#include "class.h"
#include "debug.h"
#include "tev.h"
#include "texpdag.h"
#include "tobj.h"

extern char lbl_806D0F38[8];
extern char lbl_806D0F54[8];
extern char lbl_804FD988[];
extern char texp_data_804FDC64[12];
extern int TExpAssignReg(HSD_TExp*, HSD_TExpRes*);
extern void TExp2TevDesc(HSD_TExp*, HSD_TExpTevDesc*, int*, int*);

static inline HSD_TExpType TExpGetType(HSD_TExp* texp)
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

static inline void TExpRef(HSD_TExp* texp, u8 sel)
{
    HSD_TExpType type = TExpGetType(texp);
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

extern int TExpAssignReg(HSD_TExp*, HSD_TExpRes*);

int HSD_TExpCompile(HSD_TExp* texp, HSD_TExpTevDesc** tevdesc,
                    HSD_TExp** texp_list)
{
    int num, i, val;
    HSD_TExpRes res;
    HSD_TExp* order[32];
    HSD_TExpDag list[32];
    int init_cprev = 1;
    int init_aprev = 1;

    ((tevdesc) ? ((void) 0) : __assert(lbl_806D0F38, 0x650, lbl_806D0F54));
    ((texp_list) ? ((void) 0) : __assert(lbl_806D0F38, 0x651, lbl_804FD988));

    memset(&res, 0, sizeof(HSD_TExpRes));

    TExpRef(texp, HSD_TE_RGB);
    TExpRef(texp, HSD_TE_A);
    HSD_TExpSimplify(texp);

    num = HSD_TExpMakeDag(texp, list);
    HSD_TExpSchedule(num, list, order, &res);
    for (i = 0; i < num; ++i) {
        val = TExpAssignReg(order[i], &res);
        ((val >= 0) ? ((void) 0) : __assert(lbl_806D0F38, 0x671, texp_data_804FDC64));
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
