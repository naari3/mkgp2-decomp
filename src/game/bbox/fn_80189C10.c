/* Octree shadow entries: reconstructed from the target and adjacent box methods. */
#include "src/game/bbox/nokobbox_private.h"
extern const float lbl_806D935C;
extern int lbl_806D1690, lbl_806D1694;
extern void fn_80189950(BBox *);
extern void MemoryManager_TimedFree(void *);
extern BBox *dtor_8018A0A8(BBox *, short);
static inline void ClearBounds(BBox *box) {
    box->min.x = lbl_806D935C;
    box->min.y = lbl_806D935C;
    box->min.z = lbl_806D935C;
    box->max.x = lbl_806D935C;
    box->max.y = lbl_806D935C;
    box->max.z = lbl_806D935C;
    box->radius = lbl_806D935C;
}
static inline void ClearEntries(BBox *box) {
    ShadowEntry *l = box->head;
    while (l) {
        ShadowEntry *next = l->next;
        if (l) {
            lbl_806D1690--;
            MemoryManager_TimedFree(l);
        }
        l = next;
    }
    box->head = 0;
}
static inline void DeleteInner(BBox *box) {
    if (box) {
        if (box->next) {
            dtor_8018A0A8(box->next, 1);
            box->next = 0;
        }
        if (box->child) {
            dtor_8018A0A8(box->child, 1);
            box->child = 0;
        }
        fn_80189950(box);
        ClearBounds(box);
        lbl_806D1694--;
        MemoryManager_TimedFree(box);
    }
}
static inline void DeleteOuter(BBox *box) {
    if (box) {
        if (box->next) {
            DeleteInner(box->next);
            box->next = 0;
        }
        if (box->child) {
            DeleteInner(box->child);
            box->child = 0;
        }
        ClearEntries(box);
        ClearBounds(box);
        lbl_806D1694--;
        MemoryManager_TimedFree(box);
    }
}
#pragma auto_inline off
void fn_80189C10(BBox *box) {
    if (box->next) {
        DeleteOuter(box->next);
        box->next = 0;
    }
    if (box->child) {
        DeleteOuter(box->child);
        box->child = 0;
    }
    ClearEntries(box);
    ClearBounds(box);
}
#pragma auto_inline reset
