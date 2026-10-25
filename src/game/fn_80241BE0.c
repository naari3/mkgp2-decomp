typedef struct Obj {
    unsigned char pad_0[0x4];
    int f_4;
} Obj;

extern void fn_802CED98(int);

void fn_80241BE0(void *p0) {
    fn_802CED98(((Obj *)p0)->f_4);
}
