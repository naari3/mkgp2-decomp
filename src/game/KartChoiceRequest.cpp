#include "game/KartChoiceOwnerPrivate.h"
extern "C" void fn_8023B7E4(KartChoiceOwner *self) {
    if (self->phase < 4) self->phase = 4;
}
