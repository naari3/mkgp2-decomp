/* KartFxExhaustRay + EffectVfx10_KartTrail_Tick (0x800BD1BC..0x800BDD74).
 * One TU: both functions address the shared parameter pool (.rodata
 * 0x80329E20..) through one section anchor (regalloc_patterns 13). */
#include "game/DrawEffectAccess.h"

extern int g_kartVariant;
extern int g_gameMode;
extern int g_cupId;
extern const float lbl_806D5348; /* pi */
/* Shared effect parameter pool, addressed from one section base. */
const float KartFxExhaustRay_rodata_80329E20[255] = {
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
const float EffectVfx72_ItemStarAura_Tick_rodata_8032A21C[15] = { 1.79999995f, 1.5f, 1.0f, 1.10000002f, 1.0f, 1.10000002f, 1.29999995f, 1.0f, 1.79999995f, 1.0f, 1.0f, 1.79999995f, 1.79999995f, 0.0f, 0.0f };
const float lbl_8032A258[15] = { 1.5f, 1.10000002f, 1.0f, 1.0f, 1.04999995f, 1.0f, 1.12f, 0.949999988f, 1.0f, 1.10000002f, 1.0f, 2.79999995f, 1.20000005f, 0.0f, 0.0f };
const float lbl_8032A294[15] = { 1.39999998f, 1.10000002f, 1.10000002f, 1.10000002f, 1.10000002f, 1.0f, 1.5f, 1.0f, 1.20000005f, 1.39999998f, 0.200000003f, 1.39999998f, 0.800000012f, 0.0f, 0.0f };
const float lbl_8032A2D0[15] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.29999995f, 1.0f, 0.0f, 0.0f };
const float KartFx_BurnoutChargeTick_rodata_8032A30C[15] = {
    1.05999994f, 1.10000002f, 1.0f, 1.01999998f, 1.0f, 1.04999995f, 1.0f, 1.0f, 1.01999998f, 1.0f, 1.0f, 1.08000004f, 1.0f, 0.0f, 0.0f,
};
const Vec EffectVfx9_DriftSpark_Tick_rodata_8032A348 = { 1.0f, 0.200000003f, 0.200000003f };
#include "game/types/RayColors.h"
const RayColors lbl_8032A354 = { {
    { 1.20000005f, 0.400000006f, 0.400000006f },
    { 0.800000012f, 0.600000024f, 0.0f },
} };
const struct { float scales[26]; unsigned int flags[2]; float values[6]; } EffectItemChainIndicator_Tick_rodata_8032A36C = {
    { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.60000002f },
    { 1, 1 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
};
const Vec EffectVfx6D_KartSmokeSpark_Tick_rodata_8032A3F4 = { 0.0f, 0.0f, -10.0f };
const Vec lbl_8032A400 = { -2.0f, 0.0f, 0.0f };
const Vec lbl_8032A40C = { 2.0f, 0.0f, 0.0f };
const Vec lbl_8032A418 = { 0.0f, 0.0f, 0.0f };
const Vec lbl_8032A424 = { 0.0f, 0.0f, -7.0f };

extern const Vec EffectVfx10_KartTrail_Tick_data_8041A274;
extern unsigned char *PcbSlot_GetByIndex(int pcbIdx);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern void VfxSlot_SetUVScroll(void *slot, float u, float v);
extern void Matrix4_Copy(float dst[4][4], float src[4][4]);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float angle);
#ifdef __MWERKS__
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec *);
static inline void Mtx44_Translate_ByValue(float dst[4][4], float src[4][4], Vec v) { Mtx44_Translate(dst, src, &v); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
extern void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float sx, float sy, float sz);


