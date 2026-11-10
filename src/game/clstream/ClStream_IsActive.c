#include "game/types/ClStream.h"

extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[];

int ClStream_IsActive(unsigned int i) {
    if (!g_ClStream_Initialized) {
        return 0;
    }
    if (i > 5) {
        return 0;
    }
    return g_ClStreams[i].state != 0;
}
