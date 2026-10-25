typedef struct Obj {
    unsigned char pad_0[0x30];
    int f_30;
} Obj;

void *fn_801E6D64(Obj *obj) {
    return &obj->f_30;
}
