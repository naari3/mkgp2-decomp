/* ItemObject_Tick_Kind2426_FastDrop (0x800E10E8): DrawEffect tick for the
 * fast-dropping item kinds 0x24/0x26. Falls with decaying speed, follows the
 * owner kart's root matrix, and drops an orbit spark every 5 frames. */
#include "game/DrawEffectAccess.h"

typedef struct FastDropWork {
    unsigned char pad0[4];
    unsigned int life;
    unsigned int sparkTimer;
    unsigned char pad0C[8];
    float speed;
    unsigned char pad18[0x1C];
    Vec offset;
    unsigned char pad40[0x58];
    void *driver;
} FastDropWork;

extern const float lbl_806D5BB4; /* 0.1 */
extern const float lbl_806D5BD4; /* 2.0 */
extern const float lbl_806D5C10; /* 20 deg */
extern const float lbl_806D5C14; /* 0.5 */
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
extern void Effect_KartOrbitSpark_Update(unsigned char *self);

void ItemObject_Tick_Kind2426_FastDrop(unsigned char *self, FastDropWork *work)
{
    float m[4][4];
    unsigned char *spark;

    switch (FINISHED) {
    case 0:
        work->speed = lbl_806D5BD4;
        work->life = 0x14;
        work->sparkTimer = 0;
        FINISHED++;
    case 1:
        break;
    }

    if (work->life == 0) {
        F(0x2C) -= lbl_806D5BB4;
        if (F(0x2C) < 0.0f) {
            U8(0x28) = 0;
            U8(0xC8) = 3;
            U8(0xC9) = 0;
            return;
        }
    }

    work->speed -= lbl_806D5C14;
    if (work->speed < 0.0f) {
        work->speed = 0.0f;
    }
    work->offset.y += work->speed;
    F(0xB0) = BuildOrientationFromYaw(lbl_806D5C10 + F(0xB0));

    if (work->driver != 0) {
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(work->driver));
        Mtx44_TransformVec3(V(0xA0), m, work->offset);
    }

    if (FinalLapCoinJump_CheckActiveForObject(work->driver)) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }

    if (work->sparkTimer == 0) {
        spark = DrawEffect_SpawnDirect(Effect_KartOrbitSpark_Update);
        if (spark != 0) {
            Vec3_Copy(V_(spark, 0x8C), V(0xA0));
            *(void **)(spark + 0x11C) = work->driver;
        }
        work->sparkTimer = 5;
    }
}
