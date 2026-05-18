/*
 * AI_KartController accessor: AI_GetItemType @ 0x801E6DA0.
 *
 * Returns the type of the item currently held by the kart's ItemHolder.
 * Returns 0 when no holder is bound (field 0x24 == NULL).
 *
 * The TU sits in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entry (matching the
 * Vtable_CallSlot2.cpp pattern).
 */

extern unsigned int ItemHolder_GetItemType(void *holder);

#pragma exceptions on
unsigned int AI_GetItemType(int self) {
    void *holder = *(void **)(self + 0x24);
    if (holder) {
        return ItemHolder_GetItemType(holder);
    }
    return 0;
}
#pragma exceptions reset
