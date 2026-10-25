typedef struct Obj {
    unsigned char pad_0[0x1C];
    int f_1C;
} Obj;

void fn_801DB994(Obj *obj, int value) {
    obj->f_1C = value;
}
