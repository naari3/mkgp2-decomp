typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern unsigned char *ItemObject_AllocGabyou(void);
extern void Item_RenderFlyingFromKart(unsigned char *self, void *obj, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void fn_80108B04(void);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern char lbl_80331628[];
extern const float lbl_806D6718;
extern const float lbl_806D6740;
extern const float lbl_806D672C;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80109044(unsigned char *self)
{
    Vec3 pos;
    Vec3 rot;
    int i;
    unsigned char *o;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x62);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80331628, 0x10, 1);
        self[0x28] = 1;
        *(float *)(self + 0x2C) = lbl_806D6718;
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, lbl_806D6718);
        SpriteSlot_SetScale(self + 0x14, lbl_806D6718);
        *(unsigned char **)(self + 0x148) = ItemObject_AllocGabyou();
        if (*(unsigned char **)(self + 0x148)) {
            *(int *)(*(unsigned char **)(self + 0x148) + 0x10) = 1;
        }
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        Item_RenderFlyingFromKart(self, *(void **)(self + 0x148), 1, lbl_806D6740, lbl_806D6718, lbl_806D672C);
        if (*(unsigned char **)(self + 0x148)) {
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, *(float *)(*(unsigned char **)(self + 0x148) + 0x20));
        }
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(self + 0x184))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        if (*(signed char *)(self + 0x18C)) {
            self[0x28] = 1;
            if (*(char *)(self + 0x18C) == 1) {
                for (i = 0; i < 5; i++) {
                    o = ItemObject_AllocFromPool(fn_80108B04);
                    if (o) {
                        *(int *)(o + 0x10) = (signed char)i;
                        o[0x1DC] = self[0x1DC];
                        *(int *)(o + 0x1E0) = *(int *)(self + 0x1E0);
                        *(int *)(o + 0x180) = *(int *)(self + 0x180);
                        *(int *)(o + 0x184) = *(int *)(self + 0x184);
                        Vec3_Copy(o + 0x190, self + 0x190);
                    }
                }
            }
            SpriteSlot_Container_Free(*(void **)(self + 0x148));
            *(void **)(self + 0x148) = 0;
            self[0x18C] = 0;
            self[0x28] = 0;
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
    }
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF0));
    ItemObject_TickTimer((unsigned int *)(self + 0xF4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF8));
    ItemObject_TickTimer((unsigned int *)(self + 0xFC));
}
