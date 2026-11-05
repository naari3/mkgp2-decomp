#include "lobj_private.h"

#undef __FILE__
#define __FILE__ "lobj.c"

static inline int LObjNormalize(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (fabsf(src->x) <= LOBJ_FLT_MIN && fabsf(src->y) <= LOBJ_FLT_MIN &&
        fabsf(src->z) <= LOBJ_FLT_MIN)
    {
        return -1;
    }
    PSVECNormalize(src, dst);
    return 0;
}

void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir)
{
    Vec3 position = { 0.0F, 0.0F, 0.0F };
    Vec3 interest = { 0.0F, 0.0F, 0.0F };

    if (lobj == NULL) {
        return;
    }

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    if (LObjNormalize(dir, dir) != 0) {
        dir->x = 0.0F;
        dir->y = 0.0F;
        dir->z = 1.0F;
    }
}
