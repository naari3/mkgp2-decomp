typedef struct Obj {
    unsigned char pad_0[0x174];
    int f_174;
} Obj;

void fn_801FE3B4(Obj *obj, int value) {
    obj->f_174 = value;
}
