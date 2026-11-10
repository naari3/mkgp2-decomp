#ifndef GAME_TYPES_ENRAKUWORK_H
#define GAME_TYPES_ENRAKUWORK_H

#include "game/types/Vec.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct EnrakuWork EnrakuWork;
struct EnrakuWork {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ unsigned int timers[4];
    /* 0x014 */ float tether;
    /* 0x018 */ float tetherScale;
    /* 0x01C */ unsigned char pad_01C[0x18];
    /* 0x034 */ Vec anchor;
    /* 0x040 */ unsigned char pad_040[0xC];
    /* 0x04C */ unsigned char *eff;
    /* 0x050 */ unsigned char pad_050[0x2C];
    /* 0x07C */ int approach;
    /* 0x080 */ unsigned char pad_080[0x14];
    /* 0x094 */ void *owner;
    /* 0x098 */ void *driver;
    /* 0x09C */ void *target;
    /* 0x0A0 */ signed char launch;
    /* 0x0A1 */ unsigned char pad_0A1[0x4F];
    /* 0x0F0 */ unsigned char shellColor;
    /* 0x0F1 */ unsigned char pad_0F1[0x3];
    /* 0x0F4 */ int shellTimer;
};

#endif /* GAME_TYPES_ENRAKUWORK_H */
