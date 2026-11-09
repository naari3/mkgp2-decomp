/*
 * 0x801F0CC0..0x801F26C8: clEzMenu, the 14-state "easy menu" scene (stick
 * level select plus two yes/no pages). Each state has an update and a draw
 * handler reached through member function pointer tables; the tables are
 * filled by the TU's static initializer (fn_801F27B4, still asm).
 */

#include "game/FlowScene.h"

struct Rect {
    float x, y, w, h;
};

struct EffectObj {
    ~EffectObj();
};

struct EffectSlot {
    char pad00[0x94];
    ~EffectSlot();
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float Stick();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual unsigned char Pressed(int mask);
};

extern "C" {
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void GX_EndDraw(int);
void GX_BeginDraw(void);
void clCGameDemoWC_StubBlr_800adda0(void);
void clCGameDemoWC_StubBlr_800adda4(void);
void clCGameDemoWC_StubBlr_800adda8(int);
void *StrPcb_GetInstance(void);
void StrPcb_RunAndWaitIdle(void *pcb);
void StrPcb_ResetCommands_Neutral(void *pcb, int mode);
int fn_8020A788(FlowFaderI *t);
void fn_8020A7CC(FlowFaderI *t, int from, int to, short dur);
void fn_801F6E98(EffectSlot *s, unsigned int color);
void fn_801F6ED0(EffectSlot *s, float sx, float sy);
void fn_801F6C2C(EffectSlot *s, const Rect *r, int flipX, int flipY);
void fn_801F6D58(EffectSlot *s, const Rect *r, int flipX, int flipY);
void fn_801F6F7C(EffectSlot *s, const Rect *r, float speed);
void fn_801F7040(EffectSlot *s, const Rect *r, float speed);
void fn_801F7B74(EffectObj *o, EffectSlot *s, float z);
}

float lbl_804E4C28[66] = {
    0.0f, 0.0f, 0.0f, 0.0f, 256.0f, 0.0f, 0.0f, 0.0f,
    512.0f, 0.0f, 0.0f, 0.0f, 0.0f, 256.0f, 0.0f, 0.0f,
    256.0f, 256.0f, 0.0f, 0.0f, 512.0f, 256.0f, 0.0f, 0.0f,
    0.0f, 25.0f, 0.0f, 0.0f, 320.0f, 97.0f, 320.0f, 25.0f,
    0.0f, 97.0f, 320.0f, 88.0f, 158.0f, 352.0f, 0.0f, 410.0f,
    324.0f, 28.0f, 96.0f, 380.0f, 320.0f, 62.0f, 150.0f, 62.0f,
    398.0f, 380.0f, 320.0f, 0.0f, 150.0f, 62.0f, 115.0f, 122.0f,
    0.0f, 184.0f, 409.0f, 226.0f, 55.0f, 386.0f, 0.0f, 438.0f,
    232.0f, 40.0f,
};

Rect lbl_804E4D30[2] = {
    {55.0f, 386.0f, 0.0f, 0.0f},
    {355.0f, 386.0f, 0.0f, 0.0f},
};

float sTbl128[50] = {
    0.0f, 27.0f, 0.0f, 0.0f, 640.0f, 90.0f, 160.0f, 239.0f,
    0.0f, 90.0f, 284.0f, 201.0f, 480.0f, 239.0f, 284.0f, 90.0f,
    284.0f, 201.0f, 57.0f, 340.0f, 493.0f, 341.0f, 531.0f, 137.0f,
    145.0f, 364.0f, 0.0f, 377.0f, 351.0f, 50.0f, 110.0f, 419.0f,
    0.0f, 291.0f, 420.0f, 37.0f, 288.0f, 202.0f, 568.0f, 90.0f,
    64.0f, 75.0f, 632.0f, 90.0f, -64.0f, 75.0f, 568.0f, 90.0f,
    64.0f, 75.0f,
};

Rect sTbl1F0[2] = {
    {0.0f, 377.0f, 351.0f, 50.0f},
    {0.0f, 427.0f, 351.0f, 50.0f},
};

Rect sTbl210[3] = {
    {0.0f, 327.0f, 420.0f, 37.0f},
    {0.0f, 291.0f, 420.0f, 37.0f},
    {320.0f, 271.0f, 0.0f, 0.0f},
};

Rect sTbl240[7] = {
    {159.0f, 157.0f, 0.0f, 0.0f},
    {223.0f, 125.0f, 0.0f, 0.0f},
    {288.0f, 110.0f, 0.0f, 0.0f},
    {355.0f, 110.0f, 0.0f, 0.0f},
    {420.0f, 125.0f, 0.0f, 0.0f},
    {483.0f, 157.0f, 0.0f, 0.0f},
    {320.0f, 392.0f, 0.0f, 0.0f},
};

