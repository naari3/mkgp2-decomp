/* JumpDistanceMode_InitTimerDisplay (0x80213A64): builds the timer HUD sprites
 * (label, separators and three digits of `value`). */

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    int tail[5];
    ResCtrl();
    ~ResCtrl() {}
};

struct TimerDisplay {
    int x0;
    int value;
    unsigned char x8;
    float xC;
    unsigned int sprites[7];
};

extern "C" {
extern const float lbl_806DAD70;
extern const float lbl_806DAD7C;
extern const float lbl_806DAE10;
extern float JumpDistanceMode_rodata_803C3CF0[];
void fn_80121E10(ResCtrl *rc);
unsigned int SpriteHandle_CreateDefault(ResCtrl *rc, int layer);
}

extern "C" TimerDisplay *JumpDistanceMode_InitTimerDisplay(TimerDisplay *self, int value) {
    int d, t;

    self->x0 = 0;
    self->value = value;
    self->x8 = 0;
    self->xC = lbl_806DAD7C;
    {
        ResCtrl rc;

        rc.resId = 0x1B72;
        rc.flag = 1;
        rc.x = JumpDistanceMode_rodata_803C3CF0[0];
        rc.y = JumpDistanceMode_rodata_803C3CF0[1];
        rc.z = lbl_806DAD70;
        self->sprites[0] = SpriteHandle_CreateDefault(&rc, 4);
        fn_80121E10(&rc);
        rc.resId = 0x1ECD;
        rc.flag = 1;
        rc.x = JumpDistanceMode_rodata_803C3CF0[2];
        rc.y = JumpDistanceMode_rodata_803C3CF0[3];
        rc.z = lbl_806DAD70;
        self->sprites[1] = SpriteHandle_CreateDefault(&rc, 4);
        rc.flag = 1;
        rc.x = JumpDistanceMode_rodata_803C3CF0[4];
        rc.y = JumpDistanceMode_rodata_803C3CF0[5];
        rc.z = lbl_806DAD70;
        self->sprites[2] = SpriteHandle_CreateDefault(&rc, 4);
        fn_80121E10(&rc);
        rc.resId = 0x1B73;
        rc.flag = 1;
        rc.x = JumpDistanceMode_rodata_803C3CF0[6];
        rc.y = JumpDistanceMode_rodata_803C3CF0[7];
        rc.z = lbl_806DAD70;
        self->sprites[3] = SpriteHandle_CreateDefault(&rc, 4);
        d = (value / 100) % 10;
        fn_80121E10(&rc);
        rc.resId = d != 0 ? d + 0x1B73 : 0x1ECD;
        rc.flag = 1;
        rc.x = JumpDistanceMode_rodata_803C3CF0[8];
        rc.y = JumpDistanceMode_rodata_803C3CF0[9];
        rc.z = lbl_806DAD70;
        rc.scaleY = rc.scaleX = lbl_806DAE10;
        self->sprites[4] = SpriteHandle_CreateDefault(&rc, 4);
        t = (value / 10) % 10;
        fn_80121E10(&rc);
        rc.resId = t + 0x1B73;
        rc.flag = 1;
        rc.x = JumpDistanceMode_rodata_803C3CF0[10];
        rc.y = JumpDistanceMode_rodata_803C3CF0[11];
        rc.z = lbl_806DAD70;
        rc.scaleY = rc.scaleX = lbl_806DAE10;
        self->sprites[5] = SpriteHandle_CreateDefault(&rc, 4);
        fn_80121E10(&rc);
        rc.resId = value % 10 + 0x1B73;
        rc.flag = 1;
        rc.x = JumpDistanceMode_rodata_803C3CF0[12];
        rc.y = JumpDistanceMode_rodata_803C3CF0[13];
        rc.z = lbl_806DAD70;
        rc.scaleY = rc.scaleX = lbl_806DAE10;
        self->sprites[6] = SpriteHandle_CreateDefault(&rc, 4);
    }
    return self;
}
