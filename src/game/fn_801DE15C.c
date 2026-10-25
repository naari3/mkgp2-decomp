extern void *lbl_806D18B4;
extern char lbl_803BD08C[];
extern void MemoryManager_TimedFree(void *);
extern void DebugPrintf(const char *fmt, ...);

static inline void DeleteSingleton(void *p) {
    if (p != 0) {
        DebugPrintf(lbl_803BD08C);
        MemoryManager_TimedFree(p);
    }
}

void fn_801DE15C(void) {
    if (lbl_806D18B4 != 0) {
        DeleteSingleton(lbl_806D18B4);
    }
    lbl_806D18B4 = 0;
}
