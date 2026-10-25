/*
 * 0x802253EC..0x80226640: network single-play join scene (vtable
 * lbl_804EDF3C, base clSceneInterface lbl_803FE0C8). Scrolls a "waiting
 * for host" text, waits for the host PCB through a SyncWaiter and lets the
 * player open a coin popup (NetJoinPopup) while waiting.
 */

#include "game/FlowScene.h"

typedef long long OSTime;
extern "C" OSTime OSGetTime(void);
#define OS_BUS_CLOCK (*(unsigned long *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))

struct Sprite {
    int x0;
    int layer;
    int x8;
    float x;
    float y;
    char pad14[0x20 - 0x14];
    float alpha;
    char pad24[0x30 - 0x24];
    Sprite(int res, int a, int b);
    ~Sprite();
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

struct SpriteBox {
    int h;
    SpriteBox(ResCtrl *rc, int layer);
    ~SpriteBox();
    void Cull();
    void SetActive(int on);
    void SetAlpha(int a);
};

struct TextSprite {
    char pad000[8];
    float width;
    char pad00C[0x18 - 0xC];
    int visible;
    char pad01C[0x230 - 0x1C];
    TextSprite();
    ~TextSprite() {}
    TextManager *tm() { return (TextManager *)this; }
};

struct SceneObj {
    char pad00[0x20];
    SceneObj(int a, int b, int c, int d, int e);
    ~SceneObj();
    void Update();
    void Draw();
};

struct SyncWaiter {
    char pad00[0x14];
    virtual ~SyncWaiter();
    virtual void v0C();
    virtual void v10();
    virtual void Update();
    virtual void Draw();
    char pad18[0x4C - 0x18];
    SyncWaiter();
};

struct FlowPanel {
    int state;
    char pad04[0x1C];
    unsigned char showBg;
    unsigned char x21;
    char pad22[0x46];
    FlowPanel();
};

struct CoinPopupDetail {
    char pad00[0x10];
    int state;
    int pad14;
    int mode;
    char pad1C[0x8C - 0x1C];
    CoinPopupDetail(int a, int b, int c);
    int Mode() { return state < 2 ? 2 : mode; }
    unsigned char Closed() { return state == 6; }
};

struct ItemMsgWnd {
    char body[0x5C];
    ItemMsgWnd();
};

struct PcbMode {
    char pad00[8];
    int mode;
    int sub;
};

struct RankLog;

extern "C" {
extern ItemMsgWnd *lbl_806D1A88;
extern RankLog *lbl_806D10A0;
extern unsigned char lbl_806D17F0;
extern unsigned char lbl_806D17F1;
extern int lbl_806D1A78;
extern int g_localPcbRole;
extern const float lbl_806DB358;
extern const float lbl_806DB35C;
extern const float lbl_806DB360;
extern const float lbl_806DB364;
extern const float lbl_806DB368;
extern const float lbl_806DB36C;
extern const float lbl_806DB370;
extern const float lbl_806DB374;
extern const float lbl_806DB378;
extern const float lbl_806DB37C;
extern const float lbl_806DB380;
extern const float lbl_806DB384;
extern const float lbl_806DB388;
extern const float lbl_806DB38C;
extern const float lbl_806DB390;
extern const float lbl_806DB394;
extern const float lbl_806DB398;
extern const float lbl_806DB39C;
extern const float lbl_806DB3A0;
extern const float lbl_806DB3A4;
extern const float lbl_806DB3A8;
extern const float lbl_806DB3AC;
extern const float lbl_806DB3B0;
extern const float lbl_806DB3B4;
extern const float lbl_806DB3B8;
extern const float lbl_806DB3C8;
PcbMode *fn_801DAEC0(void);
void SetLocalPcbRole(int role);
void SetSyncTarget(int target);
float PcbSyncTable_LookupValueByState(int state);
void SetPcbScratchFlag_806d11a4(void);
unsigned char PCBComm_ConfirmHostBattle(void);
void PlayStats_IncSinglePlayJoin(void);
int fn_8021B568(SyncWaiter *w);
void fn_8021B5D4(SyncWaiter *w);
void fn_8021B5F4(SyncWaiter *w, int a);
void fn_801D9A2C(FlowPanel *p);
void fn_801D9B70(FlowPanel *p, int pressed);
void fn_801D9F88(FlowPanel *p, short flag);
void fn_801D919C(FlowPanel *p);
void fn_801D8E28(FlowPanel *p, float x, float y);
void fn_801D9180(FlowPanel *p, int v);
void clFlowKart_SetupTextLayout(FlowPanel *p, int layout);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int mode);
const char *GetTextureByIdAndLang(unsigned int id, int lang);
void fn_8023CD3C(SceneObj *p, float a, float b);
void fn_8023CCF8(SceneObj *p, float a, float b);
void fn_8023CD24(SceneObj *p, float a, float b);
void fn_8023CCCC(SceneObj *p, float a, float b);
void fn_8023CEB4(SceneObj *p);
void fn_8023CFD4(SceneObj *p);
void fn_80232284(ItemMsgWnd *wnd, float t);
void fn_801FE27C(int t);
void fn_801FE348(void);
void TitleStats_ResetRaceStagingState(RankLog *log);
void RankLog_OnRoundComplete(RankLog *log);
void fn_80161F28(CoinPopupDetail *p, int flag);
void fn_8016039C(CoinPopupDetail *p);
void fn_80160588(CoinPopupDetail *p, int dir, bool b);
void fn_801A0004(Sprite *spr);
unsigned char fn_8019FE78(Sprite *spr);
void Sprite_SetupAnim(Sprite *spr, int anim, int loop, int arg);
unsigned char Sprite_AdvanceAnim(Sprite *spr, float dt);
void fn_80121E10(ResCtrl *rc);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_SetCornerAlpha(int sprite, int alpha);
void SpriteHandle_RecomputeCull(int sprite);
}

