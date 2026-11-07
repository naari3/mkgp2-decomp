#include "game/SteeringRingInsertPrivate.h"
static inline unsigned long AssignDistance(const SteeringRingConstIter &first, const SteeringRingConstIter &last) {
    return RingDistance4(first,last);
}
static inline const unsigned long &AssignMin(const unsigned long &a, const unsigned long &b) {
    return a < b ? a : b;
}
static inline unsigned long AssignMaxSize() {
    unsigned long limit = 0xFFFFFFFFUL / sizeof(int);
    unsigned long max = 0xFFFFFFFFUL;
    return AssignMin(limit, max);
}
static inline int *AssignAllocate(unsigned long n) {
    return (int *)Alloc(n * sizeof(int));
}
extern "C" void fn_801E4544(SteeringRing *s, const SteeringRingConstIter &first, const SteeringRingConstIter &last) {
    unsigned long n=AssignDistance(first,last);
    if(n>AssignMaxSize()) throw std::length_error(lbl_803BD2A4);
    if(n<=s->capacity) {
        RingCopy4(first,last,s->data);
        s->head=0;
        s->count=n;
    } else {
        int *old=s->data;
        s->data=AssignAllocate(n);
        RingCopy4(first,last,s->data);
        if(old) MemoryManager_TimedFree(old);
        s->capacity=n;
        s->count=n;
        s->head=0;
    }
}
