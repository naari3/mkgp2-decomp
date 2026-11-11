#ifndef GAME_TYPES_CLMNCARDT01_H
#define GAME_TYPES_CLMNCARDT01_H
#include "game/types/clMnCardClasses.h"
#include "game/singleton.h"
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

struct CardChoicePanel;

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
void fn_80161F28(CardChoicePanel *p, int flag);
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


struct CardChoicePanel {
    char pad[0x10]; int state; int pad14; int result;
    float x, y, x2, y2;
    char pad2c[0x24]; char group50[0x10]; TextManager *center;
    char pad64[8]; float offset[8];
    CardChoicePanel(int, int, int);
};
struct clMnCardT01 : clMnCardT0Interface {
    int kind;
    unsigned char field2C; char pad2D[3];
    int field30;
    TextManager *texts;
    int coins;
    unsigned char field3C; char pad3D[3];
    int field40;
    CoinCounter *counter;
    CardChoicePanel *detail;
    CoinWindowHolder window;
    CoinPromptHolder prompt;
    clMnCardT01(int);
    virtual ~clMnCardT01();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    void FadeIn();
    void FadeOut();
    void Select();
};
#endif
