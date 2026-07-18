/*
 * TripleBladeRing (0x800B3C8C..0x800B4164) shared definitions.
 *
 * Rotating 6-blade ring item effect (triple-banana style orbit ring).
 * 4 functions, each its own single-fn reversed extab group, split into
 * 3 TUs (SetWorldYaw is NonMatching-parked, see its TU header):
 *   TripleBladeRing_Draw        0x800B3C8C size:0x1AC (extab 0x8000A6A0, eti 0x80022B74)
 *   TripleBladeRing_DrawCb      0x800B3E38 size:0x9C  (extab 0x8000A6A8, eti 0x80022B80)
 *   TripleBladeRing_SetWorldYaw 0x800B3ED4 size:0x1C0 (extab 0x8000A6B0, eti 0x80022B8C)
 *   TripleBladeRing_Update      0x800B4094 size:0xD0  (extab 0x8000A6B8, eti 0x80022B98)
 *
 * All TUs build with -Cpp_exceptions on (CW auto-emits extab/extabindex
 * per fn; emit order = fn address order = target layout).
 *
 * Field offsets from Ghidra decompile (typed accesses verified by
 * byte-identical rebuild of Draw/DrawCb/Update).
 */
#ifndef GAME_TRIPLEBLADERING_H
#define GAME_TRIPLEBLADERING_H

typedef struct TBRVec3 {
    float x;
    float y;
    float z;
} TBRVec3;

typedef struct TripleBladeRing TripleBladeRing;

/* Child draw-effect actor (only the fields these TUs touch). */
typedef struct DrawEffectActor {
    unsigned char _pad00[0x14];
    unsigned char bindSlot[4];  /* +0x14: passed to VfxSlot_BindResource */
    void *wrapSlot;             /* +0x18: cLNormal3DWrap slot instance */
    unsigned char _pad1C[0x28 - 0x1C];
    unsigned char flag28;       /* +0x28 */
} DrawEffectActor;

struct TripleBladeRing {
    unsigned char _pad00[0x2C];
    float angle;                            /* 0x2C: world yaw written by SetWorldYaw */
    unsigned char _pad30[0x78 - 0x30];
    void (*drawFn)(TripleBladeRing *self);  /* 0x78 */
    TripleBladeRing *drawArg;               /* 0x7C */
    unsigned char _pad80[0x8C - 0x80];
    TBRVec3 pos;                            /* 0x8C: world position */
    unsigned char _pad98[0xB4 - 0x98];
    char initFlag;                          /* 0xB4 */
    unsigned char _padB5[0xC9 - 0xB5];
    char termFlag;                          /* 0xC9 */
    unsigned char _padCA[0xCC - 0xCA];
    DrawEffectActor *slotA;                 /* 0xCC: child draw-effect actor A */
    DrawEffectActor *slotB;                 /* 0xD0: child draw-effect actor B */
    float phase0;                           /* 0xD4: master phase */
    float phaseSin;                         /* 0xD8: sin-shaped phase */
    float phases[3];                        /* 0xDC..0xE4: per-arm blade phases */
    float mtx[16];                          /* 0xE8: world matrix (4x4) */
};

/* Sub-view of the fields from +0xCC, used by Draw via a base pointer. */
typedef struct TripleBladeRingFx {
    DrawEffectActor *slotA; /* +0x00 (self+0xCC) */
    DrawEffectActor *slotB; /* +0x04 */
    float phase0;           /* +0x08 */
    float phaseSin;         /* +0x0C */
    float phases[3];        /* +0x10 */
    float mtx[16];          /* +0x1C (self+0xE8) */
} TripleBladeRingFx;

void TripleBladeRing_Draw(TripleBladeRing *self);
void TripleBladeRing_DrawCb(TripleBladeRing *self);
void TripleBladeRing_SetWorldYaw(TripleBladeRing *self, float yaw, void *worldMtx);
void TripleBladeRing_Update(TripleBladeRing *self);

#endif /* GAME_TRIPLEBLADERING_H */
