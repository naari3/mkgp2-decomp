#include "game/MathInline.h"

extern float fn_8025E3C4(const Vec3f *a, const Vec3f *b);

float fn_800D3184(const Vec3f *a, const Vec3f *b)
{
    return MathInline_sqrtf(fn_8025E3C4(a, b));
}
