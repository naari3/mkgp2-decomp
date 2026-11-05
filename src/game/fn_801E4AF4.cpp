#include "game/SteeringRingInsertPrivate.h"
extern "C" void fn_801E4AF4(SteeringRing *s, const SteeringRingIter &position, unsigned long n, const int &value) {
    if(n) {
        unsigned long max=RingMax();
        if(n>max || s->count>max-n) throw std::length_error(lbl_803BD2C0);
        unsigned long newCount=s->count+n;
        if(newCount<=s->capacity) {
            unsigned long before=position.index;
            SteeringRingIter end=s->end();
            unsigned long after=end.index-position.index;
            if(before<after) {
                if(s->head>=n) s->head-=n;
                else s->head=s->capacity-(n-s->head);
                if(before==0) RingFillN(s->begin(),n,value);
                else {
                    SteeringRingIter start=s->begin();
                    RingCopyForward(RingAdvance(start,n),RingAdvance(start,n+before),start);
                    RingFillN(RingAdvance(start,before),n,value);
                }
            } else {
                if(after==0) RingFillN(s->end(),n,value);
                else {
                    RingCopyBackward(position,s->end(),RingAdvance(s->end(),n));
                    RingFillN(position,n,value);
                }
            }
            s->count+=n;
        } else {
            unsigned long cap=RingMaxRef(s->capacity,lbl_806CFF88);
            while(newCount>cap) cap*=2;
            unsigned long before=position.index;
            int *p=(int *)Alloc(cap*4);
            if(before) RingCopy(s->begin(),position,p);
            int *q=p+before;
            unsigned long remaining=n;
            while(remaining) { *q++=value; --remaining; }
            if(before<s->count) RingCopy(position,s->end(),p+before+n);
            if(s->data) MemoryManager_TimedFree(s->data);
            s->data=p;
            s->count=newCount;
            s->capacity=cap;
            s->head=0;
        }
    }
}
