/* Observed 0xBC-byte slot view; unknown fields remain padding. */
#include "game/types/RaceContextSlot.h"

extern "C" {
void Unknown_DeleteIfFlag_800a5188(void*, short);
void fn_800A51C4(void*);
void __construct_array(void*, void (*)(void*), void (*)(void*, short), unsigned long, unsigned long);
}

/* Whole-array reset like RankingTable_Init; the by-reference clear keeps the
 * -1/0 constants inside the 8x-unrolled loop. */
static inline void ClearSlot(RaceContextSlot& s)
{
    s.type = -1; s.id = -1; s.word08 = 0; s.word0C = 0; s.driver = 0;
    s.index84 = 0; s.word88 = 0; s.word8C = 0; s.index90 = -1; s.index94 = -1;
}
static inline void InitializeSlots(RaceContextSlot* self)
{
    for (int index = 0; index < 128; index++) {
        ClearSlot(self[index]);
    }
}

extern "C" RaceContextSlot* RaceContextArray_Init(RaceContextSlot* self)
{
    __construct_array(self, fn_800A51C4, Unknown_DeleteIfFlag_800a5188, sizeof(RaceContextSlot), 128);
    InitializeSlots(self);
    return self;
}
