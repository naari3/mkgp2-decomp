#include "game/SteeringRingInsertPrivate.h"
static inline unsigned long AssignDistance(const SteeringRingConstIter &first, const SteeringRingConstIter &last) {
    return RingDistance4(first,last);
}
extern "C" void fn_801E4544(SteeringRing *s, const SteeringRingConstIter &first, const SteeringRingConstIter &last) {
    unsigned long n=AssignDistance(first,last);
    if(n>RingMax()) throw std::length_error(lbl_803BD2A4);
    if(n<=s->capacity) {
        RingCopy4(first,last,s->data);
        s->head=0;
        s->count=n;
    } else {
        int *old=s->data;
        s->data=(int *)Alloc(n*4);
        RingCopy4(first,last,s->data);
        if(old) MemoryManager_TimedFree(old);
        s->capacity=n;
        s->count=n;
        s->head=0;
    }
}
