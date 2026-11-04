#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

void MObjUpdateFunc(void*, enum_t, HSD_ObjData*);
extern HSD_ClassInfo* default_class;
extern HSD_MObj* current_mobj;
HSD_TObj* tobj_toon;
HSD_TObj* tobj_shadows;
HSD_MObj* mobj_override;
int mobj_override_enable;
void (*tev_stage_callback)(int);
int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
{
    mobj->rendermode = desc->rendermode;
    mobj->tobj = HSD_TObjLoadDesc(desc->texdesc);
    mobj->mat = HSD_MaterialAlloc();
    memcpy(mobj->mat, desc->mat, sizeof(HSD_Material));
    mobj->rendermode |= RENDER_TOON;
    if (desc->pedesc != NULL) {
        mobj->pe = hsdAllocMemPiece(sizeof(HSD_PEDesc));
        memcpy(mobj->pe, desc->pedesc, sizeof(HSD_PEDesc));
    }
    mobj->aobj = NULL;
    return 0;
}

void HSD_MObjSetDefaultClass(HSD_MObjInfo* info)
{
    if (info) {
        HSD_ASSERT(367, hsdIsDescendantOf(HSD_CLASS_INFO(info), HSD_CLASS_INFO(&hsdMObj)));
    }
    default_class = HSD_CLASS_INFO(info);
}

HSD_ClassInfo* HSD_MObjGetDefaultClass(void)
{
    return default_class != NULL ? default_class : HSD_CLASS_INFO(&hsdMObj);
}

HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    if (mobjdesc) {
        HSD_MObj* mobj;
        HSD_ClassInfo* info;

        if (!mobjdesc->class_name ||
            !(info = hsdSearchClassInfo(mobjdesc->class_name)))
        {
            mobj = HSD_MObjAlloc();
        } else {
            mobj = hsdNew(info);
            HSD_ASSERT(406, mobj);
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}

HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list)
{
    HSD_TExp *diff, *spec, *ext, *alpha;
    HSD_TExp *exp, *exp_2, *exp_3;
    HSD_TObj *tobj, *tobj_2, *tobj_3, *tobj_4, *toon = NULL;
    u32 done = 0;

    u8 _[20];

    HSD_ASSERT(416, list);
    *list = NULL;
    for (tobj = tobj_top; tobj != NULL; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            toon = tobj;
        }
    }

    if (mobj->rendermode & RENDER_VERTEX) {
        exp = HSD_TExpTev(list);
        HSD_TExpOrder(exp, NULL, GX_COLOR0A0);
        HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, HSD_TEXP_RAS);
        HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS);
        diff = exp;
        alpha = exp;
    } else {
        HSD_TExp* diff_cnst =
            HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
        HSD_TExp* alpha_cnst =
            HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32, list);

        exp = HSD_TExpTev(list);
        HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff_cnst);
        HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, alpha_cnst);
        diff = exp;
        alpha = exp;
    }

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
        HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpAlphaIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, alpha,
                        HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        alpha = exp_2;
    }

    if (mobj->rendermode & RENDER_SPECULAR) {
        HSD_TExp* cnst =
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
        exp_2 = HSD_TExpTev(list);
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
