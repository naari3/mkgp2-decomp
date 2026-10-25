typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void fn_80111D8C(unsigned char *self, unsigned char *ctx);
extern unsigned char *ItemObject_SpawnWithAlias(int id, int alias);
extern void Vec3_Copy(void *dst, void *src);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, void *a, float b, float c, float d);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_801122AC(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;
    unsigned char *o;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x74);
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        self[0x8C] = 3;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_80111D8C(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            o = ItemObject_SpawnWithAlias(0x68, 0xFF);
            if (o) {
                o[0x1DC] = sub[0xF0];
                *(int *)(o + 0x1E0) = *(int *)(sub + 0xF4);
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
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
            o = ItemObject_SpawnWithAlias(0x68, 0xFF);
            if (o) {
                o[0x1DC] = sub[0xF0];
                *(int *)(o + 0x1E0) = *(int *)(sub + 0xF4);
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
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
            Item_DecayVelocityScalar(self, 1.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.26179934f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            o = ItemObject_SpawnWithAlias(0x68, 0xFF);
            if (o) {
                o[0x1DC] = sub[0xF0];
                *(int *)(o + 0x1E0) = *(int *)(sub + 0xF4);
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 8:
            o = ItemObject_SpawnWithAlias(0x68, 0xFF);
            if (o) {
                o[0x1DC] = sub[0xF0];
                *(int *)(o + 0x1E0) = *(int *)(sub + 0xF4);
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 5:
            o = ItemObject_SpawnWithAlias(0x68, 0xFF);
            if (o) {
                o[0x1DC] = sub[0xF0];
                *(int *)(o + 0x1E0) = *(int *)(sub + 0xF4);
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
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
