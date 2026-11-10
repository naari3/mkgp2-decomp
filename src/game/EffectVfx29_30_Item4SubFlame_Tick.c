/* EffectVfx29_30_Item4SubFlame_Tick (0x800BF174): flame jet (resource 0x1D
 * or 0x1E) on the kart root while the linked item is in state 4. Its height
 * follows a 5-key piecewise-linear curve over the frame counter.
 * The segment loop is unrolled by the compiler and the curve is passed as an
 * expression (regalloc_patterns 62). */
#include "game/DrawEffectAccess.h"

#include "game/types/FlameCurve.h"

extern FlameCurve EffectVfx29_30_Item4SubFlame_Tick_data_8041A224[];
extern const float lbl_806D51BC; /* 2.0 */
extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D5344; /* 100.0 */
extern void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float sx, float sy, float sz);

/* A two-row window: the value row is five floats after the key row. */
static inline void FlameCurve_Segment(float (*k)[5], float t, float *out)
{
    float k0 = k[0][0];
    if (k0 <= t && t < k[0][1]) {
        *out = (t - k0) * ((k[1][1] - k[1][0]) / (k[0][1] - k0)) + k[1][0];
    }
}

static inline float FlameCurve_Evaluate(FlameCurve *curve, float t)
{
    float height;

    if (curve->keys[4] <= t) {
        height = curve->values[4];
    } else {
        int i;

        for (i = 0; i < 4; i++) {
            FlameCurve_Segment((float (*)[5])((char *)curve + i * sizeof(float)), t, &height);
        }
    }
    return height;
}

void EffectVfx29_30_Item4SubFlame_Tick(unsigned char *self)
{
    float root[4][4];
    float scale[4][4];
    unsigned char *item;
    int active;

    switch (STATE) {
    case 0:
        if (I(0x10) == 0) {
            VfxSlot_BindResource(SLOT(self), 0x1D);
        } else {
            VfxSlot_BindResource(SLOT(self), 0x1E);
        }
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        F(0x2C) = 1.0f;
        F(0xB0) = 1.0f;
        U8(0x190) = 0;
        F(0x150) = 0.0f;
        F(0x154) = 0.0f;
        STATE++;
    case 1:
        break;
    }

    item = P(0xDC);
    active = 0;
    if (item != 0 && (int)item[0xD4] == 4 && (int)item[0xD5] == 4 && lbl_806D51BC <= *(float *)(item + 0xF0)) {
        active = 1;
    }
    if (active && !S8(0x190)) {
        F(0x150) = 0.0f;
    }
    U8(0x190) = active;
    F(0x150) += 1.0f;
    if (60.0f < F(0x150)) {
        F(0x150) = 60.0f;
    }
    if (active) {
        F(0x154) = 1.0f;
    }
    F(0x154) -= 0.3f;
    if (F(0x154) < 0.0f) {
        F(0x154) = 0.0f;
    }
    if (F(0x154) != lbl_806D51C0) {
        U8(0x28) = 1;
        if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
            U8(0x28) = 0;
        } else {
            U8(0x28) = 1;
        }
    } else {
        U8(0x28) = 0;
    }

    if (S8(0x28)) {
        float height;
        int idx = I(0x10);

        height = FlameCurve_Evaluate(EffectVfx29_30_Item4SubFlame_Tick_data_8041A224 + idx, F(0x150));

        height /= lbl_806D5344;
        if (height == lbl_806D51C0) {
            U8(0x28) = 0;
            return;
        }
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
        Matrix4_Identity(scale);
        Mtx44_Scale_PerAxis(scale, scale, lbl_806D51C4, height * F(0x154), lbl_806D51C4);
        Matrix4_Multiply(root, scale, root);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, root);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    }
}
