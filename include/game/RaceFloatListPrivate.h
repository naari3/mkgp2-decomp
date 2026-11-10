#ifndef GAME_RACE_FLOAT_LIST_PRIVATE_H
#define GAME_RACE_FLOAT_LIST_PRIVATE_H
#include "game/types/size_t.h"
struct RaceFloatNode {
    RaceFloatNode *prev, *next;
    float value;
};
struct RaceFloatList {
    unsigned int count;
    RaceFloatNode *last, *first;
    RaceFloatNode *End() { return (RaceFloatNode *)&last; }
};
extern "C" void *Alloc(unsigned long);
extern "C" void MemoryManager_TimedFree(void *);
inline void *operator new(size_t, void *p) { return p; }
inline void operator delete(void *, void *) {}
struct RaceFloatNodeGuard {
    RaceFloatNode **allocator;
    RaceFloatNode *node;
    RaceFloatNodeGuard(RaceFloatNode **a, RaceFloatNode *n):allocator(a),node(n) {}
    ~RaceFloatNodeGuard() { if (node) MemoryManager_TimedFree(node); }
    RaceFloatNode *Release() { RaceFloatNode *n=node; node=0; return n; }
};
#endif
