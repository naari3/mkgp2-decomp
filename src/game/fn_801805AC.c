typedef struct Obj {
    unsigned char pad_0[0x40];
    int f_40;
} Obj;

void fn_801805AC(Obj *obj, int value) {
    obj->f_40 = value;
}
