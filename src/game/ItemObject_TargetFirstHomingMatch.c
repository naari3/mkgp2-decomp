typedef struct HomingState {
    unsigned char active;
    unsigned char pad_01[0x9B];
    void *target;
} HomingState;

typedef struct ItemObject {
    signed char inUse;
    unsigned char pad_01[7];
    int kind;
    int released;
    unsigned char pad_10[0xB8];
    unsigned char homingMode;
    unsigned char pad_C9[0x23];
    HomingState homing;
    unsigned char pad_18C[0x60];
} ItemObject;

extern ItemObject lbl_80638300[0x100];

static inline ItemObject *find_homing(ItemObject *self, void *target) {
    int i;

    for (i = 0; i < 0x100; i++) {
        ItemObject *item = &lbl_80638300[i];

        if (item->inUse && item->released == 0 && item != self) {
            unsigned char kind = item->kind;

            if ((unsigned char)(kind - 0x2E) <= 2 || kind == 0x31) {
                HomingState *homing = &item->homing;

                if ((int)item->homingMode == 1 && homing->target == target &&
                    homing->active != 0) {
                    return item;
                }
            }
        }
    }
    return 0;
}

void ItemObject_TargetFirstHomingMatch(ItemObject *self, void *target) {
    ItemObject *item = find_homing(self, target);

    if (item != 0) {
        item->pad_18C[0] = 1;
    }
}
