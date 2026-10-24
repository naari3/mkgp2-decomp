extern unsigned char g_randSeedDebugEnable;
extern char lbl_80321194[];
extern void DebugPrintf(const char *, ...);

unsigned char RandSeedDebug_SetEnable(unsigned char enable) {
    unsigned char prev = g_randSeedDebugEnable;

    if (enable != prev) {
        g_randSeedDebugEnable = enable;
        DebugPrintf(lbl_80321194, enable);
    }
    return prev;
}
