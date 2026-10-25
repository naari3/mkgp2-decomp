/* Flow scene destructor: releases its sprites and capture buffer, then restores the background. */
struct SpriteObj {
    ~SpriteObj();
};

struct InputView {
    unsigned char opaque[4];
    unsigned char enabled;
    unsigned char opaque5[0x13];
    int held;
    int edge;
};

struct FlowBase {
    void *vt;
    FlowBase();
    ~FlowBase();
};

extern "C" {
extern InputView *g_pInputState;
extern void *lbl_8049AD40[];
void fn_801B7B04(int arg);
void fn_801699D8(int a, int b);
void fn_80169C44(void);
void MemoryManager_Free(void *p);
unsigned char GetVBlankFlag(void);
void NamCam_End(void);
void fn_80120A08(int id);
void fn_80121210(void);
void SetupBgSprites(int arg);
}

struct CamCapture {
    unsigned char active;
    void *buf;

    ~CamCapture() {
        MemoryManager_Free(buf);
        if (GetVBlankFlag()) {
            if (GetVBlankFlag() && active) {
                active = 0;
                NamCam_End();
            }
            buf = 0;
        }
    }
};

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

struct Scene801C5C34 : FlowBase {
    char pad4[0x2C];
    SpriteObj *s30;
    SpriteObj *s34;
    SpriteObj *s38;
    SpriteObj *s3C;
    SpriteObj *s40;
    SpriteObj *s44;
    SpriteObj *s48;
    SpriteObj *s4C;
    SpriteObj *rowA[11];
    SpriteObj *rowB[11];
    SpriteObj *sA8;
    CamCapture *cam;

    ~Scene801C5C34();
};

Scene801C5C34::~Scene801C5C34() {
    int i;

    vt = lbl_8049AD40;
    fn_801B7B04(1);
    if (input_state()) {
        InputView *input = input_state();
        input->enabled = 0;
        input->held = 0;
        input->edge = 0;
    }
    fn_801699D8(0, 0);
    fn_80169C44();
    delete sA8;
    delete s40;
    delete s44;
    delete s3C;
    delete s38;
    delete s34;
    delete s30;
    delete s48;
    delete s4C;
    delete cam;
    for (i = 0; i < 11; i++) {
        delete rowA[i];
        delete rowB[i];
    }
    fn_80120A08(0x18DD);
    fn_80121210();
    SetupBgSprites(1);
}
