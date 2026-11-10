#ifndef GAME_TYPES_OPTIONDRAWSCENE_H
#define GAME_TYPES_OPTIONDRAWSCENE_H

#include "game/types/OptionDrawPanel.h"
#include "game/types/OptionDrawTarget.h"

typedef struct OptionDrawScene {
    char pad0[0x20];
    OptionDrawTarget *target;
    void *preview;
    char pad28[0x10];
    OptionDrawPanel *panel38;
    OptionDrawPanel *panel3C;
    char pad40[8];
    int texture;
    unsigned char toggle;
    char pad4D[3];
    float fade50;
    float fade54;
    unsigned char selection;
} OptionDrawScene;

#endif /* GAME_TYPES_OPTIONDRAWSCENE_H */
