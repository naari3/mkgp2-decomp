/* Per-kart AI tick: drives speed before the race starts, then the AI logic. */
typedef struct PathSlot {
    float v[3];
    float speed;
    float accel;
    int ids[3];
} PathSlot;

#include "game/types/KartAI.h"

extern "C" {
extern void *Read_U32[8];
extern int g_cupId;
extern int g_roundIndex;
extern PathSlot lbl_806792D8[8];
extern const float lbl_806DA3E0;
extern const float lbl_806DA3E4;
void *GetEnemyParam(void);
float GetKartTuningSpeedFactor(void *param, int cup, int round, int kart);
unsigned char IsRaceStarted(void);
void KartController_SetTargetSpeed(void *kart, float a, float b);
void KartController_TimedUpdate(void *kart);
int fn_801DC6FC(int kart);
int fn_801DC72C(int kart);
void fn_801E6B0C(void *kart, float v);
void fn_801E6B38(void *kart, float v);
void fn_801E6B64(void *kart, int v);
void fn_801E6C10(void *kart, int v);
}

static inline float TuningFactor(int kart) {
    int cup;
    int round;
    round = g_roundIndex;
    cup = g_cupId;
    return GetKartTuningSpeedFactor(GetEnemyParam(), cup, round, kart);
}

static inline float StartSpeed(int kart) {
    return lbl_806DA3E0 * (lbl_806DA3E4 * TuningFactor(kart));
}

extern "C" {
unsigned char fn_801E6DD4(void *);
void fn_801E6C54(void *, int);
extern int g_gameMode;
int *AI_GetItemList(void *, int, int, int, int);
int ReplayRandCursor_Advance(void *, int, int);
}
static inline int *ItemList(int kart) {
    int mode;
    int *items;
    int round;
    int cup;
    cup = g_cupId;
    round = g_roundIndex;
    mode = g_gameMode;
    items = AI_GetItemList(GetEnemyParam(), mode, cup, round, kart);
    return items;
}
extern "C" {
void fn_801DC6B4(int, int);
void fn_801DC740(int, int);
void fn_801DC714(int, int);
int fn_801E6D64(void *);
float fn_801E6CFC(void *);
float fn_801E6CC8(void *);
unsigned char fn_801E6594(void *);
void *KartController_GetRenderObj(void *);
unsigned char KartMovement_CanReceiveItem(void *, int);
}
static inline int ItemAt(const int *items, unsigned int index) {
    return items[index];
}

extern "C" void fn_801E9CBC(KartAI *self, int kart) {
    void *ctrl = Read_U32[kart];
    if (!ctrl) return;
    fn_801DC6B4(kart, -1);
    if (!IsRaceStarted()) {
        float speed = StartSpeed(kart);
        KartController_SetTargetSpeed(ctrl, speed, speed);
    } else {
        self->Think(kart);
    }
    fn_801DC740(kart, fn_801E6D64(ctrl));
    lbl_806792D8[kart].speed = fn_801E6CFC(ctrl);
    lbl_806792D8[kart].accel = fn_801E6CC8(ctrl);
    KartController_TimedUpdate(ctrl);
    int item = -1;
    if (fn_801E6DD4(ctrl)) {
        fn_801E6C54(ctrl, 0);
        if (fn_801E6594(ctrl)) {
            if (KartMovement_CanReceiveItem(KartController_GetRenderObj(ctrl), 1)) {
                int *items = ItemList(0);
                int *p = items;
                int count = 0;
                while (*p > -1) { ++p; ++count; }
                item = ItemAt(items, ReplayRandCursor_Advance(items, count, 0));
                fn_801E6C10(ctrl, item);
            }
        }
    }
    fn_801DC714(kart, item);
}
