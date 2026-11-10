#include "game/types/Vec3.h"

void Vec3_ScaleXZ(Vec3 *__restrict dst, const Vec3 *__restrict src, float scale) {
    dst->x = src->x * scale;
    dst->y = src->y;
    dst->z = src->z * scale;
}
