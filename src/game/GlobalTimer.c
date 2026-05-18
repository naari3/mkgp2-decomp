typedef unsigned int u32;
typedef signed int s32;

extern s32 g_globalTimer;

u32 IsGlobalTimerExpired(void) {
    return ((u32)(-g_globalTimer) & ~(u32)g_globalTimer) >> 31;
}

void Timer_Decrement(void) {
    if (g_globalTimer <= 0) {
        return;
    }
    g_globalTimer = g_globalTimer - 1;
}
