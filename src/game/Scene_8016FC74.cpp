/*
 * 0x8016FC74..0x8016FD0C: deleting destructor of a course model object
 * with a looping SE (vtable lbl_8049123C, base vtable lbl_80490FE0).
 */

struct CourseModel {
    void *vtable;
    void *model;
};

extern "C" {
extern char lbl_8049123C[];
extern char lbl_80490FE0[];
extern char lbl_8036E0C8[];
int fn_8016C394(int);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);

CourseModel *fn_8016FC74(CourseModel *self, short flag) {
    if (self) {
        self->vtable = lbl_8049123C;
        fn_8016C394(0x34);
        if (self->model) {
            Object_DtorWithGXSync(self->model, 1);
        }
        DebugPrintf(lbl_8036E0C8);
        if (self) {
            self->vtable = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}
