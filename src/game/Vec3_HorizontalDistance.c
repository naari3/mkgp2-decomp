#include "game/MathInline.h"

extern void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);

float Vec3_HorizontalDistance(const Vec3f *a, const Vec3f *b)
{
    Vec3f d;
    Vec3_Subtract(a, b, &d);
    return MathInline_sqrtf(d.x * d.x + d.z * d.z);
}
