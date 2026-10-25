typedef struct Obj {
    unsigned char pad_0[0xC];
    float f_C;
    float f_10;
} Obj;

extern const float lbl_806DB190;

void fn_80224EBC(Obj *obj) {
    obj->f_C = lbl_806DB190;
    obj->f_10 = lbl_806DB190;
}
