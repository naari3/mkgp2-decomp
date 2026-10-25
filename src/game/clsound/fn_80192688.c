typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x1c - 0x8];
} SndSlot;

typedef struct SndPrio {
    unsigned int id;
    int state;
    int x;
} SndPrio;

extern unsigned char ClSound_Initialized;
extern SndSlot lbl_80678378[32];
extern SndPrio lbl_80677F40[37];
extern unsigned char fn_80194158(unsigned char v, unsigned char lo, unsigned char hi);

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == lbl_80678378[i].id && !(lbl_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

static inline void TouchPrio(unsigned int id) {
    SndPrio *e;
    int i;
    for (i = 0; i < 37; i++) {
        if (lbl_80677F40[i].id == -1) break;
        if (id == lbl_80677F40[i].id) {
            SndPrio *q;
            lbl_80677F40[i].state = 3;
            lbl_80677F40[i].x = 0;
            q = lbl_80677F40;
            e = &q[i];
            for (; i > 0; e--) {
                SndPrio t;
                int k;
                if (e[-1].state == 3) break;
                k = i - 1;
                t = *e;
                i--;
                e->id = q[k].id;
                e->state = q[k].state;
                e->x = q[k].x;
                q[k] = t;
            }
            break;
        }
    }
}

int fn_80192688(unsigned int id, unsigned char v) {
    int slot;
    unsigned char c;
    if (!ClSound_Initialized) {
        return 1;
    }
    slot = FindSlot(id);
    c = fn_80194158(v, 1, 7);
    if (slot >= 0) {
        TouchPrio(lbl_80678378[slot].id);
        lbl_80678378[slot].flags = (c << 11) | ((lbl_80678378[slot].flags & ~6) | 2);
    }
    return 1;
}
