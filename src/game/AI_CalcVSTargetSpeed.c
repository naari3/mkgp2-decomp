#include "game/AISpeedPrivate.h"
#pragma opt_propagation off
extern int fn_801DC69C(int);
extern int fn_801DC6CC(int);
extern void *GetKartSlotKartVariant(int);
extern void AI_UseItem(void *, void *);
static inline void VSSetSpeed(void *ctrl, float max, float min) {
    KartController_SetTargetSpeed(ctrl, 10.0f * (1000.0f * max), 10.0f * (1000.0f * min));
}
/* fakematch (decl order + shared offset): both branches live in one inline so
 * that the start-of-race branch's `kart * 4` is numbered between the
 * locals of the normal branch (target keeps it in r27), and the locals
 * are declared in the order the allocator colours them, last declared
 * first (regalloc_patterns 70). Natural code is two helpers,
 * `ctrl = Read_U32[kart]` and `scale = fn_801DE7B8()[kart]`. */
static inline void Speed(AISpeedOwner *self, int kart) {
        int round;
        float min;
        AIPairRecord *record;
        void *param;
        float bonus;
        void *ctrl;
        int off;
        int lap;
        int rank;
        float max;
        int cup;
        int rank1;
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
        VSSetSpeed(ictrl, imax, imin);
        } else {
        ctrl = Read_U32[kart];
        record = &lbl_806793D8[kart];
        param = GetEnemyParam();
        max = GetBaseSpeedMax(param, cup = g_cupId, round = g_roundIndex);
        min = GetBaseSpeedMin(param, cup, round);
        { rank1 = KartController_GetRenderObj(ctrl)->rank;
        bonus = AI_CalcDistanceSpeedBonus(kart, CarObject_GetRenderObj(self->car)->rank, rank1); }
        max += bonus; min += bonus;
        rank = KartController_GetRenderObj(ctrl)->rank;
        lap = KartController_GetRenderObj(ctrl)->lap;
        bonus = AI_CalcLapSpeedBonus(kart, g_totalLaps - lap, AI_GetLapDifference(ctrl), rank);
        max += bonus; min += bonus;
        if (fn_801DC69C(kart) != -1) {
            AI_UseItem(Read_U32[kart], GetKartSlotKartVariant(fn_801DC6CC(kart)));
        }
        bonus = record->speedBonus;
        max += bonus; min += bonus;
        KartController_SetTargetSpeed(ctrl, 10.0f * (1000.0f * max), 10.0f * (1000.0f * min));
        }
}
void AI_CalcVSTargetSpeed(AISpeedOwner *self, int kart) {
 Speed(self, kart);
}
