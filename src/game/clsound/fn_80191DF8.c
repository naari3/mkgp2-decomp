typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x14 - 0x8];
    unsigned short vol;
    unsigned char pad16[0x1c - 0x16];
} SndSlot;

typedef struct Vec3 { float x, y, z; } Vec3;
extern unsigned char ClSound_Initialized;
extern const Vec3 lbl_8037CEC4;
extern int fn_801913B0(int slot, Vec3 *pos);
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

int fn_80191DF8(unsigned int id, float x, float y, float z) {
    int i;
    Vec3 v;
    if (!ClSound_Initialized) {
        return 1;
    }
    v = lbl_8037CEC4;
    v.x = x;
    v.y = y;
    v.z = z;
    i = FindSlot(id);
    if (i >= 0) {
        return fn_801913B0(i, &v);
    }
    return 1;
}
