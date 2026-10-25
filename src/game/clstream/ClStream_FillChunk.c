typedef struct DVDFileInfo { unsigned char pad[0x3c]; } DVDFileInfo;

typedef struct StreamInfo {
    unsigned char pad0[0xc];
    unsigned short loop;
    unsigned short padE;
    unsigned int loopStart;
} StreamInfo;

typedef struct ClStream {
    unsigned char pad0[0x10];
    unsigned int flags;
    unsigned char pad14[4];
    DVDFileInfo dvd;
    StreamInfo *info;
    unsigned int size;
    unsigned char *base;
    unsigned char idx;
    unsigned char pad61[3];
    unsigned int mask;
    unsigned char pad68[4];
    unsigned int pos;
    unsigned int fill;
} ClStream;

extern int DVDReadPrio(DVDFileInfo *f, void *buf, int len, int off, int prio);
extern void *memset(void *, int, unsigned long);
extern void *memcpy(void *, const void *, unsigned long);
extern void DebugPrintf(const char *, ...);
extern unsigned char *lbl_806D16DC;
extern const char lbl_8037D1CC[];

void ClStream_FillChunk(ClStream *s) {
    unsigned int rem;
    unsigned int n;
    unsigned int aligned;
    unsigned int len;
    int r;
    if (((s->mask >> (s->idx * 2)) & 3) != 0) return;
    rem = 0x35a0 - s->fill;
    n = rem;
    if (s->pos + rem > s->size) n = s->size - s->pos;
    if (n != 0) {
        aligned = s->pos & ~3;
        len = (s->pos + n - aligned + 0x1f) & ~0x1f;
        r = DVDReadPrio(&s->dvd, lbl_806D16DC, len, aligned + 0x60, 2);
        if (r < len) {
            if (r < 0) {
                memset(lbl_806D16DC, 0, len);
            } else {
                memset(lbl_806D16DC + r, 0, len - r);
            }
            DebugPrintf(lbl_8037D1CC, len, r);
        }
        memcpy((void *)((unsigned int)s->base + s->idx * 0x35a0 + s->fill), lbl_806D16DC + (s->pos - aligned), n);
        s->pos += n;
        s->fill += n;
        if (s->fill >= 0x35a0) {
            s->mask |= 1 << (s->idx * 2);
            s->fill = 0;
        }
    } else if (s->info->loop != 0) {
        s->pos = s->info->loopStart >> 1;
    } else {
        memset(s->base + s->idx * 0x35a0 + s->fill, 0, rem);
        s->mask |= 1 << (s->idx * 2);
        s->fill = 0;
        if ((s->flags & 0x1c0) != 0x100) s->flags += 0x40;
    }
}
