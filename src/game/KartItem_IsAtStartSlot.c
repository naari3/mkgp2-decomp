#include "game/types/KartItem.h"

extern int g_kartStartSlot;
extern void fn_801737CC(void *);

float *KartMovement_GetVelocityPtr(KartItem *kart) {
    return kart->velocity;
}

int KartItem_SetVec3At338(KartItem *kart, float *vec) {
    if (vec == 0) {
        return 0;
    }
    kart->velocity[0] = vec[0];
    kart->velocity[1] = vec[1];
    kart->velocity[2] = vec[2];
    return 1;
}

#pragma exceptions on
int KartItem_IsAtStartSlot(KartItem *kart) {
    if (kart->slot != g_kartStartSlot) {
        return 0;
    }
    fn_801737CC(kart->driver);
    return 1;
}
#pragma exceptions reset
