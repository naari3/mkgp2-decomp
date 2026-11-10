#include "game/types/Vec3.h"

#include "game/types/BBox.h"

extern int lbl_806D1694;
extern void fn_80189FD8(BBox *box, Vec3 *min, Vec3 *max);

BBox *fn_8018A278(BBox *box, Vec3 *min, Vec3 *max, int a, int b) {
    lbl_806D1694++;
    box->min.x = 0.0f;
    box->min.y = 0.0f;
    box->min.z = 0.0f;
    box->max.x = 0.0f;
    box->max.y = 0.0f;
    box->max.z = 0.0f;
    box->x28 = b;
    box->x2c = a;
    box->x30 = 0;
    box->x34 = 0;
    box->x38 = 0;
    fn_80189FD8(box, min, max);
    return box;
}
