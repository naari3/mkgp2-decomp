/* Active (attached to kart) state for the Onchi Speaker item. */
#include "game/objview/item_state_private.h"

typedef struct OnchiEffect {
    unsigned char pad0[0x8c];
    Vec3 pos;
    unsigned char pad98[0xcc - 0x98];
    Item *item;
    unsigned char padd0[0x11c - 0xd0];
    void *driver;
} OnchiEffect;

typedef struct OnchiDriverInput {
    unsigned char pad0[0x10];
    unsigned long long buttons;
} OnchiDriverInput;

typedef struct OnchiDriver {
    unsigned char pad0[0x304];
    OnchiDriverInput *input;
} OnchiDriver;

typedef struct OnchiActiveState {
    unsigned char pad0[4];
    unsigned int timer;
    unsigned int holdTimer;
    unsigned int smokeTimer;
    unsigned char pad10[4];
    float blend;
    float wobble;
    unsigned char pad1c[0x34 - 0x1c];
    Vec3 offset;
    Vec3 delta;
    OnchiEffect *effect;
    unsigned char pad50[0x9c - 0x50];
    OnchiDriver *driver;
} OnchiActiveState;

extern float BuildOrientationFromYaw(float);
extern void DrawEffect_Free(OnchiEffect *);
extern OnchiEffect *DrawEffect_SpawnDirect(void *);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern void Item_DecayVelocityScalar(Item *, float);
extern void JointByName_GetWorldPosition(Vec3 *, void *, const char *);
extern void *KartDriver_GetKartRootMtx(void *);
extern float KartFxParam_GetConst1p5(void *);
extern void Mtx44_GetTranslation_ColMajor(Vec3 *, float (*)[4]);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void Mtx44_TransformVec3(Vec3 *, float (*)[4], Vec3);
extern void Mtx_TransposeToMtx44(float (*)[4], void *);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *, int, float);
extern void SpriteSlot_SetScale(void *, float);
extern void Vec2_RotateY(Vec3 *, Vec3 *, float);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern float Vec3_HorizontalYawTo(Vec3 *, Vec3 *);
extern void Vec3_Lerp(Vec3 *, Vec3, Vec3, float);
extern void Vec3_Subtract_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern double sin(double);

extern void DrawEffect_Cb_KartWheelSmokeOrbital_Tick();
extern void DrawEffect_Cb_UVScroll_Tick();
extern const Vec3 OnchiSpeaker_State2_Active_rodata_8032F4F8;
extern const char lbl_8032F504[];
extern const float lbl_806D5F18, lbl_806D5F2C, lbl_806D5F30;
extern const float lbl_806D5F34, lbl_806D5F38, lbl_806D5F3C, lbl_806D5F40;
extern const float lbl_806D5F44;

#pragma exceptions on
void OnchiSpeaker_State2_Active(Item *item, OnchiActiveState *state)
{
    float m[4][4];
    Vec3 root;
    Vec3 local;
    Vec3 kart;
    OnchiEffect *smoke;
    OnchiDriverInput *input;
    float yaw;

    switch (item->subphase) {
    case 0:
        item->subphase++;
        item->step = 0;
    case 1:
        switch (item->step) {
        case 0:
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 2, lbl_806D5F18);
            SpriteSlot_SetScale(item->sprite, 1.0f);
            GetSpawnPosition(&item->velocity, lbl_806D5F18, lbl_806D5F18, lbl_806D5F18);
            item->x3c = 0;
            state->blend = lbl_806D5F18;
            state->wobble = lbl_806D5F18;
            state->timer = 1800;
            state->holdTimer = 10;
            state->smokeTimer = 0;
            state->effect = DrawEffect_SpawnDirect(DrawEffect_Cb_UVScroll_Tick);
            if (state->effect) {
                state->effect->driver = state->driver;
                state->effect->item = item;
            }
            item->step++;
            break;
        case 1:
            break;
        }
        if (FinalLapCoinJump_CheckActiveForObject(state->driver)) {
            item->visible = 0;
        } else {
            item->visible = 1;
        }
        if (state->timer == 0) {
            item->scale -= lbl_806D5F2C;
            if (item->scale < lbl_806D5F18) {
                item->visible = 0;
                DrawEffect_Free(state->effect);
                state->effect = 0;
                item->phase = 3;
                item->subphase = 0;
                break;
            }
        } else if (state->smokeTimer == 0) {
            smoke = DrawEffect_SpawnDirect(DrawEffect_Cb_KartWheelSmokeOrbital_Tick);
            if (smoke) {
                JointByName_GetWorldPosition(&smoke->pos, item->sprite, lbl_8032F504);
                smoke->driver = state->driver;
            }
            state->smokeTimer = 10;
        }
        Item_DecayVelocityScalar(item, lbl_806D5F30 * KartFxParam_GetConst1p5(state->driver));
        state->blend += lbl_806D5F2C;
        if (1.0f < state->blend) {
            state->blend = 1.0f;
        }
        state->wobble = BuildOrientationFromYaw(lbl_806D5F34 + state->wobble);
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(state->driver));
        Mtx44_GetTranslation_ColMajor(&root, m);
        local = OnchiSpeaker_State2_Active_rodata_8032F4F8;
        Vec2_RotateY(&local, &local, lbl_806D5F38 * (float)sin(state->wobble));
        Mtx44_TransformVec3(&local, m, local);
        yaw = Vec3_HorizontalYawTo(&item->pos, &root);
        Vec3_Lerp(&item->pos, local, item->pos, state->blend);
        item->rotation.x = BuildOrientationFromYaw(lbl_806D5F18 * state->blend + item->rotation.x * (1.0f - state->blend));
        item->rotation.y = BuildOrientationFromYaw(yaw * state->blend + item->rotation.y * (1.0f - state->blend));
        if (state->holdTimer == 0) {
            input = state->driver->input;
            if ((input->buttons & 0x02000000ULL) == 0) {
                state->timer = 0;
            }
            if (input->buttons & 0x00010000ULL) {
                DrawEffect_Free(state->effect);
                state->effect = 0;
                item->subphase = 2;
                item->step = 0;
            }
        }
        break;
    case 2:
        Mtx44_GetTranslation_RowMajor(&kart, KartDriver_GetKartRootMtx(state->driver));
        switch (item->step) {
        case 0:
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D5F18);
            SpriteSlot_SetScale(item->sprite, 1.0f);
            Vec3_Subtract_DestFirst(&state->offset, &item->pos, &kart);
            GetSpawnPosition(&state->delta, lbl_806D5F18, lbl_806D5F3C, lbl_806D5F18);
            item->step++;
            break;
        case 1:
            break;
        }
        item->scale -= lbl_806D5F2C;
        if (item->scale < lbl_806D5F18) {
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
            break;
        }
        item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D5F40);
        Item_DecayVelocityScalar(item, lbl_806D5F30 * KartFxParam_GetConst1p5(state->driver));
        state->delta.y += lbl_806D5F44;
        Vec3_Add_DestFirst(&state->offset, &state->offset, &state->delta);
        Vec3_Add_DestFirst(&item->pos, &kart, &state->offset);
        break;
    }
}
#pragma exceptions reset
