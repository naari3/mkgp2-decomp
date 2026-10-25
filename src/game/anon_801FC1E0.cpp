/*
 * Card / continue flow scenes @ 0x801FC1E0..0x801FD320.
 *
 * FlowScene (ctor fn_801FD41C, dtor dtor_801FD32C) is the shared base;
 * CardFlowScene (vtable lbl_804EC02C) and CoinFlowScene (vtable
 * lbl_804EBFAC) derive from it. Vtables live in the auto .data blob; the
 * undeclared key virtual keeps CW from emitting them here.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

extern "C" {
void CreditMgr_SetActiveSlot(int slot);
int CreditMgr_GetCoinCount(int slot, int mode);
}

struct VObject {
    virtual ~VObject();
};

struct FlowTask {
    virtual void _key();
    virtual void f0C();
    virtual void f10();
};

struct FlowScene {
    virtual void _key();
    char pad04[0x0C];
    FlowTask *task;
    char pad14[0x04];
    int state;
    int subState;
    int timer;
    int cursor;
    FlowScene(int arg);
    ~FlowScene();
};

struct CardFlowScene : FlowScene {
    int kind;
    int arg2C;
    int field30;
    int coins;
    unsigned char field38;
    char pad39[3];
    int slot;
    unsigned char field40;
    unsigned char field41;
    char pad42[2];
    int field44;
    CardFlowScene(int arg, int base);
    ~CardFlowScene();
    virtual void _key2();
};

struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0x13];
    int held;
    int edge;
};

/* 0x230-byte text manager (ctor fn_80149214, dtor dtor_800869D0). */
struct TextManager {
    char pad000[0x18];
    int visible;
    char pad01C[0x22C - 0x1C];
    float scale;
    TextManager();
    ~TextManager();
};

struct ItemMsgWnd {
    char body[0x5C];
    ItemMsgWnd();
};

struct CoinCounter {
    char body[0x10];
    CoinCounter(int slot);
};

struct CoinWindow {
    char body[0x68];
    CoinWindow();
};

struct CoinPrompt {
    char body[0x20];
    CoinPrompt(int a, int b, int c, int d, int e);
};

struct CoinPopupDetail;

extern "C" {
extern InputState *g_pInputState;
extern ItemMsgWnd *lbl_806D1A88;
extern int lbl_803BFF40[];
extern const char *lbl_804EBF58[][3];
extern const float lbl_806DA800;
extern const float lbl_806DA820;
extern const float lbl_806DA824;
extern const float lbl_806DA828;
extern const float lbl_806DA82C;
extern const float lbl_806DA814;
extern const float lbl_806DA818;
extern const float lbl_806DA7EC;
extern const float lbl_806DA7E8;
extern const float lbl_806DA810;
extern const float lbl_806DA7E4;
int isJapanese(void);
void TexMgr_SetTexture(TextManager *tm, const char *fmt, ...);
void fn_801F93EC(TextManager *tm, float x, float y);
void fn_80232284(ItemMsgWnd *wnd, float t);
void fn_80161F28(CoinPopupDetail *p, int flag);
void fn_8024E244(CoinCounter *p, int flag);
void fn_80218D90(int mode);
char *fn_801DAEC0(void);
void fn_8023CFE0(CoinPrompt *p, int flag);
void fn_801D9F88(CoinWindow *p, int flag);
void fn_8023CEB4(CoinPrompt *p);
void fn_8023CD3C(CoinPrompt *p, float a, float b);
void fn_8023CCF8(CoinPrompt *p, float a, float b);
void fn_8023CD24(CoinPrompt *p, float a, float b);
void fn_8023CCCC(CoinPrompt *p, float a, float b);
void fn_8023CDA8(CoinPrompt *p);
void fn_8023CFD4(CoinPrompt *p);
}

struct CoinWindowHolder {
    CoinWindow *p;
    CoinWindowHolder(CoinWindow *q) : p(q) {}
    ~CoinWindowHolder() throw() { fn_801D9F88(p, 1); }
};

struct CoinPromptHolder {
    CoinPrompt *p;
    CoinPromptHolder(CoinPrompt *q) : p(q) {}
    ~CoinPromptHolder() throw() { fn_8023CFE0(p, 1); }
};

