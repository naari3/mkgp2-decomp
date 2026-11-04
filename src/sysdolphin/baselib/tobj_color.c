#include "tobj.h"

#include <placeholder.h>
#include <string.h>

#include "aobj.h"
#include "cobj.h"
#include "debug.h"
#include "lobj.h"
#include "memory.h"
#include "mtx.h"
#include "tev.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#define FLT_EPSILON 1.00000001335e-10F

#include "tobj_private.h"
extern void* tobj_unk_ptr;
extern f32 tobj_unk_f0;
extern f32 tobj_unk_f1;
extern int tobj_unk_flag;
void fn_802D47F4(int);
extern char lbl_806D0C94[7];
extern char lbl_806D0CAC[2];
#undef __FILE__
#define __FILE__ lbl_806D0C94
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void) 0 : __assert(__FILE__, line, lbl_806D0CAC))
static inline void TObjSetupTevModulateShadow(HSD_TObj* shadow)
{
    static HSD_TevDesc tevdesc = {
        NULL,           TEVCONF_MODE,  (GXTevStageID) (-1), GX_TEXCOORD_NULL,
        GX_TEXMAP_NULL, GX_COLOR_NULL, GX_TEV_ADD,          GX_CC_ZERO,
        GX_CC_CPREV,    GX_CC_TEXC,    GX_CC_ZERO,          GX_CS_SCALE_1,
        GX_TB_ZERO,     GX_ENABLE,     GX_TEVPREV,          GX_TEV_ADD,
        GX_CA_ZERO,     GX_CA_ZERO,    GX_CA_ZERO,          GX_CA_APREV,
        GX_CS_SCALE_1,  GX_TB_ZERO,    GX_ENABLE,           GX_TEVPREV,
        GX_TC_LINEAR,
    };

    for (; shadow && tobj_coord(shadow) == TEX_COORD_SHADOW;
         shadow = shadow->next)
    {
        tevdesc.stage = HSD_StateAssignTev();
        tevdesc.coord = shadow->coord;
        tevdesc.map = shadow->id;
        HSD_SetupTevStage(&tevdesc);
    }
}

static inline void SetupEmbossBumpTev(HSD_TObj* bump)
{
    static HSD_TevDesc tevdesc = {
        NULL,           TEVCONF_MODE, (GXTevStageID) (-1), GX_TEXCOORD_NULL,
        GX_TEXMAP_NULL, GX_COLOR0A0,  GX_TEV_SUB,          GX_CC_ZERO,
        GX_CC_TEXC,     GX_CC_RASC,   GX_CC_CPREV,         GX_CS_SCALE_1,
        GX_TB_ZERO,     GX_ENABLE,    GX_TEVPREV,          GX_TEV_SUB,
        GX_CA_ZERO,     GX_CA_ZERO,   GX_CA_ZERO,          GX_CA_APREV,
        GX_CS_SCALE_1,  GX_TB_ZERO,   GX_ENABLE,           GX_TEVPREV,
        GX_TC_LINEAR,
    };

    tevdesc.stage = HSD_StateAssignTev();
    tevdesc.coord = bump->coord;
    tevdesc.map = bump->id;
    tevdesc.u.tevconf.clr_op = GX_TEV_ADD;
    tevdesc.u.tevconf.alpha_op = GX_TEV_ADD;
    tevdesc.u.tevconf.clr_clamp = GX_DISABLE;
    HSD_SetupTevStage(&tevdesc);
    tevdesc.stage = HSD_StateAssignTev();
    tevdesc.coord = (GXTexCoordID) (bump->coord + 1);
    tevdesc.u.tevconf.clr_op = GX_TEV_SUB;
    tevdesc.u.tevconf.alpha_op = GX_TEV_SUB;
    tevdesc.u.tevconf.clr_clamp = GX_ENABLE;
    HSD_SetupTevStage(&tevdesc);
}

