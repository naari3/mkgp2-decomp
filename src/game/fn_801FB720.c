extern void fn_8016039C(void *p);
extern void fn_8024E05C(void *p);
extern void fn_801D9A2C(void *p);
extern void fn_8023CD54(void *p);

typedef struct ResourceSet {
    char pad_0[0x44];
    void *res44;
    void *res48;
    void *res4C;
    void *res50;
} ResourceSet;

void fn_801FB720(ResourceSet *self) {
    if (self->res48 != 0) {
        fn_8016039C(self->res48);
    }
    if (self->res44 != 0) {
        fn_8024E05C(self->res44);
    }
    fn_801D9A2C(self->res4C);
    fn_8023CD54(self->res50);
}
