/*
 * MemoryManager_Alloc @ 0x8003ADFC - 0x8003AFB8 (2 fns, 1 TU).
 *
 *   0x8003ADFC MemoryManager_AllocTagged (size 0xEC)
 *   0x8003AEE8 MemoryManager_Free        (size 0xD0)
 *
 * Same family as MemoryManager_TimedFree.cpp / Alloc (0x8003B1FC). Both
 * functions time themselves with a stack ScopedTimer (slot 0x13) and bail
 * to an infinite loop on "memory manager no init" / "memory empty".
 *
 * Unlike MemoryManager_TimedFree, the ScopedTimer destructor is NOT inlined
 * here: both functions call the canonical out-of-line __dt__11ScopedTimerFv
 * (0x8002CCD8, owned by FlowDispatcher_ScopedTimer.c), so the class only
 * declares the destructor in this TU.
 *
 * Exception metadata (auto-emitted by CW with -Cpp_exceptions on):
 *  - MemoryManager_AllocTagged: DESTROYLOCAL only, no FP (extab 0x18080000)
 *  - MemoryManager_Free: throw() spec -> SPECIFICATION + ACTIVECATCHBLOCK,
 *    frame pointer in r31 (extab 0x10180000)
 *
 * This TU also owns the .rodata message pool at 0x802E9D90 (see the
 * definitions below). MemoryManager_AllocTagged addresses all four of its
 * strings off a single section base cached in r31 (+0x00 fmt, +0x20 stop
 * request, +0x30 memory empty, +0x58 operator new).
 */

extern "C" unsigned int OSGetTick(void);
extern "C" void DebugPrintf(const char *fmt, ...);
extern "C" void *OSAllocFromHeap(void *heap, unsigned int size);
extern "C" void OSFreeToHeap(void *heap, void *ptr);
extern "C" void fn_80276D30(char *dst, int size, const char *fmt, ...);

extern "C" unsigned char lbl_806D0FA1;
extern "C" void *lbl_806CF010;
/*
 * Message string pool at 0x802E9D90, owned by this TU (the original
 * MemoryManager TU defined these literals; CW addresses them
 * section-relatively, which is why MemoryManager_AllocTagged forms a single
 * ...rodata.0 base in r31 and uses raw addi offsets 0x0/0x20/0x30/0x58,
 * while MemoryManager_Free (one use per string) rematerializes per-symbol
 * lis/addi pairs. Defining them as named const arrays reproduces both
 * addressing shapes and exports the symbols other TUs reference
 * (MemoryManager_TimedFree.cpp externs lbl_802E9DB0/lbl_802E9DD0).
 */
extern "C" const char lbl_802E9D90[0x20] = "memory manager no init\nmes:%s\n";
extern "C" const char lbl_802E9DB0[0x10] = "stop request\n";
extern "C" const char lbl_802E9DC0[0x10] = "memory empty\n";
extern "C" const char lbl_802E9DD0[0x18] = "memory manager no init\n";
extern "C" const char lbl_802E9DE8[0x10] = "operator new\n";

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

extern "C" void *MemoryManager_AllocTagged(unsigned int size, char *tag)
{
    ScopedTimer timer(0x13);
    char buf[0x200];
    void *ptr;

    if (lbl_806D0FA1 == 0) {
        fn_80276D30(buf, 0x200, lbl_802E9D90, tag);
        DebugPrintf(buf);
        DebugPrintf(lbl_802E9DB0);
        for (;;) {}
    }

    if (size == 0) {
        size += 1;
    }

    ptr = OSAllocFromHeap(lbl_806CF010, size);
    if (ptr == 0) {
        DebugPrintf(lbl_802E9DC0);
        DebugPrintf(lbl_802E9DE8);
        DebugPrintf(lbl_802E9DB0);
        for (;;) {}
    }

    return ptr;
}

extern "C" void MemoryManager_Free(void *ptr) throw()
{
    ScopedTimer timer(0x13);
    char buf[0x200];

    if (lbl_806D0FA1 == 0) {
        fn_80276D30(buf, 0x200, lbl_802E9DD0);
        DebugPrintf(buf);
        DebugPrintf(lbl_802E9DB0);
        for (;;) {}
    }

    if (ptr == 0) {
        return;
    }

    OSFreeToHeap(lbl_806CF010, ptr);
}
