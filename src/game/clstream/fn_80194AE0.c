typedef struct ClStream {
    unsigned char state;
    unsigned char pad1[3];
    struct ClStream *pair;
    unsigned char pad8[8];
    unsigned int flags;
    unsigned char pad14;
    unsigned char volume;
    unsigned char pad16[0x78 - 0x16];
} ClStream;

extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[];

int fn_80194AE0(unsigned int i, unsigned char vol) {
    ClStream *s;
    ClStream *p;
    if (!g_ClStream_Initialized) {
        return 1;
    }
    if (i > 5) {
        return 0;
    }
    s = &g_ClStreams[i];
    p = s->pair;
    if (p != 0) {
        if (s->state != 0) {
            s->volume = vol;
            p->volume = vol;
            if (s->state > 3) {
                s->flags |= 2;
                p->flags |= 2;
            }
        }
    } else {
        if (s->state != 0) {
            s->volume = vol;
            if (s->state > 3) {
                s->flags |= 2;
            }
        }
    }
    return 1;
}
