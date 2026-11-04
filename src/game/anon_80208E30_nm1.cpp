#include "game/anon_80208E30_private.h"

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
