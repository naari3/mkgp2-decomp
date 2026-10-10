#include "KartFxDrift.h"

extern "C" {
void KartFx_DriftPuffTick(Effect *effect) {
    KartState *kartState = effect->kart->state;
    float transform[16], base[16];
    switch (effect->state) {
    case 0:
        VfxSlot_BindResource(effect->slot, 0x7D);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        VfxSlot_SetAnimSpeed(effect->slot, lbl_806D51E8);
        effect->visible = 0;
        effect->active = 0;
        effect->scale = lbl_806D51C4;
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->expired) { DrawEffect_Free(effect); return; }
    if (effect->active) {
        if (effect->delay == 0) {
            Effect *piece = DrawEffect_SpawnDirect(KartFx_DriftPuffParticleTick);
            if (piece) piece->kart = effect->kart;
            effect->delay = Rand_RangeInt(10, 30);
        }
        if ((int)effect->slot[10] == 2) {
            if (DriftFlag(kartState) == 0 && (kartState->flags & 0x4000000000000000ULL) == 0) effect->active = 0;
        }
    } else {
        if (DriftFlag(kartState) != 0 || (kartState->flags & 0x4000000000000000ULL) != 0) effect->active = 1;
    }
    if (effect->active) {
        if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
        else effect->visible = 1;
    } else effect->visible = 0;
    Mtx_TransposeToMtx44(base, KartDriver_GetKartRootMtx(effect->kart));
    Matrix4_Identity(transform);
    Matrix4_PreMultiplyTranslation(transform, transform, lbl_806D51C0, lbl_806D5218, lbl_806D51C0);
    Matrix4_Multiply(base, transform, base);
    Mtx44_Inverse_GaussJordan(transform, base);
    const Vec3 &camera = Mtx44_TransformVec3(transform, lbl_805DF3D0.position);
    Matrix4_Identity(transform);
    Mtx44_Scale_Uniform(transform, transform, lbl_806D5304);
    Matrix4_PreMultiplyTranslation(transform, transform, lbl_806D51C0, lbl_806D51C0, lbl_806D5308);
    Matrix4_PreMultiplyRotY(transform, transform, BuildOrientationFromYaw((float)Atan2(camera.x, camera.z)));
    Matrix4_Multiply(base, transform, base);
    DbgScene_CopyMatrix3x4Transpose(effect->matrix, base);
    Mtx44_GetTranslation_RowMajor(&effect->position, effect->matrix);
    Timers(effect);
}
}
