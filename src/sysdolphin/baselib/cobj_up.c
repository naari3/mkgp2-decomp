#include "cobj_private.h"

int HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up)
{
    if (cobj == NULL || up == NULL) {
        return 0;
    }
    if ((cobj->flags & 1) != 0) {
        *up = cobj->u.up;
        return 1;
    }
    return roll2upvec(cobj, up, cobj->u.roll);
}
