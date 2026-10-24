#include "game/MathInline.h"

extern const float lbl_806D5AC8;
extern float Vec3_Magnitude_Wrapper(const Vec3f *);
extern void Vec3_Scale(Vec3f *out, const Vec3f *v, float s);
extern void Vec3_Add_DestFirst(Vec3f *out, const Vec3f *a, const Vec3f *b);

void Vec3_AddNormalizedXZ(void *owner, Vec3f *pos, const Vec3f *dir)
{
    Vec3f step;
    float mag;

    if (owner == 0) {
        return;
    }
    mag = Vec3_Magnitude_Wrapper(dir);
    if (mag == lbl_806D5AC8) {
        return;
    }
    Vec3_Scale(&step, dir, 0.5f * (1.0f / mag));
    step.y = lbl_806D5AC8;
    Vec3_Add_DestFirst(pos, pos, &step);
}
