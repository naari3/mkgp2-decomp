/* Native reconstruction of the assigned single-function TU. */
#include "game/AISpeedPrivate.h"
#include "game/AIGPSpeedPrivate.h"
extern GPSpeedParams *GetKartTuningGPSpeedParams(void *, int, int, int);
extern int abs(int);
extern float AI_CalcItemSpeedBonus(void *, int, float, float);
extern void AI_UpdateItemUseLogic(void *, int);
static inline void GPSetSpeed(void *ctrl, float max, float min) {
    KartController_SetTargetSpeed(ctrl, 10.0f * (1000.0f * max), 10.0f * (1000.0f * min));
}
static inline void GPInitialSpeed(int kart) {
    void *ctrl = Read_U32[kart];
    int cup = g_cupId;
    int round = g_roundIndex;
    float max = GetBaseSpeedMax(GetEnemyParam(), cup, round);
    float min = GetBaseSpeedMin(GetEnemyParam(), cup, round);
    float scale = fn_801DE7B8()[kart];
    max *= scale;
    min *= scale;
    GPSetSpeed(ctrl, max, min);
}
static inline float GPLapBonus(void *ctrl, int kart) {
    int lap;
    int rank = KartController_GetRenderObj(ctrl)->rank;
    lap = KartController_GetRenderObj(ctrl)->lap;
    {
        int difference = AI_GetLapDifference(ctrl);
        return AI_CalcLapSpeedBonus(kart, g_totalLaps - lap, difference, rank);
    }
}
static inline int HasFlags(GPStatus *status, unsigned long long mask) {
    unsigned long long flags = status->flagsA;
    flags |= status->flagsB;
    return (flags & mask) != 0;
}
static inline float GPCatchup(AIPairRecord *record, int kart) {
    if (record->field1C > 0) {
        GPSpeedParams *params = GetKartTuningGPSpeedParams(GetEnemyParam(), g_cupId, g_roundIndex, kart);
        if ((int)record->field08 < 0) {
            float distance;
            --record->field1C;
            if (record->field1C <= 0) record->field1C = -(int)(60.0f * (0.25f * params->cooldown));
            distance = 10.0f * (1000.0f * params->retreatDistance);
            if (distance * distance < record->field20) return 0.0f;
            return params->retreatA + params->retreatB;
        } else {
            float distance = 10.0f * (1000.0f * params->normalDistance);
            if (distance * distance < record->field20) return 0.0f;
            return params->normalA + params->normalB;
        }
    } else {
        if (record->field1C < 0) ++record->field1C;
        record->field20 = 0.0f;
        return 0.0f;
    }
}
static inline float FollowBonus(GPOwner *self, AIPairRecord *record, AIPairRecord *other, int mode) {
    float delta;
    float bonus;
    if (record->field24) return 0.0f;
    if (mode == 2) { record->field24 = 2; record->field28 = 120; }
    else { record->field24 = 1; record->field28 = 240; }
    delta = abs(record->waypoint - other->waypoint) - self->followDistance;
    bonus = (mode == 2 ? 2.4f : 4.2000003f) * delta;
    if (mode == 2) { if (0.0f < bonus) bonus = -bonus; }
    else { if (bonus < 0.0f) bonus = -bonus; }
    return bonus;
}
void AI_CalcGPTargetSpeed(GPOwner *self, int kart) {
    AIPairRecord *record = &lbl_806793D8[kart];
    if (self->common.frame < lbl_806D1920) {
        GPInitialSpeed(kart);
        record->field24 = 2;
        record->field28 = 1;
    } else {
        void *ctrl = Read_U32[kart];
        void *param = GetEnemyParam();
        int cup = g_cupId;
        int round = g_roundIndex;
        float max = GetBaseSpeedMax(param, cup, round);
        float min = GetBaseSpeedMin(param, cup, round);
        float bonus = GPCatchup(record, kart);
        int rank;
        max += bonus; min += bonus;
        rank = ((GPDriver *)record->driver)->rank;
        if (rank > 0) {
            AIPairRecord *other = 0;
            int distance = 1;
            int i = 0;
            while (i < 8) {
                other = &lbl_806793D8[i];
                if (other->driver && rank - distance == ((GPDriver *)other->driver)->rank) {
                    GPDriver *driver = other->driver;
                    if (driver->state < 0 || driver->state > 3) break;
                    if (driver->rank == 0) {
                        bonus = FollowBonus(self, record, other, 1);
                        max += bonus; min += bonus;
                        break;
                    } else {
                        i = 0; other = 0; ++distance;
                    }
                } else other = 0;
                ++i;
            }
            if (record->field24 == 0) {
                if (!other) record->field28 = -1;
                else if (!HasFlags(((GPDriver *)other->driver)->status, ~(unsigned long long)0)) {
                    int separation = abs(record->waypoint - other->waypoint);
                    if (separation < self->followDistance) {
                        bonus = FollowBonus(self, record, other, 2);
                        max += bonus; min += bonus;
                    }
                    if (self->followDistance < separation) {
                        bonus = FollowBonus(self, record, other, 1);
                        max += bonus; min += bonus;
                    }
                } else record->field28 = -1;
            }
            if (record->field28 > 0) {
                --record->field28;
                if (record->field28 <= 0) { record->field24 = 0; record->field28 = -1; }
            }
        }
        bonus = GPLapBonus(ctrl, kart);
        min += bonus; max += bonus;
        bonus = AI_CalcItemSpeedBonus(self, kart, max, min);
        max += bonus; min += bonus;
        {
            int rank = KartController_GetRenderObj(ctrl)->rank;
            bonus = AI_CalcDistanceSpeedBonus(kart, CarObject_GetRenderObj(self->common.car)->rank, rank);
        }
        max += bonus; min += bonus;
        bonus = record->speedBonus;
        max += bonus; min += bonus;
        AI_UpdateItemUseLogic(self, kart);
        GPSetSpeed(ctrl, max, min);
    }
}
