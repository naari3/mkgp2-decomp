#include "game/anon_80208E30_private.h"

void CollisionMgr::Update() {
    PtrVec *v = lists;
    for (int i = 0; i < 2; i++, v++) {
        Vec zero = lbl_803C2814;
        for (CollisionObject **p = v->begin(); p != v->end(); p++) {
            for (CollisionObject *o = *p; o; o = o->next) {
                o->hit = 0;
                o->depth = 0.0f;
                o->normal = zero;
                o->contact = zero;
                o->other = 0;
            }
        }
    }
    CollisionObject *a;
    CollisionObject *b;
    int i;
    CollisionObject **it;
    CollisionObject **jt;
    for (i = 0; i < 2; i++) {
        PtrVec &v = lists[i];
        it = v.begin();
        while (it != v.end()) {
            for (jt = it + 1; jt != v.end(); jt++) {
                for (a = *it; a; a = a->next) {
                    for (b = *jt; b; b = b->next) {
                        fn_802086AC(this, a, b);
                    }
                }
            }
            it = v.erase(it);
        }
    }
}


void CollisionMgr::Add(CollisionObject *obj, int list) {
    PtrVec &v = lists[list];
    PtrVec_InsertFill(&v, v.end(), 1, &obj);
}

CollisionMgr::~CollisionMgr() {}

CollisionMgr::CollisionMgr() {}
