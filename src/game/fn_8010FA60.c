typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_8010F40C(unsigned char *self, unsigned char *sub);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *kart);
extern void Effect_FourSpark_Res65_68_Update(void *e);
extern unsigned char *DrawEffect_SpawnDirect(void (*cb)(void *));
extern void JointByName_GetWorldPosition(void *out, void *slot, const char *name);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec3 *b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, void *a, float b, float c, float d);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern void SpriteSlot_SetJointScaleByName(void *slot, const char *name, float x, float y, float z);

extern const char lbl_80331BD8[];

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item_GrowScale(unsigned char *self, unsigned char *sub, float *k)
{
    *(float *)(sub + 0x14) += 0.3f;
    if (5.0f < *(float *)(sub + 0x14)) {
        *(float *)(sub + 0x14) = 5.0f;
    }
    *k = 0.9f * *k + 0.1f;
    *(float *)(self + 0xC4) = *k * *(float *)(sub + 0x14);
}

static inline void Item_CheckOpenAnim(unsigned char *self)
{
    if (*(char *)(self + 0x1E) == 1) {
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
    }
}

static inline void Item_TickFallFade(unsigned char *self, unsigned char *sub, Vec3 *g1, Vec3 *g2)
{
    float gy;

    switch ((signed char)self[0xC9]) {
    case 0:
        *g1 = *(Vec3 *)(self + 0xA0);
        ItemObject_GetGroundTypeAt(g1, (float *)(sub + 0x18), 0);
        if (*(char *)(self + 0xCB) != 5) {
            *(unsigned int *)(sub + 0x4) = 10;
        } else {
            *(unsigned int *)(sub + 0x4) = 0;
        }
        if (*(char *)(self + 0xCB) == 5) {
            *(float *)(self + 0xBC) = 0.0f;
        }
        *(float *)(sub + 0x1C) = *(float *)(self + 0xC4) / *(float *)(sub + 0x14);
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
    if (sub[0] != 0) {
        *g2 = *(Vec3 *)(self + 0xA0);
        if (ItemObject_GetGroundTypeAt(g2, &gy, 0)) {
            *(float *)(self + 0xA4) = *(float *)(self + 0xA4) + (gy - *(float *)(sub + 0x18));
            *(float *)(sub + 0x18) = gy;
        }
    }
    Item_GrowScale(self, sub, (float *)(sub + 0x1C));
}

void fn_8010FA60(unsigned char *self)
{
    const char *str = lbl_80331BD8;
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;
    Vec3 c;
    Vec3 t;
    Vec3 f9b;
    Vec3 f9a;
    Vec3 f5b;
    Vec3 f5a;
    float s;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x71);
        self[0x8C] = 2;
        self[0x8D] = 0;
        *(float *)(sub + 0x14) = 1.0f;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_8010F40C(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            switch ((signed char)self[0xC9]) {
            case 0:
                Item_PrepareHitRebound(self, sub + 0x40, sub + 0x34, sub + 0x4);
                *(float *)(sub + 0x18) = *(float *)(self + 0xC4) / *(float *)(sub + 0x14);
                self[0xC9]++;
            case 1:
                break;
            }
            if (*(unsigned int *)(sub + 0x4) == 0) {
                if (sub[0] != 0) {
                    ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(sub + 0x9C));
                }
                {
    unsigned char *e;
    Vec3 snd;

    e = DrawEffect_SpawnDirect(Effect_FourSpark_Res65_68_Update);
    if (e != 0) {
        JointByName_GetWorldPosition(e + 0x8C, self + 0x14, str + 0x3FC);
        *(float *)(e + 0xB0) = *(float *)(self + 0xC4);
        *(void **)(e + 0x11C) = *(void **)(sub + 0x9C);
    }
    snd = *(Vec3 *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0xBB, &snd, 0);
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}
                break;
            }
            Item_CheckOpenAnim(self);
            c = *(Vec3 *)(sub + 0x34);
            Vec3_AddNormalizedXZ(self, sub + 0x40, &c);
            Mtx44_GetTranslation_RowMajor(&t, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
            Vec3_Add_DestFirst(self + 0xA0, &t, sub + 0x40);
            Item_GrowScale(self, sub, (float *)(sub + 0x18));
            break;
        case 3:
            switch ((signed char)self[0xC9]) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                *(float *)(sub + 0x18) = 0.0f;
                *(float *)(sub + 0x1C) = *(float *)(self + 0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, sub + 0x18, *(float *)(sub + 0x1C), 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            }
            Item_CheckOpenAnim(self);
            break;
        case 4:
            {
    unsigned char *e;
    Vec3 snd;

    e = DrawEffect_SpawnDirect(Effect_FourSpark_Res65_68_Update);
    if (e != 0) {
        JointByName_GetWorldPosition(e + 0x8C, self + 0x14, str + 0x3FC);
        *(float *)(e + 0xB0) = *(float *)(self + 0xC4);
        *(void **)(e + 0x11C) = *(void **)(sub + 0x9C);
    }
    snd = *(Vec3 *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0xBB, &snd, 0);
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}
            break;
        case 6:
            switch ((signed char)self[0xC9]) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(sub + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                *(unsigned int *)(sub + 0x4) = 30;
                *(float *)(sub + 0x18) = *(float *)(self + 0xC4) / *(float *)(sub + 0x14);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.26179934f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            }
            Item_GrowScale(self, sub, (float *)(sub + 0x18));
            Item_CheckOpenAnim(self);
            break;
        case 7:
            {
    unsigned char *e;
    Vec3 snd;

    e = DrawEffect_SpawnDirect(Effect_FourSpark_Res65_68_Update);
    if (e != 0) {
        JointByName_GetWorldPosition(e + 0x8C, self + 0x14, str + 0x3FC);
        *(float *)(e + 0xB0) = *(float *)(self + 0xC4);
        *(void **)(e + 0x11C) = *(void **)(sub + 0x9C);
    }
    snd = *(Vec3 *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0xBB, &snd, 0);
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}
            break;
        case 9:
            Item_TickFallFade(self, sub, &f9a, &f9b);
            break;
        case 5:
            Item_TickFallFade(self, sub, &f5a, &f5b);
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
    s = 1.0f / *(float *)(sub + 0x14);
    SpriteSlot_SetJointScaleByName(self + 0x14, str + 0x410, s, s, s);
    SpriteSlot_SetJointScaleByName(self + 0x14, str + 0x42C, s, s, s);
    SpriteSlot_SetJointScaleByName(self + 0x14, str + 0x448, s, s, s);
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
