#ifndef GAME_TYPES_HUDRESSET_H
#define GAME_TYPES_HUDRESSET_H

#include "game/types/ResTrio.h"

struct HudResSet {
    HudResSet(int coins, int layer, int mode);
    int state;
    int layer;
    char pad8[8];
    char res[11][0x58];
    char texts[3][0x230];
    ResTrio tail;
    ~HudResSet() {
        ResTrio_Destroy(&tail, 0);
        __destroy_arr(texts, (void *)dtor_800869D0, 0x230, 3);
        __destroy_arr(res, (void *)dtor_80082960, 0x58, 11);
    }
};

#endif /* GAME_TYPES_HUDRESSET_H */
