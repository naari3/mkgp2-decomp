typedef struct Obj {
    unsigned char pad[0x21];
    unsigned char b21;
    unsigned char pad2[0xe];
    unsigned char b30;
} Obj;

void fn_801999D0(Obj *o, unsigned char v) {
    o->b30 = v;
    o->b21 = o->b30;
}
