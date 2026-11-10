/* SoundMgr_Play (0x80192884): start a sound definition in a free voice slot,
 * restarting a voice that already plays the id and stopping same-group voices
 * for exclusive definitions, then queue the id. */
typedef struct SndDef {
    unsigned int effect;
    unsigned char group, mode, pad6[2];
    float nearDistance, farDistance;
    unsigned char volume, pad11;
    unsigned short pitch;
    unsigned char delay, category, pad16[2];
    unsigned int attributes;
} SndDef;

typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char group, pad9[3];
    unsigned int handle;
    unsigned char scale, volume, pan, surround;
    unsigned short pitch, speed;
    unsigned char category, delay, pad1a[2];
} SndSlot;

typedef struct SndQueue {
    unsigned int id;
    int state;
    int timer;
} SndQueue;

extern unsigned char ClSound_Initialized;
extern SndDef lbl_80379554[];
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];
extern SndQueue ClSound_InitSoundSystem_bss_80677F40[37];

static inline void SndQueue_Stop(unsigned int id) {
    int i;
    for (i = 0; i < 37; i++) {
        if (ClSound_InitSoundSystem_bss_80677F40[i].id == 0xFFFFFFFF) break;
        if (id == ClSound_InitSoundSystem_bss_80677F40[i].id) {
            SndQueue *q;
            SndQueue *e;
            ClSound_InitSoundSystem_bss_80677F40[i].state = 3;
            ClSound_InitSoundSystem_bss_80677F40[i].timer = 0;
            q = ClSound_InitSoundSystem_bss_80677F40;
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

static inline int FindPlaying(SndSlot *slots, unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == slots[i].id && !(slots[i].flags & 6)) return i;
    }
    return -1;
}

static inline int FindQueued(unsigned int id) {
    int i;
    for (i = 0; i < 37; i++) {
        if (ClSound_InitSoundSystem_bss_80677F40[i].id == 0xFFFFFFFF) return -1;
        if (id == ClSound_InitSoundSystem_bss_80677F40[i].id) return i;
    }
    return -1;
}

static inline void QueuePush(unsigned int *pid) {
    unsigned int id = *pid;
    int i = FindQueued(id);
    if (i >= 0) {
        SndQueue *q = ClSound_InitSoundSystem_bss_80677F40;
        SndQueue *d = &q[i];
        for (; i < 36; i++, d++) { int k = i + 1; d->id = q[k].id; d->state = q[k].state; d->timer = q[k].timer; }
        ClSound_InitSoundSystem_bss_80677F40[36].id = 0xFFFFFFFF;
    }
    for (i = 0; i < 37; i++) {
        if (ClSound_InitSoundSystem_bss_80677F40[i].id == 0xFFFFFFFF) {
            ClSound_InitSoundSystem_bss_80677F40[i].id = id;
            ClSound_InitSoundSystem_bss_80677F40[i].state = 1;
            ClSound_InitSoundSystem_bss_80677F40[i].timer = 10;
            break;
        }
    }
}

static inline void SlotSetup(SndSlot *s, unsigned int id, SndDef *def) {
    s->id = id;
    s->group = def->group;
    s->category = def->category;
    s->handle = -1;
    s->scale = 0x80;
    s->volume = 0x7F;
    s->pan = 0x40;
    s->surround = 0x40;
    s->pitch = def->pitch;
    s->speed = 0x2000;
    s->delay = def->delay;
}

#pragma exceptions on
int SoundMgr_Play(unsigned int id) {
    unsigned int index;
    SndSlot *s;
    int i;
    SndSlot *slots;
    unsigned int variant;
    if (!ClSound_Initialized) return 0;
    index = id & ~0x78000000;
    variant = id & 0x78000000;
    if (index >= 490) return 0;
    slots = ClSound_InitSoundSystem_bss_80678378;
    i = FindPlaying(slots, id);
    if (i >= 0) {
        if (ClSound_InitSoundSystem_bss_80678378[i].delay != 0) return 1;
        SndQueue_Stop(ClSound_InitSoundSystem_bss_80678378[i].id);
        ClSound_InitSoundSystem_bss_80678378[i].flags = (ClSound_InitSoundSystem_bss_80678378[i].flags & ~6) | 4;
    }
    if (lbl_80379554[index].mode == 2) {
        unsigned char *group = &lbl_80379554[index].group;
        s = slots;
        for (i = 0; i < 32; i++, s++) {
            if (s->id != 0xFFFFFFFF && s->group == *group &&
                variant == (s->id & 0x78000000) && !(s->flags & 6)) {
                SndQueue_Stop(s->id);
                s->flags = (s->flags & ~6) | 4;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        if (slots->flags == 0) break;
        slots++;
    }
    if (i >= 32) return 0;
    {
        SndDef *def = &lbl_80379554[index];
        ClSound_InitSoundSystem_bss_80678378[i].flags = ((def->attributes & 2) ? 0 : 0x200) | 0x11;
        SlotSetup(&ClSound_InitSoundSystem_bss_80678378[i], id, def);
        if (ClSound_InitSoundSystem_bss_80678378[i].pitch != 0x2000) ClSound_InitSoundSystem_bss_80678378[i].flags |= 0x80;
        QueuePush(&ClSound_InitSoundSystem_bss_80678378[i].id);
    }
    return 1;
}
#pragma exceptions reset
