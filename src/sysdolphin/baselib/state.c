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

/* The six channel descriptors are separate objects (the target addresses
 * them off the pooled .data base, which needs 3+ objects). */
static HSD_Chan chan_table = { NULL, GX_COLOR1, 0, { 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_SPEC };
static HSD_Chan chan_table_30 = { NULL, GX_COLOR0, 0, { 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_SPOT };
static HSD_Chan chan_table_60 = { NULL, GX_ALPHA0, 0, { 0 }, { 0 }, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_SPOT };
static HSD_Chan chan_table_90 = { NULL, GX_ALPHA0, 0, { 0 }, { 0 }, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_SPOT };
static HSD_Chan chan_table_C0 = { NULL, GX_COLOR0, 0, { 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE };
static HSD_Chan chan_table_F0 = { NULL, GX_ALPHA0, 0, { 0 }, { 0x00, 0x00, 0x00, 0xFF }, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE };


void HSD_SetupChannelMode(u32 rendermode)
{
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
        chan_table.light_mask = HSD_LObjGetLightMaskSpecular();
        HSD_SetupChannel(&chan_table);
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
                         &chan_table_30.amb_color);
        } else {
            chan_table_30.amb_color = dark_matter;
        }
        chan_table_30.mat_src = (diffuse_mode >> 1) & 1;
        chan_table_30.light_mask = HSD_LObjGetLightMaskDiffuse();
        HSD_SetupChannel(&chan_table_30);
        if (alpha_mode & RENDER_ALPHA_VTX) {
            chan_table_60.chan = GX_ALPHA1;
            alpha_chan = 1;
            HSD_SetupChannel(&chan_table_90);
        } else {
            chan_table_60.chan = GX_ALPHA0;
        }
        chan_table_60.light_mask = HSD_LObjGetLightMaskAlpha();
        if (lobj != NULL && (lobj->flags & 0x10)) {
            alpha = lobj->color.a;
        } else {
            alpha = 0;
        }
        if (chan_table_60.light_mask != 0) {
            chan_table_60.enable = GX_ENABLE;
            chan_table_60.mat_color.a = 0xFF;
            chan_table_60.amb_color.a = alpha;
        } else {
            chan_table_60.enable = GX_DISABLE;
            chan_table_60.mat_color.a = alpha;
        }
        HSD_SetupChannel(&chan_table_60);
    } else {
        chan_table_C0.mat_src = (diffuse_mode >> 1) & 1;
        HSD_SetupChannel(&chan_table_C0);
        chan_table_F0.mat_src = (alpha_mode >> 14) & 1;
        HSD_SetupChannel(&chan_table_F0);
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
