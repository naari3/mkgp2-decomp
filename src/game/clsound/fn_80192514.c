typedef struct SndQueue {
    unsigned int id;
    int state;
    int timer;
} SndQueue;

typedef struct SndSlot {
    union {
        unsigned int flags;
        struct {
            unsigned int pad : 29;
            unsigned int stopping : 1;
            unsigned int paused : 1;
            unsigned int loop : 1;
        } b;
    } u;
    unsigned int id;
    unsigned char group;
    unsigned char pad9[0x1c - 9];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot lbl_80678378[32];
extern SndQueue lbl_80677F40[37];

static inline void SndQueue_Stop(unsigned int id) {
    int i;
    for (i = 0; i < 37; i++) {
        if (lbl_80677F40[i].id == 0xFFFFFFFF) break;
        if (id == lbl_80677F40[i].id) {
            SndQueue *q;
            SndQueue *e;
            lbl_80677F40[i].state = 3;
            lbl_80677F40[i].timer = 0;
            q = lbl_80677F40;
            e = &q[i];
            for (; i > 0; e--) {
                SndQueue t;
                int k;
                if (e[-1].state == 3) break;
                k = i - 1;
                t = *e;
                i--;
                e->id = q[k].id;
                e->state = q[k].state;
                e->timer = q[k].timer;
                q[k] = t;
            }
            break;
        }
    }
}

extern unsigned char fn_80194158(int a, int b, int c);

int fn_80192514(unsigned int group, int a) {
    int i;
    unsigned int v;
    if (!ClSound_Initialized) return 1;
    v = fn_80194158(a, 1, 7) << 11;
    for (i = 0; i < 32; i++) {
        SndSlot *s = &lbl_80678378[i];
        if (s->id != 0xFFFFFFFF && group == s->group && !(s->u.flags & 6)) {
            SndQueue_Stop(s->id);
            s->u.flags = v | ((s->u.flags & ~6) | 2);
        }
    }
    return 1;
}
