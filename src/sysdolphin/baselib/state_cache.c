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

#include "state_private.h"
/* Preserve target tail padding without changing the byte cache alignment. */
#pragma force_active on
static u32 state_cache_padding_word;
static u8 state_cache_padding_byte1;
static u8 state_cache_padding_byte0;
#pragma force_active reset
static u8 state_point_size;
static u8 state_line_width;
static int state_cull_mode;
static int state_blend_type;
static int state_src_factor;
static int state_dst_factor;
static int state_logic_op;
static u8 state_z_enable;
static int state_z_func;
static u8 state_z_update;
static int state_alpha_comp0;
static u8 state_alpha_ref0;
static int state_alpha_op;
static int state_alpha_comp1;
static u8 state_alpha_ref1;
static u8 state_color_update;
static u8 state_alpha_update;
static u8 state_enable_dst_alpha;
static u8 state_dst_alpha;
static u8 state_before_tex;
static u8 state_dither;

struct invalidate_funcs_t {
    int mask;
    void (*func)(void);
} invalidate_funcs[] = {
    { HSD_STATE_PRIMITIVE, _HSD_StateInvalidatePrimitive },
    { HSD_STATE_VTX_ATTR, _HSD_StateInvalidateVtxAttr },
    { HSD_STATE_COLOR_CHANNEL, _HSD_StateInvalidateColorChannel },
    { HSD_STATE_TEV_STAGE, _HSD_StateInvalidateTevStage },
    { HSD_STATE_TEV_REGISTER, _HSD_StateInvalidateTevRegister },
    { HSD_STATE_TEX_COORD_GEN, _HSD_StateInvalidateTexCoordGen },
    { HSD_STATE_RENDER_MODE, _HSD_StateInvalidateRenderMode },
    { HSD_STATE_NONE }
};

void HSD_SetMaterialShininess(f32 shininess)
{
    matstate.shininess = shininess;
}

void HSD_StateSetCullMode(int mode)
{
    if (state_cull_mode != mode) {
        GXSetCullMode(mode);
        state_cull_mode = mode;
    }
}

void HSD_StateSetBlendMode(int type, int src_factor, int dst_factor, int op)
{
    if (state_blend_type != type || state_src_factor != src_factor ||
        state_dst_factor != dst_factor || state_logic_op != op)
    {
        GXSetBlendMode(type, src_factor, dst_factor, op);
        state_blend_type = type;
        state_src_factor = src_factor;
        state_dst_factor = dst_factor;
        state_logic_op = op;
    }
}

void HSD_StateSetZMode(int arg0, int arg1, int arg2)
{
    arg2 = arg2 ? GX_TRUE : GX_FALSE;
    arg0 = arg0 ? GX_TRUE : GX_FALSE;

    if (state_z_enable != (u32) arg0 || state_z_func != arg1 ||
        state_z_update != (u32) arg2)
    {
        GXSetZMode(arg0, arg1, arg2);
        state_z_enable = arg0;
        state_z_func = arg1;
        state_z_update = arg2;
    }
}

void HSD_StateSetAlphaCompare(int arg0, u8 arg1, int arg2, int arg3, u8 arg4)
{
    if (state_alpha_comp0 != arg0 || state_alpha_ref0 != arg1 ||
        state_alpha_op != arg2 || state_alpha_comp1 != arg3 ||
        state_alpha_ref1 != arg4)
    {
        GXSetAlphaCompare(arg0, arg1, arg2, arg3, arg4);
        state_alpha_comp0 = arg0;
        state_alpha_ref0 = arg1;
        state_alpha_op = arg2;
        state_alpha_comp1 = arg3;
        state_alpha_ref1 = arg4;
    }
}

void HSD_StateSetColorUpdate(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_color_update != (u32) arg0) {
        GXSetColorUpdate(arg0);
        state_color_update = arg0;
    }
}

void HSD_StateSetAlphaUpdate(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_alpha_update != (u32) arg0) {
        GXSetAlphaUpdate(arg0);
        state_alpha_update = arg0;
    }
}

void HSD_StateSetDstAlpha(int arg0, u8 arg1)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_enable_dst_alpha != (u32) arg0 || state_dst_alpha != arg1) {
        GXSetDstAlpha(arg0, arg1);
        state_enable_dst_alpha = arg0;
        state_dst_alpha = arg1;
    }
}

void HSD_StateSetZCompLoc(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_before_tex != (u32) arg0) {
        GXSetZCompLoc(arg0);
        state_before_tex = (u8) arg0;
    }
}

void HSD_StateSetDither(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_dither != (u32) arg0) {
        GXSetDither(arg0);
        state_dither = arg0;
    }
}

void _HSD_StateInvalidatePrimitive(void)
{
    state_line_width = 0;
    state_cull_mode = -1;
    state_point_size = 0xFF;
}

void _HSD_StateInvalidateVtxAttr(void)
{
    HSD_ClearVtxDesc();
}

void _HSD_StateInvalidateRenderMode(void)
{
    state_blend_type = -1;
    state_src_factor = -1;
    state_dst_factor = -1;
    state_logic_op = -1;
    state_z_enable = -1;
    state_z_func = -1;
    state_z_update = -1;
    state_alpha_comp0 = -1;
    state_alpha_ref0 = 0;
    state_alpha_op = -1;
    state_alpha_comp1 = -1;
    state_alpha_ref1 = 0;
    state_color_update = -1;
    state_alpha_update = -1;
    state_enable_dst_alpha = -1;
    state_dst_alpha = 0;
    state_before_tex = -1;
    state_dither = -1;
}

void HSD_StateInvalidate(int mask)
{
    int i;
    for (i = 0; invalidate_funcs[i].mask != HSD_STATE_NONE; i++) {
        if (mask & invalidate_funcs[i].mask) {
            invalidate_funcs[i].func();
        }
    }
}
