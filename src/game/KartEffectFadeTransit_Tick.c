typedef struct KartEffectFadeTransit {
    unsigned char active;
    unsigned char pad[3];
    void *owner;
    void *kartBody;
    void *shadowBillboard;
    float value;
    float target;
    int timer;
} KartEffectFadeTransit;

typedef struct KartEffectFadeTransitOwner {
    unsigned char pad[8];
    unsigned int field8;
    float fieldC;
    unsigned char pad10[0x18];
    int field28;
} KartEffectFadeTransitOwner;

extern float lbl_806D2890;
extern float lbl_806D2894;
extern float lbl_806D2898;
extern float lbl_806D289C;
extern void KartBody_SetWarpTransitFlag(void *kartBody, int enabled);
extern void ShadowBillboard_BeginFadeCleanup(void *shadowBillboard);
extern void ShadowBillboard_SetField0xA4(void *shadowBillboard, float value);

void KartEffectFadeTransit_Tick(KartEffectFadeTransit *self)
{
    KartEffectFadeTransitOwner *owner;
    float limit;

    if ((self->timer != 0) && (self->target < self->value)) {
        limit = lbl_806D2898;
        self->target += lbl_806D2894;
        if (self->target <= limit) {
            ShadowBillboard_SetField0xA4(
                self->shadowBillboard,
                lbl_806D289C * ((limit - self->target) / limit));
        }
        if (self->target >= self->value) {
            float zero;

            ShadowBillboard_SetField0xA4(self->shadowBillboard, lbl_806D2890);
            zero = lbl_806D2890;
            self->value = zero;
            self->target = zero;
            self->timer = 0;

            owner = self->owner;
            if (owner->field28 > 0) {
                if (owner->fieldC < zero) {
                    owner->fieldC = zero;
                }
                owner->field8 = 0;
            }
            KartBody_SetWarpTransitFlag(self->kartBody, 0);
            ShadowBillboard_BeginFadeCleanup(self->shadowBillboard);
        }
    }
}
