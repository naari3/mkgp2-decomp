#ifndef GAME_TYPES_SHAREDEFFECT_H
#define GAME_TYPES_SHAREDEFFECT_H

#include "game/types/EffectSlot.h"

struct EffectObj;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SharedEffect SharedEffect;
struct SharedEffect {
    /* 0x000 */ struct EffectObj *objs[2];
    /* 0x008 */ EffectSlot slots[4];
};

#endif /* GAME_TYPES_SHAREDEFFECT_H */
