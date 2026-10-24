typedef struct RenderTarget RenderTarget;

typedef struct RenderTargetVtbl {
    void *slots[20];
    void (*release)(RenderTarget *, int handle);
} RenderTargetVtbl;

struct RenderTarget {
    RenderTargetVtbl *vtbl;
};

typedef struct RenderOwner {
    unsigned char pad[8];
    RenderTarget *target;
} RenderOwner;

typedef struct RenderSession {
    unsigned char pad[4];
    RenderOwner *owner;
    int handle;
    unsigned char active;
} RenderSession;

extern void fn_802C22D8(int);
extern void fn_802BCF94(int);
extern void fn_802CAEA0(void);
extern void fn_802C14B8(int);
extern void MemoryManager_TimedFree(void *);

RenderSession *dtor_8007D9C4(RenderSession *self, short flags) {
    if (self != 0) {
        if (self->active == 1) {
            RenderTarget *target = self->owner->target;

            target->vtbl->release(target, self->handle);
            fn_802C22D8(0);
            fn_802BCF94(0);
            fn_802CAEA0();
            fn_802C14B8(-1);
            self->active = 0;
        }
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
