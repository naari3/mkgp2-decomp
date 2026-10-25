/* DrawEffect_Cb_KartWheel_DualSpawn (0x800B7C9C): parent of two wheel
 * children (DrawEffect_KartWheel_TripleChildSpawn), one per rear wheel.
 * It fades in while the driver has status flag 8 or 0x10 set, spins at a
 * random rate and drives both children each frame. */
#include "game/DrawEffectAccess.h"

typedef struct { float v[4]; } PhaseTable;

extern const PhaseTable lbl_8032A6D4;
extern int Rand_RangeInt(int lo, int hi);
extern double sin(double x);
extern void DrawEffect_KartWheel_TripleChildSpawn(unsigned char *self);
extern void DrawEffect_KartWheel_TripleChildUpdate(unsigned char *child, Vec *pos, float scale, float alpha);

#define D(o) (*(float *)(d + (o)))
#define DI(o) (*(unsigned int *)(d + (o)))
#define DP(o) (*(unsigned char **)(d + (o)))

static inline unsigned char Flag_Test(unsigned long long flags, unsigned long long mask)
{
    unsigned char r = 0;
    if (flags & mask) {
        r = 1;
    }
    return r;
}

void DrawEffect_Cb_KartWheel_DualSpawn(unsigned char *self)
{
    unsigned char *d = self + 0xCC;
    unsigned char **child;
    float *phase;
    int i;

    switch (STATE) {
    case 0:
        DP(0x10) = DrawEffect_SpawnDirect(DrawEffect_KartWheel_TripleChildSpawn);
        DP(0x14) = DrawEffect_SpawnDirect(DrawEffect_KartWheel_TripleChildSpawn);
        F(0x2C) = 0.0f;
        D(0x84) = 0.0f;
        D(0x88) = 0.0f;
        DI(0xB4) = 0;
        STATE++;
    case 1:
        break;
    }

    if (FINISHED) {
        if (DP(0x10) != 0) {
            *(signed char *)(DP(0x10) + 0xC9) = 1;
        }
        if (DP(0x14) != 0) {
            *(signed char *)(DP(0x14) + 0xC9) = 1;
        }
        DP(0x10) = 0;
        DP(0x14) = 0;
        DrawEffect_Free(self);
        return;
    }
    {
        unsigned long long flags = *(unsigned long long *)(*(unsigned char **)(DP(0x50) + 0x304) + 0x10);
        int active = 0;
        if (Flag_Test(flags, 8ULL)) {
            active = 1;
        }
        if (flags & 0x10ULL) {
            active = 1;
        }
        if (active != 0) {
            F(0x2C) += 0.1f;
            if (1.0f < F(0x2C)) {
                F(0x2C) = 1.0f;
            }
        } else {
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                F(0x2C) = 0.0f;
            }
        }
    }
    if (DI(0xB4) == 0) {
        D(0x88) = 0.017453292f * Rand_RangeFloat(1.0f, 6.0f);
        DI(0xB4) = Rand_RangeInt(30, 60);
    }
    D(0x84) = BuildOrientationFromYaw(D(0x84) + D(0x88));
    if (FinalLapCoinJump_CheckActiveForObject(DP(0x50))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
    for (i = 0; i < 2; i++) {
        if (DP(0x10 + i * 4) != 0) {
            Vec wheel;
            PhaseTable offs;
            Vec local;
            Vec local2;
            float k;
            if (i == 0) {
                Mtx44_GetTranslation_RowMajor(&wheel, KartDriver_GetJointByIdx(DP(0x50), 2));
            } else {
                Mtx44_GetTranslation_RowMajor(&wheel, KartDriver_GetJointByIdx(DP(0x50), 3));
            }
            offs = lbl_8032A6D4;
            k = 0.8f * ((1.0f + (float)sin(BuildOrientationFromYaw(D(0x84) + offs.v[i]))) * 0.5f) + 0.2f;
            if (S8(0x28)) {
                local = wheel;
                DrawEffect_KartWheel_TripleChildUpdate(DP(0x10 + i * 4), &local, 0.9f, F(0x2C) * k);
            } else {
                local2 = wheel;
                DrawEffect_KartWheel_TripleChildUpdate(DP(0x10 + i * 4), &local2, 0.9f, 0.0f);
            }
            *(float *)(DP(0x10 + i * 4) + 0x150) += 0.007142857f;
            if (1.0f < *(float *)(DP(0x10 + i * 4) + 0x150)) {
                *(float *)(DP(0x10 + i * 4) + 0x150) -= 1.0f;
            }
        }
    }
    DrawEffect_TickTimer((unsigned int *)(d + 0xB4));
    DrawEffect_TickTimer((unsigned int *)(d + 0xB8));
    DrawEffect_TickTimer((unsigned int *)(d + 0xBC));
    DrawEffect_TickTimer((unsigned int *)(d + 0xC0));
}