void HSD_TObjSetupVolatileTev(HSD_TObj* tobj, u32 rendermode)
{
    for (; tobj; tobj = tobj->next) {
        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }

        if (tobj_bump(tobj)) {
            SetupEmbossBumpTev(tobj);
        }

        if (tobj_lightmap(tobj) & TEX_LIGHTMAP_SHADOW) {
            TObjSetupTevModulateShadow(tobj);
            break;
        }
    }
}

void MakeColorGenTExp(u32 lightmap, HSD_TObj* tobj, HSD_TExp** c,
                             HSD_TExp** a, HSD_TExp** list, int repeat)
{
    HSD_TObjTev* tev = tobj->tev;
    u8* in;
    HSD_TExp *e0, *tmp;
    int i;

    HSD_TExp* konst_rgb;
    HSD_TExp* konst_r;
    HSD_TExp* konst_g;
    HSD_TExp* konst_b;
    HSD_TExp* konst_a;
    HSD_TExp* reg0_rgb;
    HSD_TExp* reg0_a;
    HSD_TExp* reg1_rgb;
    HSD_TExp* reg1_a;

    int use_k_rgb = 0;
    int use_k_r = 0;
    int use_k_g = 0;
    int use_k_b = 0;
    int use_k_a = 0;
    int use_reg0_rgb = 0;
    int use_reg0_a = 0;
    int use_reg1_rgb = 0;
    int use_reg1_a = 0;

    in = &tev->color_a;
    for (i = 0; i < 4; i++) {
        switch (in[i]) {
        case TOBJ_TEV_CC_KONST_RGB:
            use_k_rgb = 1;
            break;
        case TOBJ_TEV_CC_KONST_RRR:
            use_k_r = 1;
            break;
        case TOBJ_TEV_CC_KONST_GGG:
            use_k_g = 1;
            break;
        case TOBJ_TEV_CC_KONST_BBB:
            use_k_b = 1;
            break;
        case TOBJ_TEV_CC_KONST_AAA:
            use_k_a = 1;
            break;
        case TOBJ_TEV_CC_TEX0_RGB:
            use_reg0_rgb = 1;
            break;
        case TOBJ_TEV_CC_TEX0_AAA:
            use_reg0_a = 1;
            break;
        case TOBJ_TEV_CC_TEX1_RGB:
            use_reg1_rgb = 1;
            break;
        case TOBJ_TEV_CC_TEX1_AAA:
            use_reg1_a = 1;
            break;
        default:
            break;
        }
    }
    in = &tev->alpha_a;
    for (i = 0; i < 4; i++) {
        switch (in[i]) {
        case TOBJ_TEV_CA_KONST_R:
            use_k_r = 1;
            break;
        case TOBJ_TEV_CA_KONST_G:
            use_k_g = 1;
            break;
        case TOBJ_TEV_CA_KONST_B:
            use_k_b = 1;
            break;
        case TOBJ_TEV_CA_KONST_A:
            use_k_a = 1;
            break;
        case TOBJ_TEV_CA_TEX0_A:
            use_reg0_a = 1;
            break;
        case TOBJ_TEV_CA_TEX1_A:
            use_reg1_a = 1;
            break;
        default:
            break;
        }
    }

    if (use_k_rgb) {
        konst_rgb =
            HSD_TExpCnst(&tobj->tev->konst, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_k_r) {
        konst_r = HSD_TExpCnst(&tobj->tev->konst.r, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_g) {
        konst_g = HSD_TExpCnst(&tobj->tev->konst.g, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_b) {
        konst_b = HSD_TExpCnst(&tobj->tev->konst.b, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_a) {
        konst_a = HSD_TExpCnst(&tobj->tev->konst.a, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_reg0_rgb) {
        reg0_rgb = HSD_TExpCnst(&tobj->tev->tev0, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_reg0_a) {
        reg0_a = HSD_TExpCnst(&tobj->tev->tev0.a, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_reg1_rgb) {
        reg1_rgb = HSD_TExpCnst(&tobj->tev->tev1, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_reg1_a) {
        reg1_a = HSD_TExpCnst(&tobj->tev->tev1.a, HSD_TE_X, HSD_TE_U8, list);
    }

    e0 = HSD_TExpTev(list);
    HSD_TExpOrder(e0, tobj, GX_COLOR_NULL);

    if (tev->active & TOBJ_TEVREG_ACTIVE_COLOR_TEV) {
        HSD_TEInput sel[4];
        HSD_TExp* exp[4];
        int i;

        in = &tev->color_a;
        for (i = 0; i < 4; i++) {
            switch (in[i]) {
            case GX_CC_ZERO:
                sel[i] = HSD_TE_0;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_ONE:
                sel[i] = HSD_TE_1;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_HALF:
                sel[i] = HSD_TE_4_8;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_TEXC:
                sel[i] = HSD_TE_RGB;
                exp[i] = HSD_TEXP_TEX;
                break;
            case GX_CC_TEXA:
                sel[i] = HSD_TE_A;
                exp[i] = HSD_TEXP_TEX;
                break;
            case TOBJ_TEV_CC_KONST_RGB:
                sel[i] = HSD_TE_RGB;
                exp[i] = konst_rgb;
                break;
            case TOBJ_TEV_CC_KONST_RRR:
                sel[i] = HSD_TE_X;
                exp[i] = konst_r;
                break;
            case TOBJ_TEV_CC_KONST_GGG:
                sel[i] = HSD_TE_X;
                exp[i] = konst_g;
                break;
            case TOBJ_TEV_CC_KONST_BBB:
                sel[i] = HSD_TE_X;
                exp[i] = konst_b;
                break;
            case TOBJ_TEV_CC_KONST_AAA:
                sel[i] = HSD_TE_X;
                exp[i] = konst_a;
                break;
            case TOBJ_TEV_CC_TEX0_RGB:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_RGB, reg0_rgb);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX0_AAA:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg0_a);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX1_RGB:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_RGB, reg1_rgb);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX1_AAA:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg1_a);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            default:
                HSD_ASSERT(1359, 0);
                break;
            }
        }

        HSD_TExpColorOp(e0, (GXTevOp) tev->color_op,
                        (GXTevBias) tev->color_bias,
                        (GXTevScale) tev->color_scale, tev->color_clamp);
        HSD_TExpColorIn(e0, sel[0], exp[0], sel[1], exp[1], sel[2], exp[2],
                        sel[3], exp[3]);
        *c = e0;
    }

    if (tev->active & TOBJ_TEVREG_ACTIVE_ALPHA_TEV) {
        HSD_TEInput sel[4];
        HSD_TExp* exp[4];
        int i;

        in = &tev->alpha_a;
        for (i = 0; i < 4; i++) {
            switch (in[i]) {
            case GX_CA_ZERO:
                sel[i] = HSD_TE_0;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CA_TEXA:
                sel[i] = HSD_TE_A;
                exp[i] = HSD_TEXP_TEX;
                break;
            case TOBJ_TEV_CA_KONST_R:
                sel[i] = HSD_TE_X;
                exp[i] = konst_r;
                break;
            case TOBJ_TEV_CA_KONST_G:
                sel[i] = HSD_TE_X;
                exp[i] = konst_g;
                break;
            case TOBJ_TEV_CA_KONST_B:
                sel[i] = HSD_TE_X;
                exp[i] = konst_b;
                break;
            case TOBJ_TEV_CA_KONST_A:
                sel[i] = HSD_TE_X;
                exp[i] = konst_a;
                break;
            case TOBJ_TEV_CA_TEX0_A:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpAlphaOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpAlphaIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg0_a);
                sel[i] = HSD_TE_A;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CA_TEX1_A:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpAlphaOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpAlphaIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg1_a);
                sel[i] = HSD_TE_A;
                exp[i] = tmp;
                break;
            default:
                HSD_ASSERT(1432, 0);
                break;
            }
        }

        HSD_TExpAlphaOp(e0, (GXTevOp) tev->alpha_op,
                        (GXTevBias) tev->alpha_bias,
                        (GXTevScale) tev->alpha_scale, tev->alpha_clamp);
        HSD_TExpAlphaIn(e0, sel[0], exp[0], sel[1], exp[1], sel[2], exp[2],
                        sel[3], exp[3]);

        *a = e0;
    }
}
