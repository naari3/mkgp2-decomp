typedef struct ClStream {
    unsigned char state;
    unsigned char pad1[0xb];
    unsigned int handle;
    unsigned char pad10[0x54 - 0x10];
    void *buf0;
    unsigned char pad58[4];
    void *buf1;
    unsigned char pad60[0x78 - 0x60];
} ClStream;

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
        OSFreeToHeap(lbl_806CF010, g_ClStreams[i].buf0);
        OSFreeToHeap(lbl_806CF010, g_ClStreams[i].buf1);
        g_ClStreams[i].state = 0;
        g_ClStreams[i].buf0 = 0;
        g_ClStreams[i].handle = -1;
        g_ClStreams[i].buf1 = 0;
    }
    g_ClStream_Initialized = 0;
}
