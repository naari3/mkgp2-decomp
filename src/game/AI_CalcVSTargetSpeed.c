#include "game/AISpeedPrivate.h"
extern int fn_801DC69C(int);
extern int fn_801DC6CC(int);
extern void *GetKartSlotKartVariant(int);
extern void AI_UseItem(void *, void *);
static inline float DistanceBonus(AISpeedOwner *self, void *ctrl, int kart) {
    int rank = KartController_GetRenderObj(ctrl)->rank;
    return AI_CalcDistanceSpeedBonus(kart, CarObject_GetRenderObj(self->car)->rank, rank);
}
static inline void NormalSpeed(AISpeedOwner *self, int kart) {
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
        bonus = DistanceBonus(self, ctrl, kart);
        max += bonus; min += bonus;
        bonus = LapBonus(ctrl, kart);
        max += bonus; min += bonus;
        if (fn_801DC69C(kart) != -1) {
            AI_UseItem(Read_U32[kart], GetKartSlotKartVariant(fn_801DC6CC(kart)));
        }
        bonus = record->speedBonus;
        max += bonus; min += bonus;
        KartController_SetTargetSpeed(ctrl, lbl_806DA3E0 * (lbl_806DA3E4 * max), lbl_806DA3E0 * (lbl_806DA3E4 * min));
}
void AI_CalcVSTargetSpeed(AISpeedOwner *self, int kart) {
 if (self->frame < lbl_806D1920) SetInitialSpeed(kart);
 else NormalSpeed(self, kart);
}
