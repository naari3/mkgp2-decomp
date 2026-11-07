#ifndef GAME_RACE_DIGIT_LIST_PRIVATE_H
#define GAME_RACE_DIGIT_LIST_PRIVATE_H

/* Float list specialization used beside the race digit HUD. */
struct RaceDigitNode {
    RaceDigitNode *prev, *next;
    float value;
};
struct RaceDigitIterator {
    RaceDigitNode *node;
    RaceDigitIterator(RaceDigitNode *p) : node(p) {}
    RaceDigitIterator(const RaceDigitIterator &p) : node(p.node) {}
    bool operator==(const RaceDigitIterator &p) const { return node == p.node; }
};
struct RaceDigitList {
    int count;
    RaceDigitNode *last, *first;
    RaceDigitNode *End() { return (RaceDigitNode *)&last; }
    RaceDigitIterator Begin() { return RaceDigitIterator(End()->next); }
    RaceDigitIterator Finish() { return RaceDigitIterator(End()); }
};
extern "C" {
void *Alloc(unsigned long);
void MemoryManager_TimedFree(void *);
}
/* fn_80247B8C (RaceDigitListErase.cpp) takes both iterators by value. Callers
 * here pass the address of their own iterator, which is the same ABI (a class
 * with a copy ctor is passed as a pointer to the caller's copy). */
#ifndef RACE_DIGIT_LIST_ERASE_DEFINITION
extern "C" RaceDigitIterator fn_80247B8C(RaceDigitList *, RaceDigitIterator &, RaceDigitIterator &);
inline RaceDigitIterator RaceDigitEraseRange(RaceDigitList *list,
        const RaceDigitIterator &first, const RaceDigitIterator &last) {
    return fn_80247B8C(list, const_cast<RaceDigitIterator &>(first),
        const_cast<RaceDigitIterator &>(last));
}
#endif
#endif
