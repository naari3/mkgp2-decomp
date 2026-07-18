extern unsigned char g_pcbSyncTable[0x1C];

void *PcbSyncTable_Ptr(void)
{
    return g_pcbSyncTable;
}
