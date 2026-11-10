#include "game/types/Vec3.h"

#include "game/types/BBox.h"

extern int lbl_806D1694;

BBox *fn_8018A2E8(BBox *box) {
    lbl_806D1694++;
    box->min.x = 0.0f;
    box->min.y = 0.0f;
    box->min.z = 0.0f;
    box->max.x = 0.0f;
    box->max.y = 0.0f;
    box->max.z = 0.0f;
    box->x28 = 0;
    box->x2c = 0;
    box->x30 = 0;
    box->x34 = 0;
    box->x38 = 0;
    return box;
}
