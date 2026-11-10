#ifndef GAME_TYPES_GRIDCELL_H
#define GAME_TYPES_GRIDCELL_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GridCell GridCell;
struct GridCell {
    /* 0x000 */ float x;
    /* 0x004 */ float y;
    /* 0x008 */ float z;
    /* 0x00C */ float w;
    /* 0x010 */ int x10;
    /* 0x014 */ int x14;
    /* 0x018 */ unsigned char slots[80];
};

#endif /* GAME_TYPES_GRIDCELL_H */
