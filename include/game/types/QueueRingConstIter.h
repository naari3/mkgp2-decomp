#ifndef GAME_TYPES_QUEUERINGCONSTITER_H
#define GAME_TYPES_QUEUERINGCONSTITER_H

/* Declare before including (each user already does): SteeringRing, SteeringRingIter */

struct QueueRingConstIter {
    SteeringRing *ring;
    unsigned long index;
    const int *ptr;
    QueueRingConstIter(const SteeringRingIter &p)
        : ring(p.ring), index(p.index), ptr(p.ptr) {}
};

#endif /* GAME_TYPES_QUEUERINGCONSTITER_H */
