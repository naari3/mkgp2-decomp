/* clsound voice/listener unit, .text 0x801913B0..0x801933D0, merged from the
 * over-split per-function files (fn_801913B0 needs the listener pool that
 * fn_80192F04 owns: .data 0x80495F20..0x80495F48). */
#define lbl_80495F20 lbl_80495F20_hdr
#include "game/clsound_spatial_private.h"
#undef lbl_80495F20
static ClSoundVec lbl_80495F20 = {0.0f, 0.0f, 0.0f};
static ClSoundVec lbl_80495F2C = {0.0f, 0.0f, 0.0f};
typedef struct FogEye { ClSoundVec pos; float w; } FogEye;
static FogEye lbl_80495F38 = {{0.0f, 0.0f, 0.0f}, 0.0f};

/* ==== game/clsound/fn_801913B0.c (0x801913B0) ==== */
#pragma exceptions on
int fn_801913B0(int index, const ClSoundVec* position) {
    unsigned int sound_id;
    const ClSoundDef* definition;
    ClSoundVec delta;
    float near_distance, far_distance, distance;
    int volume, pan, surround;
    sound_id = ClSound_InitSoundSystem_bss_80678378[index].id & ~0x78000000;
    definition = &lbl_80379554[sound_id];
    near_distance = definition->near_distance;
    far_distance = definition->far_distance;
    Vec3_Subtract(position, &lbl_80495F38.pos, &delta);
    distance = Vec3_Magnitude(&delta);
    if (distance >= far_distance) { volume=0; surround=pan=64; }
    else {
        if (distance <= near_distance) volume=127;
        else volume=(int)(lbl_806D9514-lbl_806D9514*((distance-near_distance)/(far_distance-near_distance)));
        distance=Vec3_Dot(&delta, &lbl_80495F20);
        if (distance >= near_distance) pan=0;
        else if (distance <= -near_distance) pan=127;
        else pan=(int)(lbl_806D9518-lbl_806D951C*(distance/near_distance));
        distance=Vec3_Dot(&delta, &lbl_80495F2C);
        if (distance >= near_distance) surround=127;
        else if (distance <= -near_distance) surround=0;
        else surround=(int)(lbl_806D9518+lbl_806D951C*(distance/near_distance));
    }
    if ((unsigned char)volume != ClSound_InitSoundSystem_bss_80678378[index].volume) { ClSound_InitSoundSystem_bss_80678378[index].volume=volume; ClSound_InitSoundSystem_bss_80678378[index].flags |= 0x10; }
    if ((unsigned char)pan != ClSound_InitSoundSystem_bss_80678378[index].pan) { ClSound_InitSoundSystem_bss_80678378[index].pan=pan; ClSound_InitSoundSystem_bss_80678378[index].flags |= 0x20; }
    if ((unsigned char)surround != ClSound_InitSoundSystem_bss_80678378[index].surround) { ClSound_InitSoundSystem_bss_80678378[index].surround=surround; ClSound_InitSoundSystem_bss_80678378[index].flags |= 0x40; }
    return 1;
}

#pragma exceptions reset

/* ==== game/clsound/fn_801915DC.c (0x801915DC) ==== */
#define Entry Entry_p1
#define lbl_80379554 lbl_80379554_p1
#pragma exceptions off
typedef struct Entry {
    unsigned char pad[0x10];
    unsigned char val;
    unsigned char pad2[0xb];
} Entry;
extern Entry lbl_80379554[];

unsigned char fn_801915DC(int i) {
    return lbl_80379554[i].val;
}
#pragma exceptions reset
#undef Entry
#undef lbl_80379554

/* ==== game/clsound/fn_801915F4.c (0x801915F4) ==== */
#define ClSound_Initialized ClSound_Initialized_p2
#define FindSlot FindSlot_p2
#define SndSlot SndSlot_p2
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p2
#pragma exceptions off
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x14 - 0x8];
    unsigned short vol;
    unsigned char pad16[0x1c - 0x16];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

int fn_801915F4(unsigned int id, unsigned short vol) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    i = FindSlot(id);
    if (i >= 0) {
        if (vol != ClSound_InitSoundSystem_bss_80678378[i].vol) {
            ClSound_InitSoundSystem_bss_80678378[i].vol = vol;
            ClSound_InitSoundSystem_bss_80678378[i].flags |= 0x80;
        }
        return 1;
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_801916FC.c (0x801916FC) ==== */
#define ClSound_Initialized ClSound_Initialized_p3
#define FindSlot FindSlot_p3
#define SndSlot SndSlot_p3
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p3
#pragma exceptions off
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x13 - 0x8];
    unsigned char vol;
    unsigned char padx[0x1c - 0x14];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

int fn_801916FC(unsigned int id, unsigned char vol) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    i = FindSlot(id);
    if (i >= 0) {
        if (vol != ClSound_InitSoundSystem_bss_80678378[i].vol) {
            ClSound_InitSoundSystem_bss_80678378[i].vol = vol;
            ClSound_InitSoundSystem_bss_80678378[i].flags |= 0x40;
        }
        return 1;
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80191804.c (0x80191804) ==== */
#define ClSound_Initialized ClSound_Initialized_p4
#define FindSlot FindSlot_p4
#define SndSlot SndSlot_p4
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p4
#pragma exceptions off
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x12 - 0x8];
    unsigned char vol;
    unsigned char padx[0x1c - 0x13];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

