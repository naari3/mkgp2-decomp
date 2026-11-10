#ifndef GAME_TYPES_STEERINGQUEUEITER_H
#define GAME_TYPES_STEERINGQUEUEITER_H

#include "game/types/SteeringQueueValue.h"

/* Declare before including (each user already does): SteeringRing */

struct SteeringQueueIter {
    SteeringRing *map;
    unsigned long blockIndex;
    int *block;
    SteeringQueueValue *ptr, *end;
    unsigned long index;

    SteeringQueueIter(SteeringRing *m, unsigned long b, int *bp,
            SteeringQueueValue *p, SteeringQueueValue *e, unsigned long i)
        : map(m), blockIndex(b), block(bp), ptr(p), end(e), index(i) {}
    SteeringQueueIter(const SteeringQueueIter &o)
        : map(o.map), blockIndex(o.blockIndex), block(o.block), ptr(o.ptr),
          end(o.end), index(o.index) {}
};

#endif /* GAME_TYPES_STEERINGQUEUEITER_H */
