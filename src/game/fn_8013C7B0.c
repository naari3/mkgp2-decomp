typedef struct Obj {
    unsigned char pad_0[0x88];
    float f_88;
    float f_8C;
} Obj;

void fn_8013C7B0(Obj *obj, float a, float b) {
    obj->f_88 = a;
    obj->f_8C = b;
}
