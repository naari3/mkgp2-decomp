#include "game/types/ClStream.h"

extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[];
extern void *lbl_806D16DC;
extern void *lbl_806CF010;
extern void OSFreeToHeap(void *heap, void *ptr);
extern void sndStreamFree(unsigned int handle);

void fn_8019522C(void) {
    int i;
    if (!g_ClStream_Initialized) {
        return;
    }
    if (lbl_806D16DC != 0) {
        OSFreeToHeap(lbl_806CF010, lbl_806D16DC);
        lbl_806D16DC = 0;
    }
    for (i = 0; i < 5; i++) {
        sndStreamFree(g_ClStreams[i].handle);
        OSFreeToHeap(lbl_806CF010, g_ClStreams[i].info);
        OSFreeToHeap(lbl_806CF010, g_ClStreams[i].base);
        g_ClStreams[i].state = 0;
        g_ClStreams[i].info = 0;
        g_ClStreams[i].handle = -1;
        g_ClStreams[i].base = 0;
    }
    g_ClStream_Initialized = 0;
}
