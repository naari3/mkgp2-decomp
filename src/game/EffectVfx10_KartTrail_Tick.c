/* EffectVfx10_KartTrail_Tick (0x800BD900): kart trail ribbon (resource 0xA)
 * behind the kart. It fades with the linked item's speed, scrolls its UVs
 * with the lateral slide, and is sized by a per-character table.
 * The owned parameter pool reproduces the target's section-relative table
 * addressing. NonMatching: pool/item remain in r31/r30 rather than r30/r31. */
#include "game/DrawEffectAccess.h"

extern int g_kartVariant;
extern int g_gameMode;
extern int g_cupId;
extern const float lbl_806D5348; /* pi */
/* Shared effect parameter pool, addressed from one section base. */
const float lbl_80329E20[255] = {
    1.0f, 0.699999988f, 0.899999976f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f,
};
const float lbl_8032A21C[15] = { 1.79999995f, 1.5f, 1.0f, 1.10000002f, 1.0f, 1.10000002f, 1.29999995f, 1.0f, 1.79999995f, 1.0f, 1.0f, 1.79999995f, 1.79999995f, 0.0f, 0.0f };
const float lbl_8032A258[15] = { 1.5f, 1.10000002f, 1.0f, 1.0f, 1.04999995f, 1.0f, 1.12f, 0.949999988f, 1.0f, 1.10000002f, 1.0f, 2.79999995f, 1.20000005f, 0.0f, 0.0f };
const float lbl_8032A294[15] = { 1.39999998f, 1.10000002f, 1.10000002f, 1.10000002f, 1.10000002f, 1.0f, 1.5f, 1.0f, 1.20000005f, 1.39999998f, 0.200000003f, 1.39999998f, 0.800000012f, 0.0f, 0.0f };
const float lbl_8032A2D0[15] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.29999995f, 1.0f, 0.0f, 0.0f };
const float lbl_8032A30C[15] = {
    1.05999994f, 1.10000002f, 1.0f, 1.01999998f, 1.0f, 1.04999995f, 1.0f, 1.0f, 1.01999998f, 1.0f, 1.0f, 1.08000004f, 1.0f, 0.0f, 0.0f,
};
const Vec lbl_8032A348[3] = {
    { 1.0f, 0.200000003f, 0.200000003f },
    { 1.20000005f, 0.400000006f, 0.400000006f },
    { 0.800000012f, 0.600000024f, 0.0f },
};
const struct { float scales[26]; unsigned int flags[2]; float values[6]; } lbl_8032A36C = {
    { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.60000002f },
    { 1, 1 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
};
const Vec lbl_8032A3F4 = { 0.0f, 0.0f, -10.0f };
const Vec lbl_8032A400 = { -2.0f, 0.0f, 0.0f };
const Vec lbl_8032A40C = { 2.0f, 0.0f, 0.0f };
const Vec lbl_8032A418 = { 0.0f, 0.0f, 0.0f };
const Vec lbl_8032A424 = { 0.0f, 0.0f, -7.0f };

extern const Vec lbl_8041A274;
extern unsigned char *PcbSlot_GetByIndex(int pcbIdx);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern void VfxSlot_SetUVScroll(void *slot, float u, float v);
extern void Matrix4_Copy(float dst[4][4], float src[4][4]);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float angle);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
extern void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float sx, float sy, float sz);

static inline int KartTrail_GetCharacter(unsigned char *driver)
{
    int slot;
    int character;

    if (driver == 0) {
        return -1;
    }
    slot = *(int *)(driver + 0x1F4);
    if (slot < 0 || slot > 3) {
        return -1;
    }
    if (g_gameMode == 2) {
        if (((unsigned int)PcbSlot_GetByIndex(slot)[6] >> 1 & 3) < 2) {
            return -1;
        }
    } else {
        if (g_kartVariant < 2) {
            return -1;
        }
        if (g_cupId >= 9) {
            return -1;
        }
    }
    character = *(int *)(driver + 0x1F8);
    if (character < 0 || character >= 15) {
        return -1;
    }
    return character;
}

void EffectVfx10_KartTrail_Tick(unsigned char *self)
{
    float root[4][4];
    float m[4][4];
    float t[4][4];
    Vec slide;
    Vec off;
    unsigned char *item;

    item = P(0xDC);

    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));

    switch (STATE) {
    case 0: {
        int character;

        VfxSlot_BindResource(SLOT(self), 0xA);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        F(0x150) = 0.0f;
        F(0x154) = 0.0f;
        if (KartTrail_GetCharacter(P(0x11C)) >= 0) {
            const Vec *color = &lbl_8032A348[0];
            F(0x30) = color->x;
            F(0x34) = color->y;
            F(0x38) = color->z;
        }
        STATE++;
        S8(0x190) = 0;
        character = KartTrail_GetCharacter(P(0x11C));
        F(0x158) = character < 0 ? 1.0f : lbl_8032A294[character];
    }
    case 1:
        break;
    }

    if (0.1f <= *(float *)(item + 0x108)) {
        F(0x150) += 0.1f;
        if (1.0f < F(0x150)) {
            F(0x150) = 1.0f;
        }
        S8(0x190) = 1;
    } else {
        F(0x150) -= 0.05f;
        if (F(0x150) < 0.0f) {
            F(0x150) = 0.0f;
            S8(0x190) = 0;
        }
    }
    F(0x2C) = F(0x150);
    if (S8(0x190)) {
        if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
            U8(0x28) = 0;
        } else {
            U8(0x28) = 1;
        }
    } else {
        U8(0x28) = 0;
    }

    if (S8(0x28)) {
        Vec2_RotateY(&slide, V_(item, 0xE4), -Mtx44_GetYawOfPosZ(root));
        if (slide.x < 0.0f) {
            F(0x154) += 0.05f;
            if (1.0f < F(0x154)) {
                F(0x154) = 1.0f;
            }
        } else {
            F(0x154) -= 0.05f;
            if (F(0x154) < -1.0f) {
                F(0x154) = -1.0f;
            }
        }
        VfxSlot_SetUVScroll(SLOT(self), 0.05f * F(0x154), 0.0f);
    }

    F(0xB0) = 1.5f * F(0x158);
    if (S8(0x28)) {
        off = lbl_8032A418;
        off.z = -8.0f * F(0x158);
        Matrix4_Copy(m, root);
        Matrix4_Identity(t);
        Matrix4_PreMultiplyRotY(t, t, lbl_806D5348);
        Mtx44_Translate(t, t, off);
        Matrix4_Multiply(m, t, m);
        Matrix4_Identity(t);
        Mtx44_Scale_PerAxis(t, t, F(0xB0) * lbl_8041A274.x, F(0xB0) * lbl_8041A274.y, F(0xB0) * lbl_8041A274.z);
        Matrix4_Multiply(m, t, m);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    }
}
