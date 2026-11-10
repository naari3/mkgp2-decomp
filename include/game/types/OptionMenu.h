#ifndef GAME_TYPES_OPTIONMENU_H
#define GAME_TYPES_OPTIONMENU_H

#include "game/types/MenuTarget.h"

typedef struct OptionMenu {
    char pad0[0x1d];
    unsigned char toggleEnabled;
    char pad1E[2];
    MenuTarget *target;
    char pad24[0x20];
    float blink;
    char pad48[4];
    bool toggle;
    char pad4D[3];
    float fade50;
    float fade54;
    unsigned char sel;
    char pad59[3];
    float blink2;
    char pad60[4];
    int value;
    char pad68[0x1c];
    int scroll;
    int scrollTimer;
} OptionMenu;

#endif /* GAME_TYPES_OPTIONMENU_H */
