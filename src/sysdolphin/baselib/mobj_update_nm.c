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
static inline f32 MObjClamp(f32 x, f32 lo, f32 hi)
{
    if (x <= lo) {
        return lo;
    }
    if (x >= hi) {
        return hi;
    }
    return x;
}

void MObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_MObj* mobj = obj;
    HSD_Material* mat;
    HSD_PEDesc* pe;

    if (mobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_M_AMBIENT_R:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->ambient.r = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_AMBIENT_G:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->ambient.g = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_AMBIENT_B:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->ambient.b = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_DIFFUSE_R:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->diffuse.r = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_DIFFUSE_G:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->diffuse.g = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_DIFFUSE_B:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->diffuse.b = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_ALPHA:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->alpha = MObjClamp(1.0F - val->fv, 0.0F, 1.0F);
        }
        break;
    case HSD_A_M_SPECULAR_R:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->specular.r = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_SPECULAR_G:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->specular.g = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_SPECULAR_B:
        mat = mobj->mat;
        if (mat != NULL) {
            mat->specular.b = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_PE_REF0:
        pe = mobj->pe;
        if (pe != NULL) {
            pe->ref0 = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_PE_REF1:
        pe = mobj->pe;
        if (pe != NULL) {
            pe->ref1 = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_M_PE_DSTALPHA:
        pe = mobj->pe;
        if (pe != NULL) {
            pe->dst_alpha = (u8) (255.0F * MObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    }
}

