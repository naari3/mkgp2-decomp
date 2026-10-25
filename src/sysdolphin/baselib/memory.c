// mkgp2's HSD memory.c differs from melee's: allocation goes through a
// table of callbacks installed by the game instead of OSAllocFromHeap.
#include <Runtime/platform.h>

#include "debug.h"

typedef struct __mem_cb {
    void* (*alloc)(u32 size, u32 align, u32 flags);
    void (*free)(void* ptr);
    void* cb2;
    void* cb3;
    void (*cb4)(void* arg);
} __mem_cb;

static __mem_cb mem_cb;

void HSD_MemSetCallbacks(__mem_cb* cb, u32 size)
{
    HSD_ASSERT(20, size == sizeof(__mem_cb));
    mem_cb = *cb;
}

void HSD_MemCallback4(void* arg)
{
    mem_cb.cb4(arg);
}

void HSD_Free(void* ptr)
{
    mem_cb.free(ptr);
}

void* HSD_MemAlloc(u32 size)
{
    return mem_cb.alloc(size, 32, 0);
}
