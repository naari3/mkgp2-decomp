/* CC-class select flow constructor. */
struct SpriteObj {
    char pad0[0xC];
    float x;
    float y;
    char pad14[0x1C];

    SpriteObj(int anim, int loop, int arg);
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

struct ClassFlow : FlowBase {
    unsigned char unk4;
    unsigned char unk5;
    unsigned char unk6;
    char pad_7;
    int classCount;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    float unk20;
    float unk24;
    int unk28;
    int unk2C;
    SpriteObj *title;
    int unk34;
    int unk38;
    SpriteObj *extra;
    int unk40;
    int unk44;
    int unk48;
    int unk4C;
    float unk50;
    float unk54;

    ClassFlow();
};

extern "C" {
extern InputView *g_pInputState;
extern int g_gameMode;
extern void *lbl_8049AA0C[];
extern const float lbl_806D9AF4;
extern const float lbl_806D9AF8;
extern const float lbl_806D9AFC;
extern const float lbl_806D9B04;
extern const float lbl_806D9B10;
extern const float lbl_806D9B14;
extern const float lbl_806D9B48;
extern const float lbl_806D9B4C;
void InitBGM(void);
void InitRumbleController(int arg);
void PreloadResource(int id);
void SetScreenBrightness(float level);
void SetSyncTarget(int target);
int SetupBgSprites(unsigned char enable);
void SpriteSystem_EnsureInit(void);
int fn_801B8918(int value);
void fn_801B7B04(int arg);
}

static inline void SpriteObj_SetPos(SpriteObj *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

ClassFlow::ClassFlow() {
    vt = lbl_8049AA0C;
    SetSyncTarget(0xB);
    SpriteSystem_EnsureInit();
    PreloadResource(0x1B13);
    PreloadResource(0x1B12);
    PreloadResource(0x1666);
    PreloadResource(0x1ADE);
    PreloadResource(0x1ADF);
    PreloadResource(0x1AE0);
    PreloadResource(0x166F);
    title = new SpriteObj(0xE, 1, 0);
    if (g_gameMode == 2) {
        SpriteObj_SetPos(title, lbl_806D9B48, lbl_806D9B10);
    } else {
        SpriteObj_SetPos(title, lbl_806D9B48, lbl_806D9B14);
    }
    unk34 = 0;
    unk38 = 0;
    unk18 = 0;
    unk1C = 0;
    unk2C = 0;
    unk24 = lbl_806D9AF4;
    unk14 = 0;
    unk40 = 0;
    unk4 = 0;
    unkC = 1;
    unk28 = -1;
    unk5 = 0;
    unk20 = lbl_806D9B4C;
    unk44 = 0;
    unk48 = 0;
    unk4C = 0;
    unk50 = lbl_806D9AF4;
    unk54 = lbl_806D9AF4;
    unk6 = 0;
    if (g_gameMode != 2) {
        extra = new SpriteObj(0x47, 1, 0);
        classCount = 4;
    } else {
        extra = 0;
        classCount = 3;
    }
    if (extra != 0) {
        SpriteObj_SetPos(extra, lbl_806D9AFC, lbl_806D9B04);
    }
    if (input_state()) {
        InputView *input = input_state();
        input->enabled = 1;
        input->held = 0;
        input->edge = 0;
    }
    InitBGM();
    SetupBgSprites(1);
    SetScreenBrightness(lbl_806D9AF8);
    InitRumbleController(1);
    if (g_gameMode == 2) {
        fn_801B8918(0x1ADE);
    } else {
        fn_801B8918(0x1ADF);
    }
    fn_801B7B04(0);
}
