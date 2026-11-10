#include "game/types/ItemHolder.h"

unsigned int ItemHolder_GetItemType(ItemHolder *self) {
    return self->itemType;
}

unsigned int ItemHolder_HasItem(ItemHolder *self) {
    return (self->hasItem == 1) ? 1 : 0;
}

unsigned int ItemHolder_GetEffectCategory(ItemHolder *self) {
    return self->effectCategory;
}
