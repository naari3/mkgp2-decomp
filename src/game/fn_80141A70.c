typedef struct Obj {
    unsigned char pad_0[0x44];
    int f_44;
} Obj;

extern void fn_801674AC(int);

void fn_80141A70(void *p0) {
    fn_801674AC(((Obj *)p0)->f_44);
}
