/* DrawEffect_Cb_KartWheel_DualSpawn (0x800B7C9C): parent of two wheel
 * children (DrawEffect_KartWheel_TripleChildSpawn), one per rear wheel.
 * It fades in while the driver has status flag 8 or 0x10 set, spins at a
 * random rate and drives both children each frame. */
#include "game/DrawEffectAccess.h"
#include "game/DrawEffectWheelPairState.h"

#include "game/types/PhaseTable.h"

extern const PhaseTable DrawEffect_Cb_KartWheel_DualSpawn_rodata_8032A6D4;
extern int Rand_RangeInt(int lo, int hi);
extern double sin(double x);
extern void DrawEffect_KartWheel_TripleChildSpawn(unsigned char *self);
extern void DrawEffect_KartWheel_TripleChildUpdate(unsigned char *child, Vec *pos, float scale, float alpha);

static inline float sinf(float x)
{
    return sin(x);
}

#include "game/ItemEffectBusPrivate.h"

static inline unsigned char has_flag(ItemEffectBus *st, unsigned long long mask)
{
    unsigned char result;

    if ((st->mask & mask) == 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

void DrawEffect_Cb_KartWheel_DualSpawn(unsigned char *self)
{
    WheelPairState *d = (WheelPairState *)(self + 0xCC);
    int i;

    switch (STATE) {
    case 0:
        d->children[0] = DrawEffect_SpawnDirect(DrawEffect_KartWheel_TripleChildSpawn);
        d->children[1] = DrawEffect_SpawnDirect(DrawEffect_KartWheel_TripleChildSpawn);
        F(0x2C) = 0.0f;
        d->angle = 0.0f;
        d->speed = 0.0f;
        d->timers[0] = 0;
        STATE++;
    case 1:
        break;
    }

    if (FINISHED) {
        if (d->children[0] != 0) {
            *(signed char *)(d->children[0] + 0xC9) = 1;
        }
        if (d->children[1] != 0) {
            *(signed char *)(d->children[1] + 0xC9) = 1;
        }
        d->children[0] = 0;
        d->children[1] = 0;
        DrawEffect_Free(self);
        return;
    }
    {
        ItemEffectBus *st = *(ItemEffectBus **)(d->driver + 0x304);
        int active = 0;
        if (has_flag(st, 8ULL)) {
            active = 1;
        }
        if (st->mask & 0x10ULL) {
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
    if (d->timers[0] == 0) {
        d->speed = 0.017453292f * Rand_RangeFloat(1.0f, 6.0f);
        d->timers[0] = Rand_RangeInt(30, 60);
    }
    d->angle = BuildOrientationFromYaw(d->angle + d->speed);
    if (FinalLapCoinJump_CheckActiveForObject(d->driver)) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
    for (i = 0; i < 2; i++) {
        if (d->children[i] != 0) {
            Vec wheel;
            PhaseTable offs;
            Vec local;
            Vec local2;
            float k;
            if (i == 0) {
                Mtx44_GetTranslation_RowMajor(&wheel, KartDriver_GetJointByIdx(d->driver, 2));
            } else {
                Mtx44_GetTranslation_RowMajor(&wheel, KartDriver_GetJointByIdx(d->driver, 3));
            }
            offs = DrawEffect_Cb_KartWheel_DualSpawn_rodata_8032A6D4;
            k = 0.8f * ((1.0f + sinf(BuildOrientationFromYaw(d->angle + offs.v[i]))) / 2.0f) + 0.2f;
            if (S8(0x28)) {
                local = wheel;
                DrawEffect_KartWheel_TripleChildUpdate(d->children[i], &local, 0.9f, F(0x2C) * k);
            } else {
                local2 = wheel;
                DrawEffect_KartWheel_TripleChildUpdate(d->children[i], &local2, 0.9f, 0.0f);
            }
            *(float *)(d->children[i] + 0x150) += 0.007142857f;
            if (1.0f < *(float *)(d->children[i] + 0x150)) {
                *(float *)(d->children[i] + 0x150) -= 1.0f;
            }
        }
    }
    DrawEffect_TickTimer(&d->timers[0]);
    DrawEffect_TickTimer(&d->timers[1]);
    DrawEffect_TickTimer(&d->timers[2]);
    DrawEffect_TickTimer(&d->timers[3]);
}
