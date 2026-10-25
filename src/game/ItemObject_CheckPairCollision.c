/* ItemObject_CheckPairCollision (0x800D7ACC): sphere test between two item
 * objects; on overlap the lower-priority one (or both on a tie) is pushed out
 * along the centre line and flagged as hit. */
#include "game/DrawEffectAccess.h"

extern float fn_800D3184(const Vec *a, const Vec *b);

void ItemObject_CheckPairCollision(unsigned char *a, unsigned char *b)
{
    unsigned char *obj[2];
    Vec d;
    Vec pos[2];
    float rad[2];
    int hit[2];
    int i;

    if (a == 0 || b == 0) {
        return;
    }
    obj[0] = a;
    obj[1] = b;
    if ((int)a[0x8C] == 1 && (int)b[0x8C] == 1) {
        return;
    }

    for (i = 0; i < 2; i++) {
        Vec3_Copy(&pos[i], (Vec *)(obj[i] + 0xCC));
        rad[i] = *(float *)(obj[i] + 0xD8);
    }

    if (fn_800D3184(&pos[0], &pos[1]) - rad[0] - rad[1] < 0.0f) {
        if ((signed char)obj[0][0x8C] < (signed char)obj[1][0x8C]) {
            hit[0] = 1;
            hit[1] = 0;
        } else if ((signed char)obj[0][0x8C] == (signed char)obj[1][0x8C]) {
            hit[0] = 1;
            hit[1] = 1;
        } else {
            hit[0] = 0;
            hit[1] = 1;
        }

        for (i = 0; i < 2; i++) {
            if (hit[i] != 0) {

                obj[i][0x8D] = 2;
                obj[i][0x8E] = 1;
                Vec3_Subtract_DestFirst(&d, &pos[i], &pos[1 - i]);
                Vec3_Scale(&d, &d, rad[1 - i] * (1.0f / Vec3_Magnitude_Wrapper(&d)));
                Vec3_Add_DestFirst((Vec *)(obj[i] + 0x90), &d, (Vec *)(obj[1 - i] + 0xB8));
            }
        }
    }
}
