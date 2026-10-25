/* DrawEffect_Cb_RalySmokeVariant_Tick (0x800C80C0): smoke puff (resource
 * 0x70) on one of four joints (I(0x10)). It drifts along that joint's
 * direction in camera space, rides along with the kart's motion, and
 * shrinks away once its 10-frame hold runs out. */
#include "game/DrawEffectAccess.h"

typedef struct { Vec v[4]; } DirTable;
typedef struct { const char *name[4]; } JointTable;

extern const DirTable lbl_8032A7E0;
extern const char *const lbl_8032A880[4];
extern unsigned char lbl_805DF3D0[];
extern void VfxSlot_ResolveJoint(void *slot, const char *name);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], void *src);
extern void Mtx44_TransformVec3(Vec *out, void *m, Vec *in);

void DrawEffect_Cb_RalySmokeVariant_Tick(unsigned char *self)
{
    float inv[4][4];
    DirTable dirs = lbl_8032A7E0;
    Vec v;
    JointTable joints = *(const JointTable *)lbl_8032A880;
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
