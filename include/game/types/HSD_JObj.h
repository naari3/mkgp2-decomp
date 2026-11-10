#ifndef GAME_TYPES_HSD_JOBJ_H
#define GAME_TYPES_HSD_JOBJ_H

#include "game/types/Quat.h"
#include "game/types/Vec3.h"

struct Vec3;

/* Merged from 38 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HSD_JObj HSD_JObj;
struct HSD_JObj {
    /* 0x000 */ unsigned char pad_000[0x8];
    /* 0x008 */ struct HSD_JObj *next;
    /* 0x00C */ struct HSD_JObj *parent;
    /* 0x010 */ struct HSD_JObj *child;
    /* 0x014 */ unsigned int flags;
    /* 0x018 */ void *dobj;
    /* 0x01C */ Quat rotate;
    /* 0x02C */ Vec3 scale;
    /* 0x038 */ Vec3 translate;
    /* 0x044 */ float mtx[3][4];
    /* 0x074 */ struct Vec3 *scl;
    /* 0x078 */ void *envelopemtx;
    /* 0x07C */ void *aobj;
    /* 0x080 */ void *robj;
    /* 0x084 */ void *desc;
};

#endif /* GAME_TYPES_HSD_JOBJ_H */
