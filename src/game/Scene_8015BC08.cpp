/* 0x8015BC08..0x8015BCC4: deleting destructor of the debug model viewer scene. */

struct Viewer {
    virtual ~Viewer();
};

struct ViewerScene {
    void *vtable;
};

extern "C" {
extern Viewer *lbl_806D1588;
extern void *lbl_806D158C;
extern char lbl_80490064[];
extern char lbl_803FE0C8[];
extern void GXDrawDone(void);
extern void Object_DtorWithGXSync(void *, int);
extern void fn_80121210(void);
extern void MemoryManager_TimedFree(void *);

#pragma exceptions on

ViewerScene *fn_8015BC08(ViewerScene *self, short flag) {
    if (self) {
        self->vtable = lbl_80490064;
        GXDrawDone();
        if (lbl_806D1588) {
            delete lbl_806D1588;
            lbl_806D1588 = 0;
        }
        if (lbl_806D158C) {
            Object_DtorWithGXSync(lbl_806D158C, 1);
            lbl_806D158C = 0;
        }
        fn_80121210();
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
