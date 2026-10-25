/* Per-kart AI tick: drives speed before the race starts, then the AI logic. */
struct PathSlot {
    float v[3];
    float speed;
    float accel;
    int ids[3];
};

class KartAI {
public:
    virtual void v8();
    virtual void vC();
    virtual void Think(int kart);
};

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

extern "C" void fn_801E9594(KartAI *self, int kart) {
    void *ctrl = Read_U32[kart];
    int target;

    if (ctrl == 0) {
        return;
    }
    if (!IsRaceStarted()) {
        float speed = StartSpeed(kart);
        KartController_SetTargetSpeed(ctrl, speed, speed);
    } else {
        self->Think(kart);
    }
    fn_801E6B64(ctrl, fn_801DC72C(kart));
    fn_801E6B38(ctrl, lbl_806792D8[kart].speed);
    fn_801E6B0C(ctrl, lbl_806792D8[kart].accel);
    KartController_TimedUpdate(ctrl);
    target = fn_801DC6FC(kart);
    if (target != -1) {
        fn_801E6C10(ctrl, target);
    }
}
