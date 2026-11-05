#include "game/anon_80208E30_private.h"

static inline void SetVector(Vec *dst, float x, float y, float z) {
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

extern "C" void fn_802090F0(CollisionObject *o, float hx, float hy, float hz, const Vec *pos, const Vec *rot) {
    o->type = 1;
    o->half.x = hx;
    o->half.y = hy;
    o->half.z = hz;
    SetVector(&o->pos, pos->x, pos->y, pos->z);
    SetVector(&o->rot, rot->x, rot->y, rot->z);
}

extern "C" void CollisionObject_SetPosAndBounds(CollisionObject *o, float hx, float hy, float hz, const Vec *pos,
                                                const Vec *rot) {
    o->type = 1;
    o->half.x = hx;
    o->half.y = hy;
    o->half.z = hz;
    SetVector(&o->pos, pos->x, pos->y, pos->z);
    SetVector(&o->rot, rot->x, rot->y, rot->z);
}
