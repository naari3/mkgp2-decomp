typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void HandOverItem_HandToHandTick(unsigned char *self, unsigned char *sub);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void HandOverItem_Tick(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x53);
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        HandOverItem_HandToHandTick(self, sub);
        break;
    case 2:
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        (*(unsigned char **)(sub + 0x98))[0x2B1] = 0;
        SpriteSlot_Container_Free(self);
        return;
    }
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