int fn_80191804(unsigned int id, unsigned char vol) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    i = FindSlot(id);
    if (i >= 0) {
        if (vol != ClSound_InitSoundSystem_bss_80678378[i].vol) {
            ClSound_InitSoundSystem_bss_80678378[i].vol = vol;
            ClSound_InitSoundSystem_bss_80678378[i].flags |= 0x20;
        }
        return 1;
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_8019190C.c (0x8019190C) ==== */
#define ClSound_Initialized ClSound_Initialized_p5
#define FindSlot FindSlot_p5
#define SndSlot SndSlot_p5
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p5
#pragma exceptions off
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x11 - 0x8];
    unsigned char vol;
    unsigned char padx[0x1c - 0x12];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
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
        if (vol != ClSound_InitSoundSystem_bss_80678378[i].vol) {
            ClSound_InitSoundSystem_bss_80678378[i].vol = vol;
            ClSound_InitSoundSystem_bss_80678378[i].flags |= 0x10;
        }
        return 1;
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80191A14.c (0x80191A14) ==== */
#define ClSound_Initialized ClSound_Initialized_p6
#define FindSlot FindSlot_p6
#define Saturate_Double Saturate_Double_p6
#define SetVol SetVol_p6
#define SndSlot SndSlot_p6
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p6
#define lbl_806D9508 lbl_806D9508_p6
#define lbl_806D950C lbl_806D950C_p6
#define lbl_806D9510 lbl_806D9510_p6
#pragma exceptions on
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
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

static inline void SetVol(int i, unsigned char vol) {
    if (vol != ClSound_InitSoundSystem_bss_80678378[i].vol) {
        ClSound_InitSoundSystem_bss_80678378[i].vol = vol;
        ClSound_InitSoundSystem_bss_80678378[i].flags |= 0x10;
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
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef Saturate_Double
#undef SetVol
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80678378
#undef lbl_806D9508
#undef lbl_806D950C
#undef lbl_806D9510

/* ==== game/clsound/fn_80191B5C.c (0x80191B5C) ==== */
#define ClSound_Initialized ClSound_Initialized_p7
#define FindSlot FindSlot_p7
#define PSVECSquareMag PSVECSquareMag_p7
#define SndSlot SndSlot_p7
#define Vec3 Vec3_p7
#define Vec3_Subtract Vec3_Subtract_p7
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p7
#define lbl_80495F38 (*(Vec3 *)&lbl_80495F38)
#define fn_801913B0 fn_801913B0_ext1
extern int fn_801913B0(int slot, void *pos);
#pragma exceptions on
#pragma use_lmw_stmw on
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x14 - 0x8];
    unsigned short vol;
    unsigned char pad16[0x1c - 0x16];
} SndSlot;

typedef struct Vec3 { float x, y, z; } Vec3;
extern unsigned char ClSound_Initialized;

extern void Vec3_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern float PSVECSquareMag(Vec3 *v);

extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
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
#pragma use_lmw_stmw reset
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef PSVECSquareMag
#undef SndSlot
#undef Vec3
#undef Vec3_Subtract
#undef ClSound_InitSoundSystem_bss_80678378
#undef lbl_80495F38
#undef fn_801913B0

/* ==== game/clsound/fn_80191CF4.c (0x80191CF4) ==== */
#define ClSound_Initialized ClSound_Initialized_p8
#define FindSlot FindSlot_p8
#define SndSlot SndSlot_p8
#define Vec3 Vec3_p8
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p8
#define fn_801913B0 fn_801913B0_ext2
extern int fn_801913B0(int slot, void *pos);
#pragma exceptions on
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x14 - 0x8];
    unsigned short vol;
    unsigned char pad16[0x1c - 0x16];
} SndSlot;

typedef struct Vec3 { float x, y, z; } Vec3;
extern unsigned char ClSound_Initialized;

extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

