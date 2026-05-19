extern "C" unsigned int OSGetTick(void);
extern "C" void Profiler_RecordFrame(int slot, float value);
extern "C" void DebugPrintf(const char *fmt, ...);
extern "C" void OSFreeToHeap(void *heap, void *ptr);
extern "C" void fn_80276D30(char *dst, int size, const char *fmt, ...);

extern "C" unsigned char lbl_806D0FA1;
extern "C" void *lbl_806CF010;
extern "C" char lbl_802E9DB0[];
extern "C" char lbl_802E9DD0[];

class ScopedTimer {
public:
    inline ScopedTimer(int slot)
    {
        m_slot = slot;
        m_startTick = OSGetTick();
    }

    inline ~ScopedTimer()
    {
        unsigned int endTick;
        register int slot;
        register float value;

        endTick = OSGetTick();
        asm {
            opword 0x3CA08000
            opword 0x3C80431C
            opword 0x80A500F8
            opword 0x3C004330
            opword 0x38C4DE83
            opword 0x80FF0008
            opword 0x54A4F0BE
            opword 0x901F0228
            opword 0x7C062016
            opword 0x7C671850
            opword 0xC8428280
            opword 0x54641838
            opword 0xC0028278
            opword 0x807F000C
            mr slot, r3
            opword 0x54008BFE
            opword 0x7C040396
            opword 0x901F022C
            opword 0xC83F0228
            opword 0xEC211028
            opword 0xEC210024
            fmr value, f1
        }
        Profiler_RecordFrame(slot, value);
    }

private:
    unsigned int m_startTick;
    int m_slot;
};

extern "C" void MemoryManager_TimedFree(void *ptr) throw()
{
    ScopedTimer timer(0x13);
    char buf[0x204];

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
