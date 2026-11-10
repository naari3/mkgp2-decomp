#ifndef GAME_CLITEMBOXMANAGER_NM1_PRIVATE_H
#define GAME_CLITEMBOXMANAGER_NM1_PRIVATE_H
#include "game/types/size_t.h"

/* Private layout for the unlock TU. The value-construction wrapper must not
 * change the list types used by the separately matched manager destructors. */
#include "game/singleton.h"

void *operator new(size_t size);
void operator delete(void *ptr);
inline void *operator new(size_t, void *p) { return p; }

extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
extern const float lbl_806D2A10;
extern const float lbl_806D2A20;

void clItemBox_Dtor(void *box, int flag);
unsigned char clItemBox_Tick(void *box);
void clItemBox_Draw(void *box);
unsigned char clItemBox_IsPickedUp(void *box);
void clItemBox_ResetTimer(void *box);
void clItemBox_TransitionToDebris(void *box, float x, float y, float z);
void *clItemBox_FactoryCreate(void *entry);
unsigned char IsSpawnTableTerminator(void *entry);
float *clItemBoxResponder_GetBoundPosVec3(void *responder);
unsigned char clItemBoxResponder_IsCmdSlotFree(void *responder);
void clItemBoxResponder_CmdGetWorldPos(void *responder, float *x, float *y, float *z);
void clItemBoxResponder_CmdSlotCountdown(void *responder);
void clItemBoxManager_Bind(int index);
void clItemBoxManager_UnbindCurrent(void);
void clItemBoxManager_TeardownAssets(void);
void clItemBoxManager_LoadAssets(void);
void fn_8016CB4C(void);
void fn_8016CBAC(void *table);
}

class ScopedTimer {
public:
    ScopedTimer(int slot) { m_slot = slot; m_startTick = OSGetTick(); }
    ~ScopedTimer() {
        Profiler_RecordFrame(m_slot, (float)(((OSGetTick() - m_startTick) << 3) / ((*(volatile unsigned int *)0x800000F8 >> 2) / 125000)) / lbl_806D2A10);
    }
private:
    unsigned int m_startTick;
    int m_slot;
};

template <class T> struct equal_to {
    bool operator()(const T &a, const T &b) const { return a == b; }
};

template <class Op, class T> struct binder2nd {
    Op op;
    T value;
    binder2nd(const Op &o, const T &v) : op(o), value(v) {}
    bool operator()(const T &x) const { return op(x, value); }
};

template <class Op, class T> inline binder2nd<Op, T> bind2nd(const Op &o, const T &v)
{
    return binder2nd<Op, T>(o, v);
}

template <class T> struct NodeHolder;

/* The element subobject owns cleanup if its copy construction fails. */
template <class T> struct ListValueCopy {
    T value;
    ListValueCopy(const T &v, NodeHolder<T> &h);
    operator T &() { return value; }
    operator const T &() const { return value; }
};

template <class T> struct ListNode {
    ListNode *prev;
    ListNode *next;
    ListValueCopy<T> value;
};

template <class T> struct ListIter {
    ListNode<T> *node;

    ListIter() {}
    ListIter(ListNode<T> *n) : node(n) {}
    T &operator*() const { return node->value; }
    ListIter &operator++() { node = node->next; return *this; }
    ListIter operator++(int) { ListIter tmp = *this; node = node->next; return tmp; }
    bool operator==(const ListIter &o) const { return node == o.node; }
    bool operator!=(const ListIter &o) const { return node != o.node; }
};

struct ListHead;

template <class T> struct NodeHolder {
    ListHead *owner;
    ListNode<T> *p;

    NodeHolder(ListHead *o, ListNode<T> *n) : owner(o), p(n) {}
    ListNode<T> *release() { ListNode<T> *n = p; p = 0; return n; }
};

struct ListHead {
    ListHead *prev;
    ListHead *next;
};

template <class T> struct ListImpl {
    typedef ListNode<T> Node;
    typedef ListIter<T> iterator;

    unsigned long size;
    ListHead head;

    ListImpl();
    ~ListImpl() { erase(begin(), end()); }

    iterator begin() { return ++end(); }
    iterator end() { return iterator((Node *)&head); }
    iterator erase(const iterator &first, const iterator &last);
    iterator insert(const iterator &pos, const T &v);
    void push_back(const T &v) { Node *n = (Node *)&head; insert(iterator(n), v); }

    template <class Pred> void remove_if(Pred pred);
};

template <class T> struct ListBase : ListImpl<T> {
    ~ListBase() {}
};

#include "game/types/ResponderList.h"

#include "game/types/BoxList.h"

struct clItemBoxManagerBase {
    virtual void Key();
    virtual ~clItemBoxManagerBase();
    clItemBoxManagerBase();
};

extern "C" clItemBoxManagerBase *lbl_806D10D0;

inline clItemBoxManagerBase::clItemBoxManagerBase() { lbl_806D10D0 = this; }

#include "game/types/clItemBoxManager.h"

#endif
