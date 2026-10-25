typedef struct Obj {
    unsigned char pad_0[0x18];
    int f_18;
} Obj;

extern void fn_801D9A2C(int);

void fn_8024B544(void *p0) {
    fn_801D9A2C(((Obj *)p0)->f_18);
}
