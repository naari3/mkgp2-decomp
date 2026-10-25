/*
 * clItemBoxManager singleton: lifetime, responder registration, draw/update
 * and its two pointer lists, 0x8005F65C..0x8005FFBC.
 * The lists follow the MSL list layout: size, then the sentinel node.
 *
 * NonMatching (5/15 exact, 92% overall). Open points:
 *  - erase/insert take const iterator& here so callers pass the temporaries
 *    without copies, as the target does; erase then has to cast away const
 *    and reloads `last` one time fewer than the target.
 *  - insert: the target keeps a {head, node} holder in memory and has a dead
 *    catch landing pad (frame pointer, `stw r1`); not reproduced.
 *  - Loop iterator/end registers are swapped in the dtor and Draw_Inner;
 *    Update_Inner copies the responder position through the stack.
 *  - The weak list/base destructors and the inline ScopedTimer destructor
 *    are emitted in a different order than the target text layout.
 */

void *operator new(unsigned long size);
void operator delete(void *ptr);
inline void *operator new(unsigned long, void *p) { return p; }

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

template <class T> struct ListNode {
    ListNode *prev;
    ListNode *next;
    T value;
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
    void push_back(const T &v) { insert(end(), v); }

    template <class Pred> void remove_if(Pred pred);
};

template <class T> struct ListBase : ListImpl<T> {
    ~ListBase() {}
};

struct ResponderList : ListBase<void *> {
    ~ResponderList() {}
};

struct BoxList : ListBase<void *> {
    ~BoxList() {}
};

struct clItemBoxManagerBase {
    virtual void Key();
    virtual ~clItemBoxManagerBase() {}
    clItemBoxManagerBase();
};

extern "C" clItemBoxManagerBase *lbl_806D10D0;

inline clItemBoxManagerBase::clItemBoxManagerBase() { lbl_806D10D0 = this; }

struct clItemBoxManager : clItemBoxManagerBase {
    ResponderList responders; /* 0x04 */
    BoxList boxes;            /* 0x10 */
    unsigned char active;    /* 0x1C */

    virtual void Key();
    virtual ~clItemBoxManager();
    clItemBoxManager(void *table);
};

clItemBoxManager::~clItemBoxManager()
{
    ListIter<void *> it;
    for (it = boxes.begin(); it != boxes.end(); ++it) {
        clItemBox_Dtor(*it, 1);
    }
    clItemBoxManager_TeardownAssets();
    fn_8016CB4C();
}

extern "C" void clItemBoxManager_UnregisterResponder(clItemBoxManager *self, void *responder)
{
    self->responders.remove_if(bind2nd(equal_to<void *>(), responder));
}

extern "C" void clItemBoxManager_RegisterResponder(clItemBoxManager *self, void *responder)
{
    self->responders.push_back(responder);
}

#pragma auto_inline off
extern "C" void clItemBoxManager_Draw_Inner(clItemBoxManager *self)
{
    ListIter<void *> e;

    if (self->boxes.size == 0) {
        return;
    }
    e = self->boxes.end();
    clItemBoxManager_Bind(0);
    for (ListIter<void *> it = self->boxes.begin(); it != e; ++it) {
        clItemBox_Draw(*it);
    }
    clItemBoxManager_UnbindCurrent();
    clItemBoxManager_Bind(1);
    for (ListIter<void *> it = self->boxes.begin(); it != e; ++it) {
        clItemBox_Draw(*it);
    }
    clItemBoxManager_UnbindCurrent();
    clItemBoxManager_Bind(2);
    for (ListIter<void *> it = self->boxes.begin(); it != e; ++it) {
        clItemBox_Draw(*it);
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
};

#pragma auto_inline off
extern "C" void clItemBoxManager_Update_Inner(clItemBoxManager *self)
{
    ListIter<void *> it;
    ListIter<void *> rt;

    if (!self->active || self->boxes.size == 0) {
        return;
    }
    for (it = self->boxes.begin(); it != self->boxes.end(); ++it) {
        void *box = *it;
        if (clItemBox_Tick(box) != 1) {
            continue;
        }
        for (rt = self->responders.begin(); rt != self->responders.end(); ++rt) {
            void *responder = *rt;
            Vec3 d = *(Vec3 *)clItemBoxResponder_GetBoundPosVec3(responder);
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
    for (rt = self->responders.begin(); rt != self->responders.end(); ++rt) {
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
    return (clItemBoxManager *)lbl_806D10D0;
}

extern "C" clItemBoxManager *SoundDriver_GetOrCreate(void *table)
{
    if (clItemBoxManager_Get() == 0) {
        new clItemBoxManager(table);
    }
    return clItemBoxManager_Get();
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
            if (i != j) {
                Node *lp = j.node->prev;
                i.node->prev->next = lp->next;
                lp->next->prev = i.node->prev;
                while (i != j) {
                    Node *n = i.node;
                    ++i;
                    delete n;
                    size--;
                }
            }
            i = j;
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
        pos.node->prev->next = n;
        n->prev = pos.node->prev;
        pos.node->prev = n;
        n->next = pos.node;
        size++;
        return iterator(n);
    } catch (...) {
        operator delete(h.p);
    }
}

template <class T> ListImpl<T>::ListImpl()
{
    ListHead *h = &head;
    size = 0;
    h->next = h;
    h->prev = h;
}
