typedef struct Obj {
    unsigned char pad_0[0x74];
    float f_74;
} Obj;

void fn_80253F2C(Obj *obj, float value) {
    obj->f_74 = value;
}
