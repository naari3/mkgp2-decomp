#include "game/KartChoiceOwnerPrivate.h"
KartChoiceOwner::~KartChoiceOwner() {
    if (other) { delete other; other = 0; }
    /* The child vtable is owned elsewhere; deletion uses its virtual root view. */
    if (child) { delete (VObject *)child; child = 0; }
}
