#ifndef CONTINUE_SCENE_PRIVATE_H
#define CONTINUE_SCENE_PRIVATE_H
/*
 * Continue (insert coin) flow scene @ 0x8024D764..0x8024E338.
 *
 * ContinueScene derives from FlowScene (vtable ContinueScene_vtable_804EF000). CoinCounter
 * (0x10 bytes) is defined first so CW auto-inlines its methods into the
 * scene; its out-of-line copies are the functions at the end of the range.
 */

#include "game/FlowScene.h"

struct CoinWindow {
    int state;
    char pad04[0x1C];
    unsigned char visible;
    char pad21[0x47];
    CoinWindow();
};

#include "game/types/CoinPrompt.h"

struct CoinPopupDetail {
    int pad00[4];
    int state;
    int pad14;
    int mode;
    char pad1C[0x8C - 0x1C];
    CoinPopupDetail(int a, int b, int c);
};

#include "game/types/ItemMsgWnd.h"

struct MsgParam {
    int a;
    int b;
    const char *c;
    const char *d;
    const char *e;
    int f;
    int g;
};

struct RoundResult {
    unsigned char pad00[2];
    unsigned char pending;
    unsigned char pad03;
    int cup;
    int round;
    char pad0C[8];
    unsigned char done;
};

struct ItemDisplay;
struct RankLog;

extern "C" {
extern ItemMsgWnd *lbl_806D1A88;
extern const int lbl_806D1AB8;
extern unsigned char lbl_806D17F0;
extern unsigned char lbl_806D17F1;
extern unsigned char lbl_806D17F2;
extern int lbl_806D12C0;
extern RankLog *lbl_806D10A0;
extern int g_gameMode;
extern int g_cupId;
extern int g_ccClass;
extern int g_roundIndex;
extern char g_playerData[];
extern const char lbl_806DC020[4];
extern const char lbl_803F0848[];
extern const char ContinueScene_rodata_803F0860[];
extern const char lbl_803EFEA0[];
extern const char *lbl_806D0970[2];
extern unsigned char lbl_80598A60[];
extern const float lbl_806DC024;
extern const float lbl_806DC028;
extern const float lbl_806DC02C;
extern const float lbl_806DC030;
extern const float lbl_806DC014;
extern const float lbl_806DC010;
extern const float lbl_806DC00C;
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
bool CreditMgr_TryConfirmPlay(int slot);
void fn_801D9F88(CoinWindow *p, int flag);
void fn_801D9A2C(CoinWindow *p);
void fn_801D9B70(CoinWindow *p, bool on);
void fn_801D8DF8(CoinWindow *p, const char *text, int line);
void fn_801D919C(CoinWindow *p);
void fn_801D92D0(CoinWindow *p, MsgParam *param);
void fn_8023CFE0(CoinPrompt *p, int flag);
void fn_8023CEB4(CoinPrompt *p);
void fn_8023CD3C(CoinPrompt *p, float a, float b);
void fn_8023CCF8(CoinPrompt *p, float a, float b);
void fn_8023CD24(CoinPrompt *p, float a, float b);
void fn_8023CCCC(CoinPrompt *p, float a, float b);
void fn_80232284(ItemMsgWnd *wnd, float t);
void fn_801618CC(CoinPopupDetail *p, int a, int b);
void fn_80161F28(CoinPopupDetail *p, int flag);
void fn_80161888(CoinPopupDetail *p);
void fn_8020A7CC(FlowFaderI *f, int a, int b, int c);
ItemDisplay *ItemDisplay_GetOrCreate(void);
void fn_8020AAD4(ItemDisplay *d);
void fn_801FE27C(int t);
void TitleStats_ResetRaceStagingState(RankLog *log);
void RankLog_OnRoundComplete(RankLog *log);
RoundResult *fn_8024F588(void);
void DebugPrintf(const char *fmt, ...);
int sprintf(char *buf, const char *fmt, ...);
unsigned char fn_801D5C88(void *data, int cc);
unsigned char fn_801D5B8C(void *data, int cc, int cup, int mode);
}

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline RankLog *GetRankLog() {
    return lbl_806D10A0 == 0 ? (RankLog *)0 : lbl_806D10A0;
}

static inline bool IsNoCredit() {
    if (CreditMgr_GetPlayState(0) == 3) {
        return 1;
    }
    if (CreditMgr_GetCreditCount(1) == 0) {
        return 1;
    }
    return 0;
}

#include "game/types/CoinPromptHolder.h"

struct CoinCounter {
    int slot;
    int timer;
    unsigned char done;
    CoinWindow *window;
    CoinCounter(int s);
    ~CoinCounter();
    void Update();
    void Draw();
    void Show();
};

struct ContinueScene : FlowScene {
    int retries;
    int coins;
    unsigned char noCredit;
    unsigned char started;
    CoinCounter *counter;
    CoinPopupDetail *detail;
    CoinPromptHolder prompt;
    ContinueScene(int id);
    ~ContinueScene();
    virtual void _key4();
    void Update();
    void Confirm();
    void Cancel();
};


#endif
