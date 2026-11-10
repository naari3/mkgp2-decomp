#ifndef GAME_MENU801F0CC0_PRIVATE_H
#define GAME_MENU801F0CC0_PRIVATE_H
#include "game/types/pmf.h"
#include "game/FlowScene.h"
#include "game/TestMenuPage.h"

struct MenuRect801F { float x, y, w, h; };
struct MenuSprite801F {
    char opaque[0x94];
    ~MenuSprite801F();
};
struct MenuBase801F {
    virtual void _key();
    unsigned char active;
    char reserved[3];
    ~MenuBase801F() {}
};
struct Menu801F : MenuBase801F {
    void *context;
    MenuSprite801F *sprites;
    VHolder<FlowFaderI> fade;
    int field14;
    int selection;
    int option;
    int level;
    int state;
    virtual void _key();
    ~Menu801F();
};
PMF_TYPE(Menu801FMethod, Menu801F, void, ());
extern "C" {
extern const float lbl_806DA550, lbl_806DA554, lbl_806DA558;
extern const float lbl_806DA55C, lbl_806DA560, lbl_806DA564;
extern const float lbl_806DA568, lbl_806DA56C;
extern char lbl_804E4C28[];
extern char lbl_804E4D30[];
extern Menu801FMethod lbl_804E5050[], lbl_804E51A0[];
void clCGameDemoWC_StubBlr_800adda0(Menu801F *);
void clCGameDemoWC_StubBlr_800adda4();
void clCGameDemoWC_StubBlr_800adda8(int);
int fn_8020A788(FlowFaderI *);
void fn_8020A7CC(FlowFaderI *, int, int, int);
void fn_801F6E98(MenuSprite801F *, unsigned int);
void fn_801F7B74(void *, MenuSprite801F *, float);
void fn_801F6D58(MenuSprite801F *, void *, int, int);
void fn_801F6C2C(MenuSprite801F *, void *, int, int);
void fn_801F7040(MenuSprite801F *, void *, float);
void fn_801F6F7C(MenuSprite801F *, void *, float);
void fn_801F6ED0(MenuSprite801F *, float, float);
void fn_801F7CD8(void *, int);
void *StrPcb_GetInstance();
void StrPcb_RunAndWaitIdle(void *);
void StrPcb_ResetCommands_Neutral(void *, int);
void GX_EndDraw(int);
void GX_BeginDraw();
}
#endif
