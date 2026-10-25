typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_80118230(unsigned char *self, unsigned char *ctx);
extern void fn_80117E08(unsigned char *self, unsigned char *ctx);
extern unsigned char *ItemObject_SpawnWithAlias(int id, int alias);
extern void Vec3_Copy(void *dst, void *src);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern double sin(double);

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80118438(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;
    unsigned char *o;
    float s;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x82);
        self[0x8C] = 3;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            fn_80118230(self, sub);
            break;
        case 1:
            fn_80117E08(self, sub);
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            o = ItemObject_SpawnWithAlias(0x63, 0xFF);
            if (o) {
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 4:
            o = ItemObject_SpawnWithAlias(0x63, 0xFF);
            if (o) {
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
            Item_DecayVelocityScalar(self, 0.8f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.26179934f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 5:
            Item_DecayVelocityScalar(self, 0.8f);
            s = sin(0.017453289f * (7.2e+02f * *(float *)(sub + 0x14)));
            *(float *)(self + 0xA4) = *(float *)(self + 0xA4) - (5.0f * s + 5.0f);
            *(float *)(sub + 0x14) += 0.004166667f;
            if (1.0f <= *(float *)(sub + 0x14)) {
                *(float *)(sub + 0x14) = 0.0f;
            }
            s = sin(0.017453289f * (7.2e+02f * *(float *)(sub + 0x14)));
            *(float *)(self + 0xA4) = *(float *)(self + 0xA4) + (5.0f * s + 5.0f);
            s = sin(0.017453289f * (3.6e+02f * *(float *)(sub + 0x14)));
            *(float *)(self + 0xB0) = 0.2f * s + *(float *)(self + 0xB0);
            if (*(float *)(self + 0xB0) < 6.283184f) {
                *(float *)(self + 0xB0) += 6.283184f;
            }
            if (6.283184f <= *(float *)(self + 0xB0)) {
                *(float *)(self + 0xB0) -= 6.283184f;
            }
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
            if (*(float *)(self + 0x2C) < 0.0f) {
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
