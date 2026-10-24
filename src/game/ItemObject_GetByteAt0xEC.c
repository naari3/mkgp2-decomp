typedef struct ItemObject {
    unsigned char pad_000[0xA0];
    float position[3];
    unsigned char pad_0AC[0x40];
    unsigned char bytes[4];
    unsigned char pad_0F0[0x78];
    int field168;
    unsigned char pad_16C[0x14];
    int pair180[2];
} ItemObject;

unsigned char ItemObject_GetByteAt0xEC(ItemObject *item, int index) {
    if (item == 0) {
        return 0;
    }
    if (index < 0 || index > 3) {
        return 0;
    }
    return item->bytes[index];
}

void ItemObject_SetByteAt0xEC(ItemObject *item, int index, unsigned char value) {
    if (item == 0) {
        return;
    }
    if (index < 0 || index > 3) {
        return;
    }
    item->bytes[index] = value;
}

void ItemObject_SetField168(ItemObject *item, int value) {
    if (item != 0) {
        item->field168 = value;
    }
}

void ItemObject_SetPair180(ItemObject *item, int a, int b) {
    if (item != 0) {
        item->pair180[0] = a;
        item->pair180[1] = b;
    }
}

float *ItemObject_GetPositionPtr(ItemObject *item) {
    if (item != 0) {
        return item->position;
    }
    return 0;
}
