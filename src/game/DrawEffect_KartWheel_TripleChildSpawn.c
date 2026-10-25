#include "game/DrawEffectAccess.h"

typedef struct WheelWork {
    unsigned char pad00[0x10];
    unsigned char *children[3];  /* 0x0DC */
} WheelWork;

extern void fn_800AF4F8(unsigned char *self);

void DrawEffect_KartWheel_TripleChildSpawn(unsigned char *self)
{
    WheelWork *work = (WheelWork *)(self + 0xCC);
    int i;

    switch (STATE) {
    case 0:
        for (i = 0; i < 3; i++) {
            work->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (work->children[i] != 0) {
                if (i == 0) {
                    VfxSlot_BindResourceEx(SLOT(work->children[i]), 0x55, 0);
                } else {
                    VfxSlot_BindResourceEx(SLOT(work->children[i]), 0x54, 0);
                }
                work->children[i][0x28] = 0;
                if (i == 2) {
                    *(float *)(work->children[i] + 0x150) = 0.5f;
                }
            }
        }
        STATE++;
    case 1:
        if (FINISHED) {
            for (i = 0; i < 3; i++) {
                DrawEffect_Free(work->children[i]);
                work->children[i] = 0;
            }
            DrawEffect_Free(self);
        }
        break;
    }
}
