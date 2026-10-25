/* EffectVfx72_ItemStarAura_Tick (0x800C2124): star aura (resource 0x72) at
 * a kart hand joint; its size comes from a per-character table and it
 * fades out once its timer runs out. */
#include "game/DrawEffectAccess.h"

extern int g_kartVariant;
extern int g_gameMode;
extern int g_cupId;
extern const float lbl_806D5348; /* pi */
extern const float lbl_806D53D4; /* -35.0 */
extern const float lbl_8032A21C[];
extern unsigned char *PcbSlot_GetByIndex(int pcbIdx);
extern void EffectVfx_KartChildAttached_RenderHook(unsigned char *self);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);

static inline float ItemStarAura_GetPitch(unsigned char *driver)
{
    float pitch;

    if (driver == 0) {
        return 0.0f;
    }
    if (g_kartVariant < 2) {
        return 1.0f;
    }
    pitch = 0.0f;
    if (*(int *)(driver + 0x1F8) == 11) {
        pitch = lbl_806D53D4;
    }
    return pitch;
}

static inline int ItemStarAura_GetCharacter(unsigned char *driver)
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

void EffectVfx72_ItemStarAura_Tick(unsigned char *self)
{
    float root[4][4];
    Vec trans;
    Vec local;
    Vec pos;

    if (I(0x10) == 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetJointByIdx(P(0x11C), 0xA));
    } else {
        Mtx_TransposeToMtx44(root, KartDriver_GetJointByIdx(P(0x11C), 0xB));
    }
    Mtx44_GetTranslation_ColMajor(&trans, root);

    switch (STATE) {
    case 0: {
        float pitch;
        int character;

        VfxSlot_BindResourceEx(SLOT(self), 0x72, 0);
        *(void (**)(unsigned char *))(self + 0x78) = EffectVfx_KartChildAttached_RenderHook;
        F(0xA0) = 0.017453292f * Rand_RangeFloat(-180.0f, 180.0f);
        GetSpawnPosition(V(0xA4), 0.0f, 0.0f, 1.0f);
        Vec2_RotateY(V(0xA4), V(0xA4), lbl_806D5348);
        pitch = ItemStarAura_GetPitch(P(0x11C));
        if (0.0f != pitch) {
            Vec2_RotateX(V(0xA4), V(0xA4), 0.017453292f * pitch);
        }
        if (S8(0x190)) {
            Vec3_Scale(V(0xA4), V(0xA4), 1.5f);
        }
        local = *V(0xA4);
        Mtx44_TransformVec3(V(0xA4), root, &local);
        Vec3_Subtract_DestFirst(V(0xA4), V(0xA4), &trans);
        GetSpawnPosition(V(0x120), 0.0f, 0.0f, 0.0f);
        F(0x150) = Rand_RangeFloat(0.8f, 1.2f);
        character = ItemStarAura_GetCharacter(P(0x11C));
        F(0x154) = character < 0 ? 1.0f : lbl_8032A21C[character];
        F(0xB0) = F(0x150) * F(0x154);
        if (S8(0x190)) {
            F(0x150) *= 1.5f;
        }
        F(0x2C) = 1.0f;
        U32(0x180) = 3;
        STATE++;
    }
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        F(0x154) -= 0.15f;
        if (F(0x154) <= 0.0f) {
            U8(0x28) = 0;
            DrawEffect_Free(self);
            return;
        }
    }
    if (!S8(0x190)) {
        F(0x2C) = 0.5f * F(0xB0);
    } else {
        F(0x2C) = F(0xB0);
    }
    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    Vec3_Add_DestFirst(V(0x8C), &trans, V(0x120));
    F(0xB0) = F(0x150) * F(0x154);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
