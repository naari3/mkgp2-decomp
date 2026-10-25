/* DrawEffect_Cb_MutekiStar_VfxA (0x800B5E68): star-power sparkle (resource
 * 3) bound to one of three random joints. It rises from a lagging anchor
 * that chases the kart, spinning, and scales in and out over its life. */
#include "game/DrawEffectAccess.h"

extern const char *lbl_8041A334[3];
extern int Rand_RangeIntMax(int max);
extern void VfxSlot_ResolveJoint(void *slot, const char *name);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);

void DrawEffect_Cb_MutekiStar_VfxA(unsigned char *self)
{
    float root[4][4];
    Vec trans;
    Vec follow;
    Vec diff;
    Vec pos;
    float t;
    float s;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 3, 0);
        VfxSlot_ResolveJoint(SLOT(self), lbl_8041A334[Rand_RangeIntMax(0xF) % 3]);
        F(0x150) = 0.0f;
        GetSpawnPosition(V(0x120), 0.0f, Rand_RangeFloat(0.0f, 5.0f), Rand_RangeFloat(8.0f, 10.0f));
        Vec2_RotateY(V(0x120), V(0x120), 0.017453292f * Rand_RangeFloat(-180.0f, 180.0f));
        F(0xA0) = 0.017453292f * Rand_RangeFloat(-180.0f, 180.0f);
        F(0x154) = Rand_RangeFloat(0.5f, 1.2f);
        GetSpawnPosition(V(0x12C), 0.0f, 0.0f, 0.0f);
        F(0x158) = 0.0f;
        STATE++;
    case 1:
        break;
    }

    F(0x150) += 0.05f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    F(0x124) += 1.0f;
    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
    Mtx44_GetTranslation_ColMajor(&trans, root);
    if (0.0f == F(0x158)) {
        Vec3_Copy(&follow, &trans);
    } else {
        float len;
        Vec3_Subtract_DestFirst(&diff, V(0x12C), &trans);
        len = Vec3_Magnitude_Wrapper(&diff);
        if (F(0x158) < len) {
            Vec3_Scale(&diff, &diff, 1.0f / len * F(0x158));
            Vec3_Add_DestFirst(&follow, &trans, &diff);
        } else {
            Vec3_Copy(&follow, V(0x12C));
        }
    }
    Vec3_Copy(V(0x12C), &follow);
    F(0x158) += 2.0f;
    Vec3_Add_DestFirst(V(0x8C), &follow, V(0x120));
    F(0xA0) = BuildOrientationFromYaw(0.008726646f + F(0xA0));
    t = F(0x150);
    if (t < 0.2f) {
        s = 0.8f * (t / 0.2f);
    } else if (t < 0.8f) {
        s = 0.8f;
    } else {
        s = 0.8f * ((1.0f - t) / 0.2f);
    }
    F(0xB0) = 0.8f * (0.8f * (F(0x154) * s));
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
