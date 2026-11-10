#ifndef GAME_TYPES_STEPHOLDER_H
#define GAME_TYPES_STEPHOLDER_H

#include "game/types/Spark.h"

/* Include before this header (each user already does): "game/types/HudResSet.h", "game/types/RecordCounter.h", "game/types/VObjC.h" */

typedef struct StepHolder {
    char pad0[0xC];
    int done;
    unsigned char active;
    char pad11[3];
    int layer;
    int state;
    float t;
    char pad20[4];
    VObjC *m24;
    VObjC *m28;
    float cx;
    float cy;
    char pad34[4];
    float rot;
    float rotSpeed;
    Spark sparks[5];
    void *f90;
    RecordCounter *counter;
    struct HudResSet *step;
    unsigned char glow;
} StepHolder;

#endif /* GAME_TYPES_STEPHOLDER_H */
