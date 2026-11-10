#ifndef GAME_TYPES_GATEANIM_H
#define GAME_TYPES_GATEANIM_H

#include "game/types/clNormal3D.h"

/* Declare before including (each user already does): name */

struct GateAnim {
    char _opaque[0x180];
    GateAnim();
    ~GateAnim();
    void Load(const char *name, int flags, clNormal3D *model, const void *desc);
    void Update();
};

#endif /* GAME_TYPES_GATEANIM_H */