int fn_80191CF4(unsigned int id, Vec3 *pos) {
    int i;
    if (!ClSound_Initialized) {
        return 1;
    }
    if (pos == 0) {
        return 0;
    }
    i = FindSlot(id);
    if (i >= 0) {
        return fn_801913B0(i, pos);
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndSlot
#undef Vec3
#undef ClSound_InitSoundSystem_bss_80678378
#undef fn_801913B0

/* ==== game/clsound/fn_80191DF8.c (0x80191DF8) ==== */
#define ClSound_Initialized ClSound_Initialized_p9
#define FindSlot FindSlot_p9
#define SndSlot SndSlot_p9
#define Vec3 Vec3_p9
#define lbl_8037CEC4 lbl_8037CEC4_p9
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p9
#define fn_801913B0 fn_801913B0_ext3
extern int fn_801913B0(int slot, void *pos);
#pragma exceptions on
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

extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
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
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndSlot
#undef Vec3
#undef lbl_8037CEC4
#undef ClSound_InitSoundSystem_bss_80678378
#undef fn_801913B0

/* ==== game/clsound/fn_80191F1C.c (0x80191F1C) ==== */
#define ClSound_Initialized ClSound_Initialized_p10
#define FindSlot FindSlot_p10
#define SndSlot SndSlot_p10
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p10
#pragma exceptions off
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad8[0x11];
    unsigned char busy;
    unsigned char pad1a[2];
} SndSlot;

extern unsigned char ClSound_Initialized;
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

int fn_80191F1C(unsigned int id) {
    int i;
    if (!ClSound_Initialized) {
        return 0;
    }
    i = FindSlot(id);
    if (i >= 0 && ClSound_InitSoundSystem_bss_80678378[i].busy) {
        return 0;
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80192010.c (0x80192010) ==== */
#define FindSlot FindSlot_p11
#define SndSlot SndSlot_p11
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p11
#pragma exceptions off
typedef struct SndSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char pad[0x14];
} SndSlot;

extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
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
#pragma exceptions reset
#undef FindSlot
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_801920D4.c (0x801920D4) ==== */
#define ClSound_Initialized ClSound_Initialized_p12
#define SndQueue SndQueue_p12
#define SndQueue_Stop SndQueue_Stop_p12
#define SndSlot SndSlot_p12
#define ClSound_InitSoundSystem_bss_80677F40 lbl_80677F40_p12
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p12
#pragma exceptions on
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

int fn_801920D4(void) {
    int i;
    if (!ClSound_Initialized) return 1;
    for (i = 0; i < 32; i++) {
        SndSlot *s = &ClSound_InitSoundSystem_bss_80678378[i];
        if (s->id != 0xFFFFFFFF && !(s->u.flags & 6)) {
            SndQueue_Stop(s->id);
            s->u.flags = (s->u.flags & ~6) | 4;
        }
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef SndQueue
#undef SndQueue_Stop
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80677F40
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80192208.c (0x80192208) ==== */
#define ClSound_Initialized ClSound_Initialized_p13
#define SndQueue SndQueue_p13
#define SndQueue_Stop SndQueue_Stop_p13
#define SndSlot SndSlot_p13
#define ClSound_InitSoundSystem_bss_80677F40 lbl_80677F40_p13
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p13
#pragma exceptions on
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

int fn_80192208(unsigned int group) {
    int i;
    if (!ClSound_Initialized) return 1;
    for (i = 0; i < 32; i++) {
        SndSlot *s = &ClSound_InitSoundSystem_bss_80678378[i];
        if (s->id != 0xFFFFFFFF && group == s->group && !(s->u.flags & 6)) {
            SndQueue_Stop(s->id);
            s->u.flags = (s->u.flags & ~6) | 4;
        }
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef SndQueue
#undef SndQueue_Stop
#undef SndSlot
#undef ClSound_InitSoundSystem_bss_80677F40
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80192348.c (0x80192348) ==== */
#define ClSound_Initialized ClSound_Initialized_p14
#define FindSlot FindSlot_p14
#define ReleaseVoice ReleaseVoice_p14
#define SndSlot SndSlot_p14
#define Voice Voice_p14
#define ClSound_InitSoundSystem_bss_80677F40 lbl_80677F40_p14
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p14
#pragma exceptions on
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
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];
extern Voice ClSound_InitSoundSystem_bss_80677F40[37];


static inline void ReleaseVoice(unsigned int h) {
    Voice *e;
    int i;
    for (i = 0; i < 37; i++) {
        if (ClSound_InitSoundSystem_bss_80677F40[i].handle == -1) break;
        if (h == ClSound_InitSoundSystem_bss_80677F40[i].handle) {
            Voice *q;
            ClSound_InitSoundSystem_bss_80677F40[i].state = 3;
            ClSound_InitSoundSystem_bss_80677F40[i].x8 = 0;
            q = ClSound_InitSoundSystem_bss_80677F40;
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
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
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
        ReleaseVoice(ClSound_InitSoundSystem_bss_80678378[i].id);
        ClSound_InitSoundSystem_bss_80678378[i].flags = (ClSound_InitSoundSystem_bss_80678378[i].flags & ~6) | 4;
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef ReleaseVoice
#undef SndSlot
#undef Voice
#undef ClSound_InitSoundSystem_bss_80677F40
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80192514.c (0x80192514) ==== */
#define ClSound_Initialized ClSound_Initialized_p15
#define SndQueue SndQueue_p15
#define SndQueue_Stop SndQueue_Stop_p15
#define SndSlot SndSlot_p15
#define fn_80194158 fn_80194158_p15
#define ClSound_InitSoundSystem_bss_80677F40 lbl_80677F40_p15
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p15
#pragma exceptions on
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

extern unsigned char fn_80194158(int a, int b, int c);

int fn_80192514(unsigned int group, int a) {
    int i;
    unsigned int v;
    if (!ClSound_Initialized) return 1;
    v = fn_80194158(a, 1, 7) << 11;
    for (i = 0; i < 32; i++) {
        SndSlot *s = &ClSound_InitSoundSystem_bss_80678378[i];
        if (s->id != 0xFFFFFFFF && group == s->group && !(s->u.flags & 6)) {
            SndQueue_Stop(s->id);
            s->u.flags = v | ((s->u.flags & ~6) | 2);
        }
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef SndQueue
#undef SndQueue_Stop
#undef SndSlot
#undef fn_80194158
#undef ClSound_InitSoundSystem_bss_80677F40
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80192688.c (0x80192688) ==== */
#define ClSound_Initialized ClSound_Initialized_p16
#define FindSlot FindSlot_p16
#define SndPrio SndPrio_p16
#define SndSlot SndSlot_p16
#define TouchPrio TouchPrio_p16
#define fn_80194158 fn_80194158_p16
#define ClSound_InitSoundSystem_bss_80677F40 lbl_80677F40_p16
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p16
#pragma exceptions on
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
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];
extern SndPrio ClSound_InitSoundSystem_bss_80677F40[37];
extern unsigned char fn_80194158(unsigned char v, unsigned char lo, unsigned char hi);

static inline int FindSlot(unsigned int id) {
    int i;
    for (i = 0; i < 32; i++) {
        if (id == ClSound_InitSoundSystem_bss_80678378[i].id && !(ClSound_InitSoundSystem_bss_80678378[i].flags & 6)) {
            return i;
        }
    }
    return -1;
}

static inline void TouchPrio(unsigned int id) {
    SndPrio *e;
    int i;
    for (i = 0; i < 37; i++) {
        if (ClSound_InitSoundSystem_bss_80677F40[i].id == -1) break;
        if (id == ClSound_InitSoundSystem_bss_80677F40[i].id) {
            SndPrio *q;
            ClSound_InitSoundSystem_bss_80677F40[i].state = 3;
            ClSound_InitSoundSystem_bss_80677F40[i].x = 0;
            q = ClSound_InitSoundSystem_bss_80677F40;
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
        TouchPrio(ClSound_InitSoundSystem_bss_80678378[slot].id);
        ClSound_InitSoundSystem_bss_80678378[slot].flags = (c << 11) | ((ClSound_InitSoundSystem_bss_80678378[slot].flags & ~6) | 2);
    }
    return 1;
}
#pragma exceptions reset
#undef ClSound_Initialized
#undef FindSlot
#undef SndPrio
#undef SndSlot
#undef TouchPrio
#undef fn_80194158
#undef ClSound_InitSoundSystem_bss_80677F40
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/SoundMgr_Play.c (0x) ==== */
#define ClSound_Initialized ClSound_Initialized_p17
#define lbl_80379554 lbl_80379554_p17
#define ClSound_InitSoundSystem_bss_80677F40 lbl_80677F40_p17
#define ClSound_InitSoundSystem_bss_80678378 lbl_80678378_p17
#pragma exceptions off
/* === extracted from auto_SoundMgr_Play_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int ClSound_Initialized;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80379554[];
extern unsigned int ClSound_InitSoundSystem_bss_80677F40[];
extern unsigned int ClSound_InitSoundSystem_bss_80678378[];

/* --- function index (1 fns, .text 0x80192884..0x80192F04) ---
 * [  0] 0x80192884 size:0x680   global SoundMgr_Play
 */

/* --- forward decls --- */
#ifdef NON_MATCHING
int SoundMgr_Play(unsigned int id);
#else
asm void SoundMgr_Play(void);
#endif

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SoundMgr_Play[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SoundMgr_Play = {
    (void *)&SoundMgr_Play, 0x00000680, (void *)extab_SoundMgr_Play
};

/* --- asm function bodies (.text order = fn address order) --- */
#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C, register-only differences left (docs/gave_up.md,
 * docs/wip/SoundMgr_Play_104lines.c). Starts a sound request by id. */
typedef struct SPDefInfo {
    unsigned char group;
    unsigned char type;
    unsigned char pad2[0x12 - 0x6];
    unsigned short x12;
    unsigned char x14;
    unsigned char x15;
    unsigned char pad16[2];
    unsigned int x18;
} SPDefInfo;

typedef struct SPDef {
    unsigned int x0;
    SPDefInfo info;
} SPDef;

typedef struct SPInfo {
    unsigned int id;
    unsigned char group;
    unsigned char pad9[3];
    int xC;
    unsigned char x10;
    unsigned char x11;
    unsigned char x12;
    unsigned char x13;
    unsigned short x14;
    unsigned short x16;
    unsigned char x18;
    unsigned char x19;
    unsigned char pad1A[2];
} SPInfo;

typedef struct SPSlot {
    unsigned int flags;
    SPInfo info;
} SPSlot;

typedef struct SPQueue {
    unsigned int id;
    int state;
    int timer;
} SPQueue;


#define SP_DEFS ((SPDef *)lbl_80379554)
#define SP_QUEUE ((SPQueue *)ClSound_InitSoundSystem_bss_80677F40)
#define SP_SLOTS ((SPSlot *)ClSound_InitSoundSystem_bss_80678378)
static inline void SoundQueue_Stop(unsigned int id) {
    int i;
    for (i = 0; i < 37; i++) {
        if (SP_QUEUE[i].id == 0xFFFFFFFF) break;
        if (id == SP_QUEUE[i].id) {
            SPQueue *q;
            SPQueue *e;
            SP_QUEUE[i].state = 3;
            SP_QUEUE[i].timer = 0;
            q = SP_QUEUE;
            e = &q[i];
            for (; i > 0; e--) {
                SPQueue t;
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

static inline int SoundQueue_Find(SPQueue *q, unsigned int id) {
    int i;
    for (i = 0; i < 37; i++) {
        if (q[i].id == 0xFFFFFFFF) return -1;
        if (id == q[i].id) return i;
    }
    return -1;
}

static inline void SoundQueue_Push(SPQueue *q, SPInfo *info) {
    unsigned int id = info->id;
    int i;

    i = SoundQueue_Find(q, id);
    if (i >= 0) {
        SPQueue *p = &q[i];
        for (; i < 36; i++) {
            SPQueue *n = &SP_QUEUE[i + 1];
            p->id = n->id;
            p->state = n->state;
            p->timer = n->timer;
            p++;
        }
        SP_QUEUE[36].id = 0xFFFFFFFF;
    }
    for (i = 0; i < 37; i++, q++) {
        if (q->id == 0xFFFFFFFF) {
            SP_QUEUE[i].id = id;
            SP_QUEUE[i].state = 1;
            SP_QUEUE[i].timer = 10;
            break;
        }
    }
}

static inline int SoundSlot_Find(SPSlot *s, unsigned int id) {
    int i;

    for (i = 0; i < 32; i++) {
        if (id == s[i].info.id && (s[i].flags & 6) == 0) {
            return i;
        }
    }
    return -1;
}

int SoundMgr_Play(unsigned int id) {
    SPSlot *s;
    SPDefInfo *info;
    int i;
    SPSlot *slots;
    int j;
    unsigned int index;
    int slot;
    SPDef *def;
    unsigned int category;

    if (*(unsigned char *)&ClSound_Initialized == 0) {
        return 0;
    }
    index = id & 0x87FFFFFF;
    category = id & 0x78000000;
    if (index >= 0x1EA) {
        return 0;
    }
    slots = SP_SLOTS;
    slot = SoundSlot_Find(slots, id);
    if (slot >= 0) {
        if (SP_SLOTS[slot].info.x19 != 0) {
            return 1;
        }
        SoundQueue_Stop(SP_SLOTS[slot].info.id);
        SP_SLOTS[slot].flags = (SP_SLOTS[slot].flags & ~6) | 4;
    }
    if (SP_DEFS[index].info.type == 2) {
        info = &SP_DEFS[index].info;
        s = slots;
        for (j = 0; j < 32; j++, s++) {
            if (s->info.id != 0xFFFFFFFF && s->info.group == info->group &&
                category == (s->info.id & 0x78000000) && (s->flags & 6) == 0) {
                SoundQueue_Stop(s->info.id);
                s->flags = (s->flags & ~6) | 4;
            }
        }
    }
    for (i = 0; i < 32; i++, slots++) {
        if (slots->flags == 0) {
            break;
        }
    }
    if (i >= 32) {
        return 0;
    }
    SP_SLOTS[i].flags = (((SP_DEFS[index].info.x18 >> 1) & 1) ? 0 : 0x200) | 0x11;
    SP_SLOTS[i].info.id = id;
    SP_SLOTS[i].info.group = SP_DEFS[index].info.group;
    SP_SLOTS[i].info.x18 = SP_DEFS[index].info.x15;
    SP_SLOTS[i].info.xC = -1;
    SP_SLOTS[i].info.x10 = 0x80;
    SP_SLOTS[i].info.x11 = 0x7F;
    SP_SLOTS[i].info.x12 = 0x40;
    SP_SLOTS[i].info.x13 = 0x40;
    SP_SLOTS[i].info.x14 = SP_DEFS[index].info.x12;
    SP_SLOTS[i].info.x16 = 0x2000;
    SP_SLOTS[i].info.x19 = SP_DEFS[index].info.x14;
    if (SP_SLOTS[i].info.x14 != 0x2000) {
        SP_SLOTS[i].flags |= 0x80;
    }
    SoundQueue_Push(SP_QUEUE, &SP_SLOTS[i].info);
    return 1;
}
#undef SP_DEFS
#undef SP_QUEUE
#undef SP_SLOTS
#else
asm void SoundMgr_Play(void) { /* 0x80192884 size:0x680 */
    nofralloc
    stwu r1, -0x30(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    lbz r0, ClSound_Initialized(r13)
    cmplwi r0, 0x0
    bne SoundMgr_Play_L_801928AC
    li r3, 0x0
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_801928AC:
    rlwinm r4, r3, 0, 5, 0
    rlwinm r8, r3, 0, 1, 4
    cmplwi r4, 0x1ea
    blt SoundMgr_Play_L_801928C4
    li r3, 0x0
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_801928C4:
    lis r5, ClSound_InitSoundSystem_bss_80678378@ha
    li r0, 0x8
    addi r6, r5, ClSound_InitSoundSystem_bss_80678378@l
    li r5, 0x0
    mr r7, r6
    mtctr r0
    SoundMgr_Play_L_801928DC:
    lwz r0, 0x4(r7)
    cmplw r3, r0
    bne SoundMgr_Play_L_801928F8
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_801928F8
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_801928F8:
    lwz r0, 0x20(r7)
    addi r5, r5, 0x1
    addi r7, r7, 0x1c
    cmplw r3, r0
    bne SoundMgr_Play_L_8019291C
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_8019291C
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_8019291C:
    lwz r0, 0x20(r7)
    addi r5, r5, 0x1
    addi r7, r7, 0x1c
    cmplw r3, r0
    bne SoundMgr_Play_L_80192940
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_80192940
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_80192940:
    lwz r0, 0x20(r7)
    addi r5, r5, 0x1
    addi r7, r7, 0x1c
    cmplw r3, r0
    bne SoundMgr_Play_L_80192964
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_80192964
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_80192964:
    addi r7, r7, 0x1c
    addi r5, r5, 0x1
    bdnz SoundMgr_Play_L_801928DC
    li r5, -0x1
    SoundMgr_Play_L_80192974:
    cmpwi r5, 0x0
    blt SoundMgr_Play_L_80192A84
    mulli r0, r5, 0x1c
    lis r5, ClSound_InitSoundSystem_bss_80678378@ha
    addi r5, r5, ClSound_InitSoundSystem_bss_80678378@l
    add r9, r5, r0
    lbz r5, 0x19(r9)
    cmplwi r5, 0x0
    beq SoundMgr_Play_L_801929A0
    li r3, 0x1
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_801929A0:
    lis r7, ClSound_InitSoundSystem_bss_80677F40@ha
    li r5, 0x25
    addi r10, r7, ClSound_InitSoundSystem_bss_80677F40@l
    lwz r7, 0x4(r9)
    li r12, 0x0
    mtctr r5
    SoundMgr_Play_L_801929B8:
    lwz r9, 0x0(r10)
    addis r5, r9, 0x1
    cmplwi r5, 0xffff
    beq SoundMgr_Play_L_80192A6C
    cmplw r7, r9
    bne SoundMgr_Play_L_80192A60
    mulli r9, r12, 0xc
    lis r5, ClSound_InitSoundSystem_bss_80677F40@ha
    li r7, 0x3
    addi r11, r5, ClSound_InitSoundSystem_bss_80677F40@l
    add r30, r11, r9
    li r5, 0x0
    stw r7, 0x4(r30)
    stw r5, 0x8(r30)
    mtctr r12
    cmpwi r12, 0x0
    ble SoundMgr_Play_L_80192A6C
    SoundMgr_Play_L_801929FC:
    lwz r5, -0x8(r30)
    cmpwi r5, 0x3
    beq SoundMgr_Play_L_80192A6C
    subi r5, r12, 0x1
    lwz r10, 0x0(r30)
    mulli r5, r5, 0xc
    lwz r9, 0x4(r30)
    lwz r7, 0x8(r30)
    subi r12, r12, 0x1
    stw r10, 0x14(r1)
    add r31, r11, r5
    lwz r5, 0x0(r31)
    stw r9, 0x18(r1)
    stw r5, 0x0(r30)
    lwz r5, 0x4(r31)
    stw r7, 0x1c(r1)
    stw r5, 0x4(r30)
    lwz r5, 0x8(r31)
    stw r5, 0x8(r30)
    subi r30, r30, 0xc
    stw r10, 0x0(r31)
    stw r9, 0x4(r31)
    stw r7, 0x8(r31)
    bdnz SoundMgr_Play_L_801929FC
    b SoundMgr_Play_L_80192A6C
    SoundMgr_Play_L_80192A60:
    addi r10, r10, 0xc
    addi r12, r12, 0x1
    bdnz SoundMgr_Play_L_801929B8
    SoundMgr_Play_L_80192A6C:
    lis r5, ClSound_InitSoundSystem_bss_80678378@ha
    addi r7, r5, ClSound_InitSoundSystem_bss_80678378@l
    lwzx r5, r7, r0
    rlwinm r5, r5, 0, 31, 28
    ori r5, r5, 0x4
    stwx r5, r7, r0
    SoundMgr_Play_L_80192A84:
    mulli r0, r4, 0x1c
    lis r4, lbl_80379554@ha
    addi r4, r4, lbl_80379554@l
    add r5, r4, r0
    lbz r4, 0x5(r5)
    cmplwi r4, 0x2
    bne SoundMgr_Play_L_80192BCC
    mr r4, r6
    addi r5, r5, 0x4
    li r7, 0x0
    SoundMgr_Play_L_80192AAC:
    lwz r11, 0x4(r4)
    addis r9, r11, 0x1
    cmplwi r9, 0xffff
    beq SoundMgr_Play_L_80192BBC
    lbz r10, 0x8(r4)
    lbz r9, 0x0(r5)
    cmplw r10, r9
    bne SoundMgr_Play_L_80192BBC
    rlwinm r9, r11, 0, 1, 4
    cmplw r8, r9
    bne SoundMgr_Play_L_80192BBC
    lwz r9, 0x0(r4)
    rlwinm. r9, r9, 0, 29, 30
    bne SoundMgr_Play_L_80192BBC
    lis r10, ClSound_InitSoundSystem_bss_80677F40@ha
    li r9, 0x25
    addi r10, r10, ClSound_InitSoundSystem_bss_80677F40@l
    li r30, 0x0
    mtctr r9
    SoundMgr_Play_L_80192AF8:
    lwz r12, 0x0(r10)
    addis r9, r12, 0x1
    cmplwi r9, 0xffff
    beq SoundMgr_Play_L_80192BAC
    cmplw r11, r12
    bne SoundMgr_Play_L_80192BA0
    mulli r10, r30, 0xc
    lis r9, ClSound_InitSoundSystem_bss_80677F40@ha
    li r11, 0x3
    addi r31, r9, ClSound_InitSoundSystem_bss_80677F40@l
    add r29, r31, r10
    li r9, 0x0
    stw r11, 0x4(r29)
    stw r9, 0x8(r29)
    mtctr r30
    cmpwi r30, 0x0
    ble SoundMgr_Play_L_80192BAC
    SoundMgr_Play_L_80192B3C:
    lwz r9, -0x8(r29)
    cmpwi r9, 0x3
    beq SoundMgr_Play_L_80192BAC
    subi r9, r30, 0x1
    lwz r12, 0x0(r29)
    mulli r9, r9, 0xc
    lwz r11, 0x4(r29)
    lwz r10, 0x8(r29)
    subi r30, r30, 0x1
    stw r12, 0x8(r1)
    add r28, r31, r9
    lwz r9, 0x0(r28)
    stw r11, 0xc(r1)
    stw r9, 0x0(r29)
    lwz r9, 0x4(r28)
    stw r10, 0x10(r1)
    stw r9, 0x4(r29)
    lwz r9, 0x8(r28)
    stw r9, 0x8(r29)
    subi r29, r29, 0xc
    stw r12, 0x0(r28)
    stw r11, 0x4(r28)
    stw r10, 0x8(r28)
    bdnz SoundMgr_Play_L_80192B3C
    b SoundMgr_Play_L_80192BAC
    SoundMgr_Play_L_80192BA0:
    addi r10, r10, 0xc
    addi r30, r30, 0x1
    bdnz SoundMgr_Play_L_80192AF8
    SoundMgr_Play_L_80192BAC:
    lwz r9, 0x0(r4)
    rlwinm r9, r9, 0, 31, 28
    ori r9, r9, 0x4
    stw r9, 0x0(r4)
    SoundMgr_Play_L_80192BBC:
    addi r7, r7, 0x1
    addi r4, r4, 0x1c
    cmpwi r7, 0x20
    blt SoundMgr_Play_L_80192AAC
    SoundMgr_Play_L_80192BCC:
    li r4, 0x4
    li r7, 0x0
    mtctr r4
    SoundMgr_Play_L_80192BD8:
    lwz r4, 0x0(r6)
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    addi r6, r6, 0x1c
    addi r7, r7, 0x1
    bdnz SoundMgr_Play_L_80192BD8
    SoundMgr_Play_L_80192C7C:
    cmpwi r7, 0x20
    blt SoundMgr_Play_L_80192C8C
    li r3, 0x0
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_80192C8C:
    lis r5, lbl_80379554@ha
    lis r4, ClSound_InitSoundSystem_bss_80678378@ha
    addi r6, r5, lbl_80379554@l
    li r8, -0x1
    add r12, r6, r0
    addi r11, r4, ClSound_InitSoundSystem_bss_80678378@l
    lwz r0, 0x18(r12)
    mulli r28, r7, 0x1c
    li r5, 0x200
    lbz r10, 0x4(r12)
    extrwi r0, r0, 1, 30
    lbz r9, 0x15(r12)
    neg r0, r0
    andc r0, r5, r0
    add r29, r11, r28
    ori r0, r0, 0x11
    li r7, 0x80
    stwx r0, r11, r28
    li r6, 0x7f
    li r5, 0x40
    lhz r4, 0x12(r12)
    stw r3, 0x4(r29)
    li r3, 0x2000
    lbz r0, 0x14(r12)
    stb r10, 0x8(r29)
    stb r9, 0x18(r29)
    stw r8, 0xc(r29)
    stb r7, 0x10(r29)
    stb r6, 0x11(r29)
    stb r5, 0x12(r29)
    stb r5, 0x13(r29)
    sth r4, 0x14(r29)
    sth r3, 0x16(r29)
    stb r0, 0x19(r29)
    lhz r0, 0x14(r29)
    addi r29, r29, 0x4
    cmplwi r0, 0x2000
    beq SoundMgr_Play_L_80192D30
    lwzx r0, r11, r28
    ori r0, r0, 0x80
    stwx r0, r11, r28
    SoundMgr_Play_L_80192D30:
    lis r3, ClSound_InitSoundSystem_bss_80677F40@ha
    li r0, 0x25
    addi r3, r3, ClSound_InitSoundSystem_bss_80677F40@l
    lwz r8, 0x0(r29)
    li r9, 0x0
    mr r4, r3
    mtctr r0
    SoundMgr_Play_L_80192D4C:
    lwz r5, 0x0(r4)
    addis r0, r5, 0x1
    cmplwi r0, 0xffff
    bne SoundMgr_Play_L_80192D64
    li r9, -0x1
    b SoundMgr_Play_L_80192D80
    SoundMgr_Play_L_80192D64:
    cmplw r8, r5
    bne SoundMgr_Play_L_80192D70
    b SoundMgr_Play_L_80192D80
    SoundMgr_Play_L_80192D70:
    addi r4, r4, 0xc
    addi r9, r9, 0x1
    bdnz SoundMgr_Play_L_80192D4C
    li r9, -0x1
    SoundMgr_Play_L_80192D80:
    cmpwi r9, 0x0
    blt SoundMgr_Play_L_80192E98
    mulli r0, r9, 0xc
    lis r4, ClSound_InitSoundSystem_bss_80677F40@ha
    cmpwi r9, 0x24
    addi r7, r4, ClSound_InitSoundSystem_bss_80677F40@l
    subfic r4, r9, 0x24
    add r11, r7, r0
    bge SoundMgr_Play_L_80192E88
    srwi. r0, r4, 2
    mtctr r0
    beq SoundMgr_Play_L_80192E54
    SoundMgr_Play_L_80192DB0:
    addi r6, r9, 0x1
    mulli r5, r6, 0xc
    addi r6, r9, 0x2
    add r10, r7, r5
    lwz r0, 0x0(r10)
    mulli r5, r6, 0xc
    addi r6, r9, 0x3
    stw r0, 0x0(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x4(r11)
    lwz r0, 0x8(r10)
    add r10, r7, r5
    mulli r5, r6, 0xc
    addi r6, r9, 0x4
    stw r0, 0x8(r11)
    addi r9, r9, 0x4
    lwz r0, 0x0(r10)
    stw r0, 0xc(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x10(r11)
    lwz r0, 0x8(r10)
    add r10, r7, r5
    mulli r5, r6, 0xc
    stw r0, 0x14(r11)
    lwz r0, 0x0(r10)
    stw r0, 0x18(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x1c(r11)
    lwz r0, 0x8(r10)
    add r10, r7, r5
    stw r0, 0x20(r11)
    lwz r0, 0x0(r10)
    stw r0, 0x24(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x28(r11)
    lwz r0, 0x8(r10)
    stw r0, 0x2c(r11)
    addi r11, r11, 0x30
    bdnz SoundMgr_Play_L_80192DB0
    andi. r4, r4, 0x3
    beq SoundMgr_Play_L_80192E88
    SoundMgr_Play_L_80192E54:
    mtctr r4
    SoundMgr_Play_L_80192E58:
    addi r6, r9, 0x1
    addi r9, r9, 0x1
    mulli r5, r6, 0xc
    add r10, r7, r5
    lwz r0, 0x0(r10)
    stw r0, 0x0(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x4(r11)
    lwz r0, 0x8(r10)
    stw r0, 0x8(r11)
    addi r11, r11, 0xc
    bdnz SoundMgr_Play_L_80192E58
    SoundMgr_Play_L_80192E88:
    lis r4, ClSound_InitSoundSystem_bss_80677F40@ha
    li r0, -0x1
    addi r4, r4, ClSound_InitSoundSystem_bss_80677F40@l
    stw r0, 0x1b0(r4)
    SoundMgr_Play_L_80192E98:
    li r0, 0x25
    li r5, 0x0
    mtctr r0
    SoundMgr_Play_L_80192EA4:
    lwz r4, 0x0(r3)
    addis r0, r4, 0x1
    cmplwi r0, 0xffff
    bne SoundMgr_Play_L_80192EDC
    mulli r0, r5, 0xc
    lis r3, ClSound_InitSoundSystem_bss_80677F40@ha
    li r4, 0x1
    addi r3, r3, ClSound_InitSoundSystem_bss_80677F40@l
    stwx r8, r3, r0
    add r3, r3, r0
    li r0, 0xa
    stw r4, 0x4(r3)
    stw r0, 0x8(r3)
    b SoundMgr_Play_L_80192EE8
    SoundMgr_Play_L_80192EDC:
    addi r3, r3, 0xc
    addi r5, r5, 0x1
    bdnz SoundMgr_Play_L_80192EA4
    SoundMgr_Play_L_80192EE8:
    li r3, 0x1
    SoundMgr_Play_L_80192EEC:
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    addi r1, r1, 0x30
    blr
}
#endif
#pragma exceptions reset
#undef ClSound_Initialized
#undef lbl_80379554
#undef ClSound_InitSoundSystem_bss_80677F40
#undef ClSound_InitSoundSystem_bss_80678378

/* ==== game/clsound/fn_80192F04.c (0x80192F04) ==== */
#define CObj_GetViewMatrix_Cached CObj_GetViewMatrix_Cached_p18
#define CObj_LoadProjMatrix CObj_LoadProjMatrix_p18
#define GetCourseScene3D GetCourseScene3D_p18
#define Sci2Card_GetByteFlag1224 Sci2Card_GetByteFlag1224_p18
#define g_playerData g_playerData_p18
#define lbl_806D16C0 lbl_806D16C0_p18
#pragma exceptions on
/* 0x80192F04..0x801933D0: listener-relative volume/pan, the per-voice attribute
 * refresh, the weather variant picker and the fog/listener basis update. The
 * unit owns the listener vectors (.data 0x80495F20..0x80495F48). */



int fn_80192F04(unsigned int id, const ClSoundVec* position, unsigned char* volume, unsigned char* pan, unsigned char* surround) {
    ClSoundVec delta;
    float near_distance, far_distance, distance;
    if (!ClSound_Initialized) return 0;
    if (!position) return 0;
    id &= ~0x78000000;
    if (id >= 490) return 0;
    near_distance = lbl_80379554[id].near_distance;
    far_distance = lbl_80379554[id].far_distance;
    Vec3_Subtract(position, &lbl_80495F38.pos, &delta);
    distance = Vec3_Magnitude(&delta);
    if (distance >= far_distance) {
        if (volume) *volume = 0;
        if (pan) *pan = 64;
        if (surround) *surround = 64;
    } else {
        if (volume) {
            if (distance <= near_distance) *volume = 127;
            else *volume = (int)(lbl_806D9514 - lbl_806D9514 * ((distance-near_distance)/(far_distance-near_distance)));
        }
        if (pan) {
            distance = Vec3_Dot(&delta, &lbl_80495F20);
            if (distance >= near_distance) *pan = 0;
            else if (distance <= -near_distance) *pan = 127;
            else *pan = (int)(lbl_806D9518 - lbl_806D951C*(distance/near_distance));
        }
        if (surround) {
            distance = Vec3_Dot(&delta, &lbl_80495F2C);
            if (distance >= near_distance) *surround = 127;
            else if (distance <= -near_distance) *surround = 0;
            else *surround = (int)(lbl_806D9518 + lbl_806D951C*(distance/near_distance));
        }
    }
    return 1;
}

extern unsigned char lbl_806D16C0;

#pragma exceptions off
void fn_80193134(unsigned char v) {
    int i;
    if (lbl_806D16C0 == v) {
        return;
    }
    lbl_806D16C0 = v;
    for (i = 0; i < 32; i++) {
        if (ClSound_InitSoundSystem_bss_80678378[i].id != -1) {
            ClSound_InitSoundSystem_bss_80678378[i].flags |= (lbl_80379554[ClSound_InitSoundSystem_bss_80678378[i].id & ~0x78000000].attributes & 2) ? 0 : 0x200;
        }
    }
}
#pragma exceptions reset

/* WeatherSystem_PickVariant: forced id -1 consults the card flag and the
 * player data, 0..4 pick clear/cloudy/overcast/rain/thunder. */
extern unsigned char Sci2Card_GetByteFlag1224(void);
extern unsigned char g_playerData[0x1DC];

#pragma exceptions on
unsigned char WeatherSystem_PickVariant(int forcedId) {
    if (forcedId < 0) {
        if ((Sci2Card_GetByteFlag1224() & 0xFF) == 0) {
            return 0x5F;
        }
        forcedId = g_playerData[0xC];
    }
    switch (forcedId) {
    case 0:
        return 0x00;
    case 1:
        return 0x50;
    case 3:
        return 0x73;
    case 4:
        return 0x7F;
    case 2:
    default:
        return 0x5F;
    }
}
#pragma exceptions reset

#pragma exceptions off
int fn_801932F8(void) {
    return 90;
}
#pragma exceptions reset

extern void *GetCourseScene3D(void);
extern float *CObj_GetViewMatrix_Cached(void *cobj);
extern void CObj_LoadProjMatrix(void *cobj, ClSoundVec *pos);
void Fog_UpdateFromCourseScene3D(void) {
    if (GetCourseScene3D()) {
        float *m = CObj_GetViewMatrix_Cached(GetCourseScene3D());
        lbl_80495F20.x = m[0];
        lbl_80495F20.y = m[4];
        lbl_80495F20.z = m[8];
        lbl_80495F2C.x = m[2];
        lbl_80495F2C.y = m[6];
        lbl_80495F2C.z = m[10];
        CObj_LoadProjMatrix(GetCourseScene3D(), &lbl_80495F38.pos);
        lbl_80495F38.pos.x += 50.0f * lbl_80495F2C.x;
        lbl_80495F38.pos.y += 50.0f * lbl_80495F2C.y;
        lbl_80495F38.pos.z += 50.0f * lbl_80495F2C.z;
    }
}
#pragma exceptions reset
#undef CObj_GetViewMatrix_Cached
#undef CObj_LoadProjMatrix
#undef GetCourseScene3D
#undef Sci2Card_GetByteFlag1224
#undef g_playerData
#undef lbl_806D16C0

