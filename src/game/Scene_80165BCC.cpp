/*
 * 0x80165BCC..0x80165E90: helpers around the object built by fn_801654E0
 * (virtual-delete thunks, factory, deleting destructors of two scenes on the
 * lbl_8048ED10 -> lbl_8048ECF8 base chain, and update/draw forwarders).
 */

struct VObj {
    virtual ~VObj();
};

struct VObjPad {
    char pad[0x14];
};

struct Model : VObjPad {
    virtual ~Model();
    virtual void M1();
    virtual void M2();
    virtual void Update();
    virtual void Animate();
    virtual void Draw();
};

struct ModelState {
    char pad00[4];
    unsigned char finished;
};

struct Obj801654E0 {
    char _opaque[0x14];
    Obj801654E0(void *a, void *b);
};

struct Scene80165C98 {
    void *vtable;
    char pad04[8];
    int finished;
    char pad10[4];
    Model *model;
};

#pragma exceptions on

extern "C" {
extern char lbl_80490EB4[];
extern char lbl_80490EE0[];
extern char lbl_8048ED10[];
extern char lbl_8048ECF8[];
extern void fn_80121210(void);
extern void MemoryManager_TimedFree(void *);

void fn_80165BCC(VObj *p) {
    delete p;
}

Obj801654E0 *fn_80165C04(void *a, void *b) {
    return new Obj801654E0(a, b);
}

void fn_80165C60(VObj *p) {
    delete p;
}

Scene80165C98 *fn_80165C98(Scene80165C98 *self, short flag) {
    if (self) {
        self->vtable = lbl_80490EB4;
        if (self->model) {
            delete self->model;
        }
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

void fn_80165D38(Scene80165C98 *self) {
    if (self->model) {
        self->model->Update();
        self->model->Animate();
        if (((ModelState *)self->model)->finished) {
            self->finished = 1;
        }
    }
}

void fn_80165DA8(Scene80165C98 *self) {
    self->model->Draw();
}

void fn_80165DD8(VObj *p) {
    delete p;
}

Scene80165C98 *fn_80165E10(Scene80165C98 *self, short flag) {
    if (self) {
        self->vtable = lbl_80490EE0;
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
}

#pragma exceptions reset
