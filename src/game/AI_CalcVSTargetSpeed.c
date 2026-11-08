#include "game/AISpeedPrivate.h"
#pragma opt_propagation off
extern int fn_801DC69C(int);
extern int fn_801DC6CC(int);
extern void *GetKartSlotKartVariant(int);
extern void AI_UseItem(void *, void *);
static inline void VSSetSpeed(void *ctrl, float max, float min) {
    KartController_SetTargetSpeed(ctrl, 10.0f * (1000.0f * max), 10.0f * (1000.0f * min));
}
static inline void VSInitialSpeed(int kart) {
    void *ctrl = Read_U32[kart];
    int cup = g_cupId;
    int round = g_roundIndex;
    float max = GetBaseSpeedMax(GetEnemyParam(), cup, round);
    float min = GetBaseSpeedMin(GetEnemyParam(), cup, round);
    float scale = fn_801DE7B8()[kart];
    max *= scale;
    min *= scale;
    VSSetSpeed(ctrl, max, min);
}
static inline float VSLapBonus(void *ctrl, int kart) {
    int lap;
    int rank = KartController_GetRenderObj(ctrl)->rank;
    lap = KartController_GetRenderObj(ctrl)->lap;
    {
        int difference = AI_GetLapDifference(ctrl);
        return AI_CalcLapSpeedBonus(kart, g_totalLaps - lap, difference, rank);
    }
}
static inline float DistanceBonus(AISpeedOwner *self, void *ctrl, int kart) {
    int rank = KartController_GetRenderObj(ctrl)->rank;
    return AI_CalcDistanceSpeedBonus(kart, CarObject_GetRenderObj(self->car)->rank, rank);
}
static inline void NormalSpeed(AISpeedOwner *self, int kart) {
        float min;
        void *param;
        AIPairRecord *record;
        void *ctrl = Read_U32[kart];
        int round;
        int cup;
        float bonus;
        float max;
        record = &lbl_806793D8[kart];
        param = GetEnemyParam();
        max = GetBaseSpeedMax(param, cup = g_cupId, round = g_roundIndex);
        min = GetBaseSpeedMin(param, cup, round);
        bonus = DistanceBonus(self, ctrl, kart);
        max += bonus; min += bonus;
        bonus = VSLapBonus(ctrl, kart);
        max += bonus; min += bonus;
        if (fn_801DC69C(kart) != -1) {
            AI_UseItem(Read_U32[kart], GetKartSlotKartVariant(fn_801DC6CC(kart)));
        }
        bonus = record->speedBonus;
        max += bonus; min += bonus;
        KartController_SetTargetSpeed(ctrl, 10.0f * (1000.0f * max), 10.0f * (1000.0f * min));
}
void AI_CalcVSTargetSpeed(AISpeedOwner *self, int kart) {
 if (self->frame < lbl_806D1920) VSInitialSpeed(kart);
 else NormalSpeed(self, kart);
}
