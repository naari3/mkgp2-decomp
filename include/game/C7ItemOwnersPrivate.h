#ifndef C7_ITEM_OWNERS_PRIVATE_H
#define C7_ITEM_OWNERS_PRIVATE_H
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void*);
/* Each effect has its own owning-pointer type and throw() EH region.
 * The virtual interface is shared: reset, tick, deleting destructor. */
template<int N> struct C7Effect {
    virtual void Init();
    virtual void Tick();
    virtual ~C7Effect();
};
template<class T> struct C7Owner {
    T* p;
    C7Owner(T* value):p(value) {}
    ~C7Owner() throw() { delete p; }
};
struct C7ItemOwners {
    void* kart;
    C7Owner<C7Effect<0> > impact;
    C7Owner<C7Effect<1> > quake;
    C7Owner<C7Effect<2> > jump;
    C7Owner<C7Effect<3> > damp;
    C7Owner<C7Effect<4> > spin;
    int state;
    C7ItemOwners(void*);
    ~C7ItemOwners();
};
struct C7SpeedOwners {
    char state[0x20];
    C7Owner<C7Effect<5> > first;
    C7Owner<C7Effect<6> > second;
    ~C7SpeedOwners();
};
#endif
