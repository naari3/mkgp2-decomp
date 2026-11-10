#ifndef GAME_TYPES_SPRITEANIMPARAMBLOCK_H
#define GAME_TYPES_SPRITEANIMPARAMBLOCK_H

struct Sprite;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpriteAnimParamBlock SpriteAnimParamBlock;
struct SpriteAnimParamBlock {
    /* 0x000 */ struct Sprite *sprite;
    /* 0x004 */ short keys[50];
    /* 0x068 */ short params[50];
};

#endif /* GAME_TYPES_SPRITEANIMPARAMBLOCK_H */
