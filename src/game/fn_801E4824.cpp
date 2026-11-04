#include "game/SteeringRingPrivate.h"
inline SteeringRingIter RingCopyBackward(SteeringRingIter first, SteeringRingIter last, SteeringRingIter out) {
    while(last.index!=first.index) { *--out=*--last; }
    return out;
}
inline SteeringRingIter RingCopyForward(SteeringRingIter first, SteeringRingIter last, SteeringRingIter out) {
    while(first.index!=last.index) { *out=*first; ++first; ++out; }
    return out;
}
inline unsigned long RingEndIndex(SteeringRing *s) {
    if(s->head+s->count<s->capacity) return s->count;
    return s->count;
}
extern "C" SteeringRingIter fn_801E4824(SteeringRing *s, const SteeringRingIter &first, const SteeringRingIter &last) {
    if(first.index==last.index) return first;
    unsigned long before=first.index;
    unsigned long after=RingEndIndex(s)-last.index;
    unsigned long n=last.index-first.index;
    if(before<after) {
        if(before) RingCopyBackward(s->begin(),first,last);
        s->head+=n;
        if(s->head>=s->capacity) s->head-=s->capacity;
    } else {
        if(after) RingCopyForward(last,s->end(),first);
    }
    s->count-=n;
    return first;
}
