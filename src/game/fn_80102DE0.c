typedef struct Vec { float x, y, z; } Vec;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void fn_801025C0(unsigned char *self, unsigned char *w);
extern void fn_80101A58(unsigned char *self, unsigned char *w);
extern void fn_80100F64(unsigned char *self, unsigned char *w);
extern void fn_801022E0(unsigned char *self, unsigned char *w);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *offset, unsigned int timer, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80102DE0(unsigned char *self)
{
    unsigned char *w = self + 0xEC;

    switch (S8(0xC8)) {
    case 0:
        if (*(int *)(self + 0x8) == 0x59) {
            SpriteSlot_InitNonLoop(self + 0x14, 0x58);
        } else {
            SpriteSlot_InitNonLoop(self + 0x14, 0x59);
        }
        self[0x8C] = 3;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_801025C0(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            if (*(int *)(self + 0x8) == 0x59) {
                fn_80101A58(self, w);
            } else {
                fn_80100F64(self, w);
            }
            break;
        case 1:
            fn_801022E0(self, w);
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
            fn_801022E0(self, w);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(w + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                WU(0x4) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            if (*(int *)(self + 0x8) == 0x59) {
                Item_DecayVelocityScalar(self, 2.0f);
            } else {
                Item_DecayVelocityScalar(self, 1.5f);
            }
            if (Item_OrbitAnchorKart(self, w + 0x34, WU(0x4), 0.2617993f, 0.2617993f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            fn_801022E0(self, w);
            break;
        case 9:
            fn_801022E0(self, w);
            break;
        case 5:
            fn_801022E0(self, w);
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
