typedef struct Obj {
    unsigned char pad_0[0xC];
    float f_C;
    float f_10;
} Obj;

extern const float lbl_806DB074;

void fn_8021ED0C(Obj *obj) {
    obj->f_C = lbl_806DB074;
    obj->f_10 = lbl_806DB074;
}
