#ifndef SHADOW_TREE_PRIVATE_H
#define SHADOW_TREE_PRIVATE_H
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/dobj.h"
/* Overlay for the parent and transform fields omitted by the partial SDK header. */
typedef struct ShadowJointFields {
    char object[8];
    HSD_JObj *next, *parent, *child;
    unsigned int flags;
    HSD_DObj *dobj;
    float transform[10];
} ShadowJointFields;
extern int lbl_806D15E8, lbl_806D15EC;
extern HSD_DObj *HSD_JObjGetDObj(HSD_JObj *);
extern HSD_DObj *HSD_DObjAlloc(void);
extern void HSD_DObjInsertNext(HSD_DObj *, HSD_DObj *);
extern void HSD_JObjAddDObj(HSD_JObj *, HSD_DObj *);
extern void HSD_DObjRemove(HSD_DObj *);
extern HSD_JObj *HSD_JObjAlloc(void);
extern void HSD_JObjUnref(HSD_JObj *);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);
extern HSD_DObj *fn_801752A8(HSD_DObj *);
extern void fn_80174D94(HSD_JObj *, unsigned char);
extern void fn_80175048(HSD_JObj *, HSD_JObj *, HSD_JObj *, unsigned char);
extern char lbl_806D8E28[8], lbl_806D8E30[8];
extern void __assert(char *, int, char *);
static inline HSD_DObj *ShadowDObjNext(HSD_DObj *d) { return d ? d->next : 0; }
static inline int ShadowHasDObj(HSD_JObj *j) { int result; if (j->flags & 0x4020) result = 0; else result = 1; return result; }
static inline void ShadowSetupMatrix(HSD_JObj *j) {
    if (j) {
        unsigned char dirty;
        if (!j) __assert(lbl_806D8E28, 0x25d, lbl_806D8E30);
        dirty = 0;
        if (!(j->flags & 0x800000) && (j->flags & 0x40)) dirty = 1;
        if (dirty) HSD_JObjSetupMatrixSub(j);
    }
}
#endif
