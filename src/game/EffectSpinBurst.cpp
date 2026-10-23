/* Narrow target-observed layout; live Ghidra types unavailable. */
struct SpinVec { float x, y, z; };
struct SpinEffect {
    char pad00[0x10];
    int kind;
    char slot[0x14];
    unsigned char visible;
    char pad29[3];
    float alpha;
    char pad30[0x5C];
    SpinVec position, rotation, velocity;
    float scale;
    signed char state;
    unsigned char finished;
    char padB6[0x66];
    void *kart;
    SpinVec offset;
    char pad12C[0x24];
    float angularVelocity;
    char pad154[0x2C];
    unsigned int timers[4];
};
extern "C" {
extern unsigned char lbl_806CF310[6], lbl_806CF318[6];
extern const float lbl_806D57A4, lbl_806D57A8, lbl_806D577C, lbl_806D57AC, lbl_806D57B0;
extern const float lbl_806D57B4, lbl_806D5770, lbl_806D57B8;
int Rand_RangeIntMax(int);
int Rand_RangeInt(int, int);
float Rand_RangeFloat(float, float);
void VfxSlot_BindResourceEx(void *, int, int);
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(SpinVec *, const void *);
void Vec3_Subtract_DestFirst(SpinVec *, const SpinVec *, const SpinVec *);
void Vec3_Add_DestFirst(SpinVec *, const SpinVec *, const SpinVec *);
void DrawEffect_Free(SpinEffect *);
float BuildOrientationFromYaw(float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void VfxSlot_SetPositionFromVec(void *, SpinVec);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);
void Effect_SpinBurst_Update(SpinEffect *effect) {
    switch (effect->state) {
    case 0:
        switch (effect->kind) {
        case 0x3D: VfxSlot_BindResourceEx(effect->slot, lbl_806CF310[Rand_RangeIntMax(4)], 0); break;
        case 0x3F: VfxSlot_BindResourceEx(effect->slot, lbl_806CF318[Rand_RangeIntMax(4)], 0); break;
        }
        effect->rotation.z = lbl_806D577C * Rand_RangeFloat(lbl_806D57A4, lbl_806D57A8);
        effect->angularVelocity = lbl_806D577C * Rand_RangeFloat(lbl_806D57AC, lbl_806D57B0);
        effect->timers[0] = Rand_RangeInt(0, 15);
        if (effect->kart) {
            SpinVec root;
            Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(effect->kart));
            Vec3_Subtract_DestFirst(&effect->offset, &effect->position, &root);
        }
        effect->state = 1;
        effect->finished = 0;
        break;
    case 1: break;
    }
    if (!effect->timers[0]) {
        effect->alpha -= lbl_806D57B4;
        if (effect->alpha < lbl_806D5770) { DrawEffect_Free(effect); return; }
    }
    effect->rotation.z = BuildOrientationFromYaw(effect->rotation.z + effect->angularVelocity);
    effect->velocity.y -= lbl_806D57B8;
    if (!effect->kart) {
        Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->velocity);
    } else {
        SpinVec root;
        Vec3_Add_DestFirst(&effect->offset, &effect->offset, &effect->velocity);
        Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(effect->kart));
        Vec3_Add_DestFirst(&effect->position, &root, &effect->offset);
    }
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->rotation.z);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (effect->timers[0]) --effect->timers[0];
    if (effect->timers[1]) --effect->timers[1];
    if (effect->timers[2]) --effect->timers[2];
    if (effect->timers[3]) --effect->timers[3];
}
}
