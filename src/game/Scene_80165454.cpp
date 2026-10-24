/* 0x80165454..0x801654E0: deleting destructor of a scene (vtable lbl_80490E1C). */

struct VObj {
    virtual ~VObj();
    virtual void Release();
};

struct Scene80165454 {
    void *vtable;
    char pad04[0xC];
    VObj *obj10;
};

extern "C" {
extern char lbl_80490E1C[];
extern char lbl_803FE0C8[];
extern void fn_80121210(void);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

Scene80165454 *fn_80165454(Scene80165454 *self, short flag) {
    if (self) {
        self->vtable = lbl_80490E1C;
        fn_80121210();
        if (self->obj10) {
            self->obj10->Release();
        }
        if (self) {
            self->vtable = lbl_803FE0C8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
}
