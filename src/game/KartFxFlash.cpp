/* Flash orbit callback. Fields are a local view of the effect ABI.
 * TransformVec3 writes its result explicitly and consumes a by-value Vec3;
 * the compiler therefore owns the input copy and emits native exception data.
 */
struct FlashVec3 { float x, y, z; };
struct FlashCamera { float matrix[16]; unsigned char pad40[0x40]; FlashVec3 position; };
struct FlashEffect {
    unsigned char pad00[0x10];
    int identity;
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float opacity;
    unsigned char pad30[0x5C];
    FlashVec3 position;
    unsigned char pad98[0x18];
    float scale;
    signed char state;
    unsigned char padB5[0x67];
    void *kart;
    FlashVec3 offset;
    unsigned char pad12C[0x24];
    float phase;
};
extern "C" {
extern const float lbl_8032A5B0[43];
extern FlashCamera lbl_805DF3D0;
extern const float lbl_806D51BC, lbl_806D51C0, lbl_806D51C4, lbl_806D51C8;
extern const float lbl_806D51D0, lbl_806D51EC, lbl_806D5230, lbl_806D5244, lbl_806D5248;
extern const float lbl_806D52D4, lbl_806D52D8, lbl_806D52DC, lbl_806D52F8, lbl_806D52FC, lbl_806D5300;
extern const double lbl_806D52E0, lbl_806D52E8, lbl_806D52F0;
void VfxSlot_BindResourceEx(void *, unsigned char, int);
float Rand_RangeFloat(float, float);
void DrawEffect_Free(FlashEffect *);
float KartCharacterParam_GetFxSizeFactor(void *);
void VfxSlot_SetScaleVec3(void *, float, float);
const float *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(FlashVec3 *, const float *);
void Vec3_Subtract_DestFirst(FlashVec3 *, const FlashVec3 *, const FlashVec3 *);
float Vec3_Magnitude_Wrapper(const FlashVec3 *);
void Vec3_Scale(FlashVec3 *, const FlashVec3 *, float);
void Vec3_Add_DestFirst(FlashVec3 *, const FlashVec3 *, const FlashVec3 *);
void Mtx44_TransformVec3(FlashVec3 *, const float *, FlashVec3);
void VfxSlot_SetPositionFromVec(void *, FlashVec3);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);

void KartFx_FlashOrbitTick(FlashEffect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x4C, 0);
        effect->phase = lbl_806D51C0;
        effect->offset.x = lbl_806D51BC * lbl_8032A5B0[effect->identity]
            + Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
        effect->offset.y = Rand_RangeFloat(lbl_806D5230, lbl_806D51C4) - lbl_806D51D0;
        effect->offset.z = lbl_806D51C8 * Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
        ++effect->state;
        break;
    case 1: break;
    }
    effect->phase += lbl_806D52D4;
    if (lbl_806D51C4 < effect->phase) {
        DrawEffect_Free(effect);
        return;
    }
    effect->offset.y += lbl_806D52D8;
    if (effect->phase < lbl_806D52DC)
        effect->opacity = effect->phase / lbl_806D52E0;
    else
        effect->opacity = lbl_806D52E8 - (effect->phase - lbl_806D52E0) / lbl_806D52F0;
    effect->opacity *= lbl_806D51EC;
    effect->scale = KartCharacterParam_GetFxSizeFactor(effect->kart);
    VfxSlot_SetScaleVec3(effect->slot,
        effect->scale * (lbl_806D51BC * (lbl_806D5244 * effect->phase + lbl_806D52DC)),
        effect->scale * (lbl_806D5248 * (lbl_806D52FC * effect->phase + lbl_806D52F8)));
    Mtx44_GetTranslation_RowMajor(&effect->position, KartDriver_GetKartRootMtx(effect->kart));
    FlashVec3 displacement;
    FlashVec3 *camera = &lbl_805DF3D0.position;
    Vec3_Subtract_DestFirst(&displacement, &effect->position, camera);
    Vec3_Scale(&displacement, &displacement,
        effect->scale * (lbl_806D5300 * (lbl_806D51C4 / Vec3_Magnitude_Wrapper(&displacement))));
    Vec3_Add_DestFirst(&effect->position, &effect->position, &displacement);
    Vec3_Scale(&displacement, &effect->offset, effect->scale);
    Mtx44_TransformVec3(&displacement, lbl_805DF3D0.matrix, displacement);
    Vec3_Subtract_DestFirst(&displacement, &displacement, camera);
    Vec3_Add_DestFirst(&effect->position, &effect->position, &displacement);
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
}
}
