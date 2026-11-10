#ifndef GAME_TYPES_SUIKABALL_H
#define GAME_TYPES_SUIKABALL_H

#include "game/types/Vec3.h"

struct Deletable;
struct Destroyable;
struct Gate;
struct GateList;
struct HsdRefObj;
struct SuikaBallObj;
struct SuikaSlot;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SuikaBall SuikaBall;
struct SuikaBall {
    /* 0x000 */ void *vtable;
    /* 0x004 */ unsigned char pad_004[0x8];
    /* 0x00C */ struct Destroyable *car;
    /* 0x010 */ void *lakitu;
    /* 0x014 */ void *environment;
    /* 0x018 */ struct Deletable *m18;
    /* 0x01C */ void *m1C;
    /* 0x020 */ struct Deletable *m20;
    /* 0x024 */ struct HsdRefObj *m24;
    /* 0x028 */ unsigned char pad_028[0x4];
    /* 0x02C */ void *hud;
    /* 0x030 */ unsigned char active;
    /* 0x031 */ unsigned char bgmOn;
    /* 0x032 */ unsigned char finished;
    /* 0x033 */ unsigned char goalReached;
    /* 0x034 */ int state;
    /* 0x038 */ unsigned char pad_038[0x4];
    /* 0x03C */ struct SuikaBallObj *m3C;
    /* 0x040 */ struct Gate *m40;
    /* 0x044 */ struct Deletable *m44;
    /* 0x048 */ struct Deletable *m48;
    /* 0x04C */ float speedScale;
    /* 0x050 */ Vec3 prevPos;
    /* 0x05C */ struct SuikaSlot *slots;
    /* 0x060 */ struct Deletable *m60;
    /* 0x064 */ struct GateList *bufs;
    /* 0x068 */ int coins;
};

#endif /* GAME_TYPES_SUIKABALL_H */
