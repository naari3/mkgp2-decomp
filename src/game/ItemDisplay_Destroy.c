/*
 * ItemDisplay_Destroy @ 0x8020AE50 (size 0x58).
 *
 * Tear down the ItemDisplay singleton: destroy its Sprite (if any),
 * free the singleton via the MemoryManager dtor, and clear the global
 * pointer. Driven from ItemDisplay shutdown paths.
 *
 * The target asm exhibits the C++ deleting-destructor offset-0 duplicate
 * `beq` idiom -- two consecutive `beq` branches share the same cr0 result
 * from `cmplwi r31, 0x0`. The outer `if` skips the whole body, the inner
 * `if` skips just the Sprite_Destroy + dtor call, leaving the trailing
 * `g_pItemDisplay = 0` to run.
 *
 * Codegen note (this idiom diverges slightly from dtor_800A9D2C's
 * `if (this) if (this)` pattern because here `this` is loaded from sdata
 * rather than received as a parameter): the local `self = g_pItemDisplay`
 * declaration MUST sit inside the outer `if (g_pItemDisplay)` block.
 * That ordering convinces CW 1.3.2 to load the global directly into r31
 * (callee-saved) via `lwz r31, g_pItemDisplay@sda21` -- no intermediate
 * `lwz r3 + mr r31, r3` pair. Declaring `self` before the outer if
 * costs an extra `mr r31, r3` and shifts the function by 4 bytes.
 *
 * extab/extabindex entries are auto-emitted by CW under
 * #pragma exceptions on (same approach as ItemDisplay_Stop).
 */

#include "game/ItemDisplay.h"

extern ItemDisplay *g_pItemDisplay;
extern void Sprite_Destroy(Sprite *sprite, int flag);
extern void dtor_8003AFB8(void *this);

#pragma exceptions on
void ItemDisplay_Destroy(void) {
    if (g_pItemDisplay) {
        ItemDisplay *self = g_pItemDisplay;
        if (self) {
            if (self->sprite) {
                Sprite_Destroy(self->sprite, 1);
            }
            dtor_8003AFB8(self);
        }
        g_pItemDisplay = 0;
    }
}
#pragma exceptions reset
