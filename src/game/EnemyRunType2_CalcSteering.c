extern void *GetEnemyParam(void);
extern char *GetKartTuningEntry(void *param, int cup, int round, int kart);
extern int g_cupId;
extern int g_roundIndex;
extern float lbl_806D1948;
extern const float lbl_806DA428;
extern const float lbl_806DA42C;
extern const float lbl_806DA430;
extern const float lbl_806DA434;
extern const float lbl_806DA438;

typedef struct EnemyRun {
    char pad_0[0x10];
    int kartId;
    char pad_14[0x89];
    unsigned char reverse;
} EnemyRun;

float EnemyRunType2_CalcSteering(EnemyRun *self, float input) {
    int round = g_roundIndex;
    int cup = g_cupId;
    float gain;
    float result;

    gain = *(float *)(GetKartTuningEntry(GetEnemyParam(), cup, round, self->kartId) + 0x30);
    if (lbl_806DA428 < gain) {
        gain = lbl_806DA428;
    }
    if (gain < lbl_806DA42C) {
        gain = lbl_806DA42C;
    }
    gain *= lbl_806DA430;
    result = lbl_806D1948 * gain;
    result -= lbl_806DA434 * input;
    if (self->reverse) {
        result *= lbl_806DA438;
    }
    return result;
}
