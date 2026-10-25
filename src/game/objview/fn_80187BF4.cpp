extern "C" {
extern const char lbl_8037741C[];
extern const char lbl_80377440[];
extern const float lbl_806D92F4;
void DebugPrintf(const char *fmt, ...);
void *FUN_8003b120(unsigned long size);
}

struct clNormal3D {
    unsigned char data[0x5c];
    clNormal3D(const char *name, int arg);
};

struct ObjBase {
    ObjBase() {}
    virtual ~ObjBase();
};

struct Slot {
    float f[7];
    int i;
};

struct Obj80187BF4 : ObjBase {
    clNormal3D *model;
    Slot *slots;
    Obj80187BF4();
    virtual ~Obj80187BF4();
};

Obj80187BF4::Obj80187BF4() {
    int i;
    DebugPrintf(lbl_8037741C);
    model = 0;
    slots = 0;
    model = new clNormal3D(lbl_80377440, 0);
    if (model == 0) return;
    slots = (Slot *)FUN_8003b120(0x60);
    if (slots == 0) return;
    for (i = 0; i < 3; i++) {
        slots[i].f[0] = lbl_806D92F4;
        slots[i].f[1] = lbl_806D92F4;
        slots[i].f[2] = lbl_806D92F4;
        slots[i].f[3] = lbl_806D92F4;
        slots[i].f[4] = lbl_806D92F4;
        slots[i].f[5] = lbl_806D92F4;
        slots[i].f[6] = lbl_806D92F4;
        slots[i].i = 0;
    }
}
