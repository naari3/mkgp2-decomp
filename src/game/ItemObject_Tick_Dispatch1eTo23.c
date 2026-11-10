/* ItemObject_Tick_Dispatch1eTo23 (0x800E1E70): handheld item kinds
 * 0x1E..0x23. The item stays in the character's hand with a per-kind
 * offset/rotation (kind 0x21 spins) until the hold flag 0x18C is set, and a
 * child effect follows it each frame. */
#include "game/types/Vec.h"

#include "game/types/HandheldPose.h"

extern HandheldPose ItemObject_Tick_Dispatch1eTo23_data_80420D58[];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_InitLoop(void *slot, int id);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_TickAnim(void *slot);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_SparkSprayCompound_Init(unsigned char *self);
extern void Effect_BindRes31or34_Init(unsigned char *self);
extern float BuildOrientationFromYaw(float yaw);
#ifdef __MWERKS__
extern void Item_RenderHandheldByCharacter(unsigned char *self, Vec ofs, Vec rot, int c, float d);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Item_RenderHandheldByCharacter(unsigned char *, Vec *, Vec *, int, float);
static inline void Item_RenderHandheldByCharacter_ByValue(unsigned char *self, Vec ofs, Vec rot, int c, float d) { Item_RenderHandheldByCharacter(self, &ofs, &rot, c, d); }
#define Item_RenderHandheldByCharacter Item_RenderHandheldByCharacter_ByValue
#endif
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
#ifdef __MWERKS__
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec *, float m[4][4], Vec *);
static inline void Mtx44_TransformVec3_ByValue(Vec *out, float m[4][4], Vec in) { Mtx44_TransformVec3(out, m, &in); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
#ifdef __MWERKS__
extern void Effect_TwoChildPlace_AndForward_E4(unsigned char *e, Vec pos, float scale, float alpha);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Effect_TwoChildPlace_AndForward_E4(unsigned char *, Vec *, float, float);
static inline void Effect_TwoChildPlace_AndForward_E4_ByValue(unsigned char *e, Vec pos, float scale, float alpha) { Effect_TwoChildPlace_AndForward_E4(e, &pos, scale, alpha); }
#define Effect_TwoChildPlace_AndForward_E4 Effect_TwoChildPlace_AndForward_E4_ByValue
#endif
#ifdef __MWERKS__
extern void Effect_ApplyUvScrollAlong_E4(unsigned char *e, Vec pos, float scale, float alpha);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Effect_ApplyUvScrollAlong_E4(unsigned char *, Vec *, float, float);
static inline void Effect_ApplyUvScrollAlong_E4_ByValue(unsigned char *e, Vec pos, float scale, float alpha) { Effect_ApplyUvScrollAlong_E4(e, &pos, scale, alpha); }
#define Effect_ApplyUvScrollAlong_E4 Effect_ApplyUvScrollAlong_E4_ByValue
#endif

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))

void ItemObject_Tick_Dispatch1eTo23(unsigned char *self)
{
    float m[4][4];
    Vec rot;
    Vec v;

    switch (S8(0xC8)) {
    case 0:
        switch (I(0x8)) {
        case 0x1E:
            I(0x10) = 0;
            break;
        case 0x1F:
            I(0x10) = 1;
            break;
        case 0x20:
            I(0x10) = 2;
            break;
        case 0x21:
            I(0x10) = 3;
            break;
        case 0x22:
            I(0x10) = 4;
            break;
        case 0x23:
            I(0x10) = 5;
            break;
        }
        switch (I(0x8)) {
        case 0x1E:
            SpriteSlot_InitNonLoop(self + 0x14, 0x1E);
            break;
        case 0x1F:
            SpriteSlot_InitNonLoop(self + 0x14, 0x1F);
            break;
        case 0x20:
            SpriteSlot_InitNonLoop(self + 0x14, 0x20);
            break;
        case 0x21:
            SpriteSlot_InitNonLoop(self + 0x14, 0x21);
            break;
        case 0x22:
            SpriteSlot_InitLoop(self + 0x14, 0x22);
            break;
        case 0x23:
            SpriteSlot_InitLoop(self + 0x14, 0x23);
            break;
        }
        self[0x14] = 4;
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        F(0x2C) = 0.0f;
        F(0x100) = 0.0f;
        switch (I(0x8)) {
        case 0x1E:
        case 0x1F:
        case 0x20:
            P(0x138) = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Init);
            break;
        case 0x21:
            break;
        case 0x22:
        case 0x23:
            P(0x138) = DrawEffect_SpawnDirect(Effect_BindRes31or34_Init);
            if (P(0x138) != 0 && I(0x8) == 0x23) {
                *(int *)(P(0x138) + 0x10) = 1;
            }
            break;
        }
        S8(0xC8) = 1;
    case 1:
        break;
    }

    if (S8(0x18C)) {
        if (P(0x138) != 0) {
            *(signed char *)(P(0x138) + 0xC9) = 1;
        }
        P(0x138) = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    F(0x2C) += 0.1f;
    if (1.0f < F(0x2C)) {
        F(0x2C) = 1.0f;
    }
    rot.x = 0.017453289f * ItemObject_Tick_Dispatch1eTo23_data_80420D58[I(0x10)].rot.x;
    rot.y = 0.017453289f * ItemObject_Tick_Dispatch1eTo23_data_80420D58[I(0x10)].rot.y;
    rot.z = 0.017453289f * ItemObject_Tick_Dispatch1eTo23_data_80420D58[I(0x10)].rot.z;
    if (I(0x8) == 0x21) {
        F(0x100) = BuildOrientationFromYaw(0.08726645f + F(0x100));
        rot.y = BuildOrientationFromYaw(rot.y + F(0x100));
    }
    Item_RenderHandheldByCharacter(self, ItemObject_Tick_Dispatch1eTo23_data_80420D58[I(0x10)].ofs, rot, 0, ItemObject_Tick_Dispatch1eTo23_data_80420D58[I(0x10)].scale);
    if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    SpriteSlot_TickAnim(self + 0x14);
    Mtx_TransposeToMtx44(m, self + 0x48);
    if (P(0x138) != 0) {
        switch (I(0x8)) {
        case 0x1E:
            GetSpawnPosition(&v, 0.0f, 1.0f, 0.0f);
            Mtx44_TransformVec3(&v, m, v);
            if (S8(0x28)) {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), v, 2.0f * F(0xC4), F(0x2C));
            } else {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), v, 2.0f * F(0xC4), 0.0f);
            }
            break;
        case 0x1F:
            if (S8(0x28)) {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), *(Vec *)(self + 0xA0), 2.6f * F(0xC4), F(0x2C));
            } else {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), *(Vec *)(self + 0xA0), 2.6f * F(0xC4), 0.0f);
            }
            break;
        case 0x20:
            GetSpawnPosition(&v, 0.0f, 4.0f, 0.0f);
            Mtx44_TransformVec3(&v, m, v);
            if (S8(0x28)) {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), v, 1.1f * (4.0f * F(0xC4)), F(0x2C));
            } else {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), v, 1.1f * (4.0f * F(0xC4)), 0.0f);
            }
            break;
        case 0x22:
        case 0x23:
            if (S8(0x28)) {
                Effect_ApplyUvScrollAlong_E4(P(0x138), *(Vec *)(self + 0xA0), 1.3 * F(0xC4), F(0x2C));
            } else {
                Effect_ApplyUvScrollAlong_E4(P(0x138), *(Vec *)(self + 0xA0), 1.3 * F(0xC4), 0.0f);
            }
            break;
        }
    }
}
