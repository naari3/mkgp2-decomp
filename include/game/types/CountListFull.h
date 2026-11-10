#ifndef GAME_TYPES_COUNTLISTFULL_H
#define GAME_TYPES_COUNTLISTFULL_H

#include "game/types/RecordCounter.h"
#include "game/types/VObj14.h"

/* Declare before including (each user already does): VObj */

struct CountListFull {
    void *vt;
    char pad4[0xC];
    int layer;
    float t;
    unsigned char on;
    char pad19[3];
    RecordCounter *f1C;
    char pad20[4];
    VObj14 *f24;
    char pad28[4];
    struct {
        int count;
        float t;
        VObj *obj;
    } e[6];
    int highlight;
};

#endif /* GAME_TYPES_COUNTLISTFULL_H */
