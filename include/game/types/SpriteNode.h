#ifndef GAME_TYPES_SPRITENODE_H
#define GAME_TYPES_SPRITENODE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpriteNode SpriteNode;
struct SpriteNode {
    /* 0x000 */ int index;
    /* 0x004 */ struct SpriteNode *prev;
    /* 0x008 */ struct SpriteNode *next;
};

#endif /* GAME_TYPES_SPRITENODE_H */
