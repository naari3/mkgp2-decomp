/*
 * Flow scene list lookups by task id @ 0x80254330..0x80254398.
 */

#include "game/FlowScene.h"

namespace {
struct It {
    ListNode *node;
    It(ListNode *n) : node(n) {}
    It &operator++() {
        node = node->next;
        return *this;
    }
    bool operator!=(const It &o) const { return node != o.node; }
};

inline It End(FlowSceneList *list) { return It(list->entries.End()); }
inline It Begin(FlowSceneList *list) { return It(list->entries.first); }
}

extern "C" FlowTask *fn_80254330(FlowSceneList *list, unsigned int id) {
    for (It it = Begin(list); it != End(list); ++it) {
        if (id == (unsigned int)it.node->task->id) {
            return it.node->task;
        }
    }
    return 0;
}

extern "C" bool fn_80254360(FlowSceneList *list, unsigned int id) {
    for (It it = Begin(list); it != End(list); ++it) {
        if (id == (unsigned int)it.node->task->id) {
            return 1;
        }
    }
    return 0;
}
