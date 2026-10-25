/* DrawEffect_Cb_KartFire_WithSE99 (0x800B72FC): kart fire effect. It keeps
 * a two-child flame on the kart's joint 15, pulled toward the camera, and
 * loops SE 0x99 while the kart's 0x1000000000000000 state bit is set. */
#include "game/DrawEffectAccess.h"

typedef struct CameraView {
    unsigned char pad0[0x80];
    Vec eye;
} CameraView;

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D5200; /* 10.0 */
extern CameraView lbl_805DF3D0;
extern void Effect_TwoChild_Res3C_3D_Init(unsigned char *e);
extern void Effect_TwoChildRotate_FromPhase150(void *fx, Vec pos, float size, float alpha);
extern float KartCharacterParam_GetFxSizeFactor(void *driver);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern signed char SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);

void DrawEffect_Cb_KartFire_WithSE99(unsigned char *self)
{
    int on;

    switch (STATE) {
    case 0:
        P(0xDC) = DrawEffect_SpawnDirect(Effect_TwoChild_Res3C_3D_Init);
        if (P(0xDC) != 0) {
            Effect_TwoChild_Res3C_3D_Init(P(0xDC));
        }
        S8(0x190) = -1;
        STATE++;
    case 1:
        break;
    }

    if (FINISHED) {
        if (S8(0x190) >= 0) {
            SoundMgr_StopSE_OrSpecial(0x99, S8(0x190));
            S8(0x190) = -1;
        }
        if (P(0xDC) != 0) {
            *(signed char *)(P(0xDC) + 0xC9) = 1;
        }
        P(0xDC) = 0;
        DrawEffect_Free(self);
        return;
    }

    on = 0;
    if (*(unsigned long long *)(*(unsigned char **)(P(0x11C) + 0x304) + 0x10) & 0x1000000000000000ULL) {
        on = 1;
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        S8(0x28) = 0;
    } else {
        S8(0x28) = 1;
    }
    if (P(0xDC) != 0) {
        Vec pos;
        Vec d;
        float size;

        *(signed char *)(P(0xDC) + 0x190) = on;
        Mtx44_GetTranslation_RowMajor(&pos, KartDriver_GetJointByIdx(P(0x11C), 0xF));
        Vec3_Subtract_DestFirst(&d, &lbl_805DF3D0.eye, &pos);
        Vec3_Scale(&d, &d, lbl_806D5200 * (lbl_806D51C4 / Vec3_Magnitude_Wrapper(&d)));
        Vec3_Add_DestFirst(&pos, &pos, &d);
        size = KartCharacterParam_GetFxSizeFactor(P(0x11C));
        if (S8(0x28)) {
            Effect_TwoChildRotate_FromPhase150(P(0xDC), pos, size, lbl_806D51C4);
        } else {
            Effect_TwoChildRotate_FromPhase150(P(0xDC), pos, size, lbl_806D51C0);
        }
        Vec3_Copy(V(0x8C), &pos);
    }
    if (on) {
        if (S8(0x190) < 0) {
            S8(0x190) = SoundMgr_CountActiveSEInstances(0x99);
            if (S8(0x190) >= 0) {
                SoundMgr_PlaySE_Positional(0x99, *V(0x8C), S8(0x190));
            }
        } else {
            SoundMgr_PlaySE_WithChannel(0x99, *V(0x8C), S8(0x190));
        }
    } else if (S8(0x190) >= 0) {
        SoundMgr_StopSE_OrSpecial(0x99, S8(0x190));
        S8(0x190) = -1;
    }
}
