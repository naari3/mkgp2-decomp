/*
 * 0x80162B00..0x80162C3C: deleting destructors of a scene (vtable
 * lbl_80490AFC) and of a credit-slot holder (vtable lbl_80490B34), plus a
 * virtual-delete thunk.
 */

struct VObj {
    virtual ~VObj();
};

struct VObjPad {
    char pad[0x14];
};

struct VObj14 : VObjPad {
    virtual ~VObj14();
};

struct Scene80162B00 {
    void *vtable;
    char pad04[4];
    VObj14 *model;
};

struct CreditHolder {
    char pad00[0x14];
    void *vtable;
};

extern "C" {
extern char lbl_80490AFC[];
extern char lbl_80490B34[];
extern char lbl_803FE0C8[];
extern void fn_80121210(void);
extern void fn_80169C44(void);
extern void CreditMgr_SetActiveSlot(int);
extern void dtor_80147584(void *, int);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

Scene80162B00 *fn_80162B00(Scene80162B00 *self, short flag) {
    if (self) {
        self->vtable = lbl_80490AFC;
        fn_80121210();
        if (self->model) {
            delete self->model;
        }
        fn_80169C44();
        if (self) {
            self->vtable = lbl_803FE0C8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

CreditHolder *fn_80162B98(CreditHolder *self, short flag) {
    if (self) {
        self->vtable = lbl_80490B34;
        CreditMgr_SetActiveSlot(0);
        dtor_80147584(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_80162C04(VObj *p) {
    delete p;
}

#pragma exceptions reset
}
