typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void fn_8011D118(unsigned char *self, unsigned char *ctx);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *out, int a, float f);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern const float lbl_806D6D54;
extern const float lbl_806D6D7C;
extern const float lbl_806D6D80;
extern const float lbl_806D6D50;
extern const float lbl_806D6D58;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_8011D564(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;
    int landed;

    switch ((signed char)self[0xC8]) {
    case 0:
        sub[0x90] = 1;
        SpriteSlot_InitNonLoop(self + 0x14, 0x87);
        self[0x8C] = 0;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            switch ((signed char)self[0xCA]) {
            case 0:
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, lbl_806D6D54);
                self[0x28] = 1;
                *(float *)(self + 0x2C) = lbl_806D6D54;
                self[0xCA]++;
            case 1:
                GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806D6D54, lbl_806D6D7C, lbl_806D6D80);
                if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98))) {
                    self[0x28] = 0;
                } else {
                    self[0x28] = 1;
                }
                switch (*(signed char *)(sub + 0xA0)) {
                case 1:
                    self[0x28] = 1;
                    sub[0xA0] = 0;
                    SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                    Item_InitLaunchFromKart(self, 0, lbl_806D6D80, lbl_806D6D54);
                    self[0xC9]++;
                    self[0xCA] = 0;
                    break;
                case 2:
                    sub[0xA0] = 0;
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                    break;
                }
                break;
            }
            break;
        case 1:
            fn_8011D118(self, sub);
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xC9]) {
        case 0:
            self[0xC9]++;
        case 1:
            Item_DecayVelocityScalar(self, lbl_806D6D50);
            if (Item_AdvanceFallingDrop(self, &landed, 0, lbl_806D6D54) && landed) {
                *(float *)(self + 0xBC) = lbl_806D6D54;
            }
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D6D58;
            if (*(float *)(self + 0x2C) < lbl_806D6D54) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
