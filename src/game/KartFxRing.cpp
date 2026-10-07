/* Ring explosion callbacks. These views describe only observed fields. */
struct Vec3 { float x, y, z; };
struct RingKartView { unsigned char pad00[0x238]; int alternateMode; };
struct RingEffectView {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char active;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0x5C];
    Vec3 position;
    Vec3 rotation;
    Vec3 velocity;
    float scale;
    signed char state, phase;
    unsigned char padB6[0x66];
    RingKartView *kart;
    Vec3 offset;
    unsigned char pad12C[0x24];
    float amount;
    unsigned char pad154[0x2C];
    unsigned int timer0, timer1, timer2, timer3;
};
struct RingCameraView { unsigned char pad00[0x80]; Vec3 position; };
extern "C" {
extern RingCameraView lbl_805DF3D0;
extern const float lbl_806D51C0, lbl_806D51C4, lbl_806D51C8;
extern const float lbl_806D51D0, lbl_806D51D4, lbl_806D51DC, lbl_806D51E8;
extern const float lbl_806D51F8, lbl_806D5200, lbl_806D5214, lbl_806D521C;
extern const float lbl_806D5250, lbl_806D527C, lbl_806D5280;
extern const float lbl_806D52AC, lbl_806D52B4, lbl_806D52B8;
void VfxSlot_BindResourceEx(void *, unsigned char, int);
void VfxSlot_SetPositionFromVec(void *, Vec3);
void VfxSlot_SetScaleUniform(void *, float);
void VfxSlot_SetRotationZ(void *, float);
void DrawEffect_Free(RingEffectView *);
RingEffectView *DrawEffect_SpawnDirect(void (*)(RingEffectView *));
void *KartDriver_GetJointByIdx(RingKartView *, int);
void *KartDriver_GetKartRootMtx(RingKartView *);
float Mtx44_GetYawOfPosZ_Padded(void *);
void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
float Vec3_Magnitude_Wrapper(const Vec3 *);
void Vec3_Scale(Vec3 *, const Vec3 *, float);
void GetSpawnPosition(Vec3 *, float, float, float);
void Vec2_RotateX(Vec3 *, const Vec3 *, float);
void Vec2_RotateY(Vec3 *, const Vec3 *, float);
int Rand_RangeIntMax(int);
float Rand_RangeFloat(float, float);
float BuildOrientationFromYaw(float);
unsigned char FinalLapCoinJump_CheckActiveForObject(RingKartView *);

static inline bool Decay(float *value, float step) {
    float minimum = 0.0f;
    *value -= step;
    if (*value < minimum) return true;
    return false;
}
static inline void GrowToLimit(float *value, float step, float limit) {
    float maximum = limit;
    float current = *value;
    *value = current + step;
    if (maximum < *value) *value = maximum;
}
static inline void AdvanceTimers(RingEffectView *effect) {
    if (effect->timer0) --effect->timer0;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
}
void KartFx_RingExplodeRayTick(RingEffectView *);
void KartFx_RingExplodeSparkTick(RingEffectView *effect) {
    switch (effect->state) {
    case 0:
        switch (Rand_RangeIntMax(15) % 3) {
        case 0: VfxSlot_BindResourceEx(effect->slot, 0x37, 0); break;
        case 1: VfxSlot_BindResourceEx(effect->slot, 0x38, 0); break;
        case 2: VfxSlot_BindResourceEx(effect->slot, 0x39, 0); break;
        }
        GetSpawnPosition(&effect->offset, lbl_806D51C0, lbl_806D51C0, lbl_806D51C0);
        GetSpawnPosition(&effect->velocity, lbl_806D51C0, lbl_806D51C0, lbl_806D51D0);
        Vec2_RotateX(&effect->velocity, &effect->velocity, lbl_806D527C);
        Vec2_RotateY(&effect->velocity, &effect->velocity, effect->rotation.y);
        effect->timer0 = 5;
        effect->rotation.z = lbl_806D521C * Rand_RangeFloat(lbl_806D5250, lbl_806D52AC);
        effect->scale = lbl_806D51E8;
        effect->active = 1;
        effect->lifetime = lbl_806D51C4;
        effect->state = 1;
        effect->phase = 0;
    case 1:
        if (effect->timer0 == 0) { effect->state = 2; effect->phase = 0; }
        break;
    case 2:
        if (Decay(&effect->lifetime, lbl_806D51D4)) {
            effect->active = 0; effect->state = 3; effect->phase = 0;
        }
        break;
    case 3:
        DrawEffect_Free(effect);
        return;
    }
    effect->velocity.y -= lbl_806D5280;
    Vec3_Add_DestFirst(&effect->offset, &effect->offset, &effect->velocity);
    Mtx44_GetTranslation_RowMajor(&effect->position, KartDriver_GetJointByIdx(effect->kart, 15));
    Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->offset);
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->rotation.z);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->active = 0;
    else effect->active = 1;
    AdvanceTimers(effect);
}
void KartFx_Slot50_RingExplodeTick(RingEffectView *effect) {
    Vec3 towardCamera;
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x3A, 0);
        effect->lifetime = lbl_806D51C4;
        effect->amount = lbl_806D51C4;
        effect->state = 1;
        effect->phase = 0;
        break;
    case 1: break;
    }
    if (Decay(&effect->amount, lbl_806D51D4)) {
        effect->active = 0;
        if (effect->kart->alternateMode == 0) {
            float yaw = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(effect->kart));
            for (int i = 0; i < 4; ++i) {
                RingEffectView *spark = DrawEffect_SpawnDirect(KartFx_RingExplodeSparkTick);
                if (spark) {
                    spark->kart = effect->kart;
                    spark->rotation.y = BuildOrientationFromYaw(lbl_806D521C * Rand_RangeFloat(lbl_806D52B4, lbl_806D51DC) + yaw);
                }
                yaw = BuildOrientationFromYaw(lbl_806D52B8 + yaw);
            }
        }
        RingEffectView *ray = DrawEffect_SpawnDirect(KartFx_RingExplodeRayTick);
        if (ray) ray->kart = effect->kart;
        DrawEffect_Free(effect);
        return;
    }
    Mtx44_GetTranslation_RowMajor(&effect->position, KartDriver_GetJointByIdx(effect->kart, 15));
    Vec3_Subtract_DestFirst(&towardCamera, &lbl_805DF3D0.position, &effect->position);
    float magnitude = Vec3_Magnitude_Wrapper(&towardCamera);
    magnitude = lbl_806D51C4 / magnitude;
    Vec3_Scale(&towardCamera, &towardCamera, lbl_806D5200 * magnitude);
    Vec3_Add_DestFirst(&effect->position, &effect->position, &towardCamera);
    effect->scale = lbl_806D5214 * effect->amount;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->active = 0;
    else effect->active = 1;
    AdvanceTimers(effect);
}
}
