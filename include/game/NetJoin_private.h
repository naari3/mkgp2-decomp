#ifndef NET_JOIN_PRIVATE_H
#define NET_JOIN_PRIVATE_H
/*
 * 0x802253EC..0x80226640: network single-play join scene (vtable
 * clCSSceneNextRaceBT_vtable_804EDF3C, base clSceneInterface lbl_803FE0C8). Scrolls a "waiting
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

#include "game/types/SceneObj.h"

#include "game/types/SyncWaiter.h"

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

#include "game/types/ItemMsgWnd.h"

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

#include "game/types/clSceneInterface.h"

struct clCSSceneNextRaceBT : clSceneInterface {
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
    clCSSceneNextRaceBT();
    ~clCSSceneNextRaceBT();
    void Destroy();
    void Update();
    void Draw();
};


#endif