inline SpriteBox::SpriteBox(ResCtrl *rc, int layer) {
    h = SpriteHandle_CreateDefault(rc, layer);
}

inline SpriteBox::~SpriteBox() {
    if (h >= 0) {
        SpriteHandle_Destroy(h);
        h = -1;
    }
}

inline void SpriteBox::Cull() {
    if (h >= 0) {
        SpriteHandle_RecomputeCull(h);
    }
}

inline void SpriteBox::SetActive(int on) {
    if (h >= 0) {
        SpriteHandle_SetActiveFlag(h, on);
    }
}

inline void SpriteBox::SetAlpha(int a) {
    if (h >= 0) {
        SpriteHandle_SetCornerAlpha(h, a);
    }
}

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline RankLog *GetRankLog() {
    return lbl_806D10A0 == 0 ? (RankLog *)0 : lbl_806D10A0;
}

static inline void SetPcbMode(int mode) {
    PcbMode *m = fn_801DAEC0();
    m->mode = mode;
}

static inline void SetPcbSub(int sub) {
    PcbMode *m = fn_801DAEC0();
    m->sub = sub;
}

static inline void SetInput(unsigned char en) {
    InputState *in = GetInput();
    in->enabled = en;
    in->held = 0;
    in->edge = 0;
}

struct NetJoinPopup {
    int state;
    int timer;
    bool ok;
    CoinPopupDetail *popup;
    Sprite *spr;
    SpriteBox *boxes[3];
    NetJoinPopup();
    ~NetJoinPopup();
    void Draw();
    void Update();
};

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
    SceneBase() : done(false) {}
};

struct clCSSceneNetJoin : SceneBase {
    int state;
    float time;
    int x10;
    int x14;
    int x18;
    unsigned char x1c;
    float scroll;
    unsigned char joined;
    float scrollMin;
    char pad2C[4];
    OSTime t0;
    unsigned char timing;
    int count;
    FlowSceneList *list;
    SyncWaiter *waiter;
    FlowPanel *panel;
    SpriteBox *box;
    TextSprite *text;
    SceneObj *prompt;
    NetJoinPopup *popup;
    clCSSceneNetJoin();
    ~clCSSceneNetJoin();
    void Destroy();
    void Update();
    void Draw();
};

void clCSSceneNetJoin::Draw() {
    waiter->Draw();
    fn_801D9A2C(panel);
    fn_801F8A34(fn_801F8E58(), text->tm(), 1);
    prompt->Draw();
    list->Draw();
    if (popup) {
        popup->Draw();
    }
}

