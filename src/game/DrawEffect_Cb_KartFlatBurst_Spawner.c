#include "game/DrawEffectAccess.h"

extern const float lbl_806D56AC; /* 20.0 */
extern const float lbl_806D56C8; /* 8.0 */
extern const float lbl_806D56CC; /* 2.0 */
extern const float lbl_806D56D4; /* -20.0 */
extern const float lbl_806D56D8; /* 5.0 */
extern const float lbl_806D56DC; /* -2.0 */

extern void DrawEffect_Cb_KartFlatBurst_Tick(unsigned char *self);

void DrawEffect_Cb_KartFlatBurst_Spawner(unsigned char *self)
{
    unsigned char *e;

    switch (STATE) {
    case 0:
        U32(0x180) = 0;
        STATE++;
    case 1:
        if (U32(0x180) == 0) {
            e = DrawEffect_SpawnDirect(DrawEffect_Cb_KartFlatBurst_Tick);
            if (e != 0) {
                ((Vec *)(e + 0x8C))->x = Rand_RangeFloat(lbl_806D56D4, lbl_806D56AC);
                ((Vec *)(e + 0x8C))->y = Rand_RangeFloat(lbl_806D56CC, lbl_806D56D8);
                ((Vec *)(e + 0x8C))->z = Rand_RangeFloat(lbl_806D56DC, lbl_806D56CC);
                Vec3_Scale((Vec *)(e + 0x8C), (Vec *)(e + 0x8C), lbl_806D56C8);
                Vec2_RotateY((Vec *)(e + 0x8C), (Vec *)(e + 0x8C), F(0x9C));
                Vec3_Add_DestFirst((Vec *)(e + 0x8C), V(0x8C), (Vec *)(e + 0x8C));
            }
            U32(0x180) = 5;
        }
        break;
    }
    TICK_TIMERS();
}
