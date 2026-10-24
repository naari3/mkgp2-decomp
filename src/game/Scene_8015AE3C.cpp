/*
 * 0x8015AE3C..0x8015AFCC: deleting destructor of the scene object built by
 * fn_8015AFCC (vtable lbl_8049003C, base vtable lbl_803FE0C8).
 */

struct VObj {
    virtual ~VObj();
    virtual void Update();
};

struct VObjPad {
    char pad[0x14];
};

struct VObj14 : VObjPad {
    virtual ~VObj14();
};

struct Scene8015AFCC {
    void *vtable;
    char pad04[0x20];
    VObj *obj24;
    char pad28[4];
    VObj *obj2C;
    VObj *obj30;
    VObj14 *obj34;
    VObj14 *obj38;
    VObj14 *obj3C;
    VObj14 *obj40;
};

extern "C" {
extern char lbl_8049003C[];
extern char lbl_803FE0C8[];
extern void MemoryManager_TimedFree(void *);
extern void fn_80121210(void);
extern void fn_8013DB9C(void);
extern unsigned char fn_8019083C(int);
extern int fn_801932F8(void);
extern void clStream_setVolume(int, int);
extern void fn_801699D8(int, int);
extern void fn_80169C44(void);

#pragma exceptions on

Scene8015AFCC *fn_8015AE3C(Scene8015AFCC *self, short flag) {
    if (self) {
        self->vtable = lbl_8049003C;
        fn_80121210();
        fn_8013DB9C();
        if (fn_8019083C(1)) {
            clStream_setVolume(1, fn_801932F8());
        }
        if (self->obj2C) {
            self->obj2C->Update();
        }
        if (self->obj30) {
            self->obj30->Update();
        }
        if (self->obj34) {
            delete self->obj34;
        }
        if (self->obj38) {
            delete self->obj38;
        }
        if (self->obj3C) {
            delete self->obj3C;
        }
        if (self->obj40) {
            delete self->obj40;
        }
        if (self->obj24) {
            delete self->obj24;
        }
        fn_801699D8(1, 0);
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

#pragma exceptions reset
}
