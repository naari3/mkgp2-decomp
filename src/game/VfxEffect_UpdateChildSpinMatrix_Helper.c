#include "game/DrawEffectAccess.h"

extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float angle);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float scale);
extern void Mtx44_GetTranslation_ColMajor(Vec *dst, float src[4][4]);
extern double sin(double angle);

void VfxEffect_UpdateChildSpinMatrix_Helper(unsigned char *self, const void *matrix)
{
    float world[4][4];
    float spin[4][4];
    float pulse;

    if (self != 0) {
        F(0xA0) = BuildOrientationFromYaw(0.17453289031982422f + F(0xA0));
        F(0x150) = BuildOrientationFromYaw(0.5235986709594727f + F(0x150));
        pulse = (float)sin(F(0x150));
        Mtx_TransposeToMtx44(world, matrix);
        Matrix4_Identity(spin);
        Matrix4_PreMultiplyTranslation(spin, spin, 0.0f, 0.0f, -3.2f);
        Matrix4_PreMultiplyRotZ(spin, spin, F(0xA0));
        Mtx44_Scale_Uniform(spin, spin, 0.05f * pulse + 1.0f);
        Matrix4_Multiply(world, spin, world);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, world);
        Mtx44_GetTranslation_ColMajor(V(0x8C), world);
        U8(0x28) = 1;
    }
}
