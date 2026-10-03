/* Observed PCB storage views; definitions remain in the existing global units. */
extern unsigned char lbl_805A6154[0x28F0];
extern unsigned char g_pcbSyncTable[0x1C];
extern int g_myPcbId;
extern float lbl_806D3160;

void *PcbSlot_GetByIndex(int index)
{
    if (index < 0 || index >= 4) return 0;
    return lbl_805A6154 + index * 0xA3C;
}

unsigned int PcbSlot_GetCharIdByte(int index)
{
    if (index < 0 || index >= 4) return 0;
    return (*(unsigned int *)(lbl_805A6154 + index * 0xA3C) >> 15) & 0xFF;
}

typedef struct {
    unsigned char disabled : 1;
    unsigned char unused6 : 1;
    unsigned char ready : 1;
    unsigned char flag4 : 1;
    unsigned char unusedLow : 4;
} ReadyFlags;

static inline unsigned int FinalReadyFlag(const ReadyFlags *ready)
{
    return ready->flag4;
}

static inline int ReadyByte(const ReadyFlags *ready)
{
    if (ready->disabled == 1) return 0;
    if (ready->ready == 0) return 0;
    return FinalReadyFlag(ready) != 0;
}

int PcbSlot_IsReadyByIndex(int index)
{
    if (index < 0 || index >= 4) return 0;
    return ReadyByte((ReadyFlags *)(lbl_805A6154 + index * 0xA3C + 0xA34));
}

float PcbSyncTable_LookupValueByState(int state)
{
    int i;
    for (i = 0; i < 4; ++i) {
        if (g_pcbSyncTable[4 + i] == state)
            return ((float *)(g_pcbSyncTable + 8))[i];
    }
    return lbl_806D3160;
}

float PcbSyncTable_GetMyValue(void)
{
    return ((float *)(g_pcbSyncTable + 4))[g_myPcbId];
}

int PcbSyncTable_MyFlagIsSet(void)
{
    return g_pcbSyncTable[3 + g_myPcbId] != 0;
}
