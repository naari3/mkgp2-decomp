typedef struct Obj {
    unsigned char pad_0[0x5C];
    float f_5C;
    float f_60;
} Obj;

void fn_8021A7BC(Obj *obj, float a, float b) {
    obj->f_5C = a;
    obj->f_60 = b;
}
