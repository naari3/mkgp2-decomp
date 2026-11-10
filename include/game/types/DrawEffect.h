#ifndef GAME_TYPES_DRAWEFFECT_H
#define GAME_TYPES_DRAWEFFECT_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DrawEffect DrawEffect;
struct DrawEffect {
    /* 0x000 */ unsigned char pad_000[0x28];
    /* 0x028 */ unsigned char active;
    /* 0x029 */ unsigned char pad_029[0x3];
    /* 0x02C */ float intensity;
    /* 0x030 */ unsigned char pad_030[0x5C];
    /* 0x08C */ float position[3];
    /* 0x098 */ unsigned char pad_098[0x18];
    /* 0x0B0 */ float scale;
    /* 0x0B4 */ unsigned char pad_0B4[0x68];
    /* 0x11C */ void *driver;
};

#endif /* GAME_TYPES_DRAWEFFECT_H */
