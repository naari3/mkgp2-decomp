typedef struct StreamBuf {
    unsigned char state;
    unsigned char pad1[0xf];
    unsigned int flags;
    unsigned char pad14[0x60 - 0x14];
    unsigned char head;
    unsigned char pad61[3];
    unsigned int used;
} StreamBuf;

int fn_80194184(int unused0, unsigned int avail, int unused2, unsigned int extra, StreamBuf *s) {
    unsigned int total = avail + extra;
    int freed = 0;
    int i;
    int idx;
    if (total < 0x5dd8) {
        return 0;
    }
    for (i = 0; i < 4 && total >= 0x5dd8; i++) {
        idx = s->head + i;
        if (idx >= 4) {
            idx -= 4;
        }
        if (((s->used >> (idx * 2)) & 3) != 3) {
            break;
        }
        s->used &= ~(3 << (idx * 2));
        total -= 0x5dd8;
        freed += 0x5dd8;
    }
    if (s->flags & 0x100) {
        s->state = 5;
    }
    return freed;
}
