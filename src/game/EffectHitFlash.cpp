/* Target-observed effect view; shared constants remain externally owned. */
struct HitVec { float x, y, z; };
struct HitItem { unsigned char pad[0xA0]; HitVec position; };
struct HitEffect {
    unsigned char pad00[0x10];
    int kind;
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x63];
    HitVec position;
    unsigned char pad98[8];
    float yaw;
    HitVec velocity;
    float scale;
    signed char state;
    unsigned char padB5[0x17];
    HitItem *item;
    unsigned char padD0[0x4C];
    void *kart;
    HitVec previous;
    unsigned char pad12C[0x24];
    float initialScale, fade, anisotropy, angularVelocity, trackedStep;
    unsigned char pad164[0x1C];
    unsigned int timers[4];
    signed char variant;
};
extern "C" {
extern const float lbl_806D54A8, lbl_806D54AC, lbl_806D54B0, lbl_806D54B4;
extern const float lbl_806D54B8, lbl_806D54BC, lbl_806D54C0, lbl_806D54C4;
extern const float lbl_806D54C8, lbl_806D54CC, lbl_806D54D0, lbl_806D54D4;
extern const float lbl_806D54D8, lbl_806D54DC, lbl_806D54E0, lbl_806D54E4;
extern const float lbl_806D54E8, lbl_806D54EC, lbl_806D54F0, lbl_806D54F4;
void VfxSlot_BindResourceEx(void *, int, int);
float Rand_RangeFloat(float, float);
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(HitVec *, const void *);
void Vec3_Subtract_DestFirst(HitVec *, const HitVec *, const HitVec *);
void Vec3_Add_DestFirst(HitVec *, const HitVec *, const HitVec *);
void Vec3_Copy(HitVec *, const HitVec *);
void DrawEffect_Free(HitEffect *);
float BuildOrientationFromYaw(float);
double FAbs_FloatAsDouble(float);
int Item_AdvanceTrackedHomingState(HitItem *, HitVec *, float);
void VfxSlot_SetPositionFromVec(void *, HitVec);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleVec3(void *, float, float, float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);

void Effect_HitFlash_Update(HitEffect *effect) {
    HitVec translation;
    HitVec delta;
    switch (effect->state) {
    case 0:
        switch (effect->kind) {
        case 0: VfxSlot_BindResourceEx(effect->slot, 0x4D, 0); break;
        case 1: VfxSlot_BindResourceEx(effect->slot, 0x80, 0); break;
        case 2: VfxSlot_BindResourceEx(effect->slot, 0x81, 0); break;
        case 3: VfxSlot_BindResourceEx(effect->slot, 0x57, 0); break;
        case 4: VfxSlot_BindResourceEx(effect->slot, 0x58, 0); break;
        }
        effect->initialScale = Rand_RangeFloat(lbl_806D54A8, lbl_806D54AC);
        switch (effect->kind) {
        case 0: break;
        case 1: effect->initialScale *= lbl_806D54B0; break;
        case 2: break;
        case 3: effect->initialScale *= lbl_806D54B4; break;
        case 4: effect->initialScale *= lbl_806D54B4; break;
        }
        if (effect->variant) effect->initialScale *= lbl_806D54B0;
        effect->fade = lbl_806D54B8;
        effect->anisotropy = Rand_RangeFloat(lbl_806D54BC, lbl_806D54C0);
        effect->yaw = lbl_806D54C4 * Rand_RangeFloat(lbl_806D54C8, lbl_806D54CC);
        effect->angularVelocity = lbl_806D54C4 * Rand_RangeFloat(lbl_806D54D0, lbl_806D54D4);
        effect->timers[0] = 30;
        if (effect->kart) Mtx44_GetTranslation_RowMajor(&effect->previous, KartDriver_GetKartRootMtx(effect->kart));
        if (effect->item) {
            Vec3_Subtract_DestFirst(&effect->previous, &effect->position, &effect->item->position);
            Rand_RangeFloat(lbl_806D54D8, lbl_806D54DC);
            Rand_RangeFloat(lbl_806D54D8, lbl_806D54DC);
            Rand_RangeFloat(lbl_806D54D8, lbl_806D54DC);
            effect->trackedStep = Rand_RangeFloat(lbl_806D54C0, lbl_806D54E0);
        }
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->timers[0] == 0) {
        effect->fade -= lbl_806D54E4;
        if (effect->fade < lbl_806D54E8) {
            DrawEffect_Free(effect);
            return;
        }
    }
    effect->velocity.y += lbl_806D54EC;
    effect->velocity.x *= lbl_806D54F0;
    effect->velocity.z *= lbl_806D54F0;
    effect->yaw = BuildOrientationFromYaw(effect->yaw + effect->angularVelocity);
    if (FAbs_FloatAsDouble(effect->anisotropy) < lbl_806D54F4) effect->anisotropy = lbl_806D54E8;
    else if (effect->anisotropy < lbl_806D54E8) effect->anisotropy += lbl_806D54F4;
    else effect->anisotropy -= lbl_806D54F4;
    Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->velocity);
    if (effect->kart) {
        Mtx44_GetTranslation_RowMajor(&translation, KartDriver_GetKartRootMtx(effect->kart));
        Vec3_Subtract_DestFirst(&delta, &translation, &effect->previous);
        Vec3_Add_DestFirst(&effect->position, &effect->position, &delta);
        Vec3_Copy(&effect->previous, &translation);
    }
    if (effect->item) {
        if (Item_AdvanceTrackedHomingState(effect->item, &effect->previous, effect->trackedStep) == 1) effect->timers[0] = 0;
        Vec3_Add_DestFirst(&effect->position, &effect->item->position, &effect->previous);
    }
    effect->scale = effect->initialScale * effect->fade;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->yaw);
    {
        float one, anisotropy, scale;
        anisotropy = effect->anisotropy;
        one = lbl_806D54B8;
        scale = effect->scale;
        VfxSlot_SetScaleVec3(effect->slot, scale * (one + anisotropy), scale * (one - anisotropy), scale);
    }
    if (effect->timers[0]) --effect->timers[0];
    if (effect->timers[1]) --effect->timers[1];
    if (effect->timers[2]) --effect->timers[2];
    if (effect->timers[3]) --effect->timers[3];
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
}
}
