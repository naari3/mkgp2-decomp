typedef struct Obj {
    unsigned char pad_0[0x18];
    int f_18;
} Obj;

extern void fn_8013B4FC(int, int);

void fn_80146160(void *p0, int p1) {
    fn_8013B4FC(((Obj *)p0)->f_18, 1);
}
