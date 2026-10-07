#include "KartFxJump.h"

extern "C" {
static inline int Decay(float *value, float step) {
    float minimum = 0.0f;
    *value -= step;
    if (*value < minimum) return 1;
    return 0;
}

void KartFx_JumpRingGlowTick(JumpEffectView *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->vfx, 0x3B, 0);
        effect->vfx[0] = 1;
        effect->lifetime = lbl_806D51C4;
        effect->scale = lbl_806D51C0;
        effect->state = 1;
        effect->phase = 0;
        break;
    case 1: break;
    }
    if (Decay(&effect->lifetime, lbl_806D51C8)) {
        DrawEffect_Free(effect);
        return;
    }
    const Vec3 &transformed = Mtx44_TransformVec3(lbl_805DF3D0, effect->position);
    VfxSlot_SetPositionFromVec(effect->vfx, transformed);
    float step, maximum, current;
    current = effect->scale;
    step = lbl_806D51C8;
    maximum = lbl_806D51C4;
    effect->scale = current + step;
    if (maximum < effect->scale) effect->scale = maximum;
    VfxSlot_SetScaleUniform(effect->vfx, lbl_806D51D0 * effect->scale);
    if (effect->kart->visible == 0) effect->visible = 0;
    else effect->visible = 1;
}

void KartFx_JumpDustSmokeTick(JumpEffectView *effect) {
    switch (effect->state) {
    case 0:
        switch (Rand_RangeIntMax(15) % 3) {
        case 0: VfxSlot_BindResourceEx(effect->vfx, 0x37, 0); break;
        case 1: VfxSlot_BindResourceEx(effect->vfx, 0x38, 0); break;
        case 2: VfxSlot_BindResourceEx(effect->vfx, 0x39, 0); break;
        }
        effect->vfx[0] = 1;
        VfxSlot_SetRotationZ(effect->vfx, lbl_806D521C * Rand_RangeFloat(lbl_806D5250, lbl_806D52AC));
        effect->lifetime = lbl_806D51C4;
        effect->scale = lbl_806D51C0;
        ++effect->state;
    case 1: {
        float step, maximum, current;
        current = effect->scale;
        step = lbl_806D51C8;
        maximum = lbl_806D51C4;
        effect->scale = current + step;
        if (maximum < effect->scale) {
            effect->scale = maximum;
            ++effect->state;
        }
        break;
    }
    case 2: {
        float minimum = 0.0f;
        effect->scale -= lbl_806D52B0;
        if (effect->scale < minimum) {
            DrawEffect_Free(effect);
            return;
        }
        effect->lifetime = effect->scale;
        break;
    }
    }
    const Vec3 &transformed = Mtx44_TransformVec3(lbl_805DF3D0, effect->position);
    VfxSlot_SetPositionFromVec(effect->vfx, transformed);
    VfxSlot_SetScaleUniform(effect->vfx, effect->scale);
    if (effect->kart->visible == 0) effect->visible = 0;
    else effect->visible = 1;
}

}
