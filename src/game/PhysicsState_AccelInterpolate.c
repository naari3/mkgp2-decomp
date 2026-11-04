/* Native candidate: 96.59091% text; automatic extab/extabindex exact.
 * FP web and constant-load ordering remain different after bounded probes. */
extern int g_roundIndex;
extern int g_cupId;
extern void *GetEnemyParam(void);
extern char *GetKartTuningEntry(void *, int, int, int);
extern const float lbl_806DA448, lbl_806DA444;
#define F(o) (*(float *)(self + (o)))
void PhysicsState_AccelInterpolate(char *self, float a, float b) {
    int round = g_roundIndex;
    int cup = g_cupId;
    float gain;
    float step;
    float delta;
    gain = *(float *)(GetKartTuningEntry(GetEnemyParam(), cup, round, *(int *)(self + 0x10)) + 4);
    gain = lbl_806DA448 * gain;
    step = lbl_806DA444 * gain;
    delta = a - F(0x6C);
    if (step < delta) F(0x6C) += step;
    else if (delta < -step) F(0x6C) -= step;
    else F(0x6C) = a;
    F(0x70) = a;
    delta = b - F(0x74);
    if (step < delta) F(0x74) += step;
    else if (delta < -step) F(0x74) -= step;
    else F(0x74) = b;
    F(0x78) = b;
}
