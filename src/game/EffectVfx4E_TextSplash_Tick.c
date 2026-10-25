/* EffectVfx4E_TextSplash_Tick (0x800C3124): ground-aligned text splash
 * (resource 0x4E). It pops in with a sine overshoot, re-aligns to the
 * ground slope whenever it moves, and shrinks or fades on finish. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5400; /* 0.0 */
extern const float lbl_806D5424; /* 1.0 */
extern const float lbl_806D5464; /* pi / 2 */
extern void SoundMgr_PlaySE_Positional(int id, Vec pos, int a);
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern float Item_ProbeForwardGroundPitch(Vec pos, float a, float b, float c);
extern float Item_ProbeLateralGroundPitch(Vec pos, float a, float b, float c);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float angle);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float angle);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
extern double sin(double x);

void EffectVfx4E_TextSplash_Tick(unsigned char *self)
{
    float m[4][4];
    int dirty = 0;

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x4E);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        U8(0x28) = 1;
        F(0x2C) = 1.0f;
        F(0xB0) = 0.0f;
        GetSpawnPosition(V(0x120), 0.0f, 0.0f, 0.0f);
        F(0x150) = 0.0f;
        SoundMgr_PlaySE_Positional(0x8F, *V(0x8C), 0);
        STATE++;
        dirty = 1;
    case 1:
        if (F(0x8C) != F(0x120) || F(0x90) != F(0x124) || F(0x94) != F(0x128)) {
            ItemObject_GetGroundTypeAt(*V(0x8C), &F(0x90), 0);
            F(0x98) = Item_ProbeForwardGroundPitch(*V(0x8C), 0.0f, 5.0f, 0.0f);
            F(0xA0) = Item_ProbeLateralGroundPitch(*V(0x8C), 0.0f, 5.0f, 0.0f);
            F(0x90) += 1.0f;
            Vec3_Copy(V(0x120), V(0x8C));
            dirty = 1;
        }
        if (lbl_806D5424 != F(0x150)) {
            F(0x150) += 0.01f;
            if (lbl_806D5424 < F(0x150)) {
                F(0x150) = lbl_806D5424;
            }
            F(0xB0) = 4.5f * (float)sin(0.017453292f * (90.0f * F(0x150)));
            dirty = 1;
        }
        switch (FINISHED) {
        case 1:
            STATE = 2;
            S8(0xB5) = 0;
            break;
        case 2:
            STATE = 3;
            S8(0xB5) = 0;
            break;
        }
        break;
    case 2:
        switch (S8(0xB5)) {
        case 0:
            F(0x150) = 0.0f;
            F(0x154) = F(0xB0);
            S8(0xB5)++;
        case 1:
            break;
        }
        F(0x150) += 0.06f;
        if (1.0f < F(0x150)) {
            DrawEffect_Free(self);
            return;
        }
        {
            float s = sin(lbl_806D5464 * F(0x150));
            F(0xB0) = F(0x154) * (1.0f - s);
        }
        dirty = 1;
        break;
    case 3:
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            DrawEffect_Free(self);
            return;
        }
        break;
    }

    if (dirty) {
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, F(0xB0));
        Matrix4_PreMultiplyRotZ(m, m, F(0xA0));
        Matrix4_PreMultiplyRotX(m, m, F(0x98));
        Mtx44_Translate(m, m, *V(0x8C));
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
    }
    TICK_TIMERS();
}
