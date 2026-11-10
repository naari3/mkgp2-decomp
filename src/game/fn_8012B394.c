/* fn_8012B394: deleting destructor of the kart preview (kart, tires,
 * driver and the part models). */
#include "game/types/KartPreviewParts.h"

extern void Object_DtorWithGXSync(void *obj, int del);
extern void KartTireFX_Dtor(void *fx, int del);
extern void MemoryManager_TimedFree(void *p);

KartPreviewParts *fn_8012B394(KartPreviewParts *self, short flag)
{
    int i;

    if (self != 0) {
        if (self->kart != 0) {
            Object_DtorWithGXSync(self->kart, 1);
        }
        if (self->tires != 0) {
            KartTireFX_Dtor(self->tires, 1);
        }
        if (self->driver != 0) {
            Object_DtorWithGXSync(self->driver, 1);
        }
        if (self->extraA != 0) {
            Object_DtorWithGXSync(self->extraA, 1);
        }
        if (self->extraB != 0) {
            Object_DtorWithGXSync(self->extraB, 1);
        }
        for (i = 0; i < 49; i++) {
            Object_DtorWithGXSync(self->parts[i], 1);
        }
        if (self->attach != 0) {
            Object_DtorWithGXSync(self->attach, 1);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
