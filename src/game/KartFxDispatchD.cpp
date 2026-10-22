/* Local views of the fields consumed by the ring-burst dispatcher.
 * NonMatching: independent stack aggregates and signed comparison codegen
 * remain different. Native EH is compiler-generated; no resource is owned here.
 */
struct RingVec { float x, y, z; };
struct RingAngles { float value[8]; };
struct RingColor { float value[3]; };
struct RingOrder { int value[8]; };
struct RingColors { RingColor color; RingOrder order; };
struct RingResources {
    unsigned char before[0x588];
    RingAngles angles;
    RingColors colors;
};
struct RingPayload {
    void *kart;
    unsigned char pad04[4];
    signed char kind, previousKind;
    unsigned char pad0a[0x3a];
    float strength;
};
struct RingEffect {
    unsigned char pad00[0x10];
    int kind;
    unsigned char pad14[0x108];
    void *kart;
    unsigned char pad120[0x30];
    float phase, strength, color;
    unsigned char pad15c[0x34];
    unsigned char firstPair;
};
extern "C" {
extern const RingResources lbl_80329E20;
extern const float lbl_806D51E8, lbl_806D51C0, lbl_806D51C8;
extern const float lbl_806D53B0, lbl_806D53B4, lbl_806D52C4;
extern const float lbl_806D53B8, lbl_806D53BC, lbl_806D53C0;
extern const float lbl_806D53C4, lbl_806D53C8, lbl_806D53CC;
extern int g_cupId;
const float *KartDriver_GetKartRootMtx(void *);
void Mtx_TransposeToMtx44(float *, const float *);
void Mtx44_GetTranslation_ColMajor(RingVec *, const float *);
float BuildOrientationFromYaw(float);
int Rand_RangeInt(int, int);
void EffectVfx1C_DriftSparkRing_Tick(RingEffect *);
void EffectVfx84_85_BoostChargeRing_Tick(RingEffect *);
void EffectVfx86_BoostRingCenter_Tick(RingEffect *);
RingEffect *DrawEffect_SpawnDirect(void (*)(RingEffect *));

void KartFx_DispatchGroupD_RingBurst(void *, RingPayload *payload, void *, int enabled) {
    const RingResources *resources = &lbl_80329E20;
    RingColor color;
    RingVec position;
    RingOrder order;
    RingAngles angles;
    float base[16];
    float strength = payload->strength;
    strength *= lbl_806D51E8;
    payload->strength = lbl_806D51C0;
    if (strength < lbl_806D51C8) return;
    signed char kind = 0;
    if (payload->kind == payload->previousKind) kind = payload->kind;
    Mtx_TransposeToMtx44(base, KartDriver_GetKartRootMtx(payload->kart));
    Mtx44_GetTranslation_ColMajor(&position, base);
    switch (kind) {
    case 1: case 2: case 3:
        if (enabled) {
            angles = resources->angles;
            angles.value[0] = BuildOrientationFromYaw(lbl_806D53B0);
            angles.value[1] = BuildOrientationFromYaw(lbl_806D53B4);
            angles.value[2] = BuildOrientationFromYaw(lbl_806D52C4);
            angles.value[3] = BuildOrientationFromYaw(lbl_806D53B8);
            angles.value[4] = BuildOrientationFromYaw(lbl_806D53BC);
            angles.value[5] = BuildOrientationFromYaw(lbl_806D53C0);
            angles.value[6] = BuildOrientationFromYaw(lbl_806D53C4);
            angles.value[7] = BuildOrientationFromYaw(lbl_806D53C8);
            color = resources->colors.color;
            order = resources->colors.order;
            for (int i = 0; i < 2; ++i) {
                int a = Rand_RangeInt(0, 2);
                int b = a + Rand_RangeInt(1, 2);
                if (b >= 3) b -= 3;
                order.value[i*3+2] = a;
                order.value[i*3+3] = b;
                order.value[i*3+4] = 3 - a - b;
            }
            for (int i = 0; i < 8; ++i) {
                RingEffect *effect = DrawEffect_SpawnDirect(EffectVfx1C_DriftSparkRing_Tick);
                if (effect) {
                    effect->kind = (unsigned char)kind;
                    effect->kart = payload->kart;
                    effect->phase = angles.value[i];
                    effect->strength = strength;
                    effect->color = color.value[order.value[i]];
                    effect->firstPair = i < 2 ? 1 : 0;
                }
            }
        }
        break;
    case 4:
        if (enabled) {
            float angle = lbl_806D51C0;
            for (int i = 0; i < 24; ++i) {
                RingEffect *effect = DrawEffect_SpawnDirect(EffectVfx84_85_BoostChargeRing_Tick);
                if (effect) {
                    effect->kart = payload->kart;
                    effect->phase = angle;
                }
                angle = BuildOrientationFromYaw(lbl_806D53CC + angle);
            }
        }
        if (g_cupId != 8 && enabled) {
            RingEffect *effect = DrawEffect_SpawnDirect(EffectVfx86_BoostRingCenter_Tick);
            if (effect) effect->kart = payload->kart;
        }
        break;
    }
}
}
