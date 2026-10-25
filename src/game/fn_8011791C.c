typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void fn_80117494(unsigned char *self, unsigned char *ctx);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetWorldPosition(Vec3 *out, void *slot, const char *name);
extern void VfxEffect_UpdateTwoChildSpinAndSound_Helper(void *e, Vec3 pos, float a, float b);
extern unsigned char *DrawEffect_SpawnDirect(void *fn);
extern void Effect_Burst_Res8F_Update(void *e);
extern char lbl_803324C0[];
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

void fn_8011791C(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    unsigned char *o;
    Vec3 wp;
    Vec3 pos;
    Vec3 rot;

    switch ((signed char)self[0xC8]) {
    case 0:
        sub[0x90] = 1;
        SpriteSlot_InitNonLoop(self + 0x14, 0x8F);
        self[0x14] = 4;
        self[0x8C] = 3;
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
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
                self[0x28] = 1;
                *(float *)(self + 0x2C) = 0.0f;
                self[0xCA]++;
            case 1:
                GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 0.5f, 2.0943947f, 1.0f);
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
                    Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
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
            fn_80117494(self, sub);
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            o = ItemObject_SpawnWithAlias(0x64, 0xFF);
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
            o = ItemObject_SpawnWithAlias(0x64, 0xFF);
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
            Item_DecayVelocityScalar(self, 3.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.26179934f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 5:
            o = ItemObject_SpawnWithAlias(0x64, 0xFF);
            if (o) {
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
        if (*(unsigned char **)(sub + 0x4C)) {
            (*(unsigned char **)(sub + 0x4C))[0xC9] = 1;
        }
        *(void **)(sub + 0x4C) = 0;
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
        JointByName_GetWorldPosition(&wp, self + 0x14, lbl_803324C0);
        VfxEffect_UpdateTwoChildSpinAndSound_Helper(*(void **)(sub + 0x4C), wp, *(float *)(self + 0xC4), *(float *)(self + 0x2C));
        o = DrawEffect_SpawnDirect(Effect_Burst_Res8F_Update);
        Vec3_Copy(o + 0x8C, &wp);
        Effect_Burst_Res8F_Update(o);
    }
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
