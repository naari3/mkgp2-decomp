#ifndef GAME_TYPES_SPRITELIST_H
#define GAME_TYPES_SPRITELIST_H

struct SpriteNode;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpriteList SpriteList;
struct SpriteList {
    /* 0x000 */ unsigned char pad_000[0x14];
    /* 0x014 */ struct SpriteNode *head;
};

#endif /* GAME_TYPES_SPRITELIST_H */
