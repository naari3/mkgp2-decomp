/* Item_ComputeBiasedTargetPos (0x800D8E20): aim point 15*k units from the
 * driver's kart, horizontally towards `target`, where k is a per-character
 * reach factor. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5AB8; /* 1.0 */
extern const float lbl_806D5ABC; /* 1.1 */
extern const float lbl_806D5AC0; /* 1.2 */
extern const float lbl_806D5AC4; /* 15.0 */
extern const float lbl_806D5AC8; /* 0.0 */
extern float Vec3_HorizontalMagnitude(const Vec *v);
extern void Vec3_ScaleXZ(Vec *dst, const Vec *src, float s);

void Item_ComputeBiasedTargetPos(Vec *out, const Vec *target, unsigned char *driver)
{
    Vec kartPos;
    Vec d;
    float mag;
    float k;

    Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(driver));
    Vec3_Subtract_DestFirst(&d, target, &kartPos);
    mag = Vec3_HorizontalMagnitude(&d);
    switch (*(unsigned int *)(driver + 0x1F8)) {
    case 0: k = lbl_806D5AB8; break;
    case 1: k = lbl_806D5AB8; break;
    case 2: k = lbl_806D5ABC; break;
    case 3: k = lbl_806D5AB8; break;
    case 4: k = lbl_806D5AC0; break;
    case 5: k = lbl_806D5AB8; break;
    case 6: k = lbl_806D5AC0; break;
    case 7: k = lbl_806D5AB8; break;
    case 8: k = lbl_806D5AB8; break;
    case 9: k = lbl_806D5AB8; break;
    case 10: k = lbl_806D5AB8; break;
    case 11: k = lbl_806D5AB8; break;
    case 12: k = lbl_806D5AB8; break;
    default: k = lbl_806D5AB8; break;
    }
    k = lbl_806D5AC4 * k;
    if (mag != lbl_806D5AC8) {
        Vec3_ScaleXZ(&d, &d, (lbl_806D5AB8 / mag) * k);
    } else {
        GetSpawnPosition(&d, lbl_806D5AC8, d.y, lbl_806D5AC8);
    }
    Vec3_Add_DestFirst(out, &kartPos, &d);
}
