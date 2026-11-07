/* Native candidate: 99.09091% text; automatic extab/extabindex exact.
 * Remaining FP homes: step f4 instead of f2, second delta f2 instead of f3. */
extern int g_roundIndex;
extern int g_cupId;
extern void *GetEnemyParam(void);
extern char *GetKartTuningEntry(void *, int, int, int);
extern const float lbl_806DA448, lbl_806DA444;
#define F(o) (*(float *)(self + (o)))

static inline void ApproachAccel(float *current, float target, float step) {
    float delta = target - *current;
    if (step < delta) *current += step;
    else if (delta < -step) *current -= step;
    else *current = target;
}

static inline float AccelRate(char *entry) {
    return lbl_806DA448 * *(float *)(entry + 4);
}

void PhysicsState_AccelInterpolate(char *self, float a, float b) {
    int round = g_roundIndex;
    int cup = g_cupId;
    float step = lbl_806DA444 * AccelRate(GetKartTuningEntry(GetEnemyParam(), cup, round, *(int *)(self + 0x10)));
    ApproachAccel(&F(0x6C), a, step);
    F(0x70) = a;
    ApproachAccel(&F(0x74), b, step);
    F(0x78) = b;
}
