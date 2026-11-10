#ifndef GAME_TYPES_HANDLEF_H
#define GAME_TYPES_HANDLEF_H

#include "game/types/Handle.h"

struct HandleF : Handle {
    unsigned char pad[0x18];
    float x, y;
    void SetXY(float a, float b) {
        x = a;
        y = b;
    }
};

#endif /* GAME_TYPES_HANDLEF_H */
