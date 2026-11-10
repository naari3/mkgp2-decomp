/* KartDriver_BuildJoint12EulerTransform (0x800D68D4): build the world matrix
 * of an attachment from driver joint 12: rotate by an Euler triple (Y, Z, X),
 * translate by an offset scaled by 1/KartFxParam_GetConst1p5, compose with the
 * joint matrix, then apply a uniform scale. */

#include "game/types/Vec.h"

extern float KartFxParam_GetConst1p5(void *driver);
extern void KartDriver_GetJointMatrix4x3(void *driver, int joint, float m[4][4]);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern void Vec3_Scale(Vec *dst, const Vec *src, float scale);
#ifdef __MWERKS__
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec *);
static inline void Mtx44_Translate_ByValue(float dst[4][4], float src[4][4], Vec t) { Mtx44_Translate(dst, src, &t); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float dst[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void PSMTXScale(float m[3][4], float x, float y, float z);
extern void PSMTXConcat(float a[3][4], float b[3][4], float ab[3][4]);

void KartDriver_BuildJoint12EulerTransform(unsigned char *obj, void *driver, const Vec *offset,
                                           const Vec *euler, float scale)
{
    float joint[4][4];
    float m[4][4];
    Vec t;

    scale = scale / KartFxParam_GetConst1p5(driver);
    KartDriver_GetJointMatrix4x3(driver, 12, joint);
    Matrix4_Identity(m);
    Matrix4_PreMultiplyRotY(m, m, euler->y);
    Matrix4_PreMultiplyRotZ(m, m, euler->z);
    Matrix4_PreMultiplyRotX(m, m, euler->x);
    Vec3_Scale(&t, offset, scale);
    Mtx44_Translate(m, m, t);
    Matrix4_Multiply(joint, m, joint);
    DbgScene_CopyMatrix3x4Transpose(obj + 0x34, joint);
    PSMTXScale((float (*)[4])m, scale, scale, scale);
    PSMTXConcat((float (*)[4])(obj + 0x34), (float (*)[4])m, (float (*)[4])(obj + 0x34));
}
