#include "game/types/DrawEffect.h"

extern void Vec3_Copy(float *dst, float *src);

void DrawEffect_ApplyScaleAndIntensity(DrawEffect *effect, float scale, float intensity,
                                       float *position) {
    if (effect != 0) {
        Vec3_Copy(effect->position, position);
        effect->scale = scale;
        effect->intensity = intensity;
        if (0.0f < intensity) {
            effect->active = 1;
        } else {
            effect->active = 0;
        }
    }
}
