/*
 * Ring buffer slot accessors (PCB inter-host communication).
 *
 * Layout per ring entry (0xdc bytes):
 *   +0x00 .. +0x9F : 4 KartSlot entries (0x28 bytes each)
 *   +0xA0 .. +0xFF : 4 RankSlot entries (0x18 bytes each)
 *
 * Host writes into the local ring (read_idx == 0 view).
 * Clients index into a 16-entry ring at g_ringBufferBase + g_ringReadIdx * 0xdc.
 */

extern unsigned char g_isCommHost;
extern int g_ringReadIdx;
extern unsigned char g_ringBufferBase[0x3700];

void *RingBuffer_GetRankSlot(int kartIdx) {
    if (kartIdx < 0 || kartIdx >= 4) {
        return (void *)0;
    }
    if (g_isCommHost == 1) {
        return g_ringBufferBase + kartIdx * 0x18 + 0xa0;
    }
    return g_ringBufferBase + g_ringReadIdx * 0xdc + kartIdx * 0x18 + 0xa0;
}

void *RingBuffer_GetEntryHead(void) {
    if (g_isCommHost == 1) {
        return &g_ringBufferBase[0];
    }
    return &g_ringBufferBase[g_ringReadIdx * 0xdc];
}

void *RingBuffer_GetKartSlot(int kartIdx) {
    if (kartIdx < 0 || kartIdx >= 4) {
        return (void *)0;
    }
    if (g_isCommHost == 1) {
        return &g_ringBufferBase[kartIdx * 0x28];
    }
    return &g_ringBufferBase[g_ringReadIdx * 0xdc] + kartIdx * 0x28;
}
