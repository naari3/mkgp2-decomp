/* Float tween value, 0x8020A6CC..0x8020A734. */
#include "game/FlowScene.h"

extern "C" const float lbl_806DABEC;

extern "C" float fn_8020A6CC(const FlowFaderF *__restrict self) {
    int t = self->b;
    int n = self->a;
    float value;
    if ((short)t <= 0) {
        value = self->x;
    } else if (t >= n) {
        value = self->y;
    } else {
        float step = self->z * t;
        step = self->x + lbl_806DABEC * step;
        value = step;
    }
    return value;
}
