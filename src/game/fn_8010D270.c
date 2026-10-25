typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_8010CC40(unsigned char *self, unsigned char *sub);
extern void fn_8010C110(unsigned char *self, unsigned char *sub);
extern void fn_8010BF20(unsigned char *self, unsigned char *sub);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, void *a, float b, float c, float d);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetWorldPosition(Vec3 *out, void *slot, const char *name);
extern void VfxEffect_UpdateChildPosScaleAlpha_Helper(void *e, Vec3 *pos, float scale, float alpha);
extern void VfxEffect_UpdateChildVisScale_Helper(void *e, Vec3 *pos, float scale, float alpha);

extern const char lbl_80331698[];

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
            *(unsigned int *)(sub + 0x4) = 10;
        } else {
            *(unsigned int *)(sub + 0x4) = 0;
        }
        if (*(char *)(self + 0xCB) == 5) {
            *(float *)(self + 0xBC) = 0.0f;
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
    if (*(char *)(self + 0xCB) != 5) {
        *(float *)(self + 0xBC) += -0.1f;
    }
    g2 = *(Vec3 *)(self + 0xA0);
    if (ItemObject_GetGroundTypeAt(&g2, &gy, 0)) {
        *(float *)(self + 0xA4) = *(float *)(self + 0xA4) + (gy - *(float *)(sub + 0x14));
        *(float *)(sub + 0x14) = gy;
    }
    Item_DecayVelocityScalar(self, 3.0f);
}

void fn_8010D270(unsigned char *self)
{
    const char *str = lbl_80331698;
    unsigned char *sub = self + 0xEC;
    Vec3 jp;
    Vec3 pos;
    Vec3 rot;
    Vec3 c1;
    Vec3 c2;
    Vec3 c3;
    Vec3 c4;
    Vec3 c5;
    Vec3 c6;

    switch ((signed char)self[0xC8]) {
    case 0:
        switch (*(int *)(self + 0x8)) {
        case 0x71:
            SpriteSlot_InitNonLoop(self + 0x14, 0x6C);
            break;
        case 0x72:
            SpriteSlot_InitNonLoop(self + 0x14, 0x6D);
            break;
        case 0x73:
            SpriteSlot_InitNonLoop(self + 0x14, 0x6E);
            break;
        }
        self[0x14] = 4;
        self[0x8C] = 3;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_8010CC40(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            fn_8010C110(self, sub);
            break;
        case 1:
            fn_8010BF20(self, sub);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 3:
            switch ((signed char)self[0xC9]) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
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
            fn_8010BF20(self, sub);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 6:
            switch ((signed char)self[0xC9]) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
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
        case 7:
            fn_8010BF20(self, sub);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
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
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    SpriteSlot_TickAnim(self + 0x14);
    if (*(void **)(sub + 0x4C)) {
        switch (*(int *)(self + 0x8)) {
        case 0x71:
            JointByName_GetWorldPosition(&jp, self + 0x14, str + 0x484);
            jp.y -= 2.0f;
            if (*(signed char *)(self + 0x28) != 0) {
                c1 = jp;
                VfxEffect_UpdateChildPosScaleAlpha_Helper(*(void **)(sub + 0x4C), &c1, *(float *)(self + 0xC4),
                                                          *(float *)(self + 0x2C));
            } else {
                c2 = jp;
                VfxEffect_UpdateChildPosScaleAlpha_Helper(*(void **)(sub + 0x4C), &c2, *(float *)(self + 0xC4),
                                                          0.0f);
            }
            break;
        case 0x72:
            JointByName_GetWorldPosition(&jp, self + 0x14, str + 0x4A0);
            jp.y -= 6.0f;
            if (*(signed char *)(self + 0x28) != 0) {
                c3 = jp;
                VfxEffect_UpdateChildVisScale_Helper(*(void **)(sub + 0x4C), &c3, *(float *)(self + 0xC4),
                                                     *(float *)(self + 0x2C));
            } else {
                c4 = jp;
                VfxEffect_UpdateChildVisScale_Helper(*(void **)(sub + 0x4C), &c4, *(float *)(self + 0xC4),
                                                     0.0f);
            }
            break;
        case 0x73:
            JointByName_GetWorldPosition(&jp, self + 0x14, str + 0x4BC);
            jp.y -= 5.0f;
            if (*(signed char *)(self + 0x28) != 0) {
                c5 = jp;
                VfxEffect_UpdateChildVisScale_Helper(*(void **)(sub + 0x4C), &c5, *(float *)(self + 0xC4),
                                                     *(float *)(self + 0x2C));
            } else {
                c6 = jp;
                VfxEffect_UpdateChildVisScale_Helper(*(void **)(sub + 0x4C), &c6, *(float *)(self + 0xC4),
                                                     0.0f);
            }
            break;
        }
    }
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
