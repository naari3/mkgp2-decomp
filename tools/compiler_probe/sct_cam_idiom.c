extern void *lbl_806D10A0;
extern void TitleTracker_Empty_PreFinalizeHook(unsigned int tracker, int kartSlot);
extern void Body(void *self, void *arg);
typedef struct V { char pad[0x10]; int kartSlot; } V;

void c1_cast(V *self, void *arg)
{
    unsigned int t;
    Body(self, arg);
    t = (unsigned int)lbl_806D10A0;
    if (t != (unsigned int)lbl_806D10A0) {
    } else if (t == 0) {
        t = 0;
    }
    if (t != 0) {
        TitleTracker_Empty_PreFinalizeHook(t, self->kartSlot);
    }
}

void c2_ptr(V *self, void *arg)
{
    void *t;
    Body(self, arg);
    t = lbl_806D10A0;
    if (t != lbl_806D10A0) {
    } else if (t == 0) {
        t = 0;
    }
    if (t != 0) {
        TitleTracker_Empty_PreFinalizeHook((unsigned int)t, self->kartSlot);
    }
}

void c3_uintext(V *self, void *arg)
{
    unsigned int t;
    Body(self, arg);
    t = *(unsigned int *)&lbl_806D10A0;
    if (t != *(unsigned int *)&lbl_806D10A0) {
    } else if (t == 0) {
        t = 0;
    }
    if (t != 0) {
        TitleTracker_Empty_PreFinalizeHook(t, self->kartSlot);
    }
}
