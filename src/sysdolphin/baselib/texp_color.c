#include "texp.h"

#include <string.h>

#include "class.h"
#include "debug.h"
#include "tev.h"
#include "texpdag.h"
#include "tobj.h"

#include "texp_inline.h"
extern char lbl_806D0F38[7];
extern char lbl_806D0F40[5];
extern char lbl_804FD988[10];
extern char lbl_804FD994[25];
extern char lbl_804FD9B0[];
#undef __FILE__
#define __FILE__ lbl_806D0F38

extern void HSD_TExpColorInSub(HSD_TETev*, HSD_TEInput, HSD_TExp*, s32);

void HSD_TExpColorIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    HSD_ASSERTMSG(0x2B5, texp, lbl_806D0F40);
    HSD_ASSERTMSG(0x2B6, HSD_TExpGetType(texp) == HSD_TE_TEV, lbl_804FD9B0);

    tev = &texp->tev;
    HSD_TExpColorInSub(tev, sel_a, exp_a, 0);
    HSD_TExpColorInSub(tev, sel_b, exp_b, 1);
    HSD_TExpColorInSub(tev, sel_c, exp_c, 2);
    HSD_TExpColorInSub(tev, sel_d, exp_d, 3);
}
