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
    unsigned char pad20[0x8];
    float w;
    float w2;
    float w3;
    unsigned char pad34[0x48 - 0x34];
    int a;
    int b;
    int c;
};

extern "C" {
extern const float lbl_806D8A0C;
extern void fn_8011FAFC(ResCtrl *r, void *dst);
}

extern "C" void fn_801696E4(void *dst, int id, float x, float y, float w, unsigned int flags) {
    if (id < 0) {
        return;
    }
    ResCtrl r;
    r.id = id;
    r.enable = 1;
    r.x = x;
    r.y = y;
    r.z = lbl_806D8A0C;
    r.w = w;
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
