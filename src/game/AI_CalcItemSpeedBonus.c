typedef struct KartStatus {
    char pad0[0x4];
    unsigned char boosting;
    char pad5[0xB];
    unsigned long long flagsA;
    unsigned long long flagsB;
} KartStatus;

typedef struct RenderObj {
    char pad[0x304];
    KartStatus *status;
} RenderObj;

typedef struct KartObj {
    char pad[0xF0];
    int hitCooldown;
} KartObj;

typedef struct AIItemState {
    char pad0[0x4];
    void *car;
    char pad8[0x10];
    unsigned char useBoost;
    unsigned char useBrake;
    char pad1A[2];
    int boostTimer;
    float boostPenalty;
    int hitTimer;
    float hitPenalty;
} AIItemState;

extern KartObj *Read_U32[];
extern void *fn_801DE1B0(void);
extern RenderObj *CarObject_GetRenderObj(void *car);
extern float fn_801DE0E8(void *param);
extern float fn_801DE000(void *param);
extern int fn_801DDE7C(void *param);
extern float fn_801DDF04(void *param);
extern int fn_801DDD6C(void *param);
extern float fn_801DDDF4(void *param);
extern int AI_GetHitCooldown(int kart);

static inline int KartStatus_HasFlag(KartStatus *s, unsigned long long mask) {
    unsigned long long f = s->flagsA;
    f |= s->flagsB;
    return (f & mask) != 0;
}

float AI_CalcItemSpeedBonus(AIItemState *self, int kart) {
    KartStatus *status;
    KartObj *kartObj;
    void *param;
    float bonus;

    kartObj = Read_U32[kart];
    param = fn_801DE1B0();
    status = CarObject_GetRenderObj(self->car)->status;
    bonus = 0.0f;

    if (self->useBoost) {
        bonus += fn_801DE0E8(param);
    }
    if (self->useBrake) {
        bonus -= fn_801DE000(param);
    }
    if (status->boosting && self->boostTimer <= 0) {
        self->boostTimer = fn_801DDE7C(param);
        self->boostPenalty = fn_801DDF04(param);
    }
    if (self->boostTimer > 0) {
        bonus -= self->boostPenalty;
        self->boostTimer--;
        if (self->boostTimer <= 0) {
            self->boostTimer = 0;
            self->boostPenalty = 0.0f;
        }
    }
    if (KartStatus_HasFlag(status, 0x10000) && self->hitTimer <= 0) {
        self->hitTimer = fn_801DDD6C(param);
        self->hitPenalty = fn_801DDDF4(param);
    }
    if (KartStatus_HasFlag(status, 0x10000)) {
        int cooldown = AI_GetHitCooldown(kart);
        if (cooldown > 0 && kartObj->hitCooldown < cooldown) {
            kartObj->hitCooldown = cooldown;
        }
    }
    if (self->hitTimer > 0) {
        bonus -= self->hitPenalty;
        self->hitTimer--;
        if (self->hitTimer <= 0) {
            self->hitTimer = 0;
            self->hitPenalty = 0.0f;
        }
    }
    return bonus;
}
