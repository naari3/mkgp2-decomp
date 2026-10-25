#ifndef GAME_DRAWEFFECTPOOL_H
#define GAME_DRAWEFFECTPOOL_H

/* DrawEffect pool entry (0x1CC bytes, 0x200 entries at lbl_805DF468).
 * Narrow target-observed layout. */
typedef struct DrawEffectVec3 {
    float x, y, z;
} DrawEffectVec3;

typedef struct DrawEffect {
    signed char active;            /* 0x000 */
    unsigned char pad001[3];
    void *callback;                /* 0x004 */
    int type;                      /* 0x008 */
    unsigned char pad00c[4];
    int variant;                   /* 0x010 */
    unsigned char slot[0x14];      /* 0x014 VfxSlot */
    unsigned char visible;         /* 0x028 */
    unsigned char pad029[0x8C - 0x29];
    DrawEffectVec3 pos;            /* 0x08C */
    unsigned char pad098[4];
    float yaw;                     /* 0x09C */
    unsigned char pad0a0[0xB0 - 0xA0];
    float scale;                   /* 0x0B0 */
    signed char state;             /* 0x0B4 */
    unsigned char pad0b5[0x1CC - 0xB5];
} DrawEffect;

extern DrawEffect lbl_805DF468[0x200];
extern void *memset(void *, int, unsigned long);

static inline int DrawEffect_AllocSlot(void)
{
    DrawEffect *e;
    int i;
    for (i = 0; i < 0x200; i++) {
        if (lbl_805DF468[i].active == 0) {
            e = &lbl_805DF468[i];
            memset(e, 0, sizeof(DrawEffect));
            e->active = 1;
            return i;
        }
    }
    return -1;
}

static inline DrawEffect *DrawEffect_SpawnInline(void *callback)
{
    int i;
    DrawEffect *e;

    if (callback == 0) {
        return 0;
    }
    i = DrawEffect_AllocSlot();
    if (i < 0) {
        return 0;
    }
    e = &lbl_805DF468[i];
    e->callback = callback;
    return e;
}

#endif
