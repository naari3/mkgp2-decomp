/* Clear all 64 ring-buffer entries and rewind the indices. */
typedef struct CommEntry {
    unsigned char data[0xdc];
} CommEntry;

extern CommEntry g_ringBufferBase[0x40];
extern int g_ringReadIdx;
extern int lbl_806D11A0;
extern void *memset(void *dst, int c, unsigned long n);

void CommBroadcast_ClearTable(void)
{
    int i;

    lbl_806D11A0 = 1;
    g_ringReadIdx = 0;
    for (i = 0; i < 0x40; i++) {
        memset(&g_ringBufferBase[i], 0, sizeof(CommEntry));
    }
}
