extern "C" void *memset(void *, int, unsigned long);

struct ItemObject {
    signed char inUse;
    unsigned char pad_01[3];
    void *owner;
    unsigned char pad_08[0x1E4];
};

extern ItemObject lbl_80638300[0x100];
extern "C" int lbl_806D14D0;

static inline ItemObject *pool_alloc(void) {
    int cursor = lbl_806D14D0;
    int i;

    for (i = 0; i < 0x100; i++) {
        int index = (cursor + 1) % 0x100;
        ItemObject *item = &lbl_80638300[index];

        if (item->inUse == 0) {
            memset(item, 0, sizeof(ItemObject));
            lbl_806D14D0 = index;
            item->inUse = 1;
            return item;
        }
        cursor++;
    }
    return 0;
}

static inline ItemObject *item_init(ItemObject *item, void *owner) {
    if (item == 0) {
        return 0;
    }
    item->owner = owner;
    return item;
}

extern "C" ItemObject *ItemObject_AllocFromPool(void *owner) {
    return item_init(pool_alloc(), owner);
}
