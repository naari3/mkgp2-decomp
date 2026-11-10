/* Draw all 15 debris particles while the burst is active. */
#include "game/types/DebrisParticle.h"

#include "game/types/DebrisBurst.h"

extern void clItemBoxResponder_DrawDebrisParticle(DebrisParticle *p);

int clItemBoxResponder_DrawDebris(DebrisBurst *self)
{
    unsigned int i;

    if (self->active == 0) {
        return 0;
    }
    for (i = 0; i < 15; i++) {
        clItemBoxResponder_DrawDebrisParticle(&self->particles[i]);
    }
    return 1;
}
