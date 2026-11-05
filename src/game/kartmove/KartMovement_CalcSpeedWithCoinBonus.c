#include "game/kartmove/speed_private.h"
#pragma exceptions on
float KartMovement_CalcSpeedWithCoinBonus(KartSpeedState *__restrict k, unsigned char bonus) {
    float result;
    float s;
    s = k->velocity.z*k->velocity.z + (k->velocity.x*k->velocity.x + k->velocity.y*k->velocity.y);
    KART_SPEED_ROOT(s);
    result = s;
    if (bonus == 1) result = s * (lbl_806D96D4 + k->coinBonus);
    return result * lbl_806D96DC;
}
