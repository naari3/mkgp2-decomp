struct ResCtrl {
    void *resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    int tail[5];
    ResCtrl();
    ~ResCtrl() {}
};

extern "C" {
void fn_8011FAFC(ResCtrl *rc, int arg);
extern void *lbl_8039FCD0[];
extern const float lbl_806DA250;
extern const float lbl_806DA254;
extern const float lbl_806DA258;
}

extern "C" void fn_801DAAA4(char *self) {
    ResCtrl rc;

    rc.resId = lbl_8039FCD0[*(int *)(self + 0x8)];
    rc.flag = 1;
    rc.x = lbl_806DA250;
    rc.y = lbl_806DA254;
    rc.z = lbl_806DA258;
    fn_8011FAFC(&rc, 0);
}
