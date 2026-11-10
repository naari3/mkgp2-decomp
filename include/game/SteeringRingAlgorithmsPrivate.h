#ifndef STEERING_RING_ALGORITHMS_PRIVATE_H
#define STEERING_RING_ALGORITHMS_PRIVATE_H
#include "game/SteeringRingPrivate.h"
extern "C" {
extern const char lbl_803BD2A4[], lbl_803BD2C0[];
extern unsigned long lbl_806CFF88;
}
#include "game/types/SteeringRingConstIter.h"
inline unsigned long RingDistance4(SteeringRingConstIter first, SteeringRingConstIter last) {
    return last.index-first.index;
}
inline int *RingCopy4(SteeringRingConstIter first, SteeringRingConstIter last, int *out) {
    while(first.index!=last.index) { *out=*first.ptr; ++first; ++out; }
    return out;
}
inline SteeringRingIter RingAdvance(SteeringRingIter p, unsigned long n) {
    p.index+=n;
    unsigned long i=p.ring->head+p.index;
    if(i>=p.ring->capacity) i-=p.ring->capacity;
    p.ptr=p.ring->data+i;
    return p;
}
inline SteeringRingIter RingCopyForward(SteeringRingIter first, SteeringRingIter last, SteeringRingIter out) {
    while(first.index!=last.index) { *out=*first; ++first; ++out; }
    return out;
}
inline SteeringRingIter RingCopyBackward(SteeringRingIter first, SteeringRingIter last, SteeringRingIter out) {
    while(last.index!=first.index) { *--out=*--last; }
    return out;
}
inline SteeringRingIter RingFillN(SteeringRingIter out, unsigned long n, const int &value) {
    while(n) { *out=value; ++out; --n; }
    return out;
}
#endif
