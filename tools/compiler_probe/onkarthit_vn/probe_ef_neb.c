/* EF: dispatch bools as single-arm (target form, kill +4 li-0) — baseline body, C, TU-style externs.
 * Expected: identical instruction stream to the in-TU 96.38% build
 * (homes self=r26 victim=r27). */
#include "probe_common.h"

struct KartItemHit {
    KartItemHitVt *vt;                  /* 0x0 */
    char pad_0x4[0xc];
    int raceScore10;                    /* 0x10 */
    char pad_0x14[0x10];
    void *soundCtrl;                    /* 0x24 */
    KartMovementSpeedView *movement;    /* 0x28 */
    KartDriverHitView *ownerDriver;     /* 0x2c */
    char pad_0x30[0x94];
    int hitTimerC4;                     /* 0xc4 */
    int coinSnapC8;                     /* 0xc8 */
    char pad_0xcc[0x31];
    unsigned char coinPenaltyFD;        /* 0xfd */
    char pad_0xfe[0xb];
    unsigned char hitState109;          /* 0x109 */
};

extern unsigned char IsRaceStarted(void);
extern KartRootMtxView *KartDriver_GetKartRootMtx(KartDriverHitView *driver);
extern void KartReaction_Front(KartDriverHitView *drv);
extern void KartReaction_Side(KartDriverHitView *drv);
extern void SoundObj_PlaySE(void *snd, int id);
extern void SoundObj_PlaySE_Direct(void *snd, int id);
extern void fn_801B1458(KartDriverHitView *drv, KartDriverHitView *victim);
extern void RankLog_OnMatchEnd(void *rank, int score, KartDriverHitView *drv, KartDriverHitView *victim);
extern void CoinSystem_RemoveCoins(KartDriverHitView *drv, int n);
extern void memset(void *dst, int c, unsigned int n);
extern void *lbl_806D10A0;
extern const float lbl_806D26EC; /* 0.0f */
extern const float lbl_806D2700;
void KartItem_ApplyImpactImpulseAndRumble(KartItemOpsView *self, int mode, float x, float y, float z);

