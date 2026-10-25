#ifndef GAME_DRAWEFFECTACCESS_H
#define GAME_DRAWEFFECTACCESS_H

/* Byte-offset accessors for DrawEffect pool entries (see DrawEffectPool.h)
 * and the VfxSlot / Vec3 helpers their per-frame callbacks call. */
typedef struct Vec { float x, y, z; } Vec;

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define U32(o) (*(unsigned int *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define V(o) ((Vec *)(self + (o)))
#define V_(e, o) ((Vec *)((e) + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define U8(o) (*(unsigned char *)(self + (o)))
#define SLOT(e) ((e) + 0x14)
#define STATE S8(0xB4)
#define FINISHED S8(0xC9)

extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void DrawEffect_Free(void *e);
extern void VfxSlot_BindResource(void *slot, int res);
extern void VfxSlot_BindResourceEx(void *slot, unsigned int res, int flags);
extern void VfxSlot_SetMatrixSourceEnabled(void *slot, int enabled);
extern void VfxSlot_SetPositionFromVec(void *slot, const Vec *pos);
extern void VfxSlot_SetRotationZ(void *slot, float angle);
extern void VfxSlot_SetRotationXYZFromVec(void *slot, const Vec *rot);
extern void VfxSlot_SetRotationXYZ(void *slot, float x, float y, float z);
extern float BuildOrientationFromYaw(float yaw);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void VfxSlot_SetScaleUniform(void *slot, float scale);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void Vec3_Add_DestFirst(Vec *dst, const Vec *a, const Vec *b);
extern void Vec3_Subtract_DestFirst(Vec *dst, const Vec *a, const Vec *b);
extern float Vec3_Magnitude_Wrapper(const Vec *v);
extern void Vec3_Scale(Vec *dst, const Vec *src, float scale);
extern float Rand_RangeFloat(float lo, float hi);
extern void Vec2_RotateX(Vec *out, const Vec *in, float angle);
extern void Vec2_RotateY(Vec *out, const Vec *in, float angle);
extern void Vec2_RotateZ(Vec *out, const Vec *in, float angle);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern void *KartDriver_GetJointByIdx(void *driver, int idx);

static inline void DrawEffect_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

#define TICK_TIMERS()                                       \
    do {                                                    \
        DrawEffect_TickTimer((unsigned int *)(self + 0x180)); \
        DrawEffect_TickTimer((unsigned int *)(self + 0x184)); \
        DrawEffect_TickTimer((unsigned int *)(self + 0x188)); \
        DrawEffect_TickTimer((unsigned int *)(self + 0x18C)); \
    } while (0)

#endif
