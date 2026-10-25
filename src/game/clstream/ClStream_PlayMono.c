typedef struct DVDFileInfo {
    unsigned char pad[0x3c];
} DVDFileInfo;

typedef struct ClStream {
    unsigned char state;
    unsigned char pad1[3];
    struct ClStream *pair;
    struct ClStream *pair2;
    unsigned int handle;
    unsigned int flags;
    unsigned char x14;
    unsigned char volume;
    unsigned char pan;
    unsigned char x17;
    DVDFileInfo file;
    unsigned char pad54[0x60 - 0x54];
    unsigned char x60;
    unsigned char pad61[3];
    unsigned int x64;
    unsigned char x68;
    unsigned char pad69[3];
    unsigned int x6c;
    unsigned int x70;
    unsigned char pad74[0x78 - 0x74];
} ClStream;

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
            g_ClStreams[i].x60 = 0;
            g_ClStreams[i].x64 = 0;
            g_ClStreams[i].x6c = 0;
            g_ClStreams[i].x70 = 0;
            g_ClStreams[i].x68 = 0;
            return i;
        }
    }
    return -1;
}

int ClStream_PlayMono(const char *path, unsigned char a, unsigned char b) {
    unsigned int i;
    ClStream *s;
    if (!g_ClStream_Initialized) {
        return -1;
    }
    Lock();
    i = AllocStream();
    Unlock();
    if (i == -1) {
        return -1;
    }
    s = &g_ClStreams[i];
    if (!DVDOpen(path, &s->file)) {
        s->state = 0;
        return -1;
    }
    g_ClStreams[i].flags = 0;
    g_ClStreams[i].x14 = a;
    g_ClStreams[i].volume = 0x7f;
    g_ClStreams[i].pan = 0x40;
    g_ClStreams[i].x17 = b;
    return i;
}
