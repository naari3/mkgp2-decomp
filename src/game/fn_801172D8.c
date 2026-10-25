typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void Effect_BindRes25_Init(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Mtx44_TransformVec3(Vec3 *out, float *m, Vec3 v);
extern void Effect_BuildYawPitchScaleMtx_48(unsigned char *e, Vec3 pos, float scale, float yaw);
extern void SpriteSlot_Container_Free(void *self);
extern int lbl_806CF428;
extern float lbl_806D6B30;
extern float lbl_806CF42C;
extern float lbl_806CF430;
extern float lbl_806CF434;
extern float lbl_806CF438;
extern float lbl_806CF43C;

void fn_801172D8(unsigned char *self)
{
    float m[16];
    Vec3 pos;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, (unsigned char)lbl_806CF428);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        *(float *)(self + 0x2C) = lbl_806D6B30;
        *(unsigned char **)(self + 0x138) = DrawEffect_SpawnDirect(Effect_BindRes25_Init);
        self[0xC8] = 1;
    case 1:
        break;
    }
    GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806CF42C, lbl_806CF430, lbl_806CF434);
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(self + 0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    if (*(unsigned char **)(self + 0x138)) {
        GetSpawnPosition(&pos, lbl_806D6B30, lbl_806CF438, lbl_806D6B30);
        Mtx_TransposeToMtx44(m, self + 0x48);
        Mtx44_TransformVec3(&pos, m, pos);
        if (*(signed char *)(self + 0x28)) {
            Effect_BuildYawPitchScaleMtx_48(*(unsigned char **)(self + 0x138), pos,
                *(float *)(self + 0xC4) * lbl_806CF43C, *(float *)(self + 0x2C));
        } else {
            Effect_BuildYawPitchScaleMtx_48(*(unsigned char **)(self + 0x138), pos,
                *(float *)(self + 0xC4) * lbl_806CF43C, lbl_806D6B30);
        }
    }
    if (*(signed char *)(self + 0x18C)) {
        if (*(unsigned char **)(self + 0x138)) {
            (*(unsigned char **)(self + 0x138))[0xC9] = 1;
        }
        *(unsigned char **)(self + 0x138) = 0;
        SpriteSlot_Container_Free(self);
    }
}
