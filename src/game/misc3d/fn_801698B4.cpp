struct ResCtrl {
    ResCtrl();
    ~ResCtrl() {}
    int id;
    int pad4;
    int mode;
    int padc;
    unsigned char enable;
    unsigned char pad11[3];
    float x;
    float y;
    float z;
    unsigned char pad20[0x48 - 0x20];
    int a;
    int b;
    int c;
};

extern "C" {
extern const float lbl_806D8A0C;
extern void fn_8011FAFC(ResCtrl *r, void *dst);
}

extern "C" void fn_801698B4(void *dst, int id, float x, float y, unsigned int flags) {
    if (id < 0) {
        return;
    }
    ResCtrl r;
    r.id = id;
    r.enable = 1;
    r.x = x;
    r.y = y;
    r.z = lbl_806D8A0C;
    if (flags & 1) {
        r.a = 1;
        r.b = 4;
        r.c = 1;
    }
    if (flags & 2) {
        r.mode = 3;
    }
    fn_8011FAFC(&r, dst);
}
