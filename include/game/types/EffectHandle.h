#ifndef GAME_TYPES_EFFECTHANDLE_H
#define GAME_TYPES_EFFECTHANDLE_H

#include "game/types/Vec3f.h"

struct SharedRef;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct EffectHandle EffectHandle;
struct EffectHandle {
    /* 0x000 */ struct SharedRef *ref;
    /* 0x004 */ Vec3f anchor;
    /* 0x010 */ Vec3f cur;
    /* 0x01C */ float blend;
};

#endif /* GAME_TYPES_EFFECTHANDLE_H */
