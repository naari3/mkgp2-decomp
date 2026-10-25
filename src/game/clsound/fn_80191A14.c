typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x10 - 0x8];
    unsigned char vol;
    unsigned char padx[0x1c - 0x11];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern float Saturate_Double(float v, float lo, float hi);
extern const float lbl_806D9508;
extern const float lbl_806D950C;
extern const float lbl_806D9510;
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

static inline void SetVol(int i, unsigned char vol) {
    if (vol != lbl_80678378[i].vol) {
        lbl_80678378[i].vol = vol;
        lbl_80678378[i].flags |= 0x10;
    }
}

int fn_80191A14(unsigned int id, float f) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    i = FindSlot(id);
    if (i >= 0) {
        SetVol(i, lbl_806D9508 * Saturate_Double(f, lbl_806D950C, lbl_806D9510));
        return 1;
    }
    return 1;
}
