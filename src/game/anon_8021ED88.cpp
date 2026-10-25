/*
 * 0x8021ED88..0x8021F088: clCSSceneChangeSingle (vtable lbl_804EDE1C, base
 * clSceneInterface lbl_803FE0C8). Shows one FlowPanel message, then drops
 * the local PCB role back to 0.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0xF];
    int dir;
    int held;
    int edge;
};

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
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}

static inline void SetInput(unsigned char en) {
    InputState *in = GetInput();
    in->enabled = en;
    in->held = 0;
    in->edge = 0;
}

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
    SceneBase() : done(false) {}
};

struct clCSSceneChangeSingle : SceneBase {
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

void clCSSceneChangeSingle::Draw() {
    if (panel) {
        fn_801D9A2C(panel);
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

clCSSceneChangeSingle::~clCSSceneChangeSingle() {
    if (panel) {
        fn_801D9F88(panel, 1);
        panel = 0;
    }
    if (GetInput()) {
        SetInput(0);
    }
}

void clCSSceneChangeSingle::Destroy() {
    delete this;
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

extern "C" clCSSceneChangeSingle *fn_8021EFB4(void) {
    return new clCSSceneChangeSingle;
}
