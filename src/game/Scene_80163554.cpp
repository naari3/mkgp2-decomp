/*
 * 0x80163554..0x80163614: deleting dtor of a small holder object, a byte
 * getter, and a virtual-delete thunk.
 */

struct VObj {
    virtual ~VObj();
};

struct Holder80163554 {
    void *vtable;
    void *child;
    unsigned char done;
};

extern "C" {
extern char lbl_80490DAC[];
extern char lbl_8048FF80[];
extern void MemoryManager_TimedFree(void *);
extern void fn_801638B4(void *, int);

#pragma exceptions on

Holder80163554 *fn_80163554(Holder80163554 *self, short flag) {
    if (self) {
        self->vtable = lbl_80490DAC;
        if (self->child) {
            fn_801638B4(self->child, 1);
        }
        if (self) {
            self->vtable = lbl_8048FF80;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

unsigned char fn_801635D4(Holder80163554 *self) {
    return self->done;
}

void fn_801635DC(VObj *p) {
    delete p;
}

#pragma exceptions reset
}
