typedef struct Vec3 { float x, y, z; } Vec3;

extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec3 *b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern void Effect_ExplosionPiece_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern const float lbl_806D6CF4;
extern const float lbl_806D6CF8;
extern const float lbl_806D6CF0;
extern const float lbl_806D6D00;
extern const float lbl_806D6CFC;
extern const float lbl_806D6D04;
extern const float lbl_806D6D08;

void fn_8011C008(unsigned char *self, unsigned char *ctx)
{
    Vec3 t;
    Vec3 dir;
    Vec3 pos;
    int i;
    float r;
    unsigned char *e;

    switch ((signed char)self[0xC9]) {
    case 0:
        Vec3_Subtract_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
        Item_PrepareHitRebound(self, ctx + 0x40, ctx + 0x34, ctx + 0x4);
        self[0xC9]++;
    case 1:
        break;
    }
    dir = *(Vec3 *)(ctx + 0x34);
    Vec3_AddNormalizedXZ(self, ctx + 0x40, &dir);
    Mtx44_GetTranslation_RowMajor(&t, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
    Vec3_Add_DestFirst(self + 0xA0, &t, ctx + 0x40);
    if (*(unsigned int *)(ctx + 0x4) == 0) {
        if (ctx[0]) {
            ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(ctx + 0x9C));
        }
        for (i = 0; i < 3; i++) {
            e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
            if (e) {
                Vec3_Copy(e + 0x8C, self + 0xA0);
                r = lbl_806D6CF0 * Rand_RangeFloat(lbl_806D6CF4, lbl_806D6CF8);
                GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, r);
                Vec2_RotateX(e + 0xA4, e + 0xA4, lbl_806D6CFC * Rand_RangeFloat(lbl_806D6D00, 0.0f));
                Vec2_RotateY(e + 0xA4, e + 0xA4, lbl_806D6CFC * Rand_RangeFloat(lbl_806D6D04, lbl_806D6D08));
                e[0x190] = 1;
                e[0x191] = 3;
                *(void **)(e + 0x11C) = *(void **)(ctx + 0x9C);
                e[0x192] = 0;
                GetSpawnPosition(e + 0x120, 0.5f, 1.0f, 1.0f);
                e[0x193] = 1;
            }
            pos = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0x87, &pos, 0);
        }
        self[0x28] = 0;
        self[0xC8] = 3;
        self[0xC9] = 0;
    }
}
