typedef struct Vec3 { float x, y, z; } Vec3;

extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern void CarrotItemEffect_Update(void);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(void));
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Effect_ExplosionPiece_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec3 *b);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern const float lbl_806D6A88;
extern const float lbl_806D6A8C;
extern const float lbl_806D6A84;
extern const float lbl_806D6A68;
extern const float lbl_806D6A94;
extern const float lbl_806D6A90;
extern const float lbl_806D6A98;
extern const float lbl_806D6A9C;
extern const float lbl_806D6AA0;
extern const float lbl_806D6A80;
extern const float lbl_806D6A6C;

static inline void SetForward(void *p, float z)
{
    GetSpawnPosition(p, 0.0f, 0.0f, z);
}

void fn_8011562C(unsigned char *self, unsigned char *ctx)
{
    Vec3 root;
    Vec3 hand;
    Vec3 pos;
    Vec3 dir;
    int i;
    unsigned char *e;
    float r;

    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
    switch ((signed char)self[0xC9]) {
    case 0:
        Item_PrepareHitRebound(self, ctx + 0x40, ctx + 0x34, ctx + 0x4);
        self[0xC9]++;
    case 1:
        if (*(unsigned int *)(ctx + 0x4) == 0) {
            if (ctx[0]) {
                ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(ctx + 0x9C));
                e = ItemObject_AllocFromPool(CarrotItemEffect_Update);
                *(void **)(e + 0x188) = *(void **)(ctx + 0x9C);
            }
            Mtx44_GetTranslation_RowMajor(&hand, KartDriver_GetJointByIdx(*(void **)(ctx + 0x9C), 0xF));
            for (i = 0; i < 5; i++) {
                e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
                if (e) {
                    Vec3_Copy(e + 0x8C, &hand);
                    SetForward(e + 0xA4, lbl_806D6A84 * Rand_RangeFloat(lbl_806D6A88, lbl_806D6A8C));
                    Vec2_RotateX(e + 0xA4, e + 0xA4, lbl_806D6A90 * Rand_RangeFloat(lbl_806D6A94, lbl_806D6A68));
                    Vec2_RotateY(e + 0xA4, e + 0xA4, lbl_806D6A90 * Rand_RangeFloat(lbl_806D6A98, lbl_806D6A9C));
                    e[0x190] = 0;
                    e[0x191] = 1;
                    *(void **)(e + 0x11C) = *(void **)(ctx + 0x9C);
                    e[0x192] = 1;
                    GetSpawnPosition(e + 0x120, lbl_806D6AA0, lbl_806D6AA0, lbl_806D6AA0);
                    e[0x193] = 1;
                }
            }
            pos = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0x87, &pos, 0);
            self[0xC9]++;
        }
        break;
    case 2:
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D6A80;
        if (*(float *)(self + 0x2C) < lbl_806D6A68) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    }
    dir = *(Vec3 *)(ctx + 0x34);
    Vec3_AddNormalizedXZ(self, ctx + 0x40, &dir);
    Vec3_Add_DestFirst(self + 0xA0, &root, ctx + 0x40);
    Item_DecayVelocityScalar(self, lbl_806D6A6C);
}
