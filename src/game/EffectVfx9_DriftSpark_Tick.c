/* EffectVfx9_DriftSpark_Tick (0x800BDD74): drift spark flare (resource 9)
 * at a rear wheel joint on the outer side of the slide. It pulses with a
 * sine over its short life and is aimed outward from the kart. */
#include "game/DrawEffectAccess.h"

extern int g_kartVariant;
extern int g_gameMode;
extern int g_cupId;
extern const float lbl_806D5348; /* pi */
extern const float lbl_806D5354; /* 30 degrees in radians */
extern const Vec lbl_8032A348;
extern unsigned char *PcbSlot_GetByIndex(int pcbIdx);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern float KartCharacterParam_GetBoostFxSizeFactor(void *driver);
extern void VfxSlot_SetScaleVec3(void *slot, float x, float y, float z);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern float Vec3_ToPitch(const Vec *v);
extern float Vec3_ToYaw(const Vec *v);
extern double sin(double x);

static inline int DriftSpark_GetCharacter(unsigned char *driver)
{
    int slot;
    int character;

    if (driver == 0) {
        return -1;
    }
    slot = *(int *)(driver + 0x1F4);
    if (slot < 0 || slot > 3) {
        return -1;
    }
    if (g_gameMode == 2) {
        if (((unsigned int)PcbSlot_GetByIndex(slot)[6] >> 1 & 3) < 2) {
            return -1;
        }
    } else {
        if (g_kartVariant < 2) {
            return -1;
        }
        if (g_cupId >= 9) {
            return -1;
        }
    }
    character = *(int *)(driver + 0x1F8);
    if (character < 0 || character >= 15) {
        return -1;
    }
    return character;
}

void EffectVfx9_DriftSpark_Tick(unsigned char *self)
{
    float root[4][4];
    Vec slide;
    Vec trans;
    Vec joint;
    Vec pos;
    Vec dir;
    Vec rot;
    Vec c1;
    Vec c2;
    Vec c3;
    Vec c4;
    float sx;
    float yaw;
    float size;

    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 9);
        Vec2_RotateY(&slide, V(0xA4), -Mtx44_GetYawOfPosZ(root));
        if (slide.x < 0.0f) {
            S8(0x190) = 1;
        } else {
            S8(0x190) = 0;
        }
        if (DriftSpark_GetCharacter(P(0x11C)) >= 0) {
            F(0x30) = lbl_8032A348.x;
            F(0x34) = lbl_8032A348.y;
            F(0x38) = lbl_8032A348.z;
        }
        F(0x150) = 0.0f;
        F(0x154) = 0.5f * F(0xB0) + 0.5f;
        STATE++;
    case 1:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
    F(0x150) += 0.1f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }

    F(0xB0) = 0.4f * KartCharacterParam_GetBoostFxSizeFactor(P(0x11C));
    sx = F(0xB0);
    {
        float s = sin(lbl_806D5348 * F(0x150));
        float sy = F(0x154) * (4.0f * (F(0xB0) * ((1.0f + s) / 2.0f)));
        if (I(0x10) != 0) {
            sy *= 0.5f;
        }
        VfxSlot_SetScaleVec3(SLOT(self), sx, sy, F(0xB0));
    }
    yaw = 0.017453292f * (45.0f * F(0x150) + 135.0f);
    if (S8(0x190)) {
        yaw *= -1.0f;
    }
    size = 2.2f * KartCharacterParam_GetBoostFxSizeFactor(P(0x11C));
    Mtx44_GetTranslation_ColMajor(&trans, root);
    if (!S8(0x190)) {
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), 6));
    } else {
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), 7));
    }
    GetSpawnPosition(&pos, 0.0f, 0.0f, 1.5f * size);
    Vec2_RotateY(&pos, &pos, yaw);
    c1 = pos;
    Mtx44_TransformVec3(&pos, root, &c1);
    Vec3_Subtract_DestFirst(&pos, &pos, &trans);
    Vec3_Add_DestFirst(&pos, &pos, &joint);
    GetSpawnPosition(&dir, 0.0f, 0.0f, 1.0f);
    Vec2_RotateX(&dir, &dir, lbl_806D5354);
    Vec2_RotateY(&dir, &dir, yaw);
    c2 = dir;
    Mtx44_TransformVec3(&dir, root, &c2);
    Vec3_Subtract_DestFirst(&dir, &dir, &trans);
    rot.x = Vec3_ToPitch(&dir);
    rot.y = Vec3_ToYaw(&dir);
    rot.z = 0.0f;
    Vec3_Copy(V(0x8C), &pos);
    Vec3_Copy(V(0x98), &rot);
    c3 = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &c3);
    c4 = *V(0x98);
    VfxSlot_SetRotationXYZFromVec(SLOT(self), &c4);
    F(0x2C) = 1.0f;
    TICK_TIMERS();
}