void clCSSceneNetJoin::Update() {
    if (done == 1) {
        return;
    }
    if (state == 4) {
        done = 1;
        return;
    }
    if (count < 30) {
        if (++count == 30) {
            SetSyncTarget(0x32);
        }
    }
    bool pressed;
    InputState *in;
    float t = PcbSyncTable_LookupValueByState(g_localPcbRole);
    in = GetInput();
    pressed = in->held == 1;
    if (state >= 1) {
        if (pressed == 1) {
            SetPcbMode(4);
        } else {
            SetPcbMode(1);
        }
    }
    switch (state) {
    case 0:
        if (time >= lbl_806DB358) {
            time = lbl_806DB35C;
            state = 1;
            SetPcbSub(1);
        }
        break;
    case 1:
        if (pressed) {
            SetPcbMode(4);
            SetPcbScratchFlag_806d11a4();
        }
        if (in->held == 3 && t >= lbl_806DB360 && timing == 0) {
            SetPcbSub(4);
            state = 2;
            joined = 1;
            if (popup == 0) {
                popup = new NetJoinPopup;
            }
            break;
        }
        if (fn_8021B568(waiter) == 0 && timing == 0) {
            timing = 1;
            t0 = OSGetTime();
            fn_8021B5D4(waiter);
        }
        if (timing == 1 && (float)OSTicksToMilliseconds(OSGetTime() - t0) / lbl_806DB364 >= lbl_806DB368 && PCBComm_ConfirmHostBattle() == 1) {
            t0 = OSGetTime();
            time = lbl_806DB35C;
            state = 3;
            fn_801D919C(panel);
            if (g_localPcbRole != 0) {
                lbl_806D17F1 = 1;
            } else {
                lbl_806D17F1 = 0;
            }
        }
        break;
    case 2:
        if (fn_8021B568(waiter) == 0 && timing == 0) {
            timing = 1;
            t0 = OSGetTime();
            time = lbl_806DB35C;
            state = 1;
            joined = 0;
            if (popup) {
                delete popup;
                popup = 0;
            }
            break;
        }
        if (popup->state == 4) {
            joined = 0;
            if (popup->ok == 1) {
                joined = 1;
                state = 3;
                time = lbl_806DB35C;
                t0 = 0;
                fn_801D919C(panel);
            } else {
                SetInput(1);
                state = 1;
                time = lbl_806DB35C;
                SetPcbSub(1);
            }
            if (popup) {
                delete popup;
                popup = 0;
            }
            break;
        }
        if (t <= lbl_806DB360) {
            time = lbl_806DB35C;
            state = 1;
            joined = 0;
            if (popup) {
                delete popup;
                popup = 0;
            }
        }
        break;
    case 3:
        if (panel->state == 0 && (float)OSTicksToMilliseconds(OSGetTime() - t0) / lbl_806DB364 >= lbl_806DB36C) {
            lbl_806D17F0 = 1;
            fn_801FE348();
            if (joined == 1) {
                SetSyncTarget(0xD);
                SetLocalPcbRole(0);
                lbl_806D17F1 = 0;
            }
            fn_8021B5D4(waiter);
            RankLog *log = GetRankLog();
            if (log) {
                RankLog_OnRoundComplete(log);
                TitleStats_ResetRaceStagingState(log);
            }
            time = lbl_806DB35C;
            state = 4;
            SetPcbMode(0);
            SetPcbSub(0);
        }
        break;
    }
    if (popup == 0) {
        scroll -= lbl_806DB370;
        if (scroll <= -scrollMin) {
            scroll = scrollMin;
        }
        fn_801F93EC(text->tm(), scroll, lbl_806DB374);
        waiter->Update();
        fn_801D9B70(panel, 0);
        box->Cull();
        prompt->Update();
        list->Update();
    } else {
        popup->Update();
    }
    if (state >= 3) {
        t = lbl_806DB378;
    } else {
        fn_801FE27C((int)t);
    }
    fn_80232284(ItemMsg_Get(), t);
    time += lbl_806DB37C;
}

clCSSceneNetJoin::~clCSSceneNetJoin() {
    SetInput(0);
    if (popup) {
        delete popup;
        popup = 0;
    }
    if (prompt) {
        delete prompt;
        prompt = 0;
    }
    if (text) {
        delete text;
        text = 0;
    }
    if (panel) {
        fn_801D9F88(panel, 1);
        panel = 0;
    }
    if (box) {
        delete box;
        box = 0;
    }
    if (waiter) {
        delete waiter;
        waiter = 0;
    }
    if (list) {
        delete list;
        list = 0;
    }
}

clCSSceneNetJoin::clCSSceneNetJoin() {
    state = 0;
    time = lbl_806DB35C;
    x10 = 0;
    x14 = 1;
    x18 = lbl_806D1A78 + 1;
    x1c = 0;
    scroll = lbl_806DB380;
    joined = 0;
    scrollMin = lbl_806DB35C;
    t0 = 0;
    timing = 0;
    count = 0;
    list = new SceneListImpl;
    waiter = 0;
    panel = 0;
    box = 0;
    prompt = 0;
    popup = 0;
    SetInput(1);
    waiter = new SyncWaiter;
    fn_8021B5F4(waiter, 1);
    panel = new FlowPanel;
    clFlowKart_SetupTextLayout(panel, 0xE);
    fn_801D8E28(panel, lbl_806DB374, lbl_806DB384);
    panel->x21 = 0;
    fn_801D9180(panel, 1);
    ResCtrl rc;
    rc.resId = 0x157C;
    rc.Show(lbl_806DB374, lbl_806DB374, lbl_806DB37C);
    rc.SetScaleXY(lbl_806DB388, lbl_806DB37C);
    box = new SpriteBox(&rc, 1);
    box->Cull();
    text = new TextSprite;
    text->visible = 1;
    TexMgr_SetTexture((TextManager *)text, GetTextureByIdAndLang(0x74, -1));
    fn_801F93EC(text->tm(), scroll, lbl_806DB374);
    prompt = new SceneObj(0x73, 0x14, 0x1B1F, 0x1B1E, 1);
    fn_8023CD3C(prompt, lbl_806DB38C, lbl_806DB390);
    fn_8023CCF8(prompt, lbl_806DB394, lbl_806DB398);
    fn_8023CD24(prompt, lbl_806DB39C, lbl_806DB390);
    fn_8023CCCC(prompt, lbl_806DB3A0, lbl_806DB398);
    fn_8023CEB4(prompt);
    fn_8023CFD4(prompt);
    fn_801F8FCC(text->tm(), 2);
    fn_801F8E90(text->tm());
    scrollMin = -text->width;
    fn_801F8FCC(text->tm(), 0);
    fn_801F8E90(text->tm());
    SetSyncTarget(0x31);
    SetLocalPcbRole(5);
    PlayStats_IncSinglePlayJoin();
}

