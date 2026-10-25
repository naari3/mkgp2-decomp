typedef struct Obj {
    unsigned char pad_0[0x1C];
    float f_1C;
} Obj;

extern const float lbl_806DB9E8;
extern const float lbl_806DB9EC;

void fn_8023CFC8(Obj *obj) {
    obj->f_1C = lbl_806DB9E8;
}

void fn_8023CFD4(Obj *obj) {
    obj->f_1C = lbl_806DB9EC;
}
