typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct ItemPickTable { unsigned char b[9]; } ItemPickTable;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern int Rand_RangeIntMax(int max);
extern void fn_8011040C(unsigned char *self, unsigned char *sub);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *kart);
extern unsigned char *ItemObject_SpawnWithAlias(int id, int alias);
extern void Vec3_Copy(void *dst, void *src);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, void *a, float b, float c, float d);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern float BuildOrientationFromYaw(float yaw);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);

extern char lbl_80332038[];
extern int g_gameMode;
extern int lbl_806D134C;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item_ResolveHit(unsigned char *self, unsigned char *sub, const char *str)
{
    unsigned char *e;

    if (*(signed char *)(self + 0xCB) == 0 && sub[1] != 0) {
        ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(sub + 0x9C));
        switch (sub[0]) {
        case 0:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, str + 0x408, 0x10, 1);
            break;
        case 1:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, str + 0x408, 0x10, 1);
            e = ItemObject_SpawnWithAlias(0x2B, 0xFF);
            if (e != 0) {
                *(int *)(e + 0x10) = 1;
                Vec3_Copy(e + 0xA0, self + 0xA0);
                *(void **)(e + 0x180) = *(void **)(sub + 0x94);
                *(void **)(e + 0x184) = *(void **)(sub + 0x98);
                *(void **)(e + 0x188) = *(void **)(sub + 0x9C);
            }
            break;
        case 2:
            e = ItemObject_SpawnWithAlias(0x63, 0xFF);
            if (e != 0) {
                e[0x1DC] = sub[0xF0];
                *(int *)(e + 0x1E0) = *(int *)(sub + 0xF4);
                Vec3_Copy(e + 0xA0, self + 0xA0);
                *(void **)(e + 0x180) = *(void **)(sub + 0x94);
                *(void **)(e + 0x184) = *(void **)(sub + 0x98);
            }
            break;
        }
    } else {
        SpriteSlot_SetJointVisibilityByName(self + 0x14, str + 0x408, 0x10, 1);
    }
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}

static inline void Item_TickFall(unsigned char *self, unsigned char *sub)
{
    switch ((signed char)self[0xC9]) {
    case 0:
        if (*(char *)(self + 0xCB) != 5) {
            *(unsigned int *)(sub + 0x4) = 10;
        } else {
            *(unsigned int *)(sub + 0x4) = 0;
        }
        self[0xC9]++;
    case 1:
        break;
    }
    if (*(unsigned int *)(sub + 0x4) == 0) {
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.05f;
        if (*(float *)(self + 0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    if (*(char *)(self + 0xCB) == 9) {
        *(float *)(self + 0xBC) += -0.1f;
    }
    if (*(char *)(self + 0xCB) == 9) {
        *(float *)(self + 0xAC) = BuildOrientationFromYaw(0.087266445f + *(float *)(self + 0xAC));
    }
    Item_DecayVelocityScalar(self, 3.0f);
}

void fn_801109A0(unsigned char *self)
{
    char *str = lbl_80332038;
    unsigned char *sub = self + 0xEC;
    ItemPickTable tbl;
    Vec3 pos;
    Vec3 rot;

    switch ((signed char)self[0xC8]) {
    case 0:
        sub[0x90] = 1;
        SpriteSlot_InitNonLoop(self + 0x14, 0x72);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, str + 0x408, 0x10, 0);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, str + 0x424, 0x10, 1);
        self[0x8C] = 3;
        self[0x8D] = 0;
        tbl = *(ItemPickTable *)(str + 0x3FC);
        if (g_gameMode == 2) {
            sub[0] = tbl.b[lbl_806D134C++ % 9];
        } else {
            sub[0] = Rand_RangeIntMax(15) % 3;
        }
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_8011040C(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            Item_ResolveHit(self, sub, str);
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
            if (Item_AdvanceTetherToJoint13(self, sub + 0x14, *(float *)(sub + 0x18), 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            Item_ResolveHit(self, sub, str);
            break;
        case 6:
            switch ((signed char)self[0xC9]) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(sub + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                *(unsigned int *)(sub + 0x4) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 3.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.26179934f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 9:
            Item_TickFall(self, sub);
            break;
        case 5:
            Item_TickFall(self, sub);
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
