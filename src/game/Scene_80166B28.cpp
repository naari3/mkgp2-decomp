/*
 * 0x80166B28..0x80166BE8: empty virtual stub, virtual-delete thunk and the
 * deleting destructor of a scene (vtable DebugName163_vtable_80490F70, base chain
 * lbl_8048ED10 -> lbl_8048ECF8).
 */

#include "game/types/VObj.h"

struct Scene80166B64 {
    void *vtable;
};

extern "C" {
extern char DebugName163_vtable_80490F70[];
extern char lbl_8048ED10[];
extern char lbl_8048ECF8[];
extern void fn_80252D48(void);
extern void fn_80121210(void);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

void fn_80166B28(void) {
}

void fn_80166B2C(VObj *p) {
    delete p;
}

Scene80166B64 *fn_80166B64(Scene80166B64 *self, short flag) {
    if (self) {
        self->vtable = DebugName163_vtable_80490F70;
        fn_80252D48();
        fn_80121210();
        if (self) {
            self->vtable = lbl_8048ED10;
            if (self) {
                self->vtable = lbl_8048ECF8;
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
}
