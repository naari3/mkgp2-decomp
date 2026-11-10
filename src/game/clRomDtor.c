#include "game/types/c_region.h"
C_REGION_BEGIN
/* Observed list-owner layout only; no virtual base or exception specification. */
C_REGION_END
#pragma cplusplus on
#pragma exceptions on

struct clRom {
    unsigned char unknown00[8];
    clRom *previous;
    clRom *next;
    void *payload;
    unsigned char directFree;
    ~clRom();
};

extern "C" {
extern clRom *g_romListHead;
extern clRom *g_romListTail;
extern unsigned int g_romActiveCount;
void HSD_ArchiveFree(void *);
void HSD_Free(void *);
}
void operator delete(void *);

clRom::~clRom() {
    --g_romActiveCount;
    if (payload != 0) {
        if (directFree == 0) HSD_ArchiveFree(payload);
        else HSD_Free(payload);
    }
    if (previous == 0) g_romListHead = next;
    else previous->next = next;
    if (next == 0) g_romListTail = previous;
    else next->previous = previous;
}

#pragma cplusplus off
