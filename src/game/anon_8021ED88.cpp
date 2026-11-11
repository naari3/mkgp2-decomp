#include "game/types/size_t.h"
#include "game/singleton.h"
/*
 * 0x8021ED88..0x8021F088: clCSSceneChangeSingle (vtable clCSSceneChangeSingle_vtable_804EDE1C, base
 * clSceneInterface lbl_803FE0C8). Shows one FlowPanel message, then drops
 * the local PCB role back to 0.
 */

void *operator new(size_t size);
void operator delete(void *p) throw();

#include "game/types/InputState.h"

struct FlowPanel {
    int state;
    char pad04[0x1C];
    unsigned char showBg;
    char pad21[0x47];
    FlowPanel();
};

extern "C" {
void fn_801D9A2C(FlowPanel *self);
void fn_801D9B70(FlowPanel *self, int pressed);
void fn_801D9F88(FlowPanel *self, short flag);
void clFlowKart_SetupTextLayout(FlowPanel *self, int layout);
void SetLocalPcbRole(int role);
extern InputState *g_pInputState;
extern unsigned char lbl_806D17F1;
extern const float lbl_806DB188;
}

static inline InputState *GetInput() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline void SetInput(unsigned char en) {
    InputState *in = GetInput();
    in->enabled = en;
    in->held = 0;
    in->edge = 0;
}

#include "game/types/clSceneInterface.h"

struct clCSSceneChangeSingle : clSceneInterface {
    int state;
    float xc;
    int x10;
    int x14;
    FlowPanel *panel;
    clCSSceneChangeSingle();
    ~clCSSceneChangeSingle();
    void Destroy();
    void Update();
    void Draw();
};

extern "C" clCSSceneChangeSingle *fn_8021EFB4(void) {
    return new clCSSceneChangeSingle;
}
inline clCSSceneChangeSingle::clCSSceneChangeSingle() {
    state = 0;
    xc = lbl_806DB188;
    x10 = 0;
    x14 = 1;
    panel = 0;
    panel = new FlowPanel;
    if (GetInput()) {
        SetInput(1);
    }
}

void clCSSceneChangeSingle::Destroy() {
    delete this;
}

clCSSceneChangeSingle::~clCSSceneChangeSingle() {
    if (panel) {
        fn_801D9F88(panel, 1);
        panel = 0;
    }
    if (GetInput()) {
        SetInput(0);
    }
}

void clCSSceneChangeSingle::Update() {
    if (done == 1) {
        return;
    }
    if (state == 3) {
        done = 1;
        return;
    }
    int pressed = GetInput()->held == 1 ? 1 : 0;
    switch (state) {
    case 0:
        clFlowKart_SetupTextLayout(panel, 0xf);
        panel->showBg = 0;
        state = 1;
        break;
    case 1:
        if (panel->state == 0) {
            state = 2;
        }
        break;
    case 2:
        state = 3;
        lbl_806D17F1 = 0;
        SetLocalPcbRole(0);
        break;
    }
    if (panel) {
        fn_801D9B70(panel, pressed);
    }
}

void clCSSceneChangeSingle::Draw() {
    if (panel) {
        fn_801D9A2C(panel);
    }
}
