typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad[0x14];
} SndSlot;

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

int fn_80192010(unsigned int id) {
    if (FindSlot(id) >= 0) {
        return 1;
    }
    return 0;
}
