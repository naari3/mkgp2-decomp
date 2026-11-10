/* Forward to the kart's tire FX (KartTireFX_AddYaw) once the kart model is loaded. */
#include "game/types/KartDriver.h"

extern void KartTireFX_AddYaw(void *tireFX, float value);

int KartDriver_TriggerSlotC3Action(KartDriver *self, float value)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    if (self->tireFX != 0) {
        KartTireFX_AddYaw(self->tireFX, value);
    }
    return 1;
}
