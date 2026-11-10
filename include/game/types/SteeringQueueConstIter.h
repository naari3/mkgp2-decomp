#ifndef GAME_TYPES_STEERINGQUEUECONSTITER_H
#define GAME_TYPES_STEERINGQUEUECONSTITER_H

#include "game/types/SteeringQueueIter.h"
#include "game/types/SteeringQueueValue.h"

/* Declare before including (each user already does): SteeringRing */

struct SteeringQueueConstIter {
    SteeringRing *map;
    unsigned long blockIndex;
    int *block;
    SteeringQueueValue *ptr, *end;
    unsigned long index;
    SteeringQueueConstIter(const SteeringQueueIter &o)
        : map(o.map), blockIndex(o.blockIndex), block(o.block), ptr(o.ptr),
          end(o.end), index(o.index) {}
};

#endif /* GAME_TYPES_STEERINGQUEUECONSTITER_H */
