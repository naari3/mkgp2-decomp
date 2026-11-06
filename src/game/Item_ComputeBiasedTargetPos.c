/* Item_ComputeBiasedTargetPos (0x800D8E20): aim point 15*k units from the
 * driver's kart, horizontally towards `target`, where k is a per-character
 * reach factor. If the horizontal direction is zero, use +Z for the reach. */
#include "game/DrawEffectAccess.h"

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
    case 0: k = 1.0f; break;
    case 1: k = 1.0f; break;
    case 2: k = 1.1f; break;
    case 3: k = 1.0f; break;
    case 4: k = 1.2f; break;
    case 5: k = 1.0f; break;
    case 6: k = 1.2f; break;
    case 7: k = 1.0f; break;
    case 8: k = 1.0f; break;
    case 9: k = 1.0f; break;
    case 10: k = 1.0f; break;
    case 11: k = 1.0f; break;
    case 12: k = 1.0f; break;
    default: k = 1.0f; break;
    }
    k = 15.0f * k;
    if (mag) {
        mag = 1.0f / mag;
        Vec3_ScaleXZ(&d, &d, mag * k);
    } else {
        GetSpawnPosition(&d, 0.0f, d.y, k);
    }
    Vec3_Add_DestFirst(out, &kartPos, &d);
}
