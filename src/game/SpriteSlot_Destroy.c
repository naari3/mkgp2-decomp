/* Destroy a sprite slot's object. */
#include "game/types/SpriteSlot.h"

extern void Object_DtorWithGXSync(void *object, int del);

void SpriteSlot_Destroy(SpriteSlot *self)
{
    if (self->object != 0) {
        Object_DtorWithGXSync(self->object, 1);
        self->object = 0;
    }
}
