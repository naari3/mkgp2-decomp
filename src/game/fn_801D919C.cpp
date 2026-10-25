void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct Sprite {
    int field0;
    int layer;
    char pad08[0x28];
    Sprite(int anim, int loop, int flags);
};

struct TexMgr {
    char pad000[0x20];
    int color;
};

struct FlowPanel {
    int state;
    int field4;
    int field8;
    int fieldC;
    int alpha;
    int layer;
    char pad18[0x30];
    void *labelB;
    Sprite *labelA;
    void *icons[3];
    TexMgr *texts[3];
};

extern "C" {
void Sprite_SetupAnim(Sprite *sprite, int anim, int loop, int flags);
void Sprite_SetAnimTime(Sprite *sprite, float time);
void TexMgr_SetTexture(TexMgr *tex, const char *fmt, ...);
void fn_80121E10(void *icon);
void fn_801A0500(void *label);
void fn_801FE1D0(void);
extern const char lbl_806DA1AC[4];
}

extern "C" void fn_801D919C(FlowPanel *self) {
    int i;

    if (self->state == 0 || self->state == 3) {
        return;
    }
    self->state = 3;
    self->field8 = 0;
    self->alpha = 0x80;
    self->field4 = -1;
    if (self->labelA != 0) {
        Sprite_SetupAnim(self->labelA, 0xF, 1, 0);
    } else {
        self->labelA = new Sprite(0xF, 1, 0);
    }
    Sprite_SetAnimTime(self->labelA, 0.0f);
    self->labelA->layer = self->layer;
    for (i = 0; i < 3; i++) {
        TexMgr_SetTexture(self->texts[i], lbl_806DA1AC);
        self->texts[i]->color = -0x100;
    }
    fn_80121E10(self->icons[1]);
    fn_80121E10(self->icons[0]);
    fn_80121E10(self->icons[2]);
    if (self->labelB != 0) {
        fn_801A0500(self->labelB);
    }
    fn_801FE1D0();
}
