typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_801094E4(unsigned char *self, unsigned char *sub);
extern void fn_801092B0(unsigned char *self, unsigned char *sub);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, void *a, float b, float c, float d);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);

extern const char lbl_80331648[];
extern const char lbl_80331658[];

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item_TickFallFade(unsigned char *self, unsigned char *sub)
{
    Vec3 g1;
    Vec3 g2;
    float gy;

    switch ((signed char)self[0xC9]) {
    case 0:
        g1 = *(Vec3 *)(self + 0xA0);
        ItemObject_GetGroundTypeAt(&g1, (float *)(sub + 0x14), 0);
        if (*(char *)(self + 0xCB) != 5) {
            *(unsigned int *)(sub + 0x8) = 10;
        } else {
            *(unsigned int *)(sub + 0x8) = 0;
        }
        if (*(char *)(self + 0xCB) == 5) {
            *(float *)(self + 0xBC) = 0.0f;
        }
        self[0xC9]++;
    case 1:
        break;
    }
    if (*(unsigned int *)(sub + 0x8) == 0) {
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.05f;
        if (*(float *)(self + 0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    if (*(char *)(self + 0xCB) != 5) {
        *(float *)(self + 0xBC) += -0.1f;
    }
    g2 = *(Vec3 *)(self + 0xA0);
    if (ItemObject_GetGroundTypeAt(&g2, &gy, 0)) {
        *(float *)(self + 0xA4) = *(float *)(self + 0xA4) + (gy - *(float *)(sub + 0x14));
        *(float *)(sub + 0x14) = gy;
    }
    *(float *)(self + 0xB0) = BuildOrientationFromYaw(0.34906578f + *(float *)(self + 0xB0));
    Item_DecayVelocityScalar(self, 5.0f);
}

void fn_80109AB8(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x69);
        self[0x8C] = 3;
        self[0x8D] = 0;
        *(float *)(self + 0xB0) = 0.0f;
        *(unsigned int *)(sub + 0x4) = 0;
        sub[0x0] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_801094E4(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            fn_801092B0(self, sub);
            break;
        case 3:
            switch ((signed char)self[0xC9]) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                *(float *)(sub + 0x14) = 0.0f;
                *(float *)(sub + 0x18) = *(float *)(self + 0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, sub + 0x14, *(float *)(sub + 0x18), 0.0f, 0.34906578f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            Item_TickFallFade(self, sub);
            break;
        case 6:
            switch ((signed char)self[0xC9]) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(sub + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                *(unsigned int *)(sub + 0x8) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 5.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x8), 0.0f, 0.34906578f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            Item_TickFallFade(self, sub);
            break;
        case 9:
            Item_TickFallFade(self, sub);
            break;
        case 5:
            Item_TickFallFade(self, sub);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    if (*(unsigned int *)(sub + 0x4) == 0) {
        sub[0x0] ^= 1;
        if (sub[0x0]) {
            SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80331648, 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80331658, 0x10, 1);
        } else {
            SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80331648, 0x10, 1);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80331658, 0x10, 0);
        }
        *(unsigned int *)(sub + 0x4) = 30;
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
