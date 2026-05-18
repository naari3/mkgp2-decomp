/*
 * ItemDisplay_GetOrCreate @ 0x8020AEA8 (size 0x60).
 *
 * Lazy-init the ItemDisplay singleton. If g_pItemDisplay is already set,
 * return it as-is. Otherwise Alloc(0x14) and initialize the fields to
 * their default values:
 *   sprite        = 0
 *   state         = 0
 *   styleId       = 4
 *   currentItemId = 0
 *   pendingItemId = -1
 *
 * Field offsets are verified by the store sequence in the target asm
 * (stw 0x0, 0x4, 0x8, 0xC, 0x10).
 *
 * Note: the asm stores `r3` (the Alloc result, may be 0) into
 * g_pItemDisplay unconditionally after the init block. Hence the
 * local `self` is assigned to g_pItemDisplay outside the inner
 * `if (self)` block.
 *
 * extab/extabindex entries are auto-emitted by CW under
 * #pragma exceptions on (same approach as ItemDisplay_Stop).
 */

#include "game/ItemDisplay.h"

extern ItemDisplay *g_pItemDisplay;
extern void *Alloc(int size);

#pragma exceptions on
ItemDisplay *ItemDisplay_GetOrCreate(void) {
    ItemDisplay *self;
    if (g_pItemDisplay == 0) {
        self = (ItemDisplay *)Alloc(0x14);
        if (self != 0) {
            self->sprite = 0;
            self->state = 0;
            self->styleId = 4;
            self->currentItemId = 0;
            self->pendingItemId = -1;
        }
        g_pItemDisplay = self;
    }
    return g_pItemDisplay;
}
#pragma exceptions reset
