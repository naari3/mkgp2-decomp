/* ItemObject_Tick_Kind28_BananaTrioSpawner (0x800E0B10): the triple-banana
 * spawner swings its offset around the kart; after half a turn it spawns
 * the three child bananas, and it retires itself after a full turn. The
 * offset radius and height blend toward kart-scaled targets as it turns. */
#include "game/DrawEffectAccess.h"

typedef struct BananaTrioWork {
    unsigned char pad0[0x14];
    float angle;
    float angleStart;
    unsigned char pad1C[0x34 - 0x1C];
    Vec offset;
    unsigned char pad40[0x98 - 0x40];
    void *kart;
} BananaTrioWork;

extern const float lbl_806D5BB0; /* 0.0 */
extern const float lbl_806D5BB8; /* 1.0 */
extern const float lbl_806D5BC8; /* pi */
extern const float lbl_806D5BE0; /* 3.0 */
extern const float lbl_806D5BE4; /* 5.0 */
extern const float lbl_806D5BF4; /* 2pi */
extern const float lbl_806D5BF8; /* 2pi/30 */
extern float Vec3_ToYaw(const Vec *v);
extern void SoundMgr_PlaySE_Positional(int id, Vec pos, int flags);
extern unsigned char *ItemObject_AllocFromPool(void (*tick)(void));
extern void ItemObject_Tick_Kind28_BananaTrioChild(void);
extern float KartFxParam_GetConst1p5(void *kart);
extern float Vec3_HorizontalMagnitude(const Vec *v);
extern void Vec3_ScaleXZ(Vec *out, const Vec *in, float s);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec v);
extern float Mtx44_GetYawOfPosZ_Padded(void *mtx);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);

void ItemObject_Tick_Kind28_BananaTrioSpawner(unsigned char *self, BananaTrioWork *w)
{
    float len;
    float u;
    float t;
    float radius;

    switch (S8(0xC9)) {
    default:
        break;
    case 0:
        w->angle = lbl_806D5BF4 - Vec3_ToYaw(&w->offset);
        w->angleStart = w->angle;
        SoundMgr_PlaySE_Positional(0xC3, *V(0xA0), 0);
        S8(0xC9)++;
    case 1:
        if (w->angle < lbl_806D5BC8) {
            int i;
            for (i = 0; i < 3; i++) {
                unsigned char *child = ItemObject_AllocFromPool(ItemObject_Tick_Kind28_BananaTrioChild);
                if (child != 0) {
                    *(unsigned int *)(child + 0x10) = (unsigned char)i;
                    *(void **)(child + 0x184) = w->kart;
                }
            }
            S8(0xC9)++;
        }
        break;
    }

    Vec2_RotateY(&w->offset, &w->offset, lbl_806D5BF8);
    w->angle -= lbl_806D5BF8;
    if (w->angle < lbl_806D5BB0) {
        U8(0x28) = 0;
        S8(0xC8) = 3;
        S8(0xC9) = 0;
        return;
    }
    F(0x2C) = w->angle / lbl_806D5BC8;
    if (F(0x2C) < lbl_806D5BB0) {
        F(0x2C) = lbl_806D5BB0;
    }
    {
        float span = w->angleStart - lbl_806D5BC8;
        t = (span - (w->angle - lbl_806D5BC8)) / span;
    }
    if (lbl_806D5BB8 < t) {
        t = lbl_806D5BB8;
    }
    {
        radius = lbl_806D5BE4 * KartFxParam_GetConst1p5(w->kart);
        len = Vec3_HorizontalMagnitude(&w->offset);
        Vec3_ScaleXZ(&w->offset, &w->offset, lbl_806D5BB8 / len);
        u = lbl_806D5BB8 - t;
        Vec3_ScaleXZ(&w->offset, &w->offset, radius * t + len * u);
        radius = lbl_806D5BE0 * KartFxParam_GetConst1p5(w->kart);
        w->offset.y = radius * t + w->offset.y * u;
    }
    if (w->kart != 0) {
        float m[4][4];
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(w->kart));
        Mtx44_TransformVec3(V(0xA0), m, w->offset);
    }
    if (w->kart != 0) {
        F(0xB0) = BuildOrientationFromYaw(lbl_806D5BC8 + Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(w->kart)));
    }
    if (FinalLapCoinJump_CheckActiveForObject(w->kart)) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
