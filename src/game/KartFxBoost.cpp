/* Boost callbacks; local field views are limited to the observed ABI. */
#include "game/types/Vec3.h"
#include "game/types/Mtx44.h"
struct BoostFlags { unsigned char pad00[0x10]; unsigned long long bits; };
#include "game/types/BoostKart.h"
struct BoostEffect;
struct BoostPayload {
    unsigned char pad00[0x10];
    BoostEffect *children[3];
    unsigned char pad1C[0x34];
    BoostKart *kart;
    unsigned char pad54[0x30];
    float phase;
    unsigned char pad88[0x2C];
    unsigned int timer0, timer1, timer2, timer3;
};
struct BoostEffect {
    unsigned char pad00[0x10];
    int side;
    unsigned char slot[0x14];
    unsigned char active;
    unsigned char pad29[3];
    float opacity;
    unsigned char pad30[0x5C];
    Vec3 position;
    Vec3 rotation;
    unsigned char padA4[0xC];
    float scale;
    signed char state;
    unsigned char padB5[0x14];
    signed char destroy;
    unsigned char padCA[2];
    BoostPayload payload;
};
struct BoostResources {
    unsigned char pad00[0x7A0];
    Vec3 yaw;
    Vec3 pitch;
    Vec3 offsets[11];
};
struct BoostCamera { unsigned char pad00[0x80]; Vec3 position; };
extern "C" {
extern BoostResources KartFxExhaustRay_rodata_80329E20;
extern BoostCamera lbl_805DF3D0;
extern float lbl_806D51C0;
extern const float lbl_806D51BC, lbl_806D51C4, lbl_806D51C8;
extern const float lbl_806D51D8, lbl_806D527C, lbl_806D52BC, lbl_806D52C0;
extern const float lbl_806D52C4, lbl_806D52C8;
void VfxSlot_BindResourceEx(void *, unsigned char, int);
#ifdef __MWERKS__
void VfxSlot_SetPositionFromVec(void *, Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlot_SetPositionFromVec(void *, Vec3 *);
static inline void VfxSlot_SetPositionFromVec_ByValue(void *a0, Vec3 a1) { VfxSlot_SetPositionFromVec(a0, &a1); }
#define VfxSlot_SetPositionFromVec VfxSlot_SetPositionFromVec_ByValue
#endif
void VfxSlot_SetScaleUniform(void *, float);
void VfxSlot_SetRotationZ(void *, float);
void DrawEffect_Free(BoostEffect *);
BoostEffect *DrawEffect_SpawnDirect(void (*)(BoostEffect *));
void fn_800AF4F8(BoostEffect *);
void *KartDriver_GetJointByIdx(BoostKart *, int);
void *KartDriver_GetKartRootMtx(BoostKart *);
float Mtx44_GetYawOfPosZ_Padded(void *);
void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
void Mtx_TransposeToMtx44(Mtx44 *, void *);
#ifdef __MWERKS__
void Mtx44_TransformVec3(Vec3 *, const Mtx44 *, Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec3 *, const Mtx44 *, Vec3 *);
static inline void Mtx44_TransformVec3_ByValue(Vec3 *a0, const Mtx44 *a1, Vec3 a2) { Mtx44_TransformVec3(a0, a1, &a2); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
void Vec3_Copy(Vec3 *, const Vec3 *);
void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
float Vec3_Magnitude_Wrapper(const Vec3 *);
void Vec3_Scale(Vec3 *, const Vec3 *, float);
void GetSpawnPosition(Vec3 *, float, float, float);
void Vec2_RotateX(Vec3 *, const Vec3 *, float);
void Vec2_RotateY(Vec3 *, const Vec3 *, float);
float BuildOrientationFromYaw(float);
float KartCharacterParam_GetBoostFxSizeFactor(BoostKart *);
int KartCharacterParam_GetIdentityIndex(BoostKart *);
unsigned char FinalLapCoinJump_CheckActiveForObject(BoostKart *);

#ifndef BOOST_FLAME_ONLY
static inline void FreeBoostChildren(BoostPayload *payload) {
    int i;
    BoostPayload *walker = payload;
    for (i = 0; i < 3; ++i) {
        DrawEffect_Free(walker->children[0]);
        walker->children[0] = 0;
        walker = (BoostPayload *)((unsigned char *)walker + 4);
    }
}

void KartFx_Slot5C_TripleStreakTick(BoostEffect *effect) {
    BoostResources *resources = &KartFxExhaustRay_rodata_80329E20;
    int childIndex;
    BoostPayload *payload = &effect->payload;
    switch (effect->state) {
    case 0: {
        for (int i = 0; i < 3; ++i) {
            payload->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (payload->children[i])
                VfxSlot_BindResourceEx(payload->children[i]->slot, 0x11, 0);
        }
        float zero = lbl_806D51C0;
        payload->phase = zero;
        effect->opacity = zero;
        effect->active = 0;
        payload->timer0 = 0;
        ++effect->state;
        break;
    }
    case 1: break;
    }
    if (effect->destroy) {
        FreeBoostChildren(payload);
        DrawEffect_Free(effect);
        return;
    }
    if ((payload->kart->flags->bits & 0x0200000000000000ULL) != 0)
        payload->timer0 = 120;
    if (payload->timer0) effect->opacity = lbl_806D51C4;
    else {
        float current = effect->opacity;
        float decrement = lbl_806D51D8;
        float minimum = 0.0f;
        float faded = current - decrement;
        effect->opacity = faded;
        if (effect->opacity < minimum) effect->opacity = minimum;
    }
    if (effect->opacity != lbl_806D51C0) {
        if (FinalLapCoinJump_CheckActiveForObject(payload->kart)) effect->active = 0;
        else effect->active = 1;
    } else effect->active = 0;
    effect->scale = KartCharacterParam_GetBoostFxSizeFactor(payload->kart);
    effect->rotation.y = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(payload->kart));
    payload->phase = BuildOrientationFromYaw(lbl_806D52BC + payload->phase);
    for (childIndex = 0; childIndex < 3; ++childIndex) {
        Vec3 yaw = resources->yaw;
        Vec3 pitch = resources->pitch;
        struct OffsetTable { Vec3 entries[11]; };
        OffsetTable offsets = *(const OffsetTable *)resources->offsets;
        Vec3 offset;
        Vec3 position;
        Mtx44 matrix;
        Vec3_Copy(&offset, &offsets.entries[KartCharacterParam_GetIdentityIndex(payload->kart)]);
        GetSpawnPosition(&position, lbl_806D51C0, lbl_806D51C0, offset.z);
        Vec3_Scale(&position, &position, effect->scale);
        Vec2_RotateY(&position, &position,
            BuildOrientationFromYaw(payload->phase + effect->rotation.y + (&yaw.x)[childIndex]));
        Vec2_RotateX(&position, &position, (&pitch.x)[childIndex]);
        position.y += offset.y;
        Mtx_TransposeToMtx44(&matrix, KartDriver_GetJointByIdx(payload->kart, 15));
        Mtx44_TransformVec3(&payload->children[childIndex]->position, &matrix, position);
        payload->children[childIndex]->scale = lbl_806D52C0;
        payload->children[childIndex]->opacity = effect->opacity;
        payload->children[childIndex]->active = effect->active;
        VfxSlot_SetPositionFromVec(payload->children[childIndex]->slot, payload->children[childIndex]->position);
        VfxSlot_SetScaleUniform(payload->children[childIndex]->slot, payload->children[childIndex]->scale);
    }
    if (payload->timer0) --payload->timer0;
    if (payload->timer1) --payload->timer1;
    if (payload->timer2) --payload->timer2;
    if (payload->timer3) --payload->timer3;
}

#endif
#ifdef BOOST_FLAME_ONLY
void KartFx_Slot57_BoostFlameTick(BoostEffect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0xD, 0);
        effect->payload.phase = lbl_806D51C0;
        if (effect->side == 0) effect->rotation.z = lbl_806D527C;
        else effect->rotation.z = lbl_806D52C4;
        ++effect->state;
        break;
    case 1: break;
    }
    effect->payload.phase += lbl_806D51C8;
    if (lbl_806D51C4 < effect->payload.phase) {
        DrawEffect_Free(effect);
        return;
    }
    Vec3 position;
    Vec3 direction;
    if (effect->side == 0)
        Mtx44_GetTranslation_RowMajor(&position, KartDriver_GetJointByIdx(effect->payload.kart, 6));
    else Mtx44_GetTranslation_RowMajor(&position, KartDriver_GetJointByIdx(effect->payload.kart, 7));
    Vec3_Subtract_DestFirst(&direction, &position, &lbl_805DF3D0.position);
    Vec3_Scale(&direction, &direction,
        lbl_806D52C8 * (lbl_806D51C4 / Vec3_Magnitude_Wrapper(&direction)));
    Vec3_Add_DestFirst(&position, &position, &direction);
    Vec3_Copy(&effect->position, &position);
    effect->scale = effect->payload.phase * KartCharacterParam_GetBoostFxSizeFactor(effect->payload.kart);
    effect->opacity = lbl_806D51BC * (lbl_806D51C4 - effect->payload.phase);
    if (lbl_806D51C4 < effect->opacity) effect->opacity = lbl_806D51C4;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->rotation.z);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (FinalLapCoinJump_CheckActiveForObject(effect->payload.kart)) effect->active = 0;
    else effect->active = 1;
}
#endif
}
