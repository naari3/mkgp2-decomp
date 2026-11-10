#ifndef GAME_TYPES_KARTRENDER_H
#define GAME_TYPES_KARTRENDER_H

struct ItemEffectBus;

/* Merged from 14 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartRender KartRender;
struct KartRender {
    /* 0x000 */ unsigned char pad_000[0x1F4];
    /* 0x1F4 */ int slot;
    /* 0x1F8 */ int chara;
    /* 0x1FC */ unsigned char pad_1FC[0x3C];
    /* 0x238 */ int visible;
    /* 0x23C */ unsigned char middle[0x90];
    /* 0x2CC */ int coins;
    /* 0x2D0 */ unsigned char special;  /* also: active */
    /* 0x2D1 */ unsigned char pad_2D1[0x33];
    /* 0x304 */ struct ItemEffectBus *status;
};

#endif /* GAME_TYPES_KARTRENDER_H */
