/* Measure the transformed +Z vector after removing the matrix translation. */
#include "game/C7Mtx44Inline.h"

extern void PSVECScale(const Vec3f *src, Vec3f *dst, float scale);
extern float Vec3_Magnitude(const Vec3f *v);

float fn_800D4174(const float src[4][4])
{
    float m[4][4];
    Vec3f v;

    C7_Mtx44Copy(m, src);
    v.x = m[3][0];
    v.y = m[3][1];
    v.z = m[3][2];
    PSVECScale(&v, &v, lbl_806D5920);
    C7_Mtx44Translate(m, m, v);
    v.x = lbl_806D592C;
    v.y = lbl_806D592C;
    v.z = lbl_806D5930;
    C7_Mtx44Xform(&v, m, v);
    return Vec3_Magnitude(&v);
}
