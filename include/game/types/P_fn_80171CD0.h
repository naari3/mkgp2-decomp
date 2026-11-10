#ifndef GAME_TYPES_P_FN_80171CD0_H
#define GAME_TYPES_P_FN_80171CD0_H

#include "game/types/JObj.h"
#include "game/types/clMapEffectParts.h"

struct P_fn_80171CD0 : clMapEffectParts {
    char pad[0x78];

    P_fn_80171CD0(const char *file, JObj *joint, float a, float b);
};

#endif /* GAME_TYPES_P_FN_80171CD0_H */
