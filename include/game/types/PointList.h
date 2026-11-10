#ifndef GAME_TYPES_POINTLIST_H
#define GAME_TYPES_POINTLIST_H

struct Vec;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PointList PointList;
struct PointList {
    /* 0x000 */ int count;
    /* 0x004 */ struct Vec *pts;
};

#endif /* GAME_TYPES_POINTLIST_H */
