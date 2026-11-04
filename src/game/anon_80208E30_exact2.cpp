#include "game/anon_80208E30_private.h"

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
