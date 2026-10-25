typedef struct Obj {
    unsigned char pad_0[0x8];
    unsigned char f_8;
} Obj;

unsigned char fn_801635D4(Obj *obj) {
    return obj->f_8;
}
