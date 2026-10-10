#include "KartFxDrift.h"

/* NonMatching: growth-clamp f1/f2 identity, 5 instructions; budget exhausted. */
extern "C" {
void KartFx_DriftPuffParticleTick(Effect *effect) {
    switch (effect->state) {
    case 0: {
        VfxSlot_BindResourceEx(effect->slot, 0x71, 0);
        effect->lifetime = lbl_806D51C4;
        GetSpawnPosition(&effect->offset, lbl_806D51C0,
            Rand_RangeFloat(lbl_806D51CC, lbl_806D51DC),
            Rand_RangeFloat(lbl_806D5200, lbl_806D51DC));
        Vec2_RotateY(&effect->offset, &effect->offset, lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D5224));
        effect->rotation = lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D5224);
        effect->size = Rand_RangeFloat(lbl_806D51E8, lbl_806D51C4);
        effect->growth = lbl_806D51C0;
        ++effect->state;
        break;
    }
    case 1: {
        float maximum, step, current;
        current = effect->growth;
        step = lbl_806D5280;
        maximum = lbl_806D51C4;
        effect->growth = current + step;
        if (maximum < effect->growth) { effect->growth = maximum; ++effect->state; }
        break;
    }
    case 2:
        effect->growth -= lbl_806D5280;
        if (effect->growth < 0.0f) {
            effect->visible = 1;
            DrawEffect_Free(effect);
            return;
        }
        break;
    }
    Mtx44_GetTranslation_RowMajor(&effect->position, KartDriver_GetKartRootMtx(effect->kart));
    Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->offset);
    effect->scale = effect->size * effect->growth;
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->rotation);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    Timers(effect);
}
}

