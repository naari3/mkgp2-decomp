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

extern "C" void fn_802090F0(CollisionObject *o, float hx, float hy, float hz, const Vec *pos, const Vec *rot) {
    o->type = 1;
    o->half.x = hx;
    o->half.y = hy;
    o->half.z = hz;
    o->pos = *pos;
    o->rot = *rot;
}

extern "C" void CollisionObject_SetPosAndBounds(CollisionObject *o, float hx, float hy, float hz, const Vec *pos,
                                                const Vec *rot) {
    o->type = 1;
    o->half.x = hx;
    o->half.y = hy;
    o->half.z = hz;
    o->pos.x = pos->x;
    o->pos.y = pos->y;
    o->pos.z = pos->z;
    o->rot.x = rot->x;
    o->rot.y = rot->y;
    o->rot.z = rot->z;
}

CollisionObject::~CollisionObject() {}

extern "C" void fn_802091BC(CollisionObject *o, int type, int field2C) {
    o->next = 0;
    o->type = type;
    o->field2C = field2C;
    o->pos.x = 0.0f;
    o->pos.y = 0.0f;
    o->pos.z = 0.0f;
    o->radius = 0.0f;
    o->half.x = 0.0f;
    o->half.y = 0.0f;
    o->half.z = 0.0f;
    o->rot.x = 0.0f;
    o->rot.y = 0.0f;
    o->rot.z = 0.0f;
    Vec zero = lbl_803C2808;
    o->hit = 0;
    o->depth = 0.0f;
    o->normal = zero;
    o->contact = zero;
    o->other = 0;
}

static inline CollisionObject **PtrCopy(CollisionObject **first, CollisionObject **last, CollisionObject **out) {
    while (first < last) {
        *out++ = *first++;
    }
    return out;
}

PtrVec::PtrVec() {
    cap = 0;
    count = 0;
    data = 0;
}

CollisionObject **PtrVec::erase(CollisionObject **pos) {
    CollisionObject **e = end();
    if (e - pos - 1 != 0) {
        PtrCopy(pos + 1, e, pos);
    }
    count--;
    return pos;
}
