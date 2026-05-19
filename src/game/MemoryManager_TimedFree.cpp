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

        /*
         * This is intentionally a codegen shim, not evidence that the original
         * source used inline asm. The likely original destructor was ordinary
         * C++:
         *
         *   elapsedUnit = ((OSGetTick() - m_startTick) << 3) /
         *       (((*(volatile unsigned int *)0x800000F8) >> 2) / 125000);
         *   Profiler_RecordFrame(m_slot, (float)elapsedUnit / 60.0f);
         *
         * Pure C++ gets the surrounding C++ cleanup shape right, but CW1.3.2
         * chooses different GPRs for the reciprocal/divide block and uses r8
         * for the 0x4330 int-to-double cookie high word. The target uses r0.
         * Full inline asm including the Profiler_RecordFrame call fixes the
         * block but makes the caller preserve r29 and grow to 0x170. Keeping
         * the call in C and pinning only the arithmetic preserves the target
         * 0x168 function layout.
         *
         * See docs/notes/cpp-scoped-timer-pattern.md ("Post-match gap").
         */
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

    /*
     * Runtime writes still use size 0x200. The extra four bytes are stack
     * pressure for CW's frame allocator: the raw dtor opwords write the
     * conversion cookie at 0x228/0x22C(r31), which the compiler cannot see.
     * With a visible 0x200 buffer, CW shrinks the frame to 0x230 and saved
     * registers overlap that raw cookie area. A 0x204 visible buffer restores
     * the target 0x240 frame without changing emitted instructions for the
     * debug buffer address or length.
     */
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
