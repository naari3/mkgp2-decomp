#ifndef STEERING_RING_PRIVATE_H
#define STEERING_RING_PRIVATE_H
#include "game/types/size_t.h"
extern "C" {
unsigned long strlen(const char *);
char *strcpy(char *, const char *);
void *FUN_8003b120(unsigned long);
void MemoryManager_Free(void *);
void MemoryManager_TimedFree(void *);
void *Alloc(unsigned long);
extern const char lbl_803BD2DC[], lbl_803BD2FC[];
extern unsigned long lbl_806CFF84, lbl_806CFF80;
}
void *operator new(size_t);
void operator delete(void *);
#include "game/types/RingShared.h"
namespace std {
struct exception { exception() {} virtual ~exception(); };
struct logic_error : exception {
    RingShared message;
    logic_error(const char *s) : message(FUN_8003b120(strlen(s)+1)) { strcpy(message.ptr,s); }
    virtual ~logic_error();
};
struct length_error : logic_error {
    length_error(const char *s) : logic_error(s) {}
    virtual ~length_error();
};
}
inline unsigned long RingMax() { volatile unsigned long n=0x3fffffff; return 0x3fffffff; }
inline const unsigned long &RingMaxRef(const unsigned long &a, const unsigned long &b) { return a<b ? b : a; }
struct SteeringRing;
struct SteeringRingIter {
    SteeringRing *ring;
    unsigned long index;
    int *ptr;
    SteeringRingIter(SteeringRing *r, unsigned long i, int *p) : ring(r), index(i), ptr(p) {}
    SteeringRingIter &operator++();
    SteeringRingIter &operator--();
    int &operator*() { return *ptr; }
};
struct SteeringRing {
    unsigned long capacity, count, head;
    int *data;
    SteeringRingIter begin() { return SteeringRingIter(this,0,data+head); }
    SteeringRingIter end() {
        unsigned long i=head+count;
        if(i<capacity) return SteeringRingIter(this,count,data+i);
        else return SteeringRingIter(this,count,data+(i-capacity));
    }
};
inline SteeringRingIter &SteeringRingIter::operator++() {
    ++index;
    if(++ptr == ring->data+ring->capacity) ptr=ring->data;
    return *this;
}
inline SteeringRingIter &SteeringRingIter::operator--() {
    --index;
    if(ptr==ring->data) ptr=ring->data+ring->capacity;
    --ptr;
    return *this;
}
inline int *RingCopy(SteeringRingIter first, SteeringRingIter last, int *out) {
    while(first.index!=last.index) { *out=*first; ++first; ++out; }
    return out;
}
#endif
