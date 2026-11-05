#include "game/kartmove/speed_private.h"
#pragma exceptions on
float KartMovement_CalcCurrentSpeed(KartSpeedState *__restrict k) {
    float s;
    s = k->velocity.z*k->velocity.z + (k->velocity.x*k->velocity.x + k->velocity.y*k->velocity.y);
    KART_SPEED_ROOT(s);
    return s * lbl_806D96DC;
}
