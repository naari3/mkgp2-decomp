/* Flow scene destructor: deletes the objects in its list, then clears the list. */
class ListObj {
public:
    virtual ~ListObj();
};

struct ListNode {
    ListNode *prev;
    ListNode *next;
    ListObj *obj;
};

struct ListIter {
    ListNode *node;

    ListIter(ListNode *n) : node(n) {}
    ListObj *operator*() const { return node->obj; }
    ListIter &operator++() {
        node = node->next;
        return *this;
    }
    bool operator!=(const ListIter &o) const { return node != o.node; }
};

struct ListImpl {
    int size;
    ListNode head;

    ListIter begin() { return ++end(); }
    ListIter end() { return ListIter(&head); }
    ListIter EraseRange(const ListIter &first, const ListIter &last);

    ~ListImpl() {
        EraseRange(begin(), end());
    }
};

struct ListBase : ListImpl {
    ~ListBase() {}
};

struct ObjList : ListBase {
    ~ObjList() {}
};

#include "game/types/InputView.h"

#include "game/types/FlowBase.h"

extern "C" {
extern InputView *g_pInputState;
extern void *clFlowGpPlease_vtable_8049B16C[];
}

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

struct Scene801CCF2C : FlowBase {
    ObjList objs;

    ~Scene801CCF2C();
};

Scene801CCF2C::~Scene801CCF2C() {
    vt = clFlowGpPlease_vtable_8049B16C;
    for (ListIter it(objs.head.next); it != objs.end(); ++it) {
        delete *it;
    }
    InputView *input = input_state();
    input->enabled = 0;
    input->held = 0;
    input->edge = 0;
}
