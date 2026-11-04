#include "game/KartChoiceOwnerPrivate.h"
ChoiceChild::~ChoiceChild() {
    for (int i = 0; i < 4; ++i) SpriteHandle_Destroy(sprites[i]);
}
