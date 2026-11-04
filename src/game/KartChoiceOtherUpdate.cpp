#include "game/KartChoiceOwnerPrivate.h"
extern "C" void fn_8023B7FC(KartChoiceOwner *self) {
    if (self->phase < 5) {
        if (self->other) fn_80230ED4(self->other, 1);
    }
}
