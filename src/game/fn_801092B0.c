typedef struct Vec3 { float x, y, z; } Vec3;

extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec3 *b);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern float BuildOrientationFromYaw(float a);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern const float lbl_806D6754;
extern const float lbl_806D6758;
extern const float lbl_806D675C;
extern const float lbl_806D6760;
extern const float lbl_806D6748;
extern const float lbl_806D6750;
extern const float lbl_806D674C;

void fn_801092B0(unsigned char *self, unsigned char *ctx)
{
    Vec3 t;
    Vec3 dir;
    Vec3 pos;

    switch ((signed char)self[0xC9]) {
    case 0:
        Item_PrepareHitRebound(self, ctx + 0x40, ctx + 0x34, ctx + 0x8);
        self[0xC9]++;
    case 1:
        dir = *(Vec3 *)(ctx + 0x34);
        Vec3_AddNormalizedXZ(self, ctx + 0x40, &dir);
        if (*(unsigned int *)(ctx + 0x8) == 0) {
            if (ctx[1]) {
                ItemHit_Dispatch(self, 0, 0, *(void **)(ctx + 0x9C));
            }
            pos = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xCB, &pos, 0);
            self[0xC9]++;
            self[0xCA] = 0;
        }
        break;
    case 2:
        switch (*(signed char *)(self + 0xCA)) {
        case 0:
            *(float *)(ctx + 0x38) = lbl_806D6754;
            *(float *)(ctx + 0x34) *= lbl_806D6758;
            *(float *)(ctx + 0x3C) *= lbl_806D6758;
            *(unsigned int *)(ctx + 0x8) = 10;
            self[0xCA]++;
        case 1:
            break;
        }
        *(float *)(ctx + 0x38) += lbl_806D675C;
        Vec3_Add_DestFirst(ctx + 0x40, ctx + 0x40, ctx + 0x34);
        if (*(unsigned int *)(ctx + 0x8) == 0) {
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D6760;
            if (*(float *)(self + 0x2C) < lbl_806D6748) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
        }
        break;
    }
    Mtx44_GetTranslation_RowMajor(&t, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
    Vec3_Add_DestFirst(self + 0xA0, &t, ctx + 0x40);
    *(float *)(self + 0xB0) = BuildOrientationFromYaw(lbl_806D6750 + *(float *)(self + 0xB0));
    Item_DecayVelocityScalar(self, lbl_806D674C);
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(ctx + 0x9C))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}
