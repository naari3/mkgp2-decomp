/* Drift-spark shadow colour controller: observed local ABI views only. */
struct Vec3 { float x, y, z; };
struct KartState { unsigned char pad00[0x10]; unsigned long long flags; };
struct Kart { unsigned char pad00[0x238]; int enabled; unsigned char pad23C[0xC8]; KartState *state; };
struct Effect {
    unsigned char pad00[0x2C]; float alpha; Vec3 color;
    unsigned char pad3C[0x78]; signed char state, phase;
    unsigned char padB6[0x13]; signed char expired;
    unsigned char padCA[0x52]; Kart *kart;
    unsigned char pad120[0x30]; float opacity, red, green, blue;
    unsigned char pad160[0x20]; unsigned int duration, rise, delay, refractory;
    signed char variant, shadowActive;
};
struct ResourceView { unsigned char pad00[0x890]; Vec3 colors[3]; };
extern "C" {
extern ResourceView lbl_80329E20;
extern void *lbl_806D109C;
extern const float lbl_806D51C0, lbl_806D51C4, lbl_806D51D4, lbl_806D51D8;
extern const float lbl_806D528C, lbl_806D5274;
void DrawEffect_Free(Effect *);
int ShadowBillboard_SetEffectParams(void *, int, float, float, float, float);
void GetSpawnPosition(Vec3 *, float, float, float);
void Vec3_Lerp(Vec3 *, Vec3, Vec3, float);
}
static inline void *PresentOrNull(void *p) { if (!p) p = 0; return p; }
static inline unsigned char SparkFlag(KartState *s) {
    unsigned char b;
    if ((s->flags & 0x800ULL) == 0) b = 0; else b = 1;
    return b;
}
static inline void ResetShadow(Effect *e) {
    if (e->shadowActive) ShadowBillboard_SetEffectParams(PresentOrNull(lbl_806D109C), 5,
        lbl_806D51C0, lbl_806D51C0, lbl_806D51C0, lbl_806D51C0);
    e->shadowActive = 0;
}
static inline bool Decay(float *value, float step, float minimum) {
    *value -= step;
    if (*value < minimum) return true;
    return false;
}
extern "C" void KartFx_Slot60_DriftSparkTick(Effect *e) {
    ResourceView *resources = &lbl_80329E20;
    KartState *s = e->kart->state;
    int red = 0;
    if (SparkFlag(s)) red = 1;
    int green = 0;
    if ((s->flags & 0x200000000ULL) != 0) green = 1;
    int blue = 0;
    if ((s->flags & 0x4000000000ULL) != 0) blue = 1;
    int interrupt = 0;
    if ((s->flags & 0x10000ULL) != 0) interrupt = 1;
    if (e->expired) { ResetShadow(e); DrawEffect_Free(e); return; }
    switch (e->state) {
    case 0:
        e->opacity = lbl_806D51C0;
        e->red = lbl_806D51C0; e->green = lbl_806D51C0; e->blue = lbl_806D51C0;
        if (red) e->red = lbl_806D51C4;
        if (green) e->green = lbl_806D51C4;
        if (blue) e->blue = lbl_806D51C4;
        if (red) e->variant = 1;
        if (green) e->variant = 2;
        if (blue) e->variant = 3;
        e->shadowActive = 0; ++e->state; e->phase = 0;
    case 1:
        if (red || green || blue) {
            e->red = lbl_806D51C0; e->green = lbl_806D51C0; e->blue = lbl_806D51C0;
            if (red) e->red = lbl_806D51C4;
            if (green) e->green = lbl_806D51C4;
            if (blue) e->blue = lbl_806D51C4;
            if (red) e->variant = 1;
            if (green) e->variant = 2;
            if (blue) e->variant = 3;
            e->refractory = 0; ++e->state; e->phase = 0;
        }
        break;
    case 2:
        if (e->refractory == 0 && (red || green || blue)) {
            if (red) e->variant = 1;
            if (green) e->variant = 2;
            if (blue) e->variant = 3;
            e->phase = 0; e->refractory = 60;
        }
        switch (e->phase) {
        case 0:
            if (e->variant == 0) e->duration = 120;
            else e->duration = 60;
            e->rise = 10; e->delay = 3; e->shadowActive = 1; ++e->phase;
        case 1:
            if (e->rise != 0) {
                e->opacity += lbl_806D51D4;
                if (lbl_806D51C4 < e->opacity) e->opacity = lbl_806D51C4;
            } else {
                float minimum = lbl_806D5274;
                if (Decay(&e->opacity, lbl_806D528C, minimum)) e->opacity = minimum;
            }
            if (e->delay == 0 && interrupt) e->duration = 0;
            if (e->duration == 0) ++e->phase;
            break;
        case 2:
            if (Decay(&e->opacity, lbl_806D528C, 0.0f)) {
                e->opacity = 0.0f; ResetShadow(e);
                e->state = 1; e->phase = 0; return;
            }
            break;
        }
        switch (e->variant) {
        case 1: e->red += lbl_806D51D8; e->green -= lbl_806D51D8; e->blue -= lbl_806D51D8; break;
        case 2: e->red -= lbl_806D51D8; e->green += lbl_806D51D8; e->blue -= lbl_806D51D8; break;
        case 3: e->red -= lbl_806D51D8; e->green -= lbl_806D51D8; e->blue += lbl_806D51D8; break;
        }
        if (e->red < 0.0f) e->red = 0.0f;
        if (e->green < 0.0f) e->green = 0.0f;
        if (e->blue < 0.0f) e->blue = 0.0f;
        if (lbl_806D51C4 < e->red) e->red = lbl_806D51C4;
        if (lbl_806D51C4 < e->green) e->green = lbl_806D51C4;
        if (lbl_806D51C4 < e->blue) e->blue = lbl_806D51C4;
        {
            Vec3 a = resources->colors[0], b = resources->colors[1], c = resources->colors[2];
            GetSpawnPosition(&e->color, lbl_806D51C0, lbl_806D51C0, lbl_806D51C0);
            Vec3_Lerp(&e->color, a, e->color, e->red);
            Vec3_Lerp(&e->color, b, e->color, e->green);
            Vec3_Lerp(&e->color, c, e->color, e->blue);
        }
        e->alpha = e->opacity;
        if (e->kart->enabled == 0) ResetShadow(e);
        else {
            ShadowBillboard_SetEffectParams(PresentOrNull(lbl_806D109C), 5, e->color.x, e->color.y, e->color.z, e->alpha);
            e->shadowActive = 1;
        }
        break;
    }
    if (e->duration) --e->duration;
    if (e->rise) --e->rise;
    if (e->delay) --e->delay;
    if (e->refractory) --e->refractory;
}
