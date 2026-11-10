#ifndef GAME_TYPES_KUPPASHELLWORK_H
#define GAME_TYPES_KUPPASHELLWORK_H

#include "game/types/Vec.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KuppaShellWork KuppaShellWork;
struct KuppaShellWork {
    /* 0x000 */ unsigned char bounces;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ unsigned int timers[4];
    /* 0x014 */ float tether;
    /* 0x018 */ float tetherScale;
    /* 0x01C */ unsigned char pad_01C[0x14];
    /* 0x030 */ int seCh;
    /* 0x034 */ Vec launchPos;
    /* 0x040 */ unsigned char pad_040[0x58];
    /* 0x098 */ void *driver;
    /* 0x09C */ void *target;
    /* 0x0A0 */ signed char launch;
    /* 0x0A1 */ unsigned char pad_0A1[0x3];
};

#endif /* GAME_TYPES_KUPPASHELLWORK_H */
