/*
 * ItemDisplay_Stop @ 0x8020AA98 (size 0x3C).
 *
 * Soft-reset of the ItemDisplay singleton: clears `state` and `pendingItemId`,
 * and if a Sprite is bound, tears it down via fn_801A0500 (Sprite helper).
 *
 * extab/extabindex entries are present in the target (Large Frame: Yes flag),
 * emitted via #pragma exceptions on/reset so CW auto-generates them -- same
 * pattern as game/JObj_Visibility.c (TU sits in `game` lib, CW 1.3.2).
 *
 * Experiment: this TU includes the ItemDisplay struct definition from
 * include/game/ItemDisplay.h to check whether a pre-defined Ghidra struct
 * matches the target asm field offsets on first try.
 */

#include "game/ItemDisplay.h"

extern int fn_801A0500(Sprite *sprite);

#pragma exceptions on
void ItemDisplay_Stop(ItemDisplay *self) {
    self->state = 0;
    self->pendingItemId = -1;
    if (self->sprite != 0) {
        fn_801A0500(self->sprite);
    }
}
#pragma exceptions reset
