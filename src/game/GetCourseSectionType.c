/*
 * GetCourseSectionType @ 0x8023D6D4 (size 0x3C).
 *
 * Bounds-checked LUT accessor for course section type. Returns the signed-byte
 * entry at `(&DAT_8041cbad)[idx * 0x14]` via `fn_800D76A4(idx)`. Out-of-range
 * indices return 0.
 *
 * Singleton dtk reversed-extab group `auto_GetCourseSectionType_text` — the
 * function has an extab/extabindex entry (Large-Frame flag). #pragma
 * exceptions on/reset wraps the function so CW auto-emits the extab/extabindex
 * entry (same pattern as AI_GetYaw.c, Vtable_CallSlot2.cpp).
 */

extern signed char fn_800D76A4(int idx);

#pragma exceptions on
int GetCourseSectionType(int idx) {
    if (idx < 0 || 0x115 < idx) {
        return 0;
    }
    return fn_800D76A4(idx);
}
#pragma exceptions reset
