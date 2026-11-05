#include "game/AISpeedPrivate.h"
extern void AI_DecideAndUseItem_PairTracking(AISpeedOwner *, int);
static inline float PairDistanceBonus(AISpeedOwner *self, void *ctrl, int kart) {
    int rank = KartController_GetRenderObj(ctrl)->rank;
    unsigned char usePrimary = 1;
    int i;
    void **p = Read_U32;
    AISpeedRender *reference;
    for (i = 0; i < 8; ++i, ++p) {
        void *other = *p;
        if (other && other != ctrl) {
            if (KartController_GetRenderObj(other)->state == 6) {
                if (rank < KartController_GetRenderObj(ctrl)->rank) usePrimary = 0;
            }
        }
    }
    if (usePrimary) reference = CarObject_GetRenderObj(self->car);
    else reference = CarObject_GetRenderObj(self->partnerCar);
    return AI_CalcDistanceSpeedBonus(kart, reference->rank, rank);
}
static inline void PairSpeed(AISpeedOwner *self, int kart) {
    void *ctrl = Read_U32[kart];
    AIPairRecord *record = &lbl_806793D8[kart];
    void *param = GetEnemyParam();
    int cup = g_cupId;
    int round = g_roundIndex;
    float min;
    float max;
    float bonus;
    max = GetBaseSpeedMax(param, cup, round);
    min = GetBaseSpeedMin(param, cup, round);
    bonus = PairDistanceBonus(self, ctrl, kart);
    max += bonus; min += bonus;
    bonus = LapBonus(ctrl, kart);
    max += bonus; min += bonus;
    AI_DecideAndUseItem_PairTracking(self, kart);
    bonus = record->speedBonus;
    max += bonus; min += bonus;
    KartController_SetTargetSpeed(ctrl, lbl_806DA3E0 * (lbl_806DA3E4 * max), lbl_806DA3E0 * (lbl_806DA3E4 * min));
}
void AI_CalcTargetSpeed_PairTracking(AISpeedOwner *self, int kart) {
    if (self->frame < lbl_806D1920) SetInitialSpeed(kart);
    else PairSpeed(self, kart);
}