Rect sTbl2B0[7] = {
    {368.0f, 258.0f, 264.0f, 176.0f},
    {0.0f, 0.0f, 296.0f, 236.0f},
    {592.0f, 0.0f, 298.0f, 236.0f},
    {296.0f, 0.0f, 296.0f, 252.0f},
    {632.0f, 258.0f, 300.0f, 234.0f},
    {0.0f, 258.0f, 368.0f, 262.0f},
    {932.0f, 0.0f, 64.0f, 75.0f},
};

Rect sTbl320[6] = {
    {0.0f, 0.0f, 256.0f, 41.0f},
    {0.0f, 41.0f, 256.0f, 44.0f},
    {0.0f, 85.0f, 256.0f, 41.0f},
    {0.0f, 126.0f, 256.0f, 42.0f},
    {0.0f, 168.0f, 256.0f, 45.0f},
    {0.0f, 213.0f, 256.0f, 43.0f},
};


struct clSceneInterface {
    virtual ~clSceneInterface() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    bool done;
};

static inline unsigned int RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

static inline InputPlayer *Pad() {
    return InputMgr_GetPlayer(GetInputManager(), 0);
}

struct clEzMenu : clSceneInterface {
    EffectObj *ctx;
    EffectSlot *slots;
    VHolder<FlowFaderI> fade;
    int unk14;
    int sel;
    int yesNo;
    int level;
    int state;

    ~clEzMenu();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();

    void SetColors(int from, int to, unsigned int color) {
        for (int i = from; i < to; i++) {
            fn_801F6E98(&slots[i], color);
        }
    }
    void DrawSlots(int from, int to) {
        for (int i = from; i < to; i++) {
            fn_801F7B74(ctx, &slots[i], -1.0f);
        }
    }
    bool StepFade() {
        fade.p->Step();
        return fade.p->Done();
    }

    void DrawNone();
    void UpdExit();
    void UpdLevelOut();
    void DrawLevel();
    void UpdLevel();
    void DrawLevelIn();
    void UpdLevelIn();
    void UpdLevelBack();
    void DrawYesNoIn();
    void UpdYesNo();
    void DrawYesNo();
    void UpdYesNoIn();
    void UpdYesNoBack();
    void DrawSel();
    void UpdSel();
    void UpdSelOut();
    void DrawSelIn();
    void UpdSelBack();
    void UpdSelIn();
    void DrawTitle();
    void UpdTitle();
    void UpdTitleIn();
};

typedef void (clEzMenu::*EzFn)();

/* 13 */
void clEzMenu::UpdExit() {
    if (!done) {
        clCGameDemoWC_StubBlr_800adda0();
        clCGameDemoWC_StubBlr_800adda4();
    }
    done = true;
}

/* 12 */
void clEzMenu::UpdLevelOut() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(26, 32, RGBA(c, c, c, 0xFF));
    SetColors(32, 35, RGBA(c, c, c, 0xFF));
    if (StepFade()) {
        SetColors(26, 32, 0xFF);
        SetColors(32, 35, 0xFF);
        state = 13;
    }
}

void clEzMenu::DrawLevel() {
    DrawSlots(26, 32);
    DrawSlots(32, 35);
}

/* 11 */
void clEzMenu::UpdLevel() {
    InputPlayer *pad = Pad();
    float v = pad->Stick();
    if (v >= -1.0f && v <= -0.6666f) {
        level = 0;
    } else if (v > -0.6666f && v <= -0.3333f) {
        level = 1;
    } else if (v > -0.3333f && v <= 0.0f) {
        level = 2;
    } else if (v > 0.0f && v <= 0.3333f) {
        level = 3;
    } else if (v > 0.3333f && v <= 0.6666f) {
        level = 4;
    } else if (v > 0.6666f && v <= 1.0f) {
        level = 5;
    }
    fn_801F6D58(&slots[32], &sTbl2B0[level], 0, 0);
    fn_801F7040(&slots[33], &sTbl240[level], 1.0f);
    fn_801F6D58(&slots[34], &sTbl320[level], 0, 0);
    if (pad->Pressed(2) == 1) {
        fn_8020A7CC(fade.p, 0, 0xFF, 22);
        SetColors(6, 12, 0xFFFFFF00);
        SetColors(19, 26, 0xFFFFFF00);
        state = 10;
    }
    if (pad->Pressed(0x100) == 1) {
        fn_8020A7CC(fade.p, 0xFF, 0, 22);
        state = 12;
    }
}

void clEzMenu::DrawLevelIn() {
    DrawSlots(6, 12);
    DrawSlots(19, 26);
    DrawSlots(26, 32);
    DrawSlots(32, 35);
}

