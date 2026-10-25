#include "game/DrawEffectAccess.h"

extern const float lbl_806D565C; /* 0.0 */
extern const float lbl_806D5660; /* deg->rad */
extern const float lbl_806D5674; /* 1.5 */
extern const float lbl_806D56A4; /* 0.5 */
extern const float lbl_806D56AC; /* 20.0 */
extern const float lbl_806D56CC; /* 2.0 */
extern const float lbl_806D56D4; /* -20.0 */
extern const float lbl_806D56D8; /* 5.0 */
extern const float lbl_806D56E8; /* -60.0 */
extern const float lbl_806D56EC; /* -30.0 */
extern const float lbl_806D56F0; /* pi/4 */

extern void DrawEffect_SparkDescend_Update(unsigned char *self);
extern void DrawEffect_SmokePuff_Update(unsigned char *self);

void DrawEffect_Splatter_Update(unsigned char *self)
{
    unsigned char *e;
    float base = lbl_806D565C;
    float yaw;
    int i;

    for (i = 0; i < 8; i++) {
        e = DrawEffect_SpawnDirect(DrawEffect_SparkDescend_Update);
        if (e != 0) {
            yaw = lbl_806D5660 * Rand_RangeFloat(lbl_806D56D4, lbl_806D56AC) + base;
            GetSpawnPosition((Vec *)(e + 0x8C), 0.0f, 0.0f, Rand_RangeFloat(lbl_806D56CC, lbl_806D56D8));
            Vec2_RotateY((Vec *)(e + 0x8C), (Vec *)(e + 0x8C), yaw);
            Vec3_Add_DestFirst((Vec *)(e + 0x8C), V(0x8C), (Vec *)(e + 0x8C));
            GetSpawnPosition((Vec *)(e + 0xA4), 0.0f, 0.0f, Rand_RangeFloat(lbl_806D56A4, lbl_806D5674));
            Vec2_RotateX((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), lbl_806D5660 * Rand_RangeFloat(lbl_806D56E8, lbl_806D56EC));
            Vec2_RotateY((Vec *)(e + 0xA4), (Vec *)(e + 0xA4), yaw);
        }
        base += lbl_806D56F0;
    }
    e = DrawEffect_SpawnDirect(DrawEffect_SmokePuff_Update);
    if (e != 0) {
        Vec3_Copy((Vec *)(e + 0x8C), V(0x8C));
    }
    DrawEffect_Free(self);
}
