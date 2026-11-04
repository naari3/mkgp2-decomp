#include "lobj_private.h"

HSD_LObjInfo hsdLObj = { LObjInfoInit };

GXLightID HSD_LObjGetLightMaskDiffuse(void)
{
    return lightmask_diffuse;
}

s32 HSD_LObjGetLightMaskAlpha(void)
{
    return lightmask_alpha;
}

s32 HSD_LObjGetLightMaskSpecular(void)
{
    return lightmask_specular;
}

s32 HSD_LObjGetNbActive(void)
{
    return nb_active_lights;
}

HSD_LObj* HSD_LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < MAX_GXLIGHT) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < MAX_GXLIGHT - 1) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

/// @private
static inline f32 LObjClamp(f32 x, f32 lo, f32 hi)
{
    if (x <= lo) {
        return lo;
    }
    if (x >= hi) {
        return hi;
    }
    return x;
}

void LObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_LObj* lobj = obj;

    if (lobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_L_VIS:
        if (val->fv >= 0.5) {
            lobj->flags &= ~LOBJ_HIDDEN;
        } else {
            lobj->flags |= LOBJ_HIDDEN;
        }
        break;
    case HSD_A_L_A0:
    case HSD_A_L_CUTOFF:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a0 = val->fv;
        } else {
            lobj->u.spot.cutoff = val->fv;
        }
        break;
    case HSD_A_L_A1:
    case HSD_A_L_REFDIST:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a1 = val->fv;
        } else {
            lobj->u.spot.ref_dist = val->fv;
        }
        break;
    case HSD_A_L_A2:
    case HSD_A_L_REFBRIGHT:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a2 = val->fv;
        } else {
            lobj->u.spot.ref_br = val->fv;
        }
        break;
    case HSD_A_L_K0:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k0 = val->fv;
        }
        break;
    case HSD_A_L_K1:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k1 = val->fv;
        }
        break;
    case HSD_A_L_K2:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k2 = val->fv;
        }
        break;
    case HSD_A_L_LITC_R:
        lobj->color.r = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    case HSD_A_L_LITC_G:
        lobj->color.g = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    case HSD_A_L_LITC_B:
        lobj->color.b = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    case HSD_A_L_LITC_A:
        lobj->color.a = (u8) (255.0F * LObjClamp(val->fv, 0.0F, 1.0F));
        break;
    }
}
