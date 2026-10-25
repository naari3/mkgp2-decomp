typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x14 - 0x8];
    unsigned short vol;
    unsigned char pad16[0x1c - 0x16];
} SndSlot;

typedef struct Vec3 { float x, y, z; } Vec3;
extern unsigned char ClSound_Initialized;
extern Vec3 lbl_80495F38;
extern void Vec3_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern float PSVECSquareMag(Vec3 *v);
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

int fn_80191B5C(unsigned int id, Vec3 *pts, int n) {
    int slot;
    int best;
    int i;
    float bestD;
    float d;
    Vec3 diff;

    if (!ClSound_Initialized) {
        return 1;
    }
    if (pts == 0) {
        return 0;
    }
    if (n <= 0) {
        return 0;
    }
    slot = FindSlot(id);
    if (slot >= 0) {
        best = -1;
        for (i = 0; i < n; i++) {
            Vec3_Subtract(&pts[i], &lbl_80495F38, &diff);
            d = PSVECSquareMag(&diff);
            if (best < 0) {
                bestD = d;
                best = i;
            } else if (d < bestD) {
                best = i;
                bestD = d;
            }
        }
        return fn_801913B0(slot, &pts[best]);
    }
    return 1;
}
