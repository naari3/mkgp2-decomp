extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);

void fn_8010BEE0(unsigned char *self)
{
    if (*(signed char *)(self + 0x18C)) {
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
    }
}
