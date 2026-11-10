#include "game/types/Vec3.h"

typedef struct SparkOffsets {
    Vec3 hand;
    Vec3 handRot;
    Vec3 spark;
} SparkOffsets;

extern void Effect_SparkSprayCompound_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Effect_SparkSpray_PlaceChildren(unsigned char *effect, Vec3 pos, float scale, float alpha);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_RenderHandheldByCharacter(unsigned char *self, Vec3 pos, Vec3 rot, int flag, float scale);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_Inverse_GaussJordan(float *dst, float *src);
extern void Mtx44_TransformVec3(void *out, float *m, Vec3 v);
extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void SpriteSlot_Container_Free(unsigned char *self);
extern void SpriteSlot_InitNonLoop(unsigned char *slot, unsigned char id);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(unsigned char *slot, int enabled);
extern void SpriteSlot_SetTransform(unsigned char *slot, Vec3 pos, Vec3 rot, float scale);
extern void Vec3_Add_DestFirst(Vec3 *dst, void *a, void *b);
extern void fn_80112BE4(unsigned char *self, unsigned char *ctx);
extern unsigned int lbl_806CF3E8;
extern float lbl_806CF3EC;
extern float lbl_806CF3F0;
extern const float lbl_806D69A8;
extern const float lbl_806D69BC;
extern SparkOffsets lbl_80421DA0;

static inline void HeldTick(unsigned char *self, unsigned char *ctx, SparkOffsets *offsets)
{
    Item_RenderHandheldByCharacter(self, offsets->hand, offsets->handRot, 1, lbl_806CF3EC);
    switch ((signed char)ctx[0xA0]) {
    case 1:
        ctx[0xA0] = 0;
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
        *(float *)(self + 0x2C) = lbl_806D69BC;
        if (*(void **)(ctx + 0x98)) {
            float m[16];
            Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x98)));
            Mtx44_Inverse_GaussJordan(m, m);
            Mtx44_TransformVec3(ctx + 0x34, m, *(Vec3 *)(self + 0xA0));
        }
        self[0xC8] = 2;
        self[0xC9] = 0;
        break;
    case 2:
        ctx[0xA0] = 0;
        self[0xC8] = 3;
        self[0xC9] = 0;
        break;
    }
}

void fn_80112DDC(unsigned char *self)
{
    SparkOffsets *offsets = &lbl_80421DA0;
    unsigned char *ctx = self + 0xEC;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, lbl_806CF3E8);
        *(float *)(self + 0x2C) = lbl_806D69A8;
        *(unsigned char **)(ctx + 0x4C) = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Update);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        HeldTick(self, ctx, offsets);
        break;
    case 2:
        fn_80112BE4(self, ctx);
        break;
    case 3:
        if (*(unsigned char **)(ctx + 0x4C)) {
            (*(unsigned char **)(ctx + 0x4C))[0xC9] = 1;
        }
        *(unsigned char **)(ctx + 0x4C) = 0;
        SpriteSlot_Container_Free(self);
        return;
    }
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(ctx + 0x98))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    SpriteSlot_SetTransform(self + 0x14, *(Vec3 *)(self + 0xA0), *(Vec3 *)(self + 0xAC), *(float *)(self + 0xC4));
    if (*(unsigned char **)(ctx + 0x4C)) {
        Vec3 pos;
        Vec3_Add_DestFirst(&pos, self + 0xA0, &offsets->spark);
        if (*(signed char *)(self + 0x28)) {
            Effect_SparkSpray_PlaceChildren(*(unsigned char **)(ctx + 0x4C), pos, *(float *)(self + 0xC4) * lbl_806CF3F0, *(float *)(self + 0x2C));
        } else {
            Effect_SparkSpray_PlaceChildren(*(unsigned char **)(ctx + 0x4C), pos, *(float *)(self + 0xC4) * lbl_806CF3F0, lbl_806D69A8);
        }
    }
    if (*(unsigned int *)(ctx + 0x4)) (*(unsigned int *)(ctx + 0x4))--;
    if (*(unsigned int *)(ctx + 0x8)) (*(unsigned int *)(ctx + 0x8))--;
    if (*(unsigned int *)(ctx + 0xC)) (*(unsigned int *)(ctx + 0xC))--;
    if (*(unsigned int *)(ctx + 0x10)) (*(unsigned int *)(ctx + 0x10))--;
}
