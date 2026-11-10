/* fn_8012BDF4: clears a kart preview before its models are loaded. */
#include "game/types/KartPreviewParts.h"

void fn_8012BDF4(KartPreviewParts *self)
{
    int i;

    self->kart = 0;
    self->tires = 0;
    self->driver = 0;
    self->extraA = 0;
    self->extraB = 0;
    self->fD8 = 0;
    self->fDC[0] = 0.0f;
    self->fDC[1] = 0.0f;
    self->fDC[2] = 0.0f;
    for (i = 0; i < 49; i++) {
        self->parts[i] = 0;
    }
    self->characterId = -1;
    self->animNext = 0;
    self->animCur = self->animNext;
    self->animBase = 0;
    self->fF8 = 0.0f;
    self->fFC = 0.0f;
    self->f100 = 1.0f;
    self->f104 = 0;
    self->f108 = 0.0f;
    self->f10C = 0.0f;
    self->f110 = 0.0f;
    self->f114 = 0.0f;
    self->f118 = 0.0f;
    self->f11C = 0.0f;
    self->f120 = 0.0f;
    self->attach = 0;
    self->attachJoint = 0;
    self->f144 = 0;
    self->f148 = 0;
    self->f14C = 0;
    self->f150 = 0;
    self->f154 = 0;
    self->f158 = 0;
    self->f15C = 0;
    self->f160 = 0;
    self->f164 = 0;
}
