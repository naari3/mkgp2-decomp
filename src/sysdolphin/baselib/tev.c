#include "tev.h"

#include <string.h>

#include "debug.h"
#include "mobj.h"
#include <dolphin/gx.h>

static struct TevReg_t {
    GXColorS10 a;
    int c;
} TevReg[4] = { 0 };

static HSD_Chan prev_ch[4] = {
    { NULL, 0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
    { NULL, 1, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
    { NULL, 2, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
    { NULL, 3, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
};

HSD_ObjAllocData render_alloc_data;
HSD_ObjAllocData tevreg_alloc_data;
HSD_ObjAllocData chan_alloc_data;

static int current_tev;
static int prev_amb_invalid[2];
static int prev_mat_invalid[2];
static int prev_num_chans;
static int num_tex_gens;

void HSD_RenderInitAllocData(void)
{
    HSD_ObjAllocInit(&render_alloc_data, 28, 4);
    HSD_ObjAllocInit(&tevreg_alloc_data, 20, 4);
    HSD_ObjAllocInit(&chan_alloc_data, sizeof(HSD_Chan), 4);
}

HSD_ObjAllocData* HSD_RenderGetAllocData(void)
{
    return &render_alloc_data;
}

HSD_ObjAllocData* HSD_TevRegGetAllocData(void)
{
    return &tevreg_alloc_data;
}

HSD_ObjAllocData* HSD_ChanGetAllocData(void)
{
    return &chan_alloc_data;
}

static bool CompareRGB(GXColor* c0, GXColor* c1)
{
    u32* d0 = (u32*) c0;
    u32* d1 = (u32*) c1;
    return ((*d0 ^ *d1) & 0xFFFFFF00) != 0;
}

static bool CompareRGBA(GXColor* c0, GXColor* c1)
{
    u32* d0 = (u32*) c0;
    u32* d1 = (u32*) c1;
    return *d0 != *d1;
}

static void CopyRGB(GXColor* dst, GXColor* src)
{
    u32* d = (u32*) dst;
    u32* s = (u32*) src;
    *d = (*d & 0xff) | (*s & 0xffffff00);
}

void HSD_SetupChannel(HSD_Chan* ch)
{
    int idx;
    GXChannelID chan;
    int no;

    if (ch == NULL || ch->chan == GX_COLOR_NULL) {
        return;
    }

    chan = ch->chan;
    idx = chan & 3;
    no = chan & 1;
    if (ch->enable != GX_DISABLE && ch->amb_src == GX_SRC_REG) {
        if (prev_amb_invalid[no] != 0) {
            prev_amb_invalid[no] = 0;
            GXSetChanAmbColor(no + 4, ch->amb_color);
            prev_ch[no].amb_color = ch->amb_color;
        } else if (chan == GX_COLOR0A0 || chan == GX_COLOR1A1) {
            if (CompareRGBA(&ch->amb_color, &prev_ch[no].amb_color)) {
                prev_ch[no].amb_color = ch->amb_color;
                goto set_amb;
            }
        } else if (chan == GX_COLOR0 || chan == GX_COLOR1) {
            if (CompareRGB(&ch->amb_color, &prev_ch[no].amb_color)) {
                CopyRGB(&prev_ch[no].amb_color, &ch->amb_color);
                goto set_amb;
            }
        } else if (ch->amb_color.a != prev_ch[no].amb_color.a) {
            prev_ch[no].amb_color.a = ch->amb_color.a;
        set_amb:
            GXSetChanAmbColor(chan, ch->amb_color);
        }
    }

    if (ch->mat_src == GX_SRC_REG) {
        if (prev_mat_invalid[no] != 0) {
            prev_mat_invalid[no] = 0;
            GXSetChanMatColor(no + 4, ch->mat_color);
            prev_ch[no].mat_color = ch->mat_color;
        } else if (chan == GX_COLOR0A0 || chan == GX_COLOR1A1) {
            if (CompareRGBA(&ch->mat_color, &prev_ch[no].mat_color)) {
                prev_ch[no].mat_color = ch->mat_color;
                goto set_mat;
            }
        } else if (chan == GX_COLOR0 || chan == GX_COLOR1) {
            if (CompareRGB(&ch->mat_color, &prev_ch[no].mat_color)) {
                CopyRGB(&prev_ch[no].mat_color, &ch->mat_color);
                goto set_mat;
            }
        } else if (ch->mat_color.a != prev_ch[no].mat_color.a) {
            prev_ch[no].mat_color.a = ch->mat_color.a;
        set_mat:
            GXSetChanMatColor(chan, ch->mat_color);
        }
    }

    if ((ch->enable != prev_ch[idx].enable) ||
        (ch->amb_src != prev_ch[idx].amb_src) ||
        (ch->mat_src != prev_ch[idx].mat_src) ||
        (ch->light_mask != prev_ch[idx].light_mask) ||
        (ch->diff_fn != prev_ch[idx].diff_fn) ||
        (ch->attn_fn != prev_ch[idx].attn_fn))
    {
        GXSetChanCtrl(chan, ch->enable, ch->amb_src, ch->mat_src,
                      ch->light_mask, ch->diff_fn, ch->attn_fn);
        prev_ch[idx].enable = ch->enable;
        prev_ch[idx].amb_src = ch->amb_src;
        prev_ch[idx].mat_src = ch->mat_src;
        prev_ch[idx].light_mask = ch->light_mask;
        prev_ch[idx].diff_fn = ch->diff_fn;
        prev_ch[idx].attn_fn = ch->attn_fn;
        if (chan == GX_COLOR0A0 || chan == GX_COLOR1A1) {
            prev_ch[idx + 2].enable = ch->enable;
            prev_ch[idx + 2].amb_src = ch->amb_src;
            prev_ch[idx + 2].mat_src = ch->mat_src;
            prev_ch[idx + 2].light_mask = ch->light_mask;
            prev_ch[idx + 2].diff_fn = ch->diff_fn;
            prev_ch[idx + 2].attn_fn = ch->attn_fn;
        }
    }
}

void HSD_DisableChannel(GXChannelID chan)
{
    int idx = chan & 3;

    switch (chan) {
    case GX_COLOR0A0:
    case GX_COLOR1A1:
        if (prev_ch[idx].enable != GX_DISABLE ||
            prev_ch[idx + 2].enable != GX_DISABLE)
        {
            GXAttnFn attn_fn;
            GXDiffuseFn diff_fn;
            GXColorSrc mat_src;
            GXColorSrc amb_src;
            prev_ch[idx + 2].enable = GX_DISABLE;
            prev_ch[idx].enable = GX_DISABLE;
            prev_ch[idx + 2].light_mask = 0;
            prev_ch[idx].light_mask = 0;
            amb_src = prev_ch[idx].amb_src;
            mat_src = prev_ch[idx].mat_src;
            diff_fn = prev_ch[idx].diff_fn;
            attn_fn = prev_ch[idx].attn_fn;
            prev_ch[idx + 2].amb_src = amb_src;
            prev_ch[idx + 2].mat_src = mat_src;
            prev_ch[idx + 2].diff_fn = diff_fn;
            prev_ch[idx + 2].attn_fn = attn_fn;
            GXSetChanCtrl(chan, GX_DISABLE, amb_src, mat_src, 0, diff_fn,
                          attn_fn);
        }
        break;
    default:
        if (prev_ch[idx].enable != GX_DISABLE) {
            prev_ch[idx].enable = GX_DISABLE;
            prev_ch[idx].light_mask = 0;
            GXSetChanCtrl(chan, GX_DISABLE, prev_ch[idx].amb_src,
                          prev_ch[idx].mat_src, 0, prev_ch[idx].diff_fn,
                          prev_ch[idx].attn_fn);
        }
        break;
    }
}

void HSD_StateSetNumChans(int num)
{
    if (prev_num_chans != num) {
        GXSetNumChans(num);
        prev_num_chans = num;
    }
}

void HSD_SetupChannelAll(HSD_Chan* channel)
{
    int num = 0;
    while (channel != NULL) {
        int temp = HSD_Channel2Num(channel->chan);
        if (temp > num) {
            num = temp;
        }
        HSD_SetupChannel(channel);
        channel = channel->next;
    }
    HSD_StateSetNumChans((u8) num);
}

int HSD_TexCoordID2Num(int);

void HSD_StateRegisterTexGen(int coord)
{
    int temp_r3 = HSD_TexCoordID2Num(coord);
    if (temp_r3 > num_tex_gens) {
        num_tex_gens = temp_r3;
    }
}

void HSD_StateSetNumTexGens(void)
{
    GXSetNumTexGens(num_tex_gens);
    num_tex_gens = 0;
}

void HSD_StateInitTev(void)
{
    current_tev = 0;
}

int HSD_StateGetNumTevStages(void)
{
    return current_tev;
}

int HSD_StateAssignTev(void)
{
    return HSD_Index2TevStage(current_tev++);
}

void HSD_StateSetNumTevStages(void)
{
    GXSetNumTevStages(current_tev);
    current_tev = 0;
}

void HSD_SetupTevStage(HSD_TevDesc* desc)
{
    u8 _[8];
    GXSetTevOrder(desc->stage, desc->coord, desc->map, desc->color);
    if (desc->flags == 0) {
        GXSetTevOp(desc->stage, (GXTevMode) desc->u.tevconf.clr_op);
        GXSetTevSwapMode(desc->stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        return;
    }
    GXSetTevColorOp(desc->stage, desc->u.tevconf.clr_op,
                    desc->u.tevconf.clr_bias, desc->u.tevconf.clr_scale,
                    desc->u.tevconf.clr_clamp, desc->u.tevconf.clr_out_reg);
    GXSetTevColorIn(desc->stage, desc->u.tevconf.clr_a, desc->u.tevconf.clr_b,
                    desc->u.tevconf.clr_c, desc->u.tevconf.clr_d);
    GXSetTevAlphaOp(desc->stage, desc->u.tevconf.alpha_op,
                    desc->u.tevconf.alpha_bias, desc->u.tevconf.alpha_scale,
                    desc->u.tevconf.alpha_clamp,
                    desc->u.tevconf.alpha_out_reg);
    GXSetTevAlphaIn(desc->stage, desc->u.tevconf.alpha_a,
                    desc->u.tevconf.alpha_b, desc->u.tevconf.alpha_c,
                    desc->u.tevconf.alpha_d);
    GXSetTevSwapMode(desc->stage, desc->u.tevconf.ras_swap,
                     desc->u.tevconf.tex_swap);
    GXSetTevKColorSel(desc->stage, desc->u.tevconf.kcsel);
    GXSetTevKAlphaSel(desc->stage, desc->u.tevconf.kasel);
}

static inline int setupTevStages(HSD_TevDesc* desc)
{
    int num = 0;

    while (desc != NULL) {
        int temp = HSD_TevStage2Num(desc->stage);
        if (temp > num) {
            num = temp;
        }
        HSD_SetupTevStage(desc);
        desc = desc->next;
    }
    return num;
}

void HSD_SetupTevStageAll(HSD_TevDesc* desc)
{
    current_tev = setupTevStages(desc);
    HSD_StateSetNumTevStages();
}

int HSD_Channel2Num(int chan)
{
    switch (chan) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 1;
    case 3:
        return 2;
    case 4:
        return 1;
    case 5:
        return 2;
    case 0xFF:
        return 0;
    default:
        HSD_ASSERT(722, 0);
        return 0;
    }
}

int HSD_Index2TevStage(int idx)
{
    switch (idx) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    case 11:
        return 11;
    case 12:
        return 12;
    case 13:
        return 13;
    case 14:
        return 14;
    case 15:
        return 15;
    default:
        HSD_ASSERT(775, 0);
        return 15;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif
#ifdef MUST_MATCH
#pragma pop
#endif

int HSD_TevStage2Num(int stage)
{
    switch (stage) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    case 5:
        return 6;
    case 6:
        return 7;
    case 7:
        return 8;
    case 8:
        return 9;
    case 9:
        return 10;
    case 10:
        return 11;
    case 11:
        return 12;
    case 12:
        return 13;
    case 13:
        return 14;
    case 14:
        return 15;
    case 15:
        return 16;
    default:
        HSD_ASSERT(859, 0);
        return 0;
    }
}

static inline int TevRegID(u32 i)
{
    switch (i) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 0;
    default:
        return 1;
    }
}

void HSD_SetTevRegAll(void)
{
    u32 i;
    for (i = 0; i < 4; i++) {
        if (TevReg[i].c != 0) {
            GXSetTevColorS10(TevRegID(i), TevReg[i].a);
            TevReg[i].c = 0;
        }
    }
}

int HSD_TexCoordID2Num(int id)
{
    switch (id) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    case 5:
        return 6;
    case 6:
        return 7;
    case 7:
        return 8;
    case 0xFF:
        return 0;
    default:
        HSD_ASSERT(1076, 0);
        return 0;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif
#ifdef MUST_MATCH
#pragma pop
#endif

static HSD_Chan invalid_prev_ch[4] = {
    { NULL, 0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
    { NULL, 1, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
    { NULL, 2, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
    { NULL, 3, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0xFF, 0, 0, 0, 0, 2, NULL },
};

void _HSD_StateInvalidateColorChannel(void)
{
    memcpy(&prev_ch, &invalid_prev_ch, sizeof(prev_ch));
    prev_amb_invalid[0] = 1;
    prev_amb_invalid[1] = 1;
    prev_mat_invalid[0] = 1;
    prev_mat_invalid[1] = 1;
    prev_num_chans = -1;
}

void _HSD_StateInvalidateTevStage(void)
{
    current_tev = 0;
}

void _HSD_StateInvalidateTevRegister(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        TevReg[i].c = 0;
    }
}

void _HSD_StateInvalidateTexCoordGen(void)
{
    num_tex_gens = 0;
}

/* Newer HSD: a material loaded from a descriptor and kept as current state.
 * The variables live in mobj.c's .sbss. */
extern HSD_MObj* lbl_806D2140;
extern int lbl_806D2144;
void fn_802C3974(HSD_MObj* mobj);
void fn_802C3818(HSD_MObj* mobj);

void fn_802C2238(void)
{
    if (lbl_806D2140 != NULL) {
        fn_802C3974(lbl_806D2140);
        fn_802C3818(lbl_806D2140);
        lbl_806D2140 = NULL;
    }
}

void fn_802C2274(HSD_MObjDesc* desc)
{
    if (desc == NULL) {
        lbl_806D2144 = 0;
        return;
    }
    lbl_806D2144 = 1;
    if (lbl_806D2140 != NULL) {
        fn_802C3974(lbl_806D2140);
        fn_802C3818(lbl_806D2140);
    }
    lbl_806D2140 = HSD_MObjLoadDesc(desc);
}
