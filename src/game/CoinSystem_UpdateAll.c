/* CoinSystem_UpdateAll (0x80139898): per-frame update of the course coins.
 * First every kart in a valid slot picks up the idle coins (state 2) it is
 * close enough to; then each coin runs its state machine:
 *   0 respawn wait, 1 rise, 2 idle spin, 3 collected (sparkle + count),
 *   4 gone, 5/8 drop delay, 6/9 drop flight, 7/10 homing to the kart. */

#include "game/types/Vec.h"

typedef float Mtx[3][4];

typedef struct CoinSpark {
    float life;  /* 0x0 */
    float x;     /* 0x4 */
    float y;     /* 0x8 */
    float z;     /* 0xC */
} CoinSpark;

typedef struct CoinFlags {
    unsigned char pad00[0x10];
    unsigned long long bits; /* 0x10 */
} CoinFlags;

typedef struct CoinKart {
    unsigned char pad000[0x1F4];
    int slot;              /* 0x1F4 */
    unsigned char pad1F8[0x2CC - 0x1F8];
    int coins;             /* 0x2CC */
    unsigned char human;   /* 0x2D0 */
    unsigned char pad2D1[0x304 - 0x2D1];
    CoinFlags *flags;      /* 0x304 */
} CoinKart;

typedef struct CoinStats {
    unsigned char pad00[0x18];
    int coinsGot;          /* 0x18 */
} CoinStats;

typedef struct Coin {
    int mode;              /* 0x00 */
    Vec pos;               /* 0x04 */
    CoinKart *owner;       /* 0x10 */
    int count;             /* 0x14 */
    int state;             /* 0x18 */
    float timer;           /* 0x1C */
    Vec cur;               /* 0x20 */
    float rot;             /* 0x2C */
    float spin;            /* 0x30 */
    float scale;           /* 0x34 */
    unsigned char pad38[0x70 - 0x38];
    CoinSpark sparks[5];   /* 0x70 */
} Coin;

extern Coin *lbl_806D1534;
extern int lbl_806D1538;
extern int CoinSystem_bss_806D153C;
extern int CoinSystem_bss_806D1540;
extern int CoinSystem_bss_806D1544;
extern unsigned char lbl_806D1548;
extern unsigned char g_raceEnded;
extern int lbl_80677CC8[];
extern float lbl_80495994[64];
extern float lbl_80495A94[48];

extern CoinKart *GetKartSlotKartVariant(int slot);
extern float *KartDriver_GetKartRootMtx(CoinKart *kart);
extern Vec *KartMovement_GetVelocityPtr(CoinKart *kart);
extern float KartMovement_GetVelocityMagnitude(CoinKart *kart);
extern float LUT_Sin12Bit(float deg);
extern float fn_80186960(float deg);
extern CoinStats *fn_8024F588(void);
extern void fn_801B377C(void);
extern unsigned char fn_8016C360(int se);
extern void fn_8016C394(int se);
extern void SoundMgr_PlaySE(int se);
extern void *GetCourseScene3D(void);
extern void CObj_LoadProjMatrix(void *scene, Vec *v);
extern void CObj_ApplyScissor(void *scene, Vec *v);
extern void Vec3_Subtract(Vec *a, Vec *b, Vec *dst);
extern void Vec3_Normalize(Vec *src, Vec *dst);
extern void PSMTXRotRad(Mtx m, char axis, float rad);
extern void PSMTXMultVec(Mtx m, Vec *src, Vec *dst);
extern void PSVECScale(Vec *src, Vec *dst, float scale);
extern void PSVECAdd(Vec *a, Vec *b, Vec *dst);
extern float PSVECSquareMag(Vec *v);


#define COIN_HOMING_BIT 0x400000000000ULL

/* The getter keeps the flags pointer a late temp, so the sparkle pointer in
 * case 3 reuses its saved register. */
static inline CoinFlags *CoinKart_GetFlags(CoinKart *kart)
{
    return kart->flags;
}

