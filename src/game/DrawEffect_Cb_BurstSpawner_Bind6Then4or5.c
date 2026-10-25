#include "game/DrawEffectAccess.h"

extern void DrawEffect_Cb_KartVfx_Bind6_YawZ(unsigned char *self);
extern void DrawEffect_Cb_KartVfx_Bind4or5_Variant(unsigned char *self);

void DrawEffect_Cb_BurstSpawner_Bind6Then4or5(unsigned char *self)
{
    unsigned char *child;
    int i;

    switch (STATE) {
    case 0:
        child = DrawEffect_SpawnDirect(DrawEffect_Cb_KartVfx_Bind6_YawZ);
        if (child != 0) {
            *(void **)(child + 0x11C) = P(0x11C);
        }
        I(0x180) = 0xE;
        STATE++;
    case 1:
        if (U32(0x180) == 0) {
            for (i = 0; i < 2; i++) {
                child = DrawEffect_SpawnDirect(DrawEffect_Cb_KartVfx_Bind4or5_Variant);
                if (child != 0) {
                    *(int *)(child + 0x10) = (unsigned char)i;
                    *(void **)(child + 0x11C) = P(0x11C);
                }
            }
            DrawEffect_Free(self);
            return;
        }
        break;
    }
    TICK_TIMERS();
}
