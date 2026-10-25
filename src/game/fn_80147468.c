typedef struct Obj {
    unsigned char pad_0[0x20];
    int f_20;
} Obj;

int fn_80147468(Obj *obj) {
    return obj->f_20;
}
