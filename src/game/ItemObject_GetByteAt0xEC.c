#include "game/types/ItemObject.h"

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
