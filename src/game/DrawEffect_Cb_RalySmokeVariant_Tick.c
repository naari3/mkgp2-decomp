/* DrawEffect_Cb_RalySmokeVariant_Tick (0x800C80C0): smoke puff (resource
 * 0x70) on one of four joints (I(0x10)). It drifts along that joint's
 * direction in camera space, rides along with the kart's motion, and
 * shrinks away once its 10-frame hold runs out. */
#include "game/DrawEffectAccess.h"

typedef struct { Vec v[4]; } DirTable;
typedef struct { const char *name[4]; } JointTable;

extern unsigned char lbl_805DF3D0[];
extern void VfxSlot_ResolveJoint(void *slot, const char *name);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], void *src);
extern void Mtx44_TransformVec3(Vec *out, void *m, Vec *in);

void DrawEffect_Cb_RalySmokeVariant_Tick(unsigned char *self)
{
    float inv[4][4];
    /* Local aggregate initializers supply the copied direction and joint tables. */
    DirTable dirs = {{
        {0.126f, 0.20099998f, 0.0f},
        {-0.182f, 0.20099998f, 0.0f},
        {-0.168f, -0.20100003f, 0.0f},
        {0.196f, -0.20100003f, 0.0f},
    }};
    Vec v;
    static const char lbl_8032A810[0x1C] = "raly_x_smoke__T_T_2_1_joint";
    static const char lbl_8032A82C[0x1C] = "raly_x_smoke__T_T_1_1_joint";
    static const char lbl_8032A848[0x1A] = "raly_x_smoke__T_T_4_joint";
    static const char lbl_8032A864[0x1A] = "raly_x_smoke__T_T_3_joint";

    JointTable joints = {{lbl_8032A810, lbl_8032A82C, lbl_8032A848, lbl_8032A864}};
    Vec cur;
    Vec delta;
    Vec local;
    Vec pos;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x70, 0);
        VfxSlot_ResolveJoint(SLOT(self), joints.name[I(0x10)]);
        Vec3_Scale(V(0x120), &dirs.v[I(0x10)], F(0xB0));
        Vec3_Copy(V(0x12C), V(0x8C));
        Vec3_Scale(V(0xA4), &dirs.v[I(0x10)], 10.0f);
        F(0x2C) = 1.0f;
        U32(0x180) = 10;
        F(0x150) = F(0xB0) / 20.0f;
        if (P(0x11C) != 0) {
            Mtx44_GetTranslation_RowMajor(V(0x138), KartDriver_GetKartRootMtx(P(0x11C)));
        }
        STATE++;
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        F(0xB0) = F(0xB0) - F(0x150);
        if (F(0xB0) < 0.0f) {
            U8(0x28) = 0;
            STATE = 3;
            S8(0xB5) = 0;
            return;
        }
    }
    Vec3_Scale(V(0xA4), V(0xA4), 0.8f);
    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    if (P(0x11C) != 0) {
        Mtx44_GetTranslation_RowMajor(&cur, KartDriver_GetKartRootMtx(P(0x11C)));
        Vec3_Subtract_DestFirst(&delta, &cur, V(0x138));
        Vec3_Add_DestFirst(V(0x12C), V(0x12C), &delta);
        Vec3_Copy(V(0x138), &cur);
    }
    Mtx44_Inverse_GaussJordan(inv, lbl_805DF3D0);
    local = *V(0x120);
    Mtx44_TransformVec3(&v, lbl_805DF3D0, &local);
    Vec3_Subtract_DestFirst(&v, &v, (Vec *)(lbl_805DF3D0 + 0x80));
    Vec3_Add_DestFirst(V(0x8C), V(0x12C), &v);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
