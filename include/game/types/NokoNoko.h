#ifndef GAME_TYPES_NOKONOKO_H
#define GAME_TYPES_NOKONOKO_H

#include "game/types/Vec.h"

/* Merged from 7 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct NokoNoko NokoNoko;
struct NokoNoko {
    /* 0x000 */ struct NokoNoko *next;
    /* 0x004 */ int kindTable;
    /* 0x008 */ int kindIndex;
    /* 0x00C */ int state;  /* also: model */
    /* 0x010 */ int model;  /* also: anim, speed */
    /* 0x014 */ float frame;
    /* 0x018 */ int timer;  /* also: extra, owner_id */
    /* 0x01C */ Vec pos;
    /* 0x028 */ float yaw;
    /* 0x02C */ float speed;  /* also: t1 */
    /* 0x030 */ float radius;  /* also: t2, turn */
    /* 0x034 */ int model2;
    /* 0x038 */ float blend;
    /* 0x03C */ float frame2;
};

#endif /* GAME_TYPES_NOKONOKO_H */
