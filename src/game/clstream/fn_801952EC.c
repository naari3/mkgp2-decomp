#include "game/types/ClStream.h"

extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[];
extern void *lbl_806D16DC;
extern void *lbl_806CF010;
extern void OSFreeToHeap(void *heap, void *ptr);
extern void sndStreamFree(unsigned int handle);

extern void *OSAllocFromHeap(void *heap, unsigned int size);
extern void fn_80194184(void);
extern unsigned int sndStreamAllocEx(unsigned int, void *, unsigned int, unsigned int,
    unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
    unsigned int, void (*)(void), ClStream *, unsigned int);
extern void DebugPrintf(const char *, ...);
extern const char lbl_8037D1FC[];

void fn_801952EC(void) {
    int i;
    if (g_ClStream_Initialized) return;
    for (i = 0; i < 5; i++) {
        g_ClStreams[i].state = 0;
        g_ClStreams[i].info = 0;
        g_ClStreams[i].handle = -1;
        g_ClStreams[i].base = 0;
    }
    lbl_806D16DC = OSAllocFromHeap(lbl_806CF010, 0x35c0);
    if (lbl_806D16DC == 0) goto fail;
    for (i = 0; i < 5; i++) {
        g_ClStreams[i].info = OSAllocFromHeap(lbl_806CF010, 0x60);
        if (g_ClStreams[i].info == 0) goto fail;
        g_ClStreams[i].base = OSAllocFromHeap(lbl_806CF010, 0xd680);
        if (g_ClStreams[i].base == 0) goto fail;
        g_ClStreams[i].handle = sndStreamAllocEx(0xff, g_ClStreams[i].base,
            0x17760, 0xbb80, 0x7f, 0x40, 0x40, 0, 0, 0, 0x30001,
            fn_80194184, &g_ClStreams[i], 0);
        if (g_ClStreams[i].handle == -1) {
            DebugPrintf(lbl_8037D1FC);
            goto fail;
        }
    }
    g_ClStream_Initialized = 1;
    return;
fail:
    if (lbl_806D16DC != 0) {
        OSFreeToHeap(lbl_806CF010, lbl_806D16DC);
        lbl_806D16DC = 0;
    }
    for (i = 0; i < 5; i++) {
        if (g_ClStreams[i].info != 0) OSFreeToHeap(lbl_806CF010, g_ClStreams[i].info);
        if (g_ClStreams[i].base != 0) OSFreeToHeap(lbl_806CF010, g_ClStreams[i].base);
        g_ClStreams[i].state = 0;
        g_ClStreams[i].info = 0;
        if (g_ClStreams[i].handle != -1) sndStreamFree(g_ClStreams[i].handle);
        g_ClStreams[i].handle = -1;
        g_ClStreams[i].base = 0;
    }
    g_ClStream_Initialized = 0;
}
