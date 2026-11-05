#include "DriveBehavior_private.h"
extern float fn_801DB860(void *, int);
extern double sin(double);
extern const float lbl_806D18E4, lbl_806D18E8;
extern const float lbl_806DA2D0, lbl_806DA2D4, lbl_806DA2D8;
extern const float lbl_806DA2DC, lbl_806DA2E0, lbl_806DA2E4, lbl_806DA2E8;

void DriveBehavior_HandleWpType(DriveBehavior *self, int waypoint) {
    float speed;
    float acceleration;
    float limit;
    float step;
    acceleration = lbl_806D18FC;
    speed = lbl_806DA2D0;
    limit = lbl_806D18E4;
    step = lbl_806D18E8;
    switch (fn_801DB830(fn_801DB8F0(), waypoint)) {
    case 3: {
        float current = self->speedScale;
        if (current > limit) self->direction = -1;
        if (current < -limit) self->direction = 1;
        speed = step * self->direction + self->speedScale;
        break;
    }
    case 4: {
        float current = self->speedScale;
        if (current > limit) self->direction = -1;
        if (current < -limit) self->direction = 1;
        speed = step * self->direction + self->speedScale;
        break;
    }
    case 5: speed = lbl_806D18F4; break;
    case 6: speed = lbl_806D18F8; break;
    case 7: {
        float current = self->speedScale;
        if (current > limit) self->direction = -1;
        if (current < -limit) self->direction = 1;
        speed = step * self->direction + self->speedScale;
        break;
    }
    case 8: self->itemLocked = 1; break;
    case 9: self->flag15 = 1; break;
    case 10:
        self->matrix[0] = lbl_806DA2D4;
        self->matrix[5] = lbl_806DA2D4;
        self->matrix[10] = lbl_806DA2D4;
        break;
    case 11: {
        float wave;
        self->phase += lbl_806DA2D8;
        if (self->phase > lbl_806DA2DC) self->phase -= lbl_806DA2DC;
        wave = sin(lbl_806DA2E0 * self->phase);
        self->matrix[0] = lbl_806DA2E8 * wave + lbl_806DA2E4;
        self->matrix[5] = lbl_806DA2E8 * (lbl_806DA2DC - wave) + lbl_806DA2E4;
        break;
    }
    case 12:
        if (!self->flag28) self->flag28 = 1;
        break;
    default:
        self->direction = 0;
        self->itemLocked = 0;
        self->flag15 = 0;
        self->speedScale = lbl_806DA2D0;
        self->acceleration = lbl_806D18FC;
        if (self->flag28) self->flag28 = 0;
        break;
    }
    self->speedScale = speed;
    self->acceleration = acceleration;
    self->parameter20 = fn_801DB860(fn_801DB8F0(), waypoint);
}
