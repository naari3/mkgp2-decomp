typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_8011136C(unsigned char *self, unsigned char *ctx);
extern void fn_80111124(unsigned char *self, unsigned char *ctx);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, void *a, float b, float c, float d);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern char lbl_80332470[];
extern char lbl_80332484[];
extern const float lbl_806D6948;
extern const float lbl_806D694C;
extern const float lbl_806D6950;
extern const float lbl_806D6954;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80111A38(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x73);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80332470, 0x10, 0);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80332484, 0x10, 1);
        self[0x8C] = 3;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_8011136C(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            fn_80111124(self, sub);
            break;
        case 3:
            switch ((signed char)self[0xC9]) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, lbl_806D6948);
                SpriteSlot_SetScale(self + 0x14, lbl_806D694C);
                GetSpawnPosition(self + 0xB8, lbl_806D6948, lbl_806D6948, lbl_806D6948);
                self[0x3C] = 0;
                *(float *)(sub + 0x14) = lbl_806D6948;
                *(float *)(sub + 0x18) = *(float *)(self + 0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, sub + 0x14, *(float *)(sub + 0x18), lbl_806D6954, lbl_806D6954)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            fn_80111124(self, sub);
            break;
        case 6:
            switch ((signed char)self[0xC9]) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, lbl_806D6948);
                SpriteSlot_SetScale(self + 0x14, lbl_806D694C);
                GetSpawnPosition(self + 0xB8, lbl_806D6948, lbl_806D6948, lbl_806D6948);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(sub + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                *(unsigned int *)(sub + 0x4) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, lbl_806D6950);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), lbl_806D6954, lbl_806D6954)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            fn_80111124(self, sub);
            break;
        case 9:
            fn_80111124(self, sub);
            break;
        case 5:
            fn_80111124(self, sub);
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
