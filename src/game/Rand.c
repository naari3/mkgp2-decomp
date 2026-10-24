extern unsigned short rand(void);
extern void srand(int seed);
extern void DebugPrintf(const char *fmt, ...);

extern unsigned char g_randSeedDebugEnable;
extern char lbl_80321178[];

#pragma exceptions on
unsigned short Rand15(void) {
    return rand();
}

void Rand_SetSeedDebug(int seed) {
    if (g_randSeedDebugEnable != 0) {
        srand(seed);
        DebugPrintf(lbl_80321178, seed);
    }
}
#pragma exceptions reset
