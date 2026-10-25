/* PCB sync-table peer scan, 0x80085648..0x800856CC. */
extern unsigned char g_pcbSyncTable[0x1C];
extern int g_myPcbId;

int PcbSync_AnyPeerAtState5(void)
{
    int i;
    int st;

    for (i = 0; i < 4; i++) {
        if (i != g_myPcbId - 1) {
            st = g_pcbSyncTable[4 + i];
            if (st == 5) {
                return st;
            }
        }
    }
    return 0;
}
