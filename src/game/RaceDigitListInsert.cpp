#include "game/types/size_t.h"
#include "game/RaceDigitListPrivate.h"

inline void *operator new(size_t, void *p) { return p; }
inline void operator delete(void *, void *) {}

struct RaceDigitFloat {
    float value;
    RaceDigitFloat(const RaceDigitFloat &v) : value(v.value) {}
};

struct RaceDigitNodeGuard {
    RaceDigitNode **allocator;
    RaceDigitNode *node;
    RaceDigitNodeGuard(RaceDigitNode **a, RaceDigitNode *n) : allocator(a), node(n) {}
    ~RaceDigitNodeGuard() { if (node) MemoryManager_TimedFree(node); }
    RaceDigitNode *Release() {
        RaceDigitNode *p = node;
        node = 0;
        return p;
    }
};

static inline RaceDigitIterator InsertNode(RaceDigitList *self,
        RaceDigitNode *at, RaceDigitNode *node) {
    at->prev->next = node;
    node->prev = at->prev;
    at->prev = node;
    node->next = at;
    ++self->count;
    return RaceDigitIterator(node);
}

extern "C" RaceDigitIterator fn_80247C3C(RaceDigitList *self,
        const RaceDigitIterator &position, const RaceDigitFloat &value) {
    RaceDigitNodeGuard guard(&self->last, (RaceDigitNode *)Alloc(sizeof(RaceDigitNode)));
    new (&guard.node->value) RaceDigitFloat(value);
    return InsertNode(self, position.node, guard.Release());
}
