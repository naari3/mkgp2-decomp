/* Narrow target-observed layout; live Ghidra types unavailable. */
struct BurstVec { float x, y, z; };
struct BurstEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x78];
    BurstVec position;
    float rotationX, rotationY, rotationZ;
    BurstVec velocity;
    float scale;
    signed char state;
    unsigned char padB5[0xCB];
    unsigned int timer0, timer1, timer2, timer3;
};
extern "C" {
extern const float lbl_806D555C, lbl_806D5560, lbl_806D5570, lbl_806D5574, lbl_806D5578;
void VfxSlot_BindResourceEx(void *, int, int);
int Rand_RangeInt(int, int);
float Rand_RangeFloatMax(float);
float Rand_RangeFloat(float, float);
void GetSpawnPosition(BurstVec *, float, float, float);
void Vec2_RotateX(BurstVec *, const BurstVec *, float);
void Vec2_RotateY(BurstVec *, const BurstVec *, float);
void DrawEffect_Free(BurstEffect *);
void Vec3_Add_DestFirst(BurstVec *, const BurstVec *, const BurstVec *);
void VfxSlot_SetPositionFromVec(void *, BurstVec);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);
void Effect_Burst_Res8F_Update(BurstEffect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x8F, 0);
        effect->timer0 = Rand_RangeInt(2, 6);
        GetSpawnPosition(&effect->velocity, lbl_806D555C, lbl_806D555C, lbl_806D5570);
        Vec2_RotateX(&effect->velocity, &effect->velocity, lbl_806D5574 * Rand_RangeFloatMax(lbl_806D5578));
        Vec2_RotateY(&effect->velocity, &effect->velocity, lbl_806D5574 * Rand_RangeFloatMax(lbl_806D5578));
        ++effect->state;
        break;
    case 1:
        break;
    }
    if (!effect->timer0) {
        DrawEffect_Free(effect);
        return;
    }
    Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->velocity);
    effect->rotationZ = lbl_806D5574 * Rand_RangeFloatMax(lbl_806D5578);
    effect->scale = Rand_RangeFloat(lbl_806D5560, lbl_806D5570);
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->rotationZ);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (effect->timer0) --effect->timer0;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
}
}
