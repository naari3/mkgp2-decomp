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
    unsigned char pad14;
    unsigned char volume;
    unsigned char pan;
    unsigned char pad17;
    DVDFileInfo file;
    unsigned char pad54[0x78 - 0x54];
} ClStream;

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
