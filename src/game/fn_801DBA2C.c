typedef struct Obj {
    unsigned char pad_0[0xC];
    int f_C;
} Obj;

int fn_801DBA2C(Obj *obj) {
    return obj->f_C;
}