/* 10 */
void clEzMenu::UpdLevelIn() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(6, 12, RGBA(0xFF, 0xFF, 0xFF, c));
    SetColors(19, 26, RGBA(0xFF, 0xFF, 0xFF, c));
    SetColors(26, 32, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    SetColors(32, 35, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    if (StepFade()) {
        SetColors(6, 12, 0xFFFFFFFF);
        SetColors(19, 26, 0xFFFFFFFF);
        SetColors(26, 32, 0xFFFFFF00);
        SetColors(32, 35, 0xFFFFFF00);
        state = 8;
    }
}

/* 9 */
void clEzMenu::UpdLevelBack() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(6, 12, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    SetColors(19, 26, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    SetColors(26, 32, RGBA(0xFF, 0xFF, 0xFF, c));
    SetColors(32, 35, RGBA(0xFF, 0xFF, 0xFF, c));
    if (StepFade()) {
        SetColors(6, 12, 0xFFFFFF00);
        SetColors(19, 26, 0xFFFFFF00);
        SetColors(26, 32, 0xFFFFFFFF);
        SetColors(32, 35, 0xFFFFFFFF);
        state = 11;
    }
}

void clEzMenu::DrawYesNoIn() {
    DrawSlots(6, 12);
    DrawSlots(19, 26);
}

/* 8 */
void clEzMenu::UpdYesNo() {
    InputPlayer *pad = Pad();
    if (pad->Pressed(0x10) == 1) {
        yesNo = 0;
    } else if (pad->Pressed(0x20) == 1) {
        yesNo = 1;
    }
    if (yesNo == 0) {
        fn_801F6ED0(&slots[20], 1.0f, 1.0f);
        fn_801F6ED0(&slots[21], 0.6f, 0.6f);
        fn_801F6D58(&slots[23], &sTbl1F0[0], 0, 0);
        fn_801F6D58(&slots[24], &sTbl210[0], 0, 0);
        fn_801F6C2C(&slots[25], (Rect *)&sTbl128[0x24], 1, 0);
    } else {
        fn_801F6ED0(&slots[20], 0.6f, 0.6f);
        fn_801F6ED0(&slots[21], 1.0f, 1.0f);
        fn_801F6D58(&slots[23], &sTbl1F0[1], 0, 0);
        fn_801F6D58(&slots[24], &sTbl210[1], 0, 0);
        fn_801F6C2C(&slots[25], (Rect *)&sTbl128[0x24], 0, 0);
    }
    if (pad->Pressed(2) == 1) {
        fn_8020A7CC(fade.p, 0, 0xFF, 22);
        SetColors(12, 19, 0xFFFFFF00);
        state = 7;
    }
    if (pad->Pressed(0x100) == 1) {
        fn_8020A7CC(fade.p, 0, 0xFF, 22);
        SetColors(26, 32, 0xFFFFFF00);
        SetColors(32, 35, 0xFFFFFF00);
        state = 9;
    }
}

void clEzMenu::DrawYesNo() {
    DrawSlots(6, 12);
    DrawSlots(19, 26);
    DrawSlots(12, 19);
}

/* 7 */
void clEzMenu::UpdYesNoIn() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(12, 19, RGBA(0xFF, 0xFF, 0xFF, c));
    SetColors(19, 26, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    if (StepFade()) {
        SetColors(12, 26, 0xFFFFFFFF);
        state = 5;
    }
}

/* 6 */
void clEzMenu::UpdYesNoBack() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(12, 19, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    SetColors(19, 26, RGBA(0xFF, 0xFF, 0xFF, c));
    if (StepFade()) {
        SetColors(12, 26, 0xFFFFFFFF);
        state = 8;
    }
}

void clEzMenu::DrawSel() {
    DrawSlots(6, 12);
    DrawSlots(12, 19);
}

/* 5 */
void clEzMenu::UpdSel() {
    InputPlayer *pad = Pad();
    if (pad->Pressed(0x10) == 1) {
        sel = 0;
    } else if (pad->Pressed(0x20) == 1) {
        sel = 1;
    }
    fn_801F6F7C(&slots[18], &lbl_804E4D30[sel], 1.0f);
    if (pad->Pressed(2) == 1) {
        fn_8020A7CC(fade.p, 0xFF, 0, 22);
        SetColors(0, 6, 0xFFFFFF00);
        state = 3;
    }
    if (pad->Pressed(0x100) == 1) {
        fn_8020A7CC(fade.p, 0, 0xFF, 22);
        SetColors(19, 26, 0xFFFFFF00);
        if (yesNo == 0) {
            fn_801F6ED0(&slots[20], 1.0f, 1.0f);
            fn_801F6ED0(&slots[21], 0.6f, 0.6f);
            fn_801F6D58(&slots[23], &sTbl1F0[0], 0, 0);
            fn_801F6D58(&slots[24], &sTbl210[0], 0, 0);
            fn_801F6C2C(&slots[25], (Rect *)&sTbl128[0x24], 1, 0);
        } else {
            fn_801F6ED0(&slots[20], 0.6f, 0.6f);
            fn_801F6ED0(&slots[21], 1.0f, 1.0f);
            fn_801F6D58(&slots[23], &sTbl1F0[1], 0, 0);
            fn_801F6D58(&slots[24], &sTbl210[1], 0, 0);
            fn_801F6C2C(&slots[25], (Rect *)&sTbl128[0x24], 0, 0);
        }
        state = 6;
    }
}

/* 4 */
void clEzMenu::UpdSelOut() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(6, 19, RGBA(c, c, c, 0xFF));
    if (StepFade()) {
        SetColors(6, 19, 0xFFFFFFFF);
        StrPcb_RunAndWaitIdle(StrPcb_GetInstance());
        StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
        state = 5;
        clCGameDemoWC_StubBlr_800adda8(2);
    }
}

void clEzMenu::DrawSelIn() {
    DrawSlots(6, 12);
    DrawSlots(12, 19);
    DrawSlots(0, 6);
}

/* 3 */
void clEzMenu::UpdSelBack() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(0, 6, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    SetColors(12, 19, RGBA(0xFF, 0xFF, 0xFF, c));
    if (StepFade()) {
        SetColors(0, 6, 0xFFFFFFFF);
        SetColors(12, 19, 0xFFFFFF00);
        state = 1;
    }
}

/* 2 */
void clEzMenu::UpdSelIn() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(0, 6, RGBA(0xFF, 0xFF, 0xFF, c));
    SetColors(12, 19, RGBA(0xFF, 0xFF, 0xFF, 0xFF - c));
    if (StepFade()) {
        SetColors(0, 6, 0xFFFFFF00);
        SetColors(12, 19, 0xFFFFFFFF);
        StrPcb_RunAndWaitIdle(StrPcb_GetInstance());
        StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
        state = 5;
        clCGameDemoWC_StubBlr_800adda8(2);
    }
}

