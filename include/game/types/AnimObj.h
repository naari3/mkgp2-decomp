#ifndef GAME_TYPES_ANIMOBJ_H
#define GAME_TYPES_ANIMOBJ_H

#include "game/types/Vec3f.h"

struct AnimDef;
struct HSD_JObj;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct AnimObj AnimObj;
struct AnimObj {
    /* 0x000 */ void *next;
    /* 0x004 */ struct AnimDef *def;
    /* 0x008 */ struct HSD_JObj *jobj;
    /* 0x00C */ float frame;
    /* 0x010 */ Vec3f offset;
    /* 0x01C */ unsigned char pad_01C[0x4];
    /* 0x020 */ float y;
};

#endif /* GAME_TYPES_ANIMOBJ_H */
