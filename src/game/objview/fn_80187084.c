#include "game/objview/path186_private.h"
extern void fn_80181EA4(Vec3f *, Vec3f *, Vec3f *, Vec3f *, float);
extern void Vec3_Subtract(Vec3f *, Vec3f *, Vec3f *);
extern double atan2(double, double);
/* Point storage and cyclic bounds are separate inputs to the lookup. */
static inline Vec3f *CyclicPoint(Path186 *path, int count, int index) {
    if (index >= count) index -= count;
    return &path->points[index];
}
void fn_80187084(View186 *self) {
    int i;
    Path186 *p;
    Vec3f old, delta;
    if (self->object == 0 || self->paths == 0) return;
    for (i = 0; i < 2; i++) {
        p = &self->paths[i];
        p->time += 0.0033333334140479565f;
        if (p->time > 1.0f) {
            p->time -= 1.0f;
            p->index++;
            if (p->index >= p->count) p->index = 0;
            { Vec3f *v = CyclicPoint(p, p->count, p->index); p->a.x = v->x; p->a.y = v->y; p->a.z = v->z; }
            { Vec3f *v = CyclicPoint(p, p->count, p->index+1); p->b.x = v->x; p->b.y = v->y; p->b.z = v->z; }
            { Vec3f *v = CyclicPoint(p, p->count, p->index+2); p->c.x = v->x; p->c.y = v->y; p->c.z = v->z; }
            p->a.x = 0.5f * (p->a.x + p->b.x);
            p->a.y = 0.5f * (p->a.y + p->b.y);
            p->a.z = 0.5f * (p->a.z + p->b.z);
            p->c.x = 0.5f * (p->b.x + p->c.x);
            p->c.y = 0.5f * (p->b.y + p->c.y);
            p->c.z = 0.5f * (p->b.z + p->c.z);
        }
        old = p->position;
        fn_80181EA4(&p->a, &p->b, &p->c, &p->position, p->time);
        Vec3_Subtract(&p->position, &old, &delta);
        p->yaw = (float)atan2(delta.x, delta.z);
    }
    self->rotation += 0.2617993950843811f;
    if (self->rotation >= 6.2831854820251465f) self->rotation -= 6.2831854820251465f;
    self->phase += 0.002f;
    if (self->phase >= 1.0f) self->phase -= 1.0f;
    self->phase2 += 0.0002f;
    if (self->phase2 >= 1.0f) self->phase2 -= 1.0f;
}
