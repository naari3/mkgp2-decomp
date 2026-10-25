#include "game/DrawEffectAccess.h"

extern const float lbl_806D63AC; /* 0.3 */

typedef struct BombWork {
    unsigned char pad00[0x4C];
    unsigned char *fx[4];        /* 0x138 */
} BombWork;

extern void fn_800AF4F8(unsigned char *self);
extern void VfxSlot_SetAnimSpeed(void *slot, float speed);
extern void SpriteSlot_Container_Free(void *self);

void BombExplosion_InitOrDestroy(unsigned char *self)
{
    BombWork *work = (BombWork *)(self + 0xEC);
    int i;

    switch (S8(0xC8)) {
    case 0:
        I(0xC) = 0;
        I(0x8) = 0x53;
        U8(0x1C) = 0x9B;
        work->fx[0] = DrawEffect_SpawnDirect(fn_800AF4F8);
        if (work->fx[0] != 0) {
            VfxSlot_BindResource(SLOT(work->fx[0]), 0x4F);
            VfxSlot_SetMatrixSourceEnabled(SLOT(work->fx[0]), 1);
            work->fx[0][0x14] = 4;
            VfxSlot_SetAnimSpeed(SLOT(work->fx[0]), lbl_806D63AC);
            work->fx[0][0x28] = 0;
        }
        for (i = 1; i < 4; i++) {
            work->fx[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (work->fx[i] != 0) {
                VfxSlot_BindResource(SLOT(work->fx[i]), 0x8A);
                VfxSlot_SetMatrixSourceEnabled(SLOT(work->fx[i]), 1);
                work->fx[i][0x14] = 4;
                work->fx[i][0x28] = 0;
            }
        }
        S8(0xC8) = 1;
    case 1:
        if (S8(0x18C)) {
            DrawEffect_Free(work->fx[0]);
            work->fx[0] = 0;
            for (i = 1; i < 4; i++) {
                DrawEffect_Free(work->fx[i]);
                work->fx[i] = 0;
            }
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}
