/*
 * DMAChannelManager_Init @ 0x800662B4 size 0x9C - real C++ retrofit
 * (2026-07-19, docs/notes/cpp-ctor-retrofit-mangled-bridge.md recipe).
 *
 * Init routine for the 32-entry transparent-draw slot pool at lbl_805987E0
 * (stride 0x14). The per-slot allocation is a genuine new-expression:
 * `slot->entry = new TDrawEntry;` with operator new = Alloc(0x84) and the
 * ctor = TransparentDraw_ResetEntry. The DELETEPOINTER(r27 ->
 * operator delete) extab action over the ctor call site is auto-emitted by
 * -Cpp_exceptions on, replacing the previous asm_fn + manual emit.
 *
 * Mangled references bridged via tools/extab_user_renames.json:
 *   __ct__10TDrawEntryFv -> TransparentDraw_ResetEntry
 *   __nw__FUl            -> Alloc                   (shared mapping)
 *   __dl__FPv            -> MemoryManager_TimedFree (shared mapping)
 */

struct TDrawEntry {
    char _opaque[0x84];
    TDrawEntry();
};

#include "game/types/TDrawSlot.h"
 /* stride 0x14 */

extern "C" {
extern TDrawSlot lbl_805987E0[0x20];
extern unsigned int DMAChannelManager_Init_data_806CEF20;
extern unsigned char lbl_806D10F0;
extern unsigned int lbl_806D10F4;
extern unsigned int lbl_806D10F8;
}

#pragma exceptions on

extern "C" void DMAChannelManager_Init(void) {
    int i;

    if (lbl_806D10F0 == 1) {
        return;
    }
    for (i = 0; i < 0x20; i++) {
        if (lbl_805987E0[i].owner != -1) {
            lbl_805987E0[i].owner = -1;
            lbl_805987E0[i].state = 5;
        }
        lbl_805987E0[i].entry = new TDrawEntry;
    }
    DMAChannelManager_Init_data_806CEF20 = 8;
    lbl_806D10F4 = 0;
    lbl_806D10F8 = 0;
    lbl_806D10F0 = 1;
}

#pragma exceptions reset
