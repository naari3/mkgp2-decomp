/*
 * 0x8016700C..0x801670FC: child release forwarder, virtual-delete thunk and
 * the deleting destructor of a scene (vtable lbl_80490F9C, base chain
 * lbl_8048ED10 -> lbl_8048ECF8).
 */

struct VObj {
    virtual ~VObj();
    virtual void M1();
    virtual void Release();
};

struct Scene8016707C {
    void *vtable;
    char pad04[0x24];
    VObj *obj28;
};

extern "C" {
extern char lbl_80490F9C[];
extern char lbl_8048ED10[];
extern char lbl_8048ECF8[];
extern void fn_80121210(void);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

void fn_8016700C(Scene8016707C *self) {
    if (self->obj28) {
        self->obj28->Release();
    }
}

void fn_80167044(VObj *p) {
    delete p;
}

Scene8016707C *fn_8016707C(Scene8016707C *self, short flag) {
    if (self) {
        self->vtable = lbl_80490F9C;
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
