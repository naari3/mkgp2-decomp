#ifndef C7_ITEM_CTOR_PRIVATE_H
#define C7_ITEM_CTOR_PRIVATE_H
#include "game/C7ItemOwnersPrivate.h"
struct C7Vec { float x,y,z; C7Vec() {} ~C7Vec() {} };
struct C7FxBase {
    virtual void Init();
    virtual void Tick();
    virtual ~C7FxBase();
    C7ItemOwners* owner;
    C7FxBase() {}
};
struct C7Impact : C7FxBase {
    virtual void Init();
    C7Vec pos;
    char matrices[0xC4];
    C7Vec velocity;
    char tail[8];
    C7Impact(C7ItemOwners* o) { owner=o; Init(); }
};
struct C7Quake : C7FxBase {
    virtual void Init();
    C7Vec pos;
    int timer;
    C7Vec axis;
    char tail[0x84];
    C7Quake(C7ItemOwners* o) { owner=o; Init(); }
};
struct C7Jump : C7FxBase {
    virtual void Init();
    C7Vec pos;
    char matrices[0xC0];
    C7Vec velocity;
    int timer;
    C7Jump(C7ItemOwners* o) { owner=o; Init(); }
};
struct C7Damp : C7FxBase {
    virtual void Init();
    C7Vec pos;
    char tail[0xC];
    C7Damp(C7ItemOwners* o) { owner=o; Init(); }
};
struct C7Spin : C7FxBase {
    virtual void Init();
    C7Vec pos;
    char matrices[0x8C];
    int timer;
    C7Spin(C7ItemOwners* o) { owner=o; timer=0; Init(); }
};
#endif