void clEzMenu::DrawTitle() {
    DrawSlots(0, 6);
}

/* 1 */
void clEzMenu::UpdTitle() {
    if (Pad()->Pressed(0x400)) {
        fn_8020A7CC(fade.p, 0xFF, 0, 22);
        fn_801F6F7C(&slots[18], &lbl_804E4D30[sel], 1.0f);
        state = 2;
    }
}

/* 0 */
void clEzMenu::UpdTitleIn() {
    unsigned char c = fn_8020A788(fade.p);
    SetColors(0, 6, RGBA(c, c, c, 0xFF));
    if (StepFade()) {
        SetColors(0, 6, 0xFFFFFFFF);
        state = 1;
    }
}

EzFn sUpdate[14] = {
    &clEzMenu::UpdTitleIn,  &clEzMenu::UpdTitle,    &clEzMenu::UpdSelIn,   &clEzMenu::UpdSelBack,
    &clEzMenu::UpdSelOut,   &clEzMenu::UpdSel,      &clEzMenu::UpdYesNoBack, &clEzMenu::UpdYesNoIn,
    &clEzMenu::UpdYesNo,    &clEzMenu::UpdLevelBack, &clEzMenu::UpdLevelIn, &clEzMenu::UpdLevel,
    &clEzMenu::UpdLevelOut, &clEzMenu::UpdExit,
};

EzFn sDraw[14] = {
    &clEzMenu::DrawTitle,   &clEzMenu::DrawTitle,   &clEzMenu::DrawSelIn,  &clEzMenu::DrawSelIn,
    &clEzMenu::DrawSel,     &clEzMenu::DrawSel,     &clEzMenu::DrawYesNo,  &clEzMenu::DrawYesNo,
    &clEzMenu::DrawYesNoIn, &clEzMenu::DrawLevelIn, &clEzMenu::DrawLevelIn, &clEzMenu::DrawLevel,
    &clEzMenu::DrawLevel,   &clEzMenu::DrawNone,
};

void clEzMenu::Draw() {
    GX_EndDraw(0);
    (this->*sDraw[state % 14])();
    GX_BeginDraw();
}

void clEzMenu::Update() {
    (this->*sUpdate[state % 14])();
}

clEzMenu::~clEzMenu() {
    delete[] slots;
    delete ctx;
}

void clEzMenu::Destroy() {
    delete this;
}