void clCSSceneNetJoin::Destroy() {
    delete this;
}

extern "C" clCSSceneNetJoin *fn_80225F6C(void) {
    return new clCSSceneNetJoin;
}

void NetJoinPopup::Draw() {
    if (spr) {
        fn_801A0004(spr);
    }
    if (popup) {
        fn_8016039C(popup);
    }
}

void NetJoinPopup::Update() {
    InputState *in = GetInput();
    bool pressed = in->held == 1;
    switch (state) {
    case 0:
        if (timer <= 10) {
            boxes[2]->SetAlpha((int)(lbl_806DB3B0 * (timer / lbl_806DB3B4)));
        }
        if (!fn_8019FE78(spr)) {
            boxes[0]->SetActive(1);
            boxes[1]->SetActive(1);
            spr->alpha = lbl_806DB35C;
            popup = new CoinPopupDetail(0, 1, 9);
            state = 1;
            timer = 0;
        }
        break;
    case 1:
        ok = popup->Mode() == 0;
        if (popup->Mode() != 2) {
            state = 2;
            timer = 0;
        }
        break;
    case 2:
        if (popup->Closed() == 1) {
            Sprite_SetupAnim(spr, 0x11, 1, 0);
            boxes[0]->SetActive(0);
            boxes[1]->SetActive(0);
            state = 3;
            timer = 0;
        }
        break;
    case 3:
        if (timer <= 10) {
            boxes[2]->SetAlpha((int)(lbl_806DB3B0 * (lbl_806DB37C - timer / lbl_806DB3B4)));
        }
        if (timer >= 10 && !fn_8019FE78(spr)) {
            state = 4;
            timer = 0;
        }
        break;
    }
    timer++;
    if (popup) {
        fn_80160588(popup, in->dir, pressed);
    }
    if (spr) {
        Sprite_AdvanceAnim(spr, lbl_806DB3B8);
    }
    for (int i = 0; i < 3; i++) {
        if (boxes[i]) {
            boxes[i]->Cull();
        }
    }
}

NetJoinPopup::~NetJoinPopup() {
    if (popup) {
        fn_80161F28(popup, 1);
        popup = 0;
    }
    if (spr) {
        delete spr;
        spr = 0;
    }
    for (int i = 0; i < 3; i++) {
        if (boxes[i]) {
            delete boxes[i];
            boxes[i] = 0;
        }
    }
}

NetJoinPopup::NetJoinPopup() {
    state = 0;
    timer = 0;
    ok = 1;
    popup = 0;
    spr = 0;
    spr = new Sprite(0x12, 1, 0);
    spr->SetPos(lbl_806DB374, lbl_806DB3C8);
    spr->layer = 2;
    ResCtrl rc;
    rc.mode = 2;
    rc.SetSize(lbl_806DB380, lbl_806DB3A4);
    rc.Show(lbl_806DB374, lbl_806DB3A8, lbl_806DB37C);
    rc.SetColor(0);
    boxes[2] = new SpriteBox(&rc, 2);
    fn_80121E10(&rc);
    rc.resId = 0x1E88;
    rc.Show(lbl_806DB374, lbl_806DB3C8, lbl_806DB37C);
    boxes[0] = new SpriteBox(&rc, 2);
    boxes[0]->SetActive(0);
    fn_80121E10(&rc);
    rc.resId = 0x1AEA;
    rc.Show(lbl_806DB374, lbl_806DB3AC, lbl_806DB37C);
    boxes[1] = new SpriteBox(&rc, 2);
    boxes[1]->SetActive(0);
    for (int i = 0; i < 3; i++) {
        boxes[i]->Cull();
    }
    if (GetRankLog()) {
        TitleStats_ResetRaceStagingState(GetRankLog());
    }
    SetPcbSub(0);
}
