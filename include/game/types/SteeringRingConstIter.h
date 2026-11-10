#ifndef GAME_TYPES_STEERINGRINGCONSTITER_H
#define GAME_TYPES_STEERINGRINGCONSTITER_H

/* Declare before including (each user already does): SteeringRing */

struct SteeringRingConstIter {
    SteeringRing *ring;
    unsigned long index;
    const int *ptr;
    unsigned long reserved;
    SteeringRingConstIter &operator++() {
        ++index;
        if(++ptr==ring->data+ring->capacity) ptr=ring->data;
        return *this;
    }
};

#endif /* GAME_TYPES_STEERINGRINGCONSTITER_H */
