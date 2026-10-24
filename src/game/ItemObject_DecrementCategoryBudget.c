typedef struct ItemOwner {
    unsigned char pad[0x344];
    void *categoryBudget;
} ItemOwner;

typedef struct ItemObject {
    unsigned char pad_00[8];
    int category;
    unsigned char pad_0C[0x178];
    ItemOwner *owner;
} ItemObject;

extern void ItemCategoryBudget_Decrement(void *budget, int category);

void ItemObject_DecrementCategoryBudget(ItemObject *item) {
    if (item != 0) {
        ItemCategoryBudget_Decrement(item->owner->categoryBudget, item->category);
    }
}
