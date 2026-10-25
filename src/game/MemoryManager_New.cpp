/*
 * The two timed heap allocators after MemoryManager_TimedFree,
 * 0x8003B120..0x8003B2D8: FUN_8003b120 ("operator new") and Alloc
 * ("operator new[]"). Same shape as MemoryManager_AllocTagged without the
 * tag; both call the out-of-line ScopedTimer destructor.
 */

extern "C" unsigned int OSGetTick(void);
extern "C" void DebugPrintf(const char *fmt, ...);
extern "C" void *OSAllocFromHeap(void *heap, unsigned int size);
extern "C" void snprintf(char *dst, int size, const char *fmt, ...);

extern "C" unsigned char lbl_806D0FA1;
extern "C" void *lbl_806CF010;
extern "C" const char lbl_802E9D90[]; /* MemoryManager message pool */

#define MM_STR_STOP_REQUEST 0x20
#define MM_STR_MEMORY_EMPTY 0x30
#define MM_STR_NO_INIT 0x40
#define MM_STR_OPERATOR_NEW 0x58
#define MM_STR_OPERATOR_NEW_ARRAY 0x68

class ScopedTimer {
public:
    inline ScopedTimer(int slot)
    {
        m_slot = slot;
        m_startTick = OSGetTick();
    }

    /* canonical definition lives at 0x8002CCD8 (FlowDispatcher_ScopedTimer.c) */
    ~ScopedTimer();

private:
    unsigned int m_startTick;
    int m_slot;
};

extern "C" void *FUN_8003b120(unsigned int size)
{
    const char *strings = lbl_802E9D90;
    ScopedTimer timer(0x13);
    char buf[0x200];
    void *ptr;

    if (lbl_806D0FA1 == 0) {
        snprintf(buf, 0x200, strings + MM_STR_NO_INIT);
        DebugPrintf(buf);
        DebugPrintf(strings + MM_STR_STOP_REQUEST);
        for (;;) {}
    }

    if (size == 0) {
        size += 1;
    }

    ptr = OSAllocFromHeap(lbl_806CF010, size);
    if (ptr == 0) {
        DebugPrintf(strings + MM_STR_MEMORY_EMPTY);
        DebugPrintf(strings + MM_STR_OPERATOR_NEW);
        DebugPrintf(strings + MM_STR_STOP_REQUEST);
        for (;;) {}
    }

    return ptr;
}

extern "C" void *Alloc(unsigned int size)
{
    const char *strings = lbl_802E9D90;
    ScopedTimer timer(0x13);
    char buf[0x200];
    void *ptr;

    if (lbl_806D0FA1 == 0) {
        snprintf(buf, 0x200, strings + MM_STR_NO_INIT);
        DebugPrintf(buf);
        DebugPrintf(strings + MM_STR_STOP_REQUEST);
        for (;;) {}
    }

    if (size == 0) {
        size += 1;
    }

    ptr = OSAllocFromHeap(lbl_806CF010, size);
    if (ptr == 0) {
        DebugPrintf(strings + MM_STR_MEMORY_EMPTY);
        DebugPrintf(strings + MM_STR_OPERATOR_NEW_ARRAY);
        DebugPrintf(strings + MM_STR_STOP_REQUEST);
        for (;;) {}
    }

    return ptr;
}
