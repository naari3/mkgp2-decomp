#include "game/FlowDispatcher_private.h"

extern "C" void Flow_TransitionTo(FlowDispatcher *self, int index)
{
    const char *text = lbl_802E89A0;
    if (self->currentIndex != -4) {
        if (self->current) {
            delete self->current;
        }
    }
    SpriteHandlePool_GC();
    fn_80121210();
    SceneFlow_DefaultGetZero(-2);
    SceneFlow_InitCleanupList();
    ++self->cleanupTag;
    SceneFlow_SetCleanupTag(self->cleanupTag);
    if (index == -4) {
        DebugPrintf(text + 0x42c);
        self->currentIndex = -4;
        self->current = self->menu;
    } else {
        if (index == -1) {
            int next = self->currentIndex + 1;
            int count = self->count;
            FlowEntry *entries = self->entries;
            for (;;) {
                next %= count;
                if (entries[next].create) {
                    self->currentIndex = next;
                    break;
                }
                ++next;
            }
        } else {
            self->currentIndex = index;
        }
        DebugPrintf(text + 0x440);
        int size = HeapStats_DumpForTag(lbl_806D2264, 0);
        DebugPrintf(self->entries[self->currentIndex].name);
        self->current = self->entries[self->currentIndex].create();
        DebugPrintf(text + 0x45c);
        HeapStats_DumpForTag(lbl_806D2264, size);
    }
}
