#ifndef GAME_TYPES_DOSSUNWORK_H
#define GAME_TYPES_DOSSUNWORK_H

#include "game/types/Vec.h"

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DossunWork DossunWork;
struct DossunWork {
    /* 0x000 */ unsigned char landed;
    /* 0x001 */ unsigned char hitKart;
    /* 0x002 */ unsigned char stopped;
    /* 0x003 */ unsigned char buildMtx;
    /* 0x004 */ unsigned int timers[4];
    /* 0x014 */ float groundY;  /* also: tether */
    /* 0x018 */ float tetherScale;  /* also: spinDir, yaw */
    /* 0x01C */ unsigned char pad_01C[0x74];
    /* 0x090 */ unsigned char active;
    /* 0x091 */ unsigned char pad_091[0x7];
    /* 0x098 */ void *driver;
    /* 0x09C */ void *target;
    /* 0x0A0 */ signed char launch;
    /* 0x0A1 */ unsigned char pad_0A1[0x3];
    /* 0x0A4 */ Vec dir;
};

#endif /* GAME_TYPES_DOSSUNWORK_H */
