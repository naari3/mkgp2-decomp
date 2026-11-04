#include "game/SteeringRingPrivate.h"
extern "C" void fn_801E5454(SteeringRing *s, const int &value) {
    if(s->count==RingMax()) throw std::length_error(lbl_803BD2DC);
    if(s->count<s->capacity) {
        unsigned long i=s->count+s->head;
        if(i>=s->capacity) i-=s->capacity;
        s->data[i]=value;
        ++s->count;
    } else {
        unsigned long n = s->count+1;
        unsigned long cap = RingMaxRef(s->capacity,lbl_806CFF84);
        if(n>cap) cap*=2;
        int *p = (int *)Alloc(cap*4);
        p[s->count]=value;
        if(s->count) RingCopy(s->begin(),s->end(),p);
        if(s->data) MemoryManager_TimedFree(s->data);
        s->data=p;
        ++s->count;
        s->capacity=cap;
        s->head=0;
    }
}
