/*
 * 0x801636B4..0x80163804: draw / update forwarders and deleting destructor
 * of a course loader scene (vtable lbl_80490DF8), plus a virtual-delete thunk.
 */

struct VObj {
    virtual ~VObj();
};

struct Scene801636B4 {
    void *vtable;
    unsigned char done;
    char pad05[3];
    void *child;
};

extern "C" {
extern char lbl_80490DF8[];
extern char lbl_803FE0C8[];
extern void fn_80163C68(void *);
extern unsigned char fn_80163EF4(void *);
extern void fn_801638B4(void *, int);
extern void SetCourseScene3D(int);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

void fn_801636B4(Scene801636B4 *self) {
    if (!self->done && self->child) {
        fn_80163C68(self->child);
    }
}

void fn_801636EC(Scene801636B4 *self) {
    if (!self->done && self->child) {
        if (fn_80163EF4(self->child) == 1) {
            self->done = 1;
        }
    }
}

Scene801636B4 *fn_80163744(Scene801636B4 *self, short flag) {
    if (self) {
        self->vtable = lbl_80490DF8;
        SetCourseScene3D(0);
        if (self->child) {
            fn_801638B4(self->child, 1);
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

void fn_801637CC(VObj *p) {
    delete p;
}

#pragma exceptions reset
}
