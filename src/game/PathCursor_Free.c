extern void MemoryManager_TimedFree(void *p);

#pragma exceptions on
void *PathCursor_Free(void *p, short should_delete) {
    if ((p != 0) && (0 < should_delete)) {
        MemoryManager_TimedFree(p);
    }
    return p;
}
#pragma exceptions reset
