/* Forward to the kart's tire FX (KartTireFX_SetVisibleAll4Wheels) once the kart model is loaded. */
#include "game/types/KartDriver.h"

extern void KartTireFX_SetVisibleAll4Wheels(void *tireFX, int value);

int KartDriver_TickAction_78d00(KartDriver *self, int value)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    if (self->tireFX != 0) {
        KartTireFX_SetVisibleAll4Wheels(self->tireFX, value);
    }
    return 1;
}
