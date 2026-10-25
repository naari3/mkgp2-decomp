typedef struct Obj {
    unsigned char pad_0[0x4];
    int f_4;
} Obj;

extern void fn_801A0004(int);

void fn_80218B5C(void *p0) {
    fn_801A0004(((Obj *)p0)->f_4);
}
