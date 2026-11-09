/* SoundMgr_Play (0x80192884): start a sound request by id. */

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct SoundDefInfo {
    u8 group;
    u8 type;
    u8 pad2[0x12 - 0x6];
    u16 x12;
    u8 x14;
    u8 x15;
    u8 pad16[2];
    u32 x18;
} SoundDefInfo;

typedef struct SoundDef {
    u32 x0;
    SoundDefInfo info;
} SoundDef;

typedef struct SoundInfo {
    u32 id;
    u8 group;
    u8 pad9[3];
    int xC;
    u8 x10;
    u8 x11;
    u8 x12;
    u8 x13;
    u16 x14;
    u16 x16;
    u8 x18;
    u8 x19;
    u8 pad1A[2];
} SoundInfo;

typedef struct SoundSlot {
    u32 flags;
    SoundInfo info;
} SoundSlot;

typedef struct SoundQueue {
    u32 id;
    int state;
    int timer;
} SoundQueue;

extern u8 ClSound_Initialized;
extern SoundDef lbl_80379554[];
extern SoundQueue lbl_80677F40[];
extern SoundSlot lbl_80678378[];

static inline void SoundQueue_Stop(u32 id) {
    SoundQueue *p;
    SoundQueue tmp;
    int i;

    for (i = 0; i < 37; i++) {
        if (lbl_80677F40[i].id == 0xFFFFFFFF) {
            break;
        }
        if (id == lbl_80677F40[i].id) {
            p = &lbl_80677F40[i];
            p->state = 3;
            p->timer = 0;
            for (; i > 0; i--) {
                SoundQueue *q;
                if (p[-1].state == 3) {
                    break;
                }
                q = &lbl_80677F40[i - 1];
                tmp = *p;
                p->id = q->id;
                p->state = q->state;
                p->timer = q->timer;
                *q = tmp;
                p--;
            }
            break;
        }
    }
}

static inline int SoundQueue_Find(u32 id) {
    int i;

    for (i = 0; i < 37; i++) {
        if (lbl_80677F40[i].id == 0xFFFFFFFF) {
            return -1;
        }
        if (id == lbl_80677F40[i].id) {
            return i;
        }
    }
    return -1;
}

static inline void SoundQueue_Push(SoundInfo *info) {
    int i;
    u32 id = info->id;

    i = SoundQueue_Find(id);
    if (i >= 0) {
        SoundQueue *p = &lbl_80677F40[i];
        for (; i < 36; i++) {
            SoundQueue *q = &lbl_80677F40[i + 1];
            p->id = q->id;
            p->state = q->state;
            p->timer = q->timer;
            p++;
        }
        lbl_80677F40[36].id = 0xFFFFFFFF;
    }
    for (i = 0; i < 37; i++) {
        if (lbl_80677F40[i].id == 0xFFFFFFFF) {
            lbl_80677F40[i].id = id;
            lbl_80677F40[i].state = 1;
            lbl_80677F40[i].timer = 10;
            break;
        }
    }
}

static inline int SoundSlot_Find(SoundSlot *s, u32 id) {
    int i;

    for (i = 0; i < 32; i++) {
        if (id == s[i].info.id && (s[i].flags & 6) == 0) {
            return i;
        }
    }
    return -1;
}

int SoundMgr_Play(u32 id) {
    SoundSlot *s;
    SoundDefInfo *info;
    int slot;
    u32 index;
    SoundSlot *slots;
    int i;
    SoundDef *def;
    u32 category;
    SoundSlot *ns;

    if (ClSound_Initialized == 0) {
        return 0;
    }
    index = id & 0x87FFFFFF;
    category = id & 0x78000000;
    if (index >= 0x1EA) {
        return 0;
    }
    slots = lbl_80678378;
    slot = SoundSlot_Find(slots, id);
    if (slot >= 0) {
        if (lbl_80678378[slot].info.x19 != 0) {
            return 1;
        }
        SoundQueue_Stop(lbl_80678378[slot].info.id);
        lbl_80678378[slot].flags = (lbl_80678378[slot].flags & ~6) | 4;
    }
    if (lbl_80379554[index].info.type == 2) {
        info = &lbl_80379554[index].info;
        s = slots;
        for (i = 0; i < 32; i++, s++) {
            if (s->info.id != 0xFFFFFFFF && s->info.group == info->group &&
                category == (s->info.id & 0x78000000) && (s->flags & 6) == 0) {
                SoundQueue_Stop(s->info.id);
                s->flags = (s->flags & ~6) | 4;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        if (slots->flags == 0) {
            break;
        }
        slots++;
    }
    if (i >= 32) {
        return 0;
    }
    def = &lbl_80379554[index];
    ns = &lbl_80678378[i];
    ns->flags = (((def->info.x18 >> 1) & 1) ? 0 : 0x200) | 0x11;
    ns->info.id = id;
    ns->info.group = def->info.group;
    ns->info.x18 = def->info.x15;
    ns->info.xC = -1;
    ns->info.x10 = 0x80;
    ns->info.x11 = 0x7F;
    ns->info.x12 = 0x40;
    ns->info.x13 = 0x40;
    ns->info.x14 = def->info.x12;
    ns->info.x16 = 0x2000;
    ns->info.x19 = def->info.x14;
    if (ns->info.x14 != 0x2000) {
        ns->flags |= 0x80;
    }
    SoundQueue_Push(&lbl_80678378[i].info);
    return 1;
}
