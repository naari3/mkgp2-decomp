/* FinalLapCoinJump_Tick (0x800B5694): drives the coin-jump particle grid
 * on the kart's joint 13 while the kart's 0x400000000000 state bit is set,
 * fading it in/out with a looping SE 0x9F. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51D8; /* 0.05 */
extern const float lbl_806D51EC; /* 0.6 */
extern void CoinJumpFx_SpawnSlots(unsigned char *e);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern signed char SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);
extern void KartDriver_GetJoint13_WorldPos(Vec *out, void *kart);
extern float KartFxParam_GetConst1p5(void *kart);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void CoinJumpFx_UpdateParticleGrid(void *fx, Vec pos, float scale, float alpha);

void FinalLapCoinJump_Tick(unsigned char *self)
{
    switch (STATE) {
    case 0:
        P(0xDC) = DrawEffect_SpawnDirect(CoinJumpFx_SpawnSlots);
        if (P(0xDC) != 0) {
            *(unsigned int *)(P(0xDC) + 0x10) = 1;
        }
        F(0x2C) = 0.0f;
        S8(0x190) = -1;
        STATE++;
    case 1:
        break;
    }

    if (FINISHED) {
        if (P(0xDC) != 0) {
            *(signed char *)(P(0xDC) + 0xC9) = 1;
        }
        P(0xDC) = 0;
        if (S8(0x190) >= 0) {
            SoundMgr_StopSE_OrSpecial(0x9F, S8(0x190));
            S8(0x190) = -1;
        }
        DrawEffect_Free(self);
        return;
    }

    if (*(unsigned long long *)(*(unsigned char **)(P(0x11C) + 0x304) + 0x10) & 0x400000000000ULL) {
        F(0x2C) += lbl_806D51D8;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
        if (S8(0x190) < 0) {
            S8(0x190) = SoundMgr_CountActiveSEInstances(0x9F);
            if (S8(0x190) >= 0) {
                SoundMgr_PlaySE_Positional(0x9F, *V(0x8C), S8(0x190));
            }
        } else {
            SoundMgr_PlaySE_WithChannel(0x9F, *V(0x8C), S8(0x190));
        }
    } else {
        F(0x2C) -= lbl_806D51D8;
        if (F(0x2C) < 0.0f) {
            F(0x2C) = 0.0f;
        }
        if (S8(0x190) >= 0) {
            SoundMgr_StopSE_OrSpecial(0x9F, S8(0x190));
            S8(0x190) = -1;
        }
    }

    KartDriver_GetJoint13_WorldPos(V(0x8C), P(0x11C));
    F(0xB0) = lbl_806D51EC * KartFxParam_GetConst1p5(P(0x11C));
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        S8(0x28) = 0;
    } else {
        S8(0x28) = 1;
    }
    if (S8(0x28)) {
        CoinJumpFx_UpdateParticleGrid(P(0xDC), *V(0x8C), F(0xB0), F(0x2C));
    } else {
        CoinJumpFx_UpdateParticleGrid(P(0xDC), *V(0x8C), F(0xB0), 0.0f);
    }
}
