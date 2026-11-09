#include "game/AISpeedPrivate.h"
#pragma opt_propagation off
static inline void PairSetSpeed(void *ctrl, float max, float min) {
    KartController_SetTargetSpeed(ctrl, 10.0f * (1000.0f * max), 10.0f * (1000.0f * min));
}
extern void AI_DecideAndUseItem_PairTracking(AISpeedOwner *, int);
static inline float PairLapBonus(void *ctrl, int kart, int rank, int lap) {
    int difference = AI_GetLapDifference(ctrl);
    return AI_CalcLapSpeedBonus(kart, g_totalLaps - lap, difference, rank);
}
/* fakematch (decl order + shared offset): same shape as AI_CalcVSTargetSpeed
 * (regalloc_patterns 70). Both branches share one inline local list so
 * the start-of-race `kart * 4` is numbered between the normal branch's
 * locals; inline locals colour last-declared first; record/ctrl are
 * declared first so they survive the first simplify sweep and take
 * r30/r31; opt_propagation off keeps cup/round as locals. Natural code is
 * PairInitialSpeed / PairDistanceBonus / PairSpeed helpers. */
static inline void Pair(AISpeedOwner *self, int kart) {
    AIPairRecord *record;
    void *ctrl;
    int i;
    unsigned char usePrimary;
    int round;
    int off;
    int cup;
    void *param;
    int drank;
    void **p;
    AISpeedRender *reference;
    int lap;
    int rank;
    float min;
    float max;
    float bonus;
    void *ictrl;
    int icup;
    int iround;
    if (self->frame < lbl_806D1920) {
        float imax, imin, scale;
        off = kart * 4;
        ictrl = *(void **)((char *)Read_U32 + off);
        icup = g_cupId;
        iround = g_roundIndex;
        imax = GetBaseSpeedMax(GetEnemyParam(), icup, iround);
        imin = GetBaseSpeedMin(GetEnemyParam(), icup, iround);
        scale = *(float *)((char *)fn_801DE7B8() + off);
        imax *= scale;
        imin *= scale;
        PairSetSpeed(ictrl, imax, imin);
    } else {
        ctrl = Read_U32[kart];
        record = &lbl_806793D8[kart];
        param = GetEnemyParam();
        cup = g_cupId;
        round = g_roundIndex;
        max = GetBaseSpeedMax(param, cup, round);
        min = GetBaseSpeedMin(param, cup, round);
        drank = KartController_GetRenderObj(ctrl)->rank;
        usePrimary = 1;
        p = Read_U32;
        for (i = 0; i < 8; ++i, ++p) {
            void *other = *p;
            if (other && ctrl != other) {
                if (KartController_GetRenderObj(other)->state == 6) {
                    if (drank < KartController_GetRenderObj(ctrl)->rank) usePrimary = 0;
                }
            }
        }
        if (usePrimary) reference = CarObject_GetRenderObj(self->car);
        else reference = CarObject_GetRenderObj(self->partnerCar);
        bonus = AI_CalcDistanceSpeedBonus(kart, reference->rank, drank);
        max += bonus; min += bonus;
        rank = KartController_GetRenderObj(ctrl)->rank;
        lap = KartController_GetRenderObj(ctrl)->lap;
        bonus = PairLapBonus(ctrl, kart, rank, lap);
        max += bonus; min += bonus;
        AI_DecideAndUseItem_PairTracking(self, kart);
        bonus = record->speedBonus;
        max += bonus; min += bonus;
        PairSetSpeed(ctrl, max, min);
    }
}
void AI_CalcTargetSpeed_PairTracking(AISpeedOwner *self, int kart) {
    Pair(self, kart);
}
