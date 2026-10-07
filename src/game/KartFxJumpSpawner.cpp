#include "KartFxJump.h"

extern "C" {
void KartFx_Slot68_JumpDustSpawner(JumpEffectView *effect) {
    Vec3 position;
    position.x = lbl_806D52A0 * Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
    position.y = lbl_806D52A4 * Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
    position.z = lbl_806D52A8;
    JumpEffectView *child = DrawEffect_SpawnDirect(KartFx_JumpDustSmokeTick);
    if (child) {
        child->kart = effect->kart;
        Vec3_Copy(&child->position, &position);
    }
    child = DrawEffect_SpawnDirect(KartFx_JumpRingGlowTick);
    if (child) {
        child->kart = effect->kart;
        Vec3_Copy(&child->position, &position);
    }
    DrawEffect_Free(effect);
}
}
