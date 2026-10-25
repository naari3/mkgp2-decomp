typedef struct Obj {
    unsigned char pad_0[0x44];
    unsigned char f_44;
} Obj;

void fn_80143880(Obj *obj) {
    obj->f_44 = 1;
}
