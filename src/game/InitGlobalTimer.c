typedef struct MediaBuffer {
    unsigned char inUse;
    void *data;
} MediaBuffer;

typedef struct MediaRange {
    int start;
    int end;
} MediaRange;

extern MediaBuffer g_mediaBuffers[6];
extern MediaRange lbl_805AC2C0[4];
typedef struct GameSettings {
    unsigned char pad[0x21];
    signed char mediaSlot;
} GameSettings;

extern GameSettings lbl_80598A60;
extern int g_globalTimer;
extern void *FUN_8003b120(int size);

void InitGlobalTimer(void) {
    int i;
    int addr;
    int skip;
    int j;

    for (i = 0; i < 6; i++) {
        g_mediaBuffers[i].inUse = 0;
        g_mediaBuffers[i].data = FUN_8003b120(0xA000);
    }
    addr = 0xE000;
    skip = lbl_80598A60.mediaSlot - 1;
    for (j = 0; j < 4; j++) {
        if (j == skip) {
            lbl_805AC2C0[j].start = 0;
            lbl_805AC2C0[j].end = 0;
        } else {
            lbl_805AC2C0[j].start = addr;
            lbl_805AC2C0[j].end = addr + 0xE000;
            addr += 0x1C000;
        }
    }
    g_globalTimer = 1200;
}
