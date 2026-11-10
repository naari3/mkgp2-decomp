#ifndef STEERING_QUEUE_MATCH_PRIVATE_H
#define STEERING_QUEUE_MATCH_PRIVATE_H

/* TU-owned queue views use the existing two-pointer RingString exception
 * model without changing the queue views consumed by other TUs. */
#include "game/SteeringRingInsertPrivate.h"

inline void *operator new(unsigned long size, void *p) { return p; }
inline void operator delete(void *memory, void *place) {}

#include "game/types/SteeringQueueValue.h"

#include "game/types/QueueBlockMap.h"

struct SteeringQueue {
    unsigned long blockSize;
    SteeringRing blocks;
    unsigned long first, count;
};

#include "game/types/SteeringQueueIter.h"

#include "game/types/SteeringQueueConstIter.h"

#include "game/types/QueueRingConstIter.h"

/* The range-assign dispatch passes an empty iterator-category tag in r6. */
struct QueueInputTag {};
struct QueueForwardTag : QueueInputTag {};
struct QueueBidirectionalTag : QueueForwardTag {};
struct QueueAssignTag : QueueBidirectionalTag {};

struct QueueAssignIter {
    SteeringRing *ring;
    unsigned long index;
    const int *ptr;
    /* Preserve the canonical const-iterator ABI, including its unused word. */
    unsigned long reserved;
    QueueAssignIter(const SteeringRingIter &o) : ring(o.ring), index(o.index), ptr(o.ptr) {}
};

extern "C" {
extern const char lbl_803BD208[], lbl_803BD260[], lbl_803BD280[];
extern const unsigned long lbl_806DA360;
extern int lbl_806D1904, lbl_806D1908;
unsigned long fn_801E5A00(void *);
void fn_801E435C(void *, unsigned long, int);
void fn_801E4544(SteeringRing *, QueueAssignIter, QueueAssignIter, QueueAssignTag);
void fn_801E5454(SteeringRing *, const int &);
void fn_801E5724(SteeringRing *, const int &);
void fn_801E4AF4(SteeringRing *, const QueueRingConstIter &, unsigned long, const int &);
SteeringRingIter fn_801E4824(SteeringRing *, const QueueRingConstIter &, const QueueRingConstIter &);
void fn_801E3848(SteeringQueue *, unsigned long, const SteeringQueueValue &);
SteeringQueueIter fn_801E35FC(SteeringQueue *, unsigned long);
void fn_801E36A8(SteeringQueue *, const SteeringQueueConstIter &, const SteeringQueueConstIter &);
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
        unsigned long j = s->blocks.count - 1;
        j += s->blocks.head;
        if (j >= s->blocks.capacity) j -= s->blocks.capacity;
        int &p = s->blocks.data[j];
        MemoryManager_TimedFree((void *)p);
        p = 0;
        --n;
    }
    s->first = s->blockSize / 2;
}

#endif
