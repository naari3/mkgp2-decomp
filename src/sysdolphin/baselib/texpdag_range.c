#include "texpdag.h"

#include <placeholder.h>
#include <string.h>

#include "debug.h"
#include "texp.h"
#include "tobj.h"

void CalcRange(HSD_TETev* tev)
{
    int i;
    int r;

    r = 0;
    if (tev->c_in[3].sel != HSD_TE_0) {
        switch (HSD_TExpGetType(tev->c_in[3].exp)) {
        case HSD_TE_TEV:
            if (tev->c_in[3].sel == HSD_TE_RGB) {
                if (tev->c_in[3].exp->tev.c_clamp != 1 &&
                    tev->c_in[3].exp->tev.c_range == 1)
                {
                    tev->c_range = 1;
                    goto alpha;
                }
                r = 0x100;
            } else {
                if (tev->c_in[3].exp->tev.a_clamp != 1 &&
                    tev->c_in[3].exp->tev.a_range == 1)
                {
                    tev->c_range = 1;
                    goto alpha;
                }
                r = 0x100;
            }
            break;
        default:
            r = 0x100;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        if (tev->c_in[i].sel != HSD_TE_0) {
            if (tev->c_op == GX_TEV_SUB) {
                tev->c_range = 1;
                goto alpha;
            }
            r += 0x100;
            break;
        }
    }
    switch (tev->c_bias) {
    case GX_TB_ADDHALF:
        r += 0x80;
        break;
    case GX_TB_SUBHALF:
        tev->c_range = 1;
        goto alpha;
    }
    switch (tev->c_scale) {
    case GX_CS_SCALE_2:
        r *= 2;
        break;
    case GX_CS_SCALE_4:
        r *= 4;
        break;
    case GX_CS_DIVIDE_2:
        r /= 2;
        break;
    }
    tev->c_range = r > 0x100;

alpha:
    r = 0;
    if (tev->a_in[3].sel != HSD_TE_0) {
        switch (HSD_TExpGetType(tev->a_in[3].exp)) {
        case HSD_TE_TEV:
            if (tev->a_in[3].exp->tev.a_clamp != 1 &&
                tev->a_in[3].exp->tev.a_range == 1)
            {
                tev->a_range = 1;
                return;
            }
            r = 0x100;
            break;
        default:
            r = 0x100;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        if (tev->a_in[i].sel != HSD_TE_0) {
            if (tev->a_op == GX_TEV_SUB) {
                tev->a_range = 1;
                return;
            }
            r += 0x100;
            break;
        }
    }
    switch (tev->a_bias) {
    case GX_TB_ADDHALF:
        r += 0x80;
        break;
    case GX_TB_SUBHALF:
        tev->a_range = 1;
        return;
    }
    switch (tev->a_scale) {
    case GX_CS_SCALE_2:
        r *= 2;
        break;
    case GX_CS_SCALE_4:
        r *= 4;
        break;
    case GX_CS_DIVIDE_2:
        r /= 2;
        break;
    }
    tev->a_range = r > 0x100;
}

