extern unsigned short fn_80278C54(void);
extern void fn_80278C4C(int seed);
extern void DebugPrintf(const char *fmt, ...);

extern unsigned char g_randSeedDebugEnable;
extern char lbl_80321178[];

#pragma exceptions on
unsigned short Rand15(void) {
    return fn_80278C54();
}

void Rand_SetSeedDebug(int seed) {
    if (g_randSeedDebugEnable != 0) {
        fn_80278C4C(seed);
        DebugPrintf(lbl_80321178, seed);
    }
}
#pragma exceptions reset
