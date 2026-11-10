/* Forward to the kart's tire FX (KartTireFX_SetRollPair_Joints88_90) once the kart model is loaded. */
#include "game/types/KartDriver.h"

extern void KartTireFX_SetRollPair_Joints88_90(void *tireFX, int value);

int KartDriver_TickAction_78778(KartDriver *self, int value)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    if (self->tireFX != 0) {
        KartTireFX_SetRollPair_Joints88_90(self->tireFX, value);
    }
    return 1;
}
