/* Narrow target-observed view; shared data is externally owned. */
struct ExplosionVec { float x, y, z; };
struct ExplosionEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float opacity;
    ExplosionVec origin;
    unsigned char pad3C[0x50];
    ExplosionVec position;
    unsigned char pad98[8];
    float yaw;
    ExplosionVec velocity;
    float scale;
    signed char state;
    unsigned char padB5[0x67];
    void *kart;
    ExplosionVec previous, tracked;
    unsigned char pad138[0x18];
    float growth, initialScale, fade, angularVelocity, tracking;
    unsigned char pad164[0x1C];
    unsigned int timers[4];
    signed char initialMode, sizeMode, resourceMode, alphaMode;
};
extern "C" {
extern const float lbl_806D54B0, lbl_806D54B4, lbl_806D54B8, lbl_806D54C0;
extern const float lbl_806D54C4, lbl_806D54C8, lbl_806D54CC, lbl_806D54E0;
extern const float lbl_806D54E8, lbl_806D54F4, lbl_806D54F8, lbl_806D54FC;
extern const float lbl_806D5500, lbl_806D5504, lbl_806D5508, lbl_806D550C;
extern const float lbl_806D5510, lbl_806D5514, lbl_806D5518, lbl_806D551C;
void VfxSlot_BindResourceEx(void *, int, int);
void Vec3_Copy(ExplosionVec *, const ExplosionVec *);
void Vec3_Scale(ExplosionVec *, const ExplosionVec *, float);
void Vec3_Add_DestFirst(ExplosionVec *, const ExplosionVec *, const ExplosionVec *);
void Vec3_Subtract_DestFirst(ExplosionVec *, const ExplosionVec *, const ExplosionVec *);
float Rand_RangeFloat(float, float);
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(ExplosionVec *, const void *);
void GetSpawnPosition(ExplosionVec *, float, float, float);
void DrawEffect_Free(ExplosionEffect *);
float BuildOrientationFromYaw(float);
void VfxSlot_SetPositionFromVec(void *, ExplosionVec);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);

void Effect_ExplosionPiece_Update(ExplosionEffect *effect) {
    ExplosionVec translation;
    ExplosionVec delta;
    switch (effect->state) {
    case 0:
        switch (effect->resourceMode) {
        case 0: VfxSlot_BindResourceEx(effect->slot, 0x6D, 0); break;
        case 1: VfxSlot_BindResourceEx(effect->slot, 0x6F, 0); break;
        case 2: VfxSlot_BindResourceEx(effect->slot, 0x6E, 0); break;
        }
        Vec3_Copy(&effect->origin, &effect->previous);
        if (effect->initialMode == 0) effect->growth = lbl_806D54B8;
        else effect->growth = lbl_806D54E8;
        switch (effect->sizeMode) {
        case 1: effect->initialScale = lbl_806D54C0 * Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC); break;
        case 2: effect->initialScale = Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC); break;
        case 3: effect->initialScale = lbl_806D54E0 * Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC); break;
        case 4: effect->initialScale = lbl_806D5500 * Rand_RangeFloat(lbl_806D54F8, lbl_806D54FC); break;
        }
        if (effect->initialMode == 0) effect->fade = lbl_806D54E8;
        else effect->fade = lbl_806D54B8;
        effect->yaw = lbl_806D54C4 * Rand_RangeFloat(lbl_806D54C8, lbl_806D54CC);
        effect->angularVelocity = lbl_806D54C4 * Rand_RangeFloat(lbl_806D5504, lbl_806D5508);
        if (effect->kart) Mtx44_GetTranslation_RowMajor(&effect->previous, KartDriver_GetKartRootMtx(effect->kart));
        GetSpawnPosition(&effect->tracked, lbl_806D54E8, lbl_806D54E8, lbl_806D54E8);
        effect->timers[0] = 15;
        effect->tracking = lbl_806D54B8;
        ++effect->state;
        break;
    case 1:
        {
            effect->growth += lbl_806D54B4;
            float limit = lbl_806D54B8;
            if (limit <= effect->growth) effect->growth = limit;
        }
        {
            effect->fade += lbl_806D54B4;
            float limit = lbl_806D54B8;
            if (limit <= effect->fade) effect->fade = limit;
        }
        if (lbl_806D54B8 <= effect->growth && lbl_806D54B8 <= effect->fade) ++effect->state;
        break;
    case 2:
        effect->growth += lbl_806D550C;
        effect->fade -= lbl_806D5510;
        if (effect->fade < lbl_806D54E8) { DrawEffect_Free(effect); return; }
        break;
    }
    if (effect->timers[0] == 0) {
        effect->tracking -= lbl_806D5514;
        float zero = lbl_806D54E8;
        if (effect->tracking < zero) effect->tracking = zero;
    }
    Vec3_Scale(&effect->velocity, &effect->velocity, lbl_806D5518);
    effect->velocity.y += lbl_806D54F4;
    Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->velocity);
    if (effect->kart) {
        Mtx44_GetTranslation_RowMajor(&translation, KartDriver_GetKartRootMtx(effect->kart));
        Vec3_Subtract_DestFirst(&delta, &translation, &effect->previous);
        Vec3_Scale(&delta, &delta, effect->tracking);
        Vec3_Add_DestFirst(&effect->position, &effect->position, &delta);
        Vec3_Copy(&effect->previous, &translation);
        Vec3_Copy(&effect->tracked, &delta);
    }
    effect->yaw = BuildOrientationFromYaw(effect->yaw + effect->angularVelocity);
    switch (effect->resourceMode) {
    case 0: effect->scale = lbl_806D54B0 * (effect->growth * effect->initialScale); break;
    case 1: effect->scale = lbl_806D5508 * (effect->growth * effect->initialScale); break;
    case 2: effect->scale = lbl_806D5508 * (effect->growth * effect->initialScale); break;
    }
    switch (effect->alphaMode) {
    case 0: effect->opacity = lbl_806D54C0 * effect->fade; break;
    case 1: effect->opacity = effect->fade; break;
    case 2: effect->opacity = lbl_806D551C * effect->fade; break;
    }
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->yaw);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (effect->timers[0]) --effect->timers[0];
    if (effect->timers[1]) --effect->timers[1];
    if (effect->timers[2]) --effect->timers[2];
    if (effect->timers[3]) --effect->timers[3];
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
}
}
