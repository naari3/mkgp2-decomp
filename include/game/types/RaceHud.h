#ifndef GAME_TYPES_RACEHUD_H
#define GAME_TYPES_RACEHUD_H

#include "game/types/PathManager.h"

struct RaceHud {
    unsigned char data[0x80];
    RaceHud(PathManager *path);
};

#endif /* GAME_TYPES_RACEHUD_H */
