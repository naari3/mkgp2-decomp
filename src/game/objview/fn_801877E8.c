#include "game/types/ObjView.h"

extern char ObjView_vtable_80495BE4[];
extern char lbl_80490FE0[];
extern const char lbl_80377304[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_801877E8(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = ObjView_vtable_80495BE4;
        if (self->child != 0) {
            Object_DtorWithGXSync(self->child, 1);
        }
        DebugPrintf(lbl_80377304);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
