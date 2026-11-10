#ifndef GAME_TYPES_ANIMSTATE_H
#define GAME_TYPES_ANIMSTATE_H

#include "game/types/AnimVec3.h"

struct AnimEntry;

/* Merged from 4 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct AnimState AnimState;
struct AnimState {
    /* 0x000 */ struct AnimEntry *entries;
    /* 0x004 */ int value4;
    /* 0x008 */ float timer[8];  /* also: time */
    /* 0x028 */ float weight;  /* also: speed */
    /* 0x02C */ signed char keyCount[8];
    /* 0x034 */ signed char lastKey[8];
    /* 0x03C */ signed char timerOn[8];  /* also: state */
    /* 0x044 */ int current;
    /* 0x048 */ AnimVec3 pos[4];  /* also: a */
    /* 0x078 */ AnimVec3 rot[4];  /* also: b */
    /* 0x0A8 */ AnimVec3 scale[4];  /* also: c */
    /* 0x0D8 */ float d[8];
};

#endif /* GAME_TYPES_ANIMSTATE_H */
