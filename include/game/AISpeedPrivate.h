#ifndef GAME_AI_SPEED_PRIVATE_H
#define GAME_AI_SPEED_PRIVATE_H
#include "game/AIPairPrivate.h"
typedef struct AISpeedOwner {
    void *vtable;
    void *car;
    void *partnerCar;
    int frame;
} AISpeedOwner;
typedef struct AISpeedRender {
    char pad[0x1F8];
    int state;
    char pad1FC[0x40];
    int rank;
    int lap;
} AISpeedRender;
extern void *Read_U32[8];
extern AIPairRecord lbl_806793D8[8];
extern int lbl_806D1920;
extern int g_cupId, g_roundIndex, g_totalLaps;
extern const float lbl_806DA3E0, lbl_806DA3E4;
extern void *GetEnemyParam(void);
extern float GetBaseSpeedMax(void *, int, int);
extern float GetBaseSpeedMin(void *, int, int);
extern float *fn_801DE7B8(void);
extern void KartController_SetTargetSpeed(void *, float, float);
extern AISpeedRender *KartController_GetRenderObj(void *);
extern AISpeedRender *CarObject_GetRenderObj(void *);
extern int AI_GetLapDifference(void *);
extern float AI_CalcDistanceSpeedBonus(int, int, int);
extern float AI_CalcLapSpeedBonus(int, int, int, int);
static inline void SetSpeed(void *ctrl, float max, float min) {
    KartController_SetTargetSpeed(ctrl, lbl_806DA3E0 * (lbl_806DA3E4 * max), lbl_806DA3E0 * (lbl_806DA3E4 * min));
}
static inline void SetInitialSpeed(int kart) {
    void *ctrl = Read_U32[kart];
    int cup = g_cupId;
    int round = g_roundIndex;
    float max = GetBaseSpeedMax(GetEnemyParam(), cup, round);
    float min = GetBaseSpeedMin(GetEnemyParam(), cup, round);
    float scale = fn_801DE7B8()[kart];
    SetSpeed(ctrl, max * scale, min * scale);
}
static inline float LapBonus(void *ctrl, int kart) {
    int rank = KartController_GetRenderObj(ctrl)->rank;
    int lap = KartController_GetRenderObj(ctrl)->lap;
    int difference = AI_GetLapDifference(ctrl);
    return AI_CalcLapSpeedBonus(kart, g_totalLaps - lap, difference, rank);
}
#endif
