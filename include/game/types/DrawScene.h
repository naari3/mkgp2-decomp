#ifndef GAME_TYPES_DRAWSCENE_H
#define GAME_TYPES_DRAWSCENE_H

#include "game/types/DrawObj.h"

typedef struct DrawScene {
    char pad0[4];
    unsigned char hidden;
    char pad5[3];
    unsigned char state;
    char pad9[0x2c - 9];
    DrawObj *a;
    DrawObj *b;
} DrawScene;

#endif /* GAME_TYPES_DRAWSCENE_H */
