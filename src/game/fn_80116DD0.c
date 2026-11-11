#include "game/types/AnimEntry.h"
/* --- owned .data 0x80421FE0..0x8042209C (tools/own_data.py) --- */
#pragma force_active on
unsigned int lbl_80421FE0[6] = { 0x00000000, 0x00000001, 0x0000000C, 0x0000002A, 0x0000003C, 0xFFFFFFFE };
unsigned int lbl_80421FF8[5] = { 0x3F19999A, 0x3F0CCCCD, 0x3EA8F5C3, 0x3F933333, 0x3F19999A };
unsigned int lbl_8042200C[6] = { 0x00000000, 0x00000001, 0x0000000F, 0x00000028, 0x0000003C, 0xFFFFFFFE };
unsigned int lbl_80422024[5] = { 0x3F4CCCCD, 0x3F5C28F6, 0x3F947AE1, 0x3ECCCCCD, 0x3F4CCCCD };
unsigned int lbl_80422038[6] = { 0x00000000, 0x00000001, 0x00000015, 0x0000002F, 0x0000003C, 0xFFFFFFFE };
unsigned int lbl_80422050[5] = { 0x3F0F5C29, 0x3F0F5C29, 0x3F6147AE, 0x3EB851EC, 0x3F0F5C29 };
AnimEntry lbl_80422064[7] = {
    { 0, { 0, 0, 0 }, &lbl_80421FE0 },
    { 8, { 0, 0, 0 }, &lbl_80421FF8 },
    { 0, { 0, 0, 0 }, &lbl_8042200C },
    { 9, { 0, 0, 0 }, &lbl_80422024 },
    { 0, { 0, 0, 0 }, &lbl_80422038 },
    { 10, { 0, 0, 0 }, &lbl_80422050 },
    { 13, { 0, 0, 0 }, 0 }
};
#pragma force_active reset
/* fn_80116DD0 (0x80116DD0): item held in the driver's hand: spawn its
 * scaling anim state, follow the hand joint while held, and either launch
 * it (phase 1) or drop it (phase 2). */

typedef float Mtx44[4][4];

typedef struct HeldItemCtx {
    unsigned char pad00[0x34];
    unsigned char launchPos[0x38]; /* 0x34 */
    void *anim;                    /* 0x6C */
    unsigned char pad70[0x28];
    void *driver;                  /* 0x98 */
    unsigned char pad9C[0x4];
    signed char phase;             /* 0xA0 */
} HeldItemCtx;

typedef struct HeldItem {
    unsigned char pad00[0x14];
    unsigned char sprite[0x14];    /* 0x14 */
    signed char visible;           /* 0x28 */
    unsigned char pad29[0x3];
    float alpha;                   /* 0x2C */
    unsigned char pad30[0x18];
    unsigned char mtx[0x80];       /* 0x48 */
    signed char mode;              /* 0xC8 */
    unsigned char launches;        /* 0xC9 */
    signed char state;             /* 0xCA */
} HeldItem;

extern void *AnimStatePool_Alloc(void *pool);
extern void AnimStatePool_Free(void *anim);
extern float AnimState_GetTotalScaleX(void *anim);
extern float AnimState_GetTotalScaleY(void *anim);
extern float AnimState_GetTotalScaleZ(void *anim);
extern void AnimState_SetGlobalScale(void *anim, float scale);
extern void AnimState_Step(void *anim);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, Mtx44 src);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void GabyouItem_BuildLocalTransformFromHandJoint(HeldItem *item, int flag, float a, float b, float c);
extern void Item_InitLaunchFromKart(HeldItem *item, void *pos, float speed, float b);
extern void *KartDriver_GetJointByIdx(void *driver, int idx);
extern void Matrix4_Identity(Mtx44 m);
extern void Matrix4_Multiply(Mtx44 a, Mtx44 b, Mtx44 out);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *joint);
extern void Mtx44_Scale_PerAxis(Mtx44 dst, Mtx44 src, float x, float y, float z);
extern void Mtx_TransposeToMtx44(Mtx44 dst, void *src);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *sprite, int anim, float frame);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *sprite, int enable);

void fn_80116DD0(HeldItem *item, HeldItemCtx *ctx)
{
    Mtx44 scale;
    Mtx44 m;

    switch (item->state) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, 0.0f);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
        ctx->anim = AnimStatePool_Alloc(lbl_80422064);
        AnimState_SetGlobalScale(ctx->anim, 1.5f);
        item->visible = 1;
        item->alpha = 0.0f;
        item->state++;
    case 1:
        GabyouItem_BuildLocalTransformFromHandJoint(item, 1, 0.0f, 2.7925262f, 1.5f);
        if (ctx->anim) {
            void *anim;
            float y;
            float z;
            AnimState_Step(anim = ctx->anim);
            Matrix4_Identity(scale);
            z = AnimState_GetTotalScaleZ(anim);
            y = AnimState_GetTotalScaleY(anim);
            Mtx44_Scale_PerAxis(scale, scale, AnimState_GetTotalScaleX(anim), y, z);
            Mtx_TransposeToMtx44(m, item->mtx);
            Matrix4_Multiply(m, scale, m);
            DbgScene_CopyMatrix3x4Transpose(item->mtx, m);
        }
        if (FinalLapCoinJump_CheckActiveForObject(ctx->driver)) {
            item->visible = 0;
        } else {
            item->visible = 1;
        }
        switch (ctx->phase) {
        case 1:
            item->visible = 1;
            ctx->phase = 0;
            if (ctx->anim) {
                AnimStatePool_Free(ctx->anim);
            }
            ctx->anim = 0;
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 0);
            Item_InitLaunchFromKart(item, ctx->launchPos, 5.0f, 0.0f);
            item->launches++;
            item->state = 0;
            return;
        case 2:
            ctx->phase = 0;
            if (ctx->anim) {
                AnimStatePool_Free(ctx->anim);
            }
            ctx->anim = 0;
            item->visible = 0;
            item->mode = 3;
            item->launches = 0;
            return;
        }
        break;
    }
    Mtx44_GetTranslation_RowMajor(ctx->launchPos, KartDriver_GetJointByIdx(ctx->driver, 12));
}
