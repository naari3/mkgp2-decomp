class VObj {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
};

extern "C" void fn_801FAB58(char *self) {
    (*(VObj **)(self + 0x10))->v10();
}
