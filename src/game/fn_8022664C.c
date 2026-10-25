typedef struct Obj {
    unsigned char pad_0[0x10];
    int f_10;
} Obj;

extern void fn_801D9A2C(int);

void fn_8022664C(void *p0) {
    fn_801D9A2C(((Obj *)p0)->f_10);
}
