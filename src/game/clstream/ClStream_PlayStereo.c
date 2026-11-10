#include "game/types/DVDFileInfo.h"

#include "game/types/ClStream.h"

extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[];
extern unsigned int g_ClStream_LockDepth;
extern int g_ClStream_SavedInterruptLevel;
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern int DVDOpen(const char *path, DVDFileInfo *file);

static inline void Lock(void) {
    if (g_ClStream_LockDepth++ == 0) {
        g_ClStream_SavedInterruptLevel = OSDisableInterrupts();
    }
}

static inline void Unlock(void) {
    if (g_ClStream_LockDepth != 0) {
        if (--g_ClStream_LockDepth == 0) {
            OSRestoreInterrupts(g_ClStream_SavedInterruptLevel);
        }
    }
}

static inline unsigned int AllocStream(void) {
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (g_ClStreams[i].state == 0) {
            g_ClStreams[i].state = 1;
            g_ClStreams[i].pair = 0;
            g_ClStreams[i].pair2 = 0;
            g_ClStreams[i].head = 0;
            g_ClStreams[i].mask = 0;
            g_ClStreams[i].pos = 0;
            g_ClStreams[i].fill = 0;
            g_ClStreams[i].x68 = 0;
            return i;
        }
    }
    return -1;
}

static inline ClStream *GetStream(unsigned int i) {
    return &g_ClStreams[i];
}

extern int DVDClose(DVDFileInfo *file);

int ClStream_PlayStereo(const char *left, const char *right, unsigned char a) {
    unsigned int i, j;
    ClStream *s, *t;
    DVDFileInfo *file;
    if (!g_ClStream_Initialized) return -1;
    Lock();
    i = AllocStream();
    j = AllocStream();
    Unlock();
    if (i == -1 || j == -1) {
        g_ClStreams[i].state = 0;
        g_ClStreams[j].state = 0;
        return -1;
    }
    s = GetStream(i);
    file = &s->file;
    if (!DVDOpen(left, file)) {
        s->state = 0;
        g_ClStreams[j].state = 0;
        return -1;
    }
    t = GetStream(j);
    if (!DVDOpen(right, &t->file)) {
        DVDClose(file);
        s->state = 0;
        t->state = 0;
        return -1;
    }
    g_ClStreams[i].flags = 0;
    g_ClStreams[i].rate = a;
    g_ClStreams[i].volume = 0x7f;
    g_ClStreams[i].pan = 0;
    g_ClStreams[i].bus = 0;
    g_ClStreams[j].flags = 0;
    g_ClStreams[j].rate = a;
    g_ClStreams[j].volume = 0x7f;
    g_ClStreams[j].pan = 0x7f;
    g_ClStreams[j].bus = 0;
    g_ClStreams[i].pair = t;
    g_ClStreams[j].pair2 = s;
    return i;
}
