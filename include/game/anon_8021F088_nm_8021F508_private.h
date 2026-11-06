#ifndef GAME_ANON_8021F088_NM_8021F508_PRIVATE_H
#define GAME_ANON_8021F088_NM_8021F508_PRIVATE_H

#include "game/anon_8021F088_private.h"

/* View of the shared coin-mileage resource pool at 0x803C6610. */
struct SetupPool {
    char prefix[0x428];
    ItemPose poses[1];
};
extern "C" const SetupPool lbl_803C6610;

#endif
