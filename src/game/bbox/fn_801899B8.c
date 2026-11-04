/* Octree shadow entries: reconstructed from the target and adjacent box methods. */
#include "src/game/bbox/nokobbox_private.h"
extern Vec3 lbl_80495D48[8];
extern const float lbl_806D9358;
extern int lbl_806D1690;
extern void *Alloc(unsigned int);
extern void fn_80189808(BBox *, int);
static inline ShadowEntry *NewEntry(FlagObject *jobj, FlagObject *dobj, Vec3 *pos, float radius) {
    ShadowEntry *l = (ShadowEntry *)Alloc(sizeof(ShadowEntry));
    if (l) {
        lbl_806D1690++;
        l->next = 0;
        l->dobj = dobj;
        l->pos.x = pos->x;
        l->pos.y = pos->y;
        l->pos.z = pos->z;
        l->radius = radius;
        l->jobj = jobj;
    }
    return l;
}
static inline int FindOctant(BBox *box, Vec3 *pos, float radius) {
    float cx, hz, hy, hx;
    hx = lbl_806D9358 * (box->max.x - box->min.x);
    hy = lbl_806D9358 * (box->max.y - box->min.y);
    hz = lbl_806D9358 * (box->max.z - box->min.z);
    for (box->cursor = 0; box->cursor < 8; box->cursor++) {
        int oct = box->cursor;
        float cy, cz;
        cx = hx * lbl_80495D48[oct].x + box->center.x;
        cy = hy * lbl_80495D48[oct].y + box->center.y;
        cz = hz * lbl_80495D48[oct].z + box->center.z;
        if (pos->x - radius > cx - hx && pos->y - radius > cy - hy && pos->z - radius > cz - hz && pos->x + radius < cx + hx && pos->y + radius < cy + hy && pos->z + radius < cz + hz) return oct;
    }
    return -1;
}
#pragma auto_inline off
void fn_801899B8(BBox *box, FlagObject *jobj, FlagObject *dobj, Vec3 *pos, float radius) {
    int oct = FindOctant(box, pos, radius);
    if (oct >= 0) {
        BBox *c;
        fn_80189808(box, oct);
        for (c = box->child; c; c = c->next) {
            if ((c->oct & 0xf) == oct) {
                fn_801899B8(c, jobj, dobj, pos, radius);
                return;
            }
        }
    }
    if (!box->head) box->head = NewEntry(jobj, dobj, pos, radius);
    else {
        ShadowEntry *l = box->head;
        while (l->next) l = l->next;
        l->next = NewEntry(jobj, dobj, pos, radius);
    }
}
#pragma auto_inline reset
