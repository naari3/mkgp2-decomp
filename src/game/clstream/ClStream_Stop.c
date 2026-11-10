#include "game/types/DVDFileInfo.h"

#include "game/types/ClStream.h"

extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[];
extern void sndStreamMixParameter(unsigned int stid, unsigned char vol, unsigned char pan, unsigned char span, unsigned char fxvol);
extern void sndStreamDeactivate(unsigned int stid);
extern int DVDClose(DVDFileInfo *file);

static inline void StopStream(ClStream *s) {
    if (s->state != 0) {
        if (s->state > 3) {
            sndStreamMixParameter(s->handle, 0, s->pan, 0x40, 0);
            sndStreamDeactivate(s->handle);
        }
        DVDClose(&s->file);
        s->state = 0;
    }
}

int ClStream_Stop(unsigned int i) {
    ClStream *s;
    if (!g_ClStream_Initialized) {
        return 1;
    }
    if (i > 5) {
        return 0;
    }
    s = &g_ClStreams[i];
    StopStream(s);
    s = g_ClStreams[i].pair;
    if (s != 0) {
        StopStream(s);
    }
    s = g_ClStreams[i].pair2;
    if (s != 0) {
        StopStream(s);
    }
    return 1;
}
