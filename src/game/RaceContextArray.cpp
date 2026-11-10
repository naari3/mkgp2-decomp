/* Observed 0xBC-byte slot view; unknown fields remain padding. */
#include "game/types/RaceContextSlot.h"

extern "C" {
void Unknown_DeleteIfFlag_800a5188(void*, short);
void fn_800A51C4(void*);
void __destroy_arr(void*, void (*)(void*, short), unsigned long, unsigned long);
void __construct_array(void*, void (*)(void*), void (*)(void*, short), unsigned long, unsigned long);
void MemoryManager_TimedFree(void*);

RaceContextSlot* RaceContextArray_Dtor(RaceContextSlot* self, short freeFlag)
{
    if (self) {
        __destroy_arr(self, Unknown_DeleteIfFlag_800a5188, sizeof(RaceContextSlot), 128);
        if (freeFlag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
}

