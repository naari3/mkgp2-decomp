#include "game/SteeringRingInsertPrivate.h"
static inline const unsigned long &RingMinRef(const unsigned long &a, const unsigned long &b) {
    return a < b ? a : b;
}
static inline unsigned long RingMaxSize() {
    unsigned long limit = 0xFFFFFFFFUL / sizeof(int);
    unsigned long max = 0xFFFFFFFFUL;
    return RingMinRef(limit, max);
}
extern "C" void fn_801E5724(SteeringRing *s, const int &value) {
    if(s->count==RingMaxSize()) throw std::length_error(lbl_803BD2FC);
    if(s->count<s->capacity) {
        if(s->head) --s->head; else s->head=s->capacity-1;
        s->data[s->head]=value;
        ++s->count;
    } else {
        unsigned long n = s->count+1;
        unsigned long cap = RingMaxRef(s->capacity,lbl_806CFF80);
        if(n>cap) cap*=2;
        int *p = (int *)Alloc(cap*4);
        *p=value;
        if(s->count) RingCopy(s->begin(),s->end(),p+1);
        if(s->data) MemoryManager_TimedFree(s->data);
        s->data=p;
        ++s->count;
        s->capacity=cap;
        s->head=0;
    }
}
