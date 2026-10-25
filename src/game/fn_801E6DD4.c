typedef struct Obj {
    unsigned char pad_0[0x94];
    unsigned char f_94;
} Obj;

unsigned char fn_801E6DD4(Obj *obj) {
    return obj->f_94;
}
