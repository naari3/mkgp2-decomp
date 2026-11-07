/* PhysicsState_AccelInterpolate: step the current accel values at +0x6C/+0x74
 * toward the requested a/b by the kart's tuned accel rate. */
extern int g_roundIndex;
extern int g_cupId;
extern void *GetEnemyParam(void);
extern char *GetKartTuningEntry(void *, int, int, int);
extern const float lbl_806DA448, lbl_806DA444;
#define F(o) (*(float *)(self + (o)))

static inline float AccelRate(char *entry) {
    return lbl_806DA448 * *(float *)(entry + 4);
}

void PhysicsState_AccelInterpolate(char *self, float a, float b) {
    int round = g_roundIndex;
    int cup = g_cupId;
    float step = lbl_806DA444 * AccelRate(GetKartTuningEntry(GetEnemyParam(), cup, round, *(int *)(self + 0x10)));
    float d = a - F(0x6C);
    if (step < d) F(0x6C) += step;
    else if (d < -step) F(0x6C) -= step;
    else F(0x6C) = a;
    F(0x70) = a;
    {
        float d = b - F(0x74);
        if (step < d) F(0x74) += step;
        else if (d < -step) F(0x74) -= step;
        else F(0x74) = b;
    }
    F(0x78) = b;
}
