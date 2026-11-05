#include "game/AISpeedPrivate.h"
static inline void PairSetSpeed(void *ctrl, float max, float min) {
    KartController_SetTargetSpeed(ctrl, 10.0f * (1000.0f * max), 10.0f * (1000.0f * min));
}
static inline void PairInitialSpeed(int kart) {
    void *ctrl = Read_U32[kart];
    int cup = g_cupId;
    int round = g_roundIndex;
    float max = GetBaseSpeedMax(GetEnemyParam(), cup, round);
    float min = GetBaseSpeedMin(GetEnemyParam(), cup, round);
    float scale = fn_801DE7B8()[kart];
    max *= scale;
    min *= scale;
    PairSetSpeed(ctrl, max, min);
}
extern void AI_DecideAndUseItem_PairTracking(AISpeedOwner *, int);
static inline float PairDistanceBonus(AISpeedOwner *self, void *ctrl, int kart) {
    int i;
    unsigned char usePrimary;
    void **p;
    int rank;
    AISpeedRender *reference;
    rank = KartController_GetRenderObj(ctrl)->rank;
    usePrimary = 1;
    p = Read_U32;
    for (i = 0; i < 8; ++i, ++p) {
        void *other = *p;
        if (other && ctrl != other) {
            if (KartController_GetRenderObj(other)->state == 6) {
                if (rank < KartController_GetRenderObj(ctrl)->rank) usePrimary = 0;
            }
        }
    }
    if (usePrimary) reference = CarObject_GetRenderObj(self->car);
    else reference = CarObject_GetRenderObj(self->partnerCar);
    return AI_CalcDistanceSpeedBonus(kart, reference->rank, rank);
}
static inline float PairLapBonus(void *ctrl, int kart) {
    int lap;
    int rank = KartController_GetRenderObj(ctrl)->rank;
    lap = KartController_GetRenderObj(ctrl)->lap;
    {
        int difference = AI_GetLapDifference(ctrl);
        return AI_CalcLapSpeedBonus(kart, g_totalLaps - lap, difference, rank);
    }
}
static inline void PairSpeed(AISpeedOwner *self, int kart) {
    int round;
    void *param;
    int cup;
    AIPairRecord *record;
    void *ctrl;
    float min;
    float max;
    float bonus;
    ctrl = Read_U32[kart];
    record = &lbl_806793D8[kart];
    param = GetEnemyParam();
    cup = g_cupId;
    round = g_roundIndex;
    max = GetBaseSpeedMax(param, cup, round);
    min = GetBaseSpeedMin(param, cup, round);
    bonus = PairDistanceBonus(self, ctrl, kart);
    max += bonus; min += bonus;
    bonus = PairLapBonus(ctrl, kart);
    max += bonus; min += bonus;
    AI_DecideAndUseItem_PairTracking(self, kart);
    bonus = record->speedBonus;
    max += bonus; min += bonus;
    PairSetSpeed(ctrl, max, min);
}
void AI_CalcTargetSpeed_PairTracking(AISpeedOwner *self, int kart) {
    if (self->frame < lbl_806D1920) PairInitialSpeed(kart);
    else PairSpeed(self, kart);
}
