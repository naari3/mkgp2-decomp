/* Local matrix of the kart's root joint, or NULL before it is loaded. */
#include "game/types/KartDriver.h"

extern void *Object_GetJObjLocalMatrix(void *model);

void *KartDriver_GetKartRootMtx(KartDriver *self)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    return Object_GetJObjLocalMatrix(self->model);
}
