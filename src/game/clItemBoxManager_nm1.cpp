/* Remaining manager/list methods, 0x8005F868..0x8005FFBC.
 * NonMatching: retain native C++ improvements while the reversed EH group
 * keeps these functions together. */
#include "game/clItemBoxManagerUnlockPrivate.h"

extern "C" void clItemBoxManager_UnregisterResponder(clItemBoxManager *self, void *responder)
{
    equal_to<void *> equal;
    binder2nd<equal_to<void *>, void *> pred(equal, responder);
    self->responders.remove_if(pred);
}

extern "C" void clItemBoxManager_RegisterResponder(clItemBoxManager *self, void *responder)
{
    self->responders.push_back(responder);
}

#pragma auto_inline off
extern "C" void clItemBoxManager_Draw_Inner(clItemBoxManager *self)
{
    ListNode<void *> *it;
    ListNode<void *> *e;

    if (self->boxes.size == 0) {
        return;
    }
    e = (ListNode<void *> *)&self->boxes.head;
    clItemBoxManager_Bind(0);
    for (it = e->next; it != e; it = it->next) {
        clItemBox_Draw(it->value);
    }
    clItemBoxManager_UnbindCurrent();
    clItemBoxManager_Bind(1);
    for (it = e->next; it != e; it = it->next) {
        clItemBox_Draw(it->value);
    }
    clItemBoxManager_UnbindCurrent();
    clItemBoxManager_Bind(2);
    for (it = e->next; it != e; it = it->next) {
        clItemBox_Draw(it->value);
    }
    clItemBoxManager_UnbindCurrent();
}
#pragma auto_inline reset

extern "C" void clItemBoxManager_Draw(clItemBoxManager *self)
{
    ScopedTimer timer(0x24);
    clItemBoxManager_Draw_Inner(self);
}

struct Vec3 {
    float x, y, z;
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    ~Vec3() {}
};

#pragma auto_inline off
extern "C" void clItemBoxManager_Update_Inner(clItemBoxManager *self)
{
    ListIter<void *> it;
    ListIter<void *> rt;
    ListNode<void *> *boxEnd;
    ListNode<void *> *responderEnd;

    if (!self->active) {
        return;
    }
    if (self->boxes.size == 0) {
        return;
    }
    boxEnd = (ListNode<void *> *)&self->boxes.head;
    responderEnd = (ListNode<void *> *)&self->responders.head;
    for (it.node = (ListNode<void *> *)self->boxes.head.next; it.node != boxEnd; ++it) {
        void *box = *it;
        if (clItemBox_Tick(box) != 1) {
            continue;
        }
        for (rt.node = (ListNode<void *> *)self->responders.head.next; rt.node != responderEnd; ++rt) {
            void *responder = *rt;
            float *p = clItemBoxResponder_GetBoundPosVec3(responder);
            Vec3 d(p[0], p[1], p[2]);
            d.x -= ((float *)box)[2];
            d.y -= ((float *)box)[3];
            d.z -= ((float *)box)[4];
            if (d.x * d.x + d.y * d.y + d.z * d.z < lbl_806D2A20) {
                if (clItemBox_IsPickedUp(box) == 1) {
                    clItemBox_ResetTimer(box);
                } else if (clItemBoxResponder_IsCmdSlotFree(responder) == 1) {
                    float x, y, z;
                    clItemBoxResponder_CmdGetWorldPos(responder, &x, &y, &z);
                    clItemBox_TransitionToDebris(box, x, y, z);
                }
                break;
            }
        }
    }
    for (rt.node = responderEnd->next; rt.node != responderEnd; ++rt) {
        clItemBoxResponder_CmdSlotCountdown(*rt);
    }
}
#pragma auto_inline reset

extern "C" void clItemBoxManager_Update(clItemBoxManager *self)
{
    ScopedTimer timer(0x24);
    clItemBoxManager_Update_Inner(self);
}

inline clItemBoxManager::clItemBoxManager(void *table)
{
    active = 1;
    if (table != 0) {
        char *entry;
        clItemBoxManager_LoadAssets();
        for (entry = (char *)table; !IsSpawnTableTerminator(entry); entry += 0x10) {
            boxes.push_back(clItemBox_FactoryCreate(entry));
        }
        fn_8016CBAC(table);
    }
}

static inline clItemBoxManager *clItemBoxManager_Get(void)
{
    return (clItemBoxManager *)SINGLETON_INSTANCE(lbl_806D10D0);
}

extern "C" clItemBoxManager *SoundDriver_GetOrCreate(void *table)
{
    if (clItemBoxManager_Get() == 0) {
        new clItemBoxManager(table);
    }
    return clItemBoxManager_Get();
}

template <class T> inline ListNode<T> *EraseListNodes(ListImpl<T> *self, ListNode<T> *first, ListNode<T> *last)
{
    if (first == last) {
        return last;
    }
    ListNode<T> *lp = last->prev;
    first->prev->next = lp->next;
    lp->next->prev = first->prev;
    while (first != last) {
        ListNode<T> *n = first;
        first = first->next;
        delete n;
        self->size--;
    }
    return last;
}

template <class T> struct EraseIter {
    ListNode<T> *node;
    EraseIter(ListNode<T> *n) : node(n) {}
    EraseIter(const EraseIter &o) : node(o.node) {}
};

template <class T> inline EraseIter<T> EraseListIters(ListImpl<T> *self, EraseIter<T> first, EraseIter<T> last)
{
    if (first.node == last.node) {
        return last;
    }
    ListNode<T> *lp = last.node->prev;
    first.node->prev->next = lp->next;
    lp->next->prev = first.node->prev;
    while (first.node != last.node) {
        ListNode<T> *n = first.node;
        first.node = n->next;
        delete n;
        self->size--;
    }
    return last;
}

template <class T> template <class Pred> void ListImpl<T>::remove_if(Pred pred)
{
    EraseIter<T> e((ListNode<T> *)&head);
    EraseIter<T> i(e.node->next);
    for (; i.node != e.node; i.node = i.node->next) {
        if (pred(i.node->value)) {
            EraseIter<T> j(i);
            j.node = j.node->next;
            for (; j.node != e.node; j.node = j.node->next) {
                if (!pred(j.node->value)) {
                    break;
                }
            }
            i = EraseListIters(this, i, j);
            if (i.node == e.node) {
                break;
            }
        }
    }
}

template <class T>
inline ListValueCopy<T>::ListValueCopy(const T &v, NodeHolder<T> &h) try : value(v)
{
}
catch (...) {
    operator delete(h.release());
}

#pragma auto_inline off
template <class T> ListIter<T> ListImpl<T>::erase(const iterator &first_, const iterator &last_)
{
    iterator &first = (iterator &)first_;
    iterator &last = (iterator &)last_;
    if (first == last) {
        return last;
    }
    Node *f = first.node;
    Node *lp = last.node->prev;
    f->prev->next = lp->next;
    lp->next->prev = f->prev;
    while (first != last) {
        Node *n = first.node;
        ++first;
        delete n;
        size--;
    }
    return last;
}

template <class T> ListIter<T> ListImpl<T>::insert(const iterator &pos, const T &v)
{
    NodeHolder<T> h(&head, (Node *)operator new(sizeof(Node)));
    new (&h.p->value) ListValueCopy<T>(v, h);
    Node *n = h.release();
    pos.node->prev->next = n;
    n->prev = pos.node->prev;
    pos.node->prev = n;
    n->next = pos.node;
    size++;
    return iterator(n);
}

template <class T> ListImpl<T>::ListImpl()
{
    ListHead *h = &head;
    size = 0;
    h->next = h;
    h->prev = h;
}
