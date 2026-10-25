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

struct FlowPanel {
    int state;
    char pad04[0xC];
    int alpha;
    int layer;
    char pad18[8];
    unsigned char showBg;
    char pad21[0x27];
    void *labelB;
    void *labelA;
    ResCtrl *icons[3];
    void *texts[3];
};

extern "C" {
void fn_8011FAFC(ResCtrl *rc, int layer);
void fn_801A0004(void *label);
void *fn_801F8E58(void);
void fn_801F8A34(void *mgr, void *text, int layer);
}

extern "C" void fn_801D9A2C(FlowPanel *self) {
    int i;

    if (self->showBg == 1) {
        ResCtrl rc;
        unsigned int color;
        rc.mode = 2;
        rc.width = 640.0f;
        rc.height = 480.0f;
        rc.flag = 1;
        rc.x = 320.0f;
        rc.y = 240.0f;
        rc.z = 1.0f;
        color = (unsigned char)self->alpha;
        rc.colors[0] = color;
        rc.colors[1] = color;
        rc.colors[2] = color;
        rc.colors[3] = color;
        fn_8011FAFC(&rc, self->layer);
    }
    if (self->labelA != 0) {
        fn_801A0004(self->labelA);
    }
    if (self->labelB != 0) {
        fn_801A0004(self->labelB);
    }
    for (i = 0; i < 3; i++) {
        ResCtrl *icon = self->icons[i];
        if (icon != 0 && self->state == 2 && (int)icon->resId != -1) {
            fn_8011FAFC(icon, self->layer);
        }
    }
    {
        void *mgr = fn_801F8E58();
        for (i = 0; i < 3; i++) {
            fn_801F8A34(mgr, self->texts[i], self->layer);
        }
    }
}