void CoinSystem_UpdateAll(void)
{
    float s;
    Vec d0;
    float range;
    Vec d7;
    Vec dir;
    CoinFlags *flags;
    Vec eye;
    Vec at;
    int i;
    Coin *c;
    Vec d10;
    float k;
    CoinKart *kart;
    /* a and b are reused across the loops and switch cases (range, phase,
     * homing target x/y); the saved FPRs only match with this sharing. */
    float a;
    float b;
    Mtx m;
    Coin *p;

    if (lbl_806D1538 == 0) {
        return;
    }

    for (i = 0; i < 8; i++) {
        kart = GetKartSlotKartVariant(i);
        if (kart == 0 || kart->slot < 0 || kart->slot > 3) {
            continue;
        }
        for (p = lbl_806D1534; p < lbl_806D1534 + lbl_806D1538; p++) {
            if (kart->coins >= 99) {
                break;
            }
            if (p->state != 2) {
                continue;
            }
            d0.x = KartDriver_GetKartRootMtx(kart)[3] - p->cur.x;
            d0.y = KartDriver_GetKartRootMtx(kart)[7] - p->cur.y;
            d0.z = KartDriver_GetKartRootMtx(kart)[11] - p->cur.z;
            a = 576.0f;
            flags = CoinKart_GetFlags(kart);
            if (flags->bits & COIN_HOMING_BIT) {
                a = 57600.0f;
            }
            if (PSVECSquareMag(&d0) < a) {
                p->state = 3;
                if (flags->bits & COIN_HOMING_BIT) {
                    p->state = 7;
                }
                p->owner = kart;
                p->count = -1;
                p->timer = 0.0f;
                p->scale = 0.0f;
            }
        }
    }

    if (CoinSystem_bss_806D153C != 0) {
        CoinSystem_bss_806D153C--;
    }

    for (c = lbl_806D1534; c < lbl_806D1534 + lbl_806D1538; c++) {
        switch (c->state) {
        case 0:
            if (c->timer > 0.0f) {
                c->timer -= 1.0f;
            } else if (CoinSystem_bss_806D153C == 0) {
                c->state = 1;
                c->timer = 0.0f;
                c->cur.x = c->pos.x;
                c->cur.y = c->pos.y;
                c->cur.z = c->pos.z;
                c->spin = 0.0f;
                c->scale = 0.0f;
                CoinSystem_bss_806D153C = 5;
            }
            break;
        case 1:
            a = c->timer / 30.0f;
            c->cur.x = c->pos.x;
            c->cur.y = 5.0f * a + c->pos.y;
            c->cur.z = c->pos.z;
            c->scale = a;
            if ((c->timer += 1.0f) >= 30.0f) {
                c->state = 2;
                c->timer = 0.0f;
                c->scale = 1.0f;
            }
            break;
        case 2:
            b = c->timer / 240.0f;
            c->spin += 0.2f * LUT_Sin12Bit(360.0f * b);
            if (c->spin < 6.283184f) {
                c->spin += 6.283184f;
            }
            if (c->spin >= 6.283184f) {
                c->spin -= 6.283184f;
            }
            c->cur.y = 5.0f * LUT_Sin12Bit(720.0f * b) + (5.5f + c->pos.y);
            if ((c->timer += 1.0f) >= 240.0f) {
                c->timer = 0.0f;
            }
            break;
        case 3:
            if (0.0f == c->timer) {
                if (c->mode == 2) {
                    lbl_80677CC8[c->owner->slot]++;
                    if (c->owner->human == 1 && !g_raceEnded) {
                        fn_8024F588()->coinsGot++;
                    }
                }
                c->count = c->owner->coins;
                c->owner->coins++;
                fn_801B377C();
                if (lbl_806D1548 == 1) {
                    lbl_806D1548 = 0;
                    c->mode = 2;
                }
                if (c->owner->human == 1) {
                    if (c->mode == 2) {
                        if (fn_8016C360(0x71) == 1) {
                            fn_8016C394(0x71);
                        }
                        SoundMgr_PlaySE(0x71);
                    } else {
                        if (fn_8016C360(0xAB) == 1) {
                            fn_8016C394(0xAB);
                        }
                        SoundMgr_PlaySE(0xAB);
                    }
                }
            }
            b = c->timer / 20.0f;
            c->cur.x = KartDriver_GetKartRootMtx(c->owner)[3];
            c->cur.y = 20.0f * b + (10.0f + KartDriver_GetKartRootMtx(c->owner)[7]);
            c->cur.z = KartDriver_GetKartRootMtx(c->owner)[11];
            c->scale = 1.0f - b;
            for (i = 0; i < 5; i++) {
                if (c->sparks[i].life >= 0.0f) {
                    c->sparks[i].y -= 2.0f;
                    if ((c->sparks[i].life += 1.0f) > 10.0f) {
                        c->sparks[i].life = -1.0f;
                    }
                }
            }
            if (((int)c->timer & 3) == 0) {
                for (i = 0; i < 5; i++) {
                    if (c->sparks[i].life < 0.0f) {
                        c->sparks[i].life = 0.0f;
                        c->sparks[i].x = 5.0f * LUT_Sin12Bit(360.0f * lbl_80495994[CoinSystem_bss_806D1540]);
                        c->sparks[i].y = 10.0f * lbl_80495A94[CoinSystem_bss_806D1544];
                        c->sparks[i].z = 5.0f * fn_80186960(360.0f * lbl_80495994[CoinSystem_bss_806D1540]);
                        if (++CoinSystem_bss_806D1540 >= 64) {
                            CoinSystem_bss_806D1540 = 0;
                        }
                        if (++CoinSystem_bss_806D1544 >= 48) {
                            CoinSystem_bss_806D1544 = 0;
                        }
                        break;
                    }
                }
            }
            if ((c->timer += 1.0f) >= 20.0f) {
                c->state = 4;
                c->timer = 0.0f;
                c->scale = 0.0f;
            }
            break;
        case 7:
            {
            float tz;
            if (0.0f == c->timer) {
                c->scale = 1.0f;
                c->timer = 0.1f;
                c->rot = 0.0f;
            }
            c->spin += 0.26179934f;
            if (c->spin < 6.283184f) {
                c->spin += 6.283184f;
            }
            if (c->spin >= 6.283184f) {
                c->spin -= 6.283184f;
            }
            a = KartDriver_GetKartRootMtx(c->owner)[3] + 60.0f * KartMovement_GetVelocityPtr(c->owner)->x;
            b = KartDriver_GetKartRootMtx(c->owner)[7] + 60.0f * KartMovement_GetVelocityPtr(c->owner)->y;
            tz = KartDriver_GetKartRootMtx(c->owner)[11] + 60.0f * KartMovement_GetVelocityPtr(c->owner)->z;
            k = 1.0f - c->timer / 60.0f;
            c->cur.x = a - k * (a - c->cur.x);
            c->cur.y = b - k * (b - c->cur.y);
            c->cur.z = tz - k * (tz - c->cur.z);
            d7.x = KartDriver_GetKartRootMtx(c->owner)[3] - c->cur.x;
            d7.y = KartDriver_GetKartRootMtx(c->owner)[7] - c->cur.y;
            d7.z = KartDriver_GetKartRootMtx(c->owner)[11] - c->cur.z;
            range = PSVECSquareMag(&d7);
            c->timer += 1.2f - k;
            if (c->timer < 30.0f) {
                c->cur.y += 1.5f;
            }
            c->scale -= 0.012f;
            if (range < 576.0f) {
                c->state = 3;
                c->timer = 0.0f;
                c->scale = 1.0f;
                c->rot = 0.0f;
            }
            }
            break;
        case 5:
        case 8:
            if (c->timer > 0.0f) {
                c->timer -= 1.0f;
            } else {
                c->timer = 0.0f;
                c->rot = 1.570796f * lbl_80495A94[CoinSystem_bss_806D1544] - 0.785398f;
                c->scale = 0.0f;
                c->state = (c->state == 8) ? 9 : 6;
                if (++CoinSystem_bss_806D1544 >= 48) {
                    CoinSystem_bss_806D1544 = 0;
                }
            }
            break;
        case 6:
        case 9:
            {
            float t;
            t = c->timer / 20.0f;
            c->cur.x = KartDriver_GetKartRootMtx(c->owner)[3];
            c->cur.y = KartDriver_GetKartRootMtx(c->owner)[7];
            c->cur.z = KartDriver_GetKartRootMtx(c->owner)[11];
            if (GetCourseScene3D() != 0) {
                CObj_LoadProjMatrix(GetCourseScene3D(), &eye);
                CObj_ApplyScissor(GetCourseScene3D(), &at);
                Vec3_Subtract(&eye, &at, &dir);
                Vec3_Normalize(&dir, &dir);
            } else {
                dir.x = KartDriver_GetKartRootMtx(c->owner)[2];
                dir.y = KartDriver_GetKartRootMtx(c->owner)[6];
                dir.z = KartDriver_GetKartRootMtx(c->owner)[10];
            }
            PSMTXRotRad(m, 'Y', 3.141592f + c->rot);
            PSMTXMultVec(m, &dir, &dir);
            PSVECScale(&dir, &dir, t * (50.0f * KartMovement_GetVelocityMagnitude(c->owner)));
            PSVECAdd(&c->cur, &dir, &c->cur);
            s = LUT_Sin12Bit(180.0f * t);
            dir.x = KartDriver_GetKartRootMtx(c->owner)[1];
            dir.y = KartDriver_GetKartRootMtx(c->owner)[5];
            dir.z = KartDriver_GetKartRootMtx(c->owner)[9];
            PSVECScale(&dir, &dir, 15.0f * s + 10.0f);
            PSVECAdd(&c->cur, &dir, &c->cur);
            c->spin += 0.5235987f;
            if (c->spin >= 6.283184f) {
                c->spin -= 6.283184f;
            }
            if ((c->timer += 1.0f) < 10.0f) {
                c->scale = 1.0f;
            } else {
                c->scale = s;
            }
            if (c->timer >= 20.0f) {
                c->state = 0;
                c->timer = 300.0f;
                c->owner = 0;
                c->scale = 0.0f;
            }
            }
            break;
        case 10:
            {
            float tz;
            if (0.0f == c->timer) {
                c->scale = 1.0f;
                c->timer = 0.1f;
                c->rot = 0.0f;
            }
            c->spin += 0.2f * LUT_Sin12Bit(360.0f * (c->timer / 40.0f));
            if (c->spin < 6.283184f) {
                c->spin += 6.283184f;
            }
            if (c->spin >= 6.283184f) {
                c->spin -= 6.283184f;
            }
            b = KartDriver_GetKartRootMtx(c->owner)[3] + 30.0f * KartMovement_GetVelocityPtr(c->owner)->x;
            a = KartDriver_GetKartRootMtx(c->owner)[7] + 30.0f * KartMovement_GetVelocityPtr(c->owner)->y;
            tz = KartDriver_GetKartRootMtx(c->owner)[11] + 30.0f * KartMovement_GetVelocityPtr(c->owner)->z;
            k = 1.0f - c->timer / 30.0f;
            c->cur.x = b - k * (b - c->cur.x);
            c->cur.y = a - k * (a - c->cur.y);
            c->cur.z = tz - k * (tz - c->cur.z);
            d10.x = KartDriver_GetKartRootMtx(c->owner)[3] - c->cur.x;
            d10.y = KartDriver_GetKartRootMtx(c->owner)[7] - c->cur.y;
            d10.z = KartDriver_GetKartRootMtx(c->owner)[11] - c->cur.z;
            range = PSVECSquareMag(&d10);
            c->timer += 1.2f - k;
            c->scale -= 0.012f;
            if (range < 225.0f) {
                c->state = 3;
                c->timer = 0.0f;
                c->scale = 1.0f;
                c->rot = 0.0f;
            }
            }
            break;
        }
    }
}
