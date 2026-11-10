#ifndef GAME_TYPES_HITEFFECT_H
#define GAME_TYPES_HITEFFECT_H

#include "game/types/Vec3.h"

struct HitItem;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HitEffect HitEffect;
struct HitEffect {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ int kind;
    /* 0x014 */ unsigned char slot[0x14];
    /* 0x028 */ unsigned char visible;
    /* 0x029 */ unsigned char pad_029[0x63];
    /* 0x08C */ Vec3 position;
    /* 0x098 */ unsigned char pad_098[0x8];
    /* 0x0A0 */ float yaw;
    /* 0x0A4 */ unsigned char velocity[12];
    /* 0x0B0 */ float scale;
    /* 0x0B4 */ signed char state;
    /* 0x0B5 */ unsigned char pad_0B5[0x17];
    /* 0x0CC */ struct HitItem *item;
    /* 0x0D0 */ unsigned char pad_0D0[0x4C];
    /* 0x11C */ void *target;
    /* 0x120 */ unsigned char previous[12];
    /* 0x12C */ unsigned char pad_12C[0x24];
    /* 0x150 */ float initialScale;
    /* 0x154 */ float fade;
    /* 0x158 */ float anisotropy;
    /* 0x15C */ float angularVelocity;
    /* 0x160 */ float trackedStep;
    /* 0x164 */ unsigned char pad_164[0x1C];
    /* 0x180 */ unsigned int timers[4];
    /* 0x190 */ signed char variant;
    /* 0x191 */ unsigned char pad_191[0x3];
};

#endif /* GAME_TYPES_HITEFFECT_H */
