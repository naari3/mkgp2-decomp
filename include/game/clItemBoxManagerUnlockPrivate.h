#ifndef GAME_CLITEMBOXMANAGER_UNLOCK_PRIVATE_H
#define GAME_CLITEMBOXMANAGER_UNLOCK_PRIVATE_H

#include "game/clItemBoxManagerPrivate.h"

/* Keep ownership of an allocated node until insertion commits. */
template <> struct NodeHolder<void *> {
    ListHead *owner;
    ListNode<void *> *p;

    NodeHolder(ListHead *o, ListNode<void *> *n) : owner(o), p(n) {}
    ~NodeHolder() { if (p) operator delete(p); }
    ListNode<void *> *release() {
        ListNode<void *> *n = p;
        p = 0;
        return n;
    }
};

#endif
