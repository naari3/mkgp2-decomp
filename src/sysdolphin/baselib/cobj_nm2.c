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

float upvec2roll(HSD_CObj* cobj, Vec3* up)
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

int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll)
{
    int res;
    Vec3 eye;
    Vec3 v0;
    Vec3 v1;
    Mtx m;

    res = HSD_CObjGetEyeVector(cobj, &eye);
    if (!res) {
        return 0;
    }
    if (1.0 - vec_get_abs_y(&eye) < 0.0001) {
        v0.x = sqrtf(eye.y * eye.y + eye.z * eye.z);
        v0.y = eye.y * (-vec_get_x(&eye) / v0.x);
        v0.z = eye.z * (-eye.x / v0.x);
    } else {
        v0.y = sqrtf(eye.x * eye.x + eye.z * eye.z);
        v0.x = eye.x * (-eye.y / v0.y);
        v0.z = eye.z * (-eye.y / v0.y);
    }
    PSMTXRotAxisRad(m, &eye, -roll);
    PSMTXMultVecSR(m, &v0, &v1);
    VECNormalize(&v1, up);
    return 1;
}
