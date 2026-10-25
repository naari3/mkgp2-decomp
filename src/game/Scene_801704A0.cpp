/*
 * 0x801704A0..0x80170544: deleting destructor of a two-model course object
 * (vtable lbl_80491264, base vtable lbl_80490FE0).
 */

struct CourseTwoModels {
    void *vtable;
    char pad04[0x8];
    void *modelA;
    void *modelB;
};

extern "C" {
extern char lbl_80491264[];
extern char lbl_80490FE0[];
extern char lbl_8036E138[];
void Object_DtorWithGXSync(void *, int);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);

CourseTwoModels *fn_801704A0(CourseTwoModels *self, short flag) {
    if (self) {
        self->vtable = lbl_80491264;
        if (self->modelA) {
            Object_DtorWithGXSync(self->modelA, 1);
        }
        if (self->modelB) {
            Object_DtorWithGXSync(self->modelB, 1);
        }
        DebugPrintf(lbl_8036E138);
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
