#include "game/MathInline.h"

extern void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);
extern double atan2(float y, float x);

float Vec3_PitchTo(const Vec3f *from, const Vec3f *to)
{
    Vec3f d;
    Vec3_Subtract(to, from, &d);
    return atan2(-d.y, MathInline_sqrtf(d.x * d.x + d.z * d.z));
}
