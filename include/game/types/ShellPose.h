#ifndef GAME_TYPES_SHELLPOSE_H
#define GAME_TYPES_SHELLPOSE_H

#include "game/types/Vec.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ShellPose ShellPose;
struct ShellPose {
    /* 0x000 */ int anim;
    /* 0x004 */ int se;
    /* 0x008 */ float scale;
    /* 0x00C */ Vec near;
    /* 0x018 */ Vec rot;
    /* 0x024 */ unsigned char pad_024[0xC];
    /* 0x030 */ Vec far;
    /* 0x03C */ unsigned char pad_03C[0xC];
};

#endif /* GAME_TYPES_SHELLPOSE_H */