#pragma exceptions off
unsigned char KartItem_OnKartHit(KartItemHit *self, KartDriverHitView *victim) { /* 0x8004A238 size:0x680 */
    struct {
        float d[3];         /* sp+0x8 */
        float mB[16];       /* sp+0x14 */
        float mA[16];       /* sp+0x54 */
    } s;
    OnHitEvent ev;              /* sp+0x94 */
    OnHitBusView *bus;          /* r25 */
    unsigned char fresh;        /* r26 */
    unsigned char b27;          /* r27 */
    unsigned char b28;          /* r28 */
    KartRootMtxView *rm;        /* r29 */
    unsigned char b26;          /* r26 (reuse) */
    unsigned char b25;          /* r25 (reuse) */
    unsigned char ok;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    KartDriverHitView *drv;
    KartDriverHitView *drv2;
    unsigned long long vf;
    float mx;
    float my;
    float mz;

    bus = self->ownerDriver->itemBus;
    ok = IsRaceStarted();
    if (ok != 0) {
        if (self->hitState109 == 0) {
            if ((bus->flags & 0x80ULL) == 0) {
                b1 = 0;
            } else {
                b1 = 1;
            }
            if (b1 == 1) {
                return 0;
            }
            if ((victim->itemBus->flags & 0x80ULL) == 0) {
                b2 = 0;
            } else {
                b2 = 1;
            }
            if (b2 == 1) {
                return 0;
            }
        }
        rm = KartDriver_GetKartRootMtx(victim);
        drv = self->ownerDriver;
        if ((drv->itemBus->flags & 0x30000000ULL) == 0) {
            float *t;
            int i;

            t = self->movement->transform;
            for (i = 0; i < 16; i++) {
                s.mA[i] = t[i];
            }
            {
                float dir0;
                float dir1;
                float dir2;
                float dot;
                s.d[0] = rm->posX - s.mA[12];
                s.d[1] = rm->posY - s.mA[13];
                s.d[2] = rm->posZ - s.mA[14];
                dir0 = s.mA[0];
                dir1 = s.mA[1];
                dir2 = *(volatile float *)&s.mA[2];         /* reload-mode slot */
                dot = s.d[0] * dir0 + s.d[1] * dir1 + s.d[2] * dir2;
                if (dot > lbl_806D26EC) {
                    KartReaction_Side(drv);
                } else {
                    KartReaction_Front(drv);
                }
            }
        }
        fresh = 0;
        if (bus->lastVictim == 0) {
            if ((self->ownerDriver->itemBus->flags & 0x30000000ULL) == 0) {
                SoundObj_PlaySE_Direct(self->soundCtrl, 0x58);
                SoundObj_PlaySE(self->soundCtrl, 0x11);
                fn_801B1458(self->ownerDriver, victim);
                if (self->hitTimerC4 <= 0) {
                    void *rank;

                    fresh = 1;
                    if ((rank = lbl_806D10A0) == 0) {
                        rank = 0;
                    }
                    if (rank != 0) {
                        RankLog_OnMatchEnd(rank, self->raceScore10, self->ownerDriver, victim);
                    }
                }
            }
            if ((self->ownerDriver->itemBus->flags & 0x10000000ULL) == 0) {
                b3 = 0;
            } else {
                b3 = 1;
            }
            if (b3 == 1) {
                SoundObj_PlaySE_Direct(self->soundCtrl, 0xc6);
            }
            self->hitTimerC4 = 0x3c;
        }
        bus->lastVictim = victim;
        if (fresh == 1) {
            if (self->coinPenaltyFD != 0) {
                if (self->raceScore10 != 4) {
                    CoinSystem_RemoveCoins(self->ownerDriver, 1);
                } else {
                    KartDriverHitView *d2 = self->ownerDriver;
                    int n = d2->coins2cc - 1;
                    if (n < 0) {
                        n = 0;
                    }
                    d2->coins2cc = n;
                }
                self->coinSnapC8 = self->ownerDriver->coins2cc;
            }
        }
        KartItem_ApplyImpactImpulseAndRumble((KartItemOpsView *)self, 1, rm->posX, rm->posY, rm->posZ);
        if (self->hitState109 == 1) {
            return 1;
        }
        drv2 = self->ownerDriver;
        b28 = 0;
        if (((*(OnHitBusView * volatile *)&drv2->itemBus)->flags & 0x20000000ULL) != b28) {
            b28 = 1;
        }
        vf = victim->itemBus->flags;
        b27 = 0;
        if ((vf & 0x20000000ULL) != b27) {
            b27 = 1;
        }
        b26 = 0;
        if (((*(OnHitBusView * volatile *)&drv2->itemBus)->flags & 0x10000000ULL) != b26) {
            b26 = 1;
        }
        b25 = 0;
        if ((vf & 0x10000000ULL) != b25) {
            b25 = 1;
        }
        memset(&ev, 0, 0x1ec);
        {
            float *t2;
            int j;

            t2 = self->movement->transform;
            for (j = 0; j < 16; j++) {
                s.mB[j] = t2[j];
            }
            {
                float mb12 = s.mB[12];
                float mb13 = s.mB[13];
                float mb14 = s.mB[14];
                float sy = rm->posY + mb13;
                float sx = rm->posX + mb12;
                float sz = rm->posZ + mb14;
                my = lbl_806D2700 * sy;
                mx = lbl_806D2700 * sx;
                mz = lbl_806D2700 * sz;
            }
            ev.posX = mx;
            ev.posY = my;
            ev.posZ = mz;
        }
        if (b28 == 1 && b27 == 0) {
            if (victim->state1f4 >= 0 && victim->state1f4 <= 3) {
                ev.kind = 2;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, 0x122);
            } else {
                ev.kind = 0x3d;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, -1);
            }
        } else if (b28 == 0 && b27 == 1) {
            ev.kind = 2;
            self->vt->applyEffect(self, &ev, -1);
        } else if (b26 == 1 && b25 == 0) {
            if (victim->state1f4 >= 0 && victim->state1f4 <= 3) {
                ev.kind = 2;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, 0x123);
            } else {
                ev.kind = 0x3d;
                victim->dispatcher->vt->onHitEvent(victim->dispatcher, &ev, -1);
            }
        } else if (b26 == 0 && b25 == 1) {
            ev.kind = 2;
            self->vt->applyEffect(self, &ev, 0x123);
        }
        return 1;
    }
    return ok;
}
#pragma exceptions reset
