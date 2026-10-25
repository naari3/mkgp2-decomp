/* KartFx_DispatchByStateBits (0x800B6700): spawns the per-kart state
 * effects (damage, star, burst, coin jump, burnout charges) for the state
 * bits set in the kart's 64-bit flag word. */
#include "game/DrawEffectAccess.h"

typedef struct KartFxState {
    void *kart;
    unsigned char pad4[0x82 - 4];
    unsigned char starCooldown;
    unsigned char pad83;
    unsigned char *coinJump;
    unsigned char pad88[4];
    unsigned char *burnoutA;
    unsigned char *burnoutB;
} KartFxState;

typedef struct KartStateFlags {
    unsigned char pad0[0x10];
    unsigned long long bits;
} KartStateFlags;

extern void DrawEffect_Cb_KartVfx_Bind1_Damage(unsigned char *e);
extern void DrawEffect_Cb_MutekiStar_VfxA(unsigned char *e);
extern void DrawEffect_Cb_MutekiStar_VfxB(unsigned char *e);
extern void DrawEffect_Cb_BurstSpawner_Bind6Then4or5(unsigned char *e);
extern void FinalLapCoinJump_Tick(unsigned char *e);
extern void KartFx_BurnoutChargeTick(unsigned char *e);

static inline unsigned char KartState_IsDamaged(KartStateFlags *st)
{
    if ((st->bits & 0x4000ULL) == 0) {
        return 0;
    }
    return 1;
}

void KartFx_DispatchByStateBits(void *owner, KartFxState *fx, KartStateFlags *st, int active)
{
    unsigned char *e;

    if (active) {
        if (KartState_IsDamaged(st) || (st->bits & 0x8000ULL)) {
            e = DrawEffect_SpawnDirect(DrawEffect_Cb_KartVfx_Bind1_Damage);
            if (e != 0) {
                *(void **)(e + 0x11C) = fx->kart;
            }
        }
    }
    if (active && (st->bits & 0x20000000ULL) && fx->starCooldown == 0) {
        int i;
        for (i = 0; i < 2; i++) {
            if (i != 0) {
                e = DrawEffect_SpawnDirect(DrawEffect_Cb_MutekiStar_VfxA);
            } else {
                e = DrawEffect_SpawnDirect(DrawEffect_Cb_MutekiStar_VfxB);
            }
            if (e != 0) {
                *(void **)(e + 0x11C) = fx->kart;
            }
        }
        fx->starCooldown = 5;
    }
    if (fx->starCooldown != 0) {
        fx->starCooldown--;
    }
    if (active && (st->bits & 0x100ULL)) {
        e = DrawEffect_SpawnDirect(DrawEffect_Cb_BurstSpawner_Bind6Then4or5);
        if (e != 0) {
            *(void **)(e + 0x11C) = fx->kart;
        }
    }
    if ((st->bits & 0x400000000000ULL) && fx->coinJump == 0) {
        fx->coinJump = DrawEffect_SpawnDirect(FinalLapCoinJump_Tick);
        if (fx->coinJump != 0) {
            *(void **)(fx->coinJump + 0x11C) = fx->kart;
        }
    }
    if ((st->bits & 0x40ULL) && fx->burnoutA == 0) {
        fx->burnoutA = DrawEffect_SpawnDirect(KartFx_BurnoutChargeTick);
        if (fx->burnoutA != 0) {
            *(void **)(fx->burnoutA + 0x11C) = fx->kart;
            *(void **)(fx->burnoutA + 0xDC) = owner;
        }
    }
    if ((st->bits & 0x400ULL) && fx->burnoutB == 0) {
        fx->burnoutB = DrawEffect_SpawnDirect(KartFx_BurnoutChargeTick);
        if (fx->burnoutB != 0) {
            *(unsigned int *)(fx->burnoutB + 0x10) = 1;
            *(void **)(fx->burnoutB + 0x11C) = fx->kart;
            *(void **)(fx->burnoutB + 0xDC) = owner;
        }
    }
}
