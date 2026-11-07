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
/* fakematch (pragma): opt_lifetimes off gives the final countdown walker the
 * inner responder walker's register (r30) like the target. */
#pragma push
#pragma opt_lifetimes off
extern "C" void clItemBoxManager_Update_Inner(clItemBoxManager *self)
{
    ListNode<void *> *it;
    ListNode<void *> *rt;
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
    for (it = (ListNode<void *> *)self->boxes.head.next; it != boxEnd; it = it->next) {
        void *box = it->value;
        if (clItemBox_Tick(box) != 1) {
            continue;
        }
        for (rt = (ListNode<void *> *)self->responders.head.next; rt != responderEnd; rt = rt->next) {
            void *responder = rt->value;
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
    for (rt = responderEnd->next; rt != responderEnd; rt = rt->next) {
        clItemBoxResponder_CmdSlotCountdown(rt->value);
    }
}
#pragma pop
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

template <class T> template <class Pred> void ListImpl<T>::remove_if(Pred pred)
{
    iterator e = end();
    for (iterator i = begin(); i != e; ++i) {
        if (pred(*i)) {
            iterator j = i;
            ++j;
            for (; j != e; ++j) {
                if (!pred(*j)) {
                    break;
                }
            }
            i.node = EraseListNodes(this, i.node, j.node);
            if (i == e) {
                break;
            }
        }
    }
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
    try {
        new (&h.p->value) T(v);
        Node *n = h.release();
        Node *p = pos.node;
        p->prev->next = n;
        n->prev = p->prev;
        p->prev = n;
        n->next = p;
        size++;
        return iterator(n);
    } catch (...) {
        operator delete(h.release());
    }
}

template <class T> ListImpl<T>::ListImpl()
{
    ListHead *h = &head;
    size = 0;
    h->next = h;
    h->prev = h;
}
