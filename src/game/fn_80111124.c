typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec3 *b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern void Vec3_Copy(void *dst, void *src);
extern void EffectVfx88_DustHelix_Tick(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern const float lbl_806D6948;
extern const float lbl_806D694C;
extern const float lbl_806D6958;
extern const float lbl_806D695C;
extern const float lbl_806D6950;

void fn_80111124(unsigned char *self, unsigned char *ctx)
{
    Vec3 t;
    Vec3 dir;
    Vec3 pos;
    int i;
    unsigned char *e;

    switch ((signed char)self[0xC9]) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, lbl_806D6948);
        SpriteSlot_SetScale(self + 0x14, lbl_806D694C);
        if (*(void **)(ctx + 0x9C)) {
            Item_PrepareHitRebound(self, ctx + 0x40, ctx + 0x34, ctx + 0x4);
            self[0xC9] = 1;
            self[0xCA] = 0;
        } else {
            self[0xC9] = 2;
            self[0xCA] = 0;
        }
        break;
    case 1:
        dir = *(Vec3 *)(ctx + 0x34);
        Vec3_AddNormalizedXZ(self, ctx + 0x40, &dir);
        Mtx44_GetTranslation_RowMajor(&t, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
        Vec3_Add_DestFirst(self + 0xA0, &t, ctx + 0x40);
        if (*(unsigned int *)(ctx + 0x4) == 0) {
            if (ctx[0]) {
                ItemHit_Dispatch(self, 0, 0, *(void **)(ctx + 0x9C));
            }
            Vec3_Copy(self + 0xB8, ctx + 0x34);
            self[0xC9] = 2;
            self[0xCA] = 0;
        }
        break;
    case 2:
        switch (*(signed char *)(self + 0xCA)) {
        case 0:
            for (i = 0; i < 6; i++) {
                e = DrawEffect_SpawnDirect(EffectVfx88_DustHelix_Tick);
                if (e) {
                    Vec3_Copy(e + 0x8C, self + 0xA0);
                    *(void **)(e + 0x11C) = *(void **)(ctx + 0x9C);
                }
            }
            pos = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xAE, &pos, 0);
            *(unsigned int *)(ctx + 0x4) = 60;
            self[0xCA]++;
        case 1:
            break;
        }
        if (*(unsigned int *)(ctx + 0x4) == 0) {
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D6958;
            if (*(float *)(self + 0x2C) < lbl_806D6948) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
        }
        *(float *)(self + 0xBC) += lbl_806D695C;
        break;
    }
    Item_DecayVelocityScalar(self, lbl_806D6950);
}
