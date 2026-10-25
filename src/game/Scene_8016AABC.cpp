/*
 * 0x8016AABC..0x8016AB58: deleting destructor of a course object (vtable
 * lbl_80491054, base vtable lbl_80490FE0).
 */

struct CourseObj8016AABC {
    void *vtable;
    void *model;
    void *anim;
    void *buffer;
};

extern "C" {
extern char lbl_80491054[];
extern char lbl_80490FE0[];
extern char lbl_8036CF24[];
extern void Object_DtorWithGXSync(void *, int);
extern void fn_80123B48(void *, int);
extern void MemoryManager_Free(void *);
extern void MemoryManager_TimedFree(void *);
extern void DebugPrintf(const char *, ...);

#pragma exceptions on

CourseObj8016AABC *fn_8016AABC(CourseObj8016AABC *self, short flag) {
    if (self) {
        self->vtable = lbl_80491054;
        Object_DtorWithGXSync(self->model, 1);
        fn_80123B48(self->anim, 1);
        MemoryManager_Free(self->buffer);
        DebugPrintf(lbl_8036CF24);
        if (self) {
            self->vtable = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
}
