typedef struct KartTuningEntry {
    unsigned char pad[0x30];
    float steering;
} KartTuningEntry;

typedef struct EnemyRunner {
    unsigned char pad_00[0x10];
    int kartId;
    unsigned char pad_14[0x89];
    unsigned char boosted;
} EnemyRunner;

extern int g_roundIndex;
extern int g_cupId;
extern void *GetEnemyParam(EnemyRunner *);
extern KartTuningEntry *GetKartTuningEntry(void *param, int cup, int round, int kart);

static inline float clamp_steer(float v) {
    if (100.0f < v) {
        v = 100.0f;
    }
    if (v < 0.0f) {
        v = 0.0f;
    }
    return v;
}

float EnemyRunType1_CalcSteering(EnemyRunner *enemy, float scale) {
    int round = g_roundIndex;
    int cup = g_cupId;
    float steering;
    float result;

    steering = GetKartTuningEntry(GetEnemyParam(enemy), cup, round, enemy->kartId)->steering;
    if (100.0f < steering) {
        steering = 100.0f;
    }
    if (steering < 0.0f) {
        steering = 0.0f;
    }
    steering *= 0.01f;
    result = 0.59999996f * steering + 0.1f;
    result *= scale;
    if (enemy->boosted) {
        result *= 0.15f;
    }
    return result;
}
