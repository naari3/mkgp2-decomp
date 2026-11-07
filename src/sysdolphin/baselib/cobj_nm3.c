#include "cobj_private.h"

extern inline HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj)
{
    COBJ_ASSERT(700, cobj, lbl_806D0D58);
    return cobj->interest;
}

extern inline HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj)
{
    COBJ_ASSERT(724, cobj, lbl_806D0D58);
    return cobj->eyepos;
}

extern inline void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest)
{
    COBJ_ASSERT(748, cobj, lbl_806D0D58);
    HSD_WObjGetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

extern inline void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    COBJ_ASSERT(772, cobj, lbl_806D0D58);
    HSD_WObjGetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

extern inline int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye)
{
    Vec3 eyepos;
    Vec3 interest;

    int result;
    if (!cobj || !cobj->eyepos || !cobj->interest || !eye) {
        result = 0;
    } else {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetInterest(cobj, &interest);
        VECSubtract(&interest, &eyepos, eye);
        result = vec_normalize_check(eye, eye) == 0;
    }
    return result;
}

extern inline float cobj_absf(float x)
{
    x = fabs(x);
    return x;
}

extern inline float upvec2roll(HSD_CObj* cobj, Vec3* up)
{
    Vec3 v;
    Vec3 eye;
    Mtx vmtx;
    f32 dot;

    if (!HSD_CObjGetEyeVector(cobj, &eye)) {
        dot = 0.0f;
    } else {
        dot = cobj_absf(VECDotProduct(up, &eye));
        dot = 1.0f - dot;
        if (dot < FLT_MIN) {
            dot = 0.0f;
        } else {
            C_MTXLookAt(vmtx, &orig, &uy, &eye);
            PSMTXMultVecSR(vmtx, up, &v);
            {
                float x = -v.x;
                float y = v.y;
                if (y == 0.0f) {
                    dot = x >= 0.0f ? 1.5707963267948966f : -1.5707963267948966f;
                } else {
                    dot = atan2(x, y);
                }
            }
        }
    }
    return dot;
}

extern inline f32 vec_get_x(Vec3* v)
{
    return v->x;
}

extern inline f64 vec_get_abs_y(Vec3* v)
{
    return cobj_absf(v->y);
}

extern inline f32 cobj_get_up_x(Vec3* up)
{
    return up->x;
}

void HSD_CObjSetUpVector(HSD_CObj* cobj, Vec3* up)
{
    Vec3 v;
    if (!cobj || !up) {
        return;
    }
    if ((cobj->flags & 1) != 0) {
        if (vec_normalize_check(up, &v)) {
            OSReport(lbl_804FC5B8);
            __assert(lbl_806D0D50, 976, lbl_806D0D60);
        }
        if (cobj->u.up.x != cobj_get_up_x(&v) || cobj->u.up.y != v.y ||
            cobj->u.up.z != v.z)
        {
            HSD_CObjSetMtxDirty(cobj);
            cobj->u.up = v;
        }
    } else {
        HSD_CObjSetRoll(cobj, upvec2roll(cobj, up));
    }
}
