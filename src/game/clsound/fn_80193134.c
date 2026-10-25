typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x1c - 0x8];
} SndSlot;

typedef struct SndDef {
    unsigned char pad0[0x18];
    unsigned int attr;
} SndDef;

extern unsigned char lbl_806D16C0;
extern SndSlot lbl_80678378[32];
extern SndDef lbl_80379554[];

void fn_80193134(unsigned char v) {
    int i;
    if (lbl_806D16C0 == v) {
        return;
    }
    lbl_806D16C0 = v;
    for (i = 0; i < 32; i++) {
        if (lbl_80678378[i].id != -1) {
            lbl_80678378[i].flags |= (lbl_80379554[lbl_80678378[i].id & ~0x78000000].attr & 2) ? 0 : 0x200;
        }
    }
}
