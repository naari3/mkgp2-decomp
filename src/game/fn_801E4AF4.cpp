#include "game/SteeringRingInsertPrivate.h"
static inline const unsigned long &InsertMin(const unsigned long &a, const unsigned long &b) {
    return a < b ? a : b;
}
static inline unsigned long InsertMaxSize() {
    unsigned long limit = 0xFFFFFFFFUL / sizeof(int);
    unsigned long max = 0xFFFFFFFFUL;
    return InsertMin(limit, max);
}
// Iterator addition returns the result of the mutating advance by reference.
static inline SteeringRingIter &InsertPlusAssign(SteeringRingIter &p, unsigned long n) {
    p.index += n;
    unsigned long i = p.ring->head + p.index;
    if(i >= p.ring->capacity) i -= p.ring->capacity;
    p.ptr = p.ring->data + i;
    return p;
}
static inline SteeringRingIter InsertAdvance(const SteeringRingIter &p, unsigned long n) {
    SteeringRingIter result(p);
    return InsertPlusAssign(result, n);
}
static inline int *InsertFillN(int *out, unsigned long n, const int &value) {
    while(n) { *out++ = value; --n; }
    return out;
}
extern "C" void fn_801E4AF4(SteeringRing *s, SteeringRingIter position, unsigned long n, const int &value) {
    if(n) {
        unsigned long max=InsertMaxSize();
        if(n>max || s->count>max-n) throw std::length_error(lbl_803BD2C0);
        int *p;
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
                    RingCopyForward(InsertAdvance(start,n),InsertAdvance(start,n+before),start);
                    RingFillN(InsertAdvance(start,before),n,value);
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
            p=(int *)Alloc(cap*4);
            if(before) RingCopy(s->begin(),position,p);
            InsertFillN(p+before,n,value);
            if(before<s->count) RingCopy(position,s->end(),p+before+n);
            if(s->data) MemoryManager_TimedFree(s->data);
            s->data=p;
            s->count=newCount;
            s->capacity=cap;
            s->head=0;
        }
    }
}
