#ifndef GAME_TYPES_HANDHELDPOSE_H
#define GAME_TYPES_HANDHELDPOSE_H

#include "game/types/Vec.h"

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HandheldPose HandheldPose;
struct HandheldPose {
    /* 0x000 */ signed char onKart;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ float scale;
    /* 0x008 */ Vec ofs;
    /* 0x014 */ Vec rot;
};

#endif /* GAME_TYPES_HANDHELDPOSE_H */
