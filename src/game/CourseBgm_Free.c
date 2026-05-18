extern void MemoryManager_Free(void *p);

extern void *g_courseBgm;
extern int   g_courseBgmSize;

#pragma exceptions on
void CourseBgm_Free(void) {
    MemoryManager_Free(g_courseBgm);
    g_courseBgm = 0;
    g_courseBgmSize = 0;
}
#pragma exceptions reset
