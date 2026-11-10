#ifndef GAME_TYPES_SPRITEANIM_H
#define GAME_TYPES_SPRITEANIM_H

struct SpriteAnimData;

/* Merged from 22 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpriteAnim SpriteAnim;
struct SpriteAnim {
    /* 0x000 */ unsigned char flag;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ int mode;
    /* 0x008 */ float time;
    /* 0x00C */ float c[6];
    /* 0x024 */ const char *name;
    /* 0x028 */ struct SpriteAnimData *data;
};

#endif /* GAME_TYPES_SPRITEANIM_H */
