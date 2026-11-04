/* Shadow-tree traversal expanded to the depth observed in the target. */
#include "src/game/bbox/nokobbox_private.h"
extern unsigned char fn_801375D8(Vec3 *, float);
extern unsigned char fn_801379F0(Vec3 *, float);
extern void fn_80189394(BBox *);
extern void fn_801891C4(BBox *);
void fn_801893BC(BBox *);
static inline void Hide0(BBox *box) {
    fn_80189394(box);
    {
        BBox *c;
        for(c=box->child; c; c=c->next) fn_801891C4(c);
    }
}
static inline void Hide1(BBox *box) {
    ShadowEntry *l;
    for(l=box->head; l; l=l->next) l->dobj->flags |= 1;
    {
        BBox *c;
        for(c=box->child; c; c=c->next) Hide0(c);
    }
}
static inline void Hide2(BBox *box) {
    ShadowEntry *l;
    for(l=box->head; l; l=l->next) l->dobj->flags |= 1;
    {
        BBox *c;
        for(c=box->child; c; c=c->next) Hide1(c);
    }
}
static inline void Hide3(BBox *box) {
    ShadowEntry *l;
    for(l=box->head; l; l=l->next) l->dobj->flags |= 1;
    {
        BBox *c;
        for(c=box->child; c; c=c->next) Hide2(c);
    }
}
static inline void Hide4(BBox *box) {
    ShadowEntry *l;
    for(l=box->head; l; l=l->next) l->dobj->flags |= 1;
    {
        BBox *c;
        for(c=box->child; c; c=c->next) Hide3(c);
    }
}
static inline void Hide5(BBox *box) {
    ShadowEntry *l;
    for(l=box->head; l; l=l->next) l->dobj->flags |= 1;
    {
        BBox *c;
        for(c=box->child; c; c=c->next) Hide4(c);
    }
}
static inline void Hide6(BBox *box) {
    ShadowEntry *l;
    for(l=box->head; l; l=l->next) l->dobj->flags |= 1;
    {
        BBox *c;
        for(c=box->child; c; c=c->next) Hide5(c);
    }
}
static inline void Visible3(BBox *box) {
    if(fn_801375D8(&box->center, box->radius)) {
        {
            ShadowEntry *l;
            for(l=box->head; l; l=l->next) {
                if(!(l->jobj->flags & 0x10)) {
                    if(fn_801379F0(&l->pos,l->radius)) l->dobj->flags &= ~1;
                    else l->dobj->flags |= 1;
                }
            }
        }
        {
            BBox *c;
            for(c=box->child; c; c=c->next) fn_801893BC(c);
        }
    }
    else {
        fn_801891C4(box);
    }
}
static inline void Visible2(BBox *box) {
    if(fn_801375D8(&box->center, box->radius)) {
        {
            ShadowEntry *l;
            for(l=box->head; l; l=l->next) {
                if(!(l->jobj->flags & 0x10)) {
                    if(fn_801379F0(&l->pos,l->radius)) l->dobj->flags &= ~1;
                    else l->dobj->flags |= 1;
                }
            }
        }
        {
            BBox *c;
            for(c=box->child; c; c=c->next) Visible3(c);
        }
    }
    else {
        Hide0(box);
    }
}
static inline void Visible1(BBox *box) {
    if(fn_801375D8(&box->center, box->radius)) {
        {
            ShadowEntry *l;
            for(l=box->head; l; l=l->next) {
                if(!(l->jobj->flags & 0x10)) {
                    if(fn_801379F0(&l->pos,l->radius)) l->dobj->flags &= ~1;
                    else l->dobj->flags |= 1;
                }
            }
        }
        {
            BBox *c;
            for(c=box->child; c; c=c->next) Visible2(c);
        }
    }
    else {
        Hide1(box);
    }
}
#pragma auto_inline off
void fn_801893BC(BBox *box) {
    if(fn_801375D8(&box->center, box->radius)) {
        {
            ShadowEntry *l;
            for(l=box->head; l; l=l->next) {
                if(!(l->jobj->flags & 0x10)) {
                    if(fn_801379F0(&l->pos,l->radius)) l->dobj->flags &= ~1;
                    else l->dobj->flags |= 1;
                }
            }
        }
        {
            BBox *c;
            for(c=box->child; c; c=c->next) Visible1(c);
        }
    }
    else {
        Hide6(box);
    }
}
#pragma auto_inline reset
