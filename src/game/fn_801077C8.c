typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void Item_RenderHandheldByCharacter(unsigned char *self, Vec3 *a, Vec3 *b, int c, float f);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void fn_80107040(void);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(void));
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern void Vec3_Lerp(void *dst, Vec3 a, Vec3 b, float t);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern float Mtx44_GetYawOfPosZ_Padded(void *m);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern Vec3 lbl_80331610;
extern Vec3 lbl_8033161C;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void RenderHeld(unsigned char *self)
{
    Vec3 a;
    Vec3 b;
    b = lbl_8033161C;
    a = lbl_80331610;
    Item_RenderHandheldByCharacter(self, &a, &b, 2, 0.8f);
}

void fn_801077C8(unsigned char *self)
{
    Vec3 j10;
    Vec3 j11;
    unsigned char *o;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x60);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        self[0x28] = 1;
        *(float *)(self + 0x2C) = 1.0f;
        *(float *)(self + 0xC4) = 0.0f;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            {
                Vec3 a;
                Vec3 b;
                b = lbl_8033161C;
                a = lbl_80331610;
                Item_RenderHandheldByCharacter(self, &a, &b, 2, 0.8f);
            }
            if (FinalLapCoinJump_CheckActiveForObject(*(void **)(self + 0x184))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(self + 0x18C)) {
            case 1:
                self[0x28] = 1;
                self[0x18C] = 0;
                self[0x28] = 0;
                self[0xC9] = 1;
                self[0xCA] = 0;
                break;
            case 2:
                self[0x18C] = 0;
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            }
            break;
        case 1:
            switch (*(signed char *)(self + 0xCA)) {
            case 0:
                *(unsigned int *)(self + 0xF0) = 30;
                self[0xEC] = 0;
                self[0xCA]++;
            case 1:
                if (*(unsigned int *)(self + 0xF0) == 0) {
                    o = ItemObject_AllocFromPool(fn_80107040);
                    if (o) {
                        o[0x1DC] = self[0x1DC];
                        *(int *)(o + 0x1E0) = *(int *)(self + 0x1E0);
                        Mtx44_GetTranslation_RowMajor(&j10, KartDriver_GetJointByIdx(*(void **)(self + 0x184), 10));
                        Mtx44_GetTranslation_RowMajor(&j11, KartDriver_GetJointByIdx(*(void **)(self + 0x184), 11));
                        Vec3_Lerp(o + 0xA0, j10, j11, 0.5f);
                        *(float *)(o + 0xA4) += 4.0f;
                        *(float *)(o + 0xB0) = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(*(void **)(self + 0x184)));
                        *(int *)(o + 0x180) = *(int *)(self + 0x180);
                        *(int *)(o + 0x184) = *(int *)(self + 0x184);
                    }
                    self[0xEC]++;
                    if (self[0xEC] >= 3) {
                        self[0xC8] = 3;
                        self[0xC9] = 0;
                    } else {
                        *(unsigned int *)(self + 0xF0) = 30;
                    }
                }
                break;
            }
            break;
        }
        break;
    case 2:
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    ItemObject_TickTimer((unsigned int *)(self + 0xF0));
    ItemObject_TickTimer((unsigned int *)(self + 0xF4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF8));
    ItemObject_TickTimer((unsigned int *)(self + 0xFC));
}
