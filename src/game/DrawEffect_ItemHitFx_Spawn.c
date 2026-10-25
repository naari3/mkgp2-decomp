#include "game/DrawEffectAccess.h"

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D5740; /* 500.0 */

extern unsigned char lbl_805DF3D0[];
extern float fn_800D3184(const Vec *a, const Vec *b);
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern void DrawEffect_KartDustRing_Update(unsigned char *self);
extern void DrawEffect_KartSpark_Update(unsigned char *self);

void DrawEffect_ItemHitFx_Spawn(const Vec *at, int owner)
{
    Vec pos;
    unsigned char *e;
    signed char ground;
    int i;

    if (lbl_806D5740 < fn_800D3184((Vec *)(lbl_805DF3D0 + 0x80), at)) {
        return;
    }
    Vec3_Copy(&pos, at);
    ground = ItemObject_GetGroundTypeAt(pos, &pos.y, 0);
    if (ground == 0) {
        return;
    }
    switch (ground) {
    case 1:
    case 2:
    case 3:
        e = DrawEffect_SpawnDirect(DrawEffect_KartDustRing_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), &pos);
            ((Vec *)(e + 0x8C))->y += lbl_806D5708;
            *(signed char *)(e + 0x190) = ground;
            *(int *)(e + 0xCC) = owner;
        }
        break;
    case 4:
    case 5:
        for (i = 0; i < 4; i++) {
            unsigned char *s = DrawEffect_SpawnDirect(DrawEffect_KartSpark_Update);
            if (s != 0) {
                Vec3_Copy((Vec *)(s + 0x8C), &pos);
                ((Vec *)(s + 0x8C))->y += lbl_806D56F8;
                *(int *)(s + 0xCC) = owner;
                *(signed char *)(s + 0x190) = ground;
            }
        }
        break;
    }
}
