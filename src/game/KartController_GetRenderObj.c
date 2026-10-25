typedef struct Obj {
    unsigned char pad_0[0x10];
    int f_10;
    unsigned char pad_14[0x68];
    int f_7C;
} Obj;

int KartController_GetRenderObj(Obj *obj) {
    return obj->f_10;
}

int fn_801E6E18(Obj *obj) {
    return obj->f_7C;
}
