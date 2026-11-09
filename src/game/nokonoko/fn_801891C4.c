/* Shadow-tree visibility: Visible (fn_801893BC) recurses into the children and
 * hides a culled subtree with Hide (fn_801891C4), which clears every list with
 * HideList (fn_80189394). The calls are auto-inlined into each other: the TU is
 * built with -inline deferred (which also emits the functions in reverse source
 * order, giving the target's Hide, HideList, Visible) and an inline depth of 7,
 * which reproduces the expansion depth of both recursive functions. */
#include "src/game/bbox/nokobbox_private.h"
extern unsigned char fn_801375D8(Vec3 *, float);
extern unsigned char fn_801379F0(Vec3 *, float);
#pragma inline_depth(7)
void fn_80189394(BBox *);
void fn_801891C4(BBox *);

void fn_801893BC(BBox *box) {
    if (fn_801375D8(&box->center, box->radius)) {
        {
            ShadowEntry *l;
            for (l = box->head; l; l = l->next) {
                if (!(l->jobj->flags & 0x10)) {
                    if (fn_801379F0(&l->pos, l->radius)) l->dobj->flags &= ~1;
                    else l->dobj->flags |= 1;
                }
            }
        }
        {
            BBox *c;
            for (c = box->child; c; c = c->next) fn_801893BC(c);
        }
    } else {
        fn_801891C4(box);
    }
}

void fn_80189394(BBox *box) {
    ShadowEntry *l;
    for (l = box->head; l; l = l->next) l->dobj->flags |= 1;
}

void fn_801891C4(BBox *box) {
    fn_80189394(box);
    {
        BBox *c;
        for (c = box->child; c; c = c->next) fn_801891C4(c);
    }
}
