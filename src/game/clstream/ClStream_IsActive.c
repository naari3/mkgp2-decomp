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

int ClStream_IsActive(unsigned int i) {
    if (!g_ClStream_Initialized) {
        return 0;
    }
    if (i > 5) {
        return 0;
    }
    return g_ClStreams[i].state != 0;
}
