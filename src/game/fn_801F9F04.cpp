class VObj {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
};

extern "C" void fn_8011FAB8(void);
extern "C" void fn_80203BEC(void);
extern "C" void fn_80207810(void);
extern "C" void HSD_StateInvalidate(int);

struct SceneOwner {
    char pad_0[4];
    unsigned char done;
    char pad_5[3];
    VObj *obj;
};

extern "C" void fn_801F9F04(SceneOwner *self) {
    if (self->done == 0) {
        self->obj->v10();
        fn_80207810();
        fn_80203BEC();
        fn_8011FAB8();
        HSD_StateInvalidate(-1);
    }
}
