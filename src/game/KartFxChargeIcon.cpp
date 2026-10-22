/* Charge icon: local views describe only fields observed in this callback. */
struct ChargeVec3 { float x, y, z; };
struct ChargeKart { unsigned char pad00[0x1F8]; unsigned int identity; };
struct ChargeEffect {
    unsigned char pad00[0x14];
    unsigned char slot[10];
    unsigned char animation;
    unsigned char pad1f[9];
    unsigned char visible;
    unsigned char pad29[0x1F];
    float matrix[12];
    unsigned char pad78[0x14];
    ChargeVec3 position;
    unsigned char pad98[0x18];
    float scale;
    signed char state;
    unsigned char padb5[0x67];
    ChargeKart *kart;
    ChargeVec3 offset, size;
    unsigned char pad138[0x58];
    signed char identity;
};
struct ChargePlacement { ChargeVec3 offset, scale; };
extern "C" {
extern const ChargePlacement lbl_8032A4A8[11];
extern const float lbl_806D51C0, lbl_806D51C4;
void VfxSlot_BindResourceEx(void *, int, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
void VfxSlot_SetAnimFrame(void *, float);
void VfxSlot_SetAnimSpeed(void *, float);
void Vec3_Copy(ChargeVec3 *, const ChargeVec3 *);
unsigned char FinalLapCoinJump_CheckActiveForObject(ChargeKart *);
void DrawEffect_Free(ChargeEffect *);
const float *KartDriver_GetKartRootMtx(ChargeKart *);
void Mtx_TransposeToMtx44(float *, const float *);
void Matrix4_Identity(float *);
void Matrix4_PreMultiplyTranslation(float *, const float *, float, float, float);
void Mtx44_Scale_PerAxis(float *, const float *, float, float, float);
void Matrix4_Multiply(float *, const float *, const float *);
void DbgScene_CopyMatrix3x4Transpose(float *, const float *);
void Mtx44_GetTranslation_RowMajor(ChargeVec3 *, const float *);

void KartFx_BoostChargeIconTick(ChargeEffect *effect) {
    float base[16], local[16];
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x0E, 0);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        VfxSlot_SetAnimFrame(effect->slot, lbl_806D51C0);
        VfxSlot_SetAnimSpeed(effect->slot, lbl_806D51C4);
        effect->scale = lbl_806D51C4;
        switch (effect->kart->identity) {
        case 0: effect->identity = 0; break;
        case 1: effect->identity = 1; break;
        case 2: effect->identity = 2; break;
        case 3: effect->identity = 3; break;
        case 4: effect->identity = 4; break;
        case 5: effect->identity = 5; break;
        case 6: effect->identity = 6; break;
        case 7: effect->identity = 7; break;
        case 8: effect->identity = 8; break;
        case 9: effect->identity = 9; break;
        case 10: effect->identity = 10; break;
        }
        Vec3_Copy(&effect->offset, &lbl_8032A4A8[effect->identity].offset);
        Vec3_Copy(&effect->size, &lbl_8032A4A8[effect->identity].scale);
        ++effect->state;
        break;
    case 1: break;
    }
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    if ((int)effect->animation == 1) {
        DrawEffect_Free(effect);
        return;
    }
    Mtx_TransposeToMtx44(base, KartDriver_GetKartRootMtx(effect->kart));
    Matrix4_Identity(local);
    Matrix4_PreMultiplyTranslation(local, local, effect->offset.x, effect->offset.y, effect->offset.z);
    Matrix4_Multiply(base, local, base);
    Matrix4_Identity(local);
    Mtx44_Scale_PerAxis(local, local, effect->size.x, effect->size.y, effect->size.z);
    Matrix4_Multiply(base, local, base);
    DbgScene_CopyMatrix3x4Transpose(effect->matrix, base);
    Mtx44_GetTranslation_RowMajor(&effect->position, effect->matrix);
}
}
