typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char group;
    unsigned char pad9[0x1c - 0x9];
} SndSlot;

typedef struct Voice {
    unsigned int handle;
    int state;
    int x8;
} Voice;

extern unsigned char ClSound_Initialized;
extern SndSlot lbl_80678378[32];
extern Voice lbl_80677F40[37];


static inline void ReleaseVoice(unsigned int h) {
    Voice *e;
    int i;
    for (i = 0; i < 37; i++) {
        if (lbl_80677F40[i].handle == -1) break;
        if (h == lbl_80677F40[i].handle) {
            Voice *q;
            lbl_80677F40[i].state = 3;
            lbl_80677F40[i].x8 = 0;
            q = lbl_80677F40;
            e = &q[i];
            for (; i > 0; e--) {
                Voice t;
                int k;
                if (e[-1].state == 3) break;
                k = i - 1;
                t = *e;
                i--;
                e->handle = q[k].handle;
                e->state = q[k].state;
                e->x8 = q[k].x8;
                q[k] = t;
            }
            break;
        }
    }
}

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == lbl_80678378[i].id && !(lbl_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

int fn_80192348(unsigned int id) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    i = FindSlot(id);
    if (i >= 0) {
        ReleaseVoice(lbl_80678378[i].id);
        lbl_80678378[i].flags = (lbl_80678378[i].flags & ~6) | 4;
    }
    return 1;
}
