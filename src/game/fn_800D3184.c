#include "game/MathInline.h"

extern float PSVECSquareDistance(const Vec3f *a, const Vec3f *b);

float fn_800D3184(const Vec3f *a, const Vec3f *b)
{
    return MathInline_sqrtf(PSVECSquareDistance(a, b));
}
