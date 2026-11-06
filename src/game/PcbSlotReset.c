#include "game/PcbSlotReset_private.h"

extern PcbScratchSlot lbl_805A6154[4];
extern void *memset(void *dest, int value, unsigned long size);

static inline void ResetScratchSlot(PcbScratchSlot *slot, int index)
{
    unsigned char *cursor;
    int row;
    if (index < 0 || index >= 4) return;
    if (slot->flags.local == 1) {
        slot->readIndex = 0;
        slot->writeIndex = 2;
    } else {
        slot->readIndex = 0;
        slot->writeIndex = 1;
    }
    for (row = 0, cursor = (unsigned char *)slot; row < 64; ++row, cursor += 0x28) {
        memset(cursor + 0x2C, 0, 0x28);
    }
}

void PcbSlot_ResetScratchAreas(void)
{
    int index;
    for (index = 0; index < 4; ++index) {
        ResetScratchSlot(&lbl_805A6154[index], index);
    }
}
