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

static GXColor dark_matter = { 0x00, 0x00, 0x00, 0xFF };


#include "state_private.h"
struct matstate_t matstate;

void HSD_DisableChannel(GXChannelID chan);

static HSD_Chan chan_table[6] = {
    { NULL, GX_COLOR0, 1, { 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, GX_ENABLE,
      GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_SPEC },
    { NULL, GX_COLOR0, 0, { 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, GX_ENABLE,
      GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_SPOT },
    { NULL, GX_ALPHA0, 0, { 0 }, { 0 }, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, 0,
      GX_DF_CLAMP, GX_AF_SPOT },
    { NULL, GX_ALPHA0, 0, { 0 }, { 0 }, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX,
      0, GX_DF_CLAMP, GX_AF_SPOT },
    { NULL, GX_COLOR0, 0, { 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, GX_DISABLE,
      GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE },
    { NULL, GX_ALPHA0, 0, { 0 }, { 0x00, 0x00, 0x00, 0xFF }, GX_DISABLE,
      GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE },
};

void HSD_SetupChannelMode(u32 rendermode)
{
    HSD_Chan* chans = chan_table;
    HSD_LObj* lobj;
    u32 diffuse_mode;
    u32 alpha_mode;
    int specular = 0;
    int alpha_chan = 0;
    int i;
    int max;
    u8 alpha;

    diffuse_mode = rendermode & RENDER_DIFFUSE_BITS;
    if (diffuse_mode == 0) {
        diffuse_mode = RENDER_DIFFUSE_MAT;
    }
    alpha_mode = rendermode & RENDER_ALPHA_BITS;
    if (alpha_mode == 0) {
        alpha_mode = diffuse_mode << 13;
    }

    if (rendermode & RENDER_SPECULAR) {
        chans[0].light_mask = HSD_LObjGetLightMaskSpecular();
        HSD_SetupChannel(&chans[0]);
        specular = 1;
        max = HSD_LObjGetNbActive();
        for (i = 0; i < max; i++) {
            lobj = HSD_LObjGetActiveByIndex(i);
            if (lobj != NULL) {
                HSD_LObjSetup(lobj, lobj->color, matstate.shininess);
            }
        }
    }

    if (rendermode & RENDER_DIFFUSE) {
        lobj = HSD_LObjGetActiveByID(0x100);
        if (lobj != NULL && (lobj->flags & 4)) {
            HSD_MulColor(&matstate.ambient, &lobj->color,
                         &chans[1].amb_color);
        } else {
            chans[1].amb_color = dark_matter;
        }
        chans[1].mat_src = (diffuse_mode >> 1) & 1;
        chans[1].light_mask = HSD_LObjGetLightMaskDiffuse();
        HSD_SetupChannel(&chans[1]);
        if (alpha_mode & RENDER_ALPHA_VTX) {
            chans[2].chan = GX_ALPHA1;
            alpha_chan = 1;
            HSD_SetupChannel(&chans[3]);
        } else {
            chans[2].chan = GX_ALPHA0;
        }
        chans[2].light_mask = HSD_LObjGetLightMaskAlpha();
        if (lobj != NULL && (lobj->flags & 0x10)) {
            alpha = lobj->color.a;
        } else {
            alpha = 0;
        }
        if (chans[2].light_mask != 0) {
            chans[2].enable = GX_ENABLE;
            chans[2].mat_color.a = 0xFF;
            chans[2].amb_color.a = alpha;
        } else {
            chans[2].enable = GX_DISABLE;
            chans[2].mat_color.a = alpha;
        }
        HSD_SetupChannel(&chans[2]);
    } else {
        chans[4].mat_src = (diffuse_mode >> 1) & 1;
        HSD_SetupChannel(&chans[4]);
        chans[5].mat_src = (alpha_mode >> 14) & 1;
        HSD_SetupChannel(&chans[5]);
    }

    if (specular) {
        if (!alpha_chan) {
            HSD_DisableChannel(GX_ALPHA1);
        }
        HSD_StateSetNumChans(2);
    } else if (alpha_chan) {
        HSD_DisableChannel(GX_COLOR1);
        HSD_StateSetNumChans(2);
    } else {
        HSD_DisableChannel(GX_COLOR1A1);
        HSD_StateSetNumChans(1);
    }
}
