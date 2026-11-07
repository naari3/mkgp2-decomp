#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

extern char lbl_804FC24C[0x22];
extern char lbl_806D0CE8[7];
extern char lbl_806D0CF0[5];
extern char lbl_806D0CF8[5];
extern unsigned char lbl_806D0CF5[3];

void MObjUpdateFunc(void*, enum_t, HSD_ObjData*);
extern HSD_ClassInfo* default_class;
extern HSD_MObj* current_mobj;
HSD_TObj* tobj_toon;
HSD_TObj* tobj_shadows;
HSD_MObj* mobj_override;
int mobj_override_enable;
void (*tev_stage_callback)(int);
HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list)
{
    HSD_TExp *diff, *spec, *ext, *alpha;
    HSD_TExp *exp, *exp_3;
    HSD_TExp* cnst;
    HSD_TObj *tobj, *tobj_2, *tobj_3, *tobj_4, *toon = NULL;
    u32 done = 0;

    u32 diffuse_src, alpha_src;

    if (!list) {
        __assert(lbl_806D0CE8, 428, lbl_806D0CF8);
    }
    *list = NULL;
    for (tobj = tobj_top; tobj != NULL; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            toon = tobj;
        }
    }

    diffuse_src = mobj->rendermode & RENDER_DIFFUSE_BITS;
    if (diffuse_src == RENDER_DIFFUSE_MAT0) {
        diffuse_src = RENDER_DIFFUSE_MAT;
    }
    alpha_src = mobj->rendermode & RENDER_ALPHA_BITS;
    if (alpha_src == RENDER_ALPHA_COMPAT) {
        alpha_src = diffuse_src << RENDER_ALPHA_SHIFT;
    }

    exp = HSD_TExpTev(list);
    if (mobj->rendermode & RENDER_DIFFUSE) {
        switch (diffuse_src) {
        case RENDER_DIFFUSE_VTX:
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_1, HSD_TEXP_ZERO);
            break;
        default: {
            cnst = HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, cnst);
            break;
        }
        }
        switch (alpha_src) {
        case RENDER_ALPHA_VTX: {
            cnst = HSD_TExpCnst(lbl_806D0CF5, HSD_TE_X, HSD_TE_U8, list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, cnst);
            break;
        }
        default: {
            cnst = HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, cnst);
            break;
        }
        }
    } else {
        switch (diffuse_src) {
        case RENDER_DIFFUSE_MAT: {
            cnst = HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, cnst);
            break;
        }
        case RENDER_DIFFUSE_VTX:
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB,
                           toon ? HSD_TEXP_TEX : HSD_TEXP_RAS);
            break;
        default: {
            cnst = HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_RGB, toon ? HSD_TEXP_TEX : HSD_TEXP_RAS,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_RGB, cnst);
            break;
        }
        }
        switch (alpha_src) {
        case RENDER_ALPHA_MAT: {
            cnst = HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, cnst);
            break;
        }
        case RENDER_ALPHA_VTX:
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS);
            break;
        default: {
            cnst = HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS,
                           HSD_TE_X, cnst, HSD_TE_0, HSD_TEXP_ZERO);
            break;
        }
        }
    }
    diff = exp;
    alpha = exp;

    for (tobj_2 = tobj_top; tobj_2 != NULL; tobj_2 = tobj_2->next) {
        if ((tobj_2->flags & (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT)) &&
            tobj_2->id != GX_TEXMAP_NULL)
        {
            HSD_TOBJ_METHOD(tobj_2)->make_texp(
                tobj_2, (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT), done,
                &diff, &alpha, list);
        }
    }
    done |= (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT);

    if (mobj->rendermode & RENDER_DIFFUSE) {
        HSD_TExp* exp_2;
        u32 alpha_vtx = alpha_src & RENDER_ALPHA_VTX;
        if (alpha_vtx) {
            exp_2 = HSD_TExpTev(list);
            HSD_TExpOrder(exp_2, NULL, GX_COLOR1A1);
            HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff);
            HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp_2, HSD_TE_A, alpha, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
            diff = exp_2;
            alpha = exp_2;
        }
        exp_2 = HSD_TExpTev(list);
        if (toon != NULL) {
            HSD_TExpOrder(exp_2, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_TEX, HSD_TE_0, HSD_TEXP_ZERO);
        } else {
            HSD_TExpOrder(exp_2, NULL, GX_COLOR0A0);
            HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        }
        diff = exp_2;
        if (alpha_vtx) {
            HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, alpha,
                           HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        } else {
            HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp_2, HSD_TE_A, alpha, HSD_TE_0, HSD_TEXP_ZERO,
                           HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        }
        alpha = exp_2;
    }

    if (mobj->rendermode & RENDER_SPECULAR) {
        cnst =
            HSD_TExpCnst(&mobj->mat->specular, HSD_TE_RGB, HSD_TE_U8, list);
        exp_3 = HSD_TExpTev(list);
        HSD_TExpColorOp(exp_3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_3, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB,
                        cnst);
        spec = exp_3;

        for (tobj_3 = tobj_top; tobj_3 != NULL; tobj_3 = tobj_3->next) {
            if ((tobj_3->flags & TEX_LIGHTMAP_SPECULAR) &&
                tobj_3->id != GX_TEXMAP_NULL)
            {
                HSD_TOBJ_METHOD(tobj_3)->make_texp(
                    tobj_3, TEX_LIGHTMAP_SPECULAR, done, &spec, &alpha, list);
            }
        }
        done |= TEX_LIGHTMAP_SPECULAR;

        exp_3 = HSD_TExpTev(list);
        HSD_TExpOrder(exp_3, NULL, GX_COLOR1A1);
        HSD_TExpColorOp(exp_3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_3, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, spec,
                        HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        spec = exp_3;

        exp_3 = HSD_TExpTev(list);
        HSD_TExpColorOp(exp_3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_3, HSD_TE_RGB, spec, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff);
        diff = exp_3;
    }

    ext = diff;

    for (tobj_4 = tobj_top; tobj_4 != NULL; tobj_4 = tobj_4->next) {
        if ((tobj_4->flags & TEX_LIGHTMAP_EXT) && tobj_4->id != GX_TEXMAP_NULL)
        {
            HSD_TOBJ_METHOD(tobj_4)->make_texp(tobj_4, TEX_LIGHTMAP_EXT, done,
                                               &ext, &alpha, list);
        }
    }

    if (ext != alpha || HSD_TExpGetType(ext) != HSD_TE_TEV ||
        HSD_TExpGetType(alpha) != HSD_TE_TEV)
    {
        HSD_TExp* exp_2 = HSD_TExpTev(list);
        HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB,
                        ext);
        HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpAlphaIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                        alpha);
        return exp_2;
    }

    return ext;
}
