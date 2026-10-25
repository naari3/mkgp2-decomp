typedef struct Obj {
    unsigned char pad_0[0x14];
    unsigned char f_14;
    unsigned char f_15;
    unsigned char pad_16[0x2];
    float f_18;
    float f_1C;
    float f_20;
    unsigned char pad_24[0x4];
    unsigned char f_28;
    unsigned char pad_29[0x7];
    int f_30;
} Obj;

unsigned char fn_801DEC3C(Obj *obj) {
    return obj->f_28;
}

float fn_801DEC44(Obj *obj) {
    return obj->f_20;
}

float fn_801DEC4C(Obj *obj) {
    return obj->f_1C;
}

float fn_801DEC54(Obj *obj) {
    return obj->f_18;
}

unsigned char fn_801DEC5C(Obj *obj) {
    return obj->f_15;
}

unsigned char PathFollower_IsItemLocked(Obj *obj) {
    return obj->f_14;
}

void *fn_801DEC6C(Obj *obj) {
    return &obj->f_30;
}
