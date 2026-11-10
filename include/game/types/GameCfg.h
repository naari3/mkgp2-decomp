#ifndef GAME_TYPES_GAMECFG_H
#define GAME_TYPES_GAMECFG_H

/* Merged from 7 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GameCfg GameCfg;
struct GameCfg {
    /* 0x000 */ unsigned char pad_000[0x20];
    /* 0x020 */ signed char region;
    /* 0x021 */ unsigned char pad_021[0x2];
    /* 0x023 */ unsigned char b23;
};

#endif /* GAME_TYPES_GAMECFG_H */
