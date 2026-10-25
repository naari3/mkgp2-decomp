typedef struct ClStream {
    unsigned char state;
    unsigned char pad1[3];
    struct ClStream *pair;
    struct ClStream *pair2;
    unsigned char padc[4];
    unsigned int flags;
    unsigned char pad14[0x78 - 0x14];
} ClStream;

extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[];
extern unsigned char fn_80194158(unsigned char v, unsigned char lo, unsigned char hi);

int fn_80194CEC(unsigned int i, unsigned char v) {
    unsigned int bits;
    ClStream *p;
    if (!g_ClStream_Initialized) {
        return 1;
    }
    if (i > 5) {
        return 0;
    }
    bits = fn_80194158(v, 1, 7) << 3;
    p = &g_ClStreams[i];
    if (p->state != 0) {
        p->flags |= bits;
    }
    p = g_ClStreams[i].pair;
    if (p != 0 && p->state != 0) {
        p->flags |= bits;
    }
    p = g_ClStreams[i].pair2;
    if (p != 0 && p->state != 0) {
        p->flags |= bits;
    }
    return 1;
}
