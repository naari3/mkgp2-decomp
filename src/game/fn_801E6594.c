typedef struct Obj {
    unsigned char pad_0[0x24];
    int f_24;
} Obj;

extern unsigned char fn_801E9290(int);

unsigned char fn_801E6594(void *p0) {
    return fn_801E9290(((Obj *)p0)->f_24);
}
