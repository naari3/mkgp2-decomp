#pragma cplusplus on
struct DbgMenuChild {
    virtual void f0();
    virtual void f1();
    virtual ~DbgMenuChild();
};

struct DbgMenu {
    void *vtable;
    int field4;
    DbgMenuChild *child;
};

extern "C" {
extern void MemoryManager_TimedFree(void *);
extern void dtor_8002CDF4(void *, int);
extern char lbl_8041C99C[];  /* DbgMenu vtable */

#pragma exceptions on
DbgMenu *DbgMenu_Dtor(DbgMenu *self, short flag)
{
    if (self != 0) {
        self->vtable = lbl_8041C99C;
        if (self->child != 0) {
            delete self->child;
        }
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
}
#pragma cplusplus off
