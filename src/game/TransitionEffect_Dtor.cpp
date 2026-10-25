/* TransitionEffect_Dtor @ 0x8007E390: deleting destructor of the screen
 * transition effect; frees its five work buffers and its overlay object. */

void operator delete(void *p) throw();

extern "C" void Object_DtorWithGXSync(void *obj, int flag);
extern "C" void *lbl_803FE37C[];
extern "C" void *lbl_803FE3C0[];

struct TransitionOverlay {
    void *object;

    ~TransitionOverlay() throw();
};

inline TransitionOverlay::~TransitionOverlay() throw()
{
    Object_DtorWithGXSync(object, 1);
}

struct TransitionOverlayHolder {
    TransitionOverlay *p;

    ~TransitionOverlayHolder()
    {
        TransitionOverlay *q = p;

        if (q != 0) {
            q->~TransitionOverlay();
            operator delete(q);
        }
    }
};

struct TransitionBuffer {
    void *p;

    ~TransitionBuffer()
    {
        if (p != 0) {
            delete p;
        }
    }
};

struct TransitionEffect {
    void **vtable;
    TransitionBuffer buf4;
    TransitionBuffer buf8;
    TransitionBuffer bufC;
    TransitionBuffer buf10;
    TransitionBuffer buf14;
    TransitionOverlayHolder overlay;
};

extern "C" TransitionEffect *TransitionEffect_Dtor(TransitionEffect *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_803FE37C;
        (&self->overlay)->~TransitionOverlayHolder();
        (&self->buf14)->~TransitionBuffer();
        (&self->buf10)->~TransitionBuffer();
        (&self->bufC)->~TransitionBuffer();
        (&self->buf8)->~TransitionBuffer();
        (&self->buf4)->~TransitionBuffer();
        if (self != 0) {
            self->vtable = lbl_803FE3C0;
        }
        if (flag > 0) {
            operator delete(self);
        }
    }
    return self;
}
