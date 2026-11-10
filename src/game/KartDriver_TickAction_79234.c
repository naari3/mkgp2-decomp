/* Forward to the kart's tire FX (KartTireFX_AddPitch) once the kart model is loaded. */
#include "game/types/KartDriver.h"

extern void KartTireFX_AddPitch(void *tireFX, float value);

int KartDriver_TickAction_79234(KartDriver *self, float value)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    if (self->tireFX != 0) {
        KartTireFX_AddPitch(self->tireFX, value);
    }
    return 1;
}
