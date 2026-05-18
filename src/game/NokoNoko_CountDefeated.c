typedef struct NokoNoko {
    struct NokoNoko *next;
    unsigned char pad_0x04[0x8];
    int state;
} NokoNoko;

extern unsigned char g_nokonokoEnable;
extern NokoNoko *g_nokonokoHead;

int NokoNoko_CountDefeated(void) {
    int count;
    NokoNoko *p;

    if (g_nokonokoEnable == 0) {
        return 0;
    }
    count = 0;
    for (p = g_nokonokoHead; p != 0; p = p->next) {
        if (p->state >= 4) {
            count = count + 1;
        }
    }
    return count;
}
