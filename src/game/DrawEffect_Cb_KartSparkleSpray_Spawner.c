#include "game/DrawEffectAccess.h"

extern void DrawEffect_Cb_KartSparkleSpray_Tick(unsigned char *self);
extern int Rand_RangeInt(int lo, int hi);

void DrawEffect_Cb_KartSparkleSpray_Spawner(unsigned char *self)
{
    unsigned char *e;

    switch (STATE) {
    case 0:
        switch (I(0x8)) {
        case 0xA:
            I(0x10) = 0;
            break;
        case 0xB:
            I(0x10) = 1;
            break;
        }
        STATE++;
        break;
    case 1:
        break;
    }
    if (U32(0x180) == 0) {
        e = DrawEffect_SpawnDirect(DrawEffect_Cb_KartSparkleSpray_Tick);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), V(0x8C));
            *(int *)(e + 0x10) = I(0x10);
        }
        if (I(0x10) == 0) {
            U32(0x180) = (unsigned char)Rand_RangeInt(0x1E, 0x32);
        } else {
            U32(0x180) = (unsigned char)Rand_RangeInt(0x5A, 0x96);
        }
    }
    TICK_TIMERS();
}
