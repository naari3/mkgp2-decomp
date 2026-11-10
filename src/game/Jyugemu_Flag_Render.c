/* Render the Jyugemu flag model once it is visible. */
#include "game/types/JyugemuFlag.h"

extern void Object_RenderJObjTree(void *model, int mask);

int Jyugemu_Flag_Render(JyugemuFlag *self)
{
    if (self->model == 0) {
        return 0;
    }
    if (self->kart_driver == 0) {
        return 0;
    }
    Object_RenderJObjTree(self->model, 7);
    return 1;
}
