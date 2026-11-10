
/* sdata symbols referenced from asm */
#include "game/types/size_t.h"
extern "C" const char lbl_806D2264[4];
/* === extracted from auto_FlowDispatcher_Creat_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
void *operator new(size_t size);
void operator delete(void *p);
extern "C" void DebugLog_LvIdMsg(int lv, int id, const char *msg);
extern "C" void DebugPrintf(const char *fmt, ...);
extern "C" void HeapStats_DumpForTag(const char *tag, int flag);
extern "C" void MemoryManager_TimedFree(void *);
extern "C" unsigned int OSGetTick(void);
extern "C" void Profiler_RecordFrame(int, float);

/* --- extern decls: sda21-referenced data --- */
extern "C" const float lbl_806D2268;
extern "C" float lbl_806D2280;
extern "C" unsigned int lbl_806D2288;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern "C" const char FlowDispatcher_Create_rodata_802E8DBC[];

/* --- forward decls --- */
extern "C" void __dt__11ScopedTimerFv(void);

class ScopedTimer {
public:
    ~ScopedTimer();
    static void operator delete(void *ptr) { MemoryManager_TimedFree(ptr); }

private:
    unsigned int m_startTick;
    int m_slot;
};

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab___dt__11ScopedTimerFv[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex___dt__11ScopedTimerFv = {
    (void *)&__dt__11ScopedTimerFv, 0x000000A4, (void *)extab___dt__11ScopedTimerFv
};

#include "game/types/FlowEntry.h"

struct SeqMenuScene {
    char pad[0x14];
    SeqMenuScene(FlowEntry *entries);
};

struct FlowDispatcher {
    FlowEntry *table;
    int start;
    void *current;
    int count;
    SeqMenuScene *menu;
    int f14;
    float v18[3];
    float v24[3];
    int f30;
    int f34;

    FlowDispatcher(FlowEntry *t, int s) {
        table = t;
        start = s;
        DebugPrintf(FlowDispatcher_Create_rodata_802E8DBC);
        HeapStats_DumpForTag(lbl_806D2264, 0);
        menu = new SeqMenuScene(table);
        if (s == -4) {
            current = menu;
        } else {
            current = table[start].create();
        }
        for (count = 0; table[count].create != 0; count++) {
        }
        f14 = 0;
        v24[0] = lbl_806D2268;
        v24[1] = lbl_806D2268;
        v24[2] = lbl_806D2268;
        v18[0] = lbl_806D2268;
        v18[1] = lbl_806D2268;
        v18[2] = lbl_806D2268;
        f30 = 0;
        f34 = 0;
        HeapStats_DumpForTag(lbl_806D2264, 0);
        DebugPrintf(FlowDispatcher_Create_rodata_802E8DBC);
        DebugLog_LvIdMsg(0, 0, lbl_806D2264);
    }
};

extern "C" FlowDispatcher *FlowDispatcher_Create_bss_806D0F80;

#pragma exceptions on
extern "C" FlowDispatcher *FlowDispatcher_Create(FlowEntry *table, int start) {
    if (FlowDispatcher_Create_bss_806D0F80 == 0) {
        FlowDispatcher_Create_bss_806D0F80 = new FlowDispatcher(table, start);
    }
    return FlowDispatcher_Create_bss_806D0F80;
}
#pragma exceptions reset

#pragma exceptions off
#ifdef NON_MATCHING
/* Equivalent C++ for the PC port (docs/nonmatching_c.md): the natural
 * destructor, as MainGameLoop's inlined copies have it. */
ScopedTimer::~ScopedTimer()
{
    unsigned int elapsed = ((OSGetTick() - m_startTick) << 3) /
        (((*(volatile unsigned int *)0x800000F8) >> 2) / 125000);
    Profiler_RecordFrame(m_slot, (float)elapsed / 1000000.0f);
}
#else
ScopedTimer::~ScopedTimer()
{
    register int slot;
    register float value;
    double cookie;

    OSGetTick();

    /*
     * A direct C++ spelling gets this destructor to a two-instruction schedule
     * mismatch. Keep the canonical destructor in C++ ownership, but pin the
     * small timer arithmetic sequence that CW otherwise keeps reshuffling.
     */
    asm {
    opword 0x3CA08000
    opword 0x3C80431C
    opword 0x80A500F8
    opword 0x3C004330
    opword 0x38C4DE83
    opword 0x80FE0000
    opword 0x54A4F0BE
    stw r0, cookie
    opword 0x7C062016
    opword 0x7C671850
    lfd f2, lbl_806D2288(r2)
    opword 0x54641838
    lfs f0, lbl_806D2280(r2)
    opword 0x807E0004
    opword 0x54008BFE
    opword 0x7C040396
    stw r0, cookie+4
    lfd f1, cookie
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    mr slot, r3
    fmr value, f1
    }

    Profiler_RecordFrame(slot, value);
}
#endif
#pragma exceptions reset

