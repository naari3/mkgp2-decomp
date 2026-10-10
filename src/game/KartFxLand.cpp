/* Land puff family: local views cover only fields used by these callbacks.
 * Matrix helpers expose the observed writable-result ABI. Transform's Vec3
 * input remains by value, so the compiler owns its caller-side copy.
 * Exception tables are emitted natively by C++ (-Cpp_exceptions on).
 */
struct LandVec3 { float x, y, z; };
struct LandEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float lifetime;
    LandVec3 spawn;
    unsigned char pad3c[0x50];
    LandVec3 position;
    unsigned char pad98[8];
    float rotation;
    LandVec3 velocity;
    float scale;
    signed char state;
    unsigned char padb5[0x67];
    void *kart;
    LandVec3 offset;
    unsigned char pad12c[0x24];
    float growth, stretch;
    unsigned char pad158[0x28];
    unsigned int delay, timer1, timer2, timer3;
    signed char count;
};
extern "C" {
extern const float lbl_806D51C0, lbl_806D51CC, lbl_806D51D4, lbl_806D51D8;
extern const float lbl_806D51DC, lbl_806D51E8, lbl_806D51F8, lbl_806D5208;
extern const float lbl_806D521C, lbl_806D5220, lbl_806D5224, lbl_806D5228;
extern const float lbl_806D525C, lbl_806D5260, lbl_806D5270, lbl_806D5284;
extern const float lbl_806D52B4, lbl_806D52CC, lbl_806D52D0;
void VfxSlot_BindResourceEx(void *, int, int);
void GetSpawnPosition(LandVec3 *, float, float, float);
float Rand_RangeFloat(float, float);
int Rand_RangeIntMax(int);
const float *KartDriver_GetKartRootMtx(void *);
void Mtx_TransposeToMtx44(float *, const float *);
void Mtx44_TransformVec3(LandVec3 *, const float *, LandVec3);
void Mtx44_GetTranslation_ColMajor(LandVec3 *, const float *);
void Mtx44_GetTranslation_RowMajor(LandVec3 *, const float *);
void Vec3_Subtract_DestFirst(LandVec3 *, const LandVec3 *, const LandVec3 *);
void Vec3_Add_DestFirst(LandVec3 *, const LandVec3 *, const LandVec3 *);
void Vec3_Copy(LandVec3 *, const LandVec3 *);
void Vec2_RotateX(LandVec3 *, const LandVec3 *, float);
void Vec2_RotateY(LandVec3 *, const LandVec3 *, float);
void VfxSlot_SetPositionFromVec(void *, LandVec3);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void DrawEffect_Free(LandEffect *);
LandEffect *DrawEffect_SpawnDirect(void (*)(LandEffect *));

void KartFx_JumpLandPuffPieceTick(LandEffect *effect) {
    float matrix[16];
    LandVec3 root, translation;
    switch (effect->state) {
    case 0: {
        VfxSlot_BindResourceEx(effect->slot, 0x6D, 0);
        GetSpawnPosition(&effect->spawn, lbl_806D51E8, lbl_806D51E8, lbl_806D51E8);
        effect->rotation = lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D5224);
        Mtx_TransposeToMtx44(matrix, KartDriver_GetKartRootMtx(effect->kart));
        Mtx44_TransformVec3(&effect->position, matrix, effect->offset);
        Mtx44_GetTranslation_ColMajor(&translation, matrix);
        Vec3_Subtract_DestFirst(&effect->offset, &effect->position, &translation);
        GetSpawnPosition(&effect->velocity, lbl_806D51C0, lbl_806D51E8, lbl_806D51C0);
        effect->growth = lbl_806D51D4;
        effect->stretch = Rand_RangeFloat(lbl_806D5208, lbl_806D5228);
        effect->lifetime = lbl_806D51F8;
        effect->delay = 10;
        ++effect->state;
        break;
    }
    case 1: break;
    }
    if (effect->delay == 0) {
        float minimum = 0.0f;
        effect->lifetime -= lbl_806D52CC;
        if (effect->lifetime <= minimum) {
            DrawEffect_Free(effect);
            return;
        }
    }
    Vec3_Add_DestFirst(&effect->offset, &effect->offset, &effect->velocity);
    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(effect->kart));
    Vec3_Add_DestFirst(&effect->position, &root, &effect->offset);
    if (effect->delay) effect->growth += lbl_806D51D8;
    else effect->growth -= lbl_806D5284;
    effect->scale = effect->growth * effect->stretch;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->rotation);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (effect->delay) --effect->delay;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
}

void KartFx_JumpLandPuffTick(LandEffect *effect) {
    switch (effect->state) {
    case 0:
        GetSpawnPosition(&effect->offset, lbl_806D51C0, lbl_806D51CC, lbl_806D5270);
        Vec2_RotateX(&effect->offset, &effect->offset,
            lbl_806D521C * Rand_RangeFloat(lbl_806D52D0, lbl_806D51C0));
        if (Rand_RangeIntMax(16) % 2) {
            Vec2_RotateY(&effect->offset, &effect->offset,
                lbl_806D521C * (lbl_806D5224 + Rand_RangeFloat(lbl_806D525C, lbl_806D52B4)));
        } else {
            Vec2_RotateY(&effect->offset, &effect->offset,
                lbl_806D521C * (lbl_806D5224 + Rand_RangeFloat(lbl_806D51DC, lbl_806D5260)));
        }
        effect->delay = 0;
        effect->count = 0;
        ++effect->state;
    case 1:
        if (effect->delay == 0) {
            LandEffect *child = DrawEffect_SpawnDirect(KartFx_JumpLandPuffPieceTick);
            if (child) {
                Vec3_Copy(&child->offset, &effect->offset);
                child->kart = effect->kart;
            }
            ++effect->count;
            if (effect->count >= 5) {
                DrawEffect_Free(effect);
                return;
            }
            effect->delay = 3;
        }
        break;
    }
    if (effect->delay) --effect->delay;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
}
}
