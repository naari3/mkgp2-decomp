#include "state.h"

#include "lobj.h"
#include "mobj.h"
#include "pobj.h"
#include "tev.h"
#include "texp.h"
#include "util.h"
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>

void HSD_SetupPEMode(u32 flags, HSD_PEDesc* pe)
{
    u8 var_r3_2;
    int var_r3;

    if (pe != NULL) {
        HSD_StateSetColorUpdate(pe->flags & 1);
        HSD_StateSetAlphaUpdate(pe->flags & 2);
        HSD_StateSetDstAlpha(pe->flags & 4, pe->dst_alpha);
        HSD_StateSetBlendMode(pe->type, pe->src_factor, pe->dst_factor,
                              pe->logic_op);
        HSD_StateSetZMode(pe->flags & 0x10, pe->z_comp, pe->flags & 0x20);
        HSD_StateSetZCompLoc(pe->flags & 8);
        HSD_StateSetAlphaCompare(pe->alpha_comp0, pe->ref0, pe->alpha_op,
                                 pe->alpha_comp1, pe->ref1);
        HSD_StateSetDither(pe->flags & 0x40);
        return;
    }
    HSD_StateSetColorUpdate(1);
    HSD_StateSetAlphaUpdate(0);
    HSD_StateSetDstAlpha(0, 0U);
    if (flags & 0x40000000) {
        var_r3 = 1;
    } else {
        var_r3 = 0;
    }
    HSD_StateSetBlendMode(var_r3, 4U, 5U, 0xFU);
    var_r3_2 = (flags & 0x20000000) ? GX_FALSE : GX_TRUE;
    HSD_StateSetZMode(1, (flags & 0x08000000) ? 7 : 3, var_r3_2);
    if (!(flags & 0x20000000) && (flags & 0x40000000)) {
        HSD_StateSetZCompLoc(0);
        HSD_StateSetAlphaCompare(4U, 0U, 0U, 4U, 0U);
    } else {
        HSD_StateSetZCompLoc(1);
        HSD_StateSetAlphaCompare(7U, 0U, 0U, 7U, 0U);
    }
    HSD_StateSetDither(0);
}

static inline void setupTevMode_last(void)
{
    if (!HSD_StateGetNumTevStages()) {
        HSD_TevDesc tevdesc;
        tevdesc.flags = 0;
        tevdesc.stage = HSD_StateAssignTev();
        tevdesc.coord = 0xFF;
        tevdesc.map = GX_TEXMAP_NULL;
        tevdesc.color = GX_COLOR0A0;
        tevdesc.u.tevop.tevmode = GX_PASSCLR;
        HSD_SetupTevStage(&tevdesc);
    }
}

void HSD_SetupRenderModeWithCustomPE(u32 rendermode, HSD_PEDesc* pe)
{
    setupTevMode_last();
    HSD_SetupPEMode(rendermode, pe);
    HSD_SetTevRegAll();
    HSD_StateSetNumTevStages();
    HSD_StateSetNumTexGens();
    HSD_SetupChannelMode(rendermode);
}

void HSD_SetupRenderMode(u32 rendermode)
{
    HSD_SetupRenderModeWithCustomPE(rendermode, NULL);
}
