#ifndef GAME_TYPES_SHAREDREF_H
#define GAME_TYPES_SHAREDREF_H

#include "game/types/RefSub.h"
#include "game/types/Vec3f.h"

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SharedRef SharedRef;
struct SharedRef {
    /* 0x000 */ int id;
    /* 0x004 */ float t;
    /* 0x008 */ unsigned char active;
    /* 0x009 */ unsigned char pad_009[0x3];
    /* 0x00C */ Vec3f pos;
    /* 0x018 */ RefSub subs[5];
};

#endif /* GAME_TYPES_SHAREDREF_H */
