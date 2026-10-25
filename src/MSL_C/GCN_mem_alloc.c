/**
 * GCN_mem_alloc.c
 * Description:
 */

typedef int OSHeapHandle;

/* __OSCurrHeap */
extern volatile OSHeapHandle lbl_806CF010;
#define __OSCurrHeap lbl_806CF010

/* OSReport */
void OSReport(const char* msg, ...);
void* OSGetArenaLo(void);
void* OSGetArenaHi(void);
void OSSetArenaLo(void* newLo);
void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps);
OSHeapHandle OSCreateHeap(void* start, void* end);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
void* OSAllocFromHeap(OSHeapHandle heap, unsigned long size);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);

#define OSRoundUp32B(x) (((unsigned long)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((unsigned long)(x)) & ~(32 - 1))

inline static void InitDefaultHeap(void) {
    void* arenaLo;
    void* arenaHi;

    OSReport("GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n");
    OSReport("Metrowerks CW runtime library initializing default heap\n");

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();

    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);

    arenaLo = (void*)OSRoundUp32B(arenaLo);
    arenaHi = (void*)OSRoundDown32B(arenaHi);

    OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
    OSSetArenaLo(arenaLo = arenaHi);
}

void* __sys_alloc(unsigned long size) {
    if (__OSCurrHeap == -1) {
        InitDefaultHeap();
    }

    return OSAllocFromHeap(__OSCurrHeap, size);
}

void __sys_free(void* p) {
    if (__OSCurrHeap == -1) {
        InitDefaultHeap();
    }

    OSFreeToHeap(__OSCurrHeap, p);
}
