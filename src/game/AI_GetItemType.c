/*
 * AI_KartController accessor: AI_GetItemType @ 0x801E6DA0.
 *
 * Returns the type of the item currently held by the kart's ItemHolder.
 * Returns 0 when no holder is bound (field 0x24 == NULL).
 *
 * Built with GC/2.6: reading the field through a const-qualified self lets
 * the scheduler hoist `lwz r3,0x24(r3)` above the `stw r0,0x14(r1)` LR save.
 */

extern unsigned int ItemHolder_GetItemType(void *holder);

#pragma exceptions on
unsigned int AI_GetItemType(const char *self) {
    void *holder = *(void *const *)(self + 0x24);
    return holder ? ItemHolder_GetItemType(holder) : 0;
}
#pragma exceptions reset