/* ---- KartFx_BoostExhaustRayTick (0x800BD1BC): boost exhaust ray ---- */
struct RayKart { unsigned char pad00[0x1F4]; int player, character; };
typedef struct RayEffect {
    unsigned char pad00[0x10]; int index;
    unsigned char slot[0x14], visible, pad29[3]; float opacity;
    Vec color; unsigned char pad3C[0xC]; float matrix[12];
    unsigned char pad78[0x14]; Vec position, rotation;
    unsigned char padA4[0xC]; float scale; signed char state;
    unsigned char padB5[0x67]; struct RayKart *kart; Vec anchor;
    unsigned char pad12C[0x24]; float intensity, growth, size;
    unsigned char pad15C[0x24]; unsigned int timer0, timer1, timer2, timer3;
    signed char special;
} RayEffect;
extern RayColors KartFx_BoostExhaustRayTick_data_8041A280[2];
extern signed char KartFx_BoostExhaustRayTick_bss_806D14B8;
extern const float lbl_806D51D4, lbl_806D52B8;
extern void Mtx44_GetTranslation_ColMajor(Vec *, float m[4][4]);
#ifdef __MWERKS__
extern void Mtx44_TransformVec3(Vec *, float m[4][4], Vec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec *, float m[4][4], Vec *);
static inline void Mtx44_TransformVec3_ByValue(Vec *a0, float m[4][4], Vec a2) { Mtx44_TransformVec3(a0, m, &a2); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
extern float Mtx44_GetPitchOfPosZ(float m[4][4]);
extern float Mtx44_GetPitchOfNegX_Lean(float m[4][4]);
#ifdef __MWERKS__
extern void Vec3_Lerp(Vec *, Vec, Vec, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Vec3_Lerp(Vec *, Vec *, Vec *, float);
static inline void Vec3_Lerp_ByValue(Vec *a0, Vec a1, Vec a2, float a3) { Vec3_Lerp(a0, &a1, &a2, a3); }
#define Vec3_Lerp Vec3_Lerp_ByValue
#endif
#ifdef __MWERKS__
extern signed char ItemObject_GetGroundTypeAt(Vec, float *, int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern signed char ItemObject_GetGroundTypeAt(Vec *, float *, int);
static inline signed char ItemObject_GetGroundTypeAt_ByValue(Vec a0, float *a1, int a2) { return ItemObject_GetGroundTypeAt(&a0, a1, a2); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
#ifdef __MWERKS__
extern float Item_ProbeForwardGroundPitch(Vec, float, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeForwardGroundPitch(Vec *, float, float, float);
static inline float Item_ProbeForwardGroundPitch_ByValue(Vec a0, float a1, float a2, float a3) { return Item_ProbeForwardGroundPitch(&a0, a1, a2, a3); }
#define Item_ProbeForwardGroundPitch Item_ProbeForwardGroundPitch_ByValue
#endif
#ifdef __MWERKS__
extern float Item_ProbeLateralGroundPitch(Vec, float, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeLateralGroundPitch(Vec *, float, float, float);
static inline float Item_ProbeLateralGroundPitch_ByValue(Vec a0, float a1, float a2, float a3) { return Item_ProbeLateralGroundPitch(&a0, a1, a2, a3); }
#define Item_ProbeLateralGroundPitch Item_ProbeLateralGroundPitch_ByValue
#endif
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float angle);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float angle);

static inline int CharacterIndex(struct RayKart *kart) {
    int index;
    if (!kart) return -1;
    if (kart->player < 0 || kart->player > 3) return -1;
    if (g_gameMode == 2) {
        if ((((unsigned int)PcbSlot_GetByIndex(kart->player)[6] >> 1) & 3U) < 2U) return -1;
    } else {
        if (g_kartVariant < 2) return -1;
        if (g_cupId >= 9) return -1;
    }
    index = kart->character;
    if (index < 0 || index >= 15) return -1;
    return index;
}

void KartFx_BoostExhaustRayTick(RayEffect *effect) {
    float offsetMatrix[4][4], root[4][4], matrix[4][4];
    Vec second, first, center, translation;
    Vec offset;
    float ground;
    float speed;
    Vec delta;
    float distance;
    float opacity;
    RayColors *colors;
    if (effect->index == 0) {
        Mtx44_GetTranslation_RowMajor(&first, KartDriver_GetJointByIdx(effect->kart, 0));
        Mtx44_GetTranslation_RowMajor(&second, KartDriver_GetJointByIdx(effect->kart, 1));
    } else {
        Mtx44_GetTranslation_RowMajor(&first, KartDriver_GetJointByIdx(effect->kart, 2));
        Mtx44_GetTranslation_RowMajor(&second, KartDriver_GetJointByIdx(effect->kart, 3));
    }
    Vec3_Lerp(&center, first, second, 0.5f);
    center.y -= 2.0f;
    if (effect->index != 0) {
        Mtx_TransposeToMtx44(offsetMatrix, KartDriver_GetKartRootMtx(effect->kart));
        Mtx44_GetTranslation_ColMajor(&translation, offsetMatrix);
        offset = lbl_8032A424;
        Mtx44_TransformVec3(&offset, offsetMatrix, offset);
        Vec3_Subtract_DestFirst(&offset, &offset, &translation);
        Vec3_Add_DestFirst(&center, &center, &offset);
    }
    if (effect->state == 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(effect->kart));
        effect->rotation.x = Mtx44_GetPitchOfPosZ(root);
        effect->rotation.y = Mtx44_GetYawOfPosZ(root);
        effect->rotation.z = Mtx44_GetPitchOfNegX_Lean(root);
    }
    switch (effect->state) {
    case 0: {
        int character;
        VfxSlot_BindResource(effect->slot, 11);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        Vec3_Copy(&effect->position, &center);
        effect->growth = 0.0f;
        character = CharacterIndex(effect->kart);
        effect->size = character < 0 ? 1.0f : lbl_8032A2D0[character];
        Vec3_Copy(&effect->anchor, &center);
        if (CharacterIndex(effect->kart) >= 0) effect->special = 1;
        else effect->special = 0;
        ++effect->state;
        break;
    }
    case 1: break;
    }
    if (effect->index != 0) speed = 5.0f * (4.0f * effect->growth);
    else speed = 5.0f * (4.0f * effect->growth);
    Vec3_Subtract_DestFirst(&delta, &effect->anchor, &center);
    distance = Vec3_Magnitude_Wrapper(&delta);
    if (speed < distance) {
        Vec3_Scale(&delta, &delta, (1.0f / distance) * speed);
        Vec3_Add_DestFirst(&effect->anchor, &center, &delta);
    }
    if (ItemObject_GetGroundTypeAt(effect->anchor, &ground, 0) != 0) {
        ground += 1.0f;
        if (effect->anchor.y < ground) {
            effect->anchor.y = ground;
            effect->rotation.x = Item_ProbeForwardGroundPitch(effect->anchor, effect->rotation.y, 5.0f, 1.0f);
            effect->rotation.z = Item_ProbeLateralGroundPitch(effect->anchor, effect->rotation.y, 5.0f, 1.0f);
        }
    }
    Vec3_Copy(&effect->position, &effect->anchor);
    effect->scale = effect->size;
    opacity = 2.0f * (1.0f - effect->growth);
    if (1.0f < opacity) opacity = 1.0f;
    if (effect->index == 0) effect->opacity = opacity;
    else effect->opacity = opacity;
    effect->opacity *= effect->intensity;
    if (!KartFx_BoostExhaustRayTick_bss_806D14B8) {
        KartFx_BoostExhaustRayTick_data_8041A280[1].entries[0] = lbl_8032A354.entries[0];
        KartFx_BoostExhaustRayTick_data_8041A280[1].entries[1] = lbl_8032A354.entries[1];
        KartFx_BoostExhaustRayTick_bss_806D14B8 = 1;
    }
    colors = &KartFx_BoostExhaustRayTick_data_8041A280[effect->special];
    Vec3_Lerp(&effect->color, colors->entries[1], colors->entries[0], effect->growth);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    if (effect->index == 0) effect->growth += lbl_806D51D4;
    else effect->growth += lbl_806D51D4;
    if (1.0f < effect->growth) { DrawEffect_Free(effect); return; }
    Matrix4_Identity(matrix);
    Mtx44_Scale_PerAxis(matrix, matrix, 2.0f * effect->scale, 2.0f * effect->scale, effect->scale);
    Matrix4_PreMultiplyRotY(matrix, matrix, lbl_806D5348);
    Matrix4_PreMultiplyRotX(matrix, matrix, lbl_806D52B8);
    Matrix4_PreMultiplyRotX(matrix, matrix, effect->rotation.x);
    Matrix4_PreMultiplyRotZ(matrix, matrix, effect->rotation.z);
    Matrix4_PreMultiplyRotY(matrix, matrix, effect->rotation.y);
    Mtx44_Translate(matrix, matrix, effect->position);
    DbgScene_CopyMatrix3x4Transpose(effect->matrix, matrix);
    if (effect->timer0) --effect->timer0;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
}

/* ---- EffectVfx10_KartTrail_Tick (0x800BD900) ---- */
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
            const Vec *color = &EffectVfx9_DriftSpark_Tick_rodata_8032A348;
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
        Mtx44_Scale_PerAxis(t, t, F(0xB0) * EffectVfx10_KartTrail_Tick_data_8041A274.x, F(0xB0) * EffectVfx10_KartTrail_Tick_data_8041A274.y, F(0xB0) * EffectVfx10_KartTrail_Tick_data_8041A274.z);
        Matrix4_Multiply(m, t, m);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    }
}
