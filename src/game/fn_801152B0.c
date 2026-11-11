#include "game/types/AnimEntry.h"
/* --- owned .data 0x80421DC8..0x80421F20 (tools/own_data.py) --- */
#pragma force_active on
unsigned int lbl_80421DC8[4] = { 0x00000000, 0x00000009, 0x0000000F, 0xFFFFFFFE };
unsigned int lbl_80421DD8[3] = { 0x3F800000, 0x3FA66666, 0x3F800000 };
unsigned int lbl_80421DE4[5] = { 0x00000000, 0x00000004, 0x0000000A, 0x0000000F, 0xFFFFFFFE };
unsigned int lbl_80421DF8[4] = { 0x3F800000, 0x40000000, 0x3F800000, 0x3F800000 };
unsigned int lbl_80421E08[6] = { 0x00000000, 0x00000006, 0x0000000A, 0x0000000D, 0x0000000F, 0xFFFFFFFE };
unsigned int lbl_80421E20[5] = { 0x3F800000, 0x40000000, 0x3F99999A, 0x3F800000, 0x3F800000 };
AnimEntry lbl_80421E34[7] = {
    { 0, { 0, 0, 0 }, &lbl_80421DC8 },
    { 8, { 0, 0, 0 }, &lbl_80421DD8 },
    { 0, { 0, 0, 0 }, &lbl_80421DE4 },
    { 9, { 0, 0, 0 }, &lbl_80421DF8 },
    { 0, { 0, 0, 0 }, &lbl_80421E08 },
    { 10, { 0, 0, 0 }, &lbl_80421E20 },
    { 13, { 0, 0, 0 }, 0 }
};
unsigned int lbl_80421E6C[5] = { 0x00000000, 0x00000004, 0x00000009, 0x0000000F, 0xFFFFFFFE };
unsigned int lbl_80421E80[4] = { 0x3F800000, 0x3F8CCCCD, 0x3FC66666, 0x3F800000 };
unsigned int lbl_80421E90[6] = { 0x00000000, 0x00000005, 0x0000000A, 0x0000000C, 0x0000000F, 0xFFFFFFFE };
unsigned int lbl_80421EA8[5] = { 0x3F800000, 0x3E800000, 0x3FD00000, 0x3F570A3D, 0x3F800000 };
unsigned int lbl_80421EBC[6] = { 0x00000000, 0x00000005, 0x0000000A, 0x0000000C, 0x0000000F, 0xFFFFFFFE };
unsigned int lbl_80421ED4[5] = { 0x3F800000, 0x3EB851EC, 0x3FAA3D71, 0x3F800000, 0x3F800000 };
AnimEntry lbl_80421EE8[7] = {
    { 0, { 0, 0, 0 }, &lbl_80421E6C },
    { 8, { 0, 0, 0 }, &lbl_80421E80 },
    { 0, { 0, 0, 0 }, &lbl_80421E90 },
    { 9, { 0, 0, 0 }, &lbl_80421EA8 },
    { 0, { 0, 0, 0 }, &lbl_80421EBC },
    { 10, { 0, 0, 0 }, &lbl_80421ED4 },
    { 13, { 0, 0, 0 }, 0 }
};
#pragma force_active reset
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
