extern unsigned char lbl_805A6154[0x28F0];
extern void *memset(void *dest, int value, unsigned long size);

static inline void ResetScratchSlot(unsigned char *slot, int index)
{
    int row;
    unsigned char *cursor;
    if (index < 0 || index >= 4) return;
    if (((unsigned int)slot[0xA34] >> 7) == 1) {
        slot[0xA38] = 0;
        slot[0xA39] = 2;
    } else {
        slot[0xA38] = 0;
        slot[0xA39] = 1;
    }
    for (row = 0, cursor = slot; row < 64; ++row, cursor += 0x28) {
        memset(cursor + 0x2C, 0, 0x28);
    }
}

void PcbSlot_ResetScratchAreas(void)
{
    unsigned char *slot = lbl_805A6154;
    int index;
    for (index = 0; index < 4; ++index, slot += 0xA3C) {
        ResetScratchSlot(slot, index);
    }
}
