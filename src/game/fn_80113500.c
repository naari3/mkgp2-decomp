extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void *ItemObject_AllocGabyou(void);
extern void Item_RenderFlyingFromKart(unsigned char *self, void *obj, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void SpriteSlot_Container_Free(void *self);
extern void Effect_ExplosionPiece_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern const float lbl_806D69C0;
extern const float lbl_806D69EC;
extern const float lbl_806D69FC;
extern const float lbl_806D6A00;
extern const float lbl_806D69D8;
extern const float lbl_806D69DC;
extern const float lbl_806D69D0;
extern const float lbl_806D6A04;

void fn_80113500(unsigned char *self, unsigned char *ctx)
{
    int i;
    unsigned char *e;

    switch (*(signed char *)(self + 0xCA)) {
    case 0:
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        *(void **)(ctx + 0x5C) = ItemObject_AllocGabyou();
        self[0x28] = 1;
        *(float *)(self + 0x2C) = lbl_806D69C0;
        self[0xCA]++;
    case 1:
        break;
    }
    Item_RenderFlyingFromKart(self, *(void **)(ctx + 0x5C), 1, lbl_806D69EC, lbl_806D69FC, lbl_806D6A00);
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(ctx + 0x98))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    switch (*(signed char *)(ctx + 0xA0)) {
    case 1:
        self[0x28] = 1;
        ctx[0xA0] = 0;
        SpriteSlot_Container_Free(*(void **)(ctx + 0x5C));
        *(void **)(ctx + 0x5C) = 0;
        for (i = 0; i < 6; i++) {
            e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
            if (e) {
                Vec3_Copy(e + 0x8C, self + 0xA0);
                GetSpawnPosition(e + 0xA4, lbl_806D69C0, lbl_806D69C0, lbl_806D69EC);
                Vec2_RotateX(e + 0xA4, e + 0xA4, lbl_806D69D0 * Rand_RangeFloat(lbl_806D69D8, lbl_806D69DC));
                Vec2_RotateY(e + 0xA4, e + 0xA4, lbl_806D69D0 * Rand_RangeFloat(lbl_806D69D8, lbl_806D69DC));
                e[0x191] = 1;
                *(void **)(e + 0x11C) = *(void **)(ctx + 0x98);
                GetSpawnPosition(e + 0x120, lbl_806D69EC, lbl_806D69EC, lbl_806D69EC);
            }
        }
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
        Item_InitLaunchFromKart(self, ctx + 0x34, lbl_806D6A04, lbl_806D69C0);
        self[0xC9]++;
        self[0xCA] = 0;
        break;
    case 2:
        ctx[0xA0] = 0;
        SpriteSlot_Container_Free(*(void **)(ctx + 0x5C));
        *(void **)(ctx + 0x5C) = 0;
        *(float *)(self + 0x2C) = lbl_806D69C0;
        self[0xC8] = 3;
        self[0xC9] = 0;
        break;
    default:
        Mtx44_GetTranslation_RowMajor(ctx + 0x34, KartDriver_GetJointByIdx(*(void **)(ctx + 0x98), 0xC));
        break;
    }
}
