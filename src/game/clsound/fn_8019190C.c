typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x11 - 0x8];
    unsigned char vol;
    unsigned char padx[0x1c - 0x12];
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

int fn_8019190C(unsigned int id, unsigned char vol) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    i = FindSlot(id);
    if (i >= 0) {
        if (vol != lbl_80678378[i].vol) {
            lbl_80678378[i].vol = vol;
            lbl_80678378[i].flags |= 0x10;
        }
        return 1;
    }
    return 1;
}
