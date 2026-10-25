#include "game/DrawEffectAccess.h"


extern float Mtx44_GetPitchOfPosZ_Padded(void *mtx);
extern float Mtx44_GetYawOfPosZ_Padded(void *mtx);
extern void DrawEffect_Cb_KartImpactRing_Tick(unsigned char *self);

void DrawEffect_KartImpactRing_SpawnFromVfx(unsigned char *self, void *mtx)
{
    Vec pos;
    unsigned char *e;

    if (self != 0) {
        Mtx44_GetTranslation_RowMajor(V(0x8C), mtx);
        F(0x98) = Mtx44_GetPitchOfPosZ_Padded(mtx);
        F(0x9C) = Mtx44_GetYawOfPosZ_Padded(mtx);
        F(0x150) += 0.05f;
        if (1.0f < F(0x150)) {
            F(0x150) = 1.0f;
        }
        F(0xB0) = F(0x150);
        F(0x2C) = 0.2f * F(0x150);
        pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        VfxSlot_SetRotationXYZ(SLOT(self), BuildOrientationFromYaw(3.141592f + F(0x98)), F(0x9C), 0.0f);
        VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
        U8(0x28) = 1;
        e = DrawEffect_SpawnDirect(DrawEffect_Cb_KartImpactRing_Tick);
        if (e != 0) {
            *(void **)(e + 0x11C) = P(0x11C);
            Vec3_Copy((Vec *)(e + 0x8C), V(0x8C));
            GetSpawnPosition((Vec *)(e + 0xA4), 0.0f, 0.0f,
                             0.8f * Rand_RangeFloat(0.8f, 1.2f));
            Vec2_RotateX((Vec *)(e + 0xA4), (Vec *)(e + 0xA4),
                         BuildOrientationFromYaw(0.017453289f * (10.0f * Rand_RangeFloat(-1.0f, 1.0f)) + F(0x98)));
            Vec2_RotateY((Vec *)(e + 0xA4), (Vec *)(e + 0xA4),
                         BuildOrientationFromYaw(0.017453289f * (10.0f * Rand_RangeFloat(-1.0f, 1.0f)) + F(0x9C)));
        }
    }
}
