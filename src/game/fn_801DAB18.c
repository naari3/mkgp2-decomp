typedef struct Obj {
    unsigned char pad_0[0x8];
    int f_8;
} Obj;

void fn_801DAB18(Obj *obj, int value) {
    obj->f_8 = value;
}
