extern void *g_clEnemyParam;
extern char lbl_803BD0C4[];
extern void MemoryManager_TimedFree(void *);
extern void DebugPrintf(const char *fmt, ...);

static inline void DeleteSingleton(void *p) {
    if (p != 0) {
        DebugPrintf(lbl_803BD0C4);
        MemoryManager_TimedFree(p);
    }
}

void fn_801DE6E8(void) {
    if (g_clEnemyParam != 0) {
        DeleteSingleton(g_clEnemyParam);
    }
    g_clEnemyParam = 0;
}
