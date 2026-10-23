/* Kart-relative orbit spark. Views describe target-observed offsets only. */
struct OrbitSparkVec3 { float x, y, z; };
struct OrbitSparkEffect {
    char pad00[0x14];
    char slot[0x14];
    unsigned char visible;
    char pad29[0x63];
    OrbitSparkVec3 position;
    char pad98[0x18];
    float scale;
    signed char state;
    char padB5[0x67];
    void *kart;
    OrbitSparkVec3 offset;
    char pad12C[0x24];
    float amplitude;
    float angle;
};
extern "C" {
extern const float lbl_806D54A8, lbl_806D54AC, lbl_806D54E8;
extern const float lbl_806D5520, lbl_806D54E0, lbl_806D54BC;
extern const float lbl_806D5524, lbl_806D5528, lbl_806D54B8;
extern const float lbl_806D54C0, lbl_806D5510;
void VfxSlot_BindResourceEx(void *, int, int);
float Rand_RangeFloat(float, float);
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(OrbitSparkVec3 *, const void *);
void Vec3_Subtract_DestFirst(OrbitSparkVec3 *, const OrbitSparkVec3 *, const OrbitSparkVec3 *);
void Vec3_Add_DestFirst(OrbitSparkVec3 *, const OrbitSparkVec3 *, const OrbitSparkVec3 *);
void Vec3_Copy(OrbitSparkVec3 *, const OrbitSparkVec3 *);
float BuildOrientationFromYaw(float);
double fn_8027E9E8(double);
void DrawEffect_Free(OrbitSparkEffect *);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void VfxSlot_SetPositionFromVec(void *, OrbitSparkVec3);
void VfxSlot_SetScaleUniform(void *, float);

void Effect_KartOrbitSpark_Update(OrbitSparkEffect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x7f, 0);
        effect->amplitude = Rand_RangeFloat(lbl_806D54A8, lbl_806D54AC);
        effect->angle = lbl_806D54E8;
        effect->position.x += Rand_RangeFloat(lbl_806D5520, lbl_806D54E0);
        effect->position.y += Rand_RangeFloat(lbl_806D54BC, lbl_806D54E0);
        effect->position.z += Rand_RangeFloat(lbl_806D5520, lbl_806D54E0);
        if (effect->kart) {
            OrbitSparkVec3 translation;
            Mtx44_GetTranslation_RowMajor(&translation, KartDriver_GetKartRootMtx(effect->kart));
            Vec3_Subtract_DestFirst(&effect->offset, &effect->position, &translation);
        } else {
            Vec3_Copy(&effect->offset, &effect->position);
        }
        effect->amplitude = Rand_RangeFloat(lbl_806D54A8, lbl_806D54AC);
        effect->angle = lbl_806D54E8;
        ++effect->state;
    case 1:
    {
        effect->offset.y -= lbl_806D5524;
        effect->angle = BuildOrientationFromYaw(lbl_806D5528 + effect->angle);
        float wave = (float)fn_8027E9E8(effect->angle);
        float pulse = ((lbl_806D54B8 + wave) * lbl_806D54C0) * lbl_806D54C0 + lbl_806D54C0;
        effect->scale = effect->amplitude * pulse;
        if (effect->kart) {
            OrbitSparkVec3 translation;
            Mtx44_GetTranslation_RowMajor(&translation, KartDriver_GetKartRootMtx(effect->kart));
            Vec3_Add_DestFirst(&effect->position, &translation, &effect->offset);
        } else {
            Vec3_Copy(&effect->position, &effect->offset);
        }
        effect->amplitude -= lbl_806D5510;
        if (effect->amplitude < lbl_806D54E8) {
            DrawEffect_Free(effect);
            return;
        }
        break;
    }
    }
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
}
}
