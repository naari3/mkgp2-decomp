#include "game/DrawEffectAccess.h"

extern const char *lbl_8041A334[3];
extern int Rand_RangeIntMax(int max);
extern void VfxSlot_ResolveJoint(void *slot, const char *name);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Vec3_ScaleXZ(Vec *out, Vec *in, float s);
extern double sin(double x);

/* DrawEffect_Cb_MutekiStar_VfxB (0x800B61D4): companion sparkle that orbits
 * the kart in a random direction while rising, breathing in and out. */
void DrawEffect_Cb_MutekiStar_VfxB(unsigned char *self)
{
    float root[4][4];
    Vec r;
    Vec local;
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
        S8(0x190) = Rand_RangeIntMax(0xF) % 2;
        STATE++;
    case 1:
        break;
    }

    F(0x150) += 0.05f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
    if (S8(0x190)) {
        Vec2_RotateY(&r, V(0x120), 0.017453292f * (180.0f * F(0x150)));
    } else {
        Vec2_RotateY(&r, V(0x120), 0.017453292f * (-1.0f * (180.0f * F(0x150))));
    }
    s = sin(0.017453292f * (180.0f * F(0x150)));
    Vec3_ScaleXZ(&r, &r, 0.5f * s + 0.5f);
    r.y = 10.0f * F(0x150) + r.y;
    local = r;
    Mtx44_TransformVec3(V(0x8C), root, &local);
    F(0xA0) = BuildOrientationFromYaw(0.008726646f + F(0xA0));
    t = F(0x150);
    if (t < 0.2f) {
        s = t / 0.2f;
    } else if (t < 0.8f) {
        s = 1.0f;
    } else {
        s = (1.0f - t) / 0.2f;
    }
    F(0xB0) = 0.8f * (F(0x154) * s);
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