struct CoinPopupDetail {
    ~CoinPopupDetail();
};

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline InputState *GetInput() {
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}

struct CoinFlowScene : FlowScene {
    int kind;
    unsigned char field2C;
    char pad2D[3];
    int field30;
    TextManager *texts;
    int coins;
    unsigned char field3C;
    char pad3D[3];
    int field40;
    CoinCounter *counter;
    CoinPopupDetail *detail;
    CoinWindowHolder window;
    CoinPromptHolder prompt;
    CoinFlowScene(int arg);
    ~CoinFlowScene();
    virtual void _key2();
};

extern "C" CoinFlowScene *fn_801FC1E0(int arg) {
    return new CoinFlowScene(arg);
}

extern "C" void fn_801FC614(FlowScene *self) {
    self->task->f10();
}

CoinFlowScene::~CoinFlowScene() {
    fn_80232284(ItemMsg_Get(), lbl_806DA800);
    if (detail) {
        fn_80161F28(detail, 1);
    }
    fn_8024E244(counter, 1);
    delete[] texts;
    CreditMgr_SetActiveSlot(0);
    fn_80218D90(0);
    {
        char *mgr = fn_801DAEC0();
        *(int *)(mgr + 8) = 0;
    }
}

CoinFlowScene::CoinFlowScene(int arg)
    : FlowScene(arg), kind(2), field2C(0), field30(0), coins(CreditMgr_GetCoinCount(0, -1)),
      field3C(0), field40(0), counter(0), window(new CoinWindow),
      prompt(new CoinPrompt(0x74, 0x4A, 0x1874, 0x1875, 4)) {
    InputState *in;
    int jp;
    in = GetInput();
    in->enabled = 1;
    in->held = 0;
    in->edge = 0;
    timer = lbl_803BFF40[1] + 1;
    subState = 1;
    cursor = 0;
    state = 0;
    texts = new TextManager[3];
    texts[0].visible = 1;
    texts[1].visible = 1;
    texts[2].visible = 1;
    fn_801F93EC(&texts[0], lbl_806DA820, lbl_806DA824);
    fn_801F93EC(&texts[1], lbl_806DA820, lbl_806DA820);
    fn_801F93EC(&texts[2], lbl_806DA820, lbl_806DA828);
    jp = isJapanese() != 0;
    TexMgr_SetTexture(&texts[0], lbl_804EBF58[jp][0]);
    TexMgr_SetTexture(&texts[1], lbl_804EBF58[jp][1]);
    TexMgr_SetTexture(&texts[2], lbl_804EBF58[jp][2]);
    if (jp == 1) {
        texts[0].scale = lbl_806DA82C;
        texts[1].scale = lbl_806DA82C;
        texts[2].scale = lbl_806DA82C;
    }
    CreditMgr_SetActiveSlot(2);
    fn_80218D90(2);
    counter = new CoinCounter(2);
    fn_8023CEB4(prompt.p);
    fn_8023CD3C(prompt.p, lbl_806DA814, lbl_806DA818);
    fn_8023CCF8(prompt.p, lbl_806DA7EC, lbl_806DA7E8);
    fn_8023CD24(prompt.p, lbl_806DA810, lbl_806DA7E8);
    fn_8023CCCC(prompt.p, lbl_806DA7E4, lbl_806DA7E8);
    fn_8023CDA8(prompt.p);
    fn_8023CFD4(prompt.p);
    *((unsigned char *)window.p + 0x20) = 1;
}

CardFlowScene::~CardFlowScene() {
    CreditMgr_SetActiveSlot(0);
}

CardFlowScene::CardFlowScene(int arg, int base) : FlowScene(base) {
    kind = 5;
    arg2C = arg;
    field30 = 0;
    coins = CreditMgr_GetCoinCount(0, -1);
    field38 = 1;
    slot = 3;
    field40 = 0;
    field41 = 0;
    field44 = 0;
    state = 0;
    subState = 0;
    timer = 0x4B1;
    CreditMgr_SetActiveSlot(slot);
}

extern "C" void fn_801FD2E8(VObject *obj) {
    delete obj;
}
