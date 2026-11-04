#include "game/Collision.h"

/*
 * Collision manager (0x80208E30..0x80209330): two lists of object chains,
 * tested pairwise once per frame, plus the object setup helpers.
 */

extern "C" {
void fn_802086AC(void *self, CollisionObject *a, CollisionObject *b);
extern Vec lbl_803C2808;
extern Vec lbl_803C2814;
}

struct PtrVecData {
    int cap;
    int count;
    CollisionObject **data;
    ~PtrVecData() {
        if (data) {
            operator delete(data);
        }
    }
};

struct PtrVecBase : PtrVecData {
    ~PtrVecBase() {}
};

struct PtrVec : PtrVecBase {
    PtrVec();
    ~PtrVec() {}
    CollisionObject **begin() { return data; }
    CollisionObject **end() { return data + count; }
    CollisionObject **erase(CollisionObject **pos);
};

extern "C" void PtrVec_InsertFill(PtrVec *v, CollisionObject **pos, int n, CollisionObject **val);

struct CollisionMgr {
    PtrVec lists[2];
    CollisionMgr();
    ~CollisionMgr();
    void Update();
    void Add(CollisionObject *obj, int list);
};

