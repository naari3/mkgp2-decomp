typedef struct ItemHolder {
    unsigned char pad_0x00[0x1c];
    unsigned int itemType;
    unsigned int hasItem;
    unsigned char pad_0x24[0x4];
    unsigned int effectCategory;
} ItemHolder;

unsigned int ItemHolder_GetItemType(ItemHolder *self) {
    return self->itemType;
}

unsigned int ItemHolder_HasItem(ItemHolder *self) {
    return (self->hasItem == 1) ? 1 : 0;
}

unsigned int ItemHolder_GetEffectCategory(ItemHolder *self) {
    return self->effectCategory;
}
