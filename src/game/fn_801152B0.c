extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void fn_800D748C(void);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(void));
extern void *AnimStatePool_Alloc(void *pool);
extern void AnimStatePool_Free(void *p);
extern void SpriteSlot_Container_Free(void *self);
extern void fn_80115118(unsigned char *self, unsigned char *ctx);
extern void fn_80114990(unsigned char *self, unsigned char *ctx);
extern int lbl_806CF400;
extern int lbl_806CF420;
extern unsigned char lbl_80421E34[];
extern unsigned char lbl_80421EE8[];

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_801152B0(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, (unsigned char)lbl_806CF400);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        self[0x14] = 4;
        *(unsigned char **)(sub + 0x5C) = ItemObject_AllocFromPool(fn_800D748C);
        if (*(unsigned char **)(sub + 0x5C)) {
            SpriteSlot_InitNonLoop(*(unsigned char **)(sub + 0x5C) + 0x14, (unsigned char)lbl_806CF420);
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(*(unsigned char **)(sub + 0x5C) + 0x14, 1);
        }
        *(void **)(sub + 0x6C) = AnimStatePool_Alloc(lbl_80421E34);
        *(void **)(sub + 0x70) = AnimStatePool_Alloc(lbl_80421EE8);
        self[0xC8] = 1;
        self[0xC9] = 0;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            fn_80115118(self, sub);
            break;
        case 1:
            fn_80114990(self, sub);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        if (*(void **)(sub + 0x6C)) {
            AnimStatePool_Free(*(void **)(sub + 0x6C));
        }
        if (*(void **)(sub + 0x70)) {
            AnimStatePool_Free(*(void **)(sub + 0x70));
        }
        if (*(void **)(sub + 0x5C)) {
            SpriteSlot_Container_Free(*(void **)(sub + 0x5C));
        }
        SpriteSlot_Container_Free(self);
        return;
    }
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
