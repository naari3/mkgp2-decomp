/*
 * PathFollower_EnsureGlobalAlloc @ 0x801DC5F8.
 *
 * Lazy-init singleton getter: returns the global singleton pointer at
 * lbl_806D18A0, allocating it via Alloc(1) on first call.
 *
 * The TU sits in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entry (matches the
 * AI_GetYaw / CourseBgm_Free template for singletons in this lib).
 */

extern void *Alloc(int size);
extern void *lbl_806D18A0;

#pragma exceptions on
void *PathFollower_EnsureGlobalAlloc(void) {
    if (lbl_806D18A0 == 0) {
        lbl_806D18A0 = Alloc(1);
    }
    return lbl_806D18A0;
}
#pragma exceptions reset
