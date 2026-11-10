#ifndef GAME_TYPES_RACESCENE_H
#define GAME_TYPES_RACESCENE_H

struct Deletable;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RaceScene RaceScene;
struct RaceScene {
    /* 0x000 */ void *vtable;
    /* 0x004 */ void *lakitu;  /* also: object */
    /* 0x008 */ void *jyugemuFlag;
    /* 0x00C */ void *jyugemuReverse;
    /* 0x010 */ void *lapBanner;
    /* 0x014 */ void *environment;
    /* 0x018 */ unsigned char pad_018[0x4];
    /* 0x01C */ struct Deletable *camera;  /* also: scene */
    /* 0x020 */ unsigned char pad_020[0x8];
    /* 0x028 */ struct Deletable *shadow;
    /* 0x02C */ void *hud;
    /* 0x030 */ unsigned char pad_030[0x4];
    /* 0x034 */ void *ai;  /* also: hud34 */
    /* 0x038 */ void *hud38;  /* also: coll */
    /* 0x03C */ void *overlay;
};

#endif /* GAME_TYPES_RACESCENE_H */
