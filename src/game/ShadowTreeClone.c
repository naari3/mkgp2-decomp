#include "game/ShadowTree_private.h"
void fn_80175048(HSD_JObj *src, HSD_JObj *dst, HSD_JObj *parent, unsigned char root) {
    ShadowJointFields *s = (ShadowJointFields *)src;
    ShadowJointFields *d = (ShadowJointFields *)dst;
    if (!src || !dst || !parent) return;
    d->parent = parent;
    dst->flags = src->flags | 0x40;
    if (!root) {
        d->transform[0] = s->transform[0]; d->transform[1] = s->transform[1];
        d->transform[2] = s->transform[2]; d->transform[3] = s->transform[3];
        d->transform[4] = s->transform[4]; d->transform[5] = s->transform[5];
        d->transform[6] = s->transform[6]; d->transform[7] = s->transform[7];
        d->transform[8] = s->transform[8]; d->transform[9] = s->transform[9];
    }
    if (ShadowHasDObj(src)) {
        HSD_DObj *p = HSD_JObjGetDObj(src);
        HSD_DObj *prev = 0;
        while (p) {
            HSD_DObj *copy = HSD_DObjAlloc();
            lbl_806D15EC++;
            if (!prev) HSD_JObjAddDObj(dst, copy);
            else HSD_DObjInsertNext(prev, copy);
            copy->flags = p->flags;
            copy->mobj = p->mobj;
            copy->pobj = p->pobj;
            prev = copy;
            p = ShadowDObjNext(p);
        }
    } else if (src->flags & 0x4000) dst->dobj = src->dobj;
    else if (src->flags & 0x20) dst->dobj = src->dobj;
    ShadowSetupMatrix(dst);
    if (src->flags & 0x1000) dst->child = src->child;
    else if (src->child) {
        dst->child = HSD_JObjAlloc();
        lbl_806D15E8++;
        fn_80175048(src->child, dst->child, dst, 0);
    } else dst->child = 0;
    if (!root && src->next) {
        dst->next = HSD_JObjAlloc();
        lbl_806D15E8++;
        fn_80175048(src->next, dst->next, parent, 0);
    } else dst->next = 0;
}

