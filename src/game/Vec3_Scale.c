#include "game/types/Vec3.h"

extern void PSVECScale(const Vec3 *src, Vec3 *dst, float scale);

void Vec3_Scale(Vec3 *dst, const Vec3 *src, float scale) {
    PSVECScale(src, dst, scale);
}
