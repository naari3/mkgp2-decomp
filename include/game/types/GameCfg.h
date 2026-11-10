#ifndef GAME_TYPES_GAMECFG_H
#define GAME_TYPES_GAMECFG_H

typedef struct GameCfg {
    unsigned char pad[0x20];
    signed char region;
} GameCfg;

#endif /* GAME_TYPES_GAMECFG_H */
