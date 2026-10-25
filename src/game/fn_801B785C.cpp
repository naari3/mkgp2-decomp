class VObj {
public:
    virtual void v8();
    virtual void vC();
};

extern "C" void fn_801B785C(char *self) {
    VObj *obj = *(VObj **)(self + 0x10);
    if (obj != 0) {
        obj->vC();
    }
}
