/*
 * KartFx_MasterTick, 0x800B510C..0x800B53BC: per-frame driver of the kart
 * effect block at kart+0xCC. State 0 seeds the previous root position; state 1
 * computes the local-space offset and per-frame travel, gates the effects on
 * distance/height, spawns the boost-charge icon and the drift sparks and runs
 * the five effect dispatch groups.
 */

#include "game/types/Vec.h"

extern void *DrawEffect_SpawnDirect(void (*callback)(void));
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void KartFx_DispatchByStateBits(unsigned char *self, unsigned char *fx, unsigned char *kart, int enabled);
extern void KartFx_DispatchGroupA(unsigned char *self, unsigned char *fx, unsigned char *kart, int enabled);
extern void KartFx_DispatchGroupB_AuxStarBurst(unsigned char *self, unsigned char *fx, unsigned char *kart, int enabled);
extern void KartFx_DispatchGroupD_RingBurst(unsigned char *self, unsigned char *fx, unsigned char *kart, int enabled);
extern void KartFx_DispatchGroupE_StateByte(unsigned char *self, unsigned char *fx, unsigned char *kart, int enabled);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void Mtx44_Inverse_GaussJordan(float (*dst)[4], void *src);
extern void Mtx44_TransformVec3(void *dst, float (*mtx)[4], Vec v);
extern void Vec3_Copy(void *dst, void *src);
extern float Vec3_Magnitude_Wrapper(void *v);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);

extern void KartFx_BoostChargeIconTick(void);
extern void KartFx_DriftSparkParticleTick(void);
extern unsigned char lbl_805DF3D0[];

#define F(p, o) (*(float *)((p) + (o)))
#define S8(p, o) (*(signed char *)((p) + (o)))
#define DRIVER(fx) (*(unsigned char **)(fx))

#pragma exceptions on
#pragma use_lmw_stmw on

void KartFx_MasterTick(unsigned char *self)
{
    float mtx[4][4];
    unsigned char *fx;
    unsigned char *kart;
    unsigned char *eff;
    int enabled;

    fx = self + 0xCC;
    switch (S8(self, 0xB4)) {
    case 0:
        Mtx44_GetTranslation_RowMajor(fx + 0xC, KartDriver_GetKartRootMtx(DRIVER(fx)));
        fx[0x8] = 0;
        fx[0x9] = 0;
        self[0xB4]++;
        break;
    case 1:
        kart = *(unsigned char **)(DRIVER(fx) + 0x304);
        Mtx44_GetTranslation_RowMajor(self + 0x8C, KartDriver_GetKartRootMtx(DRIVER(fx)));
        Mtx44_Inverse_GaussJordan(mtx, lbl_805DF3D0);
        Mtx44_TransformVec3(fx + 0x28, mtx, *(Vec *)(self + 0x8C));
        F(fx, 0x34) = Vec3_Magnitude_Wrapper(fx + 0x28);
        Vec3_Subtract_DestFirst(fx + 0x18, self + 0x8C, fx + 0xC);
        F(fx, 0x24) = Vec3_Magnitude_Wrapper(fx + 0x18);
        if (15.0f < F(fx, 0x24)) {
            F(fx, 0x24) = 15.0f;
        }
        Vec3_Copy(fx + 0xC, self + 0x8C);
        if (S8(fx, 0x8) == 0 || S8(fx, 0x9) == 0) {
            F(fx, 0x3C) = 0.0f;
        }
        if (F(kart, 0x28)) {
            F(fx, 0x3C) = 0.0f;
        }
        enabled = 1;
        if (500.0f < F(fx, 0x34)) {
            enabled = 0;
        }
        if (F(fx, 0x30) < -20.0f) {
            enabled = 0;
        }
        if (enabled && DRIVER(fx)[0x348] != 0) {
            DRIVER(fx)[0x348] = 0;
            eff = DrawEffect_SpawnDirect(KartFx_BoostChargeIconTick);
            if (eff != 0) {
                *(unsigned char **)(eff + 0x11C) = DRIVER(fx);
            }
        }
        if (5.0f < F(fx, 0x24) && S8(fx, 0x40) != 0) {
            if (*(int *)(DRIVER(fx) + 0x238) != 0) {
                F(fx, 0x48) += 0.2f * F(fx, 0x24);
                while (1.0f <= F(fx, 0x48)) {
                    F(fx, 0x48) -= 1.0f;
                    eff = DrawEffect_SpawnDirect(KartFx_DriftSparkParticleTick);
                    if (eff != 0) {
                        *(unsigned char **)(eff + 0x11C) = DRIVER(fx);
                    }
                }
            }
        } else {
            F(fx, 0x48) = 0.0f;
        }
        KartFx_DispatchGroupA(self, fx, kart, enabled);
        KartFx_DispatchGroupB_AuxStarBurst(self, fx, kart, enabled);
        KartFx_DispatchByStateBits(self, fx, kart, enabled);
        KartFx_DispatchGroupD_RingBurst(self, fx, kart, enabled);
        KartFx_DispatchGroupE_StateByte(self, fx, kart, enabled);
        break;
    }
}

#pragma use_lmw_stmw reset
#pragma exceptions reset
