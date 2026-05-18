/*
 * AI_KartController accessor: AI_HasItem @ 0x801E6D6C.
 *
 * Returns 1 if the ItemHolder bound to this kart controller currently
 * holds an item, 0 otherwise. Returns 0 when no holder is bound.
 *
 * The TU sits in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entry (matching the
 * Vtable_CallSlot2.cpp pattern).
 */

extern unsigned int ItemHolder_HasItem(void *holder);

#pragma exceptions on
unsigned int AI_HasItem(int self) {
    void *holder = *(void **)(self + 0x24);
    if (holder) {
        return ItemHolder_HasItem(holder);
    }
    return 0;
}
#pragma exceptions reset
