class VObj {
public:
    virtual void v8();
    virtual void vC();
};

struct Timer {
    char pad_0[4];
    int remaining;
};

extern "C" void *fn_801F4DC0(void *timer, int arg);
extern "C" void fn_80203C24(void);
extern "C" void fn_80207848(void);
extern "C" void *fn_80271340(void *, int, void *, void *, int);
extern int lbl_806D00C8;
extern int lbl_806D0108;

struct SceneOwner {
    char pad_0[4];
    unsigned char done;
    char pad_5[3];
    VObj *obj;
    int value;
};

extern "C" void fn_801F9F54(SceneOwner *self) {
    if (self->done == 0) {
        void *p = fn_801F4DC0(self->obj, 0);
        if (p != 0) {
            self->value = *(int *)((char *)fn_80271340(p, 0, &lbl_806D0108, &lbl_806D00C8, 0) + 0x1C);
        }
        if (((Timer *)self->obj)->remaining <= 0) {
            self->done = 1;
        }
        self->obj->vC();
        fn_80207848();
        fn_80203C24();
    }
}
