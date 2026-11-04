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

static HSD_TExp* TevAlloc(void)
{
    HSD_TExp* texp = hsdAllocMemPiece(sizeof(HSD_TETev));
    HSD_ASSERTMSG(0x3F, texp, lbl_806D0F40);
    return texp;
}

static HSD_TExp* CnstAlloc(void)
{
    HSD_TExp* texp = hsdAllocMemPiece(sizeof(HSD_TECnst));
    HSD_ASSERTMSG(0x47, texp, lbl_806D0F40);
    return texp;
}

HSD_TExp* HSD_TExpTev(HSD_TExp** texp_list)
{
    int i;
    HSD_TExp* texp;

    HSD_ASSERTMSG(0x127, texp_list, lbl_804FD988);
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

    HSD_ASSERTMSG(0x16A, texp_list, lbl_804FD988);

    texp = *texp_list;
    do {
        while (texp) {
            if (texp->type == HSD_TE_CNST && texp->cnst.val == val &&
                texp->cnst.comp == comp)
            {
                HSD_ASSERTMSG(0x171, texp->cnst.ctype == type, lbl_804FD994);
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
    HSD_ASSERTMSG(0x19A, texp, lbl_806D0F40);
    HSD_ASSERTMSG(0x19B, HSD_TExpGetType(texp) == HSD_TE_TEV, lbl_804FD9B0);

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
    HSD_ASSERTMSG(0x1B4, texp, lbl_806D0F40);
    HSD_ASSERTMSG(0x1B5, HSD_TExpGetType(texp) == HSD_TE_TEV, lbl_804FD9B0);

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
