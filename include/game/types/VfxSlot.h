#ifndef GAME_TYPES_VFXSLOT_H
#define GAME_TYPES_VFXSLOT_H

#include "game/types/Vec.h"

/* Merged from 14 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct VfxSlot VfxSlot;
struct VfxSlot {
    /* 0x000 */ unsigned char active;  /* also: flags */
    /* 0x001 */ unsigned char kind;
    /* 0x002 */ unsigned char pad_002[0x2];
    /* 0x004 */ void *slot;  /* also: effect, model */
    /* 0x008 */ signed char resource;
    /* 0x009 */ unsigned char pad_009[0x1];
    /* 0x00A */ unsigned char animDone;  /* also: playing */
    /* 0x00B */ unsigned char pad_00B[0x1];
    /* 0x00C */ float animFrame;  /* also: frame */
    /* 0x010 */ float scale;  /* also: speed */
    /* 0x014 */ unsigned char visible;
    /* 0x015 */ unsigned char pad_015[0x3];
    /* 0x018 */ float alpha;
    /* 0x01C */ float pos[3];
    /* 0x028 */ unsigned char pad_028[0x4];
    /* 0x02C */ float uvScroll[2];
    /* 0x034 */ float mtx[3][4];
    /* 0x064 */ void (*draw) (struct VfxSlot *self);
    /* 0x068 */ unsigned char pad_068[0x4];
    /* 0x06C */ Vec fixedPos;
};

#endif /* GAME_TYPES_VFXSLOT_H */
