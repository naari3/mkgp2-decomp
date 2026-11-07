#define RACE_DIGIT_LIST_ERASE_DEFINITION
#include "game/RaceDigitListPrivate.h"

static inline void UnlinkRange(RaceDigitNode *head, RaceDigitNode *last) {
    RaceDigitNode *tail = last->prev;
    head->prev->next = tail->next;
    tail->next->prev = head->prev;
}

extern "C" RaceDigitIterator fn_80247B8C(RaceDigitList *self,
        RaceDigitIterator first, RaceDigitIterator last) {
    if (first == last) return last;
    UnlinkRange(first.node, last.node);
    while (first.node != last.node) {
        RaceDigitNode *p = first.node;
        first.node = p->next;
        MemoryManager_TimedFree(p);
        --self->count;
    }
    return last;
}
