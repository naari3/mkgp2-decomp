typedef struct Vec { float x, y, z; } Vec;

typedef struct ScaleKey {
    float t[9];
    float v[9];
} ScaleKey;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void fn_80105180(unsigned char *self, unsigned char *w);
extern void fn_801046C4(unsigned char *self, unsigned char *w);
extern void fn_80104ED4(unsigned char *self, unsigned char *w);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *offset, unsigned int timer, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);

extern void SpriteSlot_SetJointScaleByName(void *slot, const unsigned char *name, float x, float y, float z);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const unsigned char *name);
extern void VfxLaugh_Tick(void *e, Vec pos, unsigned char visible, float scale, float alpha);

extern unsigned char lbl_803311D0[];
extern ScaleKey lbl_80421A28[2];

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80105800(unsigned char *self)
{
    unsigned char *base = lbl_803311D0;
    unsigned char *w = self + 0xEC;
    Vec scale;
    Vec jp;
    ScaleKey *key;
    float *out;
    float x;
    float t0, v0, t1, v1;
    unsigned char vis;
    int i;
    int j;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x5D);
        self[0x14] = 4;
        self[0x8C] = 2;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_80105180(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            fn_801046C4(self, w);
            break;
        case 1:
            fn_80104ED4(self, w);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                WF(0x14) = 0.0f;
                WF(0x18) = F(0xC4);
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, (float *)(w + 0x14), WF(0x18), 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            fn_80104ED4(self, w);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(w + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                WU(0x4) = 30;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 1.0f);
            if (Item_OrbitAnchorKart(self, w + 0x34, WU(0x4), 0.2617993f, 0.2617993f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            fn_80104ED4(self, w);
            break;
        case 9:
            fn_80104ED4(self, w);
            break;
        case 5:
            fn_80104ED4(self, w);
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
    scale = *(Vec *)(base + 0x3FC);
    if (*(char *)(self + 0x1D) == 1) {
        x = 680.0f + F(0x20);
        for (i = 0; i < 2; i++) {
            key = &lbl_80421A28[i];
            out = &(&scale.x)[i];
            for (j = 0; j < 8; j++) {
                t0 = key->t[j];
                v0 = key->v[j];
                t1 = key->t[j + 1];
                v1 = key->v[j + 1];
                if (t0 <= x && x <= t1) {
                    *out = (x - t0) * ((v1 - v0) / (t1 - t0)) + v0;
                }
            }
        }
    }
    SpriteSlot_SetJointScaleByName(self + 0x14, base + 0x414, scale.x, scale.y, scale.z);
    SpriteSlot_TickAnim(self + 0x14);
    if (WP(0x4C) != 0) {
        JointByName_GetWorldPosition(&jp, self + 0x14, base + 0x424);
        if (S8(0x1D) == 2 || S8(0x1D) == 3) {
            vis = self[0x28];
        } else {
            vis = 0;
        }
        VfxLaugh_Tick(WP(0x4C), jp, vis, F(0xC4), F(0x2C));
    }
    Timer_Tick((unsigned int *)(w + 0x4));
    Timer_Tick((unsigned int *)(w + 0x8));
    Timer_Tick((unsigned int *)(w + 0xC));
    Timer_Tick((unsigned int *)(w + 0x10));
}
