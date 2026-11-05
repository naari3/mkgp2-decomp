#ifndef STEERING_QUEUE_PRIVATE_H
#define STEERING_QUEUE_PRIVATE_H

#include "game/SteeringRingAlgorithmsPrivate.h"

inline void *operator new(unsigned long, void *p) { return p; }

struct SteeringQueueValue {
    int first, second;
    SteeringQueueValue() {}
    SteeringQueueValue(const SteeringQueueValue &v) : first(v.first), second(v.second) {}
};

struct QueueBlockMap : SteeringRing {
    QueueBlockMap() {
        capacity = 0;
        count = 0;
        head = 0;
        data = 0;
    }
    ~QueueBlockMap() {
        if (this) {
            if (data) MemoryManager_TimedFree(data);
        }
    }
};

struct SteeringQueue {
    unsigned long blockSize;
    SteeringRing blocks;
    unsigned long first, count;
};

struct SteeringQueueIter {
    SteeringRing *map;
    unsigned long blockIndex;
    int *block;
    SteeringQueueValue *ptr, *end;
    unsigned long index;

    SteeringQueueIter(SteeringRing *m, unsigned long b, int *bp,
            SteeringQueueValue *p, SteeringQueueValue *e, unsigned long i)
        : map(m), blockIndex(b), block(bp), ptr(p), end(e), index(i) {}
    SteeringQueueIter(const SteeringQueueIter &o)
        : map(o.map), blockIndex(o.blockIndex), block(o.block), ptr(o.ptr),
          end(o.end), index(o.index) {}
};

struct QueueRingConstIter {
    SteeringRing *ring;
    unsigned long index;
    const int *ptr;
    QueueRingConstIter(const SteeringRingIter &p)
        : ring(p.ring), index(p.index), ptr(p.ptr) {}
};

extern "C" {
extern const char lbl_803BD208[], lbl_803BD260[], lbl_803BD280[];
extern const unsigned long lbl_806DA360;
extern int lbl_806D1904, lbl_806D1908;
unsigned long fn_801E5A00(void *);
void fn_801E435C(void *, unsigned long, int);
void fn_801E4544(SteeringRing *, const SteeringRingConstIter &, const SteeringRingConstIter &);
void fn_801E5454(SteeringRing *, const int &);
void fn_801E5724(SteeringRing *, const int &);
void fn_801E4AF4(SteeringRing *, const QueueRingConstIter &, unsigned long, const int &);
SteeringRingIter fn_801E4824(SteeringRing *, const QueueRingConstIter &, const QueueRingConstIter &);
void fn_801E3848(SteeringQueue *, unsigned long, const SteeringQueueValue &);
SteeringQueueIter fn_801E35FC(SteeringQueue *, unsigned long);
void fn_801E36A8(SteeringQueue *, const SteeringQueueIter &, const SteeringQueueIter &);
void fn_801E2C40(SteeringQueue *);
}

static inline SteeringQueueValue *QueueAt(SteeringQueue *s, unsigned long i) {
    if (i < s->blockSize) {
        return (SteeringQueueValue *)s->blocks.data[s->blocks.head] + i;
    }
    unsigned long block = i / s->blockSize;
    unsigned long j = s->blocks.head + block;
    if (j >= s->blocks.capacity) j -= s->blocks.capacity;
    return (SteeringQueueValue *)s->blocks.data[j] + i % s->blockSize;
}

static inline void QueueTrim(SteeringQueue *s) {
    unsigned long n = s->blocks.count - 2;
    while (n) {
        --s->blocks.count;
        unsigned long j = s->blocks.head + s->blocks.count - 1;
        if (j >= s->blocks.capacity) j -= s->blocks.capacity;
        int &p = s->blocks.data[j];
        MemoryManager_TimedFree((void *)p);
        p = 0;
        --n;
    }
    s->first = s->blockSize / 2;
}

#endif
