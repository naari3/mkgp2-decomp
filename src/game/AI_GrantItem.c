/*
 * AI_KartController accessor: AI_GrantItem @ 0x801E65B8.
 *
 * Tries to give `itemId` to the kart controller's bound ItemHolder.
 *
 *   - Returns 0 if itemId < 1.
 *   - When `force` is 0, returns 0 if the holder already has an item bound
 *     (ItemHolder_GetItemType != 0).
 *   - Otherwise, sets the item, plays SE 9 on the bound SoundObj, and if a
 *     pending tornado-effect counter (+0xC0) is positive, clears the
 *     ItemEffectBus tornado event (id 0x1A) and the tornado visual on the
 *     bound TornadoEffect, then resets the timer pair (+0xA8 = -1, +0xC0 = 0).
 *   - Returns 1 on success.
 *
 * Lives in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps the
 * function so CW auto-emits the extab/extabindex entry (matching the
 * AI_HasItem pattern).
 */

extern int ItemHolder_GetItemType(void *holder);
extern void ItemHolder_SetItem(void *holder, int itemId, int flags);
extern void SoundObj_PlaySE(void *sound, int seId);
extern void fn_80091438(void *bus, int eventId);
extern void fn_80058534(void *effect, int eventId);

#pragma exceptions on
unsigned int AI_GrantItem(int self, int itemId, unsigned char force) {
    if (itemId <= 0) {
        return 0;
    }
    if (force == 0 && ItemHolder_GetItemType(*(void **)(self + 0x24)) != 0) {
        return 0;
    }
    ItemHolder_SetItem(*(void **)(self + 0x24), itemId, 0);
    SoundObj_PlaySE(*(void **)(self + 0x18), 9);
    if (*(int *)(self + 0xC0) > 0) {
        fn_80091438(*(void **)(*(int *)(self + 0x10) + 0x304), 0x1A);
        fn_80058534(*(void **)(self + 0x14), 0x1A);
        *(int *)(self + 0xA8) = -1;
        *(int *)(self + 0xC0) = 0;
    }
    return 1;
}
#pragma exceptions reset
