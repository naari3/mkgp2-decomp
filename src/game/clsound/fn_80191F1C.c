typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x11];
    unsigned char busy;
    unsigned char pad1a[2];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot lbl_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == lbl_80678378[i].id && !(lbl_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

int fn_80191F1C(unsigned int id) {
    int i;
    if (!ClSound_Initialized) {
        return 0;
    }
    i = FindSlot(id);
    if (i >= 0 && lbl_80678378[i].busy) {
        return 0;
    }
    return 1;
}
