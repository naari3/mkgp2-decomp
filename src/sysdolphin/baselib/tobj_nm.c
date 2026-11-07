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
HSD_TObjInfo hsdTObj = { TObjInfoInit };
static char update_imagetbl[0xF] = "tobj->imagetbl";
extern char lbl_806D0C94[7];

static inline f32 TObjClamp(f32 x, f32 lo, f32 hi)
{
    if (x <= lo) {
        return lo;
    }
    if (x >= hi) {
        return hi;
    }
    return x;
}
extern void* tobj_unk_ptr;
extern f32 tobj_unk_f0;
extern f32 tobj_unk_f1;
extern int tobj_unk_flag;
void fn_802D47F4(int);
void TObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_TObj* tobj = obj;

    if (tobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_T_TIMG: {
        int n;
        if (!tobj->imagetbl) {
            __assert(lbl_806D0C94, 385, update_imagetbl);
        }
        n = (int) val->fv;
        if (tobj->imagetbl[n]) {
            tobj->imagedesc = tobj->imagetbl[n];
        }
    } break;
    case HSD_A_T_TCLT: {
        if (tobj->tluttbl) {
            tobj->tlut_no = (int) val->fv;
        }
    } break;
    case HSD_A_T_BLEND:
        tobj->blending = TObjClamp(val->fv, 0.0F, 1.0F);
        break;
    case HSD_A_T_ROTX:
        tobj->rotate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTY:
        tobj->rotate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTZ:
        tobj->rotate.z = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAU:
        tobj->translate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAV:
        tobj->translate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAU:
        tobj->scale.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAV:
        tobj->scale.y = val->fv;
        goto mtxdirty;
    mtxdirty:
        tobj->flags |= TEX_MTX_DIRTY;
        break;
    case HSD_A_T_LOD_BIAS:
        if (tobj->lod) {
            tobj->lod->LODBias = val->fv;
        }
        break;
    case HSD_A_T_KONST_R:
        if (tobj->tev) {
            tobj->tev->konst.r = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_KONST_G:
        if (tobj->tev) {
            tobj->tev->konst.g = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_KONST_B:
        if (tobj->tev) {
            tobj->tev->konst.b = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_KONST_A:
        if (tobj->tev) {
            tobj->tev->konst.a = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV0_R:
        if (tobj->tev) {
            tobj->tev->tev0.r = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV0_G:
        if (tobj->tev) {
            tobj->tev->tev0.g = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV0_B:
        if (tobj->tev) {
            tobj->tev->tev0.b = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV0_A:
        if (tobj->tev) {
            tobj->tev->tev0.a = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV1_R:
        if (tobj->tev) {
            tobj->tev->tev1.r = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV1_G:
        if (tobj->tev) {
            tobj->tev->tev1.g = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV1_B:
        if (tobj->tev) {
            tobj->tev->tev1.b = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TEV1_A:
        if (tobj->tev) {
            tobj->tev->tev1.a = (u8) (255.0F * TObjClamp(val->fv, 0.0F, 1.0F));
        }
        break;
    case HSD_A_T_TS_BLEND:
        tobj->blending = TObjClamp(val->fv, 0.0F, 1.0F);
        break;
    }
}
