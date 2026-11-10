/* Forward to the kart's tire FX (KartTireFX_AddSpinBoth) once the kart model is loaded. */
#include "game/types/KartDriver.h"

extern void KartTireFX_AddSpinBoth(void *tireFX, float value);

int KartDriver_TickAction_79244(KartDriver *self, float value)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    if (self->tireFX != 0) {
        KartTireFX_AddSpinBoth(self->tireFX, value);
    }
    return 1;
}
