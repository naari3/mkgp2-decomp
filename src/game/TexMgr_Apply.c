/*
 * TexMgr_Apply @ 0x801F947C (size 0x9C).
 *
 * Walks the 256-entry u16 id table at self+0x24 (until 0xFFFF) and preloads
 * one of two resources of each 16-byte lbl_804E5590 entry, picked by
 * self+0x18 (1 -> +8, else +4).
 */

extern void PreloadResource(void *res);

typedef struct TexEntry {
    void *unk0;
    void *resB;
    void *resA;
    void *unkC;
} TexEntry;

typedef struct TexMgr {
    unsigned char pad0[0x18];
    int mode;
    unsigned char pad1C[0x24 - 0x1C];
    unsigned short ids[256];
} TexMgr;

extern TexEntry lbl_804E5590[];

#pragma exceptions on
void TexMgr_Apply(void *arg)
{
    TexMgr *self = arg;
    int i;

    for (i = 0; i < 256; i++) {
        if (self->ids[i] == 0xFFFF) {
            break;
        }
        if (self->mode == 1) {
            PreloadResource(lbl_804E5590[self->ids[i]].resA);
        } else {
            PreloadResource(lbl_804E5590[self->ids[i]].resB);
        }
    }
}
#pragma exceptions reset
