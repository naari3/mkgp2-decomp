#include "game/DrawEffectAccess.h"

extern const float lbl_806D555C; /* 0.0 */
extern const float lbl_806D5624; /* 0.0001 */

typedef struct TrailWork {
    unsigned char pad00[0x10];
    unsigned char *children[2];  /* 0x0DC */
} TrailWork;

extern unsigned char lbl_805DF3D0[];
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], float src[4][4]);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec v);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern double atan2(float y, float x);
extern float BuildOrientationFromYaw(float yaw);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float angle);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void Mtx_Copy(void *dst, const void *src);

void DrawEffect_KartItemTrail_ExplodeAndPropagate(unsigned char *self, const void *mtx, float alpha)
{
    float m[4][4];
    float inv[4][4];
    Vec local;
    TrailWork *work;
    int i;

    if (self != 0) {
        Mtx_TransposeToMtx44(m, mtx);
        Mtx44_Inverse_GaussJordan(inv, m);
        Mtx44_TransformVec3(&local, inv, *(Vec *)(lbl_805DF3D0 + 0x80));
        Matrix4_Identity(inv);
        Matrix4_PreMultiplyTranslation(inv, inv, lbl_806D555C, lbl_806D555C, lbl_806D5624);
        Matrix4_PreMultiplyRotY(inv, inv, BuildOrientationFromYaw(atan2(local.x, local.z)));
        Matrix4_Multiply(m, inv, m);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
        F(0x2C) = alpha;
        work = (TrailWork *)(self + 0xCC);
        for (i = 0; i < 2; i++) {
            if (work->children[i] != 0) {
                Mtx_Copy(work->children[i] + 0x48, self + 0x48);
                Vec3_Copy((Vec *)(work->children[i] + 0x8C), V(0x8C));
                *(float *)(work->children[i] + 0x2C) = F(0x2C);
                work->children[i][0x28] = 1;
            }
        }
    }
}
