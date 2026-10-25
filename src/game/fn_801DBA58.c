typedef struct Obj {
    unsigned char pad_0[0x8];
    int f_8;
} Obj;

int fn_801DBA58(Obj *obj) {
    return obj->f_8;
}
