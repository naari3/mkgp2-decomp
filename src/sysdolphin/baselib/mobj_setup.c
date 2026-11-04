#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

#include "mobj_private.h"
extern char lbl_806D0CE8[7];
extern char lbl_806D0CF0[5];
extern char lbl_806D0D00[4];
extern char lbl_806D0D04[5];
extern char lbl_804FC270[14];
#undef __FILE__
#define __FILE__ lbl_806D0CE8
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void) 0 : __assert(__FILE__, line, (line) == 839 ? lbl_804FC270 : (line) == 1148 ? lbl_806D0CF0 : (line) == 1176 ? lbl_806D0D00 : lbl_806D0D04))
void HSD_MObjCompileTev(HSD_MObj* mobj)
{
    HSD_TObj *tobj, **tail;
    HSD_TExp* texp;

    tail = NULL;
    if (mobj != NULL) {
        if (mobj->tevdesc != NULL) {
            HSD_TExpFreeTevDesc(mobj->tevdesc);
            mobj->tevdesc = NULL;
        }
        if (mobj->texp != NULL) {
            HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
            mobj->texp = NULL;
        }
        tobj = mobj->tobj;
        if (mobj->rendermode & RENDER_SHADOW) {
            if (tobj_shadows != NULL) {
                tail = &tobj;
                while (*tail != NULL) {
                    tail = &(*tail)->next;
                }
                *tail = tobj_shadows;
            }
        }
        if (mobj->rendermode & RENDER_TOON) {
            if (tobj_toon != NULL && tobj_toon->imagedesc != NULL) {
                tobj_toon->next = tobj;
                tobj = tobj_toon;
            }
        }
        HSD_TObjAssignResources(tobj);
        texp = HSD_MOBJ_METHOD(mobj)->make_texp(mobj, tobj, &mobj->texp);
        HSD_TExpCompile(texp, &mobj->tevdesc, &mobj->texp);
        if (tail != NULL) {
            *tail = NULL;
        }
    }
}

void HSD_MObjSetTevStageCallback(void (*cb)(int))
{
    tev_stage_callback = cb;
}

void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 arg2)
{
    HSD_ASSERT(839, mobj->tevdesc);
    if (tev_stage_callback != NULL) {
        HSD_StateAssignTev();
    }
    HSD_TExpSetupTev(mobj->tevdesc, mobj->texp);
    HSD_TObjSetupVolatileTev(tobj, arg2);
    if (tev_stage_callback != NULL) {
        tev_stage_callback(HSD_StateGetNumTevStages() - 1);
    }
}

void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObj *tobj, **tail;

    if (mobj_override_enable == 1) {
        mobj = mobj_override;
    }
    HSD_StateInitTev();
    rendermode = mobj->rendermode;
    HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                         mobj->mat->specular, mobj->mat->alpha);
    if (rendermode & RENDER_SPECULAR) {
        HSD_SetMaterialShininess(mobj->mat->shininess);
    }

    tobj = mobj->tobj;
    tail = NULL;

    if ((rendermode & RENDER_SHADOW) && tobj_shadows != NULL) {
        tail = &tobj;
        while (*tail != NULL) {
            tail = &(*tail)->next;
        }
        *tail = tobj_shadows;
    }
    if ((rendermode & RENDER_TOON) && tobj_toon != NULL &&
        tobj_toon->imagedesc != NULL)
    {
        tobj_toon->next = tobj;
        tobj = tobj_toon;
    }
    HSD_TObjSetup(tobj);
    HSD_TObjSetupTextureCoordGen(tobj);
    HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj, rendermode);
    HSD_SetupRenderModeWithCustomPE(rendermode, mobj->pe);
    if (tail != NULL) {
        *tail = NULL;
    }
}

void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObjSetup(NULL);
}

#ifndef MUST_MATCH
static HSD_TObjDesc tobj_toon_desc = { NULL,
                                       NULL,
                                       GX_TEXMAP7,
                                       GX_TG_COLOR0,
                                       { 0.0F, 0.0F, 0.0F },
                                       { 0.0F, 0.0F, 0.0F },
                                       { 0.0F, 0.0F, 0.0F },
                                       GX_CLAMP,
                                       GX_CLAMP,
                                       0,
                                       0,
                                       TEX_COORD_TOON,
                                       1.0F,
                                       GX_LINEAR,
                                       0,
                                       NULL,
                                       NULL };

void HSD_MObjSetToonTextureImage(HSD_ImageDesc* imagedesc)
{
    if (tobj_toon == NULL) {
        tobj_toon_desc.imagedesc = imagedesc;
        tobj_toon = HSD_TObjLoadDesc(&tobj_toon_desc);
        HSD_ASSERTREPORT(0x2F8, tobj_toon, "cannot allocate tobj for toon.");
    }
    tobj_toon->imagedesc = imagedesc;
}

void HSD_MObjSetDiffuseColor(HSD_MObj* mobj, u8 r, u8 g, u8 b)
{
    mobj->mat->diffuse.r = r;
    mobj->mat->diffuse.g = g;
    mobj->mat->diffuse.b = b;
}

void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha)
{
    mobj->mat->alpha = alpha;
}

#endif
HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return NULL;
    }
    return mobj->tobj;
}

void HSD_MObjRemove(HSD_MObj* mobj)
{
    hsdDelete(mobj);
}

HSD_MObj* HSD_MObjAlloc(void)
{
    HSD_MObj* mobj =
        hsdNew(default_class != NULL ? default_class : &hsdMObj.parent);
    HSD_ASSERT(1148, mobj);
    return mobj;
}

void fn_802C3818(HSD_MObj* mobj)
{
    if (mobj != NULL) {
        HSD_CLASS_METHOD(mobj)->destroy((HSD_Class*) mobj);
    }
}
