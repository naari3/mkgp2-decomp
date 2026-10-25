typedef struct Vec { float x, y, z; } Vec;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void fn_80100284(unsigned char *self, unsigned char *w);
extern unsigned char *ItemObject_SpawnWithAlias(int kind, int alias);
extern void Vec3_Copy(void *dst, void *src);
extern void Vec3_Scale(void *dst, void *src, float s);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *offset, unsigned int timer, float a, float b);
extern float BuildOrientationFromYaw(float yaw);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))

static inline void Item80100828_SpawnAndFade(unsigned char *self, unsigned char *w)
{
    unsigned char *p;

    switch (S8(0xC9)) {
    case 0:
        p = ItemObject_SpawnWithAlias(0x66, 0xFF);
        if (p != 0) {
            p[0x1DC] = w[0xF0];
            *(unsigned int *)(p + 0x1E0) = WU(0xF4);
            Vec3_Copy(p + 0xA0, self + 0xA0);
            Vec3_Copy(p + 0xB8, self + 0xB8);
            *(unsigned int *)(p + 0x180) = WU(0x94);
            *(unsigned int *)(p + 0x184) = WU(0x98);
        }
        self[0xC9]++;
    case 1:
        break;
    }
    Vec3_Scale(self + 0xB8, self + 0xB8, 0.5f);
    F(0x2C) -= 0.1f;
    if (F(0x2C) < 0.0f) {
        self[0x28] = 0;
        self[0xC8] = 3;
        self[0xC9] = 0;
    }
}

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80100828(unsigned char *self)
{
    unsigned char *w = self + 0xEC;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x57);
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 8, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        self[0x8C] = 2;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_80100284(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            Item80100828_SpawnAndFade(self, w);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                *(float *)(w + 0x14) = 0.0f;
                *(float *)(w + 0x18) = F(0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, (float *)(w + 0x14), *(float *)(w + 0x18), 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            Item80100828_SpawnAndFade(self, w);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(w + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                WU(0x4) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 2.0f);
            if (Item_OrbitAnchorKart(self, w + 0x34, WU(0x4), 0.2617993f, 0.2617993f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            Item80100828_SpawnAndFade(self, w);
            break;
        case 8:
            Item80100828_SpawnAndFade(self, w);
            break;
        case 9:
            switch (S8(0xC9)) {
            case 0:
                WU(0x4) = 10;
                self[0xC9]++;
            case 1:
                break;
            }
            F(0xBC) += -0.1f;
            F(0xAC) = BuildOrientationFromYaw(0.087266445f + F(0xAC));
            Item_DecayVelocityScalar(self, 2.0f);
            if (WU(0x4) == 0) {
                F(0x2C) -= 0.05f;
                if (F(0x2C) < 0.0f) {
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                }
            }
            break;
        case 5:
            Item80100828_SpawnAndFade(self, w);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    Timer_Tick((unsigned int *)(w + 0x4));
    Timer_Tick((unsigned int *)(w + 0x8));
    Timer_Tick((unsigned int *)(w + 0xC));
    Timer_Tick((unsigned int *)(w + 0x10));
}
