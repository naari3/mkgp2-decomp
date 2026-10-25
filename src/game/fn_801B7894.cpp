class VObj {
public:
    virtual void v8();
};

extern "C" void fn_801B76C8(void *self);

extern "C" void fn_801B7894(char *self) {
    VObj *obj = *(VObj **)(self + 0x10);
    if (obj != 0) {
        obj->v8();
    }
    fn_801B76C8(self);
}
