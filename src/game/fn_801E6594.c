typedef struct Obj {
    unsigned char pad_0[0x24];
    int f_24;
} Obj;

extern void fn_801E9290(int);

void fn_801E6594(void *p0) {
    fn_801E9290(((Obj *)p0)->f_24);
}
