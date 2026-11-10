#ifndef GAME_TYPES_SPRITENODEINFO_H
#define GAME_TYPES_SPRITENODEINFO_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpriteNodeInfo SpriteNodeInfo;
struct SpriteNodeInfo {
    /* 0x000 */ float x;
    /* 0x004 */ float y;
    /* 0x008 */ char rest[0x28];
};

#endif /* GAME_TYPES_SPRITENODEINFO_H */
