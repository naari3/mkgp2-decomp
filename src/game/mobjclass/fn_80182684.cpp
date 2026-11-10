/* JObj material-buffer setters: fn_801826F8 walks a JObj tree recursively,
 * fn_80182990 sets every DObj's MObj buffer with fn_80182684. The calls are
 * auto-inlined into each other (the old split TUs had them hand-expanded):
 * -inline deferred lets a function inline callees defined after it and emits
 * the functions in reverse source order (target: 80182684, 801826F8,
 * 80182954, 80182990), and inline_depth(3) reproduces the target's expansion
 * depth (the deepest level calls the out-of-line copies). */
#include "game/types/HSD_MObj.h"
#include "game/types/HSD_DObj.h"
#include "game/types/HSD_JObj.h"
extern "C" {
HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
void *hsdAllocMemPiece(unsigned int size);
void *memcpy(void *dst, const void *src, unsigned long n);
}
extern unsigned char lbl_80495988[];
#pragma inline_depth(3)
inline HSD_DObj *DObjGetNext(HSD_DObj *dobj) {
    return dobj ? dobj->next : 0;
}
inline HSD_MObj *DObjGetMObj(HSD_DObj *dobj) {
    return dobj ? dobj->mobj : 0;
}
extern "C" void fn_80182684(HSD_MObj *mobj, void *src);
extern "C" void fn_801826F8(HSD_JObj *jobj, void *src);
extern "C" void fn_80182990(HSD_JObj *jobj, void *src);
static inline void *GetSrc(int mode) {
    switch (mode) {
    case 1:
        return lbl_80495988;
    default:
        return 0;
    }
}
extern "C" void fn_80182990(HSD_JObj *jobj, void *src) {
    HSD_DObj *dobj;
    if (jobj != 0 && src != 0) {
        for (dobj = HSD_JObjGetDObj(jobj); dobj != 0; dobj = DObjGetNext(dobj)) {
            fn_80182684(DObjGetMObj(dobj), src);
        }
    }
}
extern "C" void fn_80182954(HSD_JObj *jobj, int mode) {
    fn_801826F8(jobj, GetSrc(mode));
}
extern "C" void fn_801826F8(HSD_JObj *jobj, void *src) {
    HSD_JObj *child;
    if (jobj != 0 && src != 0) {
        fn_80182990(jobj, src);
        if (!(jobj->flags & 0x1000)) {
            for (child = jobj->child; child != 0; child = child->next) {
                fn_801826F8(child, src);
            }
        }
    }
}
extern "C" void fn_80182684(HSD_MObj *mobj, void *src) {
    if (mobj != 0 && src != 0) {
        if (mobj->buf == 0) {
            mobj->buf = hsdAllocMemPiece(0xc);
            if (mobj->buf == 0) {
                return;
            }
        }
        memcpy(mobj->buf, src, 0xc);
    }
}

