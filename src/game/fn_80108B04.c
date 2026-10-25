typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_80108484(unsigned char *self, unsigned char *ctx);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern unsigned char *DrawEffect_SpawnDirect(void *fn);
extern void Effect_KartAttach_Res59_Update(void);
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
extern unsigned char lbl_806CF3E0[4];

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80108B04(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;
    Vec3 se0;
    Vec3 se4;
    unsigned char *e;
    int cb;

    switch ((signed char)self[0xC8]) {
    case 0:
        *(int *)(self + 0x8) = 0x69;
        SpriteSlot_InitNonLoop(self + 0x14, lbl_806CF3E0[*(int *)(self + 0x10)]);
        sub[0x90] = 1;
        self[0x8C] = 2;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_80108484(self, sub);
        break;
    case 2:
        switch (cb = (signed char)self[0xCB]) {
        case 0:
            se0 = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0x94, &se0, 0);
            e = DrawEffect_SpawnDirect(Effect_KartAttach_Res59_Update);
            if (e) {
                Vec3_Copy(e + 0x8C, self + 0xA0);
                *(int *)(e + 0x11C) = *(int *)(sub + 0x9C);
                if ((signed char)self[0xCB] == 0) {
                    *(int *)(e + 0x10) = 1;
                }
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
            if (Item_AdvanceTetherToJoint13(self, sub + 0x14, *(float *)(sub + 0x18), 0.0f, 0.0f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            se4 = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0x94, &se4, 0);
            e = DrawEffect_SpawnDirect(Effect_KartAttach_Res59_Update);
            if (e) {
                Vec3_Copy(e + 0x8C, self + 0xA0);
                *(int *)(e + 0x11C) = *(int *)(sub + 0x9C);
                if ((signed char)self[0xCB] == 0) {
                    *(int *)(e + 0x10) = 1;
                }
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
            Item_DecayVelocityScalar(self, 2.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.0f, 0.0f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 9:
            switch ((signed char)self[0xC9]) {
            case 0:
                if (cb != 5) {
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
                    break;
                }
            }
            if (*(char *)(self + 0xCB) != 5) {
                *(float *)(self + 0xBC) += -0.1f;
            }
            Item_DecayVelocityScalar(self, 2.0f);
            break;
        case 5:
            switch ((signed char)self[0xC9]) {
            case 0:
                if (cb != 5) {
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
                    break;
                }
            }
            if (*(char *)(self + 0xCB) != 5) {
                *(float *)(self + 0xBC) += -0.1f;
            }
            Item_DecayVelocityScalar(self, 2.0f);
            break;
        }
        break;
    case 3:
        if (*(int *)(self + 0x10) == 0) {
            ItemObject_DecrementCategoryBudget(self);
        }
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
