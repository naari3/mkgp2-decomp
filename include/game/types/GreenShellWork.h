#ifndef GAME_TYPES_GREENSHELLWORK_H
#define GAME_TYPES_GREENSHELLWORK_H

#include "game/types/Vec.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GreenShellWork GreenShellWork;
struct GreenShellWork {
    /* 0x000 */ unsigned char bounces;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ unsigned int timers[4];
    /* 0x014 */ float groundY;
    /* 0x018 */ float spin;
    /* 0x01C */ float phase;
    /* 0x020 */ unsigned char pad_020[0x10];
    /* 0x030 */ int seCh;
    /* 0x034 */ Vec launchPos;
    /* 0x040 */ Vec rebound;
    /* 0x04C */ unsigned char *eff;
    /* 0x050 */ unsigned char *spark;
    /* 0x054 */ unsigned char pad_054[0x8];
    /* 0x05C */ void *gabyou;
    /* 0x060 */ unsigned char pad_060[0x34];
    /* 0x094 */ void *owner;
    /* 0x098 */ void *driver;
    /* 0x09C */ void *target;
    /* 0x0A0 */ signed char launch;
    /* 0x0A1 */ unsigned char pad_0A1[0x4F];
    /* 0x0F0 */ unsigned char shellColor;
    /* 0x0F1 */ unsigned char pad_0F1[0x3];
    /* 0x0F4 */ int shellTimer;
};

#endif /* GAME_TYPES_GREENSHELLWORK_H */
