/* EffectVfx6D_KartSmokeSpark_Tick (0x800C0004): smoke spark (resource 0x6D)
 * spawned at a jittered point behind the kart; it fades in, follows the
 * kart with growing slack, then grows and fades out. */
#include "game/DrawEffectAccess.h"

extern const Vec lbl_8032A3F4; /* {0, 0, -10} */
extern const float lbl_806D51C0; /* 0.0 */
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);

void EffectVfx6D_KartSmokeSpark_Tick(unsigned char *self)
{
    float root[4][4];
    Vec kartPos;
    Vec diff;
    Vec off;
    Vec pos;

    if (P(0x11C) != 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
        off = lbl_8032A3F4;
        Mtx44_TransformVec3(&kartPos, root, &off);
    }

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x6D, 0);
        switch (S8(0x190)) {
        case 1:
            GetSpawnPosition(V(0x30), 1.0f, 1.0f, 1.0f);
            break;
        case 2:
            GetSpawnPosition(V(0x30), 1.0f, 1.0f, 0.9f);
            break;
        case 3:
            GetSpawnPosition(V(0x30), 0.7f, 0.6f, 0.3f);
            break;
        }
        F(0x150) = 1.0f;
        F(0x154) = 3.0f * Rand_RangeFloat(0.5f, 1.5f);
        F(0x158) = 0.0f;
        if (P(0x11C) != 0) {
            Vec3_Copy(V(0x8C), &kartPos);
        }
        F(0x8C) += Rand_RangeFloat(-2.0f, 2.0f);
        F(0x90) += Rand_RangeFloat(-2.0f, 2.0f);
        F(0x94) += Rand_RangeFloat(-2.0f, 2.0f);
        if (P(0x11C) != 0) {
            Vec3_Copy(V(0x120), &kartPos);
            Vec3_Subtract_DestFirst(V(0x12C), V(0x8C), &kartPos);
            F(0x15C) = 0.0f;
        }
        STATE++;
    case 1:
        F(0x158) += 0.25f;
        if (1.0f <= F(0x158)) {
            F(0x158) = 1.0f;
            STATE++;
        }
        break;
    case 2:
        F(0x150) += 0.015f;
        F(0x158) -= 0.05f;
        if (F(0x158) <= 0.0f) {
            DrawEffect_Free(self);
            return;
        }
        break;
    }

    if (P(0x11C) != 0) {
        float len;
        Vec3_Subtract_DestFirst(&diff, V(0x120), &kartPos);
        len = Vec3_Magnitude_Wrapper(&diff);
        if (len != lbl_806D51C0 && F(0x15C) < len) {
            Vec3_Scale(&diff, &diff, 1.0f / len * F(0x15C));
            Vec3_Add_DestFirst(V(0x120), &kartPos, &diff);
        }
        Vec3_Add_DestFirst(V(0x8C), V(0x120), V(0x12C));
        F(0x15C) += 1.0f;
    }

    F(0xB0) = F(0x150) * F(0x154);
    if ((int)U8(0x190) != 3) {
        F(0x2C) = 0.5f * F(0x158);
    } else if (P(0x11C) == 0) {
        F(0x2C) = 0.8f * F(0x158);
    } else {
        F(0x2C) = 0.8f * F(0x158);
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
}
