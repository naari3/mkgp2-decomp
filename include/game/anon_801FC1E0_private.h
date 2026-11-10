#ifndef GAME_ANON_801FC1E0_PRIVATE_H
#define GAME_ANON_801FC1E0_PRIVATE_H
#include "game/cxc_card_flow.h"
#include "game/singleton.h"

/*
 * Card / continue flow scenes @ 0x801FC1E0..0x801FD320.
 *
 * FlowScene (ctor fn_801FD41C, dtor dtor_801FD32C) is the shared base;
 * CardFlowScene (vtable CardFlowScene_vtable_804EC02C) and CoinFlowScene (vtable
 * CoinFlowScene_vtable_804EBFAC) derive from it. Vtables live in the auto .data blob; the
 * undeclared key virtual keeps CW from emitting them here.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

extern "C" {
void CreditMgr_SetActiveSlot(int slot);
int CreditMgr_GetCoinCount(int slot, int mode);
}

#include "game/types/VObject.h"

struct FlowTask {
    virtual void _key();
    virtual void f0C();
    virtual void f10();
    int count;
};

struct FlowScene {
    virtual void _key();
    char pad04[8];
    int done;
    FlowTask *task;
    CardFader *fader;
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

#include "game/types/ItemMsgWnd.h"

struct CoinCounter {
    char body[0x10];
    CoinCounter(int slot);
};

struct CoinWindow {
    char body[0x68];
    CoinWindow();
};

#include "game/types/CoinPrompt.h"

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

#include "game/types/CoinPromptHolder.h"

struct CoinPopupDetail {
    ~CoinPopupDetail();
};

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline InputState *GetInput() {
    return SINGLETON_INSTANCE(g_pInputState);
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

extern "C" {
extern unsigned char lbl_806D19C0;
extern int lbl_806D19C4;
/* fakematch: natural decl is `extern int lbl_806D19C8[2];` (written by
 * anon_801FD320.cpp). The const view lets the scheduler hoist the fade
 * duration load above the `subState = N` store, as in the target
 * (fn_801FCBCC, fn_801FCD9C). */
extern const int lbl_806D19C8[2];
extern unsigned char g_playerData[];
extern int g_currentSceneState;
void fn_80203F5C(int);
void card_save_trigger(int);
unsigned char CardSave_Tick();
int Sci2Card_GetPrintErrorCode();
int fn_801FDA78(int);
int fn_801FDCA8(int);
void fn_80203E4C();
void fn_802078B4();
int CardRW_GetSubState();
void card_eject_init();
unsigned char card_eject_state_machine();
void fn_801D7610(void *, int);
unsigned char fn_80207C64();
int fn_801FE858(CardInput *);
void fn_80207CC4(int);
int CreditMgr_GetPlayState(int);
int CreditMgr_GetCreditCount(int);
unsigned char CreditMgr_TryConfirmPlay(int);
void fn_801FE348();
void fn_801FE390();
void fn_801FE3BC();
void fn_801FE404();
void fn_801FE27C(int);
void PlayerData_ResetForFlow();
void fn_80207B28(int);
unsigned char Sci2Card_GetReceiptTestFlag();
void fn_80207AD8(int, int);
void fn_802078F8();
unsigned char fn_80207880();
void fn_801FCBCC(CardFlowScene *);
void fn_801FCD9C(CardFlowScene *);
void fn_801FCF58(CardFlowScene *);
}

static inline unsigned char CardCreditUnavailable(CardFlowScene *self) {
    if (CreditMgr_GetPlayState(0) == 3) return 1;
    if (CreditMgr_GetCreditCount(self->slot) == 0) return 1;
    return 0;
}
#endif
